#include <iostream>
#include <immintrin.h>


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

// build a mask where every kth bit is zero starting from right
uint64_t buildmask(uint32_t k) {
	uint64_t t = 0;
	for (uint32_t i = 0; i < 64; i += k)
		t = t | (1ULL << i);
	return t;
}


int main() {
	const __m256i mask3 = _mm256_set_epi64x(0x9249249249249249,0x2492492492492492,0x4924924924924924,0x9249249249249249);
	const __m256i mask5 = _mm256_set_epi64x(0x8421084210842108,0x4210842108421084,0x2108421084210842,0x1084210842108421);
	const __m256i mask7 = _mm256_set_epi64x(0x1020408102040810,0x2040810204081020,0x4081020408102040,0x8102040810204081);

	constexpr uint64_t n = 3500;
	constexpr int size = (n+511)/512;
	__m256i* p = new __m256i[size];
	__m256i temp;

	for (uint32_t i = 1, j = 1; i <= size; i++) {
		temp = _mm256_setzero_si256();
		
		// masks multiple of 3
		if(i%3==1)
			temp = _mm256_or_si256(temp, avx256_ls_test(mask3,1));
		if(i%3==2)
			temp = _mm256_or_si256(temp, avx256_ls_test(mask3,2));
		if(i%3==0)
			temp = _mm256_or_si256(temp, avx256_ls_test(mask3,0));

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
    p[i] = temp;
		
	}
	delete[] p;

}

/*
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

