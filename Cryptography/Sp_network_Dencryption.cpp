/*
Resources i use to make this
https://www.youtube.com/watch?v=DLjzI5dX8jc
https://www.youtube.com/watch?v=7mwgA9XFIEQ
*/
#include <iostream>
#include <map>

using namespace std;

uint32_t S_Box_1(uint32_t input) {
  if (input > 15)
  return -1;
  map<uint32_t, uint32_t> mp ={
    { 8,0 },
    { 2,1 },
    { 4,2 },
    { 11,3 },
    { 6,4 },
    { 14,5 },
    { 7,6 },
    { 1,7 },
    { 3,8 },
    { 13,9 },
    { 9,10 },
    { 12,11 },
    { 15,12 },
    { 5,13 },
    { 0,14 },
    { 10,15 },
  };
  return mp[input];
}

uint32_t S_Box_2(uint32_t input) {
  if (input > 15)
  return -1;
  map<uint32_t, uint32_t> mp ={
    { 6,0 },
    { 13,1 },
    { 1,2 },
    { 5,3 },
    { 7,4 },
    { 12,5 },
    { 8,6 },
    { 3,7},
    { 2,8 },
    { 0,9 },
    { 14,10 },
    { 10,11 },
    { 15,12 },
    { 9,13 },
    { 11,14 },
    { 4,15 },
  };
  return mp[input];
}

uint32_t P_box_1(uint32_t input){
    /*
    5 gchd eabf
    4 gchd eafb
    3 ghcd efab
    2 ghef cdab
    1 efgh abcd
    0 abcd efgh
    
  */
  input = (input & 0xFC) | ((input & 0x2)>>1) | ((input & 0x1)<<1); //5
  input = (input & 0x99) | ((input & 0x44)>>1) | ((input & 0x22)<<1); //4
  input = (input & 0xc3) | ((input & 0x30)>>2) | ((input & 0xc)<<2);//3
  input = (input & 0x00) | ((input & 0xcc)>>2) | ((input & 0x33)<<2); //2
  input = (input & 0x00) | ((input & 0xF0)>>4) | ((input & 0xF)<<4);
  // input = (input << 4) | (input >> 4);//1
return input;  
}

uint32_t Round(uint32_t data){
  for (uint32_t i = 0; i <= 10000; i++){
    uint32_t a, b, c;
    data = P_box_1(data);
    a = data & 0xf;
    b = data >> 4;
    data = S_Box_1(a) | (S_Box_2(b) << 4); // 1110 1101
    
  }
  return data;
}

uint32_t Dencryption(uint32_t data,uint32_t key){
  uint32_t keya , keyb ;
  keya = 0x6E;
  keyb = 0xED;
  data = Round(data);
  data = data ^ keyb;
  data = Round(data);
  data = data ^ keya;
  data = Round(data);


  return data;
}

int main(int argc, char const *argv[]) {
  uint32_t test = 218;
  test = Dencryption(test,0xED6E);
  cout << test << endl;

  test = 241;
  test = Dencryption(test,0xED6E);
  cout << test << endl;

  test = 239;
  test = Dencryption(test,0xED6E);
  cout << test << endl;
  
  test = 188;
  test = Dencryption(test,0xED6E);
  cout << test << endl;
  
  test = 63;
  test = Dencryption(test,0xED6E);
  cout << test << endl;

  return 0;
}
