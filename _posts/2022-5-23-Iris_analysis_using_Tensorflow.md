---
jupyter:
  colab:
    authorship_tag: ABX9TyNxwNtH47C2puX+BmdHac1d
    include_colab_link: true
    mount_file_id: 1dMEPeUQ2pW7-7AvMic3id0vS3Xj_CVmM
    name: Iris analysis using Tensorflow.ipynb
  kernelspec:
    display_name: Python 3
    name: python3
  language_info:
    name: python
  nbformat: 4
  nbformat_minor: 0
---

::: {.cell .markdown colab_type="text" id="view-in-github"}
`<a href="https://colab.research.google.com/github/Paradoxxs/Paradoxxs.github.io/blob/main/Iris_analysis_using_Tensorflow.ipynb" target="_parent">`{=html}`<img src="https://colab.research.google.com/assets/colab-badge.svg" alt="Open In Colab"/>`{=html}`</a>`{=html}
:::

::: {.cell .markdown id="lWHZWL0aRdoI"}
The iris data analysed using tensorflow. Lets start by importing the
libary we need to perform the analysis
:::

::: {.cell .code execution_count="36" id="UW9HiIoFQZmm"}
``` {.python}
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
import pandas as pd
import numpy as np
#from tensorflow.keras import datasets, layers, models
#from tensorflow.keras.utils import to_categorical
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
import seaborn as sns
```
:::

::: {.cell .markdown id="vjUCCBBaR4up"}
Load the data set and import it into dataframe
:::

::: {.cell .code execution_count="37" id="XjJQaBrMR3aN"}
``` {.python}
df = sns.load_dataset("iris")
```
:::

::: {.cell .markdown id="AA-KmJnEZvZV"}
We can see in the graph the data is clearly sperated.
:::

::: {.cell .code execution_count="38" colab="{\"height\":741,\"base_uri\":\"https://localhost:8080/\"}" id="CTp9ACUYZrob" outputId="db3c58a8-462e-45fa-920f-809d636a4022"}
``` {.python}
sns.set(style="ticks")
sns.set_palette("husl")
sns.pairplot(df.iloc[:,0:6], hue="species")
```

::: {.output .execute_result execution_count="38"}
    <seaborn.axisgrid.PairGrid at 0x7f6318552190>
:::

::: {.output .display_data}
![](vertopal_07c075f8c2134ba6871f577a835be473/f302ccfe69b158503fafffba77a9187daa371d76.png)
:::
:::

::: {.cell .markdown id="u75E5wZUS7BR"}
Split the data into x and y
:::

::: {.cell .code execution_count="39" colab="{\"base_uri\":\"https://localhost:8080/\"}" id="aAAZ37QrS5H3" outputId="c6c1e7f1-5e54-48f4-d00e-0be4ac48047f"}
``` {.python}
X = df.iloc[:,0:4].values
y = df.iloc[:,4].values

print(X.shape)
print(y.shape)
```

::: {.output .stream .stdout}
    (150, 4)
    (150,)
:::
:::

::: {.cell .markdown id="XK3CVnWhTf2I"}
Because tensorflow does not understand the label as string, we have to
convert it into a vector model.
:::

::: {.cell .code execution_count="40" id="LOBva5vaTSVJ"}
``` {.python}
encoder =  LabelEncoder()
y1 = encoder.fit_transform(y)
Y = pd.get_dummies(y1).values
```
:::

::: {.cell .markdown id="wDXP87RIT9HT"}
Split the data into train and test data with a test size of 20%
:::

::: {.cell .code execution_count="41" id="qYYbo0NtT8hp"}
``` {.python}
x_train, x_test, y_train, y_test = train_test_split(X,Y, test_size=0.2, random_state = 4)
```
:::

::: {.cell .code execution_count="45" colab="{\"base_uri\":\"https://localhost:8080/\"}" id="zOazAb3VUh9u" outputId="c8f44806-cd95-4880-bb4f-e7df253eacd5"}
``` {.python}
model = tf.keras.Sequential(
    [
     layers.Dense(4,input_shape=(4,),activation='relu'),
     layers.Dense(3,activation='softmax')
    ])

model.compile(loss='mse', optimizer='adam')
model.summary()
```

::: {.output .stream .stdout}
    Model: "sequential_8"
    _________________________________________________________________
    Layer (type)                 Output Shape              Param #   
    =================================================================
    dense_2 (Dense)              (None, 4)                 20        
    _________________________________________________________________
    dense_3 (Dense)              (None, 3)                 15        
    =================================================================
    Total params: 35
    Trainable params: 35
    Non-trainable params: 0
    _________________________________________________________________
:::
:::

::: {.cell .markdown id="Hpdzd-_9X57y"}
Train the model
:::

::: {.cell .code execution_count="46" colab="{\"base_uri\":\"https://localhost:8080/\"}" id="386GpQJaX7f4" outputId="683ec188-b879-41f2-fbb8-bf079a628af5"}
``` {.python}
model.fit(x_train,y_train, epochs=100)
```

