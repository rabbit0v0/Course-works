import matplotlib.pyplot as plt
from sklearn import datasets, cluster
import numpy as np

n_samples = 1500
blobs = datasets.make_blobs(n_samples=n_samples, centers=2)
noisy_circles = datasets.make_circles(n_samples=n_samples, factor=.5, noise=.05)
noisy_moons = datasets.make_moons(n_samples=n_samples, noise=.05)
dataset = [('blobs', blobs), ('noisy_circles', noisy_circles), ('noisy_moons', noisy_moons)]

for data_i, (data_name, data) in enumerate(dataset):
    X, y = data

    # Plot original data
    plt.subplot(2, 3, data_i + 1)
    plt.scatter(X[:, 0], X[:, 1])
    plt.title(data_name)

    # Cluster data with spectral clustering algorithm

    y_pred = cluster.SpectralClustering(n_clusters=2, affinity='nearest_neighbors', random_state=0).fit_predict(X)

    # Plot data after clustering
    plt.subplot(2, 3, data_i + 4)
    colors = np.array(['#ff7f00', '#4daf4a', '#f781bf', '#a65628', '#984ea3'])
    plt.scatter(X[:, 0], X[:, 1], c=colors[y_pred])
plt.show()
