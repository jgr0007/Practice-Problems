// ArraysAndStrings_1_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <map>
#include <string>

bool stringsArePermutations(
   const std::string& s1,
   const std::string& s2);

int main()
{
   std::string s1 = "abcde";
   std::string s2 = "edabc";
   if (stringsArePermutations(s1, s2))
   {
      std::cout << "Test 1 Passed\n";
   }
   else
   {
      std::cout << "Test 1 Failed\n";
   }

   s1 = "";
   s2 = "asbd";
   if (!stringsArePermutations(s1, s2))
   {
      std::cout << "Test 2 Passed\n";
   }
   else
   {
      std::cout << "Test 2 Failed\n";
   }

   s1 = "eeee";
   s2 = "eee";
   if (!stringsArePermutations(s1, s2))
   {
      std::cout << "Test 3 Passed\n";
   }
   else
   {
      std::cout << "Test 3 Failed\n";
   }

   s1 = "eeeehig";
   s2 = "eeeegih";
   if (stringsArePermutations(s1, s2))
   {
      std::cout << "Test 4 Passed\n";
   }
   else
   {
      std::cout << "Test 4 Failed\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

bool stringsArePermutations(
   const std::string& s1,
   const std::string& s2)
{
   if (s1.length() == 0 || (s1.length() != s2.length()))
   {
      return false;
   }

   std::map<char, unsigned int> charsFoundFrequency;

   for (std::string::const_iterator it = s1.begin(); it != s1.end(); it++)
   {
      // If already in hash, increment frequency count
      std::map<char, unsigned int>::iterator charIter = charsFoundFrequency.find(*it);
      if (charIter != charsFoundFrequency.end())
      {
         charIter->second++;
      }
      else
      {
         // Store to hash
         charsFoundFrequency.insert(std::make_pair(*it, 1));
      }
   }

   for (std::string::const_iterator it = s2.begin(); it != s2.end(); it++)
   {
      // Find in hash
      std::map<char, unsigned int>::iterator charIter = charsFoundFrequency.find(*it);
      if (charIter == charsFoundFrequency.end())
      {
         // Character is unique to string 2
         return false;
      }
      else
      {
         if (charIter->second == 0)
         {
            // There are more of this char in string2 than in string1
            return false;
         }
         else
         {
            // Decrement number of times found
            charIter->second--;
         }
      }
      
   }

   for (std::map<char, unsigned int>::iterator it = charsFoundFrequency.begin(); it != charsFoundFrequency.end(); it++)
   {
      if (it->second != 0)
      {
         return false;
      }
   }

   return true;
}

