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
    { 0,8 },
    { 1,2 },
    { 2,4 },
    { 3,11 },
    { 4,6 },
    { 5,14 },
    { 6,7 },
    { 7,1 },
    { 8,3 },
    { 9,13 },
    { 10,9 },
    { 11,12 },
    { 12,15 },
    { 13,5 },
    { 14,0 },
    { 15,10 },
  };
  return mp[input];
}

int S_Box_2(int input) {
  if (input > 15)
  return -1;
  map<int, int> mp ={
    { 0,6 },
    { 1,13 },
    { 2,1 },
    { 3,15 },
    { 4,7 },
    { 5,12 },
    { 6,8 },
    { 7,3},
    { 8,2 },
    { 9,0 },
    { 10,14 },
    { 11,10 },
    { 12,15 },
    { 13,9 },
    { 14,11 },
    { 15,4 },
  };
  return mp[input];
}

int P_box_1(int input){
  /*   0111 0010
     0 abcd efgh
     1 fgha bcde
     2 hafg debc
     3 hade fgbc
     4 hdae fbgc 
     5 hdae fbcg
       0100 0111
  */

input = input >> 3 | input << 5;
input = ((input & 0xcc)>>2) | ((input & 0x33)<<2);
input = (input & 0xc3) | ((input & 0x30)>>2) | ((input & 0xc)<<2);
input = (input & 0x99) | ((input & 0x44)>>1) | ((input & 0x22)<<1);
input = (input & 0xFC) | ((input & 0x2)>>1) | ((input & 0x1)<<1);

return input;  
}

int round(int data){
  for (int i = 0; i <= 5; i++){
    int a, b, c;
    a = data & 0xf;
    b = data >> 4;
    c = S_Box_1(a) | (S_Box_2(b) << 4);
    data = P_box_1(c);
  }
  return data;
}

int encryption(int data,int key){
  int keya , keyb ;
  keya = key & 0xff;
  keyb = key >> 8;
  data = round(data);
  data = data ^ keya;
  data = round(data);
  data = data ^ keyb;
  data = round(data);


  return data;
}

int main(int argc, char const *argv[]) {
  int test = 300;
  test = encryption(test,0xED6E);
  cout << test << endl;

  return 0;
}

