#include <iostream>
#include "Exceptions.h"

class Dummy {
public:
    Dummy( std::string _name = "Dummy object" ) : name( _name ) { std::cout << "Created dummy\n"; };

    Dummy( const Dummy &other ) : name( other.name ) { std::cout << "Copy created Dummy\n"; }

    ~Dummy() { std::cout << name << " is deleted\n"; }

    std::string name;
};


class MyException1 : public CException {
public:
    MyException1( std::string _message = "default error 1" ) : CException( _message ) {};
};

class MyException2 : public CException {
public:
    MyException2( std::string _message = "default error 2" ) : CException( _message ) {};
};

class MyException3 : public MyException2 {
public:
    MyException3( std::string _message = "default error 3" ) : MyException2( _message ) {};
};


int DangerousMethod1() {
THROW( new MyException1( "Some error of type 1" )) ;
}

int DangerousMethod2() {
    TRY
        DangerousMethod1();
    CATCH( MyException1, e )
    THROW( new MyException1( e->GetMessage() + ": called from Dangerous2" ))
    ETRY
}


void C( Dummy d, int i ) {
    std::cout << "Entering Function C\n";
    d.name = " C";
THROW( new MyException1()) ;
std::cout << "Exiting Function C\n";
}

void B( Dummy d, int i ) {
    std::cout << "Entering Function B\n";
    d.name = "B";
    C( d, i + 1 );
    std::cout << "Exiting Function B\n";
}

void A( Dummy d, int i ) {
    std::cout << "Entering Function A\n";
    d.name = " A";
    //  Dummy* pd = new Dummy("new Dummy"); //Not exception safe!!!
    B( d, i + 1 );
    //   delete pd;
    std::cout << "Exiting Function A\n";
}

int main() {
//    TRY
//        THROW( new MyException3())
//    CATCH( MyException3, e )
//        std::cout << e->GetMessage() << "\n";
//    ETRY
//    TRY
//        DangerousMethod2();
//    CATCH( MyException1, e )
//        std::cout << e->GetMessage() << "\n";
//    CATCH( MyException2, e )
//        std::cout << e->GetMessage() << "\n";
//    ETRY
//
//    TRY
//        THROW( new MyException1( "---" ));
//    CATCH( MyException1, e )
//        std::cout << e->GetMessage() << "\n";
//    ETRY
    std::cout << "Entering main\n";
    TRY
        Dummy d( " M" );
        A( d, 1 );
    CATCH( MyException1, e )
        std::cout << "Caught an exception with message: " << e->GetMessage() << "\n";
    ETRY
    std::cout << "Exiting main.\n";
    return 0;
}