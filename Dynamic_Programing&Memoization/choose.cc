
#include<iostream>

using namespace std;

//choose(n,r) = n!/(r! (n-r)!) = 52! / (6! 46!)

double fact(int32_t n) {
	static double memo[100]{1,1,2,6,24,120,720,5040,40320,362880,3628800};
	if (memo[n] != 0)
		return memo[n];
	for (uint32_t i = 9; i <= n; i++)
	{
		memo[i] = memo[i-1] * i;
	}
	return memo[n];
}

double choose(int n, int r){
	static double memo[100][100] = {0};

	if (memo[n][r] != 0)
		return memo[n][r];
	
	memo[n][r]=fact(n)/(fact(n)*fact(n-r));
	return memo[n][r];
}

int main()
{
	cout << choose(52, 6) << '\n';
	
	return 0;
}
