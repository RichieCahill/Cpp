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

void clear_prime(vector<u64>& prime, u64 pos){
	prime[pos>>7] |= (1ULL<< ((pos>>1)%64));
}

int main(int argc, char const *argv[]){
	// This is number you want to caculate the pater for
	constexpr u64 num =  	71;
	// The number you want to calculate to
	constexpr u64 size = num+1;
	vector<u64> prime(size,0);

	for (u64 i = num; i <= size*128; i+=2*num){
		clear_prime(prime,i);
	}

	for (u64 i = 0; i <= size-1; i++){
		cout << _tzcnt_u64(prime[i]) << " ";
		// cout << dec << i << " " << _tzcnt_u64(prime[i]) << " " << hex << prime[i] << endl;
	}

	return 0;
}
