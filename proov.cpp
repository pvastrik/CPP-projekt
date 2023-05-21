#include <iostream>
#include "Proov.h"
#include <chrono>
#include <bits/stdc++.h>
#include "graafid.h"
#include "tukeldused.h"
#include "isikukoodid.h"

#define TIMER_ENABLE = 0
#ifdef TIMER_ENABLE
#define TIMER() Timer timer();
#else
#define TIMER
#endif

/**
 * @Funktsionaalsus: Teisendab javast tulnud array vectoriks ning teostab traadi jupitamise ülesande lahendamiseks vajaliku töö.
 * @Parameetrid: "env" ja "obj" on JNI muutujad ja on vajalikud meetodi tööks. "a" on Java Array, kus on juppide pikkused.
 * "p" on minimaalse jupi pikkus. "n" on tükelduste arv.
 * @Returns: Sorteeritud isikukoodide Java Array.
 */
JNIEXPORT jint JNICALL Java_Proov_cppTukeldused(JNIEnv *env, jobject obj, jdoubleArray a, jdouble p, jint n) {
    double *arrayPtr = env->GetDoubleArrayElements(a, 0);
    auto algus = std::chrono::high_resolution_clock::now();
    std::sort(arrayPtr, arrayPtr+n);
    auto lopp = std::chrono::high_resolution_clock::now();
    auto aeg = std::chrono::duration_cast<std::chrono::milliseconds>(lopp - algus);
    std::cout << "Aega kulus: " << aeg.count() <<" ms\n";
    return tukeldusedRek(arrayPtr, p, arrayPtr[0], 0, n);

}

/**
 * @Funktsionaalsus: Teisendab javast tulnud informatsiooni ning teostab linnast linna liikumise ülesande.
 * @Parameetrid: "env" ja "obj" on JNI muutujad ja on vajalikud meetodi tööks. "lahtelinn" on linn, kust minema hakkame.
 * "x" on laadimiskordade arv. "k" on elektriauto aku suurus (km), "linnad" on linnade massiiv, "m" on graafi esitus maatriksina.
 * @Returns: Java array linnadest, kuhu saame sõita.
 */
JNIEXPORT jobjectArray JNICALL Java_Proov_cppJouame(JNIEnv *env, jobject obj, jstring lahtelinn, jint x, jint k, jobjectArray linnad, jobjectArray m) {
    int rows = env->GetArrayLength(m);
    jintArray firstRow = (jintArray)(env->GetObjectArrayElement(m, 0));
    int cols = env->GetArrayLength(firstRow);

    std::vector<std::vector<int>> mat;
    int *row = env->GetIntArrayElements(firstRow, 0);

    for (int i = 1; i < rows; ++i) {
        std::vector<int> rowVec;
        jintArray currentRow = (jintArray)(env->GetObjectArrayElement(m, i));
        row = env->GetIntArrayElements(currentRow, 0);
        for (int j = 0; j < cols; ++j) {
            rowVec.push_back(row[j]);
        }
        mat.push_back(rowVec);
    }

    int linnu = env->GetArrayLength(linnad);
    std::vector<std::string> linnaVec;
    for (int i = 0; i < linnu; ++i) {
        jstring linnString = (jstring)(env->GetObjectArrayElement(linnad, i));
        linnaVec.push_back(env->GetStringUTFChars(linnString, 0));
    }
    std::string lahteString = env->GetStringUTFChars(lahtelinn, 0);

    auto algus = std::chrono::high_resolution_clock::now();
    auto saab = jouame(lahteString, x, k, linnaVec, mat);
    auto lopp = std::chrono::high_resolution_clock::now();
    auto aeg = std::chrono::duration_cast<std::chrono::milliseconds>(lopp - algus);
    std::cout << "Aega kulus: " << aeg.count() <<" ms\n";

    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray stringArray = env->NewObjectArray(saab.size(), stringClass, 0);
    for ( int i = 0; i < saab.size(); ++i ) {
        std::string s = saab.at(i);
        jstring javaString = env->NewStringUTF( s.c_str() );
        env->SetObjectArrayElement( stringArray, i, javaString);
    }
    return stringArray;
}





/*****************ISIKUKOODIDE SORTEERIMINE*********************/



/**
    * @Funktsionaalsus: Teisendab javast tulnud array vectoriks, teostab vajaliku töö ning konventeerib seejärel tagasi.
    * @Parameetrid: "env" ja "obj" on JNI muutujad ja on vajalikud meetodi tööks. "a" on Java Array, kus on isikukoodid.
    * @Returns: Sorteeritud isikukoodide Java Array.
 */
JNIEXPORT jlongArray JNICALL Java_Proov_cppSortIsikukoodid(JNIEnv *env, jobject obj, jlongArray a){
    jsize size = env->GetArrayLength( a );
    std::vector<long> input( size );
    env->GetLongArrayRegion( a, jsize{0}, size, &input[0] );
    auto algus = std::chrono::high_resolution_clock::now();
    sort(input);
    auto lopp = std::chrono::high_resolution_clock::now();
    auto aeg = std::chrono::duration_cast<std::chrono::milliseconds>(lopp - algus);
    std::cout << "Aega kulus: " << aeg.count() <<" ms\n";
    jlongArray longArray = env->NewLongArray(input.size());

    return longArray;
    //double *arrayPtr = env->GetDoubleArrayElements(a, 0);

}




JNIEXPORT jobjectArray JNICALL Java_Proov_cppGraafiYlesanne(JNIEnv *env, jobject jobj, jstring failinimi, jstring lahtelinn, jint laadimistearv, jint maxkaugus) {
    std::string c_failinimi = env->GetStringUTFChars(failinimi, 0);
    std::string c_lahtelinn = env->GetStringUTFChars(lahtelinn, 0);
    auto paar = maatriksiks(c_failinimi, maxkaugus);

    auto algus = std::chrono::high_resolution_clock::now();
    std::vector<std::string> linnad = jouame(c_lahtelinn, maxkaugus, laadimistearv, paar.linnad, paar.matrix);
    auto lopp = std::chrono::high_resolution_clock::now();
    auto aeg = std::chrono::duration_cast<std::chrono::milliseconds>(lopp - algus);

    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray stringArray = env->NewObjectArray(linnad.size(), stringClass, 0);
    for ( int i = 0; i < linnad.size(); ++i ) {
        std::string s = linnad.at(i);
        jstring javaString = env->NewStringUTF( s.c_str() );
        env->SetObjectArrayElement( stringArray, i, javaString);
    }
//    env->ReleaseStringUTFChars(lahtelinn, c_lahtelinn);
//    env->ReleaseStringUTFChars(failinimi, c_failinimi);

    return stringArray;
}
