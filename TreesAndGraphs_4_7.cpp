#include <iostream>
#include <list>
#include <memory>
#include <utility>
#include <vector>

struct Node {
   Node(
      char nodeName)
      :
      name(nodeName)
   {
   }

   char name;
   std::vector<std::shared_ptr<Node> > children;
   std::vector<std::shared_ptr<Node> > parents;
};

struct Graph {
   std::vector<std::shared_ptr<Node> > nodes;
};

Graph graphCreateFromDependencyList(
   std::vector<std::vector<char> > projects);

void graphPrint(
   const Graph& graph);

std::list<char> buildOrderCreateFromGraph(
   Graph& graph);

void dependenciesClear(
   Graph& graph,
   char nodeName);

bool tests();

// Note: The book also lists a DFS solution which runs in the same time complexity.

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

Graph graphCreateFromDependencyList(
   std::vector<std::pair<char, char> > projects)
{
   Graph outputGraph;

   for (std::vector<std::pair<char, char> >::iterator it = projects.begin(); it != projects.end(); ++it)
   {
      std::shared_ptr<Node> parent(new Node(it->first));
      std::shared_ptr<Node> child(new Node(it->second));

      if (child->name == 0)
      {
         std::cout << "Found a node: " << parent->name << " with no dependencies. Simply adding that node to the graph.\n";
         outputGraph.nodes.push_back(parent);
         continue;
      }

      // If the parent node already exists in the Graph's vector of nodes, find it and give it another child.
      // Otherwise create a new node in the graph for that parent.
      bool parentAlreadyExists(false);
      for (auto parentIter = outputGraph.nodes.begin(); parentIter != outputGraph.nodes.end(); ++parentIter)
      {
         if ((*parentIter)->name == it->first)
         {
            parentAlreadyExists = true;
            (*parentIter)->children.push_back(child);
            break;
         }
      }
      if (!parentAlreadyExists)
      {
         parent->children.push_back(child);
         outputGraph.nodes.push_back(parent);
      }

      // If the child node already exists in the Graph's vector of nodes, find it and give it another parent.
      // Otherwise, create a new node in the graph for that child.
      bool childAlreadyExists(false);
      for (auto childIter = outputGraph.nodes.begin(); childIter != outputGraph.nodes.end(); ++childIter)
      {
         if ((*childIter)->name == it->second)
         {
            childAlreadyExists = true;
            (*childIter)->parents.push_back(parent);
            break;
         }
      }
      if (!childAlreadyExists)
      {
         child->parents.push_back(parent);
         outputGraph.nodes.push_back(child);
      }
   }

   return outputGraph;
}

void graphPrint(
   const Graph& graph)
{
   for (std::vector<std::shared_ptr<Node> >::const_iterator it = graph.nodes.begin(); it != graph.nodes.end(); ++it)
   {
      std::cout << "Printing node: " << (*it)->name << ".\n";
      std::cout << "Parent nodes: ";
      for (auto parentIter = (*it)->parents.begin(); parentIter != (*it)->parents.end(); ++parentIter)
      {
         std::cout << (*parentIter)->name << ", ";
      }
      std::cout << "\nChild nodes: ";
      for (auto childIter = (*it)->children.begin(); childIter != (*it)->children.end(); ++childIter)
      {
         std::cout << (*childIter)->name << ", ";
      }
      std::cout << "\n\n";
   }
}

std::list<char> buildOrderCreateFromGraph(
   Graph& graph)
{
   std::list<char> buildOrder;

   bool buildable(true);
   unsigned int expectedBuildOrderSize(graph.nodes.size());

   while ((buildOrder.size() != expectedBuildOrderSize) &&
      buildable)
   {
      bool buildableNodeFound(false);

      // Deciding in the loop whether or not in increment the iterator because if erase
      // is called on the iterator, it becomes invalidated.
      for (auto it = graph.nodes.begin(); it != graph.nodes.end(); )
      {
         if ((*it)->parents.size() == 0)
         {
            buildableNodeFound = true;
            char nodeName((*it)->name);
            dependenciesClear(graph, nodeName);
            buildOrder.push_back(nodeName);
            std::cout << "Adding node: " << nodeName << " to build order and removing it from graph.\n";
            it = graph.nodes.erase(it);
         }
         else
         {
            ++it;
         }
      }
      if (!buildableNodeFound)
      {
         buildable = false;
      }
   }

   if (!buildable)
   {
      buildOrder.clear();
   }

   return buildOrder;
}

