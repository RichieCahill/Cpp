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

/*
counter.cc is used to calculate the pattern and the starting mask

The offset calculation is
the first number in the pattern plus the number after zero mod the number you are masking
*/

	//loos form s to e making the temp register piking mask based on counter
	for (u32 i = 0; i < prime.size(); i++) {

		// pattern 1 0 2
		u64 temp = 0x9249249249249249 << (1+2*i)%3;

		// pattern 2 3 4 0 1
		temp |= 0x1084210842108421 << (2+i)%5;

		// pattern 3 2 1 0 6 5 4 3
		temp |= 0x8102040810204081 << (3+6*i)%7;

		// pattern 5 7 9 0 2 4 6 8 10 1 3 5
		temp |= 0x0080100200400801 << (5+2*i)%11;

		// pattern 6 7 8 9 10 11 12 0 1 2 3 4 5 6
		temp |= 0x0010008004002001 << (6+i)%13;

		// pattern 8 12 16 3 7 11 15 2 6 10 14 1 5 9 13 0 4 8
		temp |= 0x0008000400020001 << (8+4*i)%17;

		// pattern 9 2 14 7 0 12 5 17 10 3 15 8 1 13 6 18 11 4 16 9
		temp |= 0x0200004000080001 << (9+12*i)%19;

		// // pattern 11 16 21 3 8 13 18 0 5 10 15 20 2 7 12 17 22 4 9 14 19 1 6 11
		// temp |= 0x0000400000800001 << (11+5*i)%23;

		// // pattern 14 8 2 25 19 13 7 1 24 18 12 6 0 23 17 11 5 28 22 16 10 4 27 21 15 9 3 26 20 14
		// temp |= 0x0400000020000001 << (14+23*i)%29;

		// // pattern 15 13 11 9 7 5 3 1 30 28 26 24 22 20 18 16 14 12 10 8 6 4 2 0 29 27 25 23 21 19 17 15
		// temp |= 0x4000000080000001 << (15+29*i)%31;

		// // pattern 18 28 1 11 21 31 4 14 24 34 7 17 27 0 10 20 30 3 13 23 33 6 16 26 36 9 19 29 2 12 22 32 5 15 25 35 8 18
		// temp |= 0x0000002000000001 << (18+10*i)%37;

		// // pattern 20 38 15 33 10 28 5 23 0 18 36 13 31 8 26 3 21 39 16 34 11 29 6 24 1 19 37 14 32 9 27 4 22 40 17 35 12 30 7 25 2 20
		// temp |= 0x0000020000000001 << (20+18*i)%41;

		// // pattern 21 0 22 1 23 2 24 3 25 4 26 5 27 6 28 7 29 8 30 9 31 10 32 11 33 12 34 13 35 14 36 15 37 16 38 17 39 18 40 19 41 20 42 21
		// temp |= 0x0000080000000001 << (21+22*i)%43;

		// // pattern 23 6 36 19 2 32 15 45 28 11 41 24 7 37 20 3 33 16 46 29 12 42 25 8 38 21 4 34 17 0 30 13 43 26 9 39 22 5 35 18 1 31 14 44 27 10 40 23 
		// temp |= 0x0000800000000001 << (23+30*i)%47;

		// // pattern 26 15 4 46 35 24 13 2 44 33 22 11 0 42 31 20 9 51 40 29 18 7 49 38 27 16 5 47 36 25 14 3 45 34 23 12 1 43 32 21 10 52 41 30 19 8 50 39 28 17 6 48 37 26
		// temp |= 0x0020000000000001 << (26+42*i)%53;

		// // pattern 29 24 19 14 9 4 58 53 48 43 38 33 28 23 18 13 8 3 57 52 47 42 37 32 27 22 17 12 7 2 56 51 46 41 36 31 26 21 16 11 6 1 55 50 45 40 35 30 25 20 15 10 5 0 54 49 44 39 34 29
		// temp |= 0x0800000000000001 << (29+54*i)%59;



		prime[i]=temp;
		// cout << hex << i << " " << temp << endl;
	}
}

// counts the number prime numbers in the array minus the bits that are
auto counter(vector<u64>& prime, auto extra){
	auto temp = 0;
	for (const auto& i : prime) {
		temp += (64-_mm_popcnt_u64(i));
	}
	return temp - (extra-_mm_popcnt_u64(prime.back()>>(64-extra)));
}


// checks if bit at pos is 0
// return !(prime[pos/64] & (1ULL<<((pos/2)%64));
bool is_prime(vector<u64>& prime, auto pos){
	return !(prime[pos>>7] & (1ULL<<(pos>>1)));
}

void clear_prime(vector<u64>& prime, auto pos){
	prime[pos>>7] |= (1ULL<<(pos>>1));
}

void EratosthenesSieve(auto n ,vector<u64>& prime){
	// for (auto i = 59; i <= sqrt(n); i+=2){
	for (auto i = 3; i <= sqrt(n); i+=2){
		if (is_prime(prime,i)){
			for (auto j = i*i; j <= n; j+=2*i)
				clear_prime(prime,j);
		}
	}
}


int main() {
	// The number you want to calculate to
	constexpr auto total = 10000000000;
	// calculates next multipule of 128 above total
	constexpr auto mult = (128-(total%128)+total);
	// calculates the difference  between total nad mult
	constexpr auto extra = ((mult-total)>>1);
	// create and list of 64bit ints 128 time smaller then mult
	constexpr auto size = mult>>7;
	vector<u64> prime(size);

	clock_t t2 = clock();
	clock_t t0 = clock();

	list_generator(prime);

	clock_t t1 = clock();
	cout << "1 " << (t1-t0)* 1e-6  << '\n' << '\n';

	t0 = clock();

	EratosthenesSieve(mult,prime);

	t1 = clock();
	cout << "2 " << (t1-t0)* 1e-6  << '\n' << '\n';

	// This is set the firs 64bit because list_generator dosnt properly calculate the firs bits for the number its masking
	prime[0] = 0x7e92ed659b4b3490;
	t0 = clock();
	cout << dec << counter(prime,extra) << endl;

	t1 = clock();

	// clock_t t1 = clock();
	cout << (t1-t0)* 1e-6  << '\n' << '\n';
	clock_t t3 = clock();
	cout << (t2-t3)* 1e-6  << '\n' << '\n';

	return 0;
}

