#include <iostream>
#include <iomanip>
#include <vector>

const int ROW_LENGTH = 10;

std::vector<std::vector<int> > matrixRotate(
   std::vector<std::vector<int> > inputMatrix,
   int rowLength);

std::vector<std::vector<int> > matrixRotateInPlace(
   std::vector<std::vector<int> > inputMatrix,
   int rowLength);

void matrixPrint(
   std::vector<std::vector<int> > inputMatrix,
   int rowLength);

int main()
{
   std::vector<std::vector<int> > inputMatrix;

   inputMatrix.resize(ROW_LENGTH);
   for (int i = 0; i < ROW_LENGTH; ++i)
      inputMatrix[i].resize(ROW_LENGTH);

   for (int rowIndex = 0; rowIndex < ROW_LENGTH; rowIndex++)
   {
      for (int columnIndex = 0; columnIndex < ROW_LENGTH; columnIndex++)
      {
         inputMatrix[rowIndex][columnIndex] = rowIndex + columnIndex;
      }
   }

   matrixPrint(inputMatrix, ROW_LENGTH);
   std::cout << "\n\n\n";

   std::vector<std::vector<int> > outputMatrix = matrixRotate(inputMatrix, ROW_LENGTH);

   matrixPrint(outputMatrix, ROW_LENGTH);
   std::cout << "\n\n\n";

   std::vector<std::vector<int> > outputMatrix2 = matrixRotateInPlace(inputMatrix, ROW_LENGTH);
   matrixPrint(outputMatrix2, ROW_LENGTH);

   int k;
   std::cin >> k;
   return 0;
}

std::vector<std::vector<int> > matrixRotate(
   std::vector<std::vector<int> > inputMatrix,
   int rowLength)
{
   std::vector<std::vector<int> > outputMatrix;
   outputMatrix.resize(rowLength);
   for (int i = 0; i < rowLength; ++i)
      outputMatrix[i].resize(rowLength);

   for (int rowIndex = 0; rowIndex < rowLength; rowIndex++)
   {
      for (int columnIndex = 0; columnIndex < rowLength; columnIndex++)
      {
         outputMatrix[rowIndex][rowLength - 1 - columnIndex] = inputMatrix[rowIndex][columnIndex];
      }
   }

   return outputMatrix;
}

std::vector<std::vector<int> > matrixRotateInPlace(
   std::vector<std::vector<int> > inputMatrix,
   int rowLength)
{
   for (int rowNumber = 0; rowNumber < rowLength / 2; rowNumber++)
   {
      int firstElement(rowNumber);
      int lastElement(rowLength - 1 - rowNumber);

      for (int rowNumberIndex = firstElement; rowNumberIndex < lastElement; rowNumberIndex++)
      {
         int offset(rowNumberIndex - firstElement);
         int top(inputMatrix[firstElement][rowNumberIndex]);

         inputMatrix[firstElement][rowNumberIndex] = inputMatrix[lastElement - offset][firstElement];

         inputMatrix[lastElement - offset][firstElement] = inputMatrix[lastElement][lastElement-offset];

         inputMatrix[lastElement][lastElement - offset] = inputMatrix[rowNumberIndex][lastElement];

         inputMatrix[rowNumberIndex][lastElement] = top;
      }
   }
   return inputMatrix;
}

void matrixPrint(
   std::vector<std::vector<int> > inputMatrix,
   int rowLength)
{
   for (int rowIndex = 0; rowIndex < rowLength; rowIndex++)
   {
      for (int columnIndex = 0; columnIndex < rowLength; columnIndex++)
      {
         std::cout << std::setw(2) << inputMatrix[rowIndex][columnIndex] << ", ";
      }
      std::cout << '\n';
   }
}
















