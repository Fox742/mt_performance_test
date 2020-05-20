#include "PerformanceTest.h"
#include "Tests.h"
#include "string"
#include <iostream>
#include <conio.h>
#include <math.h>
#include "PreciseTimer.h"
#include "SquareMatrix.h"
#include "Computer.h"
#include "utils.h"
#include <algorithm>
#include <Common.h>
#include <fstream>

using namespace std;

void PerformanceTest::BigPerformanceTest()
{
    std::vector<int> matrixLineSizes = std::vector<int>({ 2000000, 4000000, 8000000, 10000000 });
    std::vector<int> CPUNumbers = std::vector<int>({ 1, 2, 6, 9,12 });
    std::vector<PerformanceTest::StatisticItem> results = this->experimentSeries(matrixLineSizes,CPUNumbers);
    printResults("big_performance_tests",results);
}

void PerformanceTest::SmallPerformanceTest()
{
    std::vector<int> matrixLineSizes = std::vector<int>({ 10000, 20000, 30000, 40000, 50000,60000,70000,80000,90000,100000 });
    std::vector<int> CPUNumbers = std::vector<int>({ 1, 2, 6, 9,12 });
    std::vector<PerformanceTest::StatisticItem> results = this->experimentSeries(matrixLineSizes,CPUNumbers);
    printResults("small_performance_tests",results);
}

void PerformanceTest::printResults(std::string folderName, std::vector<PerformanceTest::StatisticItem>statictics)
{
    ofstream fout;
    ClearScreen();
    Utils::DeleteFolder(folderName);
    Utils::TouchPath(folderName,true);

    std::sort(statictics.begin(),statictics.end());

    if (statictics.size())
    {
        std::cout << "RESULTS:"<<std::endl;
        int statisticsPointer = 0;
        //int dataSize = statictics[0].size();
        int dataSize;
        while (statisticsPointer < statictics.size())
        {
            int dataSize = statictics[statisticsPointer].size;
            std::cout
                    << "SIZE: "<<dataSize
                    <<" ("<<statictics[statisticsPointer].sqrtSize
                    << "X"<<statictics[statisticsPointer].sqrtSize
                    << ")"<<std::endl;
            do
            {
                PerformanceTest::StatisticItem currI = statictics[statisticsPointer];

                std::cout <<"\t"<< currI.CPUNumber<<"\t"<<currI.timeSpent<<std::endl;


                fout.open( folderName+"/"+ std::to_string(currI.size)+".txt", std::ios::app);
                fout    << currI.size<<","<<currI.sqrtSize<<","<< currI.CPUNumber<<","<< currI.timeSpent<< std::endl;
                fout.close();

                statisticsPointer++;
            }
            while ((statisticsPointer < statictics.size()) && ( dataSize == statictics[statisticsPointer].size ));


        }
    }
    else
    {
        std::cout << "There is not any statistics somewhy"<<std::endl;
    }

}

void PerformanceTest::ProgrammTest()
{
    Tests::test1();
    Tests::test2();
    Tests::test3();
    Tests::test4();
    Tests::test6();
}

std::vector<PerformanceTest::StatisticItem> PerformanceTest::experimentSeries(std::vector<int> matrixLineSize,std::vector<int> CPUNumber)
{
    std::vector<StatisticItem>results;
    for (unsigned int i=0;i<matrixLineSize.size();i++)
    {
        int matrixSize = std::sqrt(matrixLineSize[i]);
        for (unsigned int j = 0;j<CPUNumber.size();j++)
        {
            std::vector<double>timesStatistics;
            for (unsigned int k=0;k<10;k++)
            {
                double timeSpent;
                oneExpirement(matrixLineSize[i],CPUNumber[j],matrixSize,timeSpent,k);
                timesStatistics.push_back( timeSpent );
            }

            double timeSpentAvg = 0;
            for (unsigned int k=0;k<timesStatistics.size();k++)
            {
                timeSpentAvg+=timesStatistics[k];
            }
            if ( timesStatistics.size() )
                timeSpentAvg /= ((double)timesStatistics.size());


            // Сохранение информации об эксперименте
            results.push_back(
                        StatisticItem
                            (
                                matrixLineSize[i],
                                matrixSize,
                                timeSpentAvg,
                                CPUNumber[j]
                            )
                        );


        }
    }
    return results;
}

bool PerformanceTest::oneExpirement(int elementsNumber, int cpuNumber, int matrixSize ,double & timeSpent,int attempt)
{

    std::string headerStr = "MULTIPLYING MATRIXES: "+std::to_string(matrixSize)+std::string("X") + std::to_string(matrixSize)+" ("+std::to_string(elementsNumber)+
            ") ATTEMPT: "+ std::to_string(attempt)+" CPU AMOUNT: "+std::to_string(cpuNumber);

    PreciseTimer pt;

    SquareMatrix A(matrixSize,true);
    SquareMatrix B(matrixSize,true);
    Computer c(true);

    pt.startMeasure();
    c.Multiply(A,B,cpuNumber,headerStr);
    timeSpent = pt.stopMeasure();

    return true;
}

int PerformanceTest::main(int argc, char* argv[])
{
    std::string command = "";

    if (argc>1)
    {
        command = std::string(argv[1]);
    }

    if (command=="")
    {
        std::cout << "Please, enter one of three option (test, big, small): ";
        std::cin >> command;
    }

    if ( command == "test")
    {
        std::cout << "Performing self-tests" <<std::endl;
        std::cout << "Press any key to start!"<<std::endl;
        getch();
        this->ProgrammTest();
    }
    else if (command == "big")
    {
        std::cout << "You asked for performance tests with big matrixes." <<std::endl;
        std::cout << "This tests running takes long time. On conplete You will get the results on screen and folder <<big_performance_tests>>"<<std::endl;
        std::cout << "Press any key to start!"<<std::endl;
        getch();
        this->BigPerformanceTest();
    }
    else if (command == "small")
    {
        std::cout << "You asked for performance tests with small matrixes." <<std::endl;
        std::cout << "On conplete You will get the results on screen and folder <<small_performance_tests>>"<<std::endl;
        std::cout << "Press any key to start!"<<std::endl;
        getch();
        this->SmallPerformanceTest();
    }
    else
    {
        std::cout << "I am very sorry, but I don't know to command :( ";
    }

    std::cout << "Press any key to quit..."<<std::endl;
    return 0;
}
