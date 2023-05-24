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



$$p_ij=k \sum_{n=1}^c[\frac{\varphi}{(|x_i-x_n|+|y_j-y_n|)^f}+\frac{(1-\varphi)(B^{8-f})}{(2B-|x_i-x_n|-|y_i-y_n|)^g}]$$


Where:

$ \varphi_{j,i} \begin{cases}
    1 & if (|X_i-x_n|+|Y_j-y_n|)>B\\
    0 & else
\end{cases}$

The first term of the formula is known as the "distance decay function". This term accounts for the principle that the probability of a crime occurring decreases as the distance from the crime location increases.
Where $f$ defined the amount of decay 

The second term deals with the concept of a buffer zone, which describes the idea of criminal not wanting to commit crimes in the area where they live. 


Lets break down the formula into functions. 
Let's go through each function:

```python
def calculate_manhattan_distance(point_A, point_B):
    return abs(point_A[0] - point_B[0]) + abs(point_A[1] - point_B[1])
```
Calculates the Manhattan distance between two points in a plane. The Manhattan distance, also known as Taxicab geometry or L1 distance, calculates the distance that would be traveled to get from one data point to the other if a grid-like path is followed. The Manhattan distance between two items is the sum of the differences of their corresponding components. Here, `A` and `B` represent two points, where each is a list containing the x and y coordinates.

```py
def find_nearest_neighbor(target_point, list_of_points):
    shortest_distance = float('inf')  # initializing shortest_distance to infinity
    nearest_point = None
    for point in list_of_points:
        if target_point != point:  # ensuring we don't compare the point to itself
            distance = calculate_manhattan_distance(target_point, point)
            if distance < shortest_distance:
                shortest_distance = distance
                nearest_point = point
    return nearest_point
```
Finds the nearest point to a given point `target pont` from a `list of points` using the Manhattan distance. For each point in the list, the distance to the `target point` is calculated. It finally returns the point in the `list` that had the smallest distance to `Target`.
```py
def calculate_buffer_radius(crime_locations):
    total_distance = 0
    num_locations = len(crime_locations)
    for point in crime_locations:
        nearest_point = find_nearest_neighbor(point, crime_locations)
        total_distance += calculate_manhattan_distance(point, nearest_point)
    return total_distance / (2 * num_locations)
```
Computes an average distance, referred to as a 'buffer radius'. It takes in a list `crime_locaitons` of points. For each point in the list, it computes the Manhattan distance to the nearest point in the list (excluding itself), sums these distances, and finally divides the sum by twice the number of points. This serves as an average radius buffer based on the crime locations.

```py
def calculate_probability(target_x, target_y, crime_locations):  
    probability = 0
    buffer_radius = calculate_buffer_radius(crime_locations)
    f = 1 / 3
    g = 2 / 3
    for crime_location in crime_locations:
        distance = calculate_manhattan_distance(crime_location, [target_x, target_y])
        if distance > buffer_radius:
            probability += 1 / (distance ** f)
        else:
            probability += buffer_radius ** (g - f) / ((2 * buffer_radius - distance) ** g)
    return probability
```


This function calculates the Rossmo probability for a point `(x,y)` with respect to a list of crime location. This function embodies the core of the Rossmo formula. For each location in `crime_locations`, it computes the Manhattan distance to `(x,y)`. If this distance is greater than the buffer radius, it adds `1/(d**f)` to the probability (where `f` is 1/3). If the distance is less than the buffer radius, it adds `B**(g-f)/((2*B - d)**g)` to the probability (where `g` is 2/3 and `B` is the buffer radius). It finally returns the computed probability. This probability value indicates the likelihood that a given grid point could be a potential base for the criminal, based on the Rossmo formula.

These functions collectively serve to apply the Rossmo formula to a given set of locations (points), thereby identifying the probable hotspots for a serial criminal's base.


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