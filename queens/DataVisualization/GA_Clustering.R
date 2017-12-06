setwd("C:/Users/Daniel/Dropbox/GitHub/Genetic-Algorithm/queens/DataVisualization");

filename = "Genes.csv"
#filename = "InitialRoad.txt"
data <- read.table(filename, sep =  ",", header = F)

#Tutorial: https://www.statmethods.net/advstats/cluster.html
#mydata = scale(data)
mydata = scale(data[1:40,])
k_clusters = 3
# Determine number of clusters
wss <- (nrow(mydata)-1)*sum(apply(mydata,2,var))
for (i in 2:15) wss[i] <- sum(kmeans(mydata, 
                                     centers=i)$withinss)
plot(1:15, wss, type="b", xlab="Number of Clusters",
     ylab="Within groups sum of squares")












# K-Means Cluster Analysis
fit <- kmeans(mydata, k_clusters) # 5 cluster solution
# get cluster means 
aggregate(mydata,by=list(fit$cluster),FUN=mean)
# append cluster assignment
mydata <- data.frame(mydata, fit$cluster)




# K-Means Clustering with 5 clusters
fit <- kmeans(mydata, k_clusters)

# Cluster Plot against 1st 2 principal components

# vary parameters for most readable graph
library(cluster) 
clusplot(mydata, fit$cluster, color=TRUE, shade=TRUE, 
         labels=2, lines=0)

# Centroid Plot against 1st 2 discriminant functions
library(fpc)
plotcluster(mydata, fit$cluster)


