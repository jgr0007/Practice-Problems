// ArraysAndStrings_1_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <map>
#include <string>

bool stringHasAllUniqueCharacters(
   const std::string& inputString,
   bool useHash);

bool stringHasAllUniqueCharactersHash(const std::string& inputString);

bool stringHasAllUniqueCharactersXor(const std::string& inputString);

int main()
{
   std::string testString1("abcdefghijklmnopqrstuvwxyz)(*&^%$#@!");
   std::string testString2("*abcdef*");
   std::string testString3("");
   std::string testString4("1234567890");
   std::string testString5("ploikujyhtgrfedwwwwww");

   bool useHash(false);
   if (stringHasAllUniqueCharacters(testString1, useHash))
   {
      std::cout << "string: " << testString1 << " has all unique characters\n";
   }
   else
   {
      std::cout << "string: " << testString1 << " has a repeated character!\n";
   }

   if (stringHasAllUniqueCharacters(testString2, useHash))
   {
      std::cout << "string: " << testString2 << " has all unique characters\n";
   }
   else
   {
      std::cout << "string: " << testString2 << " has a repeated character!\n";
   }

   if (stringHasAllUniqueCharacters(testString3, useHash))
   {
      std::cout << "string: " << testString3 << " has all unique characters\n";
   }
   else
   {
      std::cout << "string: " << testString3 << " has a repeated character!\n";
   }

   if (stringHasAllUniqueCharacters(testString4, useHash))
   {
      std::cout << "string: " << testString4 << " has all unique characters\n";
   }
   else
   {
      std::cout << "string: " << testString4 << " has a repeated character!\n";
   }

   if (stringHasAllUniqueCharacters(testString5, useHash))
   {
      std::cout << "string: " << testString5 << " has all unique characters\n";
   }
   else
   {
      std::cout << "string: " << testString5 << " has a repeated character!\n";
   }



   int k;
   std::cin >> k;
   return 0;
}

bool stringHasAllUniqueCharacters(
   const std::string& inputString,
   bool useHash)
{
   // Handle base cases
   if (inputString.length() == 0 || inputString.length() == 1)
   {
      return true;
   }

   bool allUnique(true);
   if (useHash)
   {
      allUnique = stringHasAllUniqueCharactersHash(inputString);
   }
   else
   {
      allUnique = stringHasAllUniqueCharactersXor(inputString);
   }

   return allUnique;
}

bool stringHasAllUniqueCharactersHash(
   const std::string& inputString)
{
   std::map<char, int> foundChars;
   for (std::string::const_iterator it = inputString.begin(); it != inputString.end(); it++)
   {
      std::map<char, int>::iterator possibleDuplicate = foundChars.find(*it);
      if (possibleDuplicate != foundChars.end())
      {
         return false;
      }
      else
      {
         foundChars.insert( std::make_pair(*it, 1));
      }
   }

   return true;
}


bool stringHasAllUniqueCharactersXor(
   const std::string& inputString)
{
   char firstChar(inputString[0]);
   for (auto it = inputString.begin() + 1; it != inputString.end(); it++)
   {
      //TODO: This logic doesn't actually work.
      short result = firstChar ^ *it;
      if (result == 0)
      {
         return false;
      }
   }

   return true;
}



