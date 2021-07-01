#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    stringstream ss;
    ss << argv[1];
    double nb(0);
    ss >> nb;
    double step1(255./nb);
    double counter1(step1);
    for (double i(0); i < nb; i++) {
        for (int j(0); j < 3; j++) {
            cout << round(counter1) << " ";
        }
        counter1+=step1;
    }
    cout << endl;
    double step2(1./nb);
    double counter2(step2);
    for (double i(0); i < nb; i++) {
        if (i != 1) {
            cout << counter2 << " ";
            counter2+=step2;
        }
    }
    cout << endl;
    return 0;
}