//
// Created by priid on 20/05/2023.
//

#ifndef PROJEKT_ISIKUKOODID_H
#define PROJEKT_ISIKUKOODID_H

#include <vector>
#include <algorithm>

/**
   * @Funktsionaalsus - Rakendab counting sorti algoritmi, et teostada isikukoodide sorteerimist paisktabelis.
   * @Parameetrid - Isikukoodide vector, "kohaVaartus" isikukoodis sisalduva numbri koht mida võrreldakse, "kohti" on maksimaalne väärtus mida antud number saada võib.
*/
std::vector<long> loendamisMeetod(std::vector<long>& isikukoodid, long kohaVaartus, int kohti) {
    int suurus = isikukoodid.size();
    std::vector<int> sagedus(kohti);
    std::vector<long> sorteeritud(suurus);
    for (long l : isikukoodid) {
        int indeks = static_cast<int>((l / kohaVaartus) % 10);
        sagedus[indeks]++;
    }
    for (int i = 1; i < kohti; i++) {
        sagedus[i] += sagedus[i - 1];
    }
    for (int i = suurus - 1; i >= 0; i--) {
        int indeks = static_cast<int>((isikukoodid[i] / kohaVaartus) % 10);
        sorteeritud[sagedus[indeks] - 1] = isikukoodid[i];
        sagedus[indeks]--;
    }
    return sorteeritud;
}


/**
    * @Funktsionaalsus: Sorteerib isikukoodid sünniaja järgi
    * a) järjestuse aluseks on sünniaeg, vanemad inimesed on eespool.
    * b) kui sünniajad on võrdsed, määrab järjestuse isikukoodi järjekorranumber (kohad 8-10).
    * c) kui ka järjekorranumber on võrdne, siis määrab järjestuse esimene number.
    * @Parameetrid: isikukoodid sorteeritav isikukoodide massiiv
 */
void sort(std::vector<long>& isikukoodid) {
    int suurus = isikukoodid.size();
    std::vector<int> sagedus(2);
    std::vector<long> sorteeritud(suurus);
    for (long isik : isikukoodid) {
        int indeks = static_cast<int>((isik / 10000000000L) + 1) % 2;
        sagedus[indeks]++;
    }
    sagedus[1] += sagedus[0];
    for (int i = suurus - 1; i >= 0; i--) {
        int indeks = static_cast<int>((isikukoodid[i] / 10000000000L) + 1) % 2;
        sorteeritud[sagedus[indeks] - 1] = isikukoodid[i];
        sagedus[indeks]--;
    }
    std::copy(sorteeritud.begin(), sorteeritud.end(), isikukoodid.begin());
    std::vector<long> isikukoodid2 = isikukoodid;
    long kohaVaartus = 10L;
    for (int i = 0; i < 4; i++) {
        isikukoodid2 = loendamisMeetod(isikukoodid2, kohaVaartus, 10);
        kohaVaartus *= 10L;
    }
    isikukoodid2 = loendamisMeetod(isikukoodid2, kohaVaartus, 4);
    kohaVaartus *= 10L;
    isikukoodid2 = loendamisMeetod(isikukoodid2, kohaVaartus, 10);
    kohaVaartus *= 10L;
    isikukoodid2 = loendamisMeetod(isikukoodid2, kohaVaartus, 2);

    sagedus = std::vector<int>(500);
    for (long isik : isikukoodid2) {
        int esimene = static_cast<int>(isik / 10000000000L);
        int indeks;
        if (esimene % 2 == 0) {
            indeks = esimene * 50 + static_cast<int>((isik / 100000000) % 100);
        } else {
            indeks = (esimene + 1) * 50 + static_cast<int>((isik / 100000000) % 100);
        }
        sagedus[indeks]++;
    }
    for (int i = 1; i < 500; i++) {
        sagedus[i] += sagedus[i - 1];
    }
    for (int i = suurus - 1; i >= 0; i--) {
        int esimene = static_cast<int>(isikukoodid2[i] / 10000000000L);
        int indeks;
        if (esimene % 2 == 0) {
            indeks = esimene * 50 + static_cast<int>((isikukoodid2[i] / 100000000) % 100);
        } else {
            indeks = (esimene + 1) * 50 + static_cast<int>((isikukoodid2[i] / 100000000) % 100);
        }
        sorteeritud[sagedus[indeks] - 1] = isikukoodid2[i];
        sagedus[indeks]--;
    }
    std::copy(sorteeritud.begin(), sorteeritud.end(), isikukoodid.begin());
}


#endif //PROJEKT_ISIKUKOODID_H
