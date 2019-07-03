#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

struct Node {
   Node(int nodeVal)
      :
      val(nodeVal)
   {
   }

   int val;
   std::vector<std::shared_ptr<Node> > m_children;
};

void printTreeInOrder(
   std::shared_ptr<Node> node);

void printTreePreOrder(
   std::shared_ptr<Node> node);

void printTreePostOrder(
   std::shared_ptr<Node> node);

std::shared_ptr<Node> makeTree(
   std::vector<int> sortedArray);

bool tests();

int main()
{
   if (tests())
   {
      std::cout << "\n\n*********Passed all tests.\n";
   }
   else
   {
      std::cout << "\n\n*********At least one test failed.\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

void printTreeInOrder(
   std::shared_ptr<Node> node) 
{
   // Traverse In Order
   if (node != 0)
   {
      std::cout << "\n - ";
      printTreeInOrder(node->m_children[0]);
      std::cout << node->val << " - ";
      printTreeInOrder(node->m_children[1]);
   }
}

void printTreePreOrder(
   std::shared_ptr<Node> node)
{
   // Traverse Pre Order
   if (node != 0)
   {
      std::cout << "\n - ";
      std::cout << node->val << " - ";
      printTreePreOrder(node->m_children[0]);
      printTreePreOrder(node->m_children[1]);
   }
}

void printTreePostOrder(
   std::shared_ptr<Node> node)
{
   // Traverse Pre Order
   if (node != 0)
   {
      std::cout << "\n - ";
      printTreePostOrder(node->m_children[0]);
      printTreePostOrder(node->m_children[1]);
      std::cout << node->val << " - ";
   }
}

std::shared_ptr<Node> makeTree(
   std::vector<int> sortedArray)
{
   // Base Case
   if (sortedArray.size() == 0)
   {
      return 0;
   }

   int vectorMidPoint(sortedArray.size() / 2); // This results in us always using right-of-middle element in vectors of even length.
   std::shared_ptr<Node> childNode(new Node(sortedArray[vectorMidPoint]));

   childNode->m_children.resize(2);

   std::vector<int> subArrayLeft(sortedArray.begin(), sortedArray.begin() + sortedArray.size() / 2);
   std::vector<int> subArrayRight(sortedArray.begin() + sortedArray.size() / 2 + 1, sortedArray.end());

   // Copy right here.  This could be optimized.
   childNode->m_children[0] = makeTree(subArrayLeft);
   childNode->m_children[1] = makeTree(subArrayRight);

   return childNode;
}

bool tests()
{
   std::vector<int> testVector{ 1,3,4,7,10,11,15,19 };
   std::shared_ptr<Node> returnedTree(makeTree(testVector));

   std::cout << "Printing tree InOrder:\n";
   printTreeInOrder(returnedTree);
   std::cout << "\n Now printing tree PreOrder:\n";
   printTreePreOrder(returnedTree);
   std::cout << "\n Now printing tree PostOrder:\n";
   printTreePostOrder(returnedTree);

   return false;
}




