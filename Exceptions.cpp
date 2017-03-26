//
// Created by izeren on 3/26/17.
//
#include "Exceptions.h"


CException::CException( std::string _message ) : message( _message ) {
}

CException::~CException() {

}

std::string CException::GetMessage() const {
    return message;
}

___exception_info *___last_exception_info = 0;
___exception_info *___temp;
bool ___was_caught;
int ___ret_value;

___exception_info::~___exception_info() {}
