# @author: MasterJEET
# @email : masterjeet9@gmail.com

# Linking command:
main : main.o
	g++ obj/main.o -o bin/main
	echo Linking
main.o : source/main.cpp
	g++ -c source/main.cpp -o obj/main.o
	echo Compiling
