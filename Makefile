
CC=gcc
OPTS=-Wall -g
PROG=animaux
PROG2=jeu20
LIBS=ab.o 
LIBS2 = jeu_tp2.o

all: ${PROG} ${PROG2} ${LIBS}

${PROG}: animaux.c ${LIBS}
	${CC} animaux.c ${LIBS} ${OPTS} -o ${PROG}

${PROG2}: jeu20.c ${LIBS2}
	${CC} jeu20.c ${LIBS2} ${OPTS} -o ${PROG2}

ab.o: ab.c ab.h
	${CC} -c ab.c ${OPTS} 

jeu_tp2.o : jeu_tp2.c jeu_tp2.h
	${CC} -c jeu_tp2.c ${OPTS} 

clean:
	rm -f ${LIBS} ${LIBS2} ${PROG} ${PROG2}


