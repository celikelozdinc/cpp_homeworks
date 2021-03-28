#include <iostream>

using namespace std;

int main(){

    /*td_04.md => https://vimeo.com/362505509*/
    int __x = 5;
	decltype((__x)) __y{ __x }; //=> since (__x) is lvalue expression -> y is int&, y is bounded to x
	decltype(__y *= 2) __z = __x; //=> since (__y*=2) is lvalue expression -> z is int&, z is bounded to x
	decltype(__y--) _t_ = __x; //=> int t = 5
    int &rx{ __x }; //=> int&, rx is bounded to x
    auto ax{ rx }; // => reference drops: int ax = 5;

    ++__y; //=> x = 6
	__z *= 2; //=> x=12 
	_t_ *= 5; //=> t = 25
	ax += 10; //=> ax = 15
	std::cout << "__x = " << __x << "\n"; //=> 12
    
    /*td_06.md */
    const int _x_ = 20;
	auto _y_ = _x_; //=> const drops 
	++_y_;
	cout << _y_ << " " << _x_ << endl; //=> 21 20


    /*td_07.md => https://vimeo.com/433275373 */
    int t = 10;
    int *ptr = &t;
    auto r1 = t; //=> int
    auto r2 = *ptr; //=> int
    auto r3 = r2; //=> int
    auto &r4 = ptr; // r4(ptr) => stores address of x
    auto &r5 = *ptr; //=> r5(x) => stores x (10)

    r1 += 3; //=> r1 = 13
    r2 += 13; //=> r2 = 23 
    r3 += 20;  //=> r3 = 30
    *r4 += r2; //=> x = 33
    ++r5; // => x=34
    cout << "t = " << t << "\n";


    /* td_08.md => https://vimeo.com/433275373 */
    int xx = 10;
	const int &cr = xx; // const int &
    auto &ar = cr; //=> const does not drop. const int &ar = cr
    //++ar;


    /* td_09.md => https://vimeo.com/433275373*/
    int arr[] = { 0, 1, 2, 3, 4, 5 };
	auto ref1 = arr; //=> array decay -> int *ref1 = arr;
	auto &ref2 = arr; //=> int (&ref2)[6] ref2 is bound to arr
	++ref2[3];
	cout << (ref1[3] == ref2[3]) << "\n"; //=> 4 == 4



    /*td_10.md =>  https://vimeo.com/433275373 */
    int a[] = { 10, 20, 30, 40 };
    auto p = a; //=> array decay -> int *p = a ;
    auto &r = p; //=>  int * &r = p r is bound to p
    ++r;
	++p;
    std::cout << *r << "\n"; //=> 30
    


    /*td_13.md */
    auto _x = 0;
	decltype((_x)) _y = _x; //=> since (x_) is lvalue expression, type of y = int&
	_y++;
	cout << _x << _y << endl;  //=> 1 1


    /*td_14.md */
    int x_ = 0;
	decltype((x_)) y_ = x_; //=> since (x_) is lvalue expression, type of y = int&
	decltype(x_) z_ = x_; //=> type of z  = int
    ++x_; //=> y = 1
    y_ += 2; // => y=3
	z_ += 5; // => z=5
    cout << x_ << y_ << z_ <<endl;; //=> 3 3 5

}