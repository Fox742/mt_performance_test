#include "MatrixRandom.h"

bool MatrixRandom::inited = false;

int MatrixRandom::getNextRandom()
{
    unsigned int r;
    int low = 0;
    int high = 10;
    do
    {
      r = rand();
    } while (r < ((unsigned int)(RAND_MAX) + 1) % (high + 1 - low));
    return r % (high + 1 - low) + low;
}

