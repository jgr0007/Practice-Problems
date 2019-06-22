#include <iostream>
#include <map>

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

const Node* loopStartNodeReturn(
   const Node* const inputList);

void listPrint(
   const Node* const inputList);

int main()
{
   Node* n0 = new Node(0, 4);
   Node* n1 = new Node(n0, 6);
   Node* n2 = new Node(n1, 1);
   Node* n3 = new Node(n2, 3);
   Node* n4 = new Node(n3, 5);
   n0->next = n4;
   Node* head(n4);

   std::cout << "Testing List with loop starting at n0 (value 5)\n";
   const Node* result(loopStartNodeReturn(head));
   if (result->val == 5)
   {
      std::cout << "Test Passed.\n";
   }
   else
   {
      std::cout << "Test Failed. Expected 5, but got: " << result->val << "\n";
   }

   Node* nt0 = new Node(0, 11);
   Node* nt1 = new Node(nt0, 19);
   Node* nt2 = new Node(nt1, 14);
   Node* nt3 = new Node(nt2, 9);
   Node* nt4 = new Node(nt3, 17);
   Node* nt5 = new Node(nt4, 10);
   nt1->next = nt3;
   Node* head2(nt5);
   
   std::cout << "Testing List with loop starting at nt1 (value 9)\n";
   result = loopStartNodeReturn(head2);
   if (result->val == 9)
   {
      std::cout << "Test Passed.\n";
   }
   else
   {
      std::cout << "Test Failed. Expected 9, but got: " << result->val << "\n";
   }
   
   int k;
   std::cin >> k;
   return 0;
}

void listPrint(
   const Node* const inputList)
{
   const Node* current(inputList);
   while (current != 0)
   {
      std::cout << current->val << ", ";
      current = current->next;
   }
   std::cout << std::endl;
}

const Node* loopStartNodeReturn(
   const Node* const inputList)
{
   std::map<unsigned long, int> hashAddresses;
   const Node* current(inputList);
   while (current != 0)
   {
      unsigned long nextNodeAddress(reinterpret_cast<unsigned long>(current));
      std::map<unsigned long, int>::const_iterator it = hashAddresses.find(nextNodeAddress);
      if (it == hashAddresses.end())
      {
         hashAddresses.insert(std::make_pair(nextNodeAddress, 0));
      }
      else
      {
         return current;
      }

      current = current->next;
   }

   // Shouldn't get here. Problem lets us make the assumption that the list always has a loop.
   return 0;
}










