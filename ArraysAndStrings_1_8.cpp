#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

void matrixZeroesRowsAndColumnsClear(
   std::vector<std::vector<int> >& inputMatrix,
   int rowLength,
   int columnLength);

void matrixPrint(
   std::vector<std::vector<int> >& inputMatrix,
   int rowLength,
   int columnLength);

const int ROW_LENGTH = 3;
const int COLUMN_LENGTH = 4;

int main()
{
   std::vector<std::vector<int> > testMatrix;
   testMatrix.resize(COLUMN_LENGTH);
   for (int i = 0; i < COLUMN_LENGTH; ++i)
      testMatrix[i].resize(ROW_LENGTH);

   testMatrix[0][0] = 4;
   testMatrix[0][1] = 6;
   testMatrix[0][2] = 1;
   testMatrix[1][0] = 3;
   testMatrix[1][1] = 3;
   testMatrix[1][2] = 0;
   testMatrix[2][0] = -5;
   testMatrix[2][1] = 7;
   testMatrix[2][2] = 1;
   testMatrix[3][0] = 0;
   testMatrix[3][1] = 2;
   testMatrix[3][2] = 4;

   matrixPrint(
      testMatrix,
      ROW_LENGTH,
      COLUMN_LENGTH);
   std::cout << "\n\n\n";

   matrixZeroesRowsAndColumnsClear(
      testMatrix,
      ROW_LENGTH,
      COLUMN_LENGTH);

   matrixPrint(
      testMatrix,
      ROW_LENGTH,
      COLUMN_LENGTH);


   int k;
   std::cin >> k;
   return 0;
}

void matrixZeroesRowsAndColumnsClear(
   std::vector<std::vector<int> >& inputMatrix,
   int rowLength,
   int columnLength)
{
   // Get zeroed rows and column indexs by iterating through matrix
   std::set<int> rowIndices;
   std::set<int> columnIndices;

   for (int rowIndex = 0; rowIndex < columnLength; rowIndex++)
   {
      for (int columnIndex = 0; columnIndex < rowLength; columnIndex++)
      {
         if (inputMatrix[rowIndex][columnIndex] == 0)
         {
            rowIndices.insert(rowIndex);
            columnIndices.insert(columnIndex);
         }
      }
   }

   // Zero out the rows and columns associated with each index
   for (std::set<int>::iterator rowIter = rowIndices.begin(); rowIter != rowIndices.end(); rowIter++)
   {
      for (int rowEntry = 0; rowEntry < rowLength; rowEntry++)
      {
         inputMatrix[*rowIter][rowEntry] = 0;
      }
   }

   for (std::set<int>::iterator columnIter = columnIndices.begin(); columnIter != columnIndices.end(); columnIter++)
   {
      for (int columnEntry = 0; columnEntry < columnLength; columnEntry++)
      {
         inputMatrix[columnEntry][*columnIter] = 0;
      }
   }
}

void matrixPrint(
   std::vector<std::vector<int> >& inputMatrix,
   int rowLength,
   int columnLength)
{
   for (int rowIndex = 0; rowIndex < columnLength; rowIndex++)
   {
      for (int columnIndex = 0; columnIndex < rowLength; columnIndex++)
      {
         std::cout << std::setw(2) << inputMatrix[rowIndex][columnIndex] << ", ";
      }

      std::cout << '\n';
   }
}












