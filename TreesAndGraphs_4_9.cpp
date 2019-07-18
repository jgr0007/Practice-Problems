#include <iostream>
#include <list>
#include <memory>
#include <vector>

// This solution is just copied from the book's java code.  
// Could not figure this one out without the solution.

struct Node {
   Node(
      int nodeVal)
      :
      val(nodeVal)
   {

   }

   int val;
   std::unique_ptr<Node> left;
   std::unique_ptr<Node> right;
};

std::vector<std::list<int> > generateSequenceFromTree(
   std::unique_ptr<Node>& node);

void weaveLists(
   std::list<int> firstList,
   std::list<int> secondList,
   std::vector<std::list<int> >& results,
   std::list<int> prefix);

void treePrintPreOrder(
   std::unique_ptr<Node const>& node);

void treePrintInOrder(
   std::unique_ptr<Node const>& node);

void treePrintPostOrder(
   std::unique_ptr<Node const>& node);

void listPrint(
   std::list<int>& node);

bool test1();

bool test2();

bool test3();

int main()
{
   if (test1() &&
      test2() &&
      test3())
   {
      std::cout << "******** All tests passed. ********\n";
   }
   else
   {
      std::cout << "******** At least one test failed. ********\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

std::vector<std::list<int> > generateSequenceFromTree(
   std::unique_ptr<Node>& node)
{
   std::vector<std::list<int> > result;

   // Handle base case
   if (node == 0)
   {
      std::list<int> resultList;
      result.push_back(resultList);
      return result;
   }

   std::list<int> prefix;
   prefix.push_back(node->val);

   // Traverse post order
   std::vector<std::list<int> > leftSequence(generateSequenceFromTree(node->left));
   std::vector<std::list<int> > rightSequence(generateSequenceFromTree(node->right));

   // Weave left and right subtree lists together.
   for (auto left = leftSequence.begin(); left != leftSequence.end(); ++left)
   {
      for (auto right = rightSequence.begin(); right != rightSequence.end(); ++right)
      {
         std::vector<std::list<int> > weaved;
         weaveLists(*left, *right, weaved, prefix);
         result.insert(result.end(), weaved.begin(), weaved.end());
      }
   }

   return result;
}

// - From the book.
// This function weaves lists together in all possible ways.  This algorithm works
// by removing the head from one list, recursing, and then doing the same with the 
// other list.

void weaveLists(
   std::list<int> firstList,
   std::list<int> secondList,
   std::vector<std::list<int> >& results,
   std::list<int> prefix)
{
   // If one list is empty, add remainder to (a cloned) prefix and store the result.
   if (firstList.empty() || secondList.empty())
   {
      std::list<int> result(prefix.begin(), prefix.end());
      result.insert(result.end(), firstList.begin(), firstList.end());
      result.insert(result.end(), secondList.begin(), secondList.end());
      results.push_back(result);
      return;
   }

   // Recurse with head of first added to the prefix. Removing the head changes
   // first, so the head needs to be put back in first for other functions after 
   // this is done.
   int headFirst(firstList.front());
   firstList.pop_front();
   prefix.push_back(headFirst);
   weaveLists(firstList, secondList, results, prefix);
   prefix.pop_back();
   firstList.push_front(headFirst);

   // Recurse with head of second added to the prefix. Removing the head changes
   // second, so the head needs to be put back in second for other functions 
   // after this is done.
   int headSecond(secondList.front());
   secondList.pop_front();
   prefix.push_back(headSecond);
   weaveLists(firstList, secondList, results, prefix);
   prefix.pop_back();
   secondList.push_front(headSecond);
}

void treePrintPreOrder(
   std::unique_ptr<Node>& node)
{
   if (node != 0)
   {
      treePrintPreOrder(node->left);
      std::cout << node->val << ", ";
      treePrintPreOrder(node->right);
   }
}

void treePrintInOrder(
   std::unique_ptr<Node>& node)
{
   if (node != 0)
   {
      std::cout << node->val << ", ";
      treePrintInOrder(node->left);
      treePrintInOrder(node->right);
   }
}

void treePrintPostOrder(
   std::unique_ptr<Node>& node)
{
   if (node != 0)
   {
      treePrintPostOrder(node->left);
      treePrintPostOrder(node->right);
      std::cout << node->val << ", ";
   }
}

void listPrint(
   std::list<int>& inputList)
{
   for (auto iter = inputList.begin(); iter != inputList.end(); ++iter)
   {
      std::cout << *iter << ", ";
   }
   std::cout << "\n";
}

bool test1()
{
   std::cout << "\n\nBeginning Test 1:\n\n";

   std::unique_ptr<Node> root(new Node(2));
   std::unique_ptr<Node> node1(new Node(1));
   std::unique_ptr<Node> node3(new Node(3));

   root->left = std::move(node1);
   root->right = std::move(node3);

   std::cout << "Printing tree to confirm structure:\n\n";
   std::cout << "Pre Order Traversal:\n";
   treePrintPreOrder(root);
   std::cout << "\nIn Order Traversal:\n";
   treePrintInOrder(root);
   std::cout << "\nPost Order Traversal:\n";
   treePrintPostOrder(root);


   std::vector<std::list<int> > resultTest1(generateSequenceFromTree(root));
   std::cout << "\nPrinting output lists to verify correctness:\n\n";

   for (auto iter = resultTest1.begin(); iter != resultTest1.end(); ++iter)
   {
      listPrint(*iter);
   }

   return true;
}

bool test2()
{
   std::cout << "\n\nBeginning Test 2:\n\n";

   std::unique_ptr<Node> root(new Node(1));
   std::unique_ptr<Node> node2(new Node(2));
   std::unique_ptr<Node> node3(new Node(3));

   node2->right = std::move(node3);
   root->right = std::move(node2);

   std::cout << "Printing tree to confirm structure:\n\n";
   std::cout << "Pre Order Traversal:\n";
   treePrintPreOrder(root);
   std::cout << "\nIn Order Traversal:\n";
   treePrintInOrder(root);
   std::cout << "\nPost Order Traversal:\n";
   treePrintPostOrder(root);

   std::vector<std::list<int> > resultTest2(generateSequenceFromTree(root));
   std::cout << "\nPrinting output lists to verify correctness:\n\n";

   for (auto iter = resultTest2.begin(); iter != resultTest2.end(); ++iter)
   {
      listPrint(*iter);
   }

   return true;
}

bool test3()
{
   std::cout << "\n\nBeginning Test 3:\n\n";

   std::unique_ptr<Node> root(new Node(5));
   std::unique_ptr<Node> node1(new Node(1));
   std::unique_ptr<Node> node7(new Node(7));
   std::unique_ptr<Node> node4(new Node(4));
   std::unique_ptr<Node> node6(new Node(6));
   std::unique_ptr<Node> node9(new Node(9));
   std::unique_ptr<Node> node11(new Node(11));

   node9->right = std::move(node11);
   node7->right = std::move(node9);
   node7->left = std::move(node6);
   node1->right = std::move(node4);
   root->right = std::move(node7);
   root->left = std::move(node1);

   std::cout << "Printing tree to confirm structure:\n\n";
   std::cout << "Pre Order Traversal:\n";
   treePrintPreOrder(root);
   std::cout << "\nIn Order Traversal:\n";
   treePrintInOrder(root);
   std::cout << "\nPost Order Traversal:\n";
   treePrintPostOrder(root);

   std::vector<std::list<int> > resultTest3(generateSequenceFromTree(root));
   std::cout << "\nPrinting output lists to verify correctness:\n\n";

   for (auto iter = resultTest3.begin(); iter != resultTest3.end(); ++iter)
   {
      listPrint(*iter);
   }

   return true;
}

























