---
jupyter:
  colab:
    authorship_tag: ABX9TyP57ce7aBp/vuvNF/0KmH4o
    include_colab_link: true
    name: Comparative Phishing domains analysis.ipynb
  kernelspec:
    display_name: Python 3
    name: python3
  language_info:
    name: python
  nbformat: 4
  nbformat_minor: 0
---

::: {.cell .markdown colab_type="text" id="view-in-github"}
`<a href="https://colab.research.google.com/github/Paradoxxs/Paradoxxs.github.io/blob/main/Comparative_Phishing_domains_analysis.ipynb" target="_parent">`{=html}`<img src="https://colab.research.google.com/assets/colab-badge.svg" alt="Open In Colab"/>`{=html}`</a>`{=html}
:::

::: {.cell .markdown id="9JYZlX-fHCMb"}
The usecase of this project is to detect phishing domains in log files.
This is done by using a random forest classification tree to detect
domain generated algorihms and levensthtein to detect domain that
similar in nature to the top 1m domains.

Compared to the simple analysis this once compares the different
algorihms and select the best one.
:::

::: {.cell .code execution_count="42" id="RGW2OZPFakDF"}
``` {.python}
import math
import warnings
import numpy as np
import pandas as pd
import sklearn
from sklearn import ensemble
from sklearn import feature_extraction
from sklearn.model_selection import train_test_split
from sklearn.metrics import f1_score
from sklearn import tree, linear_model
import sklearn.ensemble as ske
from sklearn.metrics import confusion_matrix
from collections import Counter
```
:::

::: {.cell .code execution_count="43" id="he_yrWuFKOv4"}
``` {.python}
def entropy(s):
    p, lns = Counter(s), float(len(s))
    return -sum(count / lns * math.log(count / lns, 2) for count in list(p.values()))
```
:::

::: {.cell .markdown id="PWgRE56N7pm8"}
Loading the data
:::

::: {.cell .code execution_count="44" id="zNctSWgl7o_y"}
``` {.python}
dga_df = pd.read_csv('https://raw.githubusercontent.com/austin-taylor/flare/master/flare/data/misc/dga_domains.txt', names=['raw_domain'], header=None, encoding='utf-8')
word_df = pd.read_csv('https://raw.githubusercontent.com/austin-taylor/flare/master/flare/data/misc/words.txt', names=['word'], header=None, dtype={'word': np.str}, encoding='utf-8')
alexa_df = pd.read_csv('https://raw.githubusercontent.com/austin-taylor/flare/master/flare/data/alexa/top-1m.csv')
```
:::

::: {.cell .markdown id="Yma91ag6HAH9"}
Preparing the data
:::

::: {.cell .code execution_count="45" colab="{\"base_uri\":\"https://localhost:8080/\"}" id="nND60BeD7ttP" outputId="897373c6-2b17-49db-8343-1c1b74ea7935"}
``` {.python}
alexa_df.columns = ['uri']
alexa_df['domain'] = 'empt'
alexa_df['domain'] =  [alexa_df['uri'][idx].split('.')[0].strip().lower() for idx in alexa_df.index ]
alexa_df = alexa_df.dropna()
alexa_df = alexa_df.drop_duplicates()
alexa_df['class'] = 'legit'
alexa_df = alexa_df.reindex(np.random.permutation(alexa_df.index))
alexa_total = alexa_df.shape[0]
alexa_df = alexa_df[:int(alexa_total * .9)]
alexa_df[:10].index
```

::: {.output .execute_result execution_count="45"}
    Int64Index([147592, 5148, 723318, 524407, 749662, 273432, 235677, 362188,
                823896, 801630],
               dtype='int64')
:::
:::

::: {.cell .code execution_count="46" id="U6VO5CmM7y0A"}
``` {.python}
# Remove Top level domain
dga_df['domain'] = 'empt'
dga_df['domain'] =  [dga_df['raw_domain'][idx].split('.')[0].strip().lower() for idx in dga_df.index]

# Cleanup any blank lines or dups
dga_df = dga_df.dropna()
dga_df = dga_df.drop_duplicates()
dga_total = dga_df.shape[0]

# Set Class
dga_df['class'] = 'dga'

# Hold out 10% of DGA
dga_df = dga_df[:int(dga_total * .9)]
```
:::

