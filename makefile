

All:
	gcc  -Wall -fopenmp main.c -o nonPara
	gcc  -Wall -fopenmp mainPara.c -o paral

clean: 
	rm -rf *.o
	rm -rf nonPara
	rm -rf paral
