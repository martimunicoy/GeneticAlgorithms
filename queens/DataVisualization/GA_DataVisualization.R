#LIBRARIES 
library("data.table")
library("dplyr")

EXAMPLE = 0

#READ INPUT FILE
setwd("C:/Users/Daniel/Dropbox/GitHub/Genetic-Algorithm/queens/DataVisualization/inputs");
INPUT_FILENAME = paste("args",EXAMPLE,".in", sep = "")
ARGS <- read.table(INPUT_FILENAME, sep =  " ", header = F, nrows = 10)

VAL <- ARGS$V2
VAR <- as.character(ARGS$V1)
ARGS <- data.frame(VAR, VAL)


#INITIALISE CONSTANT VARIABLES

N = ARGS[ARGS == "N_QUEENS",2]
WORST_FITNESS = N*(N+1)/2
N_POPULATION = ARGS[ARGS == "N_POPULATION",2]
N_GENERATIONS = ARGS[ARGS == "N_GENERATIONS",2]
N_DEATHS = ARGS[ARGS == "N_DEATHS",2]
P_MUTATION = ARGS[ARGS == "P_MUTATION",2]
LAMBDA = ARGS[ARGS == "LAMBDA",2]
TOURNAMENT_SELECTIONS = ARGS[ARGS == "TOURNAMENT_SELECTIONS",2]
FRAC_WEIGTH = ARGS[ARGS == "FRAC_WEIGTH",2]
DENOM_POWER = ARGS[ARGS == "DENOM_POWER",2]
STRATEGY = ARGS[ARGS == "STRATEGY",2]

#FITNESS
setwd("C:/Users/Daniel/Dropbox/GitHub/Genetic-Algorithm/queens/DataVisualization");

filename = "Fitness_sample.csv"
#filename = "InitialRoad.txt"
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