void dependenciesClear(
   Graph& graph,
   char nodeName)
{
   for (auto it = graph.nodes.begin(); it != graph.nodes.end(); ++it)
   {
      for (auto parentIter = (*it)->parents.begin(); parentIter != (*it)->parents.end(); ++parentIter)
      {
         if ((*parentIter)->name == nodeName)
         {
            // Invalidates iterator, will need a new one.  This is ok, because
            // a node can only view one of its parent nodes as a parent node once.
            std::cout << "Erasing connection to parent: " << (*parentIter)->name << " from node: " << (*it)->name << ".\n";
            (*it)->parents.erase(parentIter);
            break;
         }
      }
   }
}

bool tests()
{
   std::vector<std::pair<char, char> > projects;
   projects.resize(6);

   projects[0].first = 'a';
   projects[0].second = 'd';

   projects[1].first = 'f';
   projects[1].second = 'b';

   projects[2].first = 'b';
   projects[2].second = 'd';

   projects[3].first = 'f';
   projects[3].second = 'a';

   projects[4].first = 'd';
   projects[4].second = 'c';

   projects[5].first = 'e';

   Graph inputGraph(graphCreateFromDependencyList(projects));

   std::cout << "Printing graph to make sure constructed correctly.\n";
   graphPrint(inputGraph);

   std::list<char> outputList(buildOrderCreateFromGraph(inputGraph));

   std::cout << "Printing build order:\n";
   for (auto it = outputList.begin(); it != outputList.end(); ++it)
   {
      std::cout << *it << " ";
   }

   // Could break the tests into separate functions but since there is more
   // than one legal build order, it's hard to automate the testing. So leaving
   // all the tests in one function.

   std::cout << "\n\n\nTest 2:\n";

   std::vector<std::pair<char, char> > projects2;
   projects2.resize(9);

   projects2[0].first = 'c';
   projects2[0].second = 'd';

   projects2[1].first = 'e';
   projects2[1].second = 'b';

   projects2[2].first = 'e';
   projects2[2].second = 'k';

   projects2[3].first = 'k';
   projects2[3].second = 'b';

   projects2[4].first = 'b';
   projects2[4].second = 'x';

   projects2[5].first = 'b';
   projects2[5].second = 'a';
   
   projects2[6].first = 'b';
   projects2[6].second = 'r';

   projects2[7].first = 'x';
   projects2[7].second = 'r';

   projects2[8].first = 'a';
   projects2[8].second = 'r';

   Graph inputGraph2(graphCreateFromDependencyList(projects2));

   std::cout << "Printing graph2 to make sure constructed correctly.\n";
   graphPrint(inputGraph2);

   std::list<char> outputList2(buildOrderCreateFromGraph(inputGraph2));

   std::cout << "Printing build order2:\n";
   for (auto it = outputList2.begin(); it != outputList2.end(); ++it)
   {
      std::cout << *it << " ";
   }

   std::cout << "\n\n\nTest 3:\n";

   std::vector<std::pair<char, char> > projects3;
   projects3.resize(7);

   projects3[0].first = 'a';
   projects3[0].second = 'f';

   projects3[1].first = 'f';
   projects3[1].second = 'l';

   projects3[2].first = 'o';
   projects3[2].second = 'f';

   projects3[3].first = 'l';
   projects3[3].second = 'o';

   projects3[4].first = 'c';
   projects3[4].second = 'o';

   projects3[5].first = 'c';
   projects3[5].second = 'm';

   projects3[6].first = 'o';
   projects3[6].second = 'm';

   Graph inputGraph3(graphCreateFromDependencyList(projects3));

   std::cout << "Printing graph3 to make sure constructed correctly.\n";
   graphPrint(inputGraph3);

   std::list<char> outputList3(buildOrderCreateFromGraph(inputGraph3));

   std::cout << "Checking to make sure no order exists for build order3:\n";
   if (outputList3.size() != 0)
   {
      std::cout << "Error, build order 3 is unbuildable, but the algorithm still detected a possible order.\n";
      return false;
   }

   return true;
}






































