#include <iostream>
#include "maptel.h"

int main() {
    auto id{jnp1::maptel_create()};
    char t1[] = "123456789";
    char t3[] = "";
//    jnp1::maptel_insert(id, t1, t3); // should fail on assert
    jnp1::maptel_transform(id, t1, NULL, 23); // should fail on assert


}

