#include <iostream>
#include <vector>

#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <limits>
#include <queue>
#include <algorithm>

struct Kaar;

struct GTipp {

    int info{0};
    int kaari{0};
    std::vector<Kaar> kaared;

    GTipp() = default;
    GTipp(int i) : info(i), kaari(0) {}
    GTipp(GTipp const &tipp) : info(tipp.info), kaari(tipp.kaari), kaared(tipp.kaared){}
    bool operator==(const GTipp& other) const {
        return info == other.info;
    }
};

struct Kaar {
    int kaugus;
    GTipp* algus;
    GTipp* lopp;

    Kaar(int k, GTipp* a, GTipp* l) : kaugus(k), algus(a), lopp(l) {}

    Kaar(const Kaar &other) : kaugus(other.kaugus), algus(other.algus), lopp(other.lopp) {}
    Kaar& operator=(const Kaar& other) {
        if (this != &other) {
            algus = other.algus;
            lopp = other.lopp;
            kaugus = other.kaugus;
        }
        return *this;
    }
    bool operator==(const Kaar& other) const {
        return algus == other.algus && lopp == other.lopp;
    }
};

/**
 * @Funktsionaalsus: Loob linnade maatriksist graafi.
 * @Parameetrid: "m" on maatriks. "max" on maksimaalne pikkus. "graaf" on graaf mida hakkame looma.
 */
std::vector<GTipp*> graafiks(std::vector<std::vector<int>>& M, int x) {
    std::vector<GTipp*> graaf;
    for (int i = 0; i < M.size(); i++) {
        GTipp *tipp = nullptr;
        if (graaf.size() <= i) {
            tipp = new GTipp(i);
            graaf.push_back(tipp);
        } else {
            tipp = graaf.at(i);
        }

        for (int j = 0; j < M.size(); j++) {
            GTipp *teine = nullptr;
            if (j >= graaf.size()) {
                teine = new GTipp(j);
                graaf.push_back(teine);
            } else {
                teine = graaf.at(j);
            }
            if (M.at(i).at(j) > 0 && M.at(i).at(j) <= x) {
                Kaar kaar(M.at(i).at(j), tipp, teine);
                tipp->kaared.push_back(kaar);
            }
        }
    }
    return graaf;
}



struct Pair {
    std::vector<std::string> linnad;
    std::vector<std::vector<int>> matrix;
};

/**
 * @Funktsioon: Meetod teeb antud tsv failist maatriksi ja linnade nimede vektori
 * @Parameetrid: faili nimi ja maksimaalne kaugus, mis pikkusega servad maatriksisse lisatakse.
 * @Tulemus: paar, milles on täisarvude maatriks, mis kirjeldab linnadevahelist graafi, ja massiiv linnade nimedest, et saaks hiljem indeksite järgi nimed teada.
 * */
Pair maatriksiks(const std::string& failinimi, int maxkaugus) {
    std::vector<std::vector<std::string>> andmed;
    try {
        std::ifstream file(failinimi);
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string token;
            std::vector<std::string> row;
            while (std::getline(ss, token, '\t')) {
                row.push_back(token);
            }
            andmed.push_back(row);
        }
    } catch (const std::exception& e) {
        std::cout<< e.what()<<"\n";
        return Pair{};
    }

    std::vector<std::string> linnad(andmed.size());
    std::vector<std::vector<int>> mat(linnad.size(), std::vector<int>(linnad.size(), 0));

    for (int i = 0; i < andmed.size(); i++) {
        linnad[i] = andmed[i][0];
        for (int j = 1; j <= andmed.size(); j++) {
            if (i == j-1) continue;
            std::string anne = andmed[i][j];
            int kaugus = std::stoi(anne);
            mat.at(i).at(j-1) = (kaugus > maxkaugus) ? -1 : kaugus;
        }
    }


    return Pair{linnad, mat};
}

/**
 * @Funktsioon: Meetod antud laadimiste arvu kaugusel olevate linnade leidmiseks
 * @Parameetrid: lähtelinn, elektriauto aku suurus (km) x, lubatud laadimiste arv k, linnade massiiv, linnade hulk ,graafi esitus maatriksina, graaf ise, array linnadest kuhu saame sõita.
 * @Tulemus: linnade massiiv, kuhu antu akuga lühim tee võtab täpselt k laadimist ehksiis k linnadevahelist sõitu
 * */
std::vector<std::string> jouame(std::string lahtelinn, int x, int k, std::vector<std::string>& linnad, std::vector<std::vector<int>>& M) {
    int lahte = std::find(linnad.begin(), linnad.end(), lahtelinn) - linnad.begin();
    std::vector<int> saab;
    std::vector<GTipp*> graaf = graafiks(M, x), labitud;
    GTipp *prg = graaf.at(lahte);
    std::queue<Kaar> jarjekord(std::deque<Kaar>(prg->kaared.begin(), prg->kaared.end()));
    labitud.push_back(prg);

    while (!jarjekord.empty()) {
        Kaar praegune = jarjekord.front();
        jarjekord.pop();

        prg = praegune.lopp;
        if (std::find(labitud.begin(), labitud.end(), prg) == labitud.end()) {
            for (const Kaar& kaar : prg->kaared) {
                if (std::find(labitud.begin(), labitud.end(), kaar.lopp) == labitud.end()) {
                    jarjekord.push(kaar);
                }
            }
            prg->kaari = praegune.algus->kaari + 1;
            if (prg->kaari == k) {
                saab.push_back(prg->info);
            }
            labitud.push_back(prg);
        }
    }

    std::vector<std::string> tul;
    for (const int& y : saab) {
        tul.push_back(linnad[y]);
    }
    std::sort(tul.begin(), tul.end());
    return tul;
}

std::vector<std::string> graafiYlesanne(std::string failinimi, int maxkaugus, std::string lahtelinn, int laadimistearv) {
    auto paar = maatriksiks(failinimi, maxkaugus);
    return jouame(lahtelinn, laadimistearv, maxkaugus, paar.linnad, paar.matrix);
}


// * @Funktsionaalsus: Leiab linna indeksi arrays.
// * @Parameetrid: "arr" on linnade massiiv. "s" on otsitava linna nimi. "n" on .
// * @Tagastab: Otsitava linna indeksi linnade arrays.
// */
//int getIndex(std::string *arr, std::string s, int n) {
//    std::cout << n<<"\n";
//    for (int i = 0; i < n; ++i) {
//        if (*(arr+i) == s) return i;
//    }
//    return -1;
//}

