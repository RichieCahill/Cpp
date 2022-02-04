//https://gmplib.org/manual/C_002b_002b-Interface-Integers
#include <iostream>
#include <stdio.h>
#include <gmp.h>
#include <gmpxx.h>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <string>

using namespace std;



mpz_class gcd(mpz_class m, mpz_class n){
	if (n==0)
		return m;
	return gcd(n, m%n);
}

mpz_class lcmout("0");
mpz_class lcm(mpz_class m, mpz_class n){
	return m * n / gcd(m,n);
} 


mpz_class power(mpz_class a,mpz_class n){
	mpz_class prod = 1;
	while (n>0){
		if (n%2==1)
			prod=prod*a;
		a=a*a;
		n=n/2;
	}
	return prod;
}



mpz_class memofact(uint64_t n){
	static vector<mpz_class> factmemo{1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,6227020800,87178291200,1307674368000,20922789888000,355687428096000,6402373705728000,121645100408832000,2432902008176640000};
	mpz_class temp = 1;
	if (n < factmemo.size())
		return factmemo[n];
	for (uint64_t i = factmemo.size(); i <= n; i++) {
		if (factmemo.size() == factmemo.capacity())
			factmemo.reserve(factmemo.size()*1.50);
			factmemo.push_back(factmemo[i-1] * i);
		}
	return factmemo[n];
}

mpz_class fastfact(mpz_class n){
	mpz_class temp = 1;
	for (mpz_class i = 1; i <= n; i++) {
	temp=temp*i;
	}
	return temp;
}


int main(int argc, char const *argv[]){

	cout << "gcd" << endl;
	cout << gcd(18, 15) << endl;
	cout << "lcm" << endl;
	cout << lcm(18, 12) << endl;
	cout << "power" << endl;
	cout << power(10,10) << endl;
	cout << "Fact" << endl;
	cout << fastfact(5) << endl;
	cout << memofact(5) << endl;

	return 0;
}


