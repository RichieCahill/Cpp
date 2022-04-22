#include <iostream>
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
plans
	give it better output
	chang the bool array to a bit base based array 
*/
void EratosthenesSieve(u64 n ){
	u64 count = 1; // special case to account for the only even prime, 2
	bool isPrime[n] = {false};
	
	for (u64 i = 3; i <= n; i+=2){
		isPrime[i] = true;
		cout << i << " true" << endl;
	}

	for (u64 i = 3; i <= sqrt(n); i+=2){
		if (isPrime[i]){
			count++;
			for (u64 j = i*i; j <= n; j+=2*i){
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
