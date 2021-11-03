#include <iostream>

using namespace std;




int main() {
	for (int64_t i = 0; i <= 101; i++){

		if (i % 3 == 0 && i % 5 == 0){
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
return 0;
}
