/**
 * verify.cpp
 * @author kisslune 
 */

#include "Z3Mgr.h"

using namespace z3;
using namespace SVF;


/* A simple example

int main() {
    int* p;
    int q;
    int* r;
    int x;

    p = malloc();
    q = 5;
    *p = q;
    x = *p;
    assert(x==5);
}
*/
void Z3Tests::test0()
{
    //  int* p;
    expr p = getZ3Expr("p");
    //  int q;
    expr q = getZ3Expr("q");
    //  int* r;
    expr r = getZ3Expr("r");
    //  int x;
    expr x = getZ3Expr("x");
    //  p = malloc();
    addToSolver(p == getMemObjAddress("malloc"));
    //  q = 5;
    addToSolver(q == 5);
    //  *p = q;
    storeValue(p, q);
    //  x = *p;
    addToSolver(x == loadValue(p));

    // print the expression values
    printExprValues();

    addToSolver(x == getZ3Expr(10));
    // print the result of satisfiability check
    std::cout << solver.check() << std::endl;
}


/*
// Simple integers

    int main() {
        int a;
        int b;
        a = 0;
        b = a + 1;
        assert(b > 0);
    }
*/
// void Z3Tests::test1()
// {
//     /// TODO: your code starts from here
    

// }
void Z3Tests::test1()
{
    // int a;
    expr a = getZ3Expr("a");
    // int b;
    expr b = getZ3Expr("b");
    
    // a = 0;
    addToSolver(a == getZ3Expr(0));
    
    // b = a + 1;
    addToSolver(b == a + 1);
    
    // assert(b > 0);
    addToSolver(b > getZ3Expr(0));
    
    printExprValues();
    std::cout << solver.check() << std::endl;
}
/*
  // One-level pointers

    int main() {
        int* p;
        int q;
        int b;
        p = malloc;
        *p = 0;
        q = *p;
        *p = 3;
        b = *p + 1;
        assert(b > 3);
    }
*/
// void Z3Tests::test2()
// {
//     /// TODO: your code starts from here

// }
void Z3Tests::test2()
{
    // int* p;
    expr p = getZ3Expr("p");
    // int q;
    expr q = getZ3Expr("q");
    // int b;
    expr b = getZ3Expr("b");
    
    // p = malloc;
    addToSolver(p == getMemObjAddress("malloc"));
    
    // *p = 0;
    storeValue(p, getZ3Expr(0));
    
    // q = *p;
    addToSolver(q == loadValue(p));
    
    // *p = 3;
    storeValue(p, getZ3Expr(3));
    
    // b = *p + 1;
    addToSolver(b == loadValue(p) + 1);
    
    // assert(b > 3);
    addToSolver(b > getZ3Expr(3));
    
    printExprValues();
    std::cout << solver.check() << std::endl;
}

/*
    // Mutiple-level pointers

    int main() {
        int** p;
        int* q;
        int* r;
        int x;

        p = malloc1(..);
        q = malloc2(..);
        *p = q;
        *q = 10;
        r = *p;
        x = *r;
        assert(x==10);
    }
*/
// void Z3Tests::test3()
// {
//     /// TODO: your code starts from here

// }
void Z3Tests::test3()
{
    // int** p;
    expr p = getZ3Expr("p");
    // int* q;
    expr q = getZ3Expr("q");
    // int* r;
    expr r = getZ3Expr("r");
    // int x;
    expr x = getZ3Expr("x");
    
    // p = malloc1;
    addToSolver(p == getMemObjAddress("malloc1"));
    
    // q = malloc2;
    addToSolver(q == getMemObjAddress("malloc2"));
    
    // *p = q;  (p指向的位置存储q)
    storeValue(p, q);
    
    // *q = 10;
    storeValue(q, getZ3Expr(10));
    
    // r = *p;  (从p指向的位置读取，得到q)
    addToSolver(r == loadValue(p));
    
    // x = *r;  (从r指向的位置读取)
    addToSolver(x == loadValue(r));
    
    // assert(x==10);
    addToSolver(x == getZ3Expr(10));
    
    printExprValues();
    std::cout << solver.check() << std::endl;
}
/*
   // Array and pointers

    int main() {
        int* p;
        int* x;
        int* y;
        int a;
        int b;
        p = malloc;
        x = &p[0];
        y = &p[1]
        *x = 10;
        *y = 11;
        a = *x;
        b = *y;
        assert((a + b)>20);
    }
*/
// void Z3Tests::test4()
// {
//     /// TODO: your code starts from here

