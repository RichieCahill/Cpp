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

void list_generator(vector<u64>& prime){

	//loos form s to e making the temp register piking mask based on counter
	for (u32 i = 0; i < prime.size(); i++) {

		// pattern 1 0 2
		u64 temp = 0x9249249249249249 << (1+(3-(i%3)))%3;

		// pattern 2 3 4 0 1
		temp |= 0x1084210842108421 << (2+i)%5;

		// pattern 3 2 1 0 6 5 4 3
		temp |= 0x8102040810204081 << (4+(6-(i%7)))%7;

		// pattern 5 7 9 0 2 4 6 8 10 1 3 5
		temp |= 0x0080100200400801 << (5+i*2)%11;

		// pattern 6 7 8 9 10 11 12 0 1 2 3 4 5 6
		temp |= 0x0010008004002001 << (6+i)%13;

		// pattern 8 12 16 3 7 11 15 2 6 10 14 1 5 9 13 0 4 8
		temp |= 0x0008000400020001 << (8+i*4)%17;

		// pattern 9 2 14 7 0 12 5 17 10 3 15 8 1 13 6 18 11 4 16 9
		temp |= 0x0200004000080001 << (11+((17+(18-(i%19)))*7))%19;

		// pattern 11 16 21 3 8 13 18 0 5 10 15 20 2 7 12 17 22 4 9 14 19 1 6 11
		temp |= 0x0000400000800001 << (11+i*5)%23;

		// pattern 14 8 2 25 19 13 7 1 24 18 12 6 0 23 17 11 5 28 22 16 10 4 27 21 15 9 3 26 20 14
		temp |= 0x0400000020000001 << (3+(27+(28-(i%29)))*6)%29;

		// pattern 15 13 11 9 7 5 3 1 30 28 26 24 22 20 18 16 14 12 10 8 6 4 2 0 29 27 25 23 21 19 17 15
		temp |= 0x4000000080000001 << (21+(29+(30-(i%31)))*2)%31;
		prime[i]=temp;

		// cout << hex << i << " " << temp << endl;
	}
}

// counts the number prime numbers in the array minus the bits that are
u64 counter(vector<u64>& prime, u64 extra){
u64  temp = 0;
	for (u64 i = 0; i <= prime.size()-1; i++){
		temp += (64-_mm_popcnt_u64(prime[i]));
	}
	return temp - (extra-_mm_popcnt_u64(prime[prime.size()-1]>>(64-extra)));
}


// checks if bit at pos is 0
bool is_prime(vector<u64>& prime, u64 pos){
	return !(prime[pos>>7] & (1ULL<<((pos>>1)%64)));
}

void EratosthenesSieve(u64 n ,vector<u64>& prime){
	for (u64 i = 21; i <= sqrt(n); i+=2){
		if (is_prime(prime,i)){
			for (u64 j = i*i; j <= n; j+=2*i)
				prime[j>>7] |= (1ULL<<((j>>1)%64));
		}
	}
}


int main() {
	// The number you want to calculate to
	constexpr u64 total = 10000;
	// calculates next multipule of 128 above total
	constexpr u64 mult = (128-(total%128)+total);
	// calculates the difference  between total nad mult
	constexpr u64 extra = ((mult-total)>>1);
	// create and list of 64bit ints 128 time smaller then mult
	constexpr u64 size = mult>>7;
	vector<u64> prime(size);

	clock_t t0 = clock();

	list_generator(prime);

	// clock_t t1 = clock();
	// cout << "1 " << (t1-t0)* 1e-6  << '\n' << '\n';

	// t0 = clock();

	EratosthenesSieve(mult,prime);

	// t1 = clock();
	// cout << "2 " << (t1-t0)* 1e-6  << '\n' << '\n';

	// This is set the firs 64bit because list_generator dosnt properly calculate the firs bits for the number its masking
	prime[0] = 0x7e92ed659b4b3490;
	// t0 = clock();
	cout << dec << counter(prime,extra) << endl;

	// t1 = clock();
	clock_t t1 = clock();
	cout << (t1-t0)* 1e-6  << '\n' << '\n';

	return 0;
}

