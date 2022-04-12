#include <iostream>
#include <immintrin.h>
#include <vector>
#include <cmath>

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
auto counter(vector<u64>& prime, auto extra){
	auto temp = 0;
	for (const auto& i : prime) {
		temp += (64-_mm_popcnt_u64(i));
	}
	return temp - (extra-_mm_popcnt_u64(prime.back()>>(64-extra)));
}

// checks if bit at pos is 0
bool is_prime(vector<u64>& prime, auto pos){
	return !(prime[pos>>7] & (1ULL<<(pos>>1)));
}

// checks if bit at pos is 0
void clear_prime(vector<u64>& prime, auto pos){
	prime[pos>>7] |= (1ULL<<(pos>>1));
}

// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
// this saves the outpus the a list of 64 bit ints
// this skips even numbers There is a specail case for 1 and 2
// beause 1 isnt prime and evens aren calculated the number line is 9 7 5 3 2
void EratosthenesSieve(auto n ,vector<u64>& prime){
	for (auto i = 3; i <= sqrt(n); i+=2){
		if (is_prime(prime,i)){
			for (auto j = i*i; j <= n; j+=2*i)
				clear_prime(prime,j);
		}
	}
}


int main(int argc, char const *argv[]){
	// The number you want to calculate to
	constexpr auto total = 1000;
	// calculates next multipule of 128 above total
	constexpr auto mult = (128-(total%128)+total);
	// calculates the difference  between total nad mult
	constexpr auto extra = ((mult-total)>>1);
	// create and list of 64bit ints 128 time smaller then mult
	constexpr auto size = mult>>7;
	vector<u64> prime(size,0);

	clock_t t0 = clock();
	
	EratosthenesSieve(mult,prime);

	cout << dec << counter(prime,extra) << endl;
	
	clock_t t1 = clock();
	cout << (t1-t0) * 1e-6 << '\n';

	return 0;
}

