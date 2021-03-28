#include <iostream>

using namespace std;

static int global = 12;

void quuz(const int &a) { //=> can be invoked with both lvalue expressions and rvalue expressions
    cout << "quux()::Parameter = " << a << endl;
}

void waldo(int &b) { //=> can only be invoked with lvalue expressions
    cout << "waldo()::Parameter = " << b << endl;
}

int& garbly() {
    // DO STH
    return global;
}


int main() {
    int x = 10;
    quuz(x);
    quuz(20);

    waldo(x);
    //waldo(40); //=> initial value of reference to non-const must be an lvalue

    // const reference
    const int &cr = x; // => only for READING (accessor)
    int y = cr;
    //int z = ++cr; //=> expression must be modifiable lvalue
    //cr = 10; //=> expresion must be modifiable lvalue


    // Mutating global variable
    cout << "global = " << global << endl; //=> 12
    garbly() = 45; // lvalue reference is bound to ???
    cout << "global = " << global << endl; // => 45

}