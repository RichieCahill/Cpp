// i imported https://github.com/calccrypto/uint256_t to the same dir as fixmycode01.cc
// then compiled with $ g++ -I ./uint256_t/ fixmycode01.cc uint256_t/uint256_t.cpp uint256_t/uint128_t.cpp

#include <iostream>
#include "uint256_t.h"

using namespace std;

int64_t sum(int32_t a, int32_t b) {
	int64_t s = 0;
	for (int32_t i = a; i <= b; i++)
		s += i;
	return s;
}

uint256_t fact(int32_t n) {
	uint256_t prod = 1;
	for (int32_t i = 1; i <= n; i++)
		prod *= i;
	return prod;
}

// note: const int32_t x[] is just promising that we are only reading the array x
// it is not the source of the error!
int32_t sumArray(const int32_t x[], int32_t n) {
	int32_t sum = 0;
	for (int32_t i = 0; i < n; i++)
		sum += x[i];
	return sum;
}

int32_t main() {
	cout << sum(1, 3) << '\n';	 		 		//6
	cout << sum(5, 10) << '\n';	 		 		//45
	cout << sum(1, 1000000) << '\n'; 		//500000500000
	cout << sum(1, 1000000000) << '\n'; //500000000500000000
	cout << fact(5) << '\n';						//120
	cout << fact(10) << '\n';						//3628800
	cout << fact(20) << '\n';						//2432902008176640000
	cout << fact(24) << '\n';						//620448401733239439360000 uint64_t hit integer limit
	cout << fact(50) << '\n';						//30414093201713378043612608166064768844377641568960512000000000000 
	cout << fact(59) << '\n';						//79987728622349815924550664989980645538705127915677385590566882687983820996608 uint256_t hit integer limit 
	int32_t a[] = {1, 2, 3, 4};
	int32_t b[] = {9, 8, 7, 1, 3};
	cout << sumArray(a, 4) << '\n'; //10
	cout << sumArray(b, 5) << '\n'; //28
}
