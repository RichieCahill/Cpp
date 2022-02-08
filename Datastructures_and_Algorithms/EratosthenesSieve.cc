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
void EratosthenesSieve(uint64_t n){
	uint64_t count = 1; // special case to account for the only even prime, 2
	bool isPrime[n] = {false};
	
	for (uint64_t i = 3; i <= n; i+=2){
		isPrime[i] = true;
		cout << i << " true" << endl;
	}

	for (uint64_t i = 3; i <= sqrt(n); i+=2){
		if (isPrime[i]){
			count++;
			for (uint64_t j = i*i; j <= n; j+=2*i){
				isPrime[j] == false;
				cout << j << "false" << endl;
			}
		}
	}
	
}

int main(int argc, char const *argv[]){
	EratosthenesSieve(101);
	return 0;
}
