#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include <vector>
#include <iostream>


class Row
{
     private:
          std::vector <int> body;
          Row(int size)
          {
            body = std::vector<int>(size);
          }
          friend class SquareMatrix;
public:
          int& operator [](const int k)
          {
               return body[k];
          }

};

class SquareMatrix
{
      private:
            std::vector<Row> rows;
            static int maxSize;
      public:
            SquareMatrix(int size);

            Row& operator [](const int& i)
            {
                 return rows[i];
            }

            int size()
            {
                return rows.size();
            }
};

#endif // SQUAREMATRIX_H
