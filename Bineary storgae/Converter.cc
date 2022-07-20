#include <iostream>
#include <immintrin.h>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <regex>
#include <memory.h>

using namespace std;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;



void DeleteStart(string& str){
	str = str.substr(str.find(",")+1);
}

void DeleteMulti(string& str,int n){
	for (size_t i = 0; i <= n-1; i++){
		DeleteStart(str);
	}
}

void iCutStart(string& str, ofstream& OutFile){
		i32 num = stoi(str.substr(0, str.find(",")));
		DeleteStart(str);
		OutFile.write(reinterpret_cast<const char *>(&num), sizeof(num));

}

void iCutMulti(string& str, ofstream& OutFile, int n){
	for (size_t i = 0; i <= n-1; i++){
		iCutStart(str, OutFile);
	}
}

void dCutStart(string& str, ofstream& OutFile){
	double num = stod(str.substr(0, str.find(",")));
	DeleteStart(str);
	OutFile.write(reinterpret_cast<const char *>(&num), sizeof(num));
}

struct covidreport{
u32 confirmed,deaths,totaltestresults;
float incidentrate,casefatalityratio,testingrate;
};

int main(int argc, char const *argv[]){

	const string file = "./DATA/12-31-2021.csv";
	
	ofstream out;
	out.open ("12-31-2021.bin", std::ofstream::binary);
	
	ifstream csv(file);


	string Line;
	Line.reserve(1024);
	if (!csv.is_open())
		throw "csv broke Line 82";
	getline(csv, Line);
// Province_State,Country_Region,Last_Update,Lat,Long_,Confirmed,Deaths,Recovered,Active,FIPS,Incident_Rate,Total_Test_Results,People_Hospitalized,Case_Fatality_Ratio,UID,ISO3,testingrate,hospitalizationrate
string test = "Alabama,US,2022-01-01 04:32:44,32.3182,-86.9023,896614,16455,aaa,bbb,1.0,18286.358764762088,6536745.0,,1.8352379061669792,84000001.0,USA,133316.30358634234,";

char statename[64];
char countrycode[64];
char date[64];
char ISO[64];
char recovered[64];
char active[64];
float lat,lon,FIPS;
u32 confirmed,deaths,peoplehospitalized,hospitalizationrate;
double incidentrate,totaltestresults,casefatalityratio,UID,testingrate;

char line[2048];
char state[64];

regex r ("[^,]*,[^,]*,[^,]*,[^,]*,[^,]*,([^,]*),([^,]*),([^,]*)");
cmatch m;

// smatch m;

	while (csv.getline(line,sizeof(line))){
		if (regex_search(line,m,r)){
			memcpy(state,line+m.position(1),m.length(1));
			state[m.length(1)]='\0';
			cout << m[1] << endl;
			cout << m[2] << endl;
			cout << m[3] << endl;
			// string state = m[1];
		}

		// covidreport r={confirmed,deaths,u32(totaltestresults),float(incidentrate),float(casefatalityratio),float(testingrate)};

		// out.write(reinterpret_cast<const char *>(&r), sizeof(r));

	}

	// i32 i32 i32 double i32 double i32 double
	
	out.close();

	return 0;
}

	#if 0
	while (getline(csv, Line)){
		DeleteMulti(Line, 5);
		iCutMulti(Line, out, 2);
		DeleteMulti(Line, 2);
		iCutStart(Line, out);
		dCutStart(Line, out);
		iCutStart(Line, out);
		DeleteStart(Line);
		dCutStart(Line, out);
		iCutStart(Line, out);
		DeleteStart(Line);
		dCutStart(Line, out);
	#endif