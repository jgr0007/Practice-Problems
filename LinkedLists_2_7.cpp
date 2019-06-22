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

const Node* listIntersectionFindByAddress(
   const Node* const l1,
   const Node* const l2);

void listPrint(
   const Node* const inputList);

int main()
{
   Node* n0 = new Node(0, 8);
   Node* n1 = new Node(n0, 2);
   Node* n2 = new Node(n1, 4);
   Node* n3 = new Node(n2, 5);
   Node* head1(n3);

   Node* nt0 = new Node(0, 9);
   Node* nt1 = new Node(nt0, 2);
   Node* nt2 = new Node(nt1, 4);
   Node* nt3 = new Node(nt2, 5);
   Node* head2(nt3);

   std::cout << "Testing two lists without an intersection:\n";
   std::cout << "\nList1:\n";
   listPrint(head1);
   std::cout << "\nList2:\n";
   listPrint(head2);

   const Node* result(listIntersectionFindByAddress(head1, head2));
   if (result == 0)
   {
      std::cout << "\nTest Passed\n";
   }
   else
   {
      std::cout << "\n***Test Failed\n";
   }

   nt2->next = n1;
   std::cout << "\n\nNow testing two lists with an intersection for n1 (val 2):\n";
   std::cout << "\nList1:\n";
   listPrint(head1);
   std::cout << "\nList2:\n";
   listPrint(head2);

   result = listIntersectionFindByAddress(head1, head2);
   if (result->next == n0 && result->val == 2)
   {
      std::cout << "\nTest Passed\n";
   }
   else
   {
      std::cout << "\n***Test Failed. Returned node with val: " << result->val << "\n";
   }

   head2->next = 0;
   std::cout << "\n\nNow testing two lists without an intersection (one list has only one node):\n";
   std::cout << "\nList1:\n";
   listPrint(head1);
   std::cout << "\nList2:\n";
   listPrint(head2);

   result = listIntersectionFindByAddress(head1, head2);
   if (result == 0)
   {
      std::cout << "\nTest Passed\n";
   }
   else
   {
      std::cout << "\n***Test Failed\n";
   }

   Node* np0 = new Node(n0, 4);
   head2 = np0;
   std::cout << "\n\nNow testing two lists where the tail is the intersection:\n";
   std::cout << "\nList1:\n";
   listPrint(head1);
   std::cout << "\nList2:\n";
   listPrint(head2);

   result = listIntersectionFindByAddress(head1, head2);
   if (result->next == 0 && result->val == 8)
   {
      std::cout << "\nTest Passed\n";
   }
   else
   {
      std::cout << "\n***Test Failed\n";
   }

   head2 = head1;
   std::cout << "\n\nNow testing two lists where the head is the intersection:\n";
   std::cout << "\nList1:\n";
   listPrint(head1);
   std::cout << "\nList2:\n";
   listPrint(head2);

   result = listIntersectionFindByAddress(head1, head2);
   if (result->next == n2 && result->val == 5)
   {
      std::cout << "\nTest Passed\n";
   }
   else
   {
      std::cout << "\n***Test Failed\n";
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
   std::cout << '\n';
}
const Node* listIntersectionFindByAddress(
   const Node* const l1,
   const Node* const l2)
{
   if (l1 == 0 || l2 == 0)
   {
      return 0;
   }

   std::map<long int, int> list1Hash;

   const Node* current1(l1);
   while (current1 != 0)
   {
      long int nodeAddress = reinterpret_cast<long int>(current1);
      list1Hash.insert(std::make_pair(nodeAddress, 0));
      current1 = current1->next;
   }

   const Node* current2(l2);
   while (current2 != 0)
   {
      long int current2Address(reinterpret_cast<long int>(current2));
      std::map<long int, int>::const_iterator it(list1Hash.find(current2Address));
      if (it != list1Hash.end())
      {
         return current2;
      }
      current2 = current2->next;
   }

   return 0;
}







