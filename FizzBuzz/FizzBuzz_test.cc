#include <iostream>

using namespace std;

void fizzbuzz() {
    for (int64_t i = 1; i <= 10000000; i++){

        if (i % 15 == 0){
            cout << "fizz buzz\n";
        }
        else if (i % 3 == 0){
            cout << "fizz\n";
        }
        else if (i % 5 == 0){
            cout << "buzz\n";
        }

        else cout << i << endl;
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