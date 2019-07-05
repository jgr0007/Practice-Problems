#include <iostream>
#include <memory>

struct Node {
   Node(
      int nodeVal)
      :
      val(nodeVal)
   {
   }

   int val;
   std::shared_ptr<Node> parent;
   std::shared_ptr<Node> left;
   std::shared_ptr<Node> right;
};

void inOrderTraverse(
   std::shared_ptr<Node> node);

void preOrderTraverse(
   std::shared_ptr<Node> node);

void postOrderTraverse(
   std::shared_ptr<Node> node);

int nextNodeFind(
   std::shared_ptr<Node> node);

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

void inOrderTraverse(
   std::shared_ptr<Node> node)
{
   if (node != 0)
   {
      inOrderTraverse(node->left);
      std::cout << node->val << " - ";
      inOrderTraverse(node->right);
   }
}

void preOrderTraverse(
   std::shared_ptr<Node> node)
{
   if (node != 0)
   {
      std::cout << node->val << " - ";
      preOrderTraverse(node->left);
      preOrderTraverse(node->right);
   }
}

void postOrderTraverse(
   std::shared_ptr<Node> node)
{
   if (node != 0)
   {
      postOrderTraverse(node->left);
      postOrderTraverse(node->right);
      std::cout << node->val << " - ";
   }
}

int nextNodeFind(
   std::shared_ptr<Node> node)
{
   // If node has a right child, print the leftmost node in that child's subtree.
   if (node->right != 0)
   {
      node = node->right;
      while (node->left != 0)
      {
         node = node->left;
      }

      return node->val;
   }

   // Else if current node is its parent's left child, print the parent.
   else if (node->parent->left->val == node->val)
   {
      return node->parent->val;
   }

   // Else traverse up tree until you find a node who is a left node or
   // until you are at a node whose parent is null (in which case you 
   // are at the root).
   else
   {
      while (node->parent != 0)
      {
         node = node->parent;

         // Put in a root check here so that the next if statement 
         // can't accidentally index a null ptr while at the root 
         // node.
         if (node->parent == 0)
         {
            // This can only be the root, and if we arrive at the root  
            // of the tree from the right, there is no succeeding node 
            // to find. In this case, simply return -1.
            return -1;
         }

         // If a parent is found who is a left node, print that that
         // left node's parent.
         if (node->parent->left->val == node->val)
         {
            return node->parent->val;
         }
      }

      // Won't get here because first if check inside the while loop 
      // takes care of it, but putting a return here to get rid of 
      // the compiler warning.
      return -1;
   }
}

bool tests()
{
   std::shared_ptr<Node> root(new Node(13));
   root->left = std::shared_ptr<Node>(new Node(3));
   root->left->left = std::shared_ptr<Node>(new Node(1));
   root->left->right = std::shared_ptr<Node>(new Node(8));
   root->left->right->left = std::shared_ptr<Node>(new Node(5));
   root->left->right->left->right = std::shared_ptr<Node>(new Node(6));
   root->right = std::shared_ptr<Node>(new Node(29));
   root->right->left = std::shared_ptr<Node>(new Node(27));
   root->right->right = std::shared_ptr<Node>(new Node(32));

   // Now connect each child to its parent.
   root->left->parent = root;
   root->left->left->parent = root->left;
   root->left->right->parent = root->left;
   root->left->right->left->parent = root->left->right;
   root->left->right->left->right->parent = root->left->right->left;
   root->right->parent = root;
   root->right->left->parent = root->right;
   root->right->right->parent = root->right;

   std::cout << "\nPrinting tree in order:\n";
   inOrderTraverse(root);
   std::cout << "\n";

   std::cout << "\nPrinting tree pre order:\n";
   preOrderTraverse(root);
   std::cout << "\n";

   std::cout << "\nPrinting tree post order:\n";
   postOrderTraverse(root);
   std::cout << "\n";

   int result1(nextNodeFind(root->left));
   if (result1 != 5)
   {
      std::cout << "Error - expected result1 to be 5 but got: " << result1 << "\n";
      return false;
   }

   int result2(nextNodeFind(root->right->left));
   if (result2 != 29)
   {
      std::cout << "Error - expected result2 to be 29 but got: " << result2 << "\n";
      return false;
   }

   int result3(nextNodeFind(root->left->right->left));
   if (result3 != 6)
   {
      std::cout << "Error - expected result3 to be 6 but got: " << result3 << "\n";
      return false;
   }

   int result4(nextNodeFind(root->right->right));
   if (result4 != -1)
   {
      std::cout << "Error - expected result4 to be -1 but got: " << result4 << "\n";
      return false;
   }



   return true;
}









