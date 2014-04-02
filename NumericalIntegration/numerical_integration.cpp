#include <iostream>
#include <string>

using namespace std;

string FUN = "";
string FILEPATH = "";

int main(int argc, char** argv){
	int i = 0;
	while (i < argc){
		if (!strcmp(argv[i], "-fun")) FUN = argv[++i];
		if (!strcmp(argv[i], "-f")) FILEPATH = argv[++i];
		i++;
	}
	cout << FILEPATH << endl;
	return 0;
}