/*
resorest
timehttps://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#
https://stackoverflow.com/questions/11103249/raw-file-format-c

https://github.com/ahuston-0 Helped with multithreading Figured out a figured out the algrithum to leftshift 3 and 5
https://github.com/DerDennisOP Helped with the leftshits amount

g++ -O3 -g -mavx -pthread -march=native ./avx2_primelist_multy_thread.cc

0 is can be prime 1 isnt

TODO
Make it out to a vector instead of a file
and output that vector to a file
look into the for loop alternitve

tiem to beat to 10,000,000,000 12s
*/

#include <iostream>
#include <immintrin.h>
#include <thread>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include"AVX-bit-manipulation.h"

using namespace std;


// build a mask where every kth bit is one starting from right
__m256i buildmask(uint32_t k) {
	__m256i t = _mm256_setzero_si256();
	const __m256i mask1 = _mm256_set_epi64x(0ULL,0ULL,0ULL,1ULL);
	for (uint32_t i = 0; i < 256; i += k){
		t = _mm256_lls_mm256(t, k);
		t = _mm256_or_si256(t, mask1);
	}
	return t;
}

void list_generator(uint64_t s, uint64_t e, __m256i* prime){
	//creath the file the it outputs to
	// ofstream Factfile(name, ios::out | ios::binary);

	//Move these out ?
	//set all the mask valus
	//i set 13 to 3 to save the regsters and time that leftshifting takes
	const __m256i mask31 = buildmask(31);
	const __m256i mask29 = buildmask(29);
	const __m256i mask23 = buildmask(23);
	const __m256i mask19 = buildmask(19);
	const __m256i mask17 = buildmask(17);
	const __m256i mask13 = _mm256_set_epi64x(0x0080040020010008,0x0040020010008004,0x0020010008004002,0x0010008004002001);
	const __m256i mask11 = _mm256_set_epi64x(0x2004008010020040,0x0801002004008010,0x0200400801002004,0x0080100200400801);
	const __m256i mask7 = _mm256_set_epi64x(0x1020408102040810,0x2040810204081020,0x4081020408102040,0x8102040810204081);
	const __m256i mask5 = _mm256_set_epi64x(0x8421084210842108,0x4210842108421084,0x2108421084210842,0x1084210842108421);
	const __m256i mask3 = _mm256_set_epi64x(0x9249249249249249,0x2492492492492492,0x4924924924924924,0x9249249249249249);

	__m256i temp;

	//loos form s to e making the temp register piking mask based on counter
	for (uint32_t i = s; i < e; i++) {

		temp = _mm256_setzero_si256();

		//k= numbe of in sequens of primes n = nebut your masking i bing posioion in list
		// (n+(n-k)-(i%n))%n

		// masks multiple of 3
		//patern 1 0 2
		// cout << 2-(i%3) << endl;

		temp = _mm256_or_si256(temp, _mm256_lls_mm256(mask3,2-(i%3)));
		// temp = _mm256_or_si256(temp, _mm256_lls_mm256(mask3, (5-(i%3))%3));

		// masks multiple of 5
		//patern 2 1 0 4 3
		temp = _mm256_or_si256(temp, _mm256_lls_mm256(mask5,(8-(i%5))%5));

		// masks multiple of 7
		//patern 3 6 2 5 1 4 0
		// cout << (11*i-(i%7))%7 << endl;
		temp = _mm256_or_si256(temp, _mm256_lls_mm256(mask7,(11*i-(i%7))%7));


		// masks multiple of 11
		//pttern 4 1 9 6 3 0 8 5 2 10 7
		// int n = 11, k =5;
		temp = _mm256_or_si256(temp, _mm256_lls_mm256(mask11,((9*i-4)-(i%11))%11));

		// masks multiple of 11
		//pttern 5 9 0 4 8 12 3 7 11 2 6 10 1
		temp = _mm256_or_si256(temp, _mm256_lls_mm256(mask13,((5*i+1)-(i%13))%13));

		//Outputs the avx register to disk in raw
		prime[i-1]=temp;
		// Factfile.write ((char*)&temp, sizeof (temp));
		avxout(temp);
	}
	// Factfile.close();
}


bool is_prime(uint64_t* prime, uint64_t pos){
	pos/=2;
	return !(prime[pos/64 ] & (1ULL<<(pos%64)));
}

void clear_prime(uint64_t* prime, uint64_t pos){
	pos/=2;
	prime[pos/64] |= (1ULL<<(pos%64));
}

