setwd("C:/Users/Daniel/Dropbox/GitHub/Genetic-Algorithm/queens/DataVisualization");

filename = "Fitness.csv"
#filename = "InitialRoad.txt"
data <- read.table(filename, sep =  ",", header = F)
#datat <- t(data)
generations <- data[,1]
fitness <- data[ , 2:dim(data)[2]]
fitness_opt <- apply(fitness, 1, min)
plot(generations, rowMeans(fitness), type = 'l', ylim = c(0,36), main = "Average v.s. best fitness", ylab = "Fitness", xlab = "Generation")
lines(generations, fitness_opt, col = "blue")