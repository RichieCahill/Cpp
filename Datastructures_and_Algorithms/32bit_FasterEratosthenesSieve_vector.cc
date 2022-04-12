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


using namespace std;


/*
Complexity O(log n)
with optomizations
	only checking odd number halving total number checked
	only checking to the square root of n roughly halving total number checked
	chang the bool array to a bit base based array
*/

// counts the number prime numbers in the array minus the bits that are
auto counter(vector<u32>& prime, u64 auto){
	auto  temp = 0;
	for (const auto& i : prime) {
		temp += (32-_popcnt32(i));
	}
	return temp - (extra-_popcnt32(prime.back()>>(32-extra)));
}

// checks if bit at pos is 0
bool is_prime(vector<u32>& prime, u64 auto){
	return !(prime[pos>>6] & (1ULL<<(pos>>1)%32));
}

// checks if bit at pos is 0
void clear_prime(vector<u32>& prime, uint64_t auto){
	prime[pos>>6] |= (1ULL<<(pos>>1)%32);
}

// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
// this saves the outpus the a list of 64 bit ints
// this skips even numbers There is a specail case for 1 and 2
// beause 1 isnt prime and evens aren calculated the number line is 9 7 5 3 2
void EratosthenesSieve(auto n ,vector<u32>& prime){
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
	// calculates next multipule of 64 above total
	constexpr auto mult = (64-(total%64)+total);
	// calculates the difference  between total nad mult
	constexpr auto extra = ((mult-total)/2);
	// create and list of 32bit ints 64 time smaller then mult
	constexpr auto size = mult/64;
	vector<u32> prime(size,0);
	
	clock_t t0 = clock();
	
	EratosthenesSieve(mult,prime);

	cout << dec << counter(prime,extra) << endl;	

	clock_t t1 = clock();
	cout << (t1-t0) * 1e-6 << '\n';

	return 0;
}

