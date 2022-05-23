#include <iostream>
#include <immintrin.h>
#include <vector>
#include <string>
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

// (num-1)/2 converted to num right shift 1 by Alice Huston
u64 Maskshift(u64 mask,u64 num,u64 i){
	return mask << ((num>>1)+(num-(64%num))*i)%num;
}

u64 Maskshift2(u64 mask,u64 num,u64 i){
	return mask << ((num>>1)+(64-(128%num))*i)%num;
}

u64 MaskshiftTest(u64 mask,u64 num,u64 i){
	const u64 a = num>>1;
	const u64 b =	num-(64%num);
	return mask << (a+b*i)%num;
}

int main(int argc, char const *argv[]){
u64 num=0;
	clock_t t0 = clock();

	

	for (size_t i = 0; i <= 38; i++){
	
		// pattern 1 0 2
		// u64 temp = 0x9249249249249249 << (1+2*i)%3;
		u64 temp = Maskshift(0x9249249249249249, 3,i);

		// pattern 2 3 4 0 1
		// temp |= 0x1084210842108421 << (2+i)%5;
		temp |= Maskshift(0x1084210842108421,5,i);

		// pattern 3 2 1 0 6 5 4 3
		// temp |= 0x8102040810204081 << (3+6*i)%7;
		temp |= Maskshift(0x8102040810204081,7,i);

		// pattern 5 7 9 0 2 4 6 8 10 1 3 5
		// temp |= 0x0080100200400801 << (5+2*i)%11;
		temp |= Maskshift(0x0080100200400801,11,i);

		// pattern 6 7 8 9 10 11 12 0 1 2 3 4 5 6
		// temp |= 0x0010008004002001 << (6+i)%13;
		temp |= Maskshift(0x0010008004002001,13,i);

		// pattern 8 12 16 3 7 11 15 2 6 10 14 1 5 9 13 0 4 8
		// temp |= 0x0008000400020001 << (8+4*i)%17;
		temp |= Maskshift(0x0008000400020001,17,i);

		// pattern 9 2 14 7 0 12 5 17 10 3 15 8 1 13 6 18 11 4 16 9
		// temp |= 0x0200004000080001 << (9+12*i)%19;
		temp |= Maskshift(0x0200004000080001,19,i);

		// pattern 11 16 21 3 8 13 18 0 5 10 15 20 2 7 12 17 22 4 9 14 19 1 6 11
		// temp |= 0x0000400000800001 << (11+5*i)%23;
		temp |= Maskshift(0x0000400000800001,23,i);

		// pattern 14 8 2 25 19 13 7 1 24 18 12 6 0 23 17 11 5 28 22 16 10 4 27 21 15 9 3 26 20 14
		// temp |= 0x0400000020000001 << (14+23*i)%29;
		temp |= Maskshift(0x0400000020000001,29,i);

		// pattern 15 13 11 9 7 5 3 1 30 28 26 24 22 20 18 16 14 12 10 8 6 4 2 0 29 27 25 23 21 19 17 15
		// temp |= 0x4000000080000001 << (15+29*i)%31;
		temp |= Maskshift(0x4000000080000001,31,i);

		// pattern 18 28 1 11 21 31 4 14 24 34 7 17 27 0 10 20 30 3 13 23 33 6 16 26 36 9 19 29 2 12 22 32 5 15 25 35 8 18
		// temp |= 0x0000002000000001 << (18+10*i)%37;
		temp |= Maskshift(0x0000002000000001,37,i);

		// pattern 20 38 15 33 10 28 5 23 0 18 36 13 31 8 26 3 21 39 16 34 11 29 6 24 1 19 37 14 32 9 27 4 22 40 17 35 12 30 7 25 2 20
		// temp |= 0x0000020000000001 << (20+18*i)%41;
		temp |= Maskshift(0x0000020000000001,41,i);

		// pattern 21 0 22 1 23 2 24 3 25 4 26 5 27 6 28 7 29 8 30 9 31 10 32 11 33 12 34 13 35 14 36 15 37 16 38 17 39 18 40 19 41 20 42 21
		// temp |= 0x0000080000000001 << (21+22*i)%43;
		temp |= Maskshift(0x0000080000000001,43,i);

		// pattern 23 6 36 19 2 32 15 45 28 11 41 24 7 37 20 3 33 16 46 29 12 42 25 8 38 21 4 34 17 0 30 13 43 26 9 39 22 5 35 18 1 31 14 44 27 10 40 23 
		// temp |= 0x0000800000000001 << (23+30*i)%47;
		temp |= Maskshift(0x0000800000000001,47,i);

		// pattern 26 15 4 46 35 24 13 2 44 33 22 11 0 42 31 20 9 51 40 29 18 7 49 38 27 16 5 47 36 25 14 3 45 34 23 12 1 43 32 21 10 52 41 30 19 8 50 39 28 17 6 48 37 26
		// temp |= 0x0020000000000001 << (26+42*i)%53;
		temp |= Maskshift(0x0020000000000001,53,i);

		// pattern 29 24 19 14 9 4 58 53 48 43 38 33 28 23 18 13 8 3 57 52 47 42 37 32 27 22 17 12 7 2 56 51 46 41 36 31 26 21 16 11 6 1 55 50 45 40 35 30 25 20 15 10 5 0 54 49 44 39 34 29
		// temp |= 0x0800000000000001 << (29+54*i)%59;
		temp |= Maskshift(0x0800000000000001,59,i);
 
		// 30 27 24 21 18 15 12 9 6 3 0 58 55 52 49 46 43 40 37 34 31 28 25 22 19 16 13 10 7 4 1 59 56 53 50 47 44 41 38 35 32 29 26 23 20 17 14 11 8 5 2 60 57 54 51 48 45 42 39 36 33 30
		// temp |= 0x2000000000000001 << (30+58*i)%61;
		temp |= Maskshift(0x2000000000000001,61,i);

		// temp |= 1ULL << (33+3*i)%67;
		temp |= Maskshift2(1ULL,67,i);

		// temp |= Maskshift2(1ULL,71,i);

		
		num+=64-_mm_popcnt_u64(temp);
	}
	cout << num+18 << endl;
	clock_t t1 = clock();
	cout << "1 " << (t1-t0)* 1e-6  << '\n' << '\n';

  return 0;
}

