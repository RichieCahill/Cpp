#include <iostream>
#include <cmath>

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


bool is_prime(uint64_t* prime, uint64_t pos){
	pos/=2;
	return !(prime[pos/64] & (1ULL<<(pos%64)));
}

void clear_prime(uint64_t* prime, uint64_t pos){
	pos/=2;
	prime[pos/64] |= (1ULL<<(pos%64));
}

void EratosthenesSieve(uint64_t n ){
	uint64_t count = 1; // special case to account for the only even prime, 2
	const uint64_t size = (n+511)/512*8;

	uint64_t* prime = new uint64_t[size]; 

	for (uint64_t i = 0; i < size; i++){
		prime[i]=0;
	}
	

	for (uint64_t i = 3; i <= sqrt(n); i+=2){
		if (is_prime(prime,i)){
			count++;
			for (uint64_t j = i*i; j <= n; j+=2*i){
				clear_prime(prime,j);
		}
	}

}

int main(int argc, char const *argv[]){

	EratosthenesSieve(101);
	return 0;
}
