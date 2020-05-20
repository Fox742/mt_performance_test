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

    bool _showProgress;
    void progressMultiplication( SquareMatrix & A, SquareMatrix & B, SquareMatrix & result,  std::vector<std::pair<int,int>> pairs, std::string header);

public:
    Computer(bool showProgress=false);
    static int getCPUNumber();
    SquareMatrix Multiply( SquareMatrix & A, SquareMatrix & B, int CPUToWork = 1, std::string header = "");

};

#endif // COMPUTER_H