::: {.cell .code execution_count="47" id="NXHVdGjH8AMx"}
``` {.python}
# Read in word dictionary for trigrams
word_df = word_df[word_df['word'].map(lambda x: str(x).isalpha())]
word_df = word_df.applymap(lambda x: str(x).strip().lower())
word_df = word_df.dropna()
word_df = word_df.drop_duplicates()
```
:::

::: {.cell .code execution_count="48" id="i0y8N44-76hr"}
``` {.python}
# Merge Domains
all_domains = pd.concat([alexa_df, dga_df], ignore_index=True)

# Features
all_domains['length'] = [len(x) for x in all_domains['domain']]
all_domains = all_domains[all_domains['length'] > 6]
all_domains['entropy'] = [entropy(
    x) for x in all_domains['domain']]
```
:::

::: {.cell .code execution_count="49" colab="{\"base_uri\":\"https://localhost:8080/\"}" id="9uA4MImo8f_v" outputId="709e9f05-5640-4471-b27a-32b2382949a2"}
``` {.python}
alexa_vc = feature_extraction.text.CountVectorizer(
    analyzer='char', ngram_range=(3, 5), min_df=1e-4, max_df=1.0)
print(alexa_vc)
counts_matrix = alexa_vc.fit_transform(alexa_df['domain'])
alexa_counts = np.log10(counts_matrix.sum(axis=0).getA1())
```

::: {.output .stream .stdout}
    CountVectorizer(analyzer='char', binary=False, decode_error='strict',
                    dtype=<class 'numpy.int64'>, encoding='utf-8', input='content',
                    lowercase=True, max_df=1.0, max_features=None, min_df=0.0001,
                    ngram_range=(3, 5), preprocessor=None, stop_words=None,
                    strip_accents=None, token_pattern='(?u)\\b\\w\\w+\\b',
                    tokenizer=None, vocabulary=None)
:::
:::

::: {.cell .code execution_count="50" id="Lls-SxQ2bw5S"}
``` {.python}
dict_vc = feature_extraction.text.CountVectorizer(
    analyzer='char', ngram_range=(3, 5), min_df=1e-5, max_df=1.0)
counts_matrix = dict_vc.fit_transform(word_df['word'])
dict_counts = np.log10(counts_matrix.sum(axis=0).getA1())

all_domains['alexa_grams'] = alexa_counts * \
    alexa_vc.transform(all_domains['domain']).T
all_domains['word_grams'] = dict_counts * \
    dict_vc.transform(all_domains['domain']).T
all_domains['diff'] = all_domains[
    'alexa_grams'] - all_domains['word_grams']

weird_cond = (all_domains['class'] == 'legit') & (
    all_domains['word_grams'] < 3) & (all_domains['alexa_grams'] < 2)


not_weird = all_domains[all_domains['class'] != 'weird']
X = not_weird[['length', 'entropy', 'alexa_grams', 'word_grams']].to_numpy()

# Labels (scikit learn uses 'y' for classification labels)
y = np.array(not_weird['class'].tolist())
```
:::

::: {.cell .code execution_count="51" id="LhiHEod28TXk"}
``` {.python}
# Train on a 80/20 split
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2)
```
:::

::: {.cell .code execution_count="52" id="XGe3BNZU9tQ6"}
``` {.python}
algorithms = {
        "DecisionTree": tree.DecisionTreeClassifier(max_depth=10),
        "RandomForest": ske.RandomForestClassifier(n_estimators=50),
        "GradientBoosting": ske.GradientBoostingClassifier(n_estimators=50),
        "AdaBoost": ske.AdaBoostClassifier(n_estimators=100),
    }
```
:::

::: {.cell .markdown id="lkYZUpPa_Z9i"}
Select the best argorithm and makes a prediction
:::

::: {.cell .code execution_count="53" colab="{\"base_uri\":\"https://localhost:8080/\"}" id="4BYEv0cG9yJA" outputId="2434b509-b095-431d-8b05-8ead64d0ba16"}
``` {.python}
results = {}
print("\nNow testing algorithms")
results = {k:v.fit(X_train, y_train).score(X_test, y_test) for (k,v) in algorithms.items()}
print(results)
```

