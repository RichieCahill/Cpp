#include <iostream>
#include <ctime>

using namespace std;


int guesser (int i, int inc, int num, int count) {
  if (i < num)
  {

    // cout << i << " i" << "\n";
    // cout << inc << " inc" << "\n";

    i = i+inc;
    if (inc > 1){
    inc = (inc%2==0)?(inc>>1):((inc>>1)+1);
    }

    count++;
    return guesser(i, inc, num, count);
  }
  else if (i > num)
  {

    i = i-inc;

    // cout << i << " i" << "\n";
    // cout << inc << " inc" << "\n";

    if (inc > 1){
      inc = (inc%2==0)?(inc>>1):((inc>>1)+1);
    } 
    
    
    count++;
    return guesser(i, inc, num, count);
  }
  else
  {

    cout << i << " = " << num << " it took " << count << " iterations" << '\n';
    return i;
  }
}

int main(int argc, char const *argv[])
{
  int32_t num = 0;

  //generates a number between 1 and 1000:
  // srand (time(NULL));
  // num = rand() % 1000 + 1;
  for (int num = 1; num <= 1000; num++)
    guesser(500, 250, num, 0);

  /* code */
  return 0;
}

