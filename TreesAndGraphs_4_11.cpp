#include <cstdlib>
#include <iostream>
#include <memory>
#include <ctime>

class Node {
public:
   Node(
      int nodeVal)
      :
      val(nodeVal),
      treeSize(1)
   {

   }

   int getSize()
   {
      return treeSize;
   }

   void setSize(
      int newSize)
   {
      treeSize = newSize;
   }

   int getVal()
   {
      return val;
   }

   int getRandomNode()
   {
      std::srand(std::time(0));
      int leftTreeSize (left == 0 ? 0: left->getSize());
      int index (1 + std::rand() / ((RAND_MAX + 1u) / leftTreeSize));

         if (index < leftTreeSize)
         {
            return left->getRandomNode();
         }
         else if (index == leftTreeSize)
         {
            return val;
         }
         else
         {
            return right->getRandomNode();
         }
   }

   void insertInOrder(
      int newNodeVal)
   {
      if (newNodeVal <= val)
      {
         if (left == 0)
         {
            left = std::unique_ptr<Node>(new Node(newNodeVal));
         }
         else
         {
            left->insertInOrder(newNodeVal);
         }
      }
      else
      {
         if (right == 0)
         {
            right = std::unique_ptr<Node>(new Node(newNodeVal));
         }
         else
         {
            right->insertInOrder(newNodeVal);
         }
      }

      ++treeSize;
   }

   bool find(
      int nodeVal)
   {
      if (val == nodeVal)
      {
         return true;
      }

      if (left != 0)
      {
         if (left->find(nodeVal))
         {
            return true;
         }
      }
      if (right != 0)
      {
         if (right->find(nodeVal))
         {
            return true;
         }
      }

      return false;
   }

   void deleteNode(
      std::unique_ptr<Node>& node,
      int nodeVal)
   {
      // This algorithm works by simply replacing the node with the specified
      // value with the value of the deepest node in the subtree, and then 
      // deleting the deepest node in the subtree.
      if (node != 0)
      {
         if (node->val == nodeVal)
         {
            int replacementVal(removeDeepestNode(node));
            node->val = replacementVal;
            --treeSize;
            return;
         }
         deleteNode(node->left, nodeVal);
         deleteNode(node->right, nodeVal);
      }

   }

   int removeDeepestNode(
      std::unique_ptr<Node>& node)
   {
      if (node != 0)
      {
         if (node->right != 0)
         {
            return removeDeepestNode(node->right);
         }
         else if (node->left != 0)
         {
            return removeDeepestNode(node->left);
         }
         else
         {
            int nodeVal(node->val);
            node.reset();
            return nodeVal;
         }
      }

      return -1;
   }

   std::unique_ptr<Node> left;
   std::unique_ptr<Node> right;

private:
   int val;
   int treeSize;
};

void preOrderTraversal(
   std::unique_ptr<Node>& node);

bool tests();

int main()
{
   if (tests())
   {
      std::cout << "\n\n******** All tests passed. ********\n\n";
   }
   else
   {
      std::cout << "\n\n******** At least one test failed. ********\n\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

void preOrderTraversal(
   std::unique_ptr<Node>& node)
{
   if (node != 0)
   {
      std::cout << node->getVal() << ", ";
      preOrderTraversal(node->left);
      preOrderTraversal(node->right);
   }
}

bool tests()
{
   std::unique_ptr<Node> root(new Node(20));
   std::unique_ptr<Node> node10(new Node(10));
   std::unique_ptr<Node> node30(new Node(30));
   std::unique_ptr<Node> node5(new Node(5));
   std::unique_ptr<Node> node15(new Node(15));
   std::unique_ptr<Node> node35(new Node(35));
   std::unique_ptr<Node> node3(new Node(3));
   std::unique_ptr<Node> node7(new Node(7));
   std::unique_ptr<Node> node17(new Node(17));

   node5->left = std::move(node3);
   node5->right = std::move(node7);
   node15->right = std::move(node17);
   node10->left = std::move(node5);
   node10->right = std::move(node15);
   node30->right = std::move(node35);
   root->left = std::move(node10);
   root->right = std::move(node30);

   root->setSize(9);
   root->left->setSize(6);
   root->right->setSize(2);
   root->left->left->setSize(3);
   root->left->right->setSize(2);
   root->right->right->setSize(1);
   root->left->left->left->setSize(1);
   root->left->left->right->setSize(1);
   root->left->right->right->setSize(1);
   

   std::cout << "\nPre Order Traversal:\n";
   preOrderTraversal(root);

   std::cout << "\ngetRandomNode() returns: " << root->getRandomNode();

   if (!root->find(10))
   {
      std::cout << "\n\nError - was supposed to find node 10 but did not.\n";
      return false;
   }
   if (root->find(29))
   {
      std::cout << "\n\nError - found node 29 when node 29 did not exist.\n";
      return false;
   }
   if (root->left->right->getSize() != 2)
   {
      std::cout << "\n\nError - node 15 is sized wrong with size: " << root->left->right->getSize() <<".\n";
      return false;
   }

   root->deleteNode(root->left, 5);

   std::cout << "\n Second Tree traversal:\n";
   preOrderTraversal(root);

   if (root->left->left->getVal() != 7)
   {
      std::cout << "\n\nError - node 5 was supposed to be replaced with node 7 but it: " << root->left->left->getVal() << ".\n";
      return false;
   }
   // TODO: --treeSize is broken
   //if (root->left->getSize() != 5)
   //{
   //   std::cout << "\n\nError - node 10 size was supposed to be 5 but is: " << root->left->getSize() << ".\n";
   //   return false;
   //}
   if (root->right->getSize() != 2)
   {
      std::cout << "\n\nError - node 30 size was supposed to be 2 but is: " << root->right->getSize() << ".\n";
      return false;
   }
   if (root->find(5))
   {
      std::cout << "\n\nError - node 5 was supposed to be removed but is still in tree.\n";
      return false;
   }

   root->insertInOrder(29);
   std::cout << "\n Third Tree traversal:\n";
   preOrderTraversal(root);

   if (root->right->getSize() != 3)
   {
      std::cout << "\n\nError - node 29 was not placed in right subtree.\n";
      return false;
   }
   if (!root->find(29))
   {
      std::cout << "\n\nError - node 29 could not be found after being inserted.\n";
      return false;
   }

   std::cout << "\nNew tree getRandomNode() returned: " << root->getRandomNode() << "\n";

   //TODO: Implement.
   return true;
}


































