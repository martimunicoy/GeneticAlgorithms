# TO DO List
Si alguna cosa de la llista la completem, al principi del punt/linia posar (FET)

## Prioritaries

* Potser convé definir unes constants MAX_VARIABLE, MIN_VARIABLE (una per cada variable)
i que s'usi a la llibreria arguments per controlar quin es el rang de valors permès.

* Queden pendents els TODO (allà on hi hagi '@'). Entre ells comentar algunes funcions que vaig deixar pendents (algunes que tú sabrás explicar millor). Estaria bé deixar enllestits els comentaris de funcions, la resta de coses amb @ que siguin improvements afegir-los en aquesta llista si cal.

## Sobre la marxa

* Anar completant els README.md, manuals, etc.

## No tant importants, només si dóna temps o més endavant.

* Sobretot al main: separar les inicialitzacions de variables per poder comentar cadascuna al costat (potser no cal, ho deixo aquí per recordar-m'ho).

## Idees per analitzar l'algoritme a partir de resultats

* Fixats uns parametres raonables, estudiar com evoluciona el temps total d'execució en funció de N (nombre de queens).

* Vaig deixar penjada la branca analysis_stuff on estava tot allò que vaig fer de dimenssional reduction etc, si cal ja ho recuperaré i ho afegire a mà al master per no liarla amb merges ni històries.

*

## Implementacions extra (de flipats de la vida)

* Adaptative mutation rate (veure pàgina 34 de la referència [2]).  Allà es parla d'una tal $\sigma^2$, que fent el símil jo crec que per nosalres seria la probabilitat de mutar: p_mutation.

* La fitness function que tenim crec que es o(N^2). A la referència [5] sembla que proposen una fitness que és o(2N-1) (osigi linial)


## Comentari (ja es un poc tard per fer-ho)

* M'he fixat que potser des del principi hagués estat convenient una struct que es digués Population{ Individual * individuals; int size} per
no tener que pasar sempre com a parametre n_pop. Això ens permetria també considerar poblacions amb mida variable, ja que la mida vindria controlada per la variable size.
