#include <iostream>
#include <memory>

struct NodeWithParent {
   NodeWithParent(
      int nodeVal)
      :
      val(nodeVal)
   {
   }

   int val;
   std::shared_ptr<NodeWithParent> parent;
   std::shared_ptr<NodeWithParent> left;
   std::shared_ptr<NodeWithParent> right;
};

struct NodeNoParent {
   NodeNoParent(
      int nodeVal)
      :
      val(nodeVal)
   {
   }

   int val;
   std::shared_ptr<NodeNoParent> left;
   std::shared_ptr<NodeNoParent> right;
};

void treePrintPreOrder(
   std::shared_ptr<NodeWithParent> node);

void treePrintPreOrder(
   std::shared_ptr<NodeNoParent> node);

void treePrintInOrder(
   std::shared_ptr<NodeWithParent> node);

void treePrintInOrder(
   std::shared_ptr<NodeNoParent> node);

void treePrintPostOrder(
   std::shared_ptr<NodeWithParent> node);

void treePrintInOrder(
   std::shared_ptr<NodeNoParent> node);

std::shared_ptr<NodeWithParent> intersectionFind(
   std::shared_ptr<NodeWithParent> p1,
   std::shared_ptr<NodeWithParent> p2);

int deeperNodeFind(
   std::shared_ptr<NodeWithParent> p1,
   std::shared_ptr<NodeWithParent> p2,
   bool& p1WasDeeper,
   bool& p2WasDeeper);

std::shared_ptr<NodeWithParent> firstCommonAncestorFindUsingParents(
   std::shared_ptr<NodeWithParent> p1,
   std::shared_ptr<NodeWithParent> p2);

std::shared_ptr<NodeNoParent> firstCommonAncestorFindPostOrderTraversal(
   std::shared_ptr<NodeNoParent> root,
   std::shared_ptr<NodeNoParent> p1,
   std::shared_ptr<NodeNoParent> p2);

std::shared_ptr<NodeNoParent> commonAncestorFind(
   std::shared_ptr<NodeNoParent> node,
   std::shared_ptr<NodeNoParent> p1,
   std::shared_ptr<NodeNoParent> p2,
   bool& isP1Ancestor,
   bool& isP2Ancestor,
   bool& firstCommonAncestorWasFound);

bool test1();

bool test2();

