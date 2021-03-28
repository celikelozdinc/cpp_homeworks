#include <iostream>

using namespace std;

int bar(); // => return value is not reference => rvalue expression
int &foo(); //=> return value is reference => lvalue expression
int &f1();
int f2();


int baz(int &xx, int &yy) //=> can only be invoked by lvalue expressions
{
    // both &xx and &yy references to xx in main function
	xx = 3;
	yy = 4;
	return xx + yy;
}


void qux(int& ra, const int& rb) //=> ra can be invoked with lvalue expression, rb can be invoked both lvalue and rvalue expressions
{
    cout << rb << endl;
	ra = 1;
	cout << rb << endl;
}

int main () 
{
    /* ref_01.md */
    int x = 10;
	int y = 35;
	const int primes[]{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
	int a[]{ 1, 2, 4 };
    //int &r1;  => Must be initialized
    int &r2(++x); //=> lvalue reference is bounded to lvalue expression
    //int &r3{ 10 }; => lvalue reference can not bound to rvalue expression
    const int &r4{ int() }; //=> lvalue reference is bounded to lvalue expression
    const int &r5{ int{} }; //=> lvalue reference is bounded to lvalue expression
    //int &r6 = +y; ??
    int &r7 = (x, y);
    int &r8 = x > 10 ? x : y; //=> lvalue reference is bounded to lvalue expression
    //int &r9 = f1(); //=> return value of f1 is reference
    //int &r10 = f2(); //=> return value of f2 is not reference
    //int &r11 = primes[5]; //=> reference must be const int
    int const &r12 = *primes; //=> top-level const : const pointer
    const int &r13{ x };
    //int(&r15)[] = a; //=> must be initialized with [3]
	int(&r16)[3] = a;

    /* ref_03.md => https://vimeo.com/433211545 */
    int xx = 1;
	int yy = 2;
	int zz = baz(xx, xx);
	cout << xx << yy << zz << endl; //=> 4 2 8

    /* ref_04.md => https://vimeo.com/433201294 */
    int iival = 1;
    const int &rr = iival > 0 ? iival : 1; 
    // =>  3rd operand is rvalue expression -> 
    //ternary operation becomes rvalue expression -> 
    //reference is bound to temporary object
    //int &rr = iival > 0 ? iival : 1; => initialize with rvalue expression
    iival = 5;
    cout << iival << rr << endl; //=> 5 1


    /* ref_05.md =>  https://vimeo.com/433209303*/
    int ival_ = 0;
	qux(ival_, ival_); // => 0 1

    /* ref_06.md => https://vimeo.com/433270915 */
    int _x{ 1 }, _y{ }; //=> 1 and 0
	const int &ref1 = _x > 0 ? _x : _y++; //=> 3rd operand is rvalue expression. 
    //ref1 is bounded to temporary object which has value of 1(value of x)
    //ref1 is not bounded to x
	const int &ref2 = _x > 0 ? _x : ++_y; //=> 3rd operand is lvalue expression
    //ref2 is bounded directly to x
	_x = 5;
    cout << ref1 <<  " " << ref2 << " " <<_x << " " << _y << endl; //=> 1 5 5 1

    /* ref_08.md */
    //auto a;  => Must be initialized. (İlk değer vermek zorunludur)
    //int &b; => Must be initialized
    auto c = 10;
    int &d = c;
    const auto &e = 20;
    int &f = ++c; // => lvalue reference is bounded to lvalue expression
    //int &f = c++; // => lvalue reference can not bounded to rvalue expression
    //int &g = c + 5; //=> lvalue reference can not bound to rvalue expression
    int &&h = c % 2; //=> rvalue reference is bounded to rvalue expression
    //int &&j = bar(); // => rvalue reference is bounded to rvalue expression
    //int &&m = foo(); // => rvalue reference can not bound to lvalue expression
    int ival = 10;
    int &&rval = ival + 10; //=> rvalue reference is bounded to rvalue expression
    int &p = rval;

}