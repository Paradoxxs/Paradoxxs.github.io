## Clustering Text Data Using Word Embeddings and K-means Algorithm

In the field of natural language processing (NLP), clustering text data is a common task that involves grouping similar documents together based on their content. In this blog post, we will explore how to use word embeddings and the K-means algorithm to cluster a collection of articles written in Danish.
For this demonstration, we will use a dataset of article titles that I have scraped from the internet

### Word Embeddings with Word2Vec

To represent the textual data numerically, we will use word embeddings, which capture the semantic meaning of words in a vector space. In this case, we will utilize pre-trained word embeddings from the Word2Vec model.


we load the pre-trained Word2Vec model, which has been trained on a large corpus of text data. This model allows us to convert phrases into dense vector representations.

````py
import pandas as pd
import numpy as np
from sklearn.cluster import KMeans
from gensim import models
import tensorflow as tf

model = models.Word2Vec.load(r'dsl_skipgram_2020_m5_f500_epoch2_w5.model')
````

### Transforming Phrases into Vectors

We define a function called `word2vec` that takes a list of phrases as input and converts each phrase into a vector representation using the Word2Vec model. To achieve this, we tokenize each phrase into individual words, remove stopwords, and then look up the word vectors from the Word2Vec model. We calculate the average vector for each phrase and store the resulting vectors in a list.

````py
def word2vec(phrases):
    list_sentences = []

    for phrase in phrases:
        sentence = []
        tokens = word_tokenize(phrase)
        filtered_tokens = [word for word in tokens if word in model.wv]
        for token in filtered_tokens:
            try:
                sentence.append(model.wv[token])
            except KeyError:
                pass
        
        # Calculate the average vector for the sentence
        if sentence:
            sentence_vector = tf.reduce_mean(sentence, axis=0)
            list_sentences.append(sentence_vector)
        else:
            # Some of the sentence was filled with words not present in the model so they have to be filled with empty numpy tensor
            list_sentences.append(np.zeros(500))
````




Next, we convert the list of sentence vectors into a TensorFlow `tf.Tensor` object for further processing.
´´´´py
    # Convert the list of sentence vectors to a tf.Tensor object
    tensor_sentences = tf.convert_to_tensor(list_sentences, dtype=tf.float32)
    return tensor_sentences
´´´´

````py
embeddings = word2vec(df["title"].values.tolist())
````

### Creating the Data Matrix

To prepare the data for clustering, we convert the sentence vectors into a Pandas DataFrame. Each row in the DataFrame represents a sentence, and each column represents a dimension of the vector.

````py
arrays=[]
for i in range(len(df["title"].values.tolist())):
 arrays.append(np.array(embeddings[i]))
sentencematrix = np.empty((len(df["title"].values.tolist()),500,), order = "F")
for i in range(len(df["title"].values.tolist())):
 sentencematrix[i]=arrays[i]
pandasmatrix=pd.DataFrame(sentencematrix)
````

### Determining the Optimal Number of Clusters

Before performing the actual clustering, we need to determine the optimal number of clusters. We use the elbow method, which calculates the sum of squared distances for different values of k (the number of clusters). By plotting the average distortion (a measure of clustering quality) against the number of clusters, we can identify the "elbow" point that represents the optimal number of clusters.

### Clustering with K-means

Using the optimal number of clusters determined from the elbow method, we apply the K-means algorithm to cluster the data. We initialize the K-means algorithm with the desired number of clusters and fit it to the data matrix.

````
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.metrics import pairwise_distances

# Assuming pandasmatrix is your data matrix

# Calculate the sum of squared distances for different values of k
distortions = []
k_values = range(2, 11)  # Range of k values to try

for k in k_values:
    kmeans = KMeans(n_clusters=k, random_state=0)
    kmeans.fit(pandasmatrix)
    distortions.append(sum(np.min(pairwise_distances(pandasmatrix, kmeans.cluster_centers_, metric='euclidean'), axis=1)) / pandasmatrix.shape[0])

# Plot the elbow curve
plt.plot(k_values, distortions, 'bx-')
plt.xlabel('Number of clusters (k)')
plt.ylabel('Average distortion')
plt.title('Elbow Method')
plt.show()
````

I this case I found the optimal number of cluster to be *6*. Let train the KMeans model to be looking for *6* clusters 
````
m = KMeans(6)
m.fit(pandasmatrix)
pandasmatrix['topic'] = m.labels_
pandasmatrix['sentences']=df
````

### Results and Analysis

After clustering, we can inspect the resulting clusters and the sentences within each cluster. In this example, we assign each sentence in the data matrix to a specific cluster and print out the sentences belonging to the cluster labeled as 0.

```python
print(pandasmatrix.loc[pandasmatrix['topic'] == 0, 'sentences'])
```

### Conclusion

Clustering text data is a valuable technique in various NLP applications, such as document categorization and recommendation systems. In this blog post, we demonstrated how to cluster the title of articles using word embeddings and the K-means algorithm. The process involved transforming phrases into word vectors, creating a data matrix, determining the optimal number of clusters, and finally, performing the clustering. However, keep in mind that the presented model uses pre-trained word embeddings and may not be suitable for specific domains or contexts. If you intend to put this approach into production, it would be advisable to train a new model using domain-specific data to improve the performance and relevance of the clustering results.
By following the steps outlined in this blog post, you can apply text clustering  techniques to your own datasets and gain insights from large collections of text documents. Remember to adapt the code and models to fit your specific needs and domain expertise.