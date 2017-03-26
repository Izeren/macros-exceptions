//
// Created by izeren on 3/26/17.
//
#pragma once

#include <csetjmp>
#include <string>
#include <iostream>
#include <cassert>
#include <memory>

class CException {
public:
    CException( std::string _message = "An error occured" );

    virtual ~CException();

    std::string GetMessage() const;

private:
    std::string message;
};

struct ___exception_info {
    jmp_buf buffer;
    std::shared_ptr<CException> exception;
    ___exception_info *previous;

    ~___exception_info();
};

extern ___exception_info *___last_exception_info;
extern ___exception_info *___temp;
extern bool ___was_caught;
extern int ___ret_value;

#define TRY \
___temp = new ___exception_info();\
___temp->previous = ___last_exception_info; \
___last_exception_info = ___temp;\
___ret_value = setjmp( ___last_exception_info->buffer );\
___was_caught = false; \
if ( !___ret_value ) {

#define CATCH( Type, ___exceptionName ) \
} \
if ( ___ret_value && ___last_exception_info && std::dynamic_pointer_cast<Type>( ___last_exception_info->exception )) {\
    std::shared_ptr<Type> ___exceptionName = std::dynamic_pointer_cast<Type>( ___last_exception_info->exception ); \
    ___temp = ___last_exception_info; \
    ___last_exception_info = ___last_exception_info->previous; \
    delete ___temp; \
    ___was_caught = true;

#define THROW( exceptionPtr ) \
if ( !___last_exception_info ) {\
    std::cout << "Uncaught exception\n"; \
    assert( false ); \
}\
___last_exception_info->exception = std::shared_ptr<CException>( exceptionPtr ); \
longjmp( ___last_exception_info->buffer, 1 );

#define ETRY } \
if ( !___was_caught ) {\
    ___temp = ___last_exception_info; \
    ___last_exception_info = ___last_exception_info->previous; \
    std::shared_ptr<CException> ___exception = ___temp->exception; \
    delete ___temp; \
    THROW( ___exception ) }