// }
void Z3Tests::test4()
{
    // int* p;
    expr p = getZ3Expr("p");
    // int* x;
    expr x = getZ3Expr("x");
    // int* y;
    expr y = getZ3Expr("y");
    // int a;
    expr a = getZ3Expr("a");
    // int b;
    expr b = getZ3Expr("b");
    
    // p = malloc;
    addToSolver(p == getMemObjAddress("malloc"));
    
    // x = &p[0];  (p的第0个元素的地址)
    addToSolver(x == getGepObjAddress(p, 0));
    
    // y = &p[1];  (p的第1个元素的地址)
    addToSolver(y == getGepObjAddress(p, 1));
    
    // *x = 10;
    storeValue(x, getZ3Expr(10));
    
    // *y = 11;
    storeValue(y, getZ3Expr(11));
    
    // a = *x;
    addToSolver(a == loadValue(x));
    
    // b = *y;
    addToSolver(b == loadValue(y));
    
    // assert((a + b)>20);
    addToSolver((a + b) > getZ3Expr(20));
    
    printExprValues();
    std::cout << solver.check() << std::endl;
}

/*
    // Branches

int main(int argv) {
    int a;
    int b;
    int b1;
    a = argv + 1;
    b = 5;
    if(a > 10)
        b = a;
    b1 = b;
    assert(b1 >= 5);
}
*/
// void Z3Tests::test5()
// {
//     /// TODO: your code starts from here

// }
void Z3Tests::test5()
{
    // int a, b, b1;
    expr a = getZ3Expr("a");
    expr b = getZ3Expr("b");
    expr b1 = getZ3Expr("b1");
    expr argv = getZ3Expr("argv");
    
    // a = argv + 1;
    addToSolver(a == argv + 1);
    
    // b = 5;
    // if(a > 10) b = a;
    // 使用ite(条件, then值, else值)
    addToSolver(b == ite(a > getZ3Expr(10), a, getZ3Expr(5)));
    
    // b1 = b;
    addToSolver(b1 == b);
    
    // assert(b1 >= 5);
    addToSolver(b1 >= getZ3Expr(5));
    
    printExprValues();
    std::cout << solver.check() << std::endl;
}

/*
// Compare and pointers
int main() {
   int *a = malloc1;
   int *b = malloc2;
   *a = 5;
   *b = 10;
   int *p;
   if (*a < *b) {
       p = a;
   } else {
       p = b;
   }
   assert(*p == 5);
}
*/
// void Z3Tests::test6()
// {
//     /// TODO: your code starts from here

// }
void Z3Tests::test6()
{
    // int *a, *b, *p;
    expr a = getZ3Expr("a");
    expr b = getZ3Expr("b");
    expr p = getZ3Expr("p");
    
    // a = malloc1;
    addToSolver(a == getMemObjAddress("malloc1"));
    
    // b = malloc2;
    addToSolver(b == getMemObjAddress("malloc2"));
    
    // *a = 5;
    storeValue(a, getZ3Expr(5));
    
    // *b = 10;
    storeValue(b, getZ3Expr(10));
    
    // if (*a < *b) { p = a; } else { p = b; }
    addToSolver(p == ite(loadValue(a) < loadValue(b), a, b));
    
    // assert(*p == 5);
    addToSolver(loadValue(p) == getZ3Expr(5));
    
    printExprValues();
    std::cout << solver.check() << std::endl;
}
/*
 int main() {
	int a = 1, b = 2, c = 3;
	int d;
  if (a > 0) {
  	d = b + c;
  }
  else {
  	d = b - c;
  }
  assert(d == 5);
 }
 */
// void Z3Tests::test7()
// {
//     /// TODO: your code starts from here

// }
void Z3Tests::test7()
{
    // int a = 1, b = 2, c = 3;
    expr a = getZ3Expr("a");
    expr b = getZ3Expr("b");
    expr c = getZ3Expr("c");
    expr d = getZ3Expr("d");
    
    // a = 1;
    addToSolver(a == getZ3Expr(1));
    
    // b = 2;
    addToSolver(b == getZ3Expr(2));
    
    // c = 3;
    addToSolver(c == getZ3Expr(3));
    
    // if (a > 0) { d = b + c; } else { d = b - c; }
    addToSolver(d == ite(a > getZ3Expr(0), b + c, b - c));
    
    // assert(d == 5);
    addToSolver(d == getZ3Expr(5));
    
    printExprValues();
    std::cout << solver.check() << std::endl;
}

