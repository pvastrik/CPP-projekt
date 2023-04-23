//
// Created by priid on 23/04/2023.
//

#ifndef PROJEKT_GRAAFID_H
#define PROJEKT_GRAAFID_H

#include <vector>
#include <string>

struct Kaar;

struct Tipp {
    int m_info;

    std::vector<Kaar> *m_kaared;
    int m_kaugus;
    int m_kaari;
    Tipp(int info) : m_info(info){
        m_kaared = new std::vector<Kaar>;
        m_kaugus = -1;
        m_kaari = 0;
    };
    Tipp(const Tipp &tipp) = default;
    //Tipp(Tipp &tipp) = default;
    friend bool operator==(const Tipp&, const Tipp&);



};

struct Kaar {
    int m_kaal;
    Tipp m_algus;
    Tipp m_lopp;
    Kaar(int kaal, Tipp &algus, Tipp &lopp) : m_kaal(kaal), m_algus(algus), m_lopp(lopp){};
};

int tukeldusedRek(double *a, double p, double min, int i, int len);
int getIndex(std::string *arr, std::string s, int n);
void looGraafMaatriksist(int** m, int max, std::vector<Tipp> *graaf);
void jouame(std::string lahtelinn, int x, int k, std::string *linnad, int linnu, std::vector<std::vector<int>*> *mat , std::vector<Tipp> *graaf, std::vector<std::string> *saab);

#endif //PROJEKT_GRAAFID_H


