# TO DO List
Si alguna cosa de la llista la completem, al principi del punt/linia posar (FET)

## Report
Això crec que ho hauriem d'anar planejant a partir de demà (divendres 08/12/2017) ja, abans de fer més i més millores xd

For each assignment a report must be written including:
* introduction stating the problem and the algorithm to solve it,
* the code of the program,
* the results of running the program and
* conclusions.

Overleaf: https://www.overleaf.com/12684672zycygkcnmryh#/48375443/

## Ultra prioritaries per poder fer analisi de resultats

* (FET) 1r: a les strategies crec que el WriteFitness hauria d'astar abans del if on fa un break, ja que si no, encas que faci el break llavors la fitness de la ultima generació no es printarà o qè? potser noentenc ben be aquest if look for a solution

```
// Sum up 1 generation
        n_gen++;

        // Look out for a solution
        if (best->scorer == 0 && !args.force_to_continue)
        {
            exit_code = 1;
            break;
        }

        // Write fitness
        if (args.write_fitness && n_gen <= args.max_fitness_points)
            write_fitness(&file, file_fitness, population, args.n_population,
                          n_gen);
```

* (FET) 2n: const FILE_FITNESS (que també podem posar als args.in per poder decidir el nom del fitxer, així podre associar el fitxer Fitness1.csv amb args1.in, per exemple). Més que nom del fixter contindria la direció sencera per exemple: DataVisualization/subfolderquebvulgui/nomarxiu)

* (FET) 3r.1) Afegir el write_genes que podem recuperar de la branca analysys_stuff per que en un arxiu escrigui els gens dels individus de la població cada certes iteracions com la write_fitness (ho he mirat i es LO MATEIX que el write fitness). SERIA COM DUPLICAR COSES: WRITE_FITNESS seria WRITE_GENES, MAX_FITNESS_POINTS seria MAX_GENES_POINTS.

* (FET) 3r.2) L'anterior aniria acompanyat amb un FILE_GENES per poder decidir el nom del arxiu (de fet la direció sensera DataVisualization/subfolderquebvulgui/nomarxiu) on posar els genes de les poblacions


* Amb els punts anteriors ja podriem fer estudis més facilment tenint controlats els arxius

* (això per exempel jo podria implementar funcions a R així que fero al C seria secundari, suposo) Per estudiar convergència: Afegir al summary quin percentatge de la població a convergit a l'òptim (el best individual)? (fent la norma euclidiana de sempre per exemple) i retornar el percentage de la població que ho ha fet? (95% segons [3])



## Prioritaries

* Potser convé definir unes constants MAX_VARIABLE, MIN_VARIABLE (una per cada variable)
i que s'usi a la llibreria arguments per controlar quin es el rang de valors permès.

* (FET) Unknown bug that causes a segmentation fault error while writting the results through express_genes() function.

* (FET) Millora de la funció **find_best**: si hi ha individus amb la mateixa scorer crec que sempre es quedarà amb el primer que troba (per la desigualtat estricte; i es quedaria amb l'últim que trobés si posesim desigualtat no estricta, crec). Llavors la idea de millorar-ho era d'entre els que tenen la mateixa scorer triar un at random. Així sense pensar massa crec que és bastant útil al principi, però al final si molts individus són iguals potser ja no tant. (tanmateix, si la implementació no es gaire costosa computacionalment llavors no passaria res)

* Queden pendents els TODO (allà on hi hagi '@'). Entre ells comentar algunes funcions que vaig deixar pendents (algunes que tú sabrás explicar millor). Estaria bé deixar enllestits els comentaris de funcions, la resta de coses amb @ que siguin improvements afegir-los en aquesta llista si cal.

* (FET) Afegir al summary el temps d'execució actual (el que porta fins a la generació en questió).

* (FET) Rallada the **strategies.c**: si no m'equivoco la part de codi de cadascuna de les strategies on posa:

```
 T = population;
        population = nextpopulation;
        nextpopulation = T;
        evaluate(population, args.n_population, args.n_queens);

        for (i = 0; i < args.n_population; i++)
            if (population[i].scorer < best->scorer)
                best = &population[i];

        if (args.summarize_freq != 0)
            if ((n_gen-1) % args.summarize_freq == 0)
                summarize(population, best, n_gen-1, args.n_population);

        n_gen++;

        if (best->scorer == 0 && !args.force_to_continue)
            return best;

        if (args.write_fitness && n_gen <= args.max_fitness_points)
            write_fitness(&file, file_fitness, population, args.n_population, n_gen);

```

es repeteix en totes, i quan vulguem canviar alguna cosa referent a quant imprimir coses per pantalla, en arxius etc etc, doncs llavors caldrà canviaro en totes. La qüestió és: **és molt lio fer una funció a part a la mateixa llibreria strategies si vols, que faci això??**.

* (FET) BUG mig chorra sobre el writefitness: mhe adonat que les fitness de l'última població quan troba l'òptim i para, no és afegida al .csv (crec que posant el write_fitness just abans del if aquell que fa un exit ho solucionaria)



## Sobre la marxa

* Anar afegint les references

* Anar completant els README.md, manuals, etc



## No tant importants, només si dóna temps o més endavant.

* Sobretot al main: separar les inicialitzacions de variables per poder comentar cadascuna al costat (potser no cal, ho deixo aquí per recordar-m'ho).

* (FET) Al readme posar Authors al principi

* (FET) Canviar el correu danysalgado14@gmail.com per daniel.salgado@e-campus.uab.cat (readme, .c ... ?)




## Idees per analitzar l'algoritme a partir de resultats

* Fixats uns parametres raonables, estudiar com evoluciona el temps total d'execució en funció de N (nombre de queens).

* Vaig deixar penjada la branca analysis_stuff on estava tot allò que vaig fer de dimenssional reduction etc, si cal ja ho recuperaré i ho afegire a mà al master per no liarla amb merges ni històries.

*

## Implementacions extra (de flipats de la vida)

* (FET) Fer un altra (programa) arxiu .c (main) que utilitzant les altres llibreries i maquinaria que tenim, puguem fer com un procés iteratiu que vagi cridant la funció genetic algorithm, vagi registrant les solucions que troba i les que hagi trobat donar-les com a invalides (això últim és el que seria chungo, d'entrada). Fixar com un nombre màxim d'iteracions i veure quantes troba. Per N= 8 sabem que n'hi ha 92 de solucions diferents.

* Adaptative mutation rate (veure pàgina 34 de la referència [2]).  Allà es parla d'una tal $\sigma^2$, que fent el símil jo crec que per nosalres seria la probabilitat de mutar: p_mutation.

* La fitness function que tenim crec que es o(N^2). A la referència [5] sembla que proposen una fitness que és o(2N-1) (osigi linial)



## Comentari (ja es un poc tard per fer-ho)

* M'he fixat que potser des del principi hagués estat convenient una struct que es digués Population{ Individual * individuals; int size} per
no tener que pasar sempre com a parametre n_pop. Això ens permetria també considerar poblacions amb mida variable, ja que la mida vindria controlada per la variable size.
