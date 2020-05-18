#include "Computer.h"
#include "iostream"

SquareMatrix & Computer::Multiply( SquareMatrix & A, SquareMatrix & B, int CPUToWork)
{
    if (A.size()!=B.size())
    {
        throw "Size of matrixes are not equal. Please call Multiply() with one size matrixes";
    }
    SquareMatrix result(A.size());

    // Количество процессоров меньше либо равно нулю - бросаем исключение
    if (CPUToWork <=0)
    {
        throw "Number of acting CPU should not be less or egual 0";
    }

    // Проверим - если количество задействованных процессоров больше доступных, берём число доступных процессоров
    int _CPUToWork = CPUToWork;
    if (_CPUToWork > this->CPUs.size())
    {
        _CPUToWork = this->CPUs.size();
        std::cout<< "WARNING! Entered number of CPUs more, than accessible" << std::endl;
    }


    std::vector<std::pair<int,int>>limits = getLimitsForCPU(A.size(),CPUToWork);

    this->launchMultiplication(A,B,result,limits);

    return result;
}

std::vector<std::pair<int,int>>Computer::getLimitsForCPU(int matrixSize,int CPUToWork)
{
    std::vector<std::pair<int,int>>result;

    // Если количество задействованных ядер больше, чем строк в матрице - выкидываем иключение
    if ( matrixSize/CPUToWork < 1.0 )
    {
        throw "ERROR! Number of action CPU more than matrix size";
    }

    int rowsToOneCPU = (matrixSize/CPUToWork);

    if (matrixSize % CPUToWork >0)
        rowsToOneCPU++;

    int beginPointer = 0;
    while (beginPointer<matrixSize)
    {

        if (beginPointer+rowsToOneCPU<matrixSize)
        {
            result.push_back(std::pair<int,int>(beginPointer,beginPointer+rowsToOneCPU-1));
        }
        else
        {
            result.push_back(std::pair<int,int>(beginPointer,matrixSize-1));
        }
        beginPointer += rowsToOneCPU;
    }

    return result;
}

void Computer::launchMultiplication( SquareMatrix & A, SquareMatrix & B, SquareMatrix & result,  std::vector<std::pair<int,int>> pairs)
{
    for (int i=0;i<pairs.size();i++)
    {
        CPUs[i].launchMultiplication(A,B,result,pairs[i].first,pairs[i].second);
    }

    bool oneStillWorks;
    do
    {
        oneStillWorks = false;
        for (int i=0;i<pairs.size();i++)
        {
            if ( CPUs[i].getProcessed()<CPUs[i].getTotal() )
                oneStillWorks = true;
        }
    }
    while(oneStillWorks);

    // Вызываем всем CPU join
    for (int i=0;i<pairs.size();i++)
    {
        CPUs[i].Join();
    }
}
