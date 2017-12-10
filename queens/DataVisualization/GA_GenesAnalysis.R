setwd("C:/Users/Daniel/Dropbox/GitHub/Genetic-Algorithm/queens/DataVisualization");
#library("data.table")
#library("dplyr")
filename = "Genes.csv"
#filename = "InitialRoad.txt"
all_genes <- read.csv(filename, sep =  ",", header = F)

N_GENERATIONS = 20
N_POPULATION = 10

generation_genes = list()

for(i in 0:(N_GENERATIONS-1) ){
  generation_genes[[i+1]] <- all_genes[ (i*N_POPULATION +1):((i+1)*N_POPULATION) , ] 
}


