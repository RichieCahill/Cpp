/*
Resources i use to make this
https://www.youtube.com/watch?v=DLjzI5dX8jc
https://www.youtube.com/watch?v=7mwgA9XFIEQ
*/
#include <iostream>

using namespace std;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

/*
	5 gchdeabf
	0 abcdefgh
*/
u32 P_box_1(u32 input){
	return  ((input & 0x80)>>6) | ((input & 0x40)>>1) | ((input & 0x20)>>5) | (input & 0x18) | ((input & 0x4)<<5) | ((input & 0x2)<<5) | ((input & 0x1)<<2);//5
}

u32 Round(u32 data){
	constexpr int32_t SBox1 [16]{14,7,1,8,2,13,4,6,0,10,15,3,11,9,5,12};
	constexpr int32_t SBox2 [16]{9,2,8,7,15,3,0,4,6,13,11,14,5,1,10,12};

	for (u32 i = 0; i <= 10000; i++){
		data = P_box_1(data);
		data = SBox1[data & 0xf] | (SBox2[data >> 4] << 4);
	}
	return data;
}

u32 Dencryption(u32 data,u32 key){
	return Round(Round(Round(data) ^ (key >> 8) & 0xFF) ^ key & 0xFF);
}

int main(int argc, char const *argv[]) {

	cout << Dencryption(218,0xED6E) << endl;
	cout << Dencryption(241,0xED6E) << endl;
	cout << Dencryption(12,0x6FED) << endl;
	cout << Dencryption(239,0xED6E) << endl;
	cout << Dencryption(188,0xED6E) << endl;
	cout << Dencryption(63,0xED6E) << endl;

	return 0;
}
