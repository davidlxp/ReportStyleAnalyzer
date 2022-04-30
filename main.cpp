#include <iostream>
#include "AVL.cpp"

int main() {

    AVLtree<string> T;
    T.insert("hello");
    T.print();

    T.insert("ok");
    T.print();

    T.insert("opera");
    T.print();

    T.insert("why");
    T.print();

    T.insert("water");
    T.print();

    T.insert("water");
    T.print();

    T.insert("wait");
    T.print();

    T.insert("7");
    T.print();

    cout << T.searchItem("5") << endl;

    int count = 0;
    T.getCount("watedr",count);
    cout << "watedr: " << count << endl;



//    AVLtree<int> T;
//
//    T.insert(4);
//    T.print();
//
//    T.insert(6);
//    T.print();
//
//    T.insert(10);
//    T.print();
//
//    T.insert(12);
//    T.print();
//
//    T.insert(14);
//    T.print();
//
//    T.insert(11);
//    T.print();
//
//    T.insert(18);
//    T.print();
//
//    T.insert(30);
//    T.print();
//
//    T.insert(13);
//    T.print();
//
//    T.destroy();
//
//    T.insert(100);
//    T.print();
//
//    T.insert(80);
//    T.print();
//
//    T.insert(60);
//    T.print();
//
//    T.insert(40);
//    T.print();
//
//    T.insert(20);
//    T.print();
//
//    T.insert(50);
//    T.print();
//
//    T.insert(55);
//    T.print();
//
//    T.insert(130);
//    T.print();
//
//    T.Delete(60);
//    T.print();
//
//    T.Delete(50);
//    T.print();
//
//    T.Delete(20);
//    T.print();
//
//    T.Delete(40);
//    T.print();

    return 0;
}
