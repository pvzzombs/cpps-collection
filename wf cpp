#include <iostream>
#include <fstream>

using namespace std;
int main(int argc, char *argv[]){
	ofstream a("hello.txt");
	if(a.is_open()){
		a << "Writing to file";
		a.close();
		cout << "Success" << endl;
	}else{
		cout << "Fail" << endl;
	}
	return 0;
}