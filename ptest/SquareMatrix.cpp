#include "SquareMatrix.h"
#include "MatrixRandom.h"

int SquareMatrix::maxSize=11000;


SquareMatrix::SquareMatrix(int size, bool randomFill)
{
    int realSize = size;

    if (realSize > SquareMatrix::maxSize)
    {
        std::cout << "WARNING! Attempt to create matrix more than maximal size. Maximal size is: "<<maxSize<<"X"<<maxSize<<std::endl;
        realSize = SquareMatrix::maxSize;
    }

    for (int i=0;i<realSize;i++)
    {
        rows.push_back(Row(realSize));
    }

    if (randomFill)
    {
        for (unsigned int i = 0;i<realSize;i++)
        {
            for (unsigned int j = 0;j<realSize;j++)
            {
                rows[i][j] = MatrixRandom::getNextRandom();
            }
        }
    }

}


std::string SquareMatrix::toString()
{
    std::string result = "";

    for (unsigned int i=0;i<rows.size();i++)
    {
        for (unsigned int j=0;j<rows.size();j++)
        {
            result+= (std::string ("\t") + std::to_string(rows[i][j]));
        }
        result += std::string("\n");
    }

    return result;
}


bool operator== (SquareMatrix &sm1, SquareMatrix &sm2)
{

    if (sm1.size()!=sm2.size())
        return false;
    int sz = sm1.size();
    for (int i=0; i<sz; i++)
    {
        for (int j=0; j<sz; j++)
        {
            if (sm1[i][j]!=sm2[i][j])
                return false;
        }
    }

    return true;
}

bool operator!= (SquareMatrix &sm1, SquareMatrix &sm2)
{
    return !(sm1==sm2);
}