/*
 int main() {
    int arr[2] = {0, 1};
    int a = 10;
    int *p;
    if (a > 5) {
        p = &arr[0];
    }
    else {
        p = &arr[1];
    }
    assert(*p == 0);
 }
 */
// void Z3Tests::test8()
// {
//     /// TODO: your code starts from here

// }
void Z3Tests::test8()
{
    // int arr[2] = {0, 1};
    expr arr = getZ3Expr("arr");
    expr a = getZ3Expr("a");
    expr p = getZ3Expr("p");
    
    // arr是数组的基地址
    addToSolver(arr == getMemObjAddress("arr"));
    
    // arr[0] = 0;
    storeValue(getGepObjAddress(arr, 0), getZ3Expr(0));
    
    // arr[1] = 1;
    storeValue(getGepObjAddress(arr, 1), getZ3Expr(1));
    
    // a = 10;
    addToSolver(a == getZ3Expr(10));
    
    // if (a > 5) { p = &arr[0]; } else { p = &arr[1]; }
    addToSolver(p == ite(a > getZ3Expr(5), 
                         getGepObjAddress(arr, 0), 
                         getGepObjAddress(arr, 1)));
    
    // assert(*p == 0);
    addToSolver(loadValue(p) == getZ3Expr(0));
    
    printExprValues();
    std::cout << solver.check() << std::endl;
}

/*
    // Struct and pointers

    struct A{ int f0; int* f1;};
    int main() {
       struct A* p;
       int* x;
       int* q;
       int** r;
       int* y;
       int z;

       p = malloc1;
       x = malloc2;
       *x = 5;
       q = &(p->f0);
       *q = 10;
       r = &(p->f1);
       *r = x;
       y = *r;
       z = *q + *y;
       assert(z == 15);
    }
*/
// void Z3Tests::test9()
// {
//     /// TODO: your code starts from here

// }
void Z3Tests::test9()
{
    // struct A* p;
    expr p = getZ3Expr("p");
    // int* x;
    expr x = getZ3Expr("x");
    // int* q;
    expr q = getZ3Expr("q");
    // int** r;
    expr r = getZ3Expr("r");
    // int* y;
    expr y = getZ3Expr("y");
    // int z;
    expr z = getZ3Expr("z");
    
    // p = malloc1;
    addToSolver(p == getMemObjAddress("malloc1"));
    
    // x = malloc2;
    addToSolver(x == getMemObjAddress("malloc2"));
    
    // *x = 5;
    storeValue(x, getZ3Expr(5));
    
    // q = &(p->f0);  (p的第0个字段的地址)
    addToSolver(q == getGepObjAddress(p, 0));
    
    // *q = 10;
    storeValue(q, getZ3Expr(10));
    
    // r = &(p->f1);  (p的第1个字段的地址)
    addToSolver(r == getGepObjAddress(p, 1));
    
    // *r = x;
    storeValue(r, x);
    
    // y = *r;
    addToSolver(y == loadValue(r));
    
    // z = *q + *y;
    addToSolver(z == loadValue(q) + loadValue(y));
    
    // assert(z == 15);
    addToSolver(z == getZ3Expr(15));
    
    printExprValues();
    std::cout << solver.check() << std::endl;
}

/*
int foo(int z) {
    k = z;
    return k;
}
int main() {
  int x;
  int y;
  y = foo(2);
  x = foo(3);
  assert(x == 3 && y == 2);
}
*/
// void Z3Tests::test10()
// {
//     /// TODO: your code starts from here

// }

void Z3Tests::test10()
{
    expr x = getZ3Expr("x");
    expr y = getZ3Expr("y");
    
    // y = foo(2); 返回 2
    addToSolver(y == getZ3Expr(2));
    
    // x = foo(3); 返回 3
    addToSolver(x == getZ3Expr(3));
    
    // assert(x == 3 && y == 2);
    addToSolver(x == getZ3Expr(3));
    addToSolver(y == getZ3Expr(2));
    
    printExprValues();
    std::cout << solver.check() << std::endl;
}

int main()
{
    Z3Tests tests;
    tests.test0();
    tests.resetSolver();
    tests.test1();
    tests.resetSolver();
    tests.test2();
    tests.resetSolver();
    tests.test3();
    tests.resetSolver();
    tests.test4();
    tests.resetSolver();
    tests.test5();
    tests.resetSolver();
    tests.test6();
    tests.resetSolver();
    tests.test7();
    tests.resetSolver();
    tests.test8();
    tests.resetSolver();
    tests.test9();
    tests.resetSolver();
    tests.test10();

    return 0;
}