

All:

	gcc  -Wall -fopenmp -g static.c -o static
	gcc  -Wall -fopenmp  -g parallele.c -o parallele


	gcc  -Wall -fopenmp -O2 static.c -o staticO2
	gcc  -Wall -fopenmp -O2 parallele.c -o paralleleO2

	
	gcc  -Wall -fopenmp -O3 static.c -o staticO3
	gcc  -Wall -fopenmp -O3 parallele.c -o paralleleO3



	gcc  -Wall -fopenmp -Ofast static.c -o staticOf
	gcc  -Wall -fopenmp -Ofast parallele.c -o paralleleOf

clean: 
	rm -rf *.o
	rm -rf static
	rm -rf parallele
