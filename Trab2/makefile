all: find_conflicts.o Seriabilidade.o VisaoEquivalente.o utils.o
	gcc -o find_conflicts find_conflicts.o Seriabilidade.o VisaoEquivalente.o utils.o

find_conflicts.o: find_conflicts.c Seriabilidade.h VisaoEquivalente.h utils.h
	gcc -o find_conflicts.o find_conflicts.c -c -Wall

Seriabilidade.o: Seriabilidade.c Seriabilidade.h
	gcc -o Seriabilidade.o Seriabilidade.c -c -Wall

VisaoEquivalente.o: VisaoEquivalente.c VisaoEquivalente.h
	gcc -o VisaoEquivalente.o VisaoEquivalente.c -c -Wall

utils.o: utils.c utils.h
	gcc -o utils.o utils.c -c -Wall

clean:
	rm *.o
	rm find_conflicts
