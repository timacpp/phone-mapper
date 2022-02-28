#include <cassert>
#include <cstddef>
#include <cstring>
#include "../src/maptel.h"

namespace {
  unsigned long test() {
    unsigned long id;

    id = ::mapper::maptel_create();
    ::mapper::maptel_insert(id, "997", "112");

    return id;
  }

  unsigned long id = test();
} // anonymous namespace

int main() {
  char tel[::mapper::TEL_NUM_MAX_LEN + 1];

  ::mapper::maptel_transform(id, "997", tel, ::mapper::TEL_NUM_MAX_LEN + 1);
  assert(::std::strcmp(tel, "112") == 0);
  ::mapper::maptel_delete(id);
}
