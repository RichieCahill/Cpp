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
#include <thread>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


// build a mask where every kth bit is one starting from right
uint64_t buildmask(uint32_t k) {
	uint64_t t = 0;
	const uint64_t mask1 =1ULL;
	for (uint32_t i = 0; i < 644; i += k){
		t |= (t<<k);
	}
	return t;
}

void list_generator(uint64_t s, uint64_t e, uint64_t* prime){

	// 31 0x1000000040000001

	const __m128i mask31_29 = _mm_set_epi64x(buildmask(31),buildmask(29));
	const __m128i mask23_19 = _mm_set_epi64x(buildmask(23),buildmask(19));
	const __m128i mask17_13 = _mm_set_epi64x(buildmask(17),0x0010008004002001);
	const __m128i mask11_7 = _mm_set_epi64x(0x0080100200400801,0x8102040810204081);
	const __m128i mask5_3 = _mm_set_epi64x(0x1084210842108421,0x9249249249249249);

	//loos form s to e making the temp register piking mask based on counter
	for (uint32_t i = s; i < e; i++) {

		uint64_t temp = 0;

		// patern 1 2 0
		uint64_t tempmask = _mm_extract_epi64(mask5_3, 0);
		temp |=  tempmask << (1+(i%3));
		// temp |=  tempmask << (0+(i%3))%3;

		tempmask = _mm_extract_epi64(mask5_3, 1);
		// temp |= tempmask << (1+(i%5))%5;

		// patern 3 2 1 0 6 5 4
		tempmask = _mm_extract_epi64(mask11_7, 0);
		// temp |=  tempmask << (5+(6-(i%7)))%7;

  	// patern 4 6 8 10 1 3 5 7 9 0 2
		tempmask = _mm_extract_epi64(mask11_7, 1);
		// temp |=  tempmask << ((i+2)+(i%11))%11;

		// tempmask = _mm_extract_epi64(mask17_13, 0);
		// temp |=  tempmask << (6+(i%13))%13;


		// tempmask = _mm_extract_epi64(mask17_13, 1);
		// temp |=  tempmask << (6+(i%17))%17;

		//Outputs the avx register to disk in raw
		prime[i-1]=temp;
		cout << hex << i << " " << temp << endl;



		// Factfile.write ((char*)&temp, sizeof (temp));
		// avxout(temp);
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
	constexpr uint64_t n = 5000;
	//adding allocating the number spaces a vector needs
	constexpr uint64_t size = (n+63)/64;
	//get the total number of processor on the machine
	// const auto processor_count = thread::hardware_concurrency();
	constexpr uint64_t processor_count = 1;
	//divides the work into processor_count of equal pieces
	const uint64_t piece = (processor_count-(size%processor_count)+size)/processor_count;

	uint64_t* prime = new uint64_t[size];

	cout << piece << endl;

	uint32_t start = 1;

	//create a vector of threads
	vector<thread> t;

	//creat threads till the processor_count
	//alice helped with the for loop that create the threads
	for(int i = 0; i < processor_count; i++){

		//make output file and attempts to increment it
		// it doesn't work i getting ASCII value not numbers
		string file = "/mnt/temp/test";
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
	for(auto&& e: t)
  	e.join();


	// constexpr uint64_t size2 = size*4;
	// uint64_t* prime2 = new uint64_t[size2];


	// for (uint64_t i = 0,j=0; i <= size; i++, j+=4){

	// __m128i t128_0, t128_1;
	//pulls the avx register apart and left shits stor the out put in a __m128i
	// t128_0 =	_mm256_extracti128_si256(prime[i], 0);
	// prime2[j] = _mm_extract_epi64(t128_0, 0);
	// prime2[j+1] = _mm_extract_epi64(t128_0, 1);
	// t128_1 =	_mm256_extracti128_si256(prime[i], 0);
	// prime2[j+2] = _mm_extract_epi64(t128_1, 0);
	// prime2[j+3] = _mm_extract_epi64(t128_1, 1);

		// prime2[j]=_mm256_extract_epi64(prime[i], 0);
		// prime2[j+1]=_mm256_extract_epi64(prime[i], 1);
		// prime2[j+2]=_mm256_extract_epi64(prime[i], 2);
		// prime2[j+3]=_mm256_extract_epi64(prime[i], 3);
//
	// }

	// EratosthenesSieve(n,prime2,size2);

	// counter(prime2,size2);

	// for (uint64_t i = 0; i < 16; i++){
	// 	cout << hex << prime2[i] << endl;
	// }

	delete[] prime;
	// delete[] prime,prime2;
	return 0;
}

/*







*/

