all:
	g++ ptest/main.cpp ptest/Common.cpp ptest/Computer.cpp ptest/CPU.cpp ptest/MatrixRandom.cpp ptest/PerformanceTest.cpp ptest/PreciseTimer.cpp ptest/SquareMatrix.cpp ptest/Tests.cpp ptest/utils.cpp -o ptest_exe -pthread
clean:
	rm -rf ./ptest_exe
