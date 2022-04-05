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

u32 P_box_1(u32 input){
	/*
		0 abcd efgh
		1 efgh abcd
		2 ghef cdab
		3 ghcd efab
		4 gchd eafb
		5 gchd eabf
	*/
	input = (input & 0x00) | ((input & 0xF0)>>4) | ((input & 0xF)<<4); //1
	input = (input & 0x00) | ((input & 0xcc)>>2) | ((input & 0x33)<<2);//2
	input = (input & 0xc3) | ((input & 0x30)>>2) | ((input & 0xc)<<2);//3
	input = (input & 0x99) | ((input & 0x44)>>1) | ((input & 0x22)<<1);//4
	return  (input & 0xFC) | ((input & 0x2)>>1) | ((input & 0x1)<<1);//5
}

u32 Round(u32 data){
	constexpr int32_t SBox1 [16]{8,2,4,11,6,14,7,1,3,13,9,12,15,5,0,10};
	constexpr int32_t SBox2 [16]{6,13,1,5,7,12,8,3,2,0,14,10,15,9,11,4};

	for (u32 i = 0; i <= 10000; i++){
		data = P_box_1(SBox1[data & 0xf] | (SBox2[data >> 4] << 4));
	}
	return data;
}

u32 Encryption(u32 data,u32 key){
	return Round((Round((Round(data) ^ key & 0xFF)) ^ (key >> 8) & 0xFF));
}

int main(int argc, char const *argv[]) {

	cout << Encryption(171,0xED6E) << endl;
	cout << Encryption(170,0xED6E) << endl;
	cout << Encryption(170,0x6FED) << endl;
	cout << Encryption(255,0xED6E) << endl;
	cout << Encryption(0,0xED6E) << endl;
	cout << Encryption(100,0xED6E) << endl;

	return 0;
}

