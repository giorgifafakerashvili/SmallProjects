#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/export.h"

#include "include/slice.h"


void SliceTestInitialization() {
    Slice slice;
    assert(slice.size() == 0);
}

void SliceTest() {
    const char* data = "giorgi";
    Slice slice(data);

    assert(memcmp(data, slice.data(), slice.size()) == 0);
}

int main() {

    SliceTestInitialization();
    SliceTest();


    return 0;
}