

echo "-----Debut mesure-----"

for i in {2..6}
do
	echo "----Pour $i threads----"
	export OMP_NUM_THREADS=$i
	echo "sans opti"
	./parallele
	echo "O2"
	./paralleleO2
	echo "O3"
	./paralleleO3
	echo "Ofast"
	./paralleleOf	
done

echo "----Debut static----"
./static
./staticO2
./staticO3
./staticOf
