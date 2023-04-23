## Java ja C++ võrdlus
Meie projekti eesmärk on võrrelda Java ja C++ keeltes nii keerulisemate kui ka lihtsamate probleemide lahendamist.
Selleks oleme valinud mõned ülesanded, mida lahendada nii Javas kui ka C++-s ning proovida C++-s neid lahendusi 
optimiseerida nii palju kui võimalik ning loodetavasti saama programmid kiiremini tööle.

Hetkel oleme lihtsalt tegelenud Java kaudu C++ funktsioonide väljakutsumist ning funktsioonid on põhimõtteliselt
täpselt samamoodi ülesehitatud mõlemas keeles, kuid keeltevahelise liikumise tõttu on C++ kaudu väljakutsutud funktsioonid
aeglasemad. Siiski usume, et optimiseerides ning ka keerulisemaid ülesaneid valides, saame neid piisavalt optimiseerida.

Ülesannete kirjeldused on vastavate Java meetodite juures.

Lahendused on veel puudulikud, graafi ülesanne veel C++-s ei lahendu.
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

