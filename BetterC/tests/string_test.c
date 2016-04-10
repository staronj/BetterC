/**
 * Copyright Jakub Staroń 2016
 */

#include <string.h>
#include <assert.h>
#include "better_string.h"


int main() {
  {
    const char* text = "Hello World!";
    const char* text2 = "World Hello!";
    String_pointer a = String_fromCString(text);
    String_pointer b = String_fromData(text, strlen(text));
    String_pointer c = String_fromData(text, strlen(text) - 1);
    String_pointer d = String_clone(a);
    String_pointer e = String_fromCString(text2);

    assert(String_compare(a, b) == 0);
    assert(String_compare(a, c) == 1);
    assert(String_compare(a, d) == 0);
    assert(String_compare(a, e) == -1);
    assert(!String_isEmpty(a));
    assert(String_size(a) == 12);
    assert(memcmp(String_data(a), text, strlen(text)) == 0);
    assert(String_at(a, 6) == 'W');

    {
      String_pointer substr = String_substr(a, 6, 5);
      assert(String_compareCstr(substr, "World") == 0);
      assert(String_size(substr) == 5);


      String_pointer substr2 = String_substr(a, 0, 5);
      assert(String_compareCstr(substr2, "Hello") == 0);

      String_pointer joined = String_join(substr, substr2);
      assert(String_size(joined) == 10);
      assert(String_compareCstr(joined, "WorldHello") == 0);
      assert(strcmp(String_toCstring(joined), "WorldHello") == 0);

      String_destroy(substr);
      String_destroy(substr2);
      String_destroy(joined);
    }

    {
      String_pointer empty_substr = String_substr(a, 0, 0);
      assert(String_isEmpty(empty_substr));
    }

    {
      String_pointer empty_substr = String_substr(a, 12, 100);
      assert(String_isEmpty(empty_substr));
    }


    String_destroy(a);
    String_destroy(b);
    String_destroy(c);
    String_destroy(d);
  }

}
