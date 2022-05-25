---
jupyter:
  colab:
    authorship_tag: ABX9TyNEZ49LpoIH3ZaM1IN16DHb
    include_colab_link: true
    name: Phishing domains analysis.ipynb
  kernelspec:
    display_name: Python 3
    name: python3
  language_info:
    name: python
  nbformat: 4
  nbformat_minor: 0
---

::: {.cell .markdown colab_type="text" id="view-in-github"}
`<a href="https://colab.research.google.com/github/Paradoxxs/Paradoxxs.github.io/blob/main/Phishing_domains_analysis.ipynb" target="_parent">`{=html}`<img src="https://colab.research.google.com/assets/colab-badge.svg" alt="Open In Colab"/>`{=html}`</a>`{=html}
:::

::: {.cell .code id="iDB5Cnh7PSK0"}
``` {.python}
```
:::

::: {.cell .code execution_count="1" id="RGW2OZPFakDF"}
``` {.python}
import math
import os
import re
import warnings
import numpy as np
import pandas as pd
import sklearn
from sklearn import ensemble
from sklearn import feature_extraction
from sklearn.model_selection import train_test_split
from sklearn.metrics import f1_score
from collections import Counter
import lightgbm as lgb
```
:::

::: {.cell .code execution_count="2" id="5CDw0swKd5GH"}
``` {.python}
class Alexa(object):

    def __init__(self, limit=1000000):
        self.limit = limit

    def __contains__(self, word):
        return self.domain_in_alexa(word)
```
:::

::: {.cell .code execution_count="3" id="he_yrWuFKOv4"}
``` {.python}
def entropy(s):
    p, lns = Counter(s), float(len(s))
    return -sum(count / lns * math.log(count / lns, 2) for count in list(p.values()))
```
:::

