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

void listPrint(
   Node* inputList);

Node* listPartitionUsingTwoLists(
   Node* const inputList,
   int partitionVal);

Node* listPartitionInPlace(
   Node* const inputList,
   int partitionVal);

int main()
{
   Node* n0 = new Node(0, 1);
   Node* n1 = new Node(n0, 2);
   Node* n2 = new Node(n1, 10);
   Node* n3 = new Node(n2, 5);
   Node* n4 = new Node(n3, 8);
   Node* n5 = new Node(n4, 5);
   Node* n6 = new Node(n5, 3);
   Node* head = n6;

   std::cout << "Test list initially:\n";
   listPrint(head);
   std::cout << "\n\n";

   Node* outputList = listPartitionUsingTwoLists(head, 5);
   std::cout << "Test list after val 5 partition (2 lists):\n";
   listPrint(outputList);
   std::cout << "\n\n";

   outputList = listPartitionUsingTwoLists(head, 2);
   std::cout << "Test list after val 2 partition (2 lists):\n";
   listPrint(outputList);
   std::cout << "\n\n";

   outputList = listPartitionUsingTwoLists(head, 8);
   std::cout << "Test list after val 8 partition (2 lists):\n";
   listPrint(outputList);
   std::cout << "\n\n";

   Node* outputList1 = listPartitionInPlace(head, 5);
   std::cout << "Test list after val 5 partition (in place):\n";
   listPrint(outputList1);
   std::cout << "\n\n";

   Node* outputList2 = listPartitionInPlace(outputList1, 2);
   std::cout << "Test list after val 2 partition (in place):\n";
   listPrint(outputList2);
   std::cout << "\n\n";

   Node* outputList3 = listPartitionInPlace(outputList2, 8);
   std::cout << "Test list after val 8 partition (in place):\n";
   listPrint(outputList3);
   std::cout << "\n\n";


   int k;
   std::cin >> k;
   return 0;
}

Node* listPartitionUsingTwoLists(
   Node* const inputList,
   int partitionVal)
{
   Node* current = inputList;

   Node* lessThanList(0);
   Node* greaterThanList(0);

   // Build the two different lists
   while (current != 0)
   {
      if (current->val < partitionVal)
      {
         Node* lessNode = new Node(0, current->val);
         // Add it to the end of lessThanList
         if (lessThanList == 0)
         {
            lessThanList = lessNode;
         }
         else
         {
            Node* lessThanCurrent = lessThanList;
            while (lessThanCurrent->next != 0)
            {
               lessThanCurrent = lessThanCurrent->next;
            }
            lessThanCurrent->next = lessNode;
         }
         
      }
      else
      {
         Node* greaterNode = new Node(0, current->val);
         // Add it to the end of greaterThanList
         if (greaterThanList == 0)
         {
            greaterThanList = greaterNode;
         }
         else
         {
            Node* greaterThanCurrent = greaterThanList;
            while (greaterThanCurrent->next != 0)
            {
               greaterThanCurrent = greaterThanCurrent->next;
            }
            greaterThanCurrent->next = greaterNode;
         }
         
      }

      current = current->next;
   }

   // Combine by making tail of less than list point to head greater than list
   Node* lessTail = lessThanList;
   while (lessTail->next != 0)
   {
      lessTail = lessTail->next;
   }
   lessTail->next = greaterThanList;

   return lessThanList;
}

Node* listPartitionInPlace(
   Node* const inputList,
   int partitionVal)
{
   Node* head = inputList;
   Node* previous = inputList;
   Node* current = inputList;
   while (current != 0)
   {
      // Only need to deal with elements greater than or equal to partition value
      if (current->val >= partitionVal)
      {
         // If element less than partition exists after this element, this element needs to be moved to end of list
         Node* listSearcher = current->next;
         bool listStillNeedsPartitioning(false);
         while (listSearcher != 0)
         {
            if (listSearcher->val < partitionVal)
            {
               listStillNeedsPartitioning = true;
               break;
            }
            listSearcher = listSearcher->next;
         }
         // If all elements after this element are less than partition val, the list is finished being partitioned
         if (!listStillNeedsPartitioning)
         {
            break;
         }
         else
         {
            Node* tail = current;
            int movedVal = tail->val;
            while (tail->next != 0)
            {
               tail = tail->next;
            }
            tail->next = new Node(0, movedVal);
            if (previous == current)
            {
               previous = previous->next;
               current = current->next;
               head = current;
            }
            else
            {
               previous->next = current->next;
               current = current->next;
            }
         }
      }
      else
      {
         previous = current;
         current = current->next;
      }
   }

   return head;
}

void listPrint(
   Node* inputList)
{
   while (inputList != 0)
   {
      std::cout << inputList->val << ", ";
      inputList = inputList->next;
   }
}























