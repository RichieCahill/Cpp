#include <iostream>
#include <immintrin.h>



using namespace std;

uint64_t asmadd(uint64_t c, uint64_t b){
__asm__ (
	"addl %%ebx, %%ecx;" 
	"addl %%ecx, %%ebx;"
	"imull %%ebx, %%ecx;" 
	: "=c" (c) : "c" (c) , "b" (b));
return c;
}


__m256i avx256_sub (__m256i n, __m256i s){
__asm__ (
	"addl %%ebx, %%eax;" 
	"addl %%eax, %%ebx;"
	"imull %%ebx, %%eax;" 
	: "=a" (n) : "a" (n) , "b" (s));
return n;
}
/*
#	./avx2_testing.cc:90: 	a = _mm256_sub_epi64(a,a);
	.loc 2 90 22
	cd	%ymm0, 128(%rsp)	# D.71430, a
*/

/*
__m256i avx256_rol (__m256i n, uint64_t s){
__asm__ (
	"addl %%ebx, %%eax;" 
	"addl %%eax, %%ebx;"
	"imull %%ebx, %%eax;" 
	: "=a" (n) : "a" (n) , "b" (s));
return n;
}
*/



int main(int argc, char const *argv[]){
__m256i a;

a = _mm256_set_epi64x(0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF);

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

	a = _mm256_sub_epi64(a,a);

	cout << hex << _mm256_extract_epi64(a, 3) << endl;
	cout << hex << _mm256_extract_epi64(a, 2) << endl;
	cout << hex << _mm256_extract_epi64(a, 1) << endl;
	cout << hex << _mm256_extract_epi64(a, 0) << endl;
	cout << endl;

	cout << asmadd(1, 1) << endl;
	return 0;
}