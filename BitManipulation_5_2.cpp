#include <iomanip>
#include <iostream>
#include <stdint.h>
#include <string>


union doubleTo64 {
   double doubleRep;
   uint64_t uint64rep;
};

std::string doubleToString(
   double inputNum);

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

std::string doubleToString(
   double inputNum)
{
   std::string result("");

   doubleTo64 representation = { inputNum };

   uint64_t mask(0x01);
   uint64_t bitValue(0);

   // Get furthest right bit.
   auto firstSetBitFromRight(-1);
   for (int bitNum = 0; bitNum <= 64; ++bitNum)
   {
      if (((representation.uint64rep >> bitNum) & mask) == 1)
      {
         firstSetBitFromRight = bitNum;
         break;
      }
   }
   if (firstSetBitFromRight == -1)
   {
      return "0000";
   }

   representation.uint64rep >>= firstSetBitFromRight;

   for (int bitNum = 0; bitNum <= 31; ++bitNum)
   {
      if (((representation.uint64rep >> bitNum) & mask) == 0)
      {
         result.append("0");
      }
      else
      {
         result.append("1");
      }
   }

   // Make sure number could be represented.
   // Input number has already been shifted right to 
   // the first set bit.
   if ((representation.uint64rep & 0xFFFFFFFF00000000) != 0)
   {
      result = "ERROR - input number was longer than 32 bits.";
   }

   return result;
}

bool tests()
{
   double inputNum(0.72);
   doubleTo64 representation1{ inputNum };
   std::cout << "\nTesting with the number: " << inputNum << "\n";
   std::cout << "Hex representation:\n";
   std::cout << std::hex << std::setw(16) << std::setfill('0') << representation1.uint64rep;

   std::string result(doubleToString(inputNum));
   std::cout << "\nResult is: " << result << std::endl;

   inputNum = 0.5;
   doubleTo64 representation2{ inputNum };
   std::cout << "\nTesting with the number: " << inputNum << "\n";
   std::cout << "Hex representation:\n";
   std::cout << std::hex << std::setw(16) << std::setfill('0') << representation2.uint64rep;

   result = doubleToString(inputNum);
   std::cout << "\nResult is: " << result << std::endl;

   inputNum = 0.0;
   doubleTo64 representation3{ inputNum };
   std::cout << "\nTesting with the number: " << inputNum << "\n";
   std::cout << "Hex representation:\n";
   std::cout << std::hex << std::setw(16) << std::setfill('0') << representation3.uint64rep;

   result = doubleToString(inputNum);
   std::cout << "\nResult is: " << result << std::endl;

   return false;
}













