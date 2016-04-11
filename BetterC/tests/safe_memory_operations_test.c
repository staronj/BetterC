/**
 * Copyright Jakub Staroń 2016
 */

#include <assert.h>
#include "safe_memory_operations.h"


void macro_new_test() {
  {
    int* foo = new(int, 42);
    assert(*foo == 42);
    free(foo);
  }

  {
    char* c = new(char, 'L');
    assert(*c == 'L');
    free(c);
  }

  {
    int* foo = new(int[5], 0, 1, 2, 3, 4);
    assert(foo[0] == 0);
    assert(foo[1] == 1);
    assert(foo[2] == 2);
    assert(foo[3] == 3);
    assert(foo[4] == 4);
    free(foo);
  }

  {
    int* foo = new(int[1000], 1);
    assert(foo[0] == 1);
    for (int i = 1 ; i < 1000 ; i++) {
      assert(foo[i] == 0);
    }
    free(foo);
  }

  {
    int* foo = new(int[1000]);
    for (int i = 0 ; i < 1000 ; i++) {
      assert(foo[i] == 0);
    }
    free(foo);
  }

  {
    struct foo_type {
      int a;
      char b;
      double c;
    };

    struct foo_type* foo = new(struct foo_type, 1, 'd', 3.14);
    assert(foo->a == 1);
    assert(foo->b == 'd');
    assert(foo->c == 3.14);
    free(foo);

    foo = new(struct foo_type, .c=1.23, .a=42, .b='G');
    assert(foo->a == 42);
    assert(foo->b == 'G');
    assert(foo->c == 1.23);
    free(foo);
  }

  {
    struct foo_type {
      int a, b, c;
    };

    struct foo_type* foo = new(struct foo_type);
    assert(foo->a == 0);
    assert(foo->b == 0);
    assert(foo->c == 0);
    free(foo);
  }
}

int main() {
  macro_new_test();
}

