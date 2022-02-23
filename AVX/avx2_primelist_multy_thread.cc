#include <iostream>
#include <immintrin.h>
#include <thread>

using namespace std;

void avxout(__m256i a){
	cout << hex << _mm256_extract_epi64(a, 0) << endl;
	cout << hex << _mm256_extract_epi64(a, 1) << endl;
	cout << hex << _mm256_extract_epi64(a, 2) << endl;
	cout << hex << _mm256_extract_epi64(a, 3) << endl;
	cout << endl;
}

//Leftshifts a avx256 register
__m256i avx256_ls_test (__m256i n, int64_t s){
	if (s==0)
		return n;
	__m256i temp;
	__m128i t128_0, t128_1;
	uint64_t t64_0, t64_1;
	//pulls the avx register apart and left shits stor the out put in a __m128i
	t128_0 =	_mm256_extracti128_si256(n, 0);
	t64_0 = _mm_extract_epi64(t128_0, 0);
	t64_0 = t64_0>> (64-s);
	t64_1 = _mm_extract_epi64(t128_0, 1);
	t64_1 = t64_1>> (64-s);
	t128_0 = _mm_set_epi64x(t64_0, 0X0000000000000000);
	
	//pulls the avx register apart and left shits stor the out put in a __m128i
	t128_1 = _mm256_extracti128_si256(n, 1);
	t64_0 = _mm_extract_epi64(t128_1, 0);
	t64_0 = t64_0>> (64-s);
	t128_1	= _mm_set_epi64x(t64_0, t64_1);

	//combins the 2 __m128i into a __m256i
	temp = _mm256_set_m128i(t128_1, t128_0);

	// left shit the 4 64 bit ins in n then or with temp
	n = n << s;
	n = _mm256_or_si256(n, temp);
	return n;
}

// build a mask where every kth bit is one starting from right
__m256i buildmask(uint32_t k) {
	__m256i t = _mm256_setzero_si256();
	const __m256i mask1 = _mm256_set_epi64x(0ULL,0ULL,0ULL,1ULL);
	for (uint32_t i = 0; i < 256; i += k){
		t = avx256_ls_test(t, k);
		t = _mm256_or_si256(t, mask1);
	}
	return t;
}

void list_generator(uint64_t s, uint64_t e){
	
	//Move these out ?
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
	
	for (uint32_t i = s; i <= e; i++) {
		
		
		temp = _mm256_setzero_si256();
		
		// masks multiple of 3
		switch (i%3) {
			case 0:
				temp = _mm256_or_si256(temp, avx256_ls_test(mask3,0));
				break;
			case 1:
				temp = _mm256_or_si256(temp, avx256_ls_test(mask3,1));
				break;
			case 2:
				temp = _mm256_or_si256(temp, avx256_ls_test(mask3,2));
				break;
		}
		
		// masks multiple of 5
		if(i%5==1)
			temp = _mm256_or_si256(temp, avx256_ls_test(mask5,2));
		if(i%5==2)
			temp = _mm256_or_si256(temp, avx256_ls_test(mask5,1));
		if(i%5==3)
			temp = _mm256_or_si256(temp, avx256_ls_test(mask5,0));
		if(i%5==4)
			temp = _mm256_or_si256(temp, avx256_ls_test(mask5,4));
		if(i%5==0)
			temp = _mm256_or_si256(temp, avx256_ls_test(mask5,3));

		// masks multiple of 7
		if(i%7==1)
			temp = _mm256_or_si256(temp, avx256_ls_test(mask7,3));
		if(i%7==2)
			temp = _mm256_or_si256(temp, avx256_ls_test(mask7,6));
		if(i%7==3)
			temp = _mm256_or_si256(temp, avx256_ls_test(mask7,2));
		if(i%7==4)
			temp = _mm256_or_si256(temp, avx256_ls_test(mask7,5));
		if(i%7==5)
			temp = _mm256_or_si256(temp, avx256_ls_test(mask7,1));
		if(i%7==6)
			temp = _mm256_or_si256(temp, avx256_ls_test(mask7,4));
		if(i%7==0)
			temp = _mm256_or_si256(temp, avx256_ls_test(mask7,0));
		
		avxout(temp);
		
	}
}





int main() {

	constexpr uint64_t n = 1000000000;
	constexpr int size = (n+511)/512;
	constexpr int half = size/2;
	constexpr int quarter = size/4;
	constexpr int topquarter = half+quarter;

	const auto processor_count = thread::hardware_concurrency() - 2;

	thread th1(list_generator, 1, size);
	// thread th2(list_generator, quarter,half);
	// thread th3(list_generator, half,topquarter);
	// thread th4(list_generator, topquarter,size);


  th1.join();
	// th2.join();
  // th3.join();
	// th4.join();
	cout << dec << processor_count << endl;

}

/*
	testing 3,5 and 7
	1000000000 1 threds
	run 1 ./a.out  3.05s user 8.52s system 69% cpu 16.759 total
	run 2 ./a.out  2.91s user 8.76s system 68% cpu 17.029 total
	run 3 ./a.out  3.09s user 8.52s system 68% cpu 16.974 total
	4x faster then yesterday
	1000000000 2 threds 
	run 1 1:00.18
	1000000000 4 threds 
	run 1 1:03.02
	run 2 29.788
	run 3 ./a.out  13.73s user 37.96s system 171% cpu 30.209 total
	run 4 ./a.out  13.48s user 38.10s system 174% cpu 29.639 total
	run 5 ./a.out  13.40s user 38.31s system 172% cpu 29.952 total



	
	127 125 123 121 ...25 23 21 19 17 15 13 11 9 7 5 3 1
	3=   ...                    1001001001001001001001001
	5=   ...                           100001000010000100
	 
	255                      145 143 141 139 137 135 133 131 129
							 0  1  1  1  1 0   1   1   1   1   0   1   1   1
	383                                           257
	511                                           385
	mask3 110110110110110110110
	mask5 011110111101111011110
	mask7 000000100000010000001000000100000010000001

	25 23 21 19 17 15 13 11 9 7 5 3 1
		 0  1  0  0  1  0  0  1 1 1 1 0
*/

