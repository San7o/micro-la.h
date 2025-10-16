// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#define MICRO_LA_IMPLEMENTATION
#include "micro-la.h"

int main(void)
{
#if __STDC_VERSION__ >= 201112L // >= C11
  Vec2i v = (Vec2i){ .a = 1, .b = 2};
#else
  Vec2i v = (Vec2i){ .x = 1, .y = 2};
#endif
  (void)v;
  
  return 0;
}
