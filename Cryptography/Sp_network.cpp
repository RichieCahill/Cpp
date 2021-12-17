/*
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
  if (input > 0)
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

int permutation_box(uint8_t input){
  /*   1010 1010
     0 abcd efgh
     1 fgha bcde
     2 hafg debc
     3 hade fgbc
     4 hdae fbgc 
     5 hdae fbcg
       0011 0011
  */

input = input >> 3 | input << 5;
input = ((input & 0xcc)>>2) | ((input & 0x33)<<2);
input = (input & 0xc3) | ((input & 0x30)>>2) | ((input & 0xc)<<2);
input = (input & 0x99) | ((input & 0x44)>>1) | ((input & 0x22)<<1);
input = (input & 0x99) | ((input & 0x2)>>1) | ((input & 0x1)<<1);

return input;  
}


int main(int argc, char const *argv[]) {

  return 0;
}

