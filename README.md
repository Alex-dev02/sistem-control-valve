# Documentatia sistemului de control al aerului format dintr-un termostat si mai multe valve

### Din ce este alcatuit sistemul si care ii este scopul?

Sistemul este format dintr-un termostat ce comunica cu utilizatorul prin intermediul unei interfete http. Acest termostat ofera posibilitate controlarii unui numar oricare de valve pentru reglarea temperaturii aerului dintr-o incapere.

### Pornirea sistemului

Ordinea de pornire a componentelor sistemului nu afecteaza modul acestuia de functionare. 

Daca incepem cu termostatul (si nu ii punem in subordine valve), atunci va asculta requesturile http si va incerca sa trimita comenzi valvelor, intorcand un raspuns relevant (ex: S-a modificat starea a 0 din 0 valve).

Daca pornim initial valva/valvele, acestea vor aduce temperatura aerului din incapere la 18 grade celsius si o vor mentine acolo, indiferent ca apartin sau nu unui termostat.

### Scenarii plauzibile

Punct de plecare: pornim termostatul si valvele, comunicam termostatului sa se creeze o legatura intre el si o valva sau mai multe pe baza unei adrese ip si a portului pe care aceasta ruleaza. 

Scenarii: 

- Lasam valvele sa mentina temperatura aerului la o valoare predefinita de 18 grade

- Setam un nou target de temperatura pentru valve, urmand ca acestea sa incalzeasca/raceasca aerul din incapere pana se ajunge la targetul stabilit. Intervalul de temperatura acceptat este de 15-28 de grade celsius.

- O valva se opreste din functionare, moment in care la setarea unui nou target ne va fi semnalat faptul ca una din valve nu mai raspunde 

- O valva este deconectata, dar nu oprita. Ea va reveni la temperatura predefinita de 18 grade.

- Termostatul se opreste, dar valvele continua sa functioneze. Dupa cateva secunde de la incetarea comunicarii dintre cele doua dispozitive, valvele se vor intoarce la temperatura predefinita de 18 grade.

### Cazuri neacoperite

- Adaugare pentru punctul 3 din scenariile plauzibile: sa afisam adresa ip si portul valvei care nu mai functioneaza, nu doar sa semnalam ca una sau mai multe nu raspund

- Poate ar trebui sa revenim la valoarea predefina a valvelor daca de exemplu temperatura din incapere nu a mai fost schimbata in ultimele 24 de ore

- Ar fi user friendly ca termostaul sa isi caute valvele in retea, nu sa fie ele adaugate cu ajutorul unei adrese ip si a portului (nu stiu cat de complicat ar fi)

- Eficient ar fi ca atunci cand s-a ajuns la targetul stabilit, valvele sa se opreasca si sa reporneasca daca diferenta dintre temperatura aerului din camera si cea a targetului este mai mare de 0.5 - 1 grade.
