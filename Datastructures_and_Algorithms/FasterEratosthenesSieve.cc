#include <iostream>
#include <cmath>
#include <immintrin.h>

using namespace std;


/*
Complexity O(log n)
with optomizations
	only checking odd number halving total number checked
	only checking to the square root of n roughly halving total number checked
	chang the bool array to a bit base based array
*/

// counts the number prime numbers in the array minus the bits that are
uint64_t counter(uint64_t *prime, uint64_t size, uint64_t extra){
uint64_t  temp = 0;
	for (uint64_t i = 0; i <= size-1; i++){
		temp += (64-_mm_popcnt_u64(prime[i]));
	}
	return temp - (extra-_mm_popcnt_u64(prime[size-1]>>(64-extra)));
}

// checks if bit at pos is 0
bool is_prime(uint64_t* prime, uint64_t pos){
	return !(prime[pos>>7] & (1ULL<<((pos>>1)%64)));
}

// checks if bit at pos is 0
void clear_prime(uint64_t* prime, uint64_t pos){
	prime[pos>>7] |= (1ULL<< ((pos>>1)%64));
}

// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
// this saves the outpus the a list of 64 bit ints
// this skips even numbers There is a specail case for 1 and 2
// beause 1 isnt prime and evens aren calculated the number line is 9 7 5 3 2
void EratosthenesSieve(uint64_t n ,uint64_t* prime,uint64_t size){
	for (uint64_t i = 0; i < size; i++)
		prime[i]=0;
	for (uint64_t i = 3; i <= sqrt(n); i+=2){
		if (is_prime(prime,i)){
			for (uint64_t j = i*i; j <= n; j+=2*i)
				clear_prime(prime,j);
		}
	}
}


int main(int argc, char const *argv[]){
	// The number you want to calculate to
	constexpr uint64_t total = 10000000000;
	// calculates next multipule of 128 above total
	constexpr uint64_t mult = (128-(total%128)+total);
	// calculates the difference  between total nad mult
	constexpr uint64_t extra = ((mult-total)>>1);
	// create and list of 64bit ints 128 time smaller then mult
	constexpr uint64_t size = mult>>7;
	uint64_t* prime = new uint64_t[size];

	clock_t t0 = clock();
	EratosthenesSieve(mult,prime,size);
	clock_t t1 = clock();
	cout << (t1-t0) * 1e-6 << '\n';


	cout << dec << counter(prime,size,extra) << endl;

	delete[] prime;
	return 0;


}

