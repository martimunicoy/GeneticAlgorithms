ex=$1;
file_fitness="Fitness"$ex".csv";
file_genes="Genes"$ex".csv";
troll="";
outputs="";
troll_fitness=$outputs$file_fitness$troll*;
troll_genes=$outputs$file_fitness$troll*;
mv $troll_fitness $file_fitness;
mv $troll_genes $file_genes;

mv Fitness0.csv^M Fitness0.csv