#include <iostream>
#include "Proov.h"
#include <chrono>
struct Timer{
    const std::chrono::time_point<std::chrono::high_resolution_clock> algus = {std::chrono::high_resolution_clock::now()};
    Timer() = default;
    ~Timer() {
        auto lopp = std::chrono::high_resolution_clock::now();
        auto aeg = std::chrono::duration_cast<std::chrono::milliseconds>(lopp - algus);
        std::cout << "Aega kulus: " << aeg.count() <<"\n";
    }
};



JNIEXPORT void JNICALL Java_Proov_prooviLoopi(JNIEnv * env, jobject obj, jlong n) {
int a = 0;
    for(int i= 0; i < n; i++) {
        a++;
    }

}

