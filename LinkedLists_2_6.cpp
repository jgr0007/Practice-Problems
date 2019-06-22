#include <iostream>

struct Node {
   Node* next;
   int val;
   Node(
      Node* nextNode,
      int nodeVal)
      :
      next(nextNode),
      val(nodeVal)
   {
   }
};

bool isPalindrome(
   Node* inputList);

void listPrint(
   Node* inputList);

int main()
{
   Node* n0 = new Node(0, 4);
   Node* n1 = new Node(n0, 1);
   Node* n2 = new Node(n1, 3);
   Node* n3 = new Node(n2, 1);
   Node* n4 = new Node(n3, 1);
   Node* n5 = new Node(n4, 4);
   Node* head = n5;

   std::cout << "Testing on a non-palindrome list: \n";
   listPrint(head);
   if (isPalindrome(head) == false)
   {
      std::cout << "Test Passed.\n";
   }
   else
   {
      std::cout << "Test Failed.\n";
   }

   n0 = new Node(0, 5);
   n1 = new Node(n0, 2);
   n2 = new Node(n1, 9);
   n3 = new Node(n2, 9);
   n4 = new Node(n3, 9);
   n5 = new Node(n4, 2);
   Node* n6 = new Node(n5, 5);
   head = n6;

   std::cout << "\n\nTesting on an actual palindrome list: \n";
   listPrint(head);
   if (isPalindrome(head) == true)
   {
      std::cout << "Test Passed.\n";
   }
   else
   {
      std::cout << "Test Failed.\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

void listPrint(
   Node* inputList)
{
   while (inputList != 0)
   {
      std::cout << inputList->val << ", ";
      inputList = inputList->next;
   }
   std::cout << '\n';
}

bool isPalindrome(
   Node* inputList)
{
   if (inputList == 0)
   {
      return false;
   }

   Node* lengthGetter(inputList);
   int length(0);
   while (lengthGetter != 0)
   {
      length++;
      lengthGetter = lengthGetter->next;
   }

   int numberOfComparisonsToMake(length / 2);

   int iterationCount(0);
   Node* currentLeft(0);
   Node* currentRight(0);
   int listPlace(0);

   while (iterationCount <= numberOfComparisonsToMake)
   {
      listPlace = 0;

      // Get left hand val
      currentLeft = inputList;
      while (listPlace < iterationCount)
      {
         currentLeft = currentLeft->next;
         listPlace++;
      }

      // Get right hand val
      listPlace = 0;
      currentRight = inputList;
      while (listPlace < (length - iterationCount) - 1)
      {
         currentRight = currentRight->next;
         listPlace++;
      }
      if (currentLeft->val != currentRight->val)
      {
         std::cout << "The values: " << currentLeft->val << " and: " << currentRight->val << " were not equal.\n";
         return false;
      }

      std::cout << "Passed so far for values: " << currentLeft->val << " and: " << currentRight->val << "\n";

      iterationCount++;
   }

   return true;
}














