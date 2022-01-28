//Alice Houston
#include<iostream>
#include<vector>
#include<fstream>
#include<sys/stat.h>
#include<string>

using namespace std;
//choose(n,r) = n!/(r! (n-r)!) = 52! / (6! 46!)

vector<double> factmemo{1};


void Reader(string file){
	struct stat buffer;
	if(stat("file", &buffer) != 0)
		return;
  // Create a text string, which is used to output the text file
  double myText;

  // Read from the text file
  ifstream MyReadFile("file");
  factmemo.pop_back();
  while (MyReadFile >> myText) {
    if (factmemo.size() == factmemo.capacity())
  		factmemo.reserve(factmemo.size()*1.50);
  	factmemo.push_back(myText);
  }
  // Close the file
  MyReadFile.close(); 
}

void Writer(string file){
  // Create and open a text file
  ofstream Factfile(file);
  
  // Write to the file
  for (size_t i = 0; i < factmemo.size(); i++){
    if (factmemo[i] == 0)
      break;
    Factfile << factmemo[i] << endl;
  }

  // Close the file
  Factfile.close();
}

double fact(int32_t n) {
	if (n < factmemo.size())
		return factmemo[n];
	for (uint32_t i = factmemo.size(); i <= n; i++) {
	if (factmemo.size() == factmemo.capacity())
		factmemo.reserve(factmemo.size()*1.50);
		factmemo.push_back(factmemo[i-1] * i);
	}
	return factmemo[n];
}

double choose(int n, int r) {
	static double memo[100][100] = {0};

	if (memo[n][r] != 0)
		return memo[n][r];
	
	memo[n][r]=fact(n)/(fact(n)*fact(n-r));
	return memo[n][r];
}

int main(){
	string factfile = "facttable.txt";
	Reader(factfile);
	cout << fact(20) << endl;
	cout << fact(170) << endl;
	cout << choose(52, 6) << endl;
	Writer(factfile);

	return 0;
}