::: {.output .stream .stdout}
    Epoch 1/100
    4/4 [==============================] - 1s 4ms/step - loss: 0.3975
    Epoch 2/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.3893
    Epoch 3/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3790
    Epoch 4/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3689
    Epoch 5/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3604
    Epoch 6/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3587
    Epoch 7/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3611
    Epoch 8/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3611
    Epoch 9/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3590
    Epoch 10/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3578
    Epoch 11/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3575
    Epoch 12/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3575
    Epoch 13/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3570
    Epoch 14/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3560
    Epoch 15/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3556
    Epoch 16/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3551
    Epoch 17/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3545
    Epoch 18/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.3537
    Epoch 19/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3530
    Epoch 20/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3523
    Epoch 21/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.3514
    Epoch 22/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.3505
    Epoch 23/100
    4/4 [==============================] - 0s 5ms/step - loss: 0.3492
    Epoch 24/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3482
    Epoch 25/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.3468
    Epoch 26/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3454
    Epoch 27/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.3439
    Epoch 28/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.3420
    Epoch 29/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3400
    Epoch 30/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3380
    Epoch 31/100
    4/4 [==============================] - 0s 5ms/step - loss: 0.3355
    Epoch 32/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.3326
    Epoch 33/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3294
    Epoch 34/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3260
    Epoch 35/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.3223
    Epoch 36/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3186
    Epoch 37/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.3149
    Epoch 38/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.3120
    Epoch 39/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3093
    Epoch 40/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3073
    Epoch 41/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.3062
    Epoch 42/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3056
    Epoch 43/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.3048
    Epoch 44/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3040
    Epoch 45/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3032
    Epoch 46/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.3025
    Epoch 47/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.3015
    Epoch 48/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.3006
    Epoch 49/100
    4/4 [==============================] - 0s 5ms/step - loss: 0.2998
    Epoch 50/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.2987
    Epoch 51/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2977
    Epoch 52/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2966
    Epoch 53/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2955
    Epoch 54/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.2945
    Epoch 55/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.2931
    Epoch 56/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2918
    Epoch 57/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2904
    Epoch 58/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.2888
    Epoch 59/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.2872
    Epoch 60/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2854
    Epoch 61/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2831
    Epoch 62/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2812
    Epoch 63/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.2771
    Epoch 64/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2734
    Epoch 65/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2678
    Epoch 66/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.2620
    Epoch 67/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2549
    Epoch 68/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.2500
    Epoch 69/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.2461
    Epoch 70/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.2435
    Epoch 71/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2403
    Epoch 72/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.2373
    Epoch 73/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2345
    Epoch 74/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.2322
    Epoch 75/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.2289
    Epoch 76/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2262
    Epoch 77/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.2236
    Epoch 78/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.2216
    Epoch 79/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.2188
    Epoch 80/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2164
    Epoch 81/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2139
    Epoch 82/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.2116
    Epoch 83/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.2091
    Epoch 84/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.2067
    Epoch 85/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.2044
    Epoch 86/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.2021
    Epoch 87/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.2003
    Epoch 88/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.1975
    Epoch 89/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.1953
    Epoch 90/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.1929
    Epoch 91/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.1904
    Epoch 92/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.1882
    Epoch 93/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.1856
    Epoch 94/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.1832
    Epoch 95/100
    4/4 [==============================] - 0s 6ms/step - loss: 0.1808
    Epoch 96/100
    4/4 [==============================] - 0s 4ms/step - loss: 0.1785
    Epoch 97/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.1759
    Epoch 98/100
    4/4 [==============================] - 0s 2ms/step - loss: 0.1738
    Epoch 99/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.1719
    Epoch 100/100
    4/4 [==============================] - 0s 3ms/step - loss: 0.1689
:::

::: {.output .execute_result execution_count="46"}
    <keras.callbacks.History at 0x7f63130ac310>
:::
:::

::: {.cell .code execution_count="47" id="naRHBlu7ggVL"}
``` {.python}
y_pred = model.predict(x_test)
y_test_class = np.argmax(y_test,axis=1)
y_pred_class = np.argmax(y_pred,axis=1)
```
:::

::: {.cell .markdown id="8JM-emzvh0X7"}
As you can see in the confusion matrix it not a perfect precisions of
the pedels some of them got miss classified.
:::

::: {.cell .code execution_count="48" colab="{\"base_uri\":\"https://localhost:8080/\"}" id="q6JsXZ-egjrp" outputId="98a839cc-fdd5-4451-a573-5b36cf8704cf"}
``` {.python}
from sklearn.metrics import classification_report,confusion_matrix
print(classification_report(y_test_class,y_pred_class))
print(confusion_matrix(y_test_class,y_pred_class))
```

::: {.output .stream .stdout}
                  precision    recall  f1-score   support

               0       1.00      0.62      0.77        16
               1       0.33      0.80      0.47         5
               2       0.62      0.56      0.59         9

        accuracy                           0.63        30
       macro avg       0.65      0.66      0.61        30
    weighted avg       0.78      0.63      0.67        30

    [[10  4  2]
     [ 0  4  1]
     [ 0  4  5]]
:::
:::

::: {.cell .markdown id="5J7tsUcfiYku"}
Lets test the model aginst our own data The expected result should look
like this `<br>`{=html} 0 = setosa 1 = versicolor 2 = virginica
:::

::: {.cell .code execution_count="49" colab="{\"base_uri\":\"https://localhost:8080/\"}" id="sZauUZxohog4" outputId="1e72062e-3167-45b8-dd7f-3b234197e8f8"}
``` {.python}
X_test2 = np.array([[5.1, 3.0, 1.4, 0.2],[7,3.2,4.9,1.5],[5.9,3.0,5.1,2]])#setosa, versicolor, virginica
y_pred2 = model.predict(X_test2)
y_pred2
```

::: {.output .execute_result execution_count="49"}
    array([[0.38907152, 0.37413585, 0.23679265],
           [0.20330702, 0.48684758, 0.30984536],
           [0.18420696, 0.24002235, 0.57577074]], dtype=float32)
:::
:::

::: {.cell .code execution_count="50" colab="{\"base_uri\":\"https://localhost:8080/\"}" id="_qEVXFluiiPw" outputId="55778c04-bc79-45cc-a144-e5fb9a5fb722"}
``` {.python}
print(np.argmax(y_pred2,axis=1))
```

::: {.output .stream .stdout}
    [0 1 2]
:::
:::
