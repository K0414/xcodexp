/*
 * Copyright (C) lfc
 */

#include "func.h"
#include "adder.h"

int
func(int a, int b)
{
    CAdder  A(a, b);

    return A.add();
}
