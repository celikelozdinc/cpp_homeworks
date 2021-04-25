#include <iostream>

class A {
public:
	A& f1();
	A* f2();
	const A& f3();
	void f4()const;
};


/*  const overloading example */
class _A {
public:
	void func()const
	{
		std::cout << "_A::func() const\n";
	}

	void func()
	{
		std::cout << "_A::func()\n";
		//burada sınıfın const üye işlevi olan func cagrilacak
        //const _A ca = (*this);
        //ca.func();
        //const_cast<const _A*>(this)->func();
        //((const _A *)this)->func();

	}
};


class Myclass {
public:
	void func(); //non-static member func
    static void foo();
	
};


/* function overloading example */
class B {
	void func(int); //1
public:
	void func(double); //2
	void func(double)const; //3
	void func(float) = delete; //4
};


class F {
	int mx = 10;
    static int my;
public:
	void func(F& rf)const;
};
F fg; //global instance


/* class_016.md =>  https://vimeo.com/435779773 */
void F::func(F& rf)const
{
	F local_f;
	fg.mx = 45; // can also access private members of global instances
	rf.mx = 55;
	local_f.mx = 65;
	//F::mx = 75; // can not access non-static members
    F::my = 75; // can access static members
}

/* class_013.md => https://vimeo.com/435763539 */
class Y {
	int mx = 0; // default initializer
	mutable int my = 10; // default initializer
public:
	void f(); // non-const member func
	void cf()const; // const member func

	Y* func() const //inline
	{
		// mx = 12; // const member func can not mutate non-const data member
		my = 23; // declared as mutable
		//f(); // const member func can not call non-const member func
		cf();
		// return this; // can not convert from const Y* to Y*
	}
};



/* class_11.md =>  https://vimeo.com/435749866 */
void func___(int);

class Z {
public:
	void func___() //declared as inline 
	{
		//func___(1); // Found in class scope
		//Z::func___(2); //Found in class scope
		func___(); // Recursive call
		::func___(3); // Operand of unary scope resolution operator -> Found in global scope
		//::func___();
	}
};



/* class_014.md => https://vimeo.com/435767306 */
class D {
public:
	void func(); //non-const member func
	void foo()
	{
		func(); //recursive
		foo();
		D::func(); // qualified name
		this->func();
		(*this).func();
		this->D::func();
	}
};


/* class_015.md => https://vimeo.com/435771459 */
class E {
	int x(int) 
    { 
        return 1; 
    }
public:
	void foo();
};

int x = 20; //global variable

void E::foo()
{
	if (auto x = ::x + 5; x  > 10) // if with initializer
		x = this->x(x); // 1 <- 25 
	
	// ++x; // function name can not be operand of operator++
	auto val = x(::x); //1
	E::x(::x);
}


/* class_017.md => https://vimeo.com/435790761 */
class G {
	void f(int); //1     -> function overloading
	void f(double); //2  -> function overloading

public:
	void f() //inline
	{
		f();  //recursive call
		f(12); //1
		f(1.2); //2
		f(2.3f); //2 (promotion)
		//f(4u); //ambiguity
	}
};

int main() {
    /* class_02.md =>  https://vimeo.com/368262675 */
    A ax;
	const A c;
    auto p{ &ax }; // p is *A
    ax.f2()->f1().f4();
    ax.f2()->f3().f4();
    //ax.f3().f1(); // By calling f1 after f3, can not convert from const A* to A* 
    p->f2()->f3().f4();
    c.f4(); // const member function can be called
    //c.f3(); // can not convert from const A* to A*
    //c.f3().f4(); // can not convert from const A* to A*
    ax.f4();
    c.f4();

    /* class_03.md => https://vimeo.com/368235967 */
    _A _ax;
	_ax.func();


    /* class_06.md =>  https://vimeo.com/368266774 */
    Myclass m;
    //func(); //=> Name lookup on block scope, no result. Name lookup on global scope, no result.
    m.func(); //VALID
    //Myclass::func(&m);
    //Myclass::func(m);
    m.Myclass::func(); // Scope resolution has higher priority than . operator, by using SRO, function is found and can be called with instance
	// Myclass::func(); //=> Name lookup can succesfully found func but can not be called without instance, since func is non-static member func
    Myclass::foo();
    //&m->func(); //must be pointer type
    (&m)->func(); 

    /* class_012.md => https://vimeo.com/435753617 */
    B bx;
    bx.func(2.3); //=> Exact match : 2 and 3.
    //bx.func(10); //=> Exact match : 1, but can not access private member
    //bx.func(1.2f); //=> Exact match : 4. Deleted function can not be called



}