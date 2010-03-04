/*
 * Copyright (C) lfc
 */

#include "adder.h"


CAdder::CAdder(int a, int b) : m_a(a), m_b(b)
{}

int
CAdder::add()
{
    return m_a + m_b;
}
