#include <iostream>
#include <memory>
#include <string>

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

void treePrintPreOrder(
   std::unique_ptr<Node>& node);

void treePrintInOrder(
   std::unique_ptr<Node>& node);

void treePrintPostOrder(
   std::unique_ptr<Node>& node);

void treePreOrderWriteToString(
   std::unique_ptr<Node>& node,
   std::string& outputString);

bool subtreeCheckWithStrings(
   std::unique_ptr<Node>& treeANode,
   std::unique_ptr<Node>& treeBNode);

bool checkSubTree(
   std::unique_ptr<Node>& treeANode,
   std::unique_ptr<Node>& treeBNode);

bool matchSubTree(
   std::unique_ptr<Node>& treeANode,
   std::unique_ptr<Node>& treeBNode);

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

void treePrintPreOrder(
   std::unique_ptr<Node>& node)
{
   if (node != 0)
   {
      std::cout << node->val << ", ";
      treePrintPreOrder(node->left);
      treePrintPreOrder(node->right);
   }
}

void treePrintInOrder(
   std::unique_ptr<Node>& node)
{
   if (node != 0)
   {
      treePrintInOrder(node->left);
      std::cout << node->val << ", ";
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

void treePreOrderWriteToString(
   std::unique_ptr<Node>& node,
   std::string& outputString)
{
   if (node != 0)
   {
      outputString.append(std::to_string(node->val));
      treePreOrderWriteToString(node->left, outputString);
      treePreOrderWriteToString(node->right, outputString);
   }
   else
   {
      outputString.push_back('x');
   }
}

bool subtreeCheckWithStrings(
   std::unique_ptr<Node>& treeANode,
   std::unique_ptr<Node>& treeBNode)
{
   std::string treeAString("");
   std::string treeBString("");

   treePreOrderWriteToString(treeANode, treeAString);
   treePreOrderWriteToString(treeBNode, treeBString);

   std::cout << "Tree strings are:\n" << treeAString << "\nand:\n" << treeBString << "\n";

   int startSearchPosition(0);
   if (treeAString.find(treeBString, startSearchPosition) == std::string::npos)
   {
      return false;
   }

   return true;
}

bool checkSubTree(
   std::unique_ptr<Node>& treeANode,
   std::unique_ptr<Node>& treeBNode)
{
   if (treeANode == 0 || treeBNode == 0)
   {
      return false;
   }

   if (treeANode->val == treeBNode->val)
   {
      return matchSubTree(treeANode->left, treeBNode->left) && matchSubTree(treeANode->right, treeBNode->right);
   }
   else
   {
      return checkSubTree(treeANode->left, treeBNode) || checkSubTree(treeANode->right, treeBNode);
   }
}

bool matchSubTree(
   std::unique_ptr<Node>& treeANode,
   std::unique_ptr<Node>& treeBNode)
{
   if (treeANode == 0 && treeBNode == 0)
   {
      return true;
   }

   if (treeANode == 0 || treeBNode == 0)
   {
      return false;
   }

   if (treeANode->val == treeBNode->val)
   {
      return matchSubTree(treeANode->left, treeBNode->left) && matchSubTree(treeANode->right, treeBNode->right);
   }

   return false;
}

bool tests()
{
   // Setup both trees.

   std::unique_ptr<Node> root(new Node(4));
   std::unique_ptr<Node> node17Left(new Node(17));
   std::unique_ptr<Node> node9(new Node(9));
   std::unique_ptr<Node> node6Left(new Node(6));
   std::unique_ptr<Node> node3(new Node(3));
   std::unique_ptr<Node> node11(new Node(11));
   std::unique_ptr<Node> node2(new Node(2));
   std::unique_ptr<Node> node25(new Node(25));
   std::unique_ptr<Node> node14(new Node(14));
   std::unique_ptr<Node> node17Right(new Node(17));
   std::unique_ptr<Node> node90Right(new Node(90));
   std::unique_ptr<Node> node31(new Node(31));
   std::unique_ptr<Node> node90Left(new Node(90));
   std::unique_ptr<Node> node6Right(new Node(6));
   std::unique_ptr<Node> node41(new Node(41));
   std::unique_ptr<Node> node18(new Node(18));
   std::unique_ptr<Node> node50(new Node(50));
   std::unique_ptr<Node> node26(new Node(26));
   std::unique_ptr<Node> node100(new Node(100));

   // Put tree together.
   node41->left = std::move(node26);
   node41->right = std::move(node100);
   node31->left = std::move(node18);
   node31->right = std::move(node50);
   node17Right->left = std::move(node6Right);
   node17Right->right = std::move(node41);
   node14->left = std::move(node90Left);
   node2->right = std::move(node31);
   node11->right = std::move(node90Right);
   node11->left = std::move(node17Right);
   node6Left->left = std::move(node25);
   node6Left->right = std::move(node14);
   node9->left = std::move(node11);
   node9->right = std::move(node2);
   node17Left->left = std::move(node6Left);
   node17Left->right = std::move(node3);
   root->left = std::move(node17Left);
   root->right = std::move(node9);

   // Sanity check.
   std::cout << "\nPrinting Tree A Pre Order:\n";
   treePrintPreOrder(root);
   std::cout << "\nPrinting Tree A In Order:\n";
   treePrintInOrder(root);
   std::cout << "\nPrinting Tree A Post Order:\n";
   treePrintPostOrder(root);
   std::cout << "\n";

   std::unique_ptr<Node> nodeB17(new Node(17));
   std::unique_ptr<Node> nodeB6(new Node(6));
   std::unique_ptr<Node> nodeB41(new Node(41));
   std::unique_ptr<Node> nodeB26(new Node(26));
   std::unique_ptr<Node> nodeB100(new Node(100));

   // Put tree together.
   nodeB41->left = std::move(nodeB26);
   nodeB41->right = std::move(nodeB100);
   nodeB17->left = std::move(nodeB6);
   nodeB17->right = std::move(nodeB41);

   // Sanity check.
   std::cout << "\nPrinting Tree B Pre Order:\n";
   treePrintPreOrder(nodeB17);
   std::cout << "\nPrinting Tree B In Order:\n";
   treePrintInOrder(nodeB17);
   std::cout << "\nPrinting Tree B Post Order:\n";
   treePrintPostOrder(nodeB17);
   std::cout << "\n";

   bool stringMethodResult(subtreeCheckWithStrings(root, nodeB17));
   if (!stringMethodResult)
   {
      std::cout << "Error string method failed to find subtree which existed.\n";
      return false;
   }

   bool comparisonResult(checkSubTree(root, nodeB17));
   if (!comparisonResult)
   {
      std::cout << "Error tree direct comparison failed to find subtree which existed.\n";
      return false;
   }

   // Test with a second tree

   std::unique_ptr<Node> tree3Root(new Node(4));
   std::unique_ptr<Node> tree3Node17(new Node(17));
   std::unique_ptr<Node> tree3Node9(new Node(9));
   std::unique_ptr<Node> tree3Node3(new Node(3));

   tree3Node17->right = std::move(tree3Node3);
   tree3Root->left = std::move(tree3Node17);
   tree3Root->right = std::move(tree3Node9);

   std::unique_ptr<Node> tree4Root(new Node(4));
   std::unique_ptr<Node> tree4Node17(new Node(17));
   std::unique_ptr<Node> tree4Node5(new Node(5));

   tree4Node17->right = std::move(tree4Node5);
   tree4Root->left = std::move(tree4Node17);

   bool stringMethod2Result(subtreeCheckWithStrings(tree3Root, tree4Root));
   if (stringMethod2Result)
   {
      std::cout << "Error string method 2 found subtree which did not exist.\n";
      return false;
   }

   bool comparison2Result(checkSubTree(tree3Root, tree4Root));
   if (comparison2Result)
   {
      std::cout << "Error tree direct comparison 2 found subtree which did not exist.\n";
      return false;
   }

   return true;
}































