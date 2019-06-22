// ArraysAndStrings_1_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>

std::string filledInSpacesReturn(
   const std::string& inputString,
   unsigned int trueLength);

int main()
{
   std::string testString = " fge r    ";
   int testLength = 6;
   std::string stringReturned = filledInSpacesReturn(testString, testLength);
   if (stringReturned != "%20fge%20r")
   {
      std::cout << "Test1 Failed\n";
   }
   else
   {
      std::cout << "Test1 Passed\n";
   }

   testString = "afger";
   testLength = 5;
   stringReturned = filledInSpacesReturn(testString, testLength);
   if (stringReturned != "afger")
   {
      std::cout << "Test2 Failed\n";
   }
   else
   {
      std::cout << "Test2 Passed\n";
   }

   testString = " a  ";
   testLength = 2;
   stringReturned = filledInSpacesReturn(testString, testLength);
   if (stringReturned != "%20a")
   {
      std::cout << "Test3 Failed\n";
   }
   else
   {
      std::cout << "Test3 Passed\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

std::string filledInSpacesReturn(
   const std::string& inputString,
   unsigned int trueLength)
{
   int numSpaces(0);
   // Get Number of Spaces and Create new Char Array
   for (unsigned int i = 0; i < trueLength; i++)
   {
      if (inputString[i] == ' ')
      {
         numSpaces++;
      }
   }
   const int numCounted = numSpaces;
   std::vector<char> newCharVector(trueLength + (numCounted * 2));
   
   // Iterate through inputString,writing to new Char Array
   unsigned int inputStringIndex = 0;
   unsigned int newCharVectorIndex = 0;
   for (; inputStringIndex < trueLength; inputStringIndex++)
   {
      if (inputString[inputStringIndex] == ' ')
      {
         newCharVector[newCharVectorIndex] = '%';
         newCharVector[newCharVectorIndex + 1] = '2';
         newCharVector[newCharVectorIndex + 2] = '0';
         newCharVectorIndex += 3;
      }
      else
      {
         newCharVector[newCharVectorIndex] = inputString[inputStringIndex];
         newCharVectorIndex++;
      }
   }

   // Return char array as string
   std::string returnString(newCharVector.begin(), newCharVector.end());
   return returnString;
}






