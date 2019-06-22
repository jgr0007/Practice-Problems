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
   {}
};

class PartialSum
{
public:
   Node* sum;
   int carry;
};

Node* listsAddReverse(
   const Node* const l1,
   const Node* const l2);

Node* listsAddForward(
   const Node* const l1,
   const Node* const l2);

Node* nextNodeAdd(
   const Node* const l1,
   const Node* const l2,
   int& carry);

Node* listsAddReverseBookSolution(
   Node* l1,
   Node* l2,
   int carry);

Node* listsAddForwardBookSolution(
   Node* l1,
   Node* l2);

PartialSum helper(
   Node* l1,
   Node* l2);

Node* padList(
   Node* inputList,
   int padding);

Node* insertBefore(
   Node* inputList,
   int data);

int length(
   Node* inputList);

void listPrint(
   const Node* const printedList);

int main()
{
   Node* n0 = new Node(0, 6);
   Node* n1 = new Node(n0, 1);
   Node* n2 = new Node(n1, 7);
   Node* list1(n2);

   std::cout << "List 1 contents:\n";
   listPrint(list1);

   Node* nt0 = new Node(0, 2);
   Node* nt1 = new Node(nt0, 9);
   Node* nt2 = new Node(nt1, 5);
   Node* list2(nt2);

   std::cout << "List 2 contents:\n";
   listPrint(list2);

   Node* result(listsAddReverse(list1, list2));
   std::cout << "Result of listsAddReverse:\n";
   listPrint(result);

   std::cout << "\n\n\n***Test when List 1 is bigger\n";

   n0 = new Node(0, 6);
   n1 = new Node(n0, 1);
   n2 = new Node(n1, 7);
   Node* n3 = new Node(n2, 5);
   Node* n4 = new Node(n3, 3);
   Node* n5 = new Node(n4, 4);
   list1 = n5;

   std::cout << "List 1 contents:\n";
   listPrint(list1);

   nt0 = new Node(0, 2);
   nt1 = new Node(nt0, 9);
   nt2 = new Node(nt1, 5);
   list2 = nt2;

   std::cout << "List 2 contents:\n";
   listPrint(list2);

   result = listsAddReverse(list1, list2);
   std::cout << "Result of listsAddReverse:\n";
   listPrint(result);

   std::cout << "\n\n\n***Test when List 2 is bigger\n";

   n0 = new Node(0, 6);
   n1 = new Node(n0, 1);
   n2 = new Node(n1, 7);
   list1 = n2;

   std::cout << "List 1 contents:\n";
   listPrint(list1);

   nt0 = new Node(0, 2);
   nt1 = new Node(nt0, 9);
   nt2 = new Node(nt1, 5);
   Node* nt3 = new Node(nt2, 1);
   Node* nt4 = new Node(nt3, 1);
   list2 = nt4;

   std::cout << "List 2 contents:\n";
   listPrint(list2);

   result = listsAddReverse(list1, list2);
   std::cout << "Result of listsAddReverse:\n";
   listPrint(result);

   std::cout << "\n\n\n*******************\n***Test forward recursive solution\n*******************\n\n\n";

   n0 = new Node(0, 7);
   n1 = new Node(n0, 1);
   n2 = new Node(n1, 6);
   list1 = n2;

   std::cout << "List 1 contents:\n";
   listPrint(list1);

   nt0 = new Node(0, 5);
   nt1 = new Node(nt0, 9);
   nt2 = new Node(nt1, 2);
   list2 = nt2;

   std::cout << "List 2 contents:\n";
   listPrint(list2);

   result = listsAddForward(list1, list2);
   std::cout << "Result of listsAddForward:\n";
   listPrint(result);

   std::cout << "\n\n\n***Test when List 1 is bigger\n";

   n0 = new Node(0, 6);
   n1 = new Node(n0, 1);
   n2 = new Node(n1, 7);
   n3 = new Node(n2, 5);
   n4 = new Node(n3, 3);
   n5 = new Node(n4, 4);
   list1 = n5;

   std::cout << "List 1 contents:\n";
   listPrint(list1);

   nt0 = new Node(0, 2);
   nt1 = new Node(nt0, 9);
   nt2 = new Node(nt1, 5);
   list2 = nt2;

   std::cout << "List 2 contents:\n";
   listPrint(list2);

   result = listsAddForward(list1, list2);
   std::cout << "Result of listsAddForward:\n";
   listPrint(result);

   std::cout << "\n\n\n***Test when List 2 is bigger\n";

   n0 = new Node(0, 6);
   n1 = new Node(n0, 1);
   n2 = new Node(n1, 7);
   list1 = n2;

   std::cout << "List 1 contents:\n";
   listPrint(list1);

   nt0 = new Node(0, 2);
   nt1 = new Node(nt0, 9);
   nt2 = new Node(nt1, 5);
   nt3 = new Node(nt2, 1);
   nt4 = new Node(nt3, 1);
   list2 = nt4;

   std::cout << "List 2 contents:\n";
   listPrint(list2);

   result = listsAddForward(list1, list2);
   std::cout << "Result of listsAddForward:\n";
   listPrint(result);


   std::cout << "\n\n\n*******************\n***Test reverse recursive book solution\n*******************\n\n\n";

   n0 = new Node(0, 7);
   n1 = new Node(n0, 1);
   n2 = new Node(n1, 6);
   list1 = n2;

   std::cout << "List 1 contents:\n";
   listPrint(list1);

   nt0 = new Node(0, 5);
   nt1 = new Node(nt0, 9);
   nt2 = new Node(nt1, 2);
   list2 = nt2;

   std::cout << "List 2 contents:\n";
   listPrint(list2);

   result = listsAddReverseBookSolution(list1, list2, 0);
   std::cout << "Result of listsAddReverseBookSolution:\n";
   listPrint(result);

   std::cout << "\n\n\n***Test when List 1 is bigger\n";

   n0 = new Node(0, 6);
   n1 = new Node(n0, 1);
   n2 = new Node(n1, 7);
   n3 = new Node(n2, 5);
   n4 = new Node(n3, 3);
   n5 = new Node(n4, 4);
   list1 = n5;

   std::cout << "List 1 contents:\n";
   listPrint(list1);

   nt0 = new Node(0, 2);
   nt1 = new Node(nt0, 9);
   nt2 = new Node(nt1, 5);
   list2 = nt2;

   std::cout << "List 2 contents:\n";
   listPrint(list2);

   result = listsAddReverseBookSolution(list1, list2, 0);
   std::cout << "Result of listsAddReverseBookSolution:\n";
   listPrint(result);

   std::cout << "\n\n\n***Test when List 2 is bigger\n";

   n0 = new Node(0, 6);
   n1 = new Node(n0, 1);
   n2 = new Node(n1, 7);
   list1 = n2;

   std::cout << "List 1 contents:\n";
   listPrint(list1);

   nt0 = new Node(0, 2);
   nt1 = new Node(nt0, 9);
   nt2 = new Node(nt1, 5);
   nt3 = new Node(nt2, 1);
   nt4 = new Node(nt3, 1);
   list2 = nt4;

   std::cout << "List 2 contents:\n";
   listPrint(list2);

   result = listsAddReverseBookSolution(list1, list2, 0);
   std::cout << "Result of listsAddReverseBookSolution:\n";
   listPrint(result);

   std::cout << "\n\n\n*******************\n***Test forward recursive book solution\n*******************\n\n\n";

   n0 = new Node(0, 7);
   n1 = new Node(n0, 1);
   n2 = new Node(n1, 6);
   list1 = n2;

   std::cout << "List 1 contents:\n";
   listPrint(list1);

   nt0 = new Node(0, 5);
   nt1 = new Node(nt0, 9);
   nt2 = new Node(nt1, 2);
   list2 = nt2;

   std::cout << "List 2 contents:\n";
   listPrint(list2);

   result = listsAddForwardBookSolution(list1, list2);
   std::cout << "Result of listsAddForwardBookSolution:\n";
   listPrint(result);

   std::cout << "\n\n\n***Test when List 1 is bigger\n";

   n0 = new Node(0, 6);
   n1 = new Node(n0, 1);
   n2 = new Node(n1, 7);
   n3 = new Node(n2, 5);
   n4 = new Node(n3, 3);
   n5 = new Node(n4, 4);
   list1 = n5;

   std::cout << "List 1 contents:\n";
   listPrint(list1);

   nt0 = new Node(0, 2);
   nt1 = new Node(nt0, 9);
   nt2 = new Node(nt1, 5);
   list2 = nt2;

   std::cout << "List 2 contents:\n";
   listPrint(list2);

   result = listsAddForwardBookSolution(list1, list2);
   std::cout << "Result of listsAddForwardBookSolution:\n";
   listPrint(result);

   std::cout << "\n\n\n***Test when List 2 is bigger\n";

   n0 = new Node(0, 6);
   n1 = new Node(n0, 1);
   n2 = new Node(n1, 7);
   list1 = n2;

   std::cout << "List 1 contents:\n";
   listPrint(list1);

   nt0 = new Node(0, 2);
   nt1 = new Node(nt0, 9);
   nt2 = new Node(nt1, 5);
   nt3 = new Node(nt2, 1);
   nt4 = new Node(nt3, 1);
   list2 = nt4;

   std::cout << "List 2 contents:\n";
   listPrint(list2);

   result = listsAddForwardBookSolution(list1, list2);
   std::cout << "Result of listsAddForwardBookSolution:\n";
   listPrint(result);

   int k;
   std::cin >> k;
   return 0;
}

