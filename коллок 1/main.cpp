#include <iostream>
class  A {

public:

    virtual void   f () { cout << "отладчик"; }

    void  g () { cout << "редактор связей"; }

}



class  C: public A {

public:

    void   f () { cout << "система программирования"; }

    void g () { cout << "система автоматизированного тестирования"; }

}



int main() {

    C c;

    A *p=&c;

    p-> f();

}