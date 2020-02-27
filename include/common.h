#pragma once

#include <cstdlib>
#include <iostream>

#define ASSERT(x) \
    do { \
        if( !(x) ) { \
            std::cout << "ASSERTION FAILED at " << __FILE__ << " : " << __LINE__ << std::endl; \
            abort(); \
        } \
    }while (false)

