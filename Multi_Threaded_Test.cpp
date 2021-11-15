#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <thread>

using namespace std;

void modulo(int64_t in, int64_t num, string word, string& output) {
  if (in % num == 0) {
    output += word;
  }
}

void fizzbuzz() {
  for (int64_t i = 1; i <= INT32_MAX; i++){
    char num[19];
    string output;
    
    modulo(i, 3, "Fizz", output);
    modulo(i, 5, "Buzz", output);

    if (output == "") {
        sprintf(num, "%d", i);
        output = num;
    }
    
    //cout << output << endl;
    }
}

void timed() {
	clock_t t0 = clock();
	fizzbuzz();
	clock_t t1 = clock();
  cout << (t1-t0) * 1e-6 << '\n';
}
  
  
int main()
{
    cout << "Threads 1 and 2 and 3 "
         "operating independently" << endl;
  
    thread th1(timed);
  
    thread th2(timed);
  
    thread th3(timed);
  
    thread th4(timed);
  
    thread th5(timed);
  
    thread th6(timed);

    // Wait for the threads to finish
    // Wait for thread t1 to finish
    th1.join();
  
    // Wait for thread t2 to finish
    th2.join();
  
    // Wait for thread t3 to finish
    th3.join();
  
    th4.join();
    
    th5.join();
    
    th6.join();
    return 0;
}