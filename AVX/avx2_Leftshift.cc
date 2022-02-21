#include <iostream>
#include <immintrin.h>



using namespace std;

void out(__m256i a){
cout << hex << _mm256_extract_epi64(a, 3) << endl;
cout << hex << _mm256_extract_epi64(a, 2) << endl;
cout << hex << _mm256_extract_epi64(a, 1) << endl;
cout << hex << _mm256_extract_epi64(a, 0) << endl;
cout << endl;
}

uint64_t asmadd(uint64_t c, uint64_t b){
__asm__ (
	"addl %%ebx, %%ecx;" 
	"addl %%ecx, %%ebx;"
	"imull %%ebx, %%ecx;" 
	: "=c" (c) : "c" (c) , "b" (b));
return c;
}

/*
__m256i avx256_sub (__m256i n, __m256i s){
__asm__ (
	"addl %%ebx, %%eax;" 
	"addl %%eax, %%ebx;"
	"imull %%ebx, %%eax;" 
	: "=a" (n) : "a" (n) , "b" (s));
return n;
}

#	./avx2_testing.cc:90: 	a = _mm256_sub_epi64(a,a);
	.loc 2 90 22
	cd	%ymm0, 128(%rsp)	# D.71430, a
*/


__m256i avx256_ls (__m256i n, int64_t s){
	if (s==0)
		return n;
	__m256i temp;
	
	//creats a temp __m256i taht maske the firs n bit in lane 3 2 1
	//i think can get this down to one 64 bit register and probably faster
	uint64_t rail2 = _mm256_extract_epi64(n, 2), rail1 = _mm256_extract_epi64(n, 1), rail0 = _mm256_extract_epi64(n, 0);
	
	rail2 = rail2 >> (64-s);
	rail1 = rail1 >> (64-s);
	rail0 = rail0 >> (64-s);

	temp = _mm256_set_epi64x(rail2, rail1, rail0, 0X0000000000000000);

	// left shit the 4 64 bit ins in n then or with temp
	n = n << s;
	n = _mm256_or_si256(n, temp);
	return n;
}

// _mm256_slli_si256 has to be assigned at compile time so this is less helpfull then i thought
// it may be worth it becau i beleave the register will need to dissisebled less
__m256i avx256_ls_improved (__m256i n, int s){
	if (s==0)
		return n;
	__m256i temp;
	if (s==8){	
		//i think this cn be  faster
		uint64_t rail1 = _mm256_extract_epi64(n, 1);
		
		rail1 = rail1 >> (64-s);
		
		temp = _mm256_set_epi64x(0X0000000000000000, rail1, 0X0000000000000000, 0X0000000000000000);
	
		n = _mm256_or_si256(_mm256_slli_si256(n,1), temp);

		return n;
	}

	//creats a temp __m256i taht maske the firs n bit in lane 3 2 1
	//i think can get this down to one 64 bit register and probably faster
	uint64_t rail2 = _mm256_extract_epi64(n, 2), rail1 = _mm256_extract_epi64(n, 1), rail0 = _mm256_extract_epi64(n, 0);
	
	rail2 = rail2 >> (64-s);
	rail1 = rail1 >> (64-s);
	rail0 = rail0 >> (64-s);


	temp = _mm256_set_epi64x(rail2, rail1, rail0, 0X0000000000000000);
	
	// left shit the 4 64 bit ins in n then or with temp
	n = n << s;
	n = _mm256_or_si256(n, temp);
	return n;
}

/*
//hand made
															Arch	Latency (CPI)
_mm256_extracti128_si256 = Skylake				3		1
_mm_extract_epi64 = Skylake								3		1
_mm256_set_m128i = Skylake								3		1

total 20 6.83
+			 ? ?    for _mm_set_epi64x

educated guess is total latncy 25 and cpi of 10

_mm_load may be how to build avx registers
*/

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

