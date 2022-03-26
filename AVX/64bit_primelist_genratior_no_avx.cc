/*
resorest
timehttps://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#
https://stackoverflow.com/questions/11103249/raw-file-format-c

https://github.com/ahuston-0 Helped with multithreading Figured out a figured out the algrithum to leftshift 3 and 5

g++ -O3 -g -mavx -pthread -march=native ./avx2_primelist_multy_thread.cc

0 is can be prime 1 isnt

TODO
*/

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

void list_generator(u64 s, u64 e, u64* prime){

	//loos form s to e making the temp register piking mask based on counter
	for (u32 i = s; i < e+1; i++) {

		u64 temp = 0x9249249249249249 << (2+(3-(i%3)))%3;

		temp |= 0x1084210842108421 << (1+((i%5)))%5;

		temp |= 0x8102040810204081 << (5+(6-(i%7)))%7;

		temp |= 0x0080100200400801 << (3+((i%11)*2))%11;

		temp |= 0x0010008004002001 << (5+(i%13))%13;

		temp |= 0x0008000400020001 << (4+((i%17)*4))%17;

		temp |= 0x0200004000080001 << (18+((17+(18-(i%19)))*7))%19;

		temp |= 0x0000400000800001 << (6+((i%23)*5))%23;

		temp |= 0x0400000020000001 << (9+(27+(28-(i%29)))*6)%29;

		temp |= 0x4000000080000001 << (23+(29+(30-(i%31)))*2)%31;

		prime[i-1]=temp;

		// cout << hex << i << " " << temp << endl;
	}
}

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

void EratosthenesSieve(u64 n ,u64* prime,u64 size){
	for (u64 i = 3; i <= sqrt(n); i+=2){
		if (is_prime(prime,i)){
			for (u64 j = i*i; j <= n; j+=2*i)
				prime[j>>7] |= (1ULL<<((j>>1)%64));
		}
	}
}


int main() {
	// The number you want to calculate to
	constexpr u64 total = 10000000000;
	// calculates next multipule of 128 above total
	constexpr u64 mult = (128-(total%128)+total);
	// calculates the difference  between total nad mult
	constexpr u64 extra = ((mult-total)>>1);
	// create and list of 64bit ints 128 time smaller then mult
	constexpr u64 size = mult>>7;
	u64* prime = new u64[size];

	clock_t t0 = clock();

	list_generator(1,size,prime);

	// clock_t t1 = clock();
	// cout << "1 " << (t1-t0)* 1e-6  << '\n' << '\n';

	// t0 = clock();

	EratosthenesSieve(mult,prime,size);

	// t1 = clock();
	// cout << "2 " << (t1-t0)* 1e-6  << '\n' << '\n';

	// This is set the firs 64bit because list_generator dosnt properly calculate the firs bits for the number its masking
	prime[0] = 0x7e92ed659b4b3490;
	// t0 = clock();
	cout << dec << counter(prime,size,extra) << endl;
	// t1 = clock();
	clock_t t1 = clock();
	cout << (t1-t0)* 1e-6  << '\n' << '\n';

	delete[] prime;
	return 0;
}

