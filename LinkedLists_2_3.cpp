#include <iostream>

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


void elementFromListRemove(
   Node* node);

void listPrint(
   const Node* list);

int main()
{
   Node* n0 = new Node(0, 7);
   Node* n1 = new Node(n0, 6);
   Node* n2 = new Node(n1, 5);
   Node* n3 = new Node(n2, 4);
   Node* n4 = new Node(n3, 3);
   Node* n5 = new Node(n4, 2);
   Node* n6 = new Node(n5, 1);
   Node* head = n6;

   listPrint(head);

   elementFromListRemove(n3);

   listPrint(head);

   int k;
   std::cin >> k;
   return 0;
}

void elementFromListRemove(
   Node* node)
{
   // Make it look likes its the nest node
   node->val = node->next->val;
   // Get ready to deallocate the next node
   Node* temp = node->next;
   // Skip next node and deallocate it 
   node->next = node->next->next;
   delete temp;
}

void listPrint(
   const Node* list)
{
   std::cout << "List Nodes: \n";
   while (list != 0)
   {
      std::cout << list->val << ", ";
      list = list->next;
   }
   std::cout << "\n\n";
}





