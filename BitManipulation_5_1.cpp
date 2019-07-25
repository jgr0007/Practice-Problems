#include <iostream>
#include <stdint.h>

uint32_t mergeNumbers(
   uint32_t firstNum,
   uint32_t secondNum,
   uint8_t startBit,
   uint8_t endBit);

bool tests();

int main()
{
   if (tests())
   {
      std::cout << "\n\n******** All tests passed. ********\n\n";
   }
   else
   {
      std::cout << "\n\n******** At least one test failed. ********\n\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

uint32_t mergeNumbers(
   uint32_t firstNum,
   uint32_t secondNum,
   uint8_t startBit,
   uint8_t endBit)
{
   uint32_t mask(1);
   mask <<= startBit;

   for (uint8_t bitNum = 0; bitNum <= endBit - startBit; ++bitNum)
   {
      firstNum = firstNum & (~mask);
      mask <<= 1;
   }

   secondNum <<= startBit;

   return firstNum | secondNum;
}

bool tests()
{
   uint32_t firstNum(1024);
   uint32_t secondNum(19);
   uint8_t startBit(2);
   uint8_t endBit(6);

   uint32_t result(mergeNumbers(firstNum, secondNum, startBit, endBit));
   if (result != 1100)
   {
      std::cout << "Error - expected 1100, but got: " << result << ".\n";
      return false;
   }

   firstNum = 634;
   secondNum = 14;
   startBit = 4;
   endBit = 7;

   result = mergeNumbers(firstNum, secondNum, startBit, endBit);
   if (result != 746)
   {
      std::cout << "Error - expected 746, but got: " << result << ".\n";
      return false;
   }

   firstNum = 7;
   secondNum = 2;
   startBit = 0;
   endBit = 1;

   result = mergeNumbers(firstNum, secondNum, startBit, endBit);
   if (result != 6)
   {
      std::cout << "Error - expected 6, but got: " << result << ".\n";
      return false;
   }

   firstNum = 3221225472;
   secondNum = 2;
   startBit = 30;
   endBit = 31;

   result = mergeNumbers(firstNum, secondNum, startBit, endBit);
   if (result != 2147483648)
   {
      std::cout << "Error - expected 2147483648, but got: " << result << ".\n";
      return false;
   }


   return true;
}




















