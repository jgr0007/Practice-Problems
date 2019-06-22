#include <string>
#include <iostream>

bool stringsAreOneApart(
   const std::string& s1,
   const std::string& s2);

int main()
{
   std::string testString1("playa");
   std::string testString2("plaa");
   if (stringsAreOneApart(testString1, testString2))
   {
      std::cout << "Test 1 Passed.\n";
   }
   else
   {
      std::cout << "Test 1 Failed.\n";
   }

   testString1 = ("ptaya");
   testString2 = ("plaa");
   if (!stringsAreOneApart(testString1, testString2))
   {
      std::cout << "Test 2 Passed.\n";
   }
   else
   {
      std::cout << "Test 2 Failed.\n";
   }

   testString1 = ("");
   testString2 = ("");
   if (stringsAreOneApart(testString1, testString2))
   {
      std::cout << "Test 3 Passed.\n";
   }
   else
   {
      std::cout << "Test 3 Failed.\n";
   }

   testString1 = ("xxx xx");
   testString2 = ("xxxxxx");
   if (stringsAreOneApart(testString1, testString2))
   {
      std::cout << "Test 4 Passed.\n";
   }
   else
   {
      std::cout << "Test 4 Failed.\n";
   }

   testString1 = ("bbbcccdf");
   testString2 = ("dfbbbccc");
   if (!stringsAreOneApart(testString1, testString2))
   {
      std::cout << "Test 5 Passed.\n";
   }
   else
   {
      std::cout << "Test 5 Failed.\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

bool stringsAreOneApart(
   const std::string& s1,
   const std::string& s2)
{
   bool areOneAway(true);
   bool foundOneDifferenceAlready(false);

   if ((s1.length() > s2.length() + 1) || (s2.length() > s1.length() + 1))
   {
      // Must be within one length of each other to be within one change apart
      areOneAway = false;
   }
   else if (s1.length() == s2.length() + 1)
   {
      // Use s2 as small string in comparison
      unsigned int s1Index = 0;
      unsigned int s2Index = 0;
      for (; s2Index < s2.length(); s1Index++)
      {
         if (s1[s1Index] != s2[s2Index])
         {
            if (foundOneDifferenceAlready)
            {
               areOneAway = false;
               break;
            }
            else
            {
               foundOneDifferenceAlready = true;
               continue;
            }
         }

         s2Index++;
      }
   }
   else if (s2.length() == s1.length() + 1)
   {
      // Use s1 as small string in comparison
      unsigned int s1Index = 0;
      unsigned int s2Index = 0;
      for (; s1Index < s1.length(); s2Index++)
      {
         if (s1[s1Index] != s2[s2Index])
         {
            if (foundOneDifferenceAlready)
            {
               areOneAway = false;
               break;
            }
            else
            {
               foundOneDifferenceAlready = true;
               continue;
            }
         }
         s1Index++;
      }
   }
   else
   {
      // Both strings are the same length so iterate through each for comparison as normal
      unsigned int s1Index = 0;
      unsigned int s2Index = 0;
      for (; s1Index < s1.length(); s1Index++, s2Index++)
      {
         if (s1[s1Index] != s2[s2Index])
         {
            if (foundOneDifferenceAlready)
            {
               areOneAway = false;
               break;
            }
            else
            {
               foundOneDifferenceAlready = true;
            }
         }
      }
   }

   return areOneAway;
}

