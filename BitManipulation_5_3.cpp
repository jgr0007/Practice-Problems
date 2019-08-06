#include <iostream>
#include <cstdint>

uint16_t longestPossibleSetOfOnesBruteForce(
   uint32_t inputNumber);

uint16_t longestSetOfOnesOptimized(
   uint32_t inputNumber);

bool bitIndexIsZero(
   uint16_t bitIndex,
   uint32_t inputNumber);

uint16_t longestContinuousOnesFind(
   uint32_t inputNumber);

bool tests();

int main()
{
   if (tests())
   {
      std::cout << "\n\nPassed.\n\n";
   }
   else
   {
      std::cout << "\n\nFailed.\n\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

uint16_t longestPossibleSetOfOnesBruteForce(
   uint32_t inputNumber)
{
   uint16_t longestPossibleLength(longestContinuousOnesFind(inputNumber));
   for (uint16_t bitIndex = 0; bitIndex <= 31; ++bitIndex)
   {
      if (bitIndexIsZero(bitIndex, inputNumber))
      {
         uint32_t mask(0x01 << bitIndex);
         uint32_t numberWithBitFlipped(inputNumber | mask);
         uint16_t maxFound(longestContinuousOnesFind(numberWithBitFlipped));

         if (maxFound > longestPossibleLength)
         {
            longestPossibleLength = maxFound;
         }
      }
   }

   return longestPossibleLength;
}

bool bitIndexIsZero(
   uint16_t bitIndex,
   uint32_t inputNumber)
{
   return (inputNumber & (0x01 << bitIndex)) == 0;
}

uint16_t longestContinuousOnesFind(
   uint32_t inputNumber)
{
   uint16_t longestContinuousBits(0);

   for (uint16_t bitIndex = 0; bitIndex <= 31; ++bitIndex)
   {
      if (!bitIndexIsZero(bitIndex, inputNumber))
      {
         uint16_t currentLengthOfContinuousBits(0);

         for (uint16_t bitOfContinuousBits = 0; bitOfContinuousBits <= 31 - bitIndex; ++bitOfContinuousBits)
         {
            if (bitIndexIsZero(bitIndex + bitOfContinuousBits, inputNumber))
            {
               break;
            }

            ++currentLengthOfContinuousBits;
         }

         if (currentLengthOfContinuousBits > longestContinuousBits)
         {
            longestContinuousBits = currentLengthOfContinuousBits;
         }
      }
   }

   return longestContinuousBits;
}

uint16_t longestSetOfOnesOptimized(
   uint32_t inputNumber)
{
   if (~inputNumber == 0)
   {
      return 32;
   }

   uint16_t currentLength(0);
   uint16_t previousLength(0);
   uint16_t maxLength(1);

   while (inputNumber != 0)
   {
      if ((inputNumber & 1) == 1)
      {
         ++currentLength;
      }
      else if ((inputNumber & 1) == 0)
      {
         previousLength = ((inputNumber & 2) == 0 ? 0 : currentLength);
         currentLength = 0;
      }

      uint16_t possibleMaxLength(previousLength + currentLength + 1);
      maxLength = possibleMaxLength > maxLength ? possibleMaxLength : maxLength;
      inputNumber >>= 1;
   }

   return maxLength;
}

bool tests()
{
   uint32_t testNum(3573348239);
   uint16_t result(longestPossibleSetOfOnesBruteForce(testNum));

   if (result != 9)
   {
      std::cout << "Error, expected 9, but got: " << result << ".\n";
      return false;
   }

   testNum = 0;
   result = longestPossibleSetOfOnesBruteForce(testNum);
   if (result != 1)
   {
      std::cout << "Error, expected 1, but got: " << result << ".\n";
      return false;
   }

   testNum = 4294967295;
   result = longestPossibleSetOfOnesBruteForce(testNum);
   if (result != 32)
   {
      std::cout << "Error, expected 32, but got: " << result << ".\n";
      return false;
   }

   testNum = 3707715455;
   result = longestPossibleSetOfOnesBruteForce(testNum);
   if (result != 14)
   {
      std::cout << "Error, expected 14, but got: " << result << ".\n";
      return false;
   }

   testNum = 3573348239;
   result = longestSetOfOnesOptimized(testNum);

   if (result != 9)
   {
      std::cout << "Error, expected 9, but got: " << result << ".\n";
      return false;
   }

   testNum = 0;
   result = longestSetOfOnesOptimized(testNum);
   if (result != 1)
   {
      std::cout << "Error, expected 1, but got: " << result << ".\n";
      return false;
   }

   testNum = 4294967295;
   result = longestSetOfOnesOptimized(testNum);
   if (result != 32)
   {
      std::cout << "Error, expected 32, but got: " << result << ".\n";
      return false;
   }

   testNum = 3707715455;
   result = longestSetOfOnesOptimized(testNum);
   if (result != 14)
   {
      std::cout << "Error, expected 14, but got: " << result << ".\n";
      return false;
   }

   return true;
}






















