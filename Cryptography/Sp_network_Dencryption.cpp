/*
Resources i use to make this
https://www.youtube.com/watch?v=DLjzI5dX8jc
https://www.youtube.com/watch?v=7mwgA9XFIEQ
*/

#include <iostream>
#include <map>
using namespace std;

int S_Box_1(int input) {
  if (input > 15)
  return -1;
  map<int, int> mp ={
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

int S_Box_2(int input) {
  if (input > 15)
  return -1;
  map<int, int> mp ={
    { 6,0 },
    { 13,1 },
    { 1,2 },
    { 15,3 },
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

int P_box_1(int input){
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

int Round(int data){
  for (int i = 0; i <= 1; i++){
    int a, b, c;
    data = P_box_1(data);
    a = data & 0xf;
    b = data >> 4;
    data = S_Box_1(a) | (S_Box_2(b) << 4); // 1110 1101
    
  }
  return data;
}

int Dencryption(int data,int key){
  int keya , keyb ;
  keya = key & 0xff;
  keyb = key >> 8;
  data = Round(data);
  data = data ^ keyb;
  data = Round(data);
  data = data ^ keya;
  data = Round(data);


  return data;
}

int main(int argc, char const *argv[]) {
  int test = 156;
  test = Dencryption(test,0xED6E);
  cout << test << endl;

  return 0;
}
