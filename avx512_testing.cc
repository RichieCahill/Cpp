#include <iostream>
#include <immintrin.h>



using namespace std;



int main(int argc, char const *argv[]){
__m512i a , b;
uint64_t t = 0XFFFFFFFFFFFFFFFF;
a = _mm512_set_epi64(0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF);
a = _mm512_bitshuffle_epi64_mask(a,4);



__m256i test = _mm512_extracti64x4_epi64(a, 0);
cout << hex << _mm256_extract_epi64(test, 3) << endl;
cout << hex << _mm256_extract_epi64(test, 2) << endl;
cout << hex << _mm256_extract_epi64(test, 1) << endl;
cout << hex << _mm256_extract_epi64(test, 0) << endl;
cout << endl;

	return 0;
}