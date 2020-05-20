#include "Tests.h"
#include <vector>
#include "SquareMatrix.h"
#include "Computer.h"
#include "PreciseTimer.h"
#include "windows.h"

using namespace std;

void Tests::test1()
{
    SquareMatrix sm1(4);

    sm1[0][0]=1;    sm1[0][1]=0;    sm1[0][2]=-1;   sm1[0][3]=1;
    sm1[1][0]=0;    sm1[1][1]=-2;   sm1[1][2]=0;    sm1[1][3]=1;
    sm1[2][0]=-1;   sm1[2][1]=0;    sm1[2][2]=0;    sm1[2][3]=-2;
    sm1[3][0]=2;    sm1[3][1]=1;    sm1[3][2]=1;    sm1[3][3]=0;


    SquareMatrix sm2(4);

    sm2[0][0]=2;     sm2[0][1]=1;    sm2[0][2]=2;   sm2[0][3]=0;
    sm2[1][0]=-1;    sm2[1][1]=0;    sm2[1][2]=1;   sm2[1][3]=-1;
    sm2[2][0]=1;     sm2[2][1]=0;    sm2[2][2]=-1;  sm2[2][3]=2;
    sm2[3][0]=0;     sm2[3][1]=-1;   sm2[3][2]=-2;   sm2[3][3]=1;

    std::cout << "SM1:"<<std::endl;
    std::cout << sm1.toString();
    std::cout<<std::endl;

    std::cout << "SM2:"<<std::endl;

    std::cout << sm2.toString();

    Computer c;
    SquareMatrix result = c.Multiply( sm1,sm2 );

    std::cout << "RESULT:"<<std::endl;
    std::cout << result.toString();

    SquareMatrix result2 = c.Multiply( sm1,sm2, 2 );

    std::cout << "RESULT2:"<<std::endl;
    std::cout << result2.toString();
}

void Tests::test2()
{
    SquareMatrix sm1(4);

    sm1[0][0]=1;    sm1[0][1]=0;    sm1[0][2]=-1;   sm1[0][3]=1;
    sm1[1][0]=0;    sm1[1][1]=-2;   sm1[1][2]=0;    sm1[1][3]=1;
    sm1[2][0]=-1;   sm1[2][1]=0;    sm1[2][2]=0;    sm1[2][3]=-2;
    sm1[3][0]=2;    sm1[3][1]=1;    sm1[3][2]=1;    sm1[3][3]=0;

    SquareMatrix sm2(4);

    sm2[0][0]=1;    sm2[0][1]=0;    sm2[0][2]=-1;   sm2[0][3]=1;
    sm2[1][0]=0;    sm2[1][1]=-2;   sm2[1][2]=0;    sm2[1][3]=1;
    sm2[2][0]=-1;   sm2[2][1]=0;    sm2[2][2]=0;    sm2[2][3]=-2;
    sm2[3][0]=2;    sm2[3][1]=1;    sm2[3][2]=1;    sm2[3][3]=0;

    SquareMatrix sm3(3);

    sm3[0][0]=1;    sm3[0][1]=0;    sm3[0][2]=-1;
    sm3[1][0]=0;    sm3[1][1]=-2;   sm3[1][2]=0;
    sm3[2][0]=-1;   sm3[2][1]=0;    sm3[2][2]=0;

    SquareMatrix sm4(4);

    sm4[0][0]=1000000;    sm4[0][1]=0;    sm4[0][2]=-1;   sm4[0][3]=1;
    sm4[1][0]=0;    sm4[1][1]=-2;   sm4[1][2]=0;    sm4[1][3]=1;
    sm4[2][0]=-1;   sm4[2][1]=0;    sm4[2][2]=0;    sm4[2][3]=-2;
    sm4[3][0]=2;    sm4[3][1]=1;    sm4[3][2]=1;    sm4[3][3]=0;

    std::cout << "isEqual SM1 and SM2: << " << (sm1 == sm2) <<std::endl;
    std::cout << "isEqual SM1 and SM3: << " << (sm1 == sm3) <<std::endl;
    std::cout << "isEqual SM1 and SM4: << " << (sm1 == sm4) <<std::endl;
    std::cout << "isEqual SM2 and SM4: << " << (sm2 == sm4) <<std::endl;
}

