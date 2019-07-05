#include <iostream>
#include <memory>
#include <vector>

struct ListNode {
   ListNode(
      int nodeVal,
      std::shared_ptr<ListNode> nextNode)
   :
   val(nodeVal),
   next(nextNode)
{
}

int val;
std::shared_ptr<ListNode> next;
};

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
// For practice and clarity, implement all three traversal functions.

void inOrderTraversal(
   std::shared_ptr<TreeNode> node);

void preOrderTraversal(
   std::shared_ptr<TreeNode> node);

void postOrderTraversal(
   std::shared_ptr<TreeNode> node);

// Now the algorithm for the actual practice problem.

void treeToListTraverse(
   std::shared_ptr<TreeNode> node,
   std::vector<std::shared_ptr<ListNode> >& resultVector,
   int& currentDepth);

void treeNodeToListAdd(
   std::shared_ptr<TreeNode> node,
   std::vector<std::shared_ptr<ListNode> >& resultVector,
   int& currentDepth);

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

// Note: Had to use shared_ptr for these. All the functions calls
//       pass by value - causing a pointer copy (which creates
//       shared ownership.)

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

void preOrderTraversal(
   std::shared_ptr<TreeNode> node)
{
   if (node != 0)
   {
      std::cout << node->val << " - ";
      preOrderTraversal(node->left);
      preOrderTraversal(node->right);
   }
}

void postOrderTraversal(
   std::shared_ptr<TreeNode> node)
{
   if (node != 0)
   {
      postOrderTraversal(node->left);
      postOrderTraversal(node->right);
      std::cout << node->val << " - ";
   }
}

// Note: Just ended up using shared ptrs for all the functions 
//       prototypes since so many of the arguments are pass by value.
//       And since the prototypes use shared ptrs the functions only
//       create shared ptrs in their bodies - for passing to the next
//       recursive pass by value call.

// Returning the vector by reference since each recursive call must
// modify it. I suppose I also could have made it the return argument
// and still have been able to modify it while passing it up and down
// the call stack.

void treeToListTraverse(
   std::shared_ptr<TreeNode> node,
   std::vector<std::shared_ptr<ListNode> >& resultVector,
   int& currentDepth)
{
   // Will always start by moving down a level.
   ++currentDepth;

   if (node != 0)
   {
      treeToListTraverse(node->left, resultVector, currentDepth);
      treeNodeToListAdd(node, resultVector, currentDepth);
      treeToListTraverse(node->right, resultVector, currentDepth);
   }

   // Always finish by moving up a level.
   --currentDepth;
}

void treeNodeToListAdd(
   std::shared_ptr<TreeNode> node,
   std::vector<std::shared_ptr<ListNode> >& resultVector,
   int& currentDepth)
{
   // Get a pointer to the end of the list entry. That is where
   // the new node goes.
   std::shared_ptr<ListNode> newNode(resultVector[currentDepth]);
   if (newNode == 0)
   {
      resultVector[currentDepth] = std::shared_ptr<ListNode>(new ListNode(node->val, 0));
   }
   else
   {
      while (newNode->next != 0)
      {
         newNode = newNode->next;
      }
      newNode->next = std::shared_ptr<ListNode>(new ListNode(node->val, 0));
   }
}

bool tests()
{
   // (1.) Create a tree.
   std::shared_ptr<TreeNode> root(new TreeNode(4));
   root->left = std::shared_ptr<TreeNode>(new TreeNode(7));
   root->right = std::shared_ptr<TreeNode>(new TreeNode(9));

   root->left->left = std::shared_ptr<TreeNode>(new TreeNode(2));
   root->left->right = std::shared_ptr<TreeNode>(new TreeNode(1));
   root->left->left->left = std::shared_ptr<TreeNode>(new TreeNode(5));
   root->left->left->left->left = std::shared_ptr<TreeNode>(new TreeNode(8));

   root->right->right = std::shared_ptr<TreeNode>(new TreeNode(6));

   // (2.) Print with each traversal function.
   std::cout << "In Order Traversal of first tree:\n";
   inOrderTraversal(root);
   std::cout << "\nPre Order Traversal of first tree:\n";
   preOrderTraversal(root);
   std::cout << "\nPost Order Traversal of first tree:\n";
   postOrderTraversal(root);

   // (3.) Get output vector.
   std::vector<std::shared_ptr<ListNode> > resultVector;
   // Cheating here - I know the depth of the list.  Could find this via traversal though.
   resultVector.resize(5);
   int currentDepth(-1);
   treeToListTraverse(root, resultVector, currentDepth);

   // (4.) Verify correct output vector entries.
   // We know expected size.

   if (resultVector[0]->val != 4)
   {
      std::cout << "Error, expected 4 but got: " << resultVector[0]->val << "\n";
      return false;
   }
   if (resultVector[0]->next != 0)
   {
      std::cout << "Error, first list in vector should only have one entry but has more than one.\n";
      return false;
   }

   if (resultVector[1]->val != 7)
   {
      std::cout << "Error, expected 7 but got: " << resultVector[1]->val << "\n";
      return false;
   }
   if (resultVector[1]->next->val != 9)
   {
      std::cout << "Error, expected 9 but got: " << resultVector[1]->next->val << "\n";
      return false;
   }
   if (resultVector[1]->next->next != 0)
   {
      std::cout << "Error, second list in vector should only have two entries but has more than two.\n";
      return false;
   }

   if (resultVector[2]->val != 2)
   {
      std::cout << "Error, expected 2 but got: " << resultVector[2]->val << "\n";
      return false;
   }
   if (resultVector[2]->next->val != 1)
   {
      std::cout << "Error, expected 1 but got: " << resultVector[2]->next->val << "\n";
      return false;
   }
   if (resultVector[2]->next->next->val != 6)
   {
      std::cout << "Error, expected 6 but got: " << resultVector[2]->next->next->val << "\n";
      return false;
   }
   if (resultVector[2]->next->next->next != 0)
   {
      std::cout << "Error, third list in vector should only have three entries but has more than three.\n";
      return false;
   }

   if (resultVector[3]->val != 5)
   {
      std::cout << "Error, expected 5 but got: " << resultVector[3]->val << "\n";
      return false;
   }
   if (resultVector[3]->next != 0)
   {
      std::cout << "Error, fourth list in vector should only have one entry but has more than one.\n";
      return false;
   }

   if (resultVector[4]->val != 8)
   {
      std::cout << "Error, expected 8 but got: " << resultVector[4]->val << "\n";
      return false;
   }
   if (resultVector[4]->next != 0)
   {
      std::cout << "Error, fifth list in vector should only have one entry but has more than one.\n";
      return false;
   }

   return true;
}






