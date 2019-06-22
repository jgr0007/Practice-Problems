#include <iostream>
#include <string>

std::string stringCompress(
   const std::string& inputString);

int main()
{
   std::string testString("aabcccccaaa");
   std::string result(stringCompress(testString));
   std::cout << "result of aabcccccaaa: " << result << '\n';

   testString = "abcd";
   std::cout << "result of abcd: "<< stringCompress(testString) << '\n';

   int k;
   std::cin >> k;
   return 0;
}

std::string stringCompress(
   const std::string& inputString)
{
   std::string compressedString("");

   for (unsigned int inStringIndex = 0; inStringIndex < inputString.length(); )
   {
      char compressionChar(inputString[inStringIndex]);
      int compressionCharRepeats(1);
      compressedString += compressionChar;

      while ((inStringIndex + 1 < inputString.length()) && (inputString[inStringIndex + 1] == compressionChar))
      {
         compressionCharRepeats++;
         inStringIndex++;
      }

      compressedString += std::to_string(compressionCharRepeats);
      inStringIndex++;
   }

   std::cout << "compressedString: " << compressedString << '\n';

   if (compressedString.length() < inputString.length())
   {
      return compressedString;
   }
   else
   {
      return inputString;
   }
}


