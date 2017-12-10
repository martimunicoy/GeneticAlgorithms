#LIBRARIES 
#library("data.table")
#library("dplyr")

EXAMPLE = 6
STRATEGY = 6
#READ INPUT FILE
setwd("C:/Users/Daniel/Dropbox/GitHub/Genetic-Algorithm/queens/DataVisualization/inputs");
#setwd("/home/dsalgador/Dropbox/GitHub/Genetic-Algorithm/queens/DataVisualization/inputs")
INPUT_FILENAME = paste("args",EXAMPLE, "_s", STRATEGY ,".in", sep = "")
ARGS <- read.table(INPUT_FILENAME, sep =  " ", header = F, nrows = 10)

VAL <- ARGS$V2
VAR <- as.character(ARGS$V1)
ARGS <- data.frame(VAR, VAL)


#INITIALISE CONSTANT VARIABLES

N = ARGS[ARGS == "N_QUEENS",2]
WORST_FITNESS = N*(N+1)/2
N_POPULATION = ARGS[ARGS == "N_POPULATION",2]
N_GENERATIONS = ARGS[ARGS == "N_GENERATIONS",2]+1
N_DEATHS = ARGS[ARGS == "N_DEATHS",2]
P_MUTATION = ARGS[ARGS == "P_MUTATION",2]
LAMBDA = ARGS[ARGS == "LAMBDA",2]
TOURNAMENT_SELECTIONS = ARGS[ARGS == "TOURNAMENT_SELECTIONS",2]
FRAC_WEIGTH = ARGS[ARGS == "FRACT_WEIGTH",2]
DENOM_POWER = ARGS[ARGS == "DENOM_POWER",2]
STRATEGY = ARGS[ARGS == "STRATEGY",2]

#FITNESS
setwd("C:/Users/Daniel/Dropbox/GitHub/Genetic-Algorithm/queens/DataVisualization/outputs");
#setwd("/home/dsalgador/Dropbox/GitHub/Genetic-Algorithm/queens/DataVisualization/outputs")
FITNESS_FILENAME = paste("Fitness",EXAMPLE,
                          "_s", STRATEGY ,".csv", sep = "")
#FITNESS_FILENAME = "Fitness_sample.csv"
data <- read.table(FITNESS_FILENAME, sep =  ",", header = F)
#datat <- t(data)


##PLOTS FOR THE FITNESS

generations <- data[,1]
fitness <- data[ , 2:dim(data)[2]]
fitness_opt <- apply(fitness, 1, min)
color_opt = "blue"
color_avg = "black"
color_ideal = "green"
lw = 2;
max_fitness = max(fitness)

nameplot1 = paste("fitness",EXAMPLE,
                  "_s", STRATEGY , ".png", sep="")
#par(mfrow = c(1,1))

png(nameplot1, width = 415, height = 289)
#png(nameplot1, width = 415*2, height = 289*2)

par(xpd = T, mar = par()$mar + c(0,0,0,5))
plot(generations, rowMeans(fitness), lwd=lw, type = 'l', ylim = c(0,max_fitness), main = "Fitness evolution", ylab = "Fitness", xlab = "Generation")
lines(generations, fitness_opt, col = color_opt, lwd = lw)
lines(c(1, N_GENERATIONS), c(0,0), col = color_ideal, lwd = lw)

C0 <- paste("Strategy = ", STRATEGY, sep = "")
C1 <- paste("N = ", N, sep="")
C2 <- paste("n_pop = ", N_POPULATION, sep="")
C3 <- paste("n_gen = ", N_GENERATIONS, sep="")
C4 <- paste("death_ratio = ", N_DEATHS, sep="")
C5 <- paste("p_m = ", P_MUTATION, sep="")
C6 <- paste("lambda = ", LAMBDA, sep="")
C7 <- paste("K = ", TOURNAMENT_SELECTIONS, sep="")
C8 <- paste("W = ", FRAC_WEIGTH, sep="")
C9 <- paste("E = ", DENOM_POWER, sep="")

legend(N_GENERATIONS, max_fitness,
       c(C0,C1, C2,C3,C4,C5, C6,C7,C8,C9),
       cex = 0.8,
       bty = 'n')
legend("topright", c("Average fitness","Minimum fitness", "Ideal fitness"), col = c(color_avg,color_opt,color_ideal),lwd=lw, bty ='n', cex = 0.8, seg.len = 0.5)

par(mar=c(5, 4, 4, 2) + 0.1)
dev.off()

#############
##HISTOGRAM PLOT OF THE LAST GENERATION FITNESS 
#############
nameplot2 = paste("lastfitnesshist",EXAMPLE ,
                  "_s", STRATEGY , ".png", sep="")
png(nameplot2, width = 415, height = 289)


last_fitness = t(fitness[N_GENERATIONS,]) 
max_last_fitness = max(last_fitness)

hist(last_fitness, freq= TRUE, breaks = WORST_FITNESS, xlim = c(0,max_last_fitness), xlab ="Fitness" ,main = "Histogram of the last generation fitnesses")
dev.off()


# plot(density(last_fitness))
# abline(v = 0)
# var(as.numeric(last_fitness) )
# plot(generations, as.numeric(apply(fitness,1,sd)) , type = 'l')


