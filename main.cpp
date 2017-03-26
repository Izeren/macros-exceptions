#include <iostream>
#include "Exceptions.h"

class MyException1 : public CException {
public:
    MyException1( std::string _message ) : CException( _message ) {};
};

class MyException2 : public CException {
public:
    MyException2( std::string _message ) : CException( _message ) {};
};

int DangerousMethod1() {
    THROW( new MyException1( "Some error of type 1" ));
}

int DangerousMethod2() {
    TRY
        DangerousMethod1();
//    CATCH( MyException1, e )
//        THROW( new MyException1( e->GetMessage() + ": called from Dangerous2" ))
    ETRY
}

int main() {
    std::cout << "test\n";
    TRY
        DangerousMethod2();
    CATCH( MyException1, e )
        std::cout << e->GetMessage() << "\n";
    CATCH( MyException2, e )
        std::cout << e->GetMessage() << "\n";
    ETRY


    return 0;
}