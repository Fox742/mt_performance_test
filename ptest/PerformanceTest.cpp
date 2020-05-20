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
#include <sstream>

using namespace std;

void PerformanceTest::BigPerformanceTest()
{
    std::string path = "big_performance_tests";
    Utils::DeleteFolder(path);
    std::vector<int> matrixLineSizes = std::vector<int>({ 2000000, 4000000, 8000000, 10000000 });
    std::vector<PerformanceTest::StatisticItem> results = this->experimentSeries(matrixLineSizes, this->CPUNumbers, path,1);
    printResults(path,results);
}

void PerformanceTest::SmallPerformanceTest()
{
    std::string path = "small_performance_tests";
    Utils::DeleteFolder(path);
    std::vector<int> matrixLineSizes = std::vector<int>({ 10000, 20000, 30000, 40000, 50000,60000,70000,80000,90000,100000 });
    std::vector<PerformanceTest::StatisticItem> results = this->experimentSeries(matrixLineSizes, this->CPUNumbers, path,50);
    printResults(path,results);
}

void PerformanceTest::CustomPerformanceTest( unsigned int elementsNumber, int CPUNumber)
{
    std::string path = "custom_performance_tests";
    Utils::DeleteFolder(path);
    std::vector<int> matrixLineSizes = std::vector<int>({ int(elementsNumber)});
    std::vector<int> CPUs = this->CPUNumbers;
    if (CPUNumber!=-1)
    {
        CPUs = std::vector<int>({ int(CPUNumber)});
    }
    std::vector<PerformanceTest::StatisticItem> results = this->experimentSeries(matrixLineSizes, CPUs, path,1);
    printResults(path,results);
}

void PerformanceTest::printResults(std::string folderName, std::vector<PerformanceTest::StatisticItem>statictics)
{
    ClearScreen();
    std::sort(statictics.begin(),statictics.end());

    if (statictics.size())
    {
        std::cout << "RESULTS MATRIXES MULTIPLYING TIME MEASUREMENT:"<<std::endl;
        unsigned int statisticsPointer = 0;
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
            std::cout<<"\tCPU amount:\tTime:"<<std::endl;
            do
            {
                PerformanceTest::StatisticItem currI = statictics[statisticsPointer];

                std::cout <<"\t"<< currI.CPUNumber<<"\t\t"<<currI.timeSpent<<std::endl;
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

void PerformanceTest::saveToFile(StatisticItem toSave, std::string folderName)
{
    Utils::TouchPath(folderName,true);
    ofstream fout;
    fout.open( folderName+"/"+ std::to_string(toSave.size)+".txt", std::ios::app);
    fout    << toSave.size<<","<<toSave.sqrtSize<<","<< toSave.CPUNumber<<","<< toSave.timeSpent<< std::endl;
    fout.close();
}

std::vector<PerformanceTest::StatisticItem> PerformanceTest::experimentSeries(std::vector<int> matrixLineSize, std::vector<int> CPUNumber,std::string folderName, unsigned int attemptsNumber)
{
    std::vector<StatisticItem>results;
    for (unsigned int i=0;i<matrixLineSize.size();i++)
    {
        int matrixSize = std::sqrt(matrixLineSize[i]);
        for (unsigned int j = 0;j<CPUNumber.size();j++)
        {
            if (CPUNumber[j] > Computer::getCPUNumber())
                continue;
            std::vector<double>timesStatistics;
            for (unsigned int k=0;k<attemptsNumber;k++)
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


            // Сохранение информации об эксперименте (в вектор и в файл).
            // В файл сохраняем сразу чтобы в случае если программа упала до завершения - чтобы мы знали промежуточные результаты
            StatisticItem si =
                    StatisticItem
                        (
                            matrixLineSize[i],
                            matrixSize,
                            timeSpentAvg,
                            CPUNumber[j]
                        );
            results.push_back(si);
            this->saveToFile(si,folderName);

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

bool PerformanceTest::getIntNumberFromUser(int&number,int argumentPosition,int argc, char* argv[],std::string fieldName,bool emptyAllowed)
{
    std::string StrInt = "";
    if (argumentPosition<argc)
    {
        StrInt = argv[argumentPosition];
        try
            {
                std::stringstream ss(StrInt);

                int i;
                if ((ss >> number).fail() || !(ss >> std::ws).eof())
                {
                    throw std::bad_cast();
                }
                return true;
            }
            catch(...)
            {
            }
    }

    std::cout << "Please, enter "+fieldName<<": ";
    try
    {
        std::cin >> number;
    }
    catch (...)
    {
        if (!emptyAllowed)
        {
            std::cout << "I couldn't converted "+ std::string(fieldName)<< ". Need integer number" <<std::endl;
            return false;
        }
    }
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
        std::cout << "Please, type one of three option (test, big, small, custom) and press Enter: ";
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
    else if (command == "custom")
    {
        int elementsAmount;
        int processorsNumber = -1;

        if (!getIntNumberFromUser(elementsAmount,2,argc,argv,"matrix element amount"))
        {
            return 0;
        }
        if (!getIntNumberFromUser(processorsNumber,3,argc,argv,"number of threads", true))
        {
            return 0;
        }


        if (processorsNumber==-1)
        {
            this->CustomPerformanceTest(elementsAmount);
        }
        else
        {
            this->CustomPerformanceTest(elementsAmount,processorsNumber);
        }
    }
    else
    {
        std::cout << "I am very sorry, but I don't know to command :( ";
    }

    std::cout << "Press any key to quit..."<<std::endl;
    return 0;
}
