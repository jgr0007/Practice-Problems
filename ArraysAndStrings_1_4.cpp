#include <iostream>
#include <map>
#include <string>

bool stringIsPermutationOfPalindrome(const std::string& inputString)
{
   if (inputString.length() == 0)
   {
      return false;
   }

   std::map<char, unsigned int> charsFoundFrequency;

   // Iterate though string. Store frequency of each character
   for (std::string::const_iterator it = inputString.begin(); it != inputString.end(); it++)
   {
      // Ignore spaces
      if (*it == ' ')
      {
         continue;
      }
      else
      {
         std::map<char, unsigned int>::iterator charLocationInMap = charsFoundFrequency.find(*it);
         if (charLocationInMap != charsFoundFrequency.end())
         {
            charLocationInMap->second++;
         }
         else
         {
            charsFoundFrequency.insert(std::make_pair(*it, 1));
         }
      }
   }

   // Iterate through the hash. If there is more than one char with odd frequency, return false. Otherwise,
   // at the end of the algorithm, return true
   bool oddFrequencyFound(false);
   for (std::map<char, unsigned int>::iterator it = charsFoundFrequency.begin(); it != charsFoundFrequency.end(); it++)
   {
      if (it->second % 2 != 0)
      {
         if (oddFrequencyFound)
         {
            return false;
         }
         else
         {
            oddFrequencyFound = true;
         }
      }
   }

   return true;
}

int main()
{
   std::string testString1 = "adca";
   if (!stringIsPermutationOfPalindrome(testString1))
   {
      std::cout << "Test 1 passed. testString: " << testString1 << " is not a palindrome.\n";
   }
   else
   {
      std::cout << "Test 1 failed. testString: " << testString1 << " is not a palindrome.\n";
   }

   std::string testString2 = "bb    bcce  ";
   if (!stringIsPermutationOfPalindrome(testString2))
   {
      std::cout << "Test 2 passed.\n";
   }
   else
   {
      std::cout << "Test 2 failed.\n";
   }

   std::string testString3 = "b b bcc";
   if (stringIsPermutationOfPalindrome(testString3))
   {
      std::cout << "Test 3 passed.\n";
   }
   else
   {
      std::cout << "Test 3 failed.\n";
   }

   std::string testString4 = "xxxxbbbcce";
   if (!stringIsPermutationOfPalindrome(testString4))
   {
      std::cout << "Test 4 passed.\n";
   }
   else
   {
      std::cout << "Test 4 failed.\n";
   }

   std::string testString5 = "PPPPPbb bcce ";
   if (!stringIsPermutationOfPalindrome(testString5))
   {
      std::cout << "Test 5 passed.\n";
   }
   else
   {
      std::cout << "Test 5 failed.\n";
   }

   int k;
   std::cin >> k;
   return 0;
}
