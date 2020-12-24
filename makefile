

All:
	gcc  -Wall -fopenmp -O2 main.c -o nonPara
	gcc  -Wall -fopenmp -O2 mainPara.c -o paral

clean: 
	rm -rf *.o
	rm -rf nonPara
	rm -rf paral
