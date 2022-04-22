//resources
//Alice Houston
//https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-14-17-c
//https://www.w3schools.com/cpp/cpp_files.asp
//https://linux.die.net/man/2/stat

#include<iostream>
#include<vector>
#include<fstream>
#include<sys/stat.h>
#include<string>

using namespace std;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

//choose(n,r) = n!/(r! (n-r)!) = 52! / (6! 46!)

const string factfile = "facttable.txt";
vector<double> factmemo{1};

//reads the fact table from if it exists
void Reader(){
	struct stat buffer;
	if(stat(facttable.txt, &buffer) != 0)
		return;
	double input;

	// Read from the text file
	ifstream MyReadFile(factfile);
	factmemo.pop_back();
	while (MyReadFile >> input) {
		if (factmemo.size() == factmemo.capacity())
			factmemo.reserve(factmemo.size()*1.50);
		factmemo.push_back(input);
	}
	MyReadFile.close(); 
}

//writes factmemo array to fact table
void Writer(){
	ofstream Factfile(factfile);
	
	// Write to the file
	for (size_t i = 0; i < factmemo.size(); i++){
		if (factmemo[i] == 0)
			break;
		Factfile << factmemo[i] << endl;
	}
	Factfile.close();
}

/*
factoreal calculation function
this function is O(n) if the data is not in the array but it is Ω(1) if its present
*/
double fact(i32 n) {
	if (n < factmemo.size())
		return factmemo[n];
	for (u32 i = factmemo.size(); i <= n; i++) {
	if (factmemo.size() == factmemo.capacity())
		factmemo.reserve(factmemo.size()*1.50);
		factmemo.push_back(factmemo[i-1] * i);
	}
	return factmemo[n];
}

/*
choose calculation
this function is O(n) because the factor is memoization 
but can be Ω(1) if the factor was previously calculated
*/
double choose(u32 n, u32 r) {
	static double memo[100][100] = {0};

	if (memo[n][r] != 0)
		return memo[n][r];
	
	memo[n][r]=fact(n)/(fact(n)*fact(n-r));
	return memo[n][r];
}

int main(){
	Reader();
	cout << fact(20) << endl;
	cout << fact(170) << endl;
	cout << fact(171) << endl;
	cout << choose(52, 6) << endl;
	Writer();

	return 0;
}
