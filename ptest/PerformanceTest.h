#ifndef PERFORMANCETEST_H
#define PERFORMANCETEST_H

#include "vector"
#include "string"
using namespace std;

class PerformanceTest
{
    class StatisticItem
    {
    public:
        int size;
        int sqrtSize;
        double timeSpent;
        int CPUNumber;

        StatisticItem(int _size, int _sqrtSize, double _timeSpent,int _CPUNumber):size(_size), sqrtSize(_sqrtSize),timeSpent(_timeSpent),CPUNumber(_CPUNumber)
        {

        }

        bool operator < (const StatisticItem& si) const
        {
            //return ((size < si.size) && ( CPUNumber < si.CPUNumber ));
            return size < si.size || (size == si.size && CPUNumber < si.CPUNumber);
        }

    };

private:
    void BigPerformanceTest();          // Тест производительности на больших матрицах
                                        // (где преимущества использования большого количества ядер в теории должны больше проявяться)


    void SmallPerformanceTest();        // Тест производительности на маленьких матрицах, при котором в теории выигрывает
                                        //маленькое число задействованных ядер процессоров

    void ProgrammTest();                // Тест работоспособности программы, используемые мной при разработке программы

    std::vector<PerformanceTest::StatisticItem>experimentSeries(std::vector<int> matrixLineSize, std::vector<int> CPUNumber, std::string folderName, unsigned int attemptsNumber = 10);
    // Серия эксперимент (например, эксперимент с большими матрицами и с маленькими)

    bool oneExpirement(int elementsNumber, int cpuNumber, int matrixSize ,double & timeSpent,int attempt); // возвращаем bool - если есть ошибка и мы до конца не умножили матрицу

    void printResults(std::string folderName, std::vector<PerformanceTest::StatisticItem>statictics);

    void saveToFile(StatisticItem, std::string folderName);

    std::vector<int> CPUNumbers = std::vector<int>({ 1, 2, 4, 6, 8, 9, 12 });
public:
    int main(int argc, char* argv[]);
};

#endif // PERFORMANCETEST_H
