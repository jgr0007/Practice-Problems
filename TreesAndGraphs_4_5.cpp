#include <iostream>
#include <memory>
#include <vector>

struct Node {
   Node(
      int nodeVal)
      :
      val(nodeVal)
   {
   }

   int val;
   std::shared_ptr<Node> left;
   std::shared_ptr<Node> right;
};

void preOrderTraversal(
   std::shared_ptr<Node> node);

void postOrderTraversal(
   std::shared_ptr<Node> node);

bool isBinarySearchTree(
   std::shared_ptr<Node> node);

void nodeAddToVector(
   std::shared_ptr<Node> node,
   std::vector<int>& resultVector);

bool tests();

int main()
{
   if (tests())
   {
      std::cout << "\n\n******** All tests passed. ********\n";
   }
   else
   {
      std::cout << "\n\n******** At least one test failed. ********\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

void preOrderTraversal(
   std::shared_ptr<Node> node)
{
   if (node != 0)
   {
      std::cout << node->val << " - ";
      preOrderTraversal(node->left);
      preOrderTraversal(node->right);
   }
}

void postOrderTraversal(
   std::shared_ptr<Node> node)
{
   if (node != 0)
   {
      postOrderTraversal(node->left);
      postOrderTraversal(node->right);
      std::cout << node->val << " - ";
   }
}

// Note: The book points out we don't actually need a vector to store
//       the tree to here.  We can just keep of our most recently
//       visited node during the traversal and make sure the In Order
//       traversal keeps a strictly ascending order (which is what
//       the code currently uses the vector for).

bool isBinarySearchTree(
   std::shared_ptr<Node> node)
{
   std::vector<int> resultVector;
   nodeAddToVector(node, resultVector);

   int previousValue = resultVector[0];
   for (unsigned int index = 1; index <= resultVector.size() - 1; index++)
   {
      if (previousValue > resultVector[index])
      {
         return false;
      }
      previousValue = resultVector[index];
   }

   return true;
}

void nodeAddToVector(
   std::shared_ptr<Node> node,
   std::vector<int>& resultVector)
{
   if (node != 0)
   {
      nodeAddToVector(node->left, resultVector);
      resultVector.push_back(node->val);
      nodeAddToVector(node->right, resultVector);
   }
}

bool tests()
{
   std::shared_ptr<Node> root(new Node(17));
   root->left = std::shared_ptr<Node>(new Node(11));
   root->right = std::shared_ptr<Node>(new Node(25));
   root->left->left = std::shared_ptr<Node>(new Node(8));
   root->left->right = std::shared_ptr<Node>(new Node(16));
   root->left->right->left = std::shared_ptr<Node>(new Node(13));

   if (!isBinarySearchTree(root))
   {
      std::cout << "Error - first binary tree found not to be binary search tree.\n";
      return false;
   }

   std::shared_ptr<Node> root2(new Node(9));
   root2->left = std::shared_ptr<Node>(new Node(6));
   root2->right = std::shared_ptr<Node>(new Node(17));
   root2->left->left = std::shared_ptr<Node>(new Node(1));
   root2->left->right = std::shared_ptr<Node>(new Node(11));

   if (isBinarySearchTree(root2))
   {
      std::cout << "Error - second binary tree found to be binary search tree.\n";
      return false;
   }

   return true;
}