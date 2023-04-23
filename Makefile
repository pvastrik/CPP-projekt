run:
	g++ -c -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux proov.cpp -o proov.o
	g++ -shared -fPIC -o libnative.so proov.o -lc

java:
	java -cp . -Djava.library.path=/mnt/c/Users/priid/kool/c++proge/projekt Proov.java