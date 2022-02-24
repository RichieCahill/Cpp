/*
resorest
timehttps://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#
https://github.com/ahuston-0 helped with multithreading
https://stackoverflow.com/questions/11103249/raw-file-format-c
0is can be prime 1 isnt

TODO
Make it out to a vector instead of a file
and output that vector to a file
*/

#include <iostream>
#include <immintrin.h>
#include <thread>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//couts an AVX register right to left
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

void list_generator(uint64_t s, uint64_t e, string name){
	//creath the file the it outputs to
	ofstream Factfile(name, ios::out | ios::binary);
	
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

		// masks multiple of 3
		switch (i%3) {
			case 0:
				temp = _mm256_or_si256(temp, avx256_ls_test(mask3,0));
				break;
			case 1:
				temp = _mm256_or_si256(temp, avx256_ls_test(mask3,2));
				break;
			case 2:
				temp = _mm256_or_si256(temp, avx256_ls_test(mask3,1));
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

			//Outputs the avx register to disk in raw
			Factfile.write ((char*)&temp, sizeof (temp));
	}
	Factfile.close();
}


int main() {
	//the number you arc computing to
	constexpr uint64_t n = 240000000000;
	//adding allocating the number spaces a vector needs
	constexpr uint32_t size = (n+511)/512;
	//get the total number of prosesor on the machesn
	const auto processor_count = thread::hardware_concurrency();
	// const uint32_t processor_count = 4;

	//divides the work into processor_count of equal pieces
	const uint32_t piece = (size-(size%processor_count)+size)/processor_count;

	uint32_t start = 1;
	
	//create a vector of threads
	vector<thread> t;

	//creat thred till the processor_count
	//alice helped with the for loop that creats the threds
	for(int i = 0; i < processor_count; i++){

		//make output file and atempts to imcrment it 
		// it doesn't work i getting ASCII value not numbers
		string file = "/mnt/temp/test";
		char c = i;
		cout << c << endl;
		file += c;
		file += ".csv";
		cout << file << endl;
		 
		//sets the ending position of the fuction
		uint32_t end=piece+start;
  	
		//spawns a thread with the list generator
		t.emplace_back(list_generator, start, end, file);
		
		//seth the start to the ole ned for the net iteration
		start = end;
	}

	//Joins all the thread at the end
	for(auto&& e: t){
  	e.join();
	} 
}


/*
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

