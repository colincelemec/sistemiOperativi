/* file 22sett99-1.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv)
{   int fd;		/* variabile per open */
    char c;		/* variabile per caratteri letti dal file */

	/* controllo numero di parametri */
	if (argc != 4) 	/* controllo sul numero di parametri: devono essere esattamente 3! */
	{ 	printf("Errore nel numero di parametri: %s vuole 3 parametri\n", argv[0]); 
                printf("Ci vogliono 3 argomenti: nome-file, singolo carattere da cercare e singolo carattere da sostituire\n");
        	exit(1); 
	}

	/* ora facciamo il controllo se il primo parametro e' un file (plausibile fatto con una open) che deve essere sia leggibile che scrivibile: NOTA BENE che in questo caso la open va fatta in lettura e scrittura */
	if ((fd = open(argv[1], O_RDWR)) < 0)
        { 	printf("Errore in apertura file %s\n", argv[1]); 
                exit(2); 
	}

	/* controllo secondo parametro: singolo parametro */
	if (strlen(argv[2]) != 1)	/* controlliamo che il secondo parametro sia un singolo carattere: N.B. Non viene chiesto che sia un carattere alfabetico o di una particolare categoria! */
	if (strlen(argv[2]) != 1)
        { 	printf("Errore non carattere %s\n", argv[2]); 
		exit(3); 
	}

	/* controllo terzo parametro: singolo parametro */
	if (strlen(argv[3]) != 1)	/* IDEM COME SOPRA! */
        { 	printf("Errore non carattere %s\n", argv[3]); 
		exit(4); 
	}

	/* se arriviamo qui, vuol dire che tutto e' andato bene */
	while (read(fd, &c, 1)) /* ATTENZIONE: dobbiamo leggere un solo carattere alla volta */
	/* quindi usiamo &c; inoltre, NON serve indicare nulla nella condizione, dato che la read tornera' 1 in caso di successo e quindi si entrera' nel ciclo, oppure 0 e allora si uscira' dal ciclo perche' saremo arrivati alla fine del file */
          	if (c == argv[2][0])	/* se il carattere corrente e' uguale al carattere passato ... ATTENZIONE IL CARATTERE E' DATO DALL'ELEMENTO 0 DELLA STRINGA argv[2]! */
                { 	lseek(fd, -1L, 1);
         		/* SI DEVE RIPORTARE INDIETRO IL FILE POINTER */
                  	write(fd, &argv[3][0], 1);	/* si deve scrivere il carattere passato come terzo parametro:  ATTENZIONE IL CARATTERE E' DATO DALL'ELEMENTO 0 DELLA STRINGA argv[3]! */
                }

	exit(0);
}
