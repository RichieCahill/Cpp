#include <iostream>
#include <string>
#include <time.h>

using namespace std;


void modulo(int64_t in, int64_t num, string word, string& output) {
  if (in % num == 0) {
    output += word;
  }
}

void fizzbuzz() {
  for (int64_t i = 1; i <= 10000000; i++){
    char num[10];
    string output;
    
    modulo(i, 3, "Fizz", output);
    modulo(i, 5, "Buzz", output);
    modulo(i, 6, "Buzz", output);
    modulo(i, 8, "Buzz", output);

    if (output == "") {
        sprintf(num, "%d", i);
        output = num;
    }
    
    cout << output << endl;
    }
}

int main() {
  const int n = 100000000;
	clock_t t0 = clock();
	fizzbuzz();
	clock_t t1 = clock();
  cout << (t1-t0) * 1e-6 << '\n';
  return 0;
}