void counter(uint64_t *prime, uint64_t size){
uint64_t temp = 0;
	for (uint64_t i = 0; i <= size; i++){
		temp += (64-_mm_popcnt_u64(prime[i]));
	}
cout << temp << endl;
}


void EratosthenesSieve(uint64_t n ,uint64_t* prime,uint64_t size){
	uint64_t count = 1; // special case to account for the only even prime, 2
	
	for (uint64_t i = 13; i <= sqrt(n); i+=2){
		if (is_prime(prime,i)){
			count++;
			for (uint64_t j = i*i; j <= n; j+=2*i)
				clear_prime(prime,j);
		}
	}

}


int main() {
	//the number you arc computing to
	constexpr uint64_t n = 100000000;
	//adding allocating the number spaces a vector needs
	constexpr uint64_t size = (n+511)/512;
	//get the total number of processor on the machine
	// const auto processor_count = thread::hardware_concurrency();
	constexpr uint64_t processor_count = 1;
	//divides the work into processor_count of equal pieces
	const uint64_t piece = (processor_count-(size%processor_count)+size)/processor_count;

	__m256i* prime = new __m256i[size];

	cout << piece << endl;

	uint32_t start = 1;

	//create a vector of threads
	vector<thread> t;

	//creat threads till the processor_count
	//alice helped with the for loop that create the threads
	for(int i = 0; i < processor_count; i++){

		//make output file and attempts to increment it
		// it doesn't work i getting ASCII value not numbers
		// char c = i+48;
		// cout << c << endl;
		// file += c;
		// file += ".csv";
		// cout << file << endl;

		//sets the ending position of the fuction
		uint32_t end=piece+start;

		//spawns a thread with the list generator
		t.emplace_back(list_generator, start, end, prime);

		//seth the start to the ole ned for the net iteration
		start = end;
	}

	//Joins all the thread at the end
	for(auto&& e: t){
  	e.join();
	}


	constexpr uint64_t size2 = size*4;
	uint64_t* prime2 = new uint64_t[size2];


	for (uint64_t i = 0,j=0; i <= size; i++, j+=4){
	
	// __m128i t128_0, t128_1;
	//pulls the avx register apart and left shits stor the out put in a __m128i
	// t128_0 =	_mm256_extracti128_si256(prime[i], 0);
	// prime2[j] = _mm_extract_epi64(t128_0, 0);
	// prime2[j+1] = _mm_extract_epi64(t128_0, 1);
	// t128_1 =	_mm256_extracti128_si256(prime[i], 0);
	// prime2[j+2] = _mm_extract_epi64(t128_1, 0);
	// prime2[j+3] = _mm_extract_epi64(t128_1, 1);

		prime2[j]=_mm256_extract_epi64(prime[i], 0);
		prime2[j+1]=_mm256_extract_epi64(prime[i], 1);
		prime2[j+2]=_mm256_extract_epi64(prime[i], 2);
		prime2[j+3]=_mm256_extract_epi64(prime[i], 3);

	}
	
	EratosthenesSieve(n,prime2,size2);

	counter(prime2,size2);
	
	for (uint64_t i = 0; i < 16; i++){
		cout << hex << prime2[i] << endl;
	}
	
	delete[] prime,prime2;
	return 0;
}

