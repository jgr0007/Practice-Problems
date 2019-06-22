#include <iostream>
#include <map>

struct Node {
   Node* next;
   int val;
   Node(Node* nextNode, int nodeVal)
      :
      next(nextNode),
      val(nodeVal)
   {

   }
};

void listPrint(
   Node* listToPrint);

Node* duplicatesRemove(
   Node* listToRemove);

Node* duplicatesRemoveInPlace(
   Node* listToRemove);

int main()
{
   Node* n0 = new Node(0, 5);
   Node* n1 = new Node(n0, 5);
   Node* n2 = new Node(n1, 4);
   Node* n3 = new Node(n2, 4);
   Node* n4 = new Node(n3, 4);
   Node* n5 = new Node(n4, 2);
   Node* n6 = new Node(n5, 1);
   Node* n7 = new Node(n6, 1);
   Node* n8 = new Node(n7, 1);
   Node* head = n8;

   std::cout << "Here is the test list: \n";
   listPrint(head);
   std::cout << "\n";

   std::cout << "Removing duplicates using hash table: \n";
   Node* duplicatesRemoved(duplicatesRemove(head));
   listPrint(duplicatesRemoved);
   std::cout << "\n\n\n";

   n0 = new Node(0, 2);
   n1 = new Node(n0, 5);
   n2 = new Node(n1, 3);
   n3 = new Node(n2, 4);
   n4 = new Node(n3, 3);
   n5 = new Node(n4, 2);
   n6 = new Node(n5, 1);
   n7 = new Node(n6, 9);
   n8 = new Node(n7, 1);
   head = n8;

   std::cout << "Here is the test list: \n";
   listPrint(head);
   std::cout << "\n";

   std::cout << "Removing duplicates using hash table: \n";
   duplicatesRemoved = duplicatesRemove(head);
   listPrint(duplicatesRemoved);
   std::cout << "\n\n\n";

   n0 = new Node(0, 5);
   n1 = new Node(n0, 5);
   n2 = new Node(n1, 4);
   n3 = new Node(n2, 4);
   n4 = new Node(n3, 4);
   n5 = new Node(n4, 2);
   n6 = new Node(n5, 1);
   n7 = new Node(n6, 1);
   n8 = new Node(n7, 1);
   head = n8;

   std::cout << "Here is the test list: \n";
   listPrint(head);
   std::cout << "\n";

   std::cout << "Removing duplicates in place: \n";
   duplicatesRemoved = (duplicatesRemoveInPlace(head));
   listPrint(duplicatesRemoved);
   std::cout << "\n\n\n";

   n0 = new Node(0, 2);
   n1 = new Node(n0, 5);
   n2 = new Node(n1, 3);
   n3 = new Node(n2, 4);
   n4 = new Node(n3, 3);
   n5 = new Node(n4, 2);
   n6 = new Node(n5, 1);
   n7 = new Node(n6, 9);
   n8 = new Node(n7, 1);
   head = n8;

   std::cout << "Here is the test list: \n";
   listPrint(head);
   std::cout << "\n";

   std::cout << "Removing duplicates in place: \n";
   duplicatesRemoved = (duplicatesRemoveInPlace(head));
   listPrint(duplicatesRemoved);
   std::cout << "\n\n\n";


   int k;
   std::cin >> k;
   return 0;
}

void listPrint(
   Node* listToPrint)
{
   while (listToPrint != 0)
   {
      std::cout << listToPrint->val << ", ";
      listToPrint = listToPrint->next;
   }
   std::cout << '\n';
}

Node* duplicatesRemove(
   Node* listToRemove)
{
   std::map<int, bool> duplicates;
   Node* current = listToRemove;
   Node* previousNode = listToRemove;

   while (current != 0)
   {
      int nodeVal = current->val;
      // Check if its in map
      std::map<int, bool>::iterator valDuplicate = duplicates.find(nodeVal);
      if (valDuplicate != duplicates.end())
      {
         // Remove current node
         previousNode->next = current->next;
         delete current;
         current = previousNode->next;
      }
      else
      {
         // Store val to hash
         duplicates.insert(std::make_pair(nodeVal, true));
         previousNode = current;
         current = current->next;
      }
   }

   return listToRemove;
}

Node* duplicatesRemoveInPlace(
   Node* listToRemove)
{
   Node* current = listToRemove;
   Node* searchPointer = current;
   Node* previousNode = current;

   while (current != 0)
   {
      int nodeVal = current->val;
      // Check if it exists later in the list
      bool duplicateFound(false);
      previousNode = current;
      searchPointer = current->next;
      while (searchPointer != 0)
      {
         if (searchPointer->val == nodeVal)
         {
            duplicateFound = true;
            break;
         }
         else
         {
            previousNode = searchPointer;
            searchPointer = searchPointer->next;
         }
      }
      if (duplicateFound)
      {
         // Remove search pointer duplicate node
         previousNode->next = searchPointer->next;
         delete searchPointer;
      }
      else
      {
         current = current->next;
      }
   }

   return listToRemove;
}











