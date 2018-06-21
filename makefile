main: main.o Sol_su.o GenSudoku.o
	g++ -o main main.o Sol_su.o GenSudoku.o

main.o: main.cpp GenSudoku.h Sol_su.h
	g++ -c main.cpp

GenSudoku.o: GenSudoku.cpp GenSudoku.h Sol_su.h
	g++ -c GenSudoku.cpp

Sol_su.o: Sol_su.cpp Sol_su.h
	g++ -c Sol_su.cpp

clean:
	rm main *.o