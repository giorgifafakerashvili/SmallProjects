#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/export.h"

#include "include/slice.h"
#include "include/status.h"


int main() {

    Status status;

    Status result = status.Corruption("first msg", "second msg");


    printf(result.ToString().data());

    return 0;
}