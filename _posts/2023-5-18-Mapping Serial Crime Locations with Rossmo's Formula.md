In today's post, we'll dive into an intriguing topic in criminal psychology and data science: the Rossmo Algorithm. Named after its creator, criminologist Kim Rossmo, this algorithm aims to predict a serial criminal's base of operations based on the geographical locations of their crimes. 

For our study, we will use Python and a variety of libraries to create a heatmap of likely hotspots in Atlanta, GA. This data is based onAtlanta’s murders of 1979–1981. 
## Importing Necessary Libraries

```python
from geopandas import GeoDataFrame
from shapely.geometry import Point, Polygon
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import contextily as cx
```

We'll be using geopandas and shapely for geographical data handling, matplotlib for visualization, and pandas for data manipulation.

## Defining our Crime Locations

```python
atlanta = [[33.703093, -84.532406], [33.660032, -84.49509], [33.741141, -84.383959], ... ]
```

These points represent hypothetical crime scenes in Atlanta.

## Defining Rossmo formula

These functions are the building blocks of Rossmo formula. 
Let's go through each function:

```python
def manhattan(A, B):
    return abs(A[0] - B[0]) + abs(A[1] - B[1])
```
Calculates the Manhattan distance between two points in a plane. The Manhattan distance, also known as Taxicab geometry or L1 distance, calculates the distance that would be traveled to get from one data point to the other if a grid-like path is followed. The Manhattan distance between two items is the sum of the differences of their corresponding components. Here, `A` and `B` represent two points, where each is a list containing the x and y coordinates.

```py
def nearest(A, L):
    n = len(L)
    m = A
    d = 0
    p = 0
    j = 0
    while True:
      if A[0] != L[j][0] or A[1] != L[j][1]:
        #m = L[j]
        d = manhattan(A,L[j])
        p = j
        break 
      else: j += 1
    for i in range(len(L)):
      dis = manhattan(A,L[i])
      if dis != 0 and dis < d:
        d = dis
        p = i
    return L[p]
```
Finds the nearest point to a given point `A` from a list `L` of points using the Manhattan distance. `A` is a point and `L` is a list of points. For each point in `L`, it computes the Manhattan distance to `A`, and keeps track of the smallest distance it found. It finally returns the point in `L` that had the smallest distance to `A`.

```py
def radius_buffer(L):
    s = 0
    n = len(L)
    for i in range(n):
      M = L.copy()
      del M[i]
      B = nearest(L[i], M)
      s += manhattan(L[i],B)
    return s/(2*n)
```
Computes an average distance, referred to as a 'buffer radius'. It takes in a list `L` of points. For each point in the list, it computes the Manhattan distance to the nearest point in the list (excluding itself), sums these distances, and finally divides the sum by twice the number of points. This serves as an average radius buffer based on the crime locations.

```py
def proba(i, j, L):
    proba = 0
    f = 1/3
    g = 2/3
    B = radius_buffer(L)
    for p in range(len(L)):
      d = manhattan(L[p], [i,j])
      if d > B:
        proba += 1/(d**f)
      else:
        proba += B**(g-f)/((2*B - d)**g)
    return proba

```
This function calculates the Rossmo probability for a point `(i,j)` with respect to a list `L` of points. This function embodies the core of the Rossmo formula. `i` and `j` are the x and y coordinates of the point, and `L` is a list of points. For each point in `L`, it computes the Manhattan distance to `(i,j)`. If this distance is greater than the buffer radius, it adds `1/(d**f)` to the probability (where `f` is 1/3). If the distance is less than the buffer radius, it adds `B**(g-f)/((2*B - d)**g)` to the probability (where `g` is 2/3 and `B` is the buffer radius). It finally returns the computed probability. This probability value indicates the likelihood that a given grid point could be a potential base for the criminal, based on the Rossmo formula.
These functions collectively serve to apply the Rossmo formula to a given set of locations (points), thereby identifying probable hotspots for a serial criminal's base.



## Preparing the Data

We transform our crime locations into a pandas DataFrame and extract some necessary parameters. We then convert this into a GeoDataFrame to handle the geographical data.

```python
data = pd.DataFrame(atlanta, columns=["lat", "lon"])
...
geometry = [Point(xy) for xy in zip(data["lon"], data["lat"])]
gdf = GeoDataFrame(data, geometry=geometry, crs='EPSG:4326')
```

## Creating Grid Squares

We set a predefined square size and create a grid of these squares covering the entire crime area. We then calculate the center of each square and assign it a 'probability' value based on the Rossmo formula.

```python
...
squares = [
    GeoDataFrame(geometry=[Polygon([
        (lon_min + j * x_diff, lat_min + i * y_diff),
        ...
squares_df['probability'] = squares_df.apply(lambda row: proba(row['lat'], row['lon'], atlanta), axis=1)
```

## Visualizing the Data

Finally, we use matplotlib to create a heatmap representing the calculated probabilities for each square. The crime locations are also plotted for reference.

```python
cmap = plt.cm.get_cmap('viridis')
with plt.style.context('seaborn-whitegrid'):
    ax = squares_df.plot(column='probability', cmap=cmap, figsize=(10, 10), alpha=0.2, edgecolor='k')
    gdf.plot(ax=ax, marker='o', color='red', markersize=25)
    cx.add_basemap(ax, zoom=12)
    sm = plt.cm.ScalarMappable(cmap=cmap)
    sm._A = []
    cbar = plt.colorbar(sm, shrink=0.5)
    plt.show()
```

This will yield a plot where higher probability regions are highlighted. This probabilistic approach provides a tool for law enforcement to prioritize certain areas in their investigations of serial crimes. 

![](..\assets\rossmo.png)

This is a simple demonstration of the Rossmo Algorithm. In a real-world application, data would be more complex and extensive, requiring further processing and refining of the algorithm and the variables used for the calculating.

Remember, this algorithm and others like it are just tools to aid investigators. They are not definitive answers but can provide valuable insights that, combined with traditional investigative methods, can help solve cases.

Stay tuned for more criminal intelligence projects