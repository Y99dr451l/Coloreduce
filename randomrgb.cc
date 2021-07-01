#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;

int main() {
	srand(time(0));
	ofstream outfile;
	outfile.open("header.txt",ofstream::trunc);
	double n(0);
	cin >> n;
	int f(0);
	cin >> f;
	outfile << n << endl;
	for (int i(0); i<n; i++) {
		for (int j(0); j<3; j++) {
			outfile << rand()%256 << " ";
		}
	outfile << endl;
	}
	for (double i(1); i<n; i++) {
		outfile << i/n << " ";
	}
	outfile << endl << f << endl;
	outfile.close();
	return 0;
}
