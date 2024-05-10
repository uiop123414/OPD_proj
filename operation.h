#pragma once

#include "Formula.h"


template<EntityBaseType Type> class Operation
{
public:
    Operation(void);
    ~Operation(void);
};


bool Identity(const Formula & first, const Formula & second);
bool operator == (const Formula & first, const Formula & second );
