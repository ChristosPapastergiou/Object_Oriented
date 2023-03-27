all: Main\
	ConDesFun\
	Project

Main: Main.cpp
	g++ -c -std=c++11 Main.cpp

ConDesFun: ConDesFun.cpp
	g++ -c -std=c++11 ConDesFun.cpp

Project: Main.cpp ConDesFun.cpp
	g++ -o Project Main.cpp ConDesFun.cpp

clean:
	rm -f Main ConDesFun