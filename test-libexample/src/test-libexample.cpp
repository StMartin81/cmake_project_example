#include "example/example.h"
#include <iostream>

int main(int argc, char *argv[])
{
    Example obj;

    if (obj.add(3, 2) != 5)
    {
        std::cerr << "Wrong result" << std::endl;
        return -1;
    }

    return 0;
}
