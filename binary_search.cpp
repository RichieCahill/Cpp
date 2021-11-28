#include <iostream>
#include <ctime>

using namespace std;


int guesser (int i, int num, int count) {
  if (i < num) {
    //1000 iterations to 1000 isn't efesent but it works
    i = i*2+2;
    //dosnt work
    //i = i+i/2;

    count++;
    guesser(i, num, count);
  } else if (i > num) {
    
    //i = i >> 1;
    i = i/2;

    count++;
    guesser(i, num, count);
  } else {

    cout << i << " = " << num << " it took " << count << " iterations" << '\n';
    return i;
  }
}

int main(int argc, char const *argv[])
{
  int32_t num = 0;

  //generates a number between 1 and 1000:
  //srand (time(NULL));
  //num = rand() % 1000 + 1;

  for (int i = 1; i <= 1000; i++)
    guesser(500, i, 0);

  /* code */
  return 0;
}

