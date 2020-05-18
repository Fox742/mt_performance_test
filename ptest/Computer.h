#ifndef COMPUTER_H
#define COMPUTER_H

#include "SquareMatrix.h"
#include <vector>
#include "CPU.h"
#include <thread>

class Computer
{
private:
    std::vector<CPU>CPUs;
    std::vector<std::pair<int,int>>getLimitsForCPU(int matrixSize,int CPUToWork);

    void launchMultiplication( SquareMatrix & A, SquareMatrix & B, SquareMatrix & result,  std::vector<std::pair<int,int>> pairs);

public:
    Computer()
    {
        // Определяем количество ядер процессора
        unsigned int CPUNumber = std::thread::hardware_concurrency();
        for (int i=0;i<CPUNumber;i++)
        {
            CPUs.push_back(CPU());
        }
    }

    SquareMatrix & Multiply( SquareMatrix & A, SquareMatrix & B, int CPUToWork );

};

#endif // COMPUTER_H
