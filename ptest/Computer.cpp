#include "Computer.h"
#include "iostream"
#include "Common.h"

Computer::Computer(bool showProgress):_showProgress(showProgress)
{
    // Определяем количество ядер процессора
    unsigned int CPUNumber = getCPUNumber();
    for (unsigned int i=0;i<CPUNumber;i++)
    {
        CPUs.push_back(CPU());
    }
}

int Computer::getCPUNumber()
{
    return std::thread::hardware_concurrency();
}

SquareMatrix Computer::Multiply( SquareMatrix & A, SquareMatrix & B, int CPUToWork, std::string header)
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
    unsigned int _CPUToWork = CPUToWork;
    if (_CPUToWork > this->CPUs.size())
    {
        _CPUToWork = this->CPUs.size();
        std::cout<< "WARNING! Entered number of CPUs more, than accessible" << std::endl;
    }


    std::vector<std::pair<int,int>>limits = getLimitsForCPU(A.size(),CPUToWork);

    this->progressMultiplication(A,B,result,limits, header);

    return result;
}

std::vector<std::pair<int,int>>Computer::getLimitsForCPU(int matrixSize,int CPUToWork)
{
    std::vector<std::pair<int,int>>result;

    // Если количество задействованных ядер больше, чем строк в матрице - выкидываем иключение
    //  Вообще в этом нет ничего страшного, можно одному ядру не целую строку, а какую-то её часть, но мне лень это реализовывать :)
    if ( matrixSize/CPUToWork < 1.0 )
    {
        throw "ERROR! Number of action CPU more than matrix size";
    }

    // Делим количество строк на количество потоков, а остаток от деления распределяем по потокам
    int rowsToOneCPU = (matrixSize/CPUToWork);

    if (matrixSize % CPUToWork >0)
        rowsToOneCPU++;

    int beginPointer = 0;
    // Создаем пары, каждая из которых содержит индекс первой и последней строки области, которую должен вычислить каждый из потоков
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

void Computer::progressMultiplication( SquareMatrix & A, SquareMatrix & B, SquareMatrix & result,  std::vector<std::pair<int,int>> pairs, std::string header)
{
    // Запускаем потоки, раздав каждому из них задание умножить свою часть матрицы
    //            (i-тому потоку вычислить элементы в строках с индексом от pairs[i].first до pairs[i].second )
    for (unsigned int i=0;i<pairs.size();i++)
    {
        CPUs[i].launchMultiplication(A,B,result,pairs[i].first,pairs[i].second);
    }

    // Дальше делаем активное ожидание, что все потоки выполнят своё задание
    bool oneStillWorks;
    std::vector<int>lastProcessed(pairs.size(), 0);
    int cycleNumber=0;
    do
    {
        oneStillWorks = false; // Хотя бы один поток ещё не выполнил задание
        bool needToPrint = false; // Печатаем статистику
        for (unsigned int i=0;i<pairs.size();i++)
        {
            int total = CPUs[i].getTotal();
            int processed = CPUs[i].getProcessed(); // Вообще говоря, по-хорошему это поле надо защищать мьютексом.
                                                    //          Но в данном случае у нас нет в это острой необходимости

            // Если хотя бы один поток ещё не выполнил задачу - поднимаем флаг
            if ( processed<total)
                oneStillWorks = true;

            // Каждые 25 тысяч печатаем результат сколько элементов из скольких вычислил каждый из потоков
            if (_showProgress)
            {
                if (processed - lastProcessed[i] > 25000)
                {
                    needToPrint = true;
                }
            }
         }

         // Печатаем статистику на нулевой итерации или если вычислили больше 25 тысяч жлементов после последнего вывода статистики
         if ((_showProgress )&&(needToPrint || (!cycleNumber) ) )
         {
            ClearScreen();
            if (header!="")
            {
                std::cout << header<<std::endl;
            }
            for (unsigned i = 0;i<pairs.size();i++)
            {
                int lastProcessedCPU = CPUs[i].getProcessed();
                std::cout << "\tCPU"<<i<<"\t"<<CPUs[i].getProcessed()<< "\t"<<CPUs[i].getTotal()<<std::endl;
                lastProcessed[i] = lastProcessedCPU;
            }
         }
         cycleNumber++;
    }
    while(oneStillWorks);

    // Вызываем всем CPU join
    for (unsigned int i=0;i<pairs.size();i++)
    {
        CPUs[i].Join();
    }
}
