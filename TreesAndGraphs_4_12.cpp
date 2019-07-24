#include <iostream>
#include <map>
#include <memory>

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

void inOrderTraversal(
   std::unique_ptr<Node>& node);

void preOrderTraversal(
   std::unique_ptr<Node>& node);

void sumsFind(
   std::unique_ptr<Node>& node,
   int& sumPathsFound,
   int expectedSum);

void findSumPaths(
   std::unique_ptr<Node>& node,
   int& sumPathsFound,
   int expectedSum,
   int& currentSumOfPath);

int sumsFindOptimized(
   std::unique_ptr<Node>& node,
   int targetSum);

int sumPathsFindOptimized(
   std::unique_ptr<Node>& node,
   int targetSum,
   int& runningSum,
   std::map<int, int>& runningSumFrequencies);

int getSumFrequency(
   int requestedSum,
   std::map<int, int>& runningSumFrequencies);

void updateHashTable(
   std::map<int, int>& runningSumFrequencies,
   int runningSum,
   int incrementOrDecrementFrequency);

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

void inOrderTraversal(
   std::unique_ptr<Node>& node)
{
   if (node != 0)
   {
      inOrderTraversal(node->left);
      std::cout << node->val << ", ";
      inOrderTraversal(node->right);
   }
}

void preOrderTraversal(
   std::unique_ptr<Node>& node)
{
   if (node != 0)
   {
      std::cout << node->val << ", ";
      preOrderTraversal(node->left);
      preOrderTraversal(node->right);
   }
}

void sumsFind(
   std::unique_ptr<Node>& node,
   int& sumPathsFound,
   int expectedSum)
{
   if (node != 0)
   {
      std::cout << "Searching for paths to sum: " << expectedSum << " starting from node: " << node->val << ":\n";
      int currentSumOfPath(0);
      findSumPaths(node, sumPathsFound, expectedSum, currentSumOfPath);

      sumsFind(node->left, sumPathsFound, expectedSum);
      sumsFind(node->right, sumPathsFound, expectedSum);
   }
}

void findSumPaths(
   std::unique_ptr<Node>& node,
   int& sumPathsFound,
   int expectedSum,
   int& currentSumOfPath)
{
   if (node != 0)
   {
      currentSumOfPath += node->val;
      if (currentSumOfPath == expectedSum)
      {
         std::cout << "Path terminating at node: " << node->val << " is a path to sum: " << expectedSum << ".\n\n";
         ++sumPathsFound;
      }

      int savedSumPath(currentSumOfPath);

      findSumPaths(node->left, sumPathsFound, expectedSum, currentSumOfPath);
      findSumPaths(node->right, sumPathsFound, expectedSum, savedSumPath);
   }
}

int sumsFindOptimized(
   std::unique_ptr<Node>& node,
   int targetSum)
{
   int runningSum(0);
   // runningSum, frequency
   std::map<int, int> runningSumFrequencies;
   return sumPathsFindOptimized(node, targetSum, runningSum, runningSumFrequencies);
}

int sumPathsFindOptimized(
   std::unique_ptr<Node>& node,
   int targetSum,
   int& runningSum,
   std::map<int, int>& runningSumFrequencies)
{
   if (node != 0)
   {
      runningSum += node->val;
      int sumToMakeTargetSum(runningSum - targetSum);
      int totalPaths(getSumFrequency(sumToMakeTargetSum, runningSumFrequencies));

      if (runningSum == targetSum)
      {
         ++totalPaths;
      }

      int incrementOrDecrementFrequency(1);
      updateHashTable(runningSumFrequencies, runningSum, incrementOrDecrementFrequency);

      int savedRunningSumForTraveral(runningSum);
      int savedRunningSumForFrequency(runningSum);
      totalPaths += sumPathsFindOptimized(node->left, targetSum, runningSum, runningSumFrequencies);
      totalPaths += sumPathsFindOptimized(node->right, targetSum, savedRunningSumForTraveral, runningSumFrequencies);

      incrementOrDecrementFrequency = -1;
      updateHashTable(runningSumFrequencies, savedRunningSumForFrequency, incrementOrDecrementFrequency);

      return totalPaths;
   }

   return 0;
}

int getSumFrequency(
   int requestedSum,
   std::map<int, int>& runningSumFrequencies)
{
   int sumFrequency(0);
   for (auto iter = runningSumFrequencies.begin(); iter != runningSumFrequencies.end(); ++iter)
   {
      if (iter->first == requestedSum)
      {
         sumFrequency = iter->second;
      }
   }

   return sumFrequency;
}

void updateHashTable(
   std::map<int, int>& runningSumFrequencies,
   int runningSum,
   int incrementOrDecrementFrequency)
{
   auto iter(runningSumFrequencies.find(runningSum));
   if (incrementOrDecrementFrequency == 1)
   {
      if (iter != runningSumFrequencies.end())
      {
         ++iter->second;
      }
      else
      {
         runningSumFrequencies.insert(std::make_pair(runningSum, 1));
      }
   }
   else
   {
      if (iter != runningSumFrequencies.end())
      {
         --iter->second;
      }
   }
}

