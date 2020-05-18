#include "SquareMatrix.h"

int SquareMatrix::maxSize=11000;


SquareMatrix::SquareMatrix(int size)
{
    int realSize = size;

    if (realSize > SquareMatrix::maxSize)
    {
        std::cout << "WARNING! Attempt to create matrix more than maximal size. Maximal size is: "<<maxSize<<"X"<<maxSize<<std::endl;
    }

    for (int i=0;i<size;i++)
    {
        rows.push_back(Row(size));
    }
}
