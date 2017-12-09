setwd("C:/Users/Daniel/Dropbox/GitHub/Genetic-Algorithm/queens/DataVisualization");

filename = "Fitness_sample.csv"
#filename = "InitialRoad.txt"

#INPUT PARAMETERS 

N = 8
WORST_FITNESS = N*(N+1)/2

data <- read.table(filename, sep =  ",", header = F)
#datat <- t(data)


generations <- data[,1]
fitness <- data[ , 2:dim(data)[2]]
fitness_opt <- apply(fitness, 1, min)
color_opt = "blue"
color_avg = "black"
color_ideal = "green"
lw = 2;
max_fitness = max(fitness)

par(mfrow = c(1,1))
plot(generations, rowMeans(fitness), lwd=lw, type = 'l', ylim = c(0,max_fitness), main = "Average v.s. best fitness", ylab = "Fitness", xlab = "Generation")
lines(generations, fitness_opt, col = color_opt, lwd = lw)
abline(h = 0, col = color_ideal, lwd = lw)
legend("topright", c("Average fitness","Minimum fitness", "Ideal fitness"), col = c(color_avg,color_opt,color_ideal),lwd=lw, bty ='n', cex = 1, seg.len = 0.5)


length(fitness)
last_fitness = t(fitness[length(fitness)]) 
max_last_fitness = max(last_fitness)

hist(last_fitness, breaks = WORST_FITNESS, xlim = c(0,max_last_fitness), xlab ="Fitness" ,main = "Histogram of the last generation fitnesses")



plot(density(last_fitness))
abline(v = 0)
var(as.numeric(last_fitness) )


plot(generations, as.numeric(apply(fitness,1,sd)) , type = 'l')