::: {.cell .code execution_count="4" id="Lls-SxQ2bw5S"}
``` {.python}
class dga_classifier(object):

    def __init__(self):
        print('[*] Initializing... training classifier - Please wait.')
        #self.a = Alexa()
        dga_df = pd.read_csv('dga_domains.txt', names=['raw_domain'], header=None, encoding='utf-8')
        word_df = pd.read_csv('words.txt', names=['word'], header=None, dtype={'word': np.str}, encoding='utf-8')
        self.entropy = entropy
        #self.domain_extract = domain_extract

        alexa_df = pd.read_csv('top-1m.csv')
        alexa_df.columns = ['uri']

        alexa_df['domain'] = 'empt'
        alexa_df['domain'] =  [alexa_df['uri'][idx].split('.')[0].strip().lower() for idx in alexa_df.index ]

        #alexa_df['domain'] = [self.domain_extract(uri) for uri in alexa_df['uri']]
        alexa_df = alexa_df.dropna()
        alexa_df = alexa_df.drop_duplicates()
        alexa_df['class'] = 'legit'
        alexa_df = alexa_df.reindex(np.random.permutation(alexa_df.index))
        alexa_total = alexa_df.shape[0]
        alexa_df = alexa_df[:int(alexa_total * .9)]
        alexa_df[:10].index



        # Blacklist values just differ by captilization or .com/.org/.info
   

        # Remove Top level domain
        dga_df['domain'] = 'empt'
        dga_df['domain'] =  [dga_df['raw_domain'][idx].split('.')[0].strip().lower() for idx in dga_df.index]
       
        #for idx in dga_df.index:
         # dga_df['domain'][idx] = dga_df['raw_domain'][idx].split('.')[0].strip().lower() 
        #dga_df['domain'] = dga_df.applymap(lambda x: x.split('.')[0].strip().lower())
      
        # Cleanup any blank lines or dups
        dga_df = dga_df.dropna()
        dga_df = dga_df.drop_duplicates()
        dga_total = dga_df.shape[0]

        # Set Class
        dga_df['class'] = 'dga'

        # Hold out 10% of DGA
        dga_df = dga_df[:int(dga_total * .9)]

        # Merge Domains
        all_domains = pd.concat([alexa_df, dga_df], ignore_index=True)

        # Features
        all_domains['length'] = [len(x) for x in all_domains['domain']]
        all_domains = all_domains[all_domains['length'] > 6]
        all_domains['entropy'] = [self.entropy(
            x) for x in all_domains['domain']]


        self.alexa_vc = feature_extraction.text.CountVectorizer(
            analyzer='char', ngram_range=(3, 5), min_df=1e-4, max_df=1.0)
        print(self.alexa_vc)
        counts_matrix = self.alexa_vc.fit_transform(alexa_df['domain'])
        self.alexa_counts = np.log10(counts_matrix.sum(axis=0).getA1())

        # Read in word dictionary for trigrams
        word_df = word_df[word_df['word'].map(lambda x: str(x).isalpha())]
        word_df = word_df.applymap(lambda x: str(x).strip().lower())
        word_df = word_df.dropna()
        word_df = word_df.drop_duplicates()

        self.dict_vc = feature_extraction.text.CountVectorizer(
            analyzer='char', ngram_range=(3, 5), min_df=1e-5, max_df=1.0)
        counts_matrix = self.dict_vc.fit_transform(word_df['word'])
        self.dict_counts = np.log10(counts_matrix.sum(axis=0).getA1())

        all_domains['alexa_grams'] = self.alexa_counts * \
            self.alexa_vc.transform(all_domains['domain']).T
        all_domains['word_grams'] = self.dict_counts * \
            self.dict_vc.transform(all_domains['domain']).T
        all_domains['diff'] = all_domains[
            'alexa_grams'] - all_domains['word_grams']

        weird_cond = (all_domains['class'] == 'legit') & (
            all_domains['word_grams'] < 3) & (all_domains['alexa_grams'] < 2)


        not_weird = all_domains[all_domains['class'] != 'weird']
        X = not_weird[['length', 'entropy', 'alexa_grams', 'word_grams']].to_numpy()

        # Labels (scikit learn uses 'y' for classification labels)
        y = np.array(not_weird['class'].tolist())

        # Train on a 80/20 split
        X_train, X_test, y_train, y_test = train_test_split(
            X, y, test_size=0.2)

        print('[+] Training classifier on training set')

        clf = ensemble.RandomForestClassifier(n_estimators=20, oob_score=True)
        clf.fit(X_train, y_train)
        y_pred = clf.predict(X_test)

        print('[+] Out of sample legit f1 score {}'.format(f1_score(
            y_test == 'legit', 
            y_pred == 'legit',
            pos_label = 1,
        )))

        print('[+] Out of sample dga f1 score {}'.format(f1_score(
            y_test == 'legit', 
            y_pred == 'legit',
            pos_label = 0,
        )))
        
        print('[+] Training final classifier')
        self.clf = ensemble.RandomForestClassifier(n_estimators=20, oob_score=True)
        self.clf.fit(X, y)
        print('[+] Classifier Ready')

    def ngram_count(self, domain):
        # Multiply and transpose vector
        alexa_match = self.alexa_counts * self.alexa_vc.transform([domain]).T
        dict_match = self.dict_counts * self.dict_vc.transform([domain]).T
        print(('%s Alexa match: %d, Dict match: %d' % (domain, alexa_match, dict_match)))
        return domain, alexa_match, dict_match

    def predict(self, domain):
        with warnings.catch_warnings():
            warnings.simplefilter("ignore")
            _alexa_match = self.alexa_counts * \
                self.alexa_vc.transform(
                    [domain]).T  # Matrix multiply and transpose
            _dict_match = self.dict_counts * self.dict_vc.transform([domain]).T
            _X = [len(domain), self.entropy(
                domain), _alexa_match, _dict_match]
            if int(sklearn.__version__.split('.')[1]) > 20:
                _X = [_X]
            return self.clf.predict(_X)[0]
```
:::

::: {.cell .code execution_count="5" id="rITmDweia80L"}
``` {.python}
url = 'https://raw.githubusercontent.com/llSourcell/antivirus_demo/master/data.csv'

data = pd.read_csv(url, sep='|')
#X = data['ip'].values
#y = data['url'].values
```
:::