void listPrint(
   const Node* const printedList)
{
   const Node* current = printedList;
   while (current != 0)
   {
      std::cout << current->val << ", ";
      current = current->next;
   }
   std::cout << '\n';
}

Node* listsAddReverse(
   const Node* const l1,
   const Node* const l2)
{
   const Node* current1(l1);
   const Node* current2(l2);

   // Give head a dummie node to make looping easier.
   Node* head = new Node(0, 100);
   int carry(0);
   while (current1 != 0 && current2 != 0)
   {
      int newNodeVal((current1->val + current2->val + carry) % 10);
      carry = (current1->val + current2->val + carry) > 9 ? 1 : 0;
      Node* resultListCurrent(head);
      while (resultListCurrent->next != 0)
      {
         resultListCurrent = resultListCurrent->next;
      }

      resultListCurrent->next = new Node(0, newNodeVal);
      current1 = current1->next;
      current2 = current2->next;
   }

   // Handle case of lists being inequal length
   if (current1 != 0)
   {
      while (current1 != 0)
      {
         Node* resultListCurrent(head);
         while (resultListCurrent->next != 0)
         {
            resultListCurrent = resultListCurrent->next;
         }

         resultListCurrent->next = new Node(0, ((current1->val + carry) % 10));
         carry = (current1->val + carry) > 9 ? 1 : 0;
         current1 = current1->next;
      }
   }
   else if (current2 != 0)
   {
      while (current2 != 0)
      {
         Node* resultListCurrent(head);
         while (resultListCurrent->next != 0)
         {
            resultListCurrent = resultListCurrent->next;
         }

         resultListCurrent->next = new Node(0, ((current2->val + carry) % 10));
         carry = (current2->val + carry) > 9 ? 1 : 0;
         current2 = current2->next;
      }
   }

   // Get rid of dummie node
   Node* temp(head->next);
   delete head;
   head = temp;

   return head;
}

