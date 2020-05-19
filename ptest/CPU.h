#ifndef CPU_H
#define CPU_H
#include "SquareMatrix.h"
#include "memory"
#include "thread"

class CPU
{
private:
    int _total=0;
    int _processed=0;
    bool busy = false;
    std::shared_ptr<std::thread>multiplicator;

    void DoMultiplication(SquareMatrix & A, SquareMatrix & B, SquareMatrix & result, int &begin, int &end);

public:


    CPU()
    {

    }

    void launchMultiplication( SquareMatrix & A, SquareMatrix & B, SquareMatrix & result, int &begin, int& end);

    void Join();

    int getTotal()
    {
        return this->_total;
    }

    int getProcessed()
    {
        return  this->_processed;
    }

};

#endif // CPU_H
