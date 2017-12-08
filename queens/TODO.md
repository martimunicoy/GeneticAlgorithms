# TO DO List

## Prioritaries

* Millora de la funció **find_best**: si hi ha individus amb la mateixa scorer crec que sempre es quedarà amb el primer que troba (per la desigualtat estricte; i es quedaria amb l'últim que trobés si posesim desigualtat no estricta, crec). Llavors la idea de millorar-ho era d'entre els que tenen la mateixa scorer triar un at random. Així sense pensar massa crec que és bastant útil al principi, però al final si molts individus són iguals potser ja no tant. (tanmateix, si la implementació no es gaire costosa computacionalment llavors no passaria res)

* Queden pendents els TODO (allà on hi hagi '@'). Entre ells comentar algunes funcions que vaig deixar pendents (algunes que tú sabrás explicar millor). Estaria bé deixar enllestits els comentaris de funcions, la resta de coses amb @ que siguin improvements afegir-los en aquesta llista si cal.

* Afegir al summary el temps d'execució actual (el que porta fins a la generació en questió).



## Sobre la marxa

* Anar afegint les references

* Anar completant els README.md, manuals, etc



## No tant importants, només si dóna temps o més endavant.

* Sobretot al main: separar les inicialitzacions de variables per poder comentar cadascuna al costat (potser no cal, ho deixo aquí per recordar-m'ho).

* Al readme posar Authors al principi

* Canviar el correu danysalgado14@gmail.com per daniel.salgado@e-campus.uab.cat (readme, .c ... ?)




## Idees per analitzar l'algoritme a partir de resultats

* Fixats uns parametres raonables, estudiar com evoluciona el temps total d'execució en funció de N (nombre de queens).

*

*

## Implementacions extra (de flipats de la vida)

* Fer un altra (programa) arxiu .c (main) que utilitzant les altres llibreries i maquinaria que tenim, puguem fer com un procés iteratiu que vagi cridant la funció genetic algorithm, vagi registrant les solucions que troba i les que hagi trobat donar-les com a invalides (això últim és el que seria chungo, d'entrada). Fixar com un nombre màxim d'iteracions i veure quantes troba. Per N= 8 sabem que n'hi ha 92 de solucions diferents.

* 