::: {.output .stream .stdout}

    Now testing algorithms
    {'DecisionTree': 0.9978991450976585, 'RandomForest': 0.9978714110395418, 'GradientBoosting': 0.9971711260720947, 'AdaBoost': 0.9975178017985536}
:::
:::

::: {.cell .code id="Qpw5QJwhRUeX"}
``` {.python}
Display the confusion matrix for each algorithms
```
:::

::: {.cell .code execution_count="107" colab="{\"base_uri\":\"https://localhost:8080/\"}" id="c1R2xXP9OsU1" outputId="69de731c-c38e-445e-f9b3-0e0b3b2775df"}
``` {.python}
predictions = {}
predictions = {k:v.predict(X_test) for (k,v) in algorithms.items()}
results2 = {}
for (k,v) in algorithms.items():
  print(k)
  mt = confusion_matrix(y_test, predictions[k])
  print(mt)
  print("False positive rate %f %%" % ((mt[0][1] / float(sum(mt[0])))*100))
  print('False negative rate %f %%' % ((mt[1][0] / float(sum(mt[1]))*100)))
  print('\n')
```

::: {.output .stream .stdout}
    DecisionTree
    [[   220    240]
     [    63 143704]]
    False positive rate 52.173913 %
    False negative rate 0.043821 %


    RandomForest
    [[   236    224]
     [    83 143684]]
    False positive rate 48.695652 %
    False negative rate 0.057732 %


    GradientBoosting
    [[    95    365]
     [    43 143724]]
    False positive rate 79.347826 %
    False negative rate 0.029910 %


    AdaBoost
    [[   197    263]
     [    95 143672]]
    False positive rate 57.173913 %
    False negative rate 0.066079 %
:::
:::

::: {.cell .code execution_count="109" colab="{\"base_uri\":\"https://localhost:8080/\"}" id="3tQ44-3c_VQN" outputId="224e20f9-45be-47f7-d384-538054d90dab"}
``` {.python}
winner = max(results, key=results.get)
print('best algo %s ' % (winner))
clf = algorithms[winner]
res = clf.predict(X_test)
mt = confusion_matrix(y_test, res)
print(mt)
print("False positive rate %f %%" % ((mt[0][1] / float(sum(mt[0])))*100))
print('False negative rate %f %%' % ( (mt[1][0] / float(sum(mt[1]))*100)))
```

::: {.output .stream .stdout}
    best algo GradientBoosting 
    [[    95    365]
     [    43 143724]]
    False positive rate 79.347826 %
    False negative rate 0.029910 %
:::
:::

::: {.cell .markdown id="RTt46LWa9V8l"}
Train the model on all the data in x and y.
:::

::: {.cell .code execution_count="110" id="GN0Apzg_63Ou"}
``` {.python}
    def predict(domain):
        with warnings.catch_warnings():
            warnings.simplefilter("ignore")
            _alexa_match = alexa_counts * \
                alexa_vc.transform(
                    [domain]).T  # Matrix multiply and transpose
            _dict_match = dict_counts * dict_vc.transform([domain]).T
            _X = [len(domain), entropy(
                domain), _alexa_match, _dict_match]
            if int(sklearn.__version__.split('.')[1]) > 20:
                _X = [_X]
            return clf.predict(_X)[0]
```
:::

::: {.cell .markdown id="Rej3dwTPGZEA"}
levenshtein is used to detect the minimum distance between two words
<https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#Python>
:::

::: {.cell .code execution_count="111" id="0RtXPMLW6Nhh"}
``` {.python}
def levenshtein(source, target):
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

::: {.cell .code execution_count="119" colab="{\"base_uri\":\"https://localhost:8080/\"}" id="XZzSLOUv9Ryp" outputId="ee5d5c02-5dde-44dd-ba8a-d3519a235e7c"}
``` {.python}
#Test scripts
print(dga_c.predict('gDKojad0'))
levenshtein('google.com', 'gool.com')
```

::: {.output .stream .stdout}
    dga
:::

::: {.output .execute_result execution_count="119"}
    2
:::
:::