bool tests()
{
   std::unique_ptr<Node> node8(new Node(8));
   std::unique_ptr<Node> nodeNeg5(new Node(-5));
   std::unique_ptr<Node> node12(new Node(12));
   std::unique_ptr<Node> nodeNeg2Left(new Node(-2));
   std::unique_ptr<Node> node10(new Node(10));
   std::unique_ptr<Node> node7(new Node(7));
   std::unique_ptr<Node> node3Left(new Node(3));
   std::unique_ptr<Node> node11(new Node(11));
   std::unique_ptr<Node> nodeNeg9(new Node(-9));
   std::unique_ptr<Node> node2(new Node(2));
   std::unique_ptr<Node> nodeNeg3Left(new Node(-3));
   std::unique_ptr<Node> nodeNeg3Right(new Node(-3));
   std::unique_ptr<Node> node4(new Node(4));
   std::unique_ptr<Node> nodeNeg1(new Node(-1));
   std::unique_ptr<Node> node13(new Node(13));
   std::unique_ptr<Node> node3Right(new Node(3));
   std::unique_ptr<Node> nodeNeg2Right(new Node(-2));
   std::unique_ptr<Node> node6(new Node(6));

   node3Left->left = std::move(node4);
   node3Left->right = std::move(nodeNeg1);
   nodeNeg9->left = std::move(node13);
   nodeNeg9->right = std::move(node3Right);
   nodeNeg3Left->right = std::move(nodeNeg2Right);
   nodeNeg3Right->left = std::move(node6);
   nodeNeg2Left->left = std::move(node3Left);
   nodeNeg2Left->right = std::move(node11);
   node10->left = std::move(nodeNeg9);
   node10->right = std::move(node2);
   node7->left = std::move(nodeNeg3Left);
   node7->right = std::move(nodeNeg3Right);
   nodeNeg5->left = std::move(nodeNeg2Left);
   node12->left = std::move(node10);
   node12->right = std::move(node7);
   node8->left = std::move(nodeNeg5);
   node8->right = std::move(node12);

   std::cout << "Pre order traversal as sanity check:\n\n";
   preOrderTraversal(node8);
   std::cout << std::endl;

   int expectedSum(1);
   int sumPathsFound(0);
   sumsFind(node8, sumPathsFound, expectedSum);
   if (sumPathsFound != 3)
   {
      std::cout << "Error - expected to find 3 paths to sum 1 but found: " << sumPathsFound << ".\n";
      return false;
   }
   std::cout << std::endl;

   expectedSum = 4;
   sumPathsFound = 0;
   sumsFind(node8, sumPathsFound, expectedSum);
   if (sumPathsFound != 7)
   {
      std::cout << "Error - expected to find 7 paths to sum 4 but found: " << sumPathsFound << ".\n";
      return false;
   }
   std::cout << std::endl;

   expectedSum = 20;
   sumPathsFound = 0;
   sumsFind(node8, sumPathsFound, expectedSum);
   if (sumPathsFound != 1)
   {
      std::cout << "Error - expected to find 1 path to sum 20 but found: " << sumPathsFound << ".\n";
      return false;
   }
   std::cout << std::endl;

   expectedSum = 100;
   sumPathsFound = 0;
   sumsFind(node8, sumPathsFound, expectedSum);
   if (sumPathsFound != 0)
   {
      std::cout << "Error - expected to find 0 paths to sum 100 but found: " << sumPathsFound << ".\n";
      return false;
   }
   std::cout << std::endl;


   expectedSum = 1;
   int optimizedResult(sumsFindOptimized(node8, expectedSum));
   if (optimizedResult != 3)
   {
      std::cout << "Error - expected to find 3 paths to sum 1 but found: " << optimizedResult << ".\n";
      return false;
   }
   std::cout << std::endl;

   expectedSum = 4;
   optimizedResult = sumsFindOptimized(node8, expectedSum);
   if (optimizedResult != 7)
   {
      std::cout << "Error - expected to find 7 paths to sum 4 but found: " << optimizedResult << ".\n";
      return false;
   }
   std::cout << std::endl;

   expectedSum = 20;
   optimizedResult = sumsFindOptimized(node8, expectedSum);
   if (optimizedResult != 1)
   {
      std::cout << "Error - expected to find 1 paths to sum 20 but found: " << optimizedResult << ".\n";
      return false;
   }
   std::cout << std::endl;

   expectedSum = 100;
   optimizedResult = sumsFindOptimized(node8, expectedSum);
   if (optimizedResult != 0)
   {
      std::cout << "Error - expected to find 0 paths to sum 100 but found: " << optimizedResult << ".\n";
      return false;
   }
   std::cout << std::endl;

   return true;
}

































