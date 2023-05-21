## Java ja C++ võrdlus
Meie projekti eesmärk on võrrelda Java ja C++ keeltes nii keerulisemate kui ka lihtsamate probleemide lahendamist.
Selleks oleme valinud mõned ülesanded, mida lahendada nii Javas kui ka C++-s ning proovida C++-s neid lahendusi 
optimiseerida nii palju kui võimalik ning loodetavasti saama programmid kiiremini tööle.

Leidsime, et C++ jooksutatud lahendused on keskmiselt kaks-kolm korda kiirem kui Javas tehtud lahendused.
Proovisime ka C++ koode optimiseerida, et kiiruse erinevus veel selgemalt välja tuleks. Kiirusevahe tuleb kõige paremini
välja just raskemate ülesannete puhul, kus on rohkem suhtlust mäluga.

Ülesanded valisime ainest LTAT.03.005 "Algoritmid ja Andmestruktuurid".

Java ja C++ ühildamiseks kasutasime JNI ehk Java Native Interface'i.

Ülesannete kirjeldused on vastavate Java meetodite juures.

## Kompileerimine

Projekt kasutab Javat ja C++, käima saamiseks on seega vaja
nii JDK Developer kui ka G++ tööriistu.
Nende installimiseks on tehtud Makefile-s käsk 

```sh
make install
```

Seejärel saab programmi käima panna käsuga

```sh
make run
```

Lisaks saab eraldi kompileerida C++ koodi:
```sh
make compile
```

ja jooksutada ilma uuesti kompileerimata
```sh
make java
```

