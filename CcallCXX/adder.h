/*
 * Copyright (C) lfc
 */

#ifndef _ADDER_H_INCLUDED_
#define _ADDER_H_INCLUDED_

class CAdder {
  public:
    CAdder(int a, int b);
    int add();

  private:
    int m_a, m_b;
};

#endif /* _ADDER_H_INCLUDED_ */
