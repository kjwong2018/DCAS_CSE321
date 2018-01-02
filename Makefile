all:
	 g++ -std=c++11 -O2 -Wall DCAS.cpp -o dcas -lpthread

 clean:
	 rm dcas output.txt
