//
// Created by priid on 20/05/2023.
//

#ifndef PROJEKT_TUKELDUSED_H
#define PROJEKT_TUKELDUSED_H



/**
 * @Funktsionaalsus: Tükeldab rekursiivselt jupi sobivateks pikkusteks.
 * @Parameetrid: "a" on massiiv, kus on juppide pikkused. "p" on järeloleva traadi pikkus. "min" on minimaalse jupi pikkus. "i" on tükelduste arv. "len" on traadi pikkus.
 * @Returns: Sorteeritud isikukoodide Java Array.
 */
int tukeldusedRek(double *a, double p, double min, int i, int len) {
    int kokku = 0;
    if (p < min) {
        if (p >= 0) return 1;
        return 0;
    }

    for (; i < len; i++) {
        if (a[i] > p) break;
        kokku += tukeldusedRek(a, p - a[i], min, i, len);
    }
    return kokku;

}

#endif //PROJEKT_TUKELDUSED_H
