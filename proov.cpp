#include <iostream>
#include "Proov.h"
#include <chrono>
#include <bits/stdc++.h>
#include "graafid.h"

#define TIMER_ENABLE = 0
#ifdef TIMER_ENABLE
#define TIMER() Timer();
#else
#define TIMER
#endif
struct Timer{
    std::chrono::time_point<std::chrono::high_resolution_clock> algus = std::chrono::high_resolution_clock::now();
    Timer() {
        algus = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        auto lopp = std::chrono::high_resolution_clock::now();
        auto aeg = std::chrono::duration_cast<std::chrono::milliseconds>(lopp - algus);
        std::cout << "Aega kulus: " << aeg.count() <<"\n";
    }
};



JNIEXPORT jint JNICALL Java_Proov_cppTukeldused(JNIEnv *env, jobject obj, jdoubleArray a, jdouble p, jint n) {
    TIMER();
    double *arrayPtr = env->GetDoubleArrayElements(a, 0);
    std::sort(arrayPtr, arrayPtr+n);
    return tukeldusedRek(arrayPtr, p, arrayPtr[0], 0, n);

}

JNIEXPORT jobjectArray JNICALL Java_Proov_cppJouame(JNIEnv *env, jobject obj, jstring lahtelinn, jint x, jint k, jobjectArray linnad, jobjectArray m) {
    int rows = env->GetArrayLength(m);
    jintArray firstRow = (jintArray)(env->GetObjectArrayElement(m, 0));
    int cols = env->GetArrayLength(firstRow);

    std::vector<std::vector<int>*> *mat = new std::vector<std::vector<int>*>;
    int *row = env->GetIntArrayElements(firstRow, 0);
    std::vector<int> *rowVec = new std::vector<int>;
    for (int i = 0; i < cols; ++i) {
        rowVec->push_back(row[0]);
    }
    mat->push_back(rowVec);
    for (int i = 1; i < rows; ++i) {
        rowVec = new std::vector<int>;
        jintArray currentRow = (jintArray)(env->GetObjectArrayElement(m, i));
        row = env->GetIntArrayElements(currentRow, 0);
        for (int j = 0; j < cols; ++j) {
            rowVec->push_back(row[j]);
        }
        mat->push_back(rowVec);
    }

    int linnu = env->GetArrayLength(linnad);
    std::string linnaArr[linnu];
    for (int i = 0; i < linnu; ++i) {
        jstring linnString = (jstring)(env->GetObjectArrayElement(linnad, i));
        linnaArr[i] = env->GetStringUTFChars(linnString, 0);
    }
    std::string lahteString = env->GetStringUTFChars(lahtelinn, 0);
    std::vector<std::string> *saab = new std::vector<std::string>();
    std::vector<Tipp> *graaf = new std::vector<Tipp>();
    jouame(lahteString, x, k, linnaArr, linnu, mat, graaf, saab);
    for (auto &s : *saab) {
        std::cout <<s<<"\n";
    }
    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray stringArray = env->NewObjectArray(saab->size(), stringClass, 0);
    for ( int i = 0; i < saab->size(); ++i ) {
        std::string s = saab->at(i);
        jstring javaString = env->NewStringUTF( s.c_str() );
        env->SetObjectArrayElement( stringArray, i, javaString);
    }
    return stringArray;
}

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

int getIndex(std::string *arr, std::string s, int n) {
    std::cout << n<<"\n";
    for (int i = 0; i < n; ++i) {
        if (*(arr+i) == s) return i;
    }
    return -1;
}

void looGraafMaatriksist(std::vector<std::vector<int>*> *m, int max, std::vector<Tipp> *graaf) {
    int length = m->size();
    std::cout<<length<<"\n";
    for (int i = 0; i < length; ++i) {
        Tipp tipp(0);
        if (graaf->size() <= i) {
            tipp = Tipp(i);
            graaf->push_back(tipp);
        } else {
            tipp = graaf->at(i);
        }

        for (int j = 0; j < length; j++) {
            Tipp teine(0);
            if (j >= graaf->size()) {
                teine = Tipp(j);
                graaf->push_back(teine);
            } else {
                teine = graaf->at(j);
            }
            if (m->at(i)->at(j) > 0 && m->at(i)->at(j) <= max) {
                Kaar kaar = Kaar(m->at(i)->at(j), tipp, teine);
                tipp.m_kaared->push_back(kaar);
            }
        }

    }
}

void jouame(std::string lahtelinn, int x, int k, std::string *linnad, int linnu, std::vector<std::vector<int>*> *m, std::vector<Tipp> *graaf, std::vector<std::string> *saab){
    int lahte = getIndex(linnad, lahtelinn, linnu);
    std::vector<Tipp> labitud;

    looGraafMaatriksist(m, x, graaf);
    Tipp praegune = graaf->at(lahte);
    std::queue<Kaar> jarts;
    for (Kaar &kaar : *praegune.m_kaared) {
        jarts.push(kaar);
    }

    labitud.push_back(praegune);
    while(!jarts.empty()) {
        Kaar prg = jarts.front();
        jarts.pop();
        praegune = prg.m_lopp;
        if (std::find(labitud.begin(), labitud.end(), praegune) == std::end(labitud)) {
            for (Kaar &kaar : *praegune.m_kaared) {
                if (std::find(labitud.begin(), labitud.end(), kaar.m_lopp) == std::end(labitud)) {
                    jarts.push(kaar);
                }
            }
            praegune.m_kaari = prg.m_algus.m_kaari + 1;
            if (praegune.m_kaari == k) {
                saab->push_back(linnad[praegune.m_info]);
            }
            labitud.push_back(praegune);
        }
    }

}

bool operator==(const Tipp &t1, const Tipp &t2) {
    return t1.m_info == t2.m_info;
}