Node* listsAddForward(
   const Node* const l1,
   const Node* const l2)
{
   const Node* head1(l1);
   const Node* head2(l2);
   int carryUnused(0);

   Node* head = nextNodeAdd(head1, head2, carryUnused);

   return head;
}

Node* nextNodeAdd(
   const Node* const l1,
   const Node* const l2,
   int& carry)
{
   const Node* head1(l1);
   const Node* head2(l2);
   Node* nextNodeMade(0);
   int carryResult(0);

   // Handle getting to the end of either list
   if (head1 == 0 || head2 == 0)
   {
      if (head1 != 0)
      {
         carry = 0;
         nextNodeMade = nextNodeAdd(head1->next, 0, carryResult);
         int newNodeVal(head1->val);
         Node* addedNode = new Node(nextNodeMade, newNodeVal);

         return addedNode;
      }
      else if (head2 != 0)
      {
         carry = 0;
         nextNodeMade = nextNodeAdd(head2->next, 0, carryResult);
         int newNodeVal(head2->val);
         Node* addedNode = new Node(nextNodeMade, newNodeVal);

         return addedNode;
      }
      else
      {
         carry = 0;
         return nextNodeMade;
      }
   }

   nextNodeMade = nextNodeAdd(head1->next, head2->next, carryResult);
   carry = (head1->val + head2->val + carryResult) > 9 ? 1 : 0;

   int newNodeVal((head1->val + head2->val + carryResult) % 10);
   Node* addedNode = new Node(nextNodeMade, newNodeVal);

   return addedNode;
}

Node* listsAddReverseBookSolution(
   Node* l1,
   Node* l2,
   int carry)
{
   if (l1 == 0 && l2 == 0 && carry == 0)
   {
      return 0;
   }

   Node* result = new Node(0, 100);

   int value(carry);
   if (l1 != 0)
   {
      value += l1->val;
   }
   if (l2 != 0)
   {
      value += l2->val;
   }
   result->val = value % 10;

   if (l1 != 0 || l2 != 0)
   {
      Node* more = listsAddReverseBookSolution(
         (l1 == 0 ? 0 : l1->next),
         (l2 == 0 ? 0 : l2->next),
         (value >= 10 ? 1 : 0));

      result->next = more;
   }

   return result;
}

Node* listsAddForwardBookSolution(
   Node* l1,
   Node* l2)
{
   int length1(length(l1));
   int length2(length(l2));

   if (length1 < length2)
   {
      l1 = padList(l1, length2 - length1);
   }
   else if (length1 > length2)
   {
      l2 = padList(l2, length1 - length2);
   }

   PartialSum sum = helper(l1, l2);

   if (sum.carry == 0)
   {
      return sum.sum;
   }
   else
   {
      Node* result = insertBefore(sum.sum, sum.carry);
      return result;
   }
}

PartialSum helper(
   Node* l1,
   Node* l2)
{
   if (l1 == 0 && l2 == 0)
   {
      PartialSum sum;
      sum.sum = 0;
      sum.carry = 0;
      return sum;
   }

   PartialSum sum = helper(l1->next, l2->next);

   int val = sum.carry + l1->val + l2->val;

   Node* fullResult = insertBefore(sum.sum, val % 10);

   sum.sum = fullResult;
   sum.carry = val / 10;
   return sum;
}

Node* padList(
   Node* inputList,
   int padding)
{
   Node* head = inputList;
   for (int i = 0; i < padding; i++)
   {
      head = insertBefore(head, 0);
   }
   return head;
}

Node* insertBefore(
   Node* inputList,
   int data)
{
   Node* node = new Node(0, data);
   if (inputList != 0)
   {
      node->next = inputList;
   }
   return node;
}

int length(
   Node* inputList)
{
   int len(0);
   while (inputList != 0)
   {
      len++;
      inputList = inputList->next;
   }

   return len;
}