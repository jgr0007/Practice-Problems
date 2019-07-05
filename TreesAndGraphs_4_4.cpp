#include <iostream>
#include <memory>

struct TreeNode {
   TreeNode(
      int nodeVal)
      :
      val(nodeVal)
   {
   }

   int val;
   std::shared_ptr<TreeNode> left;
   std::shared_ptr<TreeNode> right;
};

void inOrderTraversal(
   std::shared_ptr<TreeNode> node);

bool isBalanced(
   std::shared_ptr<TreeNode> node,
   int& currentDepth);

bool test1();

bool test2();

bool test3();

bool test4();

int main()
{
   if (test1() &&
      test2() &&
      test3() &&
      test4())
   {
      std::cout << "\n\n******** All tests passed. ********\n";
   }
   else
   {
      std::cout << "\n\n******** At least one test failed. ********\n";
   }

   int j;
   std::cin >> j;
   return 0;
}

void inOrderTraversal(
   std::shared_ptr<TreeNode> node)
{
   if (node != 0)
   {
      inOrderTraversal(node->left);
      std::cout << node->val << " - ";
      inOrderTraversal(node->right);
   }
}

bool isBalanced(
   std::shared_ptr<TreeNode> node,
   int& currentDepth)
{
   if (node != 0)
   {
      int leftDepth;
      int rightDepth;

      if (isBalanced(node->left, leftDepth))
      {

      }
      else
      {
         std::cout << "Simply returning false up the stack for an unbalanced left tree.\n";
         return false;
      }

      if (isBalanced(node->right, rightDepth))
      {
         
      }
      else
      {
         std::cout << "Simply returning false up the stack for an unbalanced right tree.\n";
         return false;
      }

      std::cout << "Node: " << node->val << " comparing leftDepth of: " << leftDepth << " to rightDepth of: " << rightDepth << ".\n";
      if (leftDepth - rightDepth > 1 || rightDepth - leftDepth > 1)
      {
         std::cout << "Unbalanced tree found for node: " << node->val << " where left tree depth is: " << leftDepth << " and right tree depth is: " << rightDepth << "\n";
         return false;
      }
      else
      {
         // Parent tree needs depth for comparison
         if (leftDepth > rightDepth)
         {
            currentDepth = leftDepth + 1;
         }
         else
         {
            currentDepth = rightDepth + 1;
         }
         std::cout << "Node: " << node->val << " setting currentDepth to: " << currentDepth << "\n";
      }
   }
   else
   {
      currentDepth = -1;
   }

   return true;
}

bool test1()
{
   // Make a tree
   std::shared_ptr<TreeNode> root(new TreeNode(4));

   root->left = std::shared_ptr<TreeNode>(new TreeNode(5));
   root->right = std::shared_ptr<TreeNode>(new TreeNode(1));

   root->left->left = std::shared_ptr<TreeNode>(new TreeNode(2));
   root->right->left = std::shared_ptr<TreeNode>(new TreeNode(3));
   root->right->right = std::shared_ptr<TreeNode>(new TreeNode(7));

   // Print the tree in order to make sure it was constructed correctly.
   std::cout << "Printing tree in order for sanity check:\n";
   inOrderTraversal(root);
   std::cout << "\n";

   // Check the algorithm.
   int depth(0);
   if (!isBalanced(root, depth))
   {
      std::cout << "Error - tree for tests1 found to not be balanced.\n";
      return false;
   }

   return true;
}

bool test2()
{
   std::shared_ptr<TreeNode> root(new TreeNode(92));

   root->left = std::shared_ptr<TreeNode>(new TreeNode(14));
   root->right = std::shared_ptr<TreeNode>(new TreeNode(17));

   root->left->left = std::shared_ptr<TreeNode>(new TreeNode(18));
   root->left->left->left = std::shared_ptr<TreeNode>(new TreeNode(5));
   root->left->right = std::shared_ptr<TreeNode>(new TreeNode(62));

   std::cout << "Printing tree in order for sanity check:\n";
   inOrderTraversal(root);
   std::cout << "\n";

   int depth(0);
   if (isBalanced(root, depth))
   {
      std::cout << "Error - tree for tests2 found to be balanced.\n";
      return false;
   }

   return true;
}

bool test3()
{
   std::shared_ptr<TreeNode> root(new TreeNode(2));

   root->left = std::shared_ptr<TreeNode>(new TreeNode(8));
   root->left->left = std::shared_ptr<TreeNode>(new TreeNode(4));
   root->left->left->right = std::shared_ptr<TreeNode>(new TreeNode(6));

   root->right = std::shared_ptr<TreeNode>(new TreeNode(13));
   root->right->left = std::shared_ptr<TreeNode>(new TreeNode(16));
   root->right->right = std::shared_ptr<TreeNode>(new TreeNode(5));

   std::cout << "Printing tree in order for sanity check:\n";
   inOrderTraversal(root);
   std::cout << "\n";
   
   int depth(0);
   if (isBalanced(root, depth))
   {
      std::cout << "Error - tree for tests3 found to be balanced.\n";
      return false;
   }

   return true;
}

bool test4()
{
   std::shared_ptr<TreeNode> root(new TreeNode(8));

   root->left = std::shared_ptr<TreeNode>(new TreeNode(9));
   root->left->left = std::shared_ptr<TreeNode>(new TreeNode(17));

   root->right = std::shared_ptr<TreeNode>(new TreeNode(4));
   root->right = std::shared_ptr<TreeNode>(new TreeNode(31));

   std::cout << "Printing tree in order for sanity check:\n";
   inOrderTraversal(root);
   std::cout << "\n";

   int depth(0);
   if (!isBalanced(root, depth))
   {
      std::cout << "Error - tree for tests4 found to not be balanced.\n";
      return false;
   }

   return true;
}






