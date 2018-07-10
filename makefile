
run: FileEdit.o main.o ServerCreator.o Website.o
	g++ FileEdit.o main.o ServerCreator.o Website.o -o run

FileEdit.o: FileEdit.cpp FileEdit.h
	g++ -c FileEdit.cpp

main.o: main.cpp 
	g++ -c main.cpp

ServerCreator.o: ServerCreator.cpp ServerCreator.h
	g++ -c ServerCreator.cpp

Website.o: Website.cpp Website.h
	g++ -c Website.cpp

clear:
	rm *.o run
