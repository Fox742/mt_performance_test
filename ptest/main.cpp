#include <iostream>
#include <vector>
#include "SquareMatrix.h"
#include "Computer.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    /*
    SquareMatrix sm(11001);
    int k = 1;
    for (int i=0;i<sm.size();i++)
    {
        for (int j=0;j<sm.size();j++)
        {
            sm[i][j]=k;
            k++;
        }
    }
    cout << "Initsializated!" << endl;

    for (int i=0;i<sm.size();i++)
    {
        for (int j=0;j<sm.size();j++)
        {
            std::cout << "\t" << sm[i][j];
        }
        std::cout<<std::endl;
    }
    */

    SquareMatrix sm1(100);
    SquareMatrix sm2(100);

    Computer c;
    c.Multiply( sm1,sm2,4 );

    return 0;
}