/*

	0110111010010011111111010110010110011111010011111011010010111110

	Multy threading is 2x to 4x slower cout was causing problems
	testing 3,5 and 7 02/22 8700k
	1000000000 1 threds
	run 1 ./a.out  3.05s user 8.52s system 69% cpu 16.759 total
	run 2 ./a.out  2.91s user 8.76s system 68% cpu 17.029 total
	run 3 ./a.out  3.09s user 8.52s system 68% cpu 16.974 total
	1000000000 2 threds
	run 1 1:00.18
	1000000000 4 threds
	run 1 1:03.02
	run 2 29.788
	run 3 ./a.out  13.73s user 37.96s system 171% cpu 30.209 total
	run 4 ./a.out  13.48s user 38.10s system 174% cpu 29.639 total
	run 5 ./a.out  13.40s user 38.31s system 172% cpu 29.952 total

	Writing to a file 02/22 8700k
	10000000000 1 threds
	run 1 ./a.out  21.81s user 73.79s system 99% cpu 1:36.38 total
	run 2 ./a.out  21.29s user 72.69s system 98% cpu 1:35.05 total
	run 3 ./a.out  21.86s user 72.85s system 98% cpu 1:35.77 total
	run 4
	run 5

	10000000000 4 threds
	run 1 ./a.out  22.10s user 75.97s system 397% cpu 24.696 total
	run 2 ./a.out  21.95s user 102.12s system 394% cpu 31.420 total
	run 3 ./a.out  22.16s user 100.41s system 374% cpu 32.709 total
	run 4
	run 5


	10000000000 4 threds 02/23
	run 1 ./a.out  45.86s user 349.25s system 393% cpu 1:40.38 total
	run 2 ./a.out  45.90s user 352.49s system 392% cpu 1:41.53 total
	run 3 ./a.out  52.83s user 357.83s system 392% cpu 1:44.66 total
	run 4
	run 5

	10000000000 9 threds
	run 1 ./a.out  52.03s user 486.78s system 861% cpu 1:02.58 total
	run 2


	20000000000 9 threds
	run 1 ./a.out  109.17s user 964.13s system 870% cpu 2:03.35 total
	run 2 ./a.out  102.08s user 971.09s system 872% cpu 2:02.99 total
	run 3


	120000000000 9 threds
	run 1 ./a.out  591.92s user 4497.66s system 856% cpu 9:54.32 total
	run 2

	10000000000 10 threds
	run 1 ./a.out  54.95s user 311.72s system 950% cpu 38.589 total

	I maybe hit thermal limits and defnlty hit io limits
	120000000000 10 threds
	run 1 ./a.out  673.54s user 5868.22s system 978% cpu 11:08.65 total
	run 2 ./a.out  678.23s user 8240.52s system 984% cpu 15:05.88 total
	run 3 ./a.out  664.31s user 6272.40s system 970% cpu 11:54.43 total

	120000000000 12 threds
	run 1 ./a.out  689.78s user 6498.34s system 1073% cpu 11:09.32 total
	run 2

	improved wrighting directly wright avx regiuster raw 17x faster
	120000000000 10 threds
	run 1 ./a.out  29.39s user 34.28s system 152% cpu 41.773 total
	run 2 ./a.out  12.09s user 15.64s system 66% cpu 41.807 total
	run 3 ./a.out  19.02s user 22.29s system 99% cpu 41.681 total
	run 4

	120000000000 12 threds
	run 1 ./a.out  15.93s user 19.96s system 85% cpu 41.733 total
	run 2	./a.out  30.13s user 34.15s system 153% cpu 41.775 total


	2400000000000 12 threds
	run 1 ./a.out  35.96s user 37.74s system 97% cpu 1:15.46 total
	run 2 ./a.out  31.63s user 35.98s system 89% cpu 1:15.49 total
	run 3 ./a.out  40.47s user 46.23s system 114% cpu 1:15.51 total
	run 4 ./a.out  52.40s user 63.97s system 154% cpu 1:15.49 total
	run 5 ./a.out  41.88s user 34.68s system 91% cpu 1:23.66 total


	testing 3,5,7 and 11 02/24 8700k
	120000000000 12 threds
	Not optane
	run 1 ./a.out  41.24s user 15.37s system 265% cpu 21.296 total

	run 1 ./a.out  29.38s user 11.23s system 181% cpu 22.391 total

	Optane
	run 1 ./a.out  44.64s user 23.47s system 175% cpu 38.760 total
	run 2 ./a.out  38.56s user 22.43s system 145% cpu 41.873 total



	testing 3,5,7 and 11 02/24 8700k not optane and fixed the dobling bug

	120000000000 12 threds
	run 1 ./a.out  17.40s user 7.61s system 275% cpu 9.072 total

	240000000000 12 threds
	run 1 ./a.out  33.01s user 13.14s system 187% cpu 24.612 total
	10,000,000,000/s

	testing 3,5,7 and 11 02/24 AMD EPYC 7551
	2400000000000 64 threds
	run 1 ./a.out  295.25s user 195.70s system 742% cpu 1:06.09 total
	36,363,636,363/s


	127 125 123 121 ...25 23 21 19 17 15 13 11 9 7 5 3 1
	3=   ...                  10010010010010010010010010
	5=   ...                          100001000010000100

	255                      145 143 141 139 137 135 133 131 129
							 0  1  1  1  1 0   1   1   1   1   0   1   1   1
	383                                           257
	511                                           385
	mask3 110110110110110110110
	mask5 011110111101111011110
	mask7 000000100000010000001000000100000010000001

	25 23 21 19 17 15 13 11 9 7 5 3 1
		 0  1  0  0  1  0  0  1 1 1 1 0

		 00100001 0100001
		 01001001 0010010  10010010
		 13579-35 79-3579- 3579-
		 00000000000000000000000000000000000000000000
		 001000010000100001000010000100001000010000100001
		 00010000001000000100000010000001000000100000010000001
		 01111001001011001101001011
*/