void Tests::test3()
{
    SquareMatrix sm1(8);


    sm1[0][0]=1;    sm1[0][1]=0;    sm1[0][2]=-1;   sm1[0][3]=1;    sm1[0][4]=1;    sm1[0][5]=0;    sm1[0][6]=-1;   sm1[0][7]=1;
    sm1[1][0]=0;    sm1[1][1]=-2;   sm1[1][2]=0;    sm1[1][3]=1;    sm1[1][4]=0;    sm1[1][5]=-2;   sm1[1][6]=0;    sm1[1][7]=1;
    sm1[2][0]=-1;   sm1[2][1]=0;    sm1[2][2]=0;    sm1[2][3]=-2;   sm1[2][4]=-1;   sm1[2][5]=0;    sm1[2][6]=0;    sm1[2][7]=-2;
    sm1[3][0]=2;    sm1[3][1]=1;    sm1[3][2]=1;    sm1[3][3]=0;    sm1[3][4]=2;    sm1[3][5]=1;    sm1[3][6]=1;    sm1[3][7]=0;
    sm1[4][0]=1;    sm1[4][1]=2;    sm1[4][2]=2;    sm1[4][3]=2;    sm1[4][4]=1;    sm1[4][5]=0;    sm1[4][6]=-1;   sm1[4][7]=1;
    sm1[5][0]=2;    sm1[5][1]=0;    sm1[5][2]=-1;   sm1[5][3]=-2;   sm1[5][4]=0;    sm1[5][5]=-2;   sm1[5][6]=0;    sm1[5][7]=1;
    sm1[6][0]=0;    sm1[6][1]=1;    sm1[6][2]=-2;   sm1[6][3]=0;    sm1[6][4]=-1;   sm1[6][5]=0;    sm1[6][6]=0;    sm1[6][7]=-2;
    sm1[7][0]=-1;   sm1[7][1]=0;    sm1[7][2]=0;    sm1[7][3]=-1;   sm1[7][4]=2;    sm1[7][5]=1;    sm1[7][6]=1;    sm1[7][7]=0;

    SquareMatrix sm2(8);

    sm2[0][0]=-2;    sm2[0][1]=1;    sm2[0][2]=0;   sm2[0][3]=-1;  sm2[0][4]=2;   sm2[0][5]=0;   sm2[0][6]=1;   sm2[0][7]=2;
    sm2[1][0]=-1;    sm2[1][1]=2;    sm2[1][2]=-1;  sm2[1][3]=0;   sm2[1][4]=1;   sm2[1][5]=1;   sm2[1][6]=0;   sm2[1][7]=-1;
    sm2[2][0]=0;     sm2[2][1]=1;    sm2[2][2]=-2;  sm2[2][3]=1;   sm2[2][4]=0;   sm2[2][5]=-1;  sm2[2][6]=0;   sm2[2][7]=-2;
    sm2[3][0]=1;     sm2[3][1]=0;    sm2[3][2]=2;   sm2[3][3]=2;   sm2[3][4]=-1;  sm2[3][5]=-2;  sm2[3][6]=-1;  sm2[3][7]=0;
    sm2[4][0]=2;     sm2[4][1]=-1;   sm2[4][2]=1;   sm2[4][3]=1;   sm2[4][4]=-2;  sm2[4][5]=1;   sm2[4][6]=2;   sm2[4][7]=-2;
    sm2[5][0]=-2;    sm2[5][1]=-2;   sm2[5][2]=0;   sm2[5][3]=0;   sm2[5][4]=-1;  sm2[5][5]=2;   sm2[5][6]=1;   sm2[5][7]=0;
    sm2[6][0]=-1;    sm2[6][1]=2;    sm2[6][2]=-1;  sm2[6][3]=-1;  sm2[6][4]=0;   sm2[6][5]=-2;  sm2[6][6]=1;   sm2[6][7]=-1;
    sm2[7][0]=0;     sm2[7][1]=1;    sm2[7][2]=-2;  sm2[7][3]=-2;  sm2[7][4]=1;   sm2[7][5]=1;   sm2[7][6]=-2;  sm2[7][7]=0;


    std::cout << "SM1:"<<std::endl;
    std::cout<<sm1.toString();
    std::cout<<std::endl;

    std::cout << "SM2:"<<std::endl;
    std::cout << sm2.toString();

    Computer c;
    SquareMatrix result = c.Multiply( sm1,sm2 );

    std::cout << "RESULT:"<<std::endl;
    std::cout << result.toString();

    SquareMatrix result2 = c.Multiply( sm1,sm2, 3 );

    std::cout << "RESULT2:"<<std::endl;
    std::cout << result2.toString();
}

void Tests::test4()
{
    SquareMatrix sm1 = SquareMatrix(20,true);
    SquareMatrix sm2 = SquareMatrix(20,true);
    SquareMatrix sm3 = SquareMatrix(20,true);
    Computer c;
    SquareMatrix result1 = c.Multiply( sm1,sm2, 1);
    SquareMatrix result2 = c.Multiply( sm1,sm2, 3);
    SquareMatrix result3 = c.Multiply( sm1,sm3, 1);

    cout << "IsEqual: RESULT1 and RESULT2: "<<(result1==result2)<<std::endl;
    cout << "IsEqual: RESULT1 and RESULT3: "<<(result1==result3)<<std::endl;

}

void Tests::test5()
{
    Computer c(true);
    SquareMatrix sm1 = SquareMatrix(2000,true);
    SquareMatrix sm2 = SquareMatrix(2000,true);
    SquareMatrix result1 = c.Multiply( sm1,sm2, 12);
    cout << "Multiplied!"<<std::endl;

}

void Tests::test6()
{
    PreciseTimer pt;
    pt.startMeasure();
    std::cout << "sleeping 10 seconds..."<<std::endl;
    Sleep(10000);
    cout<<pt.stopMeasure()<<std::endl;
    std::cout << "sleeping 5 seconds..."<<std::endl;
    Sleep(5000);
    pt.startMeasure();
    std::cout << "sleeping 15 seconds..."<<std::endl;
    Sleep(15000);
    cout<<pt.stopMeasure()<<std::endl;
}
