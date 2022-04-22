#include <iostream>
#include <string.h>

using namespace std;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;


int main() {
    i64 a = 0;
    i64 b = 0;
    i64 d = 0;
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
