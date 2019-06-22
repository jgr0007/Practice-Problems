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

int nodeFromBackFind(
   const Node* const linkedList,
   int kthPositionFromBack);

int nodeFromBackPrintRecursive(
   const Node* linkedList,
   int kthPositionFromBack);

int nodeFromBackGetRecursive(
   const Node* linkedList,
   int kthPositionFromBack,
   int& result);

int main()
{
   Node* n0 = new Node(0, 7);
   Node* n1 = new Node(n0, 6);
   Node* n2 = new Node(n1, 5);
   Node* n3 = new Node(n2, 4);
   Node* n4 = new Node(n3, 3);
   Node* n5 = new Node(n4, 2);
   Node* n6 = new Node(n5, 1);
   Node* n7 = new Node(n6, 20);
   Node* head(n7);

   int intFound = nodeFromBackFind(head, 2);
   if (intFound == 6)
   {
      std::cout << "Finding 2nd element from back passed\n";
   }
   else
   {
      std::cout << "Finding 2nd element from back failed. Expected 6, but got: " << intFound << '\n';
   }

   intFound = nodeFromBackFind(head, 1);
   if (intFound == 7)
   {
      std::cout << "Finding 1st element from back passed\n";
   }
   else
   {
      std::cout << "Finding 1st element from back failed. Expected 7, but got: " << intFound << '\n';
   }

   intFound = nodeFromBackFind(head, 8);
   if (intFound == 20)
   {
      std::cout << "Finding 8th element from back passed\n";
   }
   else
   {
      std::cout << "Finding 8th element from back failed. Expected 20, but got: " << intFound << '\n';
   }

   nodeFromBackPrintRecursive(head, 2);

   int resultOutput(0);
   nodeFromBackGetRecursive(head, 2, resultOutput);
   std::cout << "Recursive get result: " << resultOutput << '\n';

   int k;
   std::cin >> k;
   return 0;
}

int nodeFromBackFind(
   const Node* const linkedList,
   int kthPositionFromBack)
{
   // Iterate through list once to get length;
   const Node* current(linkedList);
   int listLength(0);

   while (current != 0)
   {
      listLength++;
      current = current->next;
   }

   // Iterate through list length - k times to get desired node
   current = linkedList;
   int numOfTimesToIterateThroughList(listLength - kthPositionFromBack);
   for (int iterationCount = 0; iterationCount < numOfTimesToIterateThroughList; iterationCount++)
   {
      current = current->next;
   }

   return current->val;
}


int nodeFromBackPrintRecursive(
   const Node* linkedList,
   int kthPositionFromBack)
{
   if (linkedList == 0)
   {
      return 0;
   }

   int index = nodeFromBackPrintRecursive(linkedList->next, kthPositionFromBack) + 1;
      if (index == kthPositionFromBack)
      {
         std::cout << kthPositionFromBack << " th position from back is " << linkedList->val << '\n';
      }

   return index;
}

int nodeFromBackGetRecursive(
   const Node* linkedList,
   int kthPositionFromBack,
   int& result)
{
   if (linkedList == 0)
   {
      return 0;
   }

   int index = nodeFromBackGetRecursive(linkedList->next, kthPositionFromBack, result) + 1;
   if (index == kthPositionFromBack)
   {
      result = linkedList->val;
   }

   return index;
}






















