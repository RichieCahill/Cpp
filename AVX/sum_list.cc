#include <iostream>
#include <immintrin.h>
#include <vector>
#include <cmath>
#include <cstdint>
#include <map>
#include <numeric>
#include <ranges>
#include <string>
#include <variant>


using namespace std;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;


void avxout(__m256i a){
	std::cout << _mm256_extract_epi32(a, 7) << "\n";
	std::cout << _mm256_extract_epi32(a, 6) << "\n";
	std::cout << _mm256_extract_epi32(a, 5) << "\n";
	std::cout << _mm256_extract_epi32(a, 4) << "\n";
	std::cout << _mm256_extract_epi32(a, 3) << "\n";
	std::cout << _mm256_extract_epi32(a, 2) << "\n";
	std::cout << _mm256_extract_epi32(a, 1) << "\n";
	std::cout << _mm256_extract_epi32(a, 0) << "\n";
	std::cout << "\n";
}

auto sum(vector<u64>& data){
	return  std::accumulate(begin(data), end(data), 0.0);
}

auto sumloop(vector<u64>& data){
	auto temp = 0;
	for (size_t i = 0; i <= data.size(); i++){
		temp += data[i];
	}
	return  temp;
}


int main(int argc, char const *argv[]){
constexpr int32_t size = 2000000001;
constexpr int32_t fast = size-size%8;



int32_t* list = new int32_t[size];

for (int32_t i = 0; i <= size; i++){
	list[i] = 1Ull;
}

// 2 Hadd intrinxis
__m256i temp= _mm256_setzero_si256(),temp2 = _mm256_setzero_si256();
clock_t t0 = clock();
for (int32_t i = 0; i < fast/8; i++) {
	temp=_mm256_set_epi32(list[i],list[i+1],list[i+2],list[i+3],list[i+4],list[i+5],list[i+6],list[i+7]);
	temp2=temp2+temp;

}


temp2=_mm256_hadd_epi32(_mm256_hadd_epi32(temp2,_mm256_setzero_si256()),_mm256_setzero_si256());


int32_t temp3 = _mm256_extract_epi32(temp2, 4)+_mm256_extract_epi32(temp2, 0);

for (int32_t i = fast; i < size; i++){
	 temp3 += list[i];
}

clock_t t1 = clock();
cout << temp3  << '\n' << '\n';

cout << "1 " << (t1-t0)*1e-6  << '\n' << '\n';


// testing somthing
temp= _mm256_setzero_si256(),temp2 = _mm256_setzero_si256();
t0 = clock();
for (int32_t i = 0; i < fast/8; i++) {
	temp=_mm256_set_epi32(list[i],list[i+1],list[i+2],list[i+3],list[i+4],list[i+5],list[i+6],list[i+7]);
	temp2=temp2+temp;

}


temp2=_mm256_hadd_epi32(temp2,_mm256_setzero_si256());

__m128i test = _mm_hadd_epi32(_mm256_extractf128_si256(temp2,1),_mm256_extractf128_si256(temp2,0));




temp3 = _mm_extract_epi32(test,0)+_mm_extract_epi32(test,2);


for (int32_t i = fast; i < size; i++){
	 temp3 += list[i];
}

t1 = clock();
cout << temp3  << '\n' << '\n';

cout << (t1-t0)*1e-6  << '\n' << '\n';









int32_t temp32 =0;
t0 = clock();

for (int32_t i = 0; i < size; i++){
	 temp32 += list[i];
}
t1 = clock();

cout << (t1-t0)*1e-6  << '\n' << '\n';

cout << temp32  << '\n' << '\n';


	return 0;
}