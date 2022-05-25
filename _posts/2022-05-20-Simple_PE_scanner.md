---
jupyter:
  colab:
    authorship_tag: ABX9TyOFAwdTlBKFdBu/azqQY/f7
    history_visible: true
    include_colab_link: true
    mount_file_id: "https://github.com/Paradoxxs/Paradoxxs.github.io/blob/main/Simple_PE_scanner.ipynb"
    name: Simple PE scanner.ipynb
  kernelspec:
    display_name: Python 3
    name: python3
  language_info:
    name: python
  nbformat: 4
  nbformat_minor: 0
---

::: {.cell .markdown colab_type="text" id="view-in-github"}
`<a href="https://colab.research.google.com/github/Paradoxxs/Paradoxxs.github.io/blob/main/Simple_PE_scanner.ipynb" target="_parent">`{=html}`<img src="https://colab.research.google.com/assets/colab-badge.svg" alt="Open In Colab"/>`{=html}`</a>`{=html}
:::

::: {.cell .code id="qQUIyP16n3Og"}
``` {.python}
import pandas as pd
import numpy as np
import pickle
import sklearn.ensemble as ske
from sklearn.model_selection import train_test_split
from sklearn import tree, linear_model
from sklearn.feature_selection import SelectFromModel
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import confusion_matrix
```
:::

::: {.cell .markdown id="9RHoB2odopDY"}
Load data
:::

::: {.cell .code colab="{\"base_uri\":\"https://localhost:8080/\"}" id="kBZxqO6qoBsf" outputId="d41b62d3-5a0e-48ad-f5c8-e9df1c737021"}
``` {.python}
data = pd.read_csv('/content/drive/MyDrive/Data science/Data/antivirus_demo_data.csv', sep='|')
X = data.drop(['Name', 'md5', 'legitimate'], axis=1).values
y = data['legitimate'].values

print('Researching important feature based on %i total features\n' % X.shape[1])
```

::: {.output .stream .stdout}
    Researching important feature based on 54 total features
:::
:::

::: {.cell .markdown id="QZq2yR7ApZEa"}
Feature selection using Trees Classifier
:::

::: {.cell .code id="qi6UEFt8oCQY"}
``` {.python}
fsel = ske.ExtraTreesClassifier().fit(X, y)
model = SelectFromModel(fsel, prefit=True)
X_new = model.transform(X)
nb_features = X_new.shape[1]
```
:::

::: {.cell .markdown id="gd76HdNmpKlQ"}
Split the data into to test and train
:::

::: {.cell .code id="PXUo-6YipJc9"}
``` {.python}
X_train, X_test, y_train, y_test = train_test_split(X_new, y ,test_size=0.2)
```
:::

::: {.cell .code colab="{\"base_uri\":\"https://localhost:8080/\"}" id="G0pE1He5oF_4" outputId="64b65e0e-6161-4e78-a200-21f4f7bd2102"}
``` {.python}
features = []

print('%i features identified as important:' % nb_features)
```

::: {.output .stream .stdout}
    13 features identified as important:
:::
:::

::: {.cell .code colab="{\"base_uri\":\"https://localhost:8080/\"}" id="qRWMTGoaoJAf" outputId="7e450951-dd8b-4a1e-d603-83298764e7b0"}
``` {.python}
indices = np.argsort(fsel.feature_importances_)[::-1][:nb_features]
for f in range(nb_features):
    print("%d. feature %s (%f)" % (f + 1, data.columns[2+indices[f]], fsel.feature_importances_[indices[f]]))


```

::: {.output .stream .stdout}
    1. feature DllCharacteristics (0.152100)
    2. feature Machine (0.104096)
    3. feature SectionsMaxEntropy (0.073897)
    4. feature VersionInformationSize (0.073672)
    5. feature Characteristics (0.067896)
    6. feature Subsystem (0.063009)
    7. feature MajorSubsystemVersion (0.062743)
    8. feature ImageBase (0.050253)
    9. feature ResourcesMaxEntropy (0.044595)
    10. feature ResourcesMinEntropy (0.043756)
    11. feature SizeOfOptionalHeader (0.043518)
    12. feature MajorOperatingSystemVersion (0.025248)
    13. feature SectionsMinEntropy (0.020449)
:::
:::

::: {.cell .markdown id="G-zuitAUsnzd"}
Defines the algorithm for comparison inside a dictionary
:::

::: {.cell .code id="6FQpPcdyoMkX"}
``` {.python}
algorithms = {
        "DecisionTree": tree.DecisionTreeClassifier(max_depth=10),
        "RandomForest": ske.RandomForestClassifier(n_estimators=50),
        "GradientBoosting": ske.GradientBoostingClassifier(n_estimators=50),
        "AdaBoost": ske.AdaBoostClassifier(n_estimators=100),
    }
```
:::

::: {.cell .markdown id="lbwhMDMlstbN"}
For loop for testing the different algorithms using a list comprehension
over dictionary
:::

::: {.cell .code colab="{\"base_uri\":\"https://localhost:8080/\"}" id="1_lLgMg63icw" outputId="41f289de-671b-4edd-930a-1b612e1002a0"}
``` {.python}
results = {}
print("\nNow testing algorithms")
results = {k:v.fit(X_train, y_train).score(X_test, y_test) for (k,v) in algorithms.items()}
print(results)
```

::: {.output .stream .stdout}

    Now testing algorithms
    {'DecisionTree': 0.9912712785222746, 'RandomForest': 0.9943498732343354, 'GradientBoosting': 0.9883375588554871, 'AdaBoost': 0.9867077145961608}
:::
:::

::: {.cell .markdown id="lsDVTW1Ws00m"}
Printing out the algroithm with the higest score.
:::

::: {.cell .code colab="{\"base_uri\":\"https://localhost:8080/\"}" id="46423YX_oROo" outputId="ec76543b-ca0d-40e2-9224-d8737a8dc651"}
``` {.python}
winner = max(results, key=results.get)
print(' %s with a %f %%' % (winner, results[winner]*100))
```

::: {.output .stream .stdout}
     RandomForest with a 99.434987 %
:::
:::

::: {.cell .code colab="{\"base_uri\":\"https://localhost:8080/\"}" id="0WaVG5I7oUqq" outputId="778942d3-0b26-48a7-e943-2a4835eec6c4"}
``` {.python}
# Identify false and true positive rates
clf = algorithms[winner]
res = clf.predict(X_test)
mt = confusion_matrix(y_test, res)
print(mt)
print("False positive rate %f %%" % ((mt[0][1] / float(sum(mt[0])))*100))
print('False negative rate %f %%' % ( (mt[1][0] / float(sum(mt[1]))*100)))
```

::: {.output .stream .stdout}
    [[19207    87]
     [   69  8247]]
    False positive rate 0.450917 %
    False negative rate 0.829726 %
:::
:::