__m256i avx256_roll (__m256i n, int64_t s){
	__m256i temp;
	
	//This i can get this down to one 64 bit register and probably faster
	uint64_t rail3 = _mm256_extract_epi64(n, 3), rail2 = _mm256_extract_epi64(n, 2), rail1 = _mm256_extract_epi64(n, 1), rail0 = _mm256_extract_epi64(n, 0);

	rail3 = rail3 >> (64-s);
	rail2 = rail2 >> (64-s);
	rail1 = rail1 >> (64-s);
	rail0 = rail0 >> (64-s);

	temp = _mm256_set_epi64x(rail2, rail1, rail0, rail3);
	
	n = n << s;

	n = _mm256_or_si256(n, temp);
	return n;
}
int main(int argc, char const *argv[]){
__m256i a;

/*
# /usr/lib/gcc/x86_64-pc-linux-gnu/11.2.0/include/avxintrin.h:1306:   return __extension__ (__m256i)(__v4di){ __D, __C, __B, __A };
	.file 3 "/usr/lib/gcc/x86_64-pc-linux-gnu/11.2.0/include/avxintrin.h"
	.loc 3 1306 62
	movq	-32(%rsp), %rax	# __A, tmp87
	movq	-24(%rsp), %rdx	# __B, tmp88
	vmovq	%rdx, %xmm2	# tmp88, tmp88
	vpinsrq	$1, %rax, %xmm2, %xmm1	# tmp87, tmp88, tmp86
	movq	-16(%rsp), %rax	# __C, tmp90
	movq	-8(%rsp), %rdx	# __D, tmp91
	vmovq	%rdx, %xmm3	# tmp91, tmp91
	vpinsrq	$1, %rax, %xmm3, %xmm0	# tmp90, tmp91, tmp89
	vinserti128	$0x1, %xmm1, %ymm0, %ymm0	# tmp86, tmp89, tmp85
.LBE36:




# ./avx2_and_bitmaps.cc:38: cout << hex << _mm256_extract_epi64(a, 0) << endl;
	.loc 2 38 9
	leaq	_ZSt3hexRSt8ios_base(%rip), %rax	#, tmp117
	movq	%rax, %rsi	# tmp117,
	leaq	_ZSt4cout(%rip), %rax	#, tmp118
	movq	%rax, %rdi	# tmp118,
	call	_ZNSolsEPFRSt8ios_baseS0_E@PLT	#
.LBB52:
# ./avx2_and_bitmaps.cc:38: cout << hex << _mm256_extract_epi64(a, 0) << endl;
	.loc 2 38 16
	vmovdqa	(%rsp), %ymm0					# a, _14
	vmovdqa	%xmm0, 80(%rsp)				# _15, __Y
	vmovdqa	80(%rsp), %xmm0				# __Y, tmp119
	vmovq	%xmm0, %rdx							# tmp119, _50
.LBE52:
	movq	%rdx, %rsi	# _50,
	movq	%rax, %rdi	# _13,
	call	_ZNSolsEx@PLT	#
# ./avx2_and_bitmaps.cc:38: cout << hex << _mm256_extract_epi64(a, 0) << endl;
	.loc 2 38 46
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rdx	#, tmp121
	movq	%rdx, %rsi	# tmp120,
	movq	%rax, %rdi	# _16,
	call	_ZNSolsEPFRSoS_E@PLT	#
*/

	a = _mm256_set_epi64x(0X1020408102040810, 0X2040810204081020, 0X4081020408102040, 0X8102040810204081);

	a = avx256_ls(a,8);
	
	out(a);

	a = _mm256_set_epi64x(0X1020408102040810, 0X2040810204081020, 0X4081020408102040, 0X8102040810204081);

	a = avx256_ls_test(a,8);
	
	out(a);
	
	a = _mm256_set_epi64x(0X1020408102040810, 0X2040810204081020, 0X4081020408102040, 0X8102040810204081);

	a = avx256_ls_improved(a,8);
	
	out(a);

	a = _mm256_set_epi64x(0X1249249249249249, 0X2492492492492492, 0X4924924924924924, 0X9249249249249249);

	a = avx256_roll(a,3);
	
	out(a);

	return 0;
}
