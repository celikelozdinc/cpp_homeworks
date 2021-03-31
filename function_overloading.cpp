#include <iostream>
using namespace std;

void foo(void *);  //1
void foo(bool); //2


/* const overloading */
void bar(char *p);  //1
void bar(const char *p); //2

enum Color {Blue, Green, Red};
void qux(Color); // 1
void qux(unsigned int); //2


void fuga(int &); //1 => accepts lvalue reference
void fuga(int &&); //2 => accepts rvalue reference
void fuga(const int &); //3
int _fuga1();
int& _fuga2();
const int& _fuga3();

void garply(int){cout << "int";}
void garply(float){cout << "float";}

void wobble(int){cout << "int";}
void wobble(double){cout << "double";}

void tata(int);  	//1
void tata(double); 	//2
void tata(long);  	//3
void tata(bool); 	//4


void display(char const *ptr){cout << ptr;} //1
void display(unsigned int uval){cout << uval;} //2



int main() {
    /* fo_01.md => https://vimeo.com/433280009 */
    int x__ = 10;

	tata('A'); //=> 2 (Integral promotion)
	tata(2.3F); //=> 2 (Promotion)
	//tata(4u) //=> Ambiguity. Conversion will be applied on each of 4 functions
	tata(10 > 5); //=> 4 (Exact match)
	tata(&x__); //=> Conversion exist from int* to bool
	//tata(nullptr);


    /* fo_02.md => https://vimeo.com/433281751 */
    double x = 1.0;
    //foo(0); //=> Conversion vs Conversion -> Ambiguity
    foo(nullptr); // 1 -> 2nd function is not viable -> there is no conversion from nullptr_t to bool
    foo(&x);
    foo(x);//2 -> 1st function is not viable -> there is no conversion from double to void*

    /* fo_03.md =>  https://vimeo.com/433282922 */
    char str[] = "Herb Sutter"; 
    char *const p1 = str; // const pointer. Pointer itself declared as const which pointing to char* 
    const char *p2 = str; // pointer to const
    const char cstr[] = "Stephan Lavavej";
    //bar(nullptr); //=> Conversion vs Conversion -> Ambiguity
    bar("Bjarne Stroustrup"); //2 -> exact match (array decay). 1 is not viable
    bar(str); // 1 -> exact match (array decay), 2 is also viable --> EXCEPTIONAL CASE
    bar(cstr); // 2 -> exact match (array decay). 1 is not viable
    bar(p1); // 1 --> EXCEPTIONAL CASE
    bar(p2); // 2-> exact match. 1 is not viable

    /* fo_04.md => https://vimeo.com/433284105 */
    qux(12); //2 => 1 is not viable, no automatic conversion from int to enum

    /* fo_05.md => https://vimeo.com/433286327 */
    int _x = 10;
	const int _cx = 20;

    fuga(_x); //=> 1. x : lvalue expression => 2 is not viable.
    fuga(_cx); //3
    fuga(_x + 5); //2. => x+5: rvalue expression => 1 is not viable.
    fuga(_fuga1()); //=> return type : pr value expression => 1 is not viable. Chooses 2
    fuga(_fuga2()); //=> return type : lvalue expression => 2 is not viable. Chooses 1
    fuga(_fuga3()); //=> return type : lvalue expression => 2 is not viable. Chooses 3


    /* fo_07.md => https://vimeo.com/433292846 */
    display("abc"); //2 is not viable
	//display(0); //=> Conversion vs Conversion. Ambiguity
    display(0u); //=> 2 -> Exact match
	display('A'); //=> 1 is not viable




    /* fo_09.md =>  https://vimeo.com/433296005*/
    //garply(2.5); //=> sends double. Ambiguity :
    //double -> int : not exact match, not  promotion. Conversion
    //double -> float: not exact match, not  promotion. Conversion

    /* fo_10.md => https://vimeo.com/433296786 */
    wobble(2.F); // => sends float
    // float -> int : not exact match, not  promotion. Conversion
    // float -> double: not an exact match. Promotion. Chooses this one

}