::: {.cell .code execution_count="6" id="0RtXPMLW6Nhh"}
``` {.python}
def levenshtein(source, target):
    # Source
    # https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#Python
    if len(source) < len(target):
        return levenshtein(target, source)

    # So now we have len(source) >= len(target).
    if len(target) == 0:
        return len(source)

    # We call tuple() to force strings to be used as sequences
    # ('c', 'a', 't', 's') - numpy uses them as values by default.
    source = np.array(tuple(source))
    target = np.array(tuple(target))

    # We use a dynamic programming algorithm, but with the
    # added optimization that we only need the last two rows
    # of the matrix.
    previous_row = np.arange(target.size + 1)
    for s in source:
        # Insertion (target grows longer than source):
        current_row = previous_row + 1

        # Substitution or matching:
        # Target and source items are aligned, and either
        # are different (cost of 1), or are the same (cost of 0).
        current_row[1:] = np.minimum(
            current_row[1:],
            np.add(previous_row[:-1], target != s))

        # Deletion (target grows shorter than source):
        current_row[1:] = np.minimum(
            current_row[1:],
            current_row[0:-1] + 1)

        previous_row = current_row

    return previous_row[-1]
```
:::

::: {.cell .code execution_count="7" colab="{\"base_uri\":\"https://localhost:8080/\"}" id="gvM8DhULIlDk" outputId="70ee6010-16a8-4342-a7f2-b880eb2c380c"}
``` {.python}
dga_c = dga_classifier()
```

::: {.output .stream .stdout}
    [*] Initializing... training classifier - Please wait.
    CountVectorizer(analyzer='char', binary=False, decode_error='strict',
                    dtype=<class 'numpy.int64'>, encoding='utf-8', input='content',
                    lowercase=True, max_df=1.0, max_features=None, min_df=0.0001,
                    ngram_range=(3, 5), preprocessor=None, stop_words=None,
                    strip_accents=None, token_pattern='(?u)\\b\\w\\w+\\b',
                    tokenizer=None, vocabulary=None)
    [+] Training classifier on training set
:::

::: {.output .stream .stderr}
    /usr/local/lib/python3.7/dist-packages/sklearn/ensemble/_forest.py:523: UserWarning: Some inputs do not have OOB scores. This probably means too few trees were used to compute any reliable oob estimates.
      warn("Some inputs do not have OOB scores. "
    /usr/local/lib/python3.7/dist-packages/sklearn/ensemble/_forest.py:528: RuntimeWarning: invalid value encountered in true_divide
      predictions[k].sum(axis=1)[:, np.newaxis])
:::

::: {.output .stream .stdout}
    [+] Out of sample legit f1 score 0.9988381234650359
    [+] Out of sample dga f1 score 0.6288888888888889
    [+] Training final classifier
:::

::: {.output .stream .stderr}
    /usr/local/lib/python3.7/dist-packages/sklearn/ensemble/_forest.py:523: UserWarning: Some inputs do not have OOB scores. This probably means too few trees were used to compute any reliable oob estimates.
      warn("Some inputs do not have OOB scores. "
    /usr/local/lib/python3.7/dist-packages/sklearn/ensemble/_forest.py:528: RuntimeWarning: invalid value encountered in true_divide
      predictions[k].sum(axis=1)[:, np.newaxis])
:::

::: {.output .stream .stdout}
    [+] Classifier Ready
:::
:::

::: {.cell .code execution_count="14" colab="{\"base_uri\":\"https://localhost:8080/\"}" id="XZzSLOUv9Ryp" outputId="ebbe0ded-1670-4f06-e236-48e0e4f654f1"}
``` {.python}
#Test scripts
print(dga_c.predict('4dg6Fdfa'))
levenshtein('google.com', 'gool.com')
```

::: {.output .stream .stdout}
    dga
:::

::: {.output .execute_result execution_count="14"}
    2
:::
:::
