

All:
	gcc  -Wall -fopenmp -O2 static.c -o static
	./static
# 	gcc  -Wall -fopenmp -O2 parallele.c -o parallele

clean: 
	rm -rf *.o
	rm -rf static
	rm -rf parallele
