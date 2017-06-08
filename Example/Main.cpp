#include "PlyContentOutputer.h"

int main(int argc, const char *argv[])
{
    PlyContentOutputer plyContentOutputer;

    return plyContentOutputer.Output(argv[1]) ? 0 : 1;
}
