#include <iostream>
#include <cmath>
#include <immintrin.h>

using namespace std;


/*
Complexity O(log n)
with optomizations 
	only checking odd number halving total number checked
	only checking to the square root of n roughly halving total number checked
plans
	give it better output
	chang the bool array to a bit base based array 
*/

	// const __m256i mask1 = _mm256_set_epi64x(0ULL,0ULL,0ULL,1ULL);

void Out(uint64_t *prime, uint64_t size){
	for (uint64_t i = 1; i <= size; i++){
		cout << hex << prime[i-1] << endl;
	}
}

uint64_t counter(uint64_t *prime, uint64_t size){
uint64_t  temp = 0;
	for (uint64_t i = 0; i <= size-1; i++){
		temp += (64-_mm_popcnt_u64(prime[i]));	
	}
	return temp;
}


bool is_prime(uint64_t* prime, uint64_t pos){
	pos/=2;
	return !(prime[pos/64] & (1ULL<<(pos%64)));
}

void clear_prime(uint64_t* prime, uint64_t pos){
	pos/=2;
	prime[pos/64] |= (1ULL<<(pos%64));
}

void EratosthenesSieve(uint64_t n ,uint64_t* prime,uint64_t size){
	
	for (uint64_t i = 0; i < size; i++)
		prime[i]=0;

	// loop intating threw odd numbers
	for (uint64_t i = 3; i <= n; i+=2){

		if (is_prime(prime,i)){
			for (uint64_t j = i*i; j <= n; j+=2*i)
				clear_prime(prime,j);
		}
	}

}

int main(int argc, char const *argv[]){
	constexpr uint64_t total = 100;
	constexpr uint64_t mult = (128-(total%128)+total);
	cout << mult << endl;
	constexpr uint64_t size = mult/128;
	constexpr uint64_t extra = 64-((mult-total)/2);
	cout << extra << endl;
	
	uint64_t* prime = new uint64_t[size];

	EratosthenesSieve(mult,prime,size);
	
	uint64_t out = counter(prime,size);
	cout << out << endl;
	
	Out(prime,size);

	uint64_t test = extra-_mm_popcnt_u64(prime[size-1]>>extra);
	cout << test << endl;
	
	out = out - test;
	
	cout << out << endl;
	
	delete[] prime;
	return 0;

}

