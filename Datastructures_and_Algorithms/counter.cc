#include <iostream>
#include <immintrin.h>
#include <vector>
#include <cmath>

using namespace std;

typedef int64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

void clear_prime(u64* prime, u64 pos){
	prime[pos>>7] |= (1ULL<< ((pos>>1)%64));
}

int main(int argc, char const *argv[]){
	// The number you want to calculate to
	constexpr u64 total = 10000;
	// calculates next multipule of 128 above total
	constexpr u64 mult = (128-(total%128)+total);
	// calculates the difference  between total nad mult
	constexpr u64 extra = ((mult-total)>>1);
	// create and list of 64bit ints 128 time smaller then mult
	constexpr u64 size = mult>>7;
	u64* prime = new u64[size];
	

	for (u64 i = 0; i <= size-1; i++)
		prime[i] = 0;
	

	u32 num = 61;
	for (u64 j = num; j <= mult; j+=2*num){
		clear_prime(prime,j);
	}
	
	for (u64 i = 0; i <= size-1; i++){
		cout << _tzcnt_u64(prime[i]) << " ";
		// cout << dec << i << " " << _tzcnt_u64(prime[i]) << " " << hex << prime[i] << endl;		
	}

	return 0;
}