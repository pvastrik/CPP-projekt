JAVA_HOME_DIR := /usr/lib/jvm/java-17-openjdk-amd64
install:
	sudo apt update
	sudo apt install openjdk-17-jdk-headless
	sudo apt install build-essential

compile:
	javac -h . Proov.java
	g++ -c -fPIC -I${JAVA_HOME_DIR}/include -I${JAVA_HOME_DIR}/include/linux proov.cpp -o proov.o
	g++ -shared -fPIC -o libnative.so proov.o -lc

java:
	java -cp . -Djava.library.path=. Proov.java