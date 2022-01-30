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
//choose(n,r) = n!/(r! (n-r)!) = 52! / (6! 46!)

vector<double> factmemo{1};

//reads the fact table from if it exists
void Reader(string file){
	struct stat buffer;
	if(stat("file", &buffer) != 0)
		return;
	double input;

	// Read from the text file
	ifstream MyReadFile("file");
	factmemo.pop_back();
	while (MyReadFile >> input) {
		if (factmemo.size() == factmemo.capacity())
			factmemo.reserve(factmemo.size()*1.50);
		factmemo.push_back(input);
	}
	MyReadFile.close(); 
}

//writes factmemo array to fact table
void Writer(string file){
	ofstream Factfile(file);
	
	// Write to the file
	for (size_t i = 0; i < factmemo.size(); i++){
		if (factmemo[i] == 0)
			break;
		Factfile << factmemo[i] << endl;
	}
	Factfile.close();
}

//factoreal calculation function
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

//choose calculation function
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
