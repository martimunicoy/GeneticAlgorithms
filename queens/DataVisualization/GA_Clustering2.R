setwd("C:/Users/Daniel/Dropbox/GitHub/Genetic-Algorithm/queens/DataVisualization");

filename = "Genes.csv"
#filename = "InitialRoad.txt"
data <- read.table(filename, sep =  ",", header = F)
my_data <- data
#Tutorial: http://www.sthda.com/english/articles/25-cluster-analysis-in-r-practical-guide/111-types-of-clustering-methods-overview-and-quick-start-r-code/
# install.packages("factoextra")
# install.packages("cluster")
# install.packages("magrittr")

library("cluster")
library("factoextra")
library("magrittr")

####
#Partitioning clustering
###
res.dist <- get_dist(data, stand = TRUE, method = "pearson")
fviz_dist(res.dist, 
          gradient = list(low = "#00AFBB", mid = "white", high = "#FC4E07"))

#Determining optimal number of clusters
library("factoextra")
fviz_nbclust(my_data, kmeans, method = "gap_stat")

k_clusters = 4
set.seed(123)
km.res <- kmeans(my_data, k_clusters, nstart = 25)
# Visualize
library("factoextra")
fviz_cluster(km.res, data = my_data,
             ellipse.type = "convex",
             palette = "jco",
             ggtheme = theme_minimal())

# Compute PAM
library("cluster")
pam.res <- pam(my_data, k_clusters)
# Visualize
fviz_cluster(pam.res)



###
#Hierarchical clustering
###

k_clusters = 4
# Compute hierarchical clustering
res.hc <- data %>%
  scale() %>%                    # Scale the data
  dist(method = "euclidean") %>% # Compute dissimilarity matrix
  hclust(method = "ward.D2")     # Compute hierachical clustering
# Visualize using factoextra
# Cut in 4 groups and color by groups
fviz_dend(res.hc, k = k_clusters, # Cut in four groups
          cex = 0.5, # label size
          k_colors = 1:k_clusters,
          color_labels_by_k = TRUE, # color labels by groups
          rect = TRUE # Add rectangle around groups
)



# Compute
#install.packages("NbClust")
# library("NbClust")
# set.seed(123)
# res.nbclust <- data %>%
#   scale() %>%
#   NbClust(distance = "euclidean",
#           min.nc = 2, max.nc = 10, 
#           method = "complete", index ="all") 
