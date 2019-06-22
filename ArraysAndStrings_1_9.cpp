#include <iostream>
#include <string>

bool isRotation(
   const std::string& s1,
   std::string& s2);

bool isSubstring(
   const std::string& s1,
   const std::string& s2);

bool isRotationBruteForce(
   const std::string& s1,
   std::string& s2);

int main()
{
   std::string string1("weirdwax");
   std::string string2("axweirdw");

   if (isRotation(string1, string2))
   {
      std::cout << "Test1 Passed\n";
   }
   else
   {
      std::cout << "Test1 Failed\n";
   }

   std::string s1("trucktop");
   std::string s2("tiptruck");

   if (!isRotation(s1, s2))
   {
      std::cout << "Test2 Passed\n";
   }
   else
   {
      std::cout << "Test2 Failed\n";
   }

   // Test brute force

   string1 = "weirdwax";
   string2 = "axweirdw";

   if (isRotationBruteForce(string1, string2))
   {
      std::cout << "Test1 Brute Force Passed\n";
   }
   else
   {
      std::cout << "Test1 Brute Force Failed\n";
   }

   s1 = "trucktop";
   s2 = "tiptruck";

   if (!isRotationBruteForce(s1, s2))
   {
      std::cout << "Test2 Brute Force Passed\n";
   }
   else
   {
      std::cout << "Test2 Brute Force Failed\n";
   }


   int k;
   std::cin >> k;
   return 0;
}

bool isRotation(
   const std::string& s1,
   std::string& s2)
{
   if (s1.length() != s2.length())
   {
      return false;
   }

   // Concatenate s2 with itself
   s2.append(s2);

   // If s1 is a substring of s2 concatenated with itself, return true. Else return false.
   if (isSubstring(s1, s2))
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool isSubstring(
   const std::string& s1,
   const std::string& s2)
{
   std::string::size_type subStringPosition = s2.find(s1);
   if (subStringPosition == std::string::npos)
   {
      return false;
   }
   else
   {
      return true;
   }
}

bool isRotationBruteForce(
   const std::string& s1,
   std::string& s2)
{
   if (s1.length() != s2.length())
   {
      std::cout << "Bad Length\n";
      return false;
   }

   if (s1 == s2)
   {
      std::cout << "Already match\n";
      return true;
   }
   else
   {
      for (unsigned int rotationCount = 0; rotationCount < s1.length() - 1; rotationCount++)
      {
         char saveLastChar = s2.back();
         for (unsigned int charIndex = s2.length() - 1; charIndex > 0; charIndex--)
         {
            s2[charIndex] = s2[charIndex - 1];
         }
         s2[0] = saveLastChar;

         // For Debug
         std::cout << "New S2 for brute force comparison: " << s2 << '\n';
         // Compare s2 to s1
         if (s1 == s2)
         {
            return true;
         }
      }
   }

   return false;
}