int main()
{
   if (test1() && test2())
   {
      std::cout << "\n\n********* All tests passed.\n";
   }
   else
   {
      std::cout << "\n\n********* At least one test failed.\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

void treePrintPreOrder(
   std::shared_ptr<NodeWithParent> node)
{
   if (node != 0)
   {
      std::cout << node->val << ", ";
      treePrintPreOrder(node->left);
      treePrintPreOrder(node->right);
   }
}

void treePrintPreOrder(
   std::shared_ptr<NodeNoParent> node)
{
   if (node != 0)
   {
      std::cout << node->val << ", ";
      treePrintPreOrder(node->left);
      treePrintPreOrder(node->right);
   }
}

void treePrintInOrder(
   std::shared_ptr<NodeWithParent> node)
{
   if (node != 0)
   {
      treePrintInOrder(node->left);
      std::cout << node->val << ", ";
      treePrintInOrder(node->right);
   }
}

void treePrintInOrder(
   std::shared_ptr<NodeNoParent> node)
{
   if (node != 0)
   {
      treePrintInOrder(node->left);
      std::cout << node->val << ", ";
      treePrintInOrder(node->right);
   }
}

void treePrintPostOrder(
   std::shared_ptr<NodeWithParent> node)
{
   if (node != 0)
   {
      treePrintPostOrder(node->left);
      treePrintPostOrder(node->right);
      std::cout << node->val << ", ";
   }
}
void treePrintPostOrder(
   std::shared_ptr<NodeNoParent> node)
{
   if (node != 0)
   {
      treePrintPostOrder(node->left);
      treePrintPostOrder(node->right);
      std::cout << node->val << ", ";
   }
}

std::shared_ptr<NodeWithParent> intersectionFind(
   std::shared_ptr<NodeWithParent> p1,
   std::shared_ptr<NodeWithParent> p2)
{
   // Hack so that if Node A is the parent of Node B,
   // the code will return the parent of Node A rather
   // than Node A itself.
   p1 = p1->parent;
   p2 = p2->parent;

   while (p1 != p2)
   {
      p1 = p1->parent;
      p2 = p2->parent;
   }

   std::cout << "Intersection found at node: " << p1->val << ".\n";
   return p1;
}

int deeperNodeFind(
   std::shared_ptr<NodeWithParent> p1,
   std::shared_ptr<NodeWithParent> p2,
   bool& p1WasDeeper,
   bool& p2WasDeeper)
{
   int p1Height(0);
   int p2Height(0);
   int heightDifference(0);

   std::shared_ptr<NodeWithParent> p1HeightChecker(p1);
   std::shared_ptr<NodeWithParent> p2HeightChecker(p2);

   while (p1HeightChecker->parent != 0)
   {
      p1HeightChecker = p1HeightChecker->parent;
      ++p1Height;
   }
   while (p2HeightChecker->parent != 0)
   {
      p2HeightChecker = p2HeightChecker->parent;
      ++p2Height;
   }

   if (p1Height > p2Height)
   {
      std::cout << "\np1: " << p1->val << " was deeper.\n";
      p1WasDeeper = true;
      heightDifference = p1Height - p2Height;
   }
   else if (p2Height > p1Height)
   {
      std::cout << "\np2: " << p2->val << " was deeper.\n";
      p2WasDeeper = true;
      heightDifference = p2Height - p1Height;
   }

   std::cout << "Calculated height difference: " << heightDifference << ".\n";
   return heightDifference;
}

std::shared_ptr<NodeWithParent> firstCommonAncestorFindUsingParents(
   std::shared_ptr<NodeWithParent> p1,
   std::shared_ptr<NodeWithParent> p2)
{
   // This check proves that the needs have a common ancestor because the 
   // problem assumes that there is only one input tree. So either there 
   // is a common ancestor, or one of the nodes is null.
   if (p1 == 0 || p2 == 0)
   {
      return 0;
   }

   // A root node does not have any ancestors and therefor cannot have
   // a common ancestor with any nodes/
   if (p1->parent == 0 || p2->parent == 0)
   {
      return 0;
   }

   bool p1WasDeeper(false);
   bool p2WasDeeper(false);
   int heightDifference(deeperNodeFind(p1, p2, p1WasDeeper, p2WasDeeper));

   std::shared_ptr<NodeWithParent> firstCommonAncestor;
   std::shared_ptr<NodeWithParent> adjustedNode;
   if (p1WasDeeper)
   {
      adjustedNode = p1;
      for (int heightAdustments = 0; heightAdustments < heightDifference; ++heightAdustments)
      {
         adjustedNode = adjustedNode->parent;
      }

      firstCommonAncestor = intersectionFind(adjustedNode, p2);
   }
   else if (p2WasDeeper)
   {
      adjustedNode = p2;
      for (int heightAdustments = 0; heightAdustments < heightDifference; ++heightAdustments)
      {
         adjustedNode = adjustedNode->parent;
      }

      firstCommonAncestor = intersectionFind(p1, adjustedNode);
   }
   else
   {
      firstCommonAncestor = intersectionFind(p1, p2);
   }

   return firstCommonAncestor;
}

std::shared_ptr<NodeNoParent> firstCommonAncestorFindPostOrderTraversal(
   std::shared_ptr<NodeNoParent> root,
   std::shared_ptr<NodeNoParent> p1,
   std::shared_ptr<NodeNoParent> p2)
{
   if (p1 == 0 || p2 == 0)
   {
      return 0;
   }
   if (p1 == root || p2 == root)
   {
      return 0;
   }

   bool isP1Ancestor(false);
   bool isP2Ancestor(false);
   bool firstCommonAncestorWasFound(false);

   std::shared_ptr<NodeNoParent> firstCommonAncestor(commonAncestorFind(root, p1, p2, isP1Ancestor, isP2Ancestor, firstCommonAncestorWasFound));

   return firstCommonAncestor;
}

std::shared_ptr<NodeNoParent> commonAncestorFind(
   std::shared_ptr<NodeNoParent> node,
   std::shared_ptr<NodeNoParent> p1,
   std::shared_ptr<NodeNoParent> p2,
   bool& isP1Ancestor,
   bool& isP2Ancestor,
   bool& firstCommonAncestorWasFound)
{
   if (node != 0)
   {
      if (isP1Ancestor && isP2Ancestor)
      {
         return node;
      }

      std::shared_ptr<NodeNoParent> possibleFirstCommonAncestorLeft(commonAncestorFind(node->left, p1, p2, isP1Ancestor, isP2Ancestor, firstCommonAncestorWasFound));
      
      if ((isP1Ancestor && isP2Ancestor)
         &&
         (!firstCommonAncestorWasFound))
      {
         firstCommonAncestorWasFound = true;
         return node;
      }
      else if ((isP1Ancestor && isP2Ancestor)
         &&
         (firstCommonAncestorWasFound))
      {
         return possibleFirstCommonAncestorLeft;
      }

      std::shared_ptr<NodeNoParent> possibleFirstCommonAncestorRight;
      bool resetFlag(false);
      if (isP1Ancestor)
      {
         possibleFirstCommonAncestorRight = commonAncestorFind(node->right, p1, p2, resetFlag, isP2Ancestor, firstCommonAncestorWasFound);
      }
      else
      {
         possibleFirstCommonAncestorRight = commonAncestorFind(node->right, p1, p2, isP1Ancestor, isP2Ancestor, firstCommonAncestorWasFound);
      }

      if ((isP1Ancestor && isP2Ancestor )
         &&
         (!firstCommonAncestorWasFound))
      {
         firstCommonAncestorWasFound = true;
         return node;
      }
      else if((isP1Ancestor && isP2Ancestor)
         &&
         (firstCommonAncestorWasFound))
      {
         return possibleFirstCommonAncestorRight;
      }

      if (node == p1)
      {
         isP1Ancestor = true;
      }
      else if (node == p2)
      {
         isP2Ancestor = true;
      }
   }

   return 0;
}


bool test1()
{
   std::cout << "Beginning test1:\n\n";

   // Build tree with parent connections.
   std::shared_ptr<NodeWithParent> root(new NodeWithParent(4));

   std::shared_ptr<NodeWithParent> node9(new NodeWithParent(9));
   std::shared_ptr<NodeWithParent> node7(new NodeWithParent(7));
   std::shared_ptr<NodeWithParent> node2(new NodeWithParent(2));
   std::shared_ptr<NodeWithParent> node20(new NodeWithParent(20));
   std::shared_ptr<NodeWithParent> node5(new NodeWithParent(5));
   std::shared_ptr<NodeWithParent> node12(new NodeWithParent(12));
   std::shared_ptr<NodeWithParent> node1(new NodeWithParent(1));
   std::shared_ptr<NodeWithParent> node10(new NodeWithParent(10));
   std::shared_ptr<NodeWithParent> node55(new NodeWithParent(55));
   std::shared_ptr<NodeWithParent> node8(new NodeWithParent(8));
   std::shared_ptr<NodeWithParent> node71(new NodeWithParent(71));
   std::shared_ptr<NodeWithParent> node19(new NodeWithParent(19));

   root->parent = 0;
   root->left = node9;
   root->right = node7;

   node9->parent = root;
   node9->left = node2;
   node9->right = node20;

   node7->parent = root;
   node7->left = node5;
   node7->right = node12;

   node2->parent = node9;

   node20->parent = node9;
   node20->left = node1;

   node5->parent = node7;
   node5->left = node10;
   node5->right = node55;

   node12->parent = node7;
   node12->right = node8;

   node1->parent = node20;
   node1->right = node71;

   node10->parent = node5;

   node55->parent = node5;

   node8->parent = node12;
   node8->right = node19;

   node71->parent = node1;

   node19->parent = node8;

   // Sanity check
   std::cout << "Printing tree to make sure constructed correctly.\n\n";

   std::cout << "PreOrder traversal:\n";
   treePrintPreOrder(root);

   std::cout << "\nInOrder traversal:\n";
   treePrintInOrder(root);

   std::cout << "\nPostOrder traversal:\n";
   treePrintPostOrder(root);

   std::cout << "\n\n";

   // Run tests with tree with parent connections.
   std::shared_ptr<NodeWithParent> commonAncestor1(firstCommonAncestorFindUsingParents(node55, node19));
   if (commonAncestor1->val != 7)
   {
      std::cout << "Error, expected to find node 7 but found node: " << commonAncestor1->val << ".\n";
      return false;
   }

   std::shared_ptr<NodeWithParent> commonAncestor2(firstCommonAncestorFindUsingParents(node2, node8));
   if (commonAncestor2->val != 4)
   {
      std::cout << "Error, expected to find node 4 but found node: " << commonAncestor2->val << ".\n";
      return false;
   }

   std::shared_ptr<NodeWithParent> commonAncestor3(firstCommonAncestorFindUsingParents(node1, node71));
   if (commonAncestor3->val != 20)
   {
      std::cout << "Error, expected to find node 20 but found node: " << commonAncestor3->val << ".\n";
      return false;
   }

   std::shared_ptr<NodeWithParent> commonAncestor4(firstCommonAncestorFindUsingParents(node10, node55));
   if (commonAncestor4->val != 5)
   {
      std::cout << "Error, expected to find node 5 but found node: " << commonAncestor4->val << ".\n";
      return false;
   }

   std::shared_ptr<NodeWithParent> commonAncestor5(firstCommonAncestorFindUsingParents(node2, 0));
   if (commonAncestor5 != 0)
   {
      std::cout << "Error, expected to return a null pointer but instead returned: " << commonAncestor5->val << ".\n";
      return false;
   }

   return true;
}

bool test2()
{
   std::cout << "\n\nBeginning test2:\n\n";

   // Build tree without parent connections.

   std::shared_ptr<NodeNoParent> root(new NodeNoParent(4));

   std::shared_ptr<NodeNoParent> node9(new NodeNoParent(9));
   std::shared_ptr<NodeNoParent> node7(new NodeNoParent(7));
   std::shared_ptr<NodeNoParent> node2(new NodeNoParent(2));
   std::shared_ptr<NodeNoParent> node20(new NodeNoParent(20));
   std::shared_ptr<NodeNoParent> node5(new NodeNoParent(5));
   std::shared_ptr<NodeNoParent> node12(new NodeNoParent(12));
   std::shared_ptr<NodeNoParent> node1(new NodeNoParent(1));
   std::shared_ptr<NodeNoParent> node10(new NodeNoParent(10));
   std::shared_ptr<NodeNoParent> node55(new NodeNoParent(55));
   std::shared_ptr<NodeNoParent> node8(new NodeNoParent(8));
   std::shared_ptr<NodeNoParent> node71(new NodeNoParent(71));
   std::shared_ptr<NodeNoParent> node19(new NodeNoParent(19));

   root->left = node9;
   root->right = node7;

   node9->left = node2;
   node9->right = node20;

   node7->left = node5;
   node7->right = node12;

   node20->left = node1;

   node5->left = node10;
   node5->right = node55;

   node12->right = node8;

   node1->right = node71;

   node8->right = node19;

   // Sanity check
   std::cout << "Printing tree to make sure constructed correctly.\n\n";

   std::cout << "PreOrder traversal:\n";
   treePrintPreOrder(root);

   std::cout << "\nInOrder traversal:\n";
   treePrintInOrder(root);

   std::cout << "\nPostOrder traversal:\n";
   treePrintPostOrder(root);

   std::cout << "\n\n";

   // Run tests with tree without parent connections.
   std::shared_ptr<NodeNoParent> commonAncestor1(firstCommonAncestorFindPostOrderTraversal(root, node55, node19));
   if (commonAncestor1->val != 7)
   {
      std::cout << "Error, expected to find node 7 but found node: " << commonAncestor1->val << ".\n";
      return false;
   }

   std::shared_ptr<NodeNoParent> commonAncestor2(firstCommonAncestorFindPostOrderTraversal(root, node2, node8));
   if (commonAncestor2->val != 4)
   {
      std::cout << "Error, expected to find node 4 but found node: " << commonAncestor2->val << ".\n";
      return false;
   }

   std::shared_ptr<NodeNoParent> commonAncestor3(firstCommonAncestorFindPostOrderTraversal(root, node1, node71));
   if (commonAncestor3->val != 20)
   {
      std::cout << "Error, expected to find node 20 but found node: " << commonAncestor3->val << ".\n";
      return false;
   }

   std::shared_ptr<NodeNoParent> commonAncestor4(firstCommonAncestorFindPostOrderTraversal(root, node10, node55));
   if (commonAncestor4->val != 5)
   {
      std::cout << "Error, expected to find node 5 but found node: " << commonAncestor4->val << ".\n";
      return false;
   }

   std::shared_ptr<NodeNoParent> commonAncestor5(firstCommonAncestorFindPostOrderTraversal(root, node2, 0));
   if (commonAncestor5 != 0)
   {
      std::cout << "Error, expected to return a null pointer but instead returned: " << commonAncestor5->val << ".\n";
      return false;
   }

   std::shared_ptr<NodeNoParent> commonAncestor6(firstCommonAncestorFindPostOrderTraversal(root, root, node5));
   if (commonAncestor5 != 0)
   {
      std::cout << "Error, expected to return a null pointer but instead returned: " << commonAncestor6->val << ".\n";
      return false;
   }

   return true;
}





















