#include <iostream>
using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    // Constructor
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // Friend function to overload '<<'
    friend ostream& operator<<(ostream& os, const Complex c){
        os << c.real << " + " << c.imag << endl;
        return os;
    }
};


int main() {
    Complex c1(3.0, 4.0);
    Complex c2(1.5, -2.5);

    cout << "First Complex number: " << c1 << endl;
    cout << "Second Complex number: " << c2 << endl;

    return 0;
}
