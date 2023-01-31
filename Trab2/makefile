all: find_conflicts.o Seriabilidade.o
	gcc -o find_conflicts find_conflicts.o Seriabilidade.o

find_conflicts.o: find_conflicts.c Seriabilidade.h
	gcc -o find_conflicts.o find_conflicts.c -c -Wall

Seriabilidade.o: Seriabilidade.c Seriabilidade.h
	gcc -o Seriabilidade.o Seriabilidade.c -c -Wall

clean:
	rm *.o
	rm find_conflicts
