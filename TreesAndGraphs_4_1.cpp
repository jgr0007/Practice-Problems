#include <iomanip>
#include <iostream>
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

class Node {
public:
   Node(
      int val)
      :
      nodeVal(val)
   {
   }

   Node(const Node& rhs) :
   nodeVal(rhs.nodeVal),
   neighbors(rhs.neighbors)
   {
      
   }

   int nodeVal;
   std::vector<Node> neighbors;
};

class Graph {
public:
   void adjacencyListPrint() const
   {
      for (std::vector<Node>::const_iterator it = nodes.begin(); it != nodes.end(); it++)
      {
         std::cout << std::setw(2) << it->nodeVal << ": ";
         for (std::vector<Node>::const_iterator adjacent = it->neighbors.begin(); adjacent != it->neighbors.end(); adjacent++)
         {
            std::cout << std::setw(2) << adjacent->nodeVal << ",";
         }
         std::cout << "\n";
      }
   }

   std::vector<Node> nodes;
};



bool pathExists(
   Node startNode,
   Node endNode);

bool nodeVisit(
   Node nodeToVisit,
   Node endNode,
   std::list<Node>& queue,
   std::unordered_map<int, Node>& visitedNodes);

bool tests();

int main()
{
   if (tests())
   {
      std::cout << "********All tests passed.\n";
   }
   else
   {
      std::cout << "********At least one test failed.\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

bool pathExists(
   Node startNode,
   Node endNode)
{
   std::list<Node> queue;
   std::unordered_map<int, Node> visitedNodes;

   queue.push_back(startNode);
   visitedNodes.insert(std::make_pair(startNode.nodeVal, startNode));

   while (!queue.empty())
   {
      if (!nodeVisit(queue.front(), endNode, queue, visitedNodes))
      {
         std::cout << "Node checked: " << queue.front().nodeVal << " is not the searched for node.\n";
         queue.pop_front();
      }
      else
      {
         std::cout << "\nPath between: " << startNode.nodeVal << " and: " << endNode.nodeVal << " has been found.\n\n";
         return true;
      }
   }

   return false;
}

bool nodeVisit(
   Node nodeToVisit,
   Node endNode,
   std::list<Node>& queue,
   std::unordered_map<int, Node>& visitedNodes)
{
   if (nodeToVisit.nodeVal == endNode.nodeVal)
   {
      return true;
   }
   else
   {
      // Enqueue all neighbors if they have not been visited.
      for (std::vector<Node>::const_iterator it = nodeToVisit.neighbors.begin(); it != nodeToVisit.neighbors.end(); it++)
      {
         std::unordered_map<int, Node>::const_iterator visitedSearcher(visitedNodes.find(it->nodeVal));

         if (visitedSearcher == visitedNodes.end())
         {
            std::cout << "Enqueueing node: " << it->nodeVal << " because it is an unvisited neighbor of: " << nodeToVisit.nodeVal << "\n";
            queue.push_back(*it);
         }
         else
         {
            std::cout << "Not enqueing node: " << it->nodeVal << " because it has already been visited.\n";
         }
      }
      // Mark node visited
      std::cout << "Marking node: " << nodeToVisit.nodeVal << " visited because it is not the endNode.\n";
      visitedNodes.insert(std::make_pair(nodeToVisit.nodeVal, nodeToVisit));

      return false;
   }
}

bool tests()
{
   // Setup

   Graph graph;
   // Create all nodes
   Node node2(2);
   Node node1(1);
   Node node4(4);
   Node node5(5);
   Node node8(8);
   Node node11(11);
   Node node6(6);
   Node node15(15);
   Node node3(3);

   // Define each node's neighbors
   // This does not initialize perfectly. It is actually good enough to satisfy the algorithm though.
   node1.neighbors.insert(node1.neighbors.begin(), node4);
   node2.neighbors.insert(node2.neighbors.begin(), node1);
   node5.neighbors.insert(node5.neighbors.begin(), node2);
   node5.neighbors.insert(node5.neighbors.begin() + 1, node4);
   node8.neighbors.insert(node8.neighbors.begin(), node5);
   node11.neighbors.insert(node11.neighbors.begin(), node4);
   node8.neighbors.insert(node8.neighbors.begin() + 1, node11);
   node11.neighbors.insert(node11.neighbors.begin() + 1, node8);
   
   node6.neighbors.insert(node6.neighbors.begin(), node3);
   node15.neighbors.insert(node15.neighbors.begin(), node3);
   node6.neighbors.insert(node6.neighbors.begin() + 1, node15);
   
   
   // Put each node in graph
   graph.nodes.insert(graph.nodes.begin(), node2);
   graph.nodes.insert(graph.nodes.begin() + 1, node1);
   graph.nodes.insert(graph.nodes.begin() + 2, node4);
   graph.nodes.insert(graph.nodes.begin() + 3, node5);
   graph.nodes.insert(graph.nodes.begin() + 4, node8);
   graph.nodes.insert(graph.nodes.begin() + 5, node11);
   graph.nodes.insert(graph.nodes.begin() + 6, node6);
   graph.nodes.insert(graph.nodes.begin() + 7, node15);
   graph.nodes.insert(graph.nodes.begin() + 8, node3);

   std::cout << "Checking graph by printing adjacency list:\n\n";
   graph.adjacencyListPrint();

   if (!pathExists(node6, node3))
   {
      std::cout << "Error, failed to find existing path between nodes 6 and 3.\n";
      return false;
   }

   if (!pathExists(node8, node4))
   {
      std::cout << "Error, failed to find existing path between nodes 8 and 4.\n";
      return false;
   }

   if (!pathExists(node2, node4))
   {
      std::cout << "Error, failed to find existing path between nodes 2 and 4.\n";
      return false;
   }

   if (!pathExists(node5, node2))
   {
      std::cout << "Error, failed to find existing path between nodes 5 and 2.\n";
      return false;
   }

   if (!pathExists(node15, node3))
   {
      std::cout << "Error, failed to find existing path between nodes 15 and 3.\n";
      return false;
   }

   if (pathExists(node3, node6))
   {
      std::cout << "Error, reported path between nodes 3 and 6 that did not actually exist.\n";
      return false;
   }

   if (pathExists(node15, node6))
   {
      std::cout << "Error, reported path between nodes 15 and 6 that did not actually exist.\n";
      return false;
   }

   if (pathExists(node4, node2))
   {
      std::cout << "Error, reported path between nodes 4 and 2 that did not actually exist.\n";
      return false;
   }

   if (pathExists(node2, node8))
   {
      std::cout << "Error, reported path between nodes 2 and 8 that did not actually exist.\n";
      return false;
   }

   return true;
}

























