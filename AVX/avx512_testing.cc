#include <iostream>
#include <immintrin.h>



using namespace std;



int main(int argc, char const *argv[]){
__m512i a;
uint64_t t = 0XFFFFFFFFFFFFFFFF;

/*

vmovq = avx move quad word https://docs.oracle.com/cd/E36784_01/html/E36859/gntbd.html
vpinsrq =vpinsrqhttps://www.felixcloutier.com/x86/pinsrb:pinsrd:pinsrq


.LBB11:
	.file 3 "/usr/lib/gcc/x86_64-linux-gnu/8/include/avx512fintrin.h"
	.loc 3 84 44

	movq	248(%rsp), %rax 
	movq	240(%rsp), %rdx
	vmovq	%rdx, %xmm4
	vpinsrq	$1, %rax, %xmm4, %xmm2
	
	movq	232(%rsp), %rax
	movq	224(%rsp), %rdx
	vmovq	%rdx, %xmm5
	vpinsrq	$1, %rax, %xmm5, %xmm1
	
	movq	216(%rsp), %rax
	movq	208(%rsp), %rdx
	vmovq	%rdx, %xmm6
	vpinsrq	$1, %rax, %xmm6, %xmm3
	
	movq	200(%rsp), %rax
	movq	192(%rsp), %rdx
	vmovq	%rdx, %xmm7
	vpinsrq	$1, %rax, %xmm7, %xmm0
	
	vinserti128	$0x1, %xmm3, %ymm0, %ymm0
	vinserti128	$0x1, %xmm2, %ymm1, %ymm1
	vinserti64x4	$0x1, %ymm1, %zmm0, %zmm0
.LBE11:

.LBB11:
	.file 3 "/usr/lib/gcc/x86_64-linux-gnu/8/include/avx512fintrin.h"
	.loc 3 84 44
	
	movq	248(%rsp), %rax 
	movq	240(%rsp), %rdx
	vmovq	%rdx, %xmm4
	vpinsrq	$1, %rax, %xmm4, %xmm2
	
	movq	232(%rsp), %rax
	movq	224(%rsp), %rdx
	vmovq	%rdx, %xmm5
	vpinsrq	$1, %rax, %xmm5, %xmm1
	
	movq	216(%rsp), %rax
	movq	208(%rsp), %rdx
	vmovq	%rdx, %xmm6
	vpinsrq	$1, %rax, %xmm6, %xmm3
	
	movq	200(%rsp), %rax
	movq	192(%rsp), %rdx
	vmovq	%rdx, %xmm7
	vpinsrq	$1, %rax, %xmm7, %xmm0
	
	vinserti128	$0x1, %xmm3, %ymm0, %ymm0
	vinserti128	$0x1, %xmm2, %ymm1, %ymm1
.LBE11:
*/

a = _mm512_set_epi64(0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF, 0XFFFFFFFFFFFFFFFF);

a = a << 2;
__m256i test = _mm512_extracti64x4_epi64(a, 0);
cout << hex << _mm256_extract_epi64(test, 3) << endl;
cout << hex << _mm256_extract_epi64(test, 2) << endl;
cout << hex << _mm256_extract_epi64(test, 1) << endl;
cout << hex << _mm256_extract_epi64(test, 0) << endl;
cout << endl;

 test = _mm512_extracti64x4_epi64(a, 1);
cout << hex << _mm256_extract_epi64(test, 3) << endl;
cout << hex << _mm256_extract_epi64(test, 2) << endl;
cout << hex << _mm256_extract_epi64(test, 1) << endl;
cout << hex << _mm256_extract_epi64(test, 0) << endl;
cout << endl;

	return 0;
}