#include <iostream>
#include <utility>

using namespace std;

class MyObj2
{
public:
    MyObj2()
    {
        cout << "Calling MyObj2 og constructor" << endl;
    }

    MyObj2(const MyObj2& obj)
    {
        cout << "Calling MyObj2 copy constructor" << endl;
    }

    MyObj2(MyObj2&& obj)
    {
        cout << "Calling MyObj2 move constructor" << endl;
    }
};

class MyObj
{
public:
    int a;
    MyObj2 b;
    MyObj(int x) : a(x)
    {
        cout << "Calling og constructor" << endl;
    }

    MyObj(const MyObj& obj) : a(obj.a)
    {
        cout << "Calling copy constructor" << endl;
    }

    MyObj(MyObj&& obj) : a(obj.a)
    {
        cout << "Calling move constructor" << endl;
    }

    MyObj2 getB()
    {
        MyObj2 bb;
        return bb;
    }
};

MyObj example1()
{
    MyObj a = MyObj(3);
    a.a = rand() % 100;
    return a;
}

MyObj example1_2()
{
    auto a = MyObj(3);
    return a;
}

MyObj example1_3()
{
    MyObj a = MyObj(3);
    return std::move(a);
}

MyObj example2()
{
    MyObj x1 = MyObj(3);
    MyObj x2 = MyObj(3);
    int a = rand() % 100;
    if (a > 5)
    {
        return x1;
    }
    return x2;
}

MyObj example4()
{
    MyObj x1 = MyObj(3);
    MyObj x2 = MyObj(3);
    int a = rand() % 100;
    return (a > 50 ? x1 : x2);
}

MyObj example4_1()
{
    MyObj x1 = MyObj(3);
    MyObj x2 = MyObj(3);
    int a = rand() % 100;
    (a > 50 ? x1 : x2);
    return x1;
}

MyObj example4_2()
{
    int a = rand() % 100;
    return (a > 50 ? MyObj(3) : MyObj(5));
}

MyObj example5()
{
    MyObj x1 = MyObj(3);
    int a = rand() % 100;
    if(a > 5)
    {
        x1.a = a;
        return x1;
    }
    else
    {
        x1.a = 7;
        return x1;
    }
}

MyObj example5_2()
{
    int a = rand() % 100;
    if(a > 5)
    {
        MyObj x1 = MyObj(3);
        return x1;
    }
    else
    {
        MyObj x1 = MyObj(3);
        return x1;
    }
}

MyObj example6()
{
    try
    {
        throw MyObj(3);
    }
    catch(const MyObj& e)
    {
        cout << "caught object\n";
        return e;
    }
    catch(...)
    {
        return MyObj(3);
    }
    
}

MyObj example7(MyObj a)
{
    return a;
}

MyObj2 example8()
{
    MyObj x1 = MyObj(3);
    return x1.b;
}

MyObj2 example8_1()
{
    MyObj x1 = MyObj(3);
    return x1.getB();
}

std::pair<MyObj, MyObj> return2MyObjPair()
{
    auto myPair = std::pair(MyObj(3), MyObj(3));
    return myPair;
}

MyObj example11()
{
    auto [a, b] = return2MyObjPair();
    cout << "After obj a asignment\n";
    return a;
}

int main()
{
    cout << "example1:\n";
    MyObj ex1 = example1(); // RVO
    cout << "ex1.a: " << ex1.a << endl;

    cout << "example1_2:\n";
    MyObj ex1_2 = example1_2(); // RVO
    cout << "ex1_2.a: " << ex1_2.a << endl;

    cout << "example1_3:\n";
    MyObj ex1_3 = example1_3(); // NO RVO
    cout << "ex1_3.a: " << ex1_3.a << endl;

    cout << "example2:\n";
    MyObj ex2 = example2(); // NO RVO
    cout << "ex2.a: " << ex2.a << endl;

    cout << "example4:\n";
    MyObj ex4 = example4(); // NO RVO
    cout << "ex4.a: " << ex4.a << endl;

    cout << "example4_1:\n";
    MyObj ex4_1 = example4_1(); // RVO
    cout << "ex4_1.a: " << ex4_1.a << endl;

    cout << "example4_2:\n";
    MyObj ex4_2 = example4_2(); // RVO
    cout << "ex4_2.a: " << ex4_2.a << endl;

    cout << "example5:\n";
    MyObj ex5 = example5(); // RVO
    cout << "ex5.a: " << ex5.a << endl;

    cout << "example5_2:\n";
    MyObj ex5_2 = example5_2(); // NO RVO
    cout << "ex5_2.a: " << ex5_2.a << endl;

    cout << "example6:\n";
    MyObj ex6 = example6(); // NO RVO
    cout << "ex6.a: " << ex6.a << endl;

    cout << "example7:\n";
    MyObj ex7 = example7(MyObj(3)); // NO RVO
    cout << "ex7.a: " << ex7.a << endl;

    cout << "example8:\n";
    MyObj2 ex8 = example8(); // NO RVO

    cout << "example8_1:\n";
    MyObj2 ex8_1 = example8_1(); // RVO

    cout << "example11:\n";
    MyObj ex11 = example11(); // NO RVO

    return 0;
}