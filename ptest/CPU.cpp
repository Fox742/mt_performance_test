#include "CPU.h"
#include "thread"
#include <memory>
#include "windows.h"

void CPU::launchMultiplication( SquareMatrix & A, SquareMatrix & B, SquareMatrix & result, int &begin, int &end)
{
    this->_total = A.size()*(end-begin+1);
    this->_processed = 0;


    // Запускаем в потоке лямбда-функцию, вызывающую функцию перемножения
    this->multiplicator = std::shared_ptr<std::thread>(
        new std::thread([this,&A,&B,&result,&begin,&end](){
           this->DoMultiplication(A,B,result,begin,end);
        })
    );

}


void CPU::DoMultiplication(SquareMatrix & A, SquareMatrix & B, SquareMatrix & result, int & begin, int & end)
{
    /*
    for (int i=0;i<10;i++)
    {
        std::cout<<"begin="<<begin<<" end="<<end<<std::endl;
        Sleep(1000);
    }
    */

    for (int i=begin;i<=end;i++)
    {
        for (int j=0;j<A.size();j++)
        {
            result[i][j] = 0;
            for (int k=0;k<A.size();k++)
            {
                result[i][j] += (A[i][k]*B[k][j]);
            }
            this->_processed++;
        }
    }

}

void CPU::Join()
{
    if (!this->multiplicator)
        return;
    this->multiplicator->join();
}
