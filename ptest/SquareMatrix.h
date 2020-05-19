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
            SquareMatrix(int size, bool randomFill=false);

            Row& operator [](const int& i)
            {
                 return rows[i];
            }

            int size() const
            {
                return rows.size();
            }
            friend bool operator== (SquareMatrix &sm1,SquareMatrix &sm2);
            friend bool operator!= (SquareMatrix &sm1,SquareMatrix &sm2);
};

bool operator== (SquareMatrix &sm1, SquareMatrix &sm2);
bool operator!= (SquareMatrix &sm1, SquareMatrix &sm2);

#endif // SQUAREMATRIX_H
