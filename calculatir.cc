#include <iostream>
#include <string.h>

using namespace std;

int64_t main() {
    int64_t a = 0;
    int64_t b = 0;
    int64_t d = 0;
    cout << "num 1/n";
    cin >> a;
    cout << "num 2/n";
    cin >> b;
    char c;
    cin >> c;
    if (c == '+'){
        d=a+b;
    }
    else if (c == '-'){
        d=a-b;
    }
    else if (c == '*'){
        d=a*b;
    }
    else if (c == '/'){
        if (a == 0 || b == 0){
            cout << "Fuck off dont devide by 0 assh home" << endl;
        }
        else
            d=a/b;
    }
    else {
        cout << "Invalid input" << endl;
    }

    cout << d << endl;
    return 0;
}
