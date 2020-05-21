# mt_performance_test
Программа, умеющая генерировать матрицы и перемножать с помощью разного количества потоков и замерять время выполнения операции умножения.
Может быть использована при оценке количества параллельных потоков при разработке параллелных программ.
Но вообще, я разработал эту программу, так как мне стало интересно сколько можно выйграть 
процессорного времени при использовании разного количества ядер процессора.

Программа разработана в QtCreator, также есть возможность скомпилировать её в Linux с использованием утилиты make

Программа может работать в 4 режимах:

`test` - запускаются несколько Smoke-тестов, которые я использовал для разработки и отладки  
`big` - запускается серия умножений матриц разных размеров, матрица каждого из размеров умножается  
с помощью разного количества процессорных ядер. В данном режиме берутся большие размеры матриц (от двух миллионов элементов)  
`small` - запускается серия умножений матриц маленького размера (от 10000 элементов до 100000)  
для оценки работы оптимизации для маленького количества данных  
`custom sizeOfmatrix [NumberOfCPU]` - можно задать линейный размер перемножаемой матрицы (общее количество элементов)  
и количество ядер, используемых для перемножения.  

Режимы можно также подавать как параметры в качестве параметров командной строки. Программа результаты в файлы и выводит на экран

На компьютере с 6-ядерным процессором с поддержкой гипертрединга были получены следующие результаты:  

RESULTS MATRIXES MULTIPLYING TIME MEASUREMENT:  
SIZE: 2000000 (1414X1414)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbspCPU amount:     Time:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp1               105.653  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp2               54.7714  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp4               29.0473  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp6               23.5544  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp8               20.4794  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp9               18.6496  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp12              15.2686  
SIZE: 4000000 (2000X2000)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbspCPU amount:     Time:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp1               332.076  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp2               166.589  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp4               93.5608  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp6               73.1498  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp8               60.8784  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp9               56.2641  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp12              50.9823  
SIZE: 8000000 (2828X2828)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbspCPU amount:     Time:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp1               906.695  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp2               458.498  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp4               255.85  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp6               199.818  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp8               173.113  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp9               160.066  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp12              146.542  
SIZE: 10000000 (3162X3162)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbspCPU amount:     Time:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp1               1272  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp2               635.295  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp4               375.263  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp6               294.152  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp8               253.171  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp9               237.27  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp12              211.899  
