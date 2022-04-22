#include <iostream>
#include <cmath>
#include <immintrin.h>

using namespace std;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

/*
Complexity O(log n)
with optomizations
	only checking odd number halving total number checked
	only checking to the square root of n roughly halving total number checked
	chang the bool array to a bit base based array
*/

// counts the number prime numbers in the array minus the bits that are
u64 counter(u64 *prime, u64 size, u64 extra){
u64  temp = 0;
	for (u64 i = 0; i <= size-1; i++){
		temp += (64-_mm_popcnt_u64(prime[i]));
	}
	return temp - (extra-_mm_popcnt_u64(prime[size-1]>>(64-extra)));
}

// checks if bit at pos is 0
bool is_prime(u64* prime, u64 pos){
	return !(prime[pos>>7] & (1ULL<<((pos>>1)%64)));
}

// checks if bit at pos is 0
void clear_prime(u64* prime, u64 pos){
	prime[pos>>7] |= (1ULL<< ((pos>>1)%64));
}

// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
// this saves the outpus the a list of 64 bit ints
// this skips even numbers There is a specail case for 1 and 2
// beause 1 isnt prime and evens aren calculated the number line is 9 7 5 3 2
void EratosthenesSieve(u64 n ,u64* prime,u64 size){
	for (u64 i = 0; i < size; i++)
		prime[i]=0;
	for (u64 i = 3; i <= sqrt(n); i+=2){
		if (is_prime(prime,i)){
			for (u64 j = i*i; j <= n; j+=2*i)
				clear_prime(prime,j);
		}
	}
}


int main(int argc, char const *argv[]){
	// The number you want to calculate to
	constexpr u64 total = 100000000000;
	// calculates next multipule of 128 above total
	constexpr u64 mult = (128-(total%128)+total);
	// calculates the difference  between total nad mult
	constexpr u64 extra = ((mult-total)>>1);
	// create and list of 64bit ints 128 time smaller then mult
	constexpr u64 size = mult>>7;
	u64* prime = new u64[size];

	clock_t t0 = clock();
	
	EratosthenesSieve(mult,prime,size);

	cout << dec << counter(prime,size,extra) << endl;
	
	clock_t t1 = clock();
	cout << (t1-t0) * 1e-6 << '\n';

	delete[] prime;
	return 0;


}

