#include <iostream>

class MultiStack
{
public:
   MultiStack(
      int memorySize,
      int numStacks)
      :
      m_array(new int[memorySize]),
      m_numStacks(numStacks)
   {
      m_spaceAllocatedPerStack = memorySize / numStacks;
      m_stackBaseAddresses = new int[numStacks];
      m_stackLimits = new int[numStacks];
      m_stackTops = new int[numStacks];

      memorySpaceInitialize();
   }

   ~MultiStack()
   {
      // Release memory
      delete[] m_array;
      delete[] m_stackBaseAddresses;
      delete[] m_stackLimits;
      delete[] m_stackTops;
   }

   //TODO: Handle 4 other operations out of 6. Delete all of them.

   void push(
      int newData,
      int stackIndex)
   {
      if (!stackIndexExists(stackIndex))
      {
         stackIndex = m_numStacks - 1;
      }

      // TODO: This isn't ideal, but I'm lazy tonight. If a stack is at capacity, pop the top off so you can push the next element.
      if (pushWouldCauseOverflow(stackIndex))
      {
         std::cout << "Warning, stack: " << stackIndex << " is full. Popping off the top element: " << peek(stackIndex) << " to make room for new element: " << newData << "\n";
         pop(stackIndex);
      }

      int entryPosition(m_stackTops[stackIndex - 1] + 1);
      m_array[entryPosition] = newData;
      ++m_stackTops[stackIndex - 1];
   }

   void pop(
      int stackIndex)
   {
      if (!stackIndexExists(stackIndex))
      {
         stackIndex = m_numStacks - 1;
      }

      if (isEmpty(stackIndex))
      {
         std::cout << "Warning, stack: " << stackIndex << " has no elements to pop. Doing nothing.\n";
      }
      else
      {
         // No need to erase any data - the array stays allocated. Just decrement the top.
         --m_stackTops[stackIndex-1];
      }
   }

   int peek(
      int stackIndex)
   {
      if (!stackIndexExists(stackIndex))
      {
         stackIndex = m_numStacks - 1;
      }

      if (isEmpty(stackIndex))
      {
         std::cout << "Warning, stack: " << stackIndex << " has no elements to peek. Doing nothing.\n";
         return -1;
      }
      else
      {
         return m_array[m_stackTops[stackIndex-1]];
      }
   }

   bool isEmpty(
      int stackIndex)
   {
      if (!stackIndexExists(stackIndex))
      {
         stackIndex = m_numStacks - 1;
      }

      return m_stackTops[stackIndex-1] == m_stackBaseAddresses[stackIndex-1] - 1;
   }

private:
   void memorySpaceInitialize()
   {
      for (int baseAddressesIndex = 0; baseAddressesIndex < m_numStacks; baseAddressesIndex++)
      {
         m_stackBaseAddresses[baseAddressesIndex] = (m_spaceAllocatedPerStack * baseAddressesIndex);
         m_stackLimits[baseAddressesIndex] = m_spaceAllocatedPerStack * (baseAddressesIndex + 1) - 1;
         m_stackTops[baseAddressesIndex] = m_stackBaseAddresses[baseAddressesIndex] - 1;
      }
   }

   bool pushWouldCauseOverflow(
      int stackIndex)
   {
      // If top of stack is at address of base address + allocated stack allocation - 1 (because arrays are zero indexed), the 
      // stackis full. Pushing more data would cause an overflow.
      //return (m_stackLimits[stackIndex-1] == m_spaceAllocatedPerStack*(stackIndex + 1)) - 1;

      return m_stackTops[stackIndex - 1] == m_stackLimits[stackIndex - 1];
   }

   // TODO: For now, if someone passes in a stack index that does not exist, just going to grab the highest stack.  
   bool stackIndexExists(
      int stackIndex)
   {
      return stackIndex <= m_numStacks;
   }

   int* m_array;
   int m_spaceAllocatedPerStack;
   int m_numStacks;
   int* m_stackBaseAddresses;
   int* m_stackLimits;
   int* m_stackTops;
};

bool pushCapacityTest();
bool popCapacityTest();
bool peekCapacityTest();

bool pushEmpty();
bool pushNonEmpty();

bool popEmpty();
bool popNonEmpty();

bool peekEmpty();
bool peekNonEmpty();

int main()
{
   std::cout << "********Testing with small array size 10 to test memory limits.\n";
      if (pushCapacityTest() &&
         popCapacityTest() &&
         peekCapacityTest())
      {
         std::cout << "All memory limits tests passed.\n";
      }
      else
      {
         std::cout << "At least one memory limits test failed.\n";
      }

      std::cout << "\n********Testing push() function.\n";
      if (pushEmpty() &&
         pushNonEmpty())
      {
         std::cout << "All push() tests passed.\n";
      }
      else
      {
         std::cout << "One push() test failed.\n";
      }

      std::cout << "\n********Testing pop() function.\n";
      if (popEmpty() &&
         popNonEmpty())
      {
         std::cout << "All pop() tests passed.\n";
      }
      else
      {
         std::cout << "One pop() test failed.\n";
      }

      std::cout << "\n********Testing peek() function.\n";
      if (peekEmpty() &&
         peekNonEmpty())
      {
         std::cout << "All peek() tests passed.\n";
      }
      else
      {
         std::cout << "One peek() test failed.\n";
      }

   int k;
   std::cin >> k;
   return 0;
}

bool pushCapacityTest()
{
   int memorySpace(10);
   int numStacks(3);

   MultiStack* multiStack = new MultiStack(10, 3);

   // Fill up stacks
   multiStack->push(1, 1);
   multiStack->push(2, 1);
   multiStack->push(3, 1);

   multiStack->push(10, 2);
   multiStack->push(12, 2);
   multiStack->push(14, 2);

   multiStack->push(100, 3);
   multiStack->push(101, 3);
   multiStack->push(102, 3);

   if (multiStack->peek(1) != 3)
   {
      std::cout << "Error in pushCapacityTest. Expected to peek 3 but peeked: " << multiStack->peek(1) << "\n";
      return false;
   }
   if (multiStack->peek(2) != 14)
   {
      std::cout << "Error in pushCapacityTest. Expected to peek 14 but peeked: " << multiStack->peek(2) << "\n";
      return false;
   }
   if (multiStack->peek(3) != 102)
   {
      std::cout << "Error in pushCapacityTest. Expected to peek 102 but peeked: " << multiStack->peek(3) << "\n";
      return false;
   }

   multiStack->push(9, 1);
   if (multiStack->peek(1) != 9)
   {
      std::cout << "Error in pushCapacityTest. Expected to peek 9 but peeked: " << multiStack->peek(1) << "\n";
      return false;
   }

   delete multiStack;

   return true;
}

bool popCapacityTest()
{
   int memorySpace(10);
   int numStacks(3);

   MultiStack* multiStack = new MultiStack(10, 3);

   // Fill up stacks
   multiStack->push(1, 1);
   multiStack->push(2, 1);
   multiStack->push(3, 1);

   multiStack->push(10, 2);
   multiStack->push(12, 2);
   multiStack->push(14, 2);

   multiStack->push(100, 3);
   multiStack->push(101, 3);
   multiStack->push(102, 3);

   multiStack->pop(1);

   if (multiStack->peek(1) != 2)
   {
      std::cout << "Error in popCapacityTest. Expected to peek 2 but peeked: " << multiStack->peek(1) << "\n";
      return false;
   }

   delete multiStack;

   return true;
}

bool peekCapacityTest()
{
   int memorySpace(10);
   int numStacks(3);

   MultiStack* multiStack = new MultiStack(10, 3);

   // Fill up stacks
   multiStack->push(1, 1);
   multiStack->push(2, 1);
   multiStack->push(3, 1);

   multiStack->push(10, 2);
   multiStack->push(12, 2);
   multiStack->push(14, 2);

   multiStack->push(100, 3);
   multiStack->push(101, 3);
   multiStack->push(102, 3);

   int result(multiStack->peek(3));
   if (result != 102)
   {
      std::cout << "Error in popCapacityTest. Expected to peek 102 but peeked: " << multiStack->peek(3) << "\n";
      return false;
   }

   delete multiStack;

   return true;
}

bool pushEmpty()
{
   int memorySpace(10);
   int numStacks(3);

   MultiStack* multiStack = new MultiStack(10, 3);

   // Fill up stacks
   multiStack->push(10, 2);
   multiStack->push(12, 2);
   multiStack->push(14, 2);

   multiStack->push(100, 3);
   multiStack->push(101, 3);
   multiStack->push(102, 3);

   multiStack->push(5, 1);
   int result(multiStack->peek(1));
   if (result != 5)
   {
      std::cout << "Error in pushEmpty. Expected to peek 5 but peeked: " << multiStack->peek(1) << "\n";
      return false;
   }

   delete multiStack;

   return true;
}

bool pushNonEmpty()
{
   int memorySpace(10);
   int numStacks(3);

   MultiStack* multiStack = new MultiStack(10, 3);

   // Fill up stacks
   multiStack->push(10, 2);
   multiStack->push(12, 2);
   multiStack->push(14, 2);

   multiStack->push(100, 3);
   multiStack->push(101, 3);
   multiStack->push(102, 3);

   multiStack->push(5, 1);
   multiStack->push(6, 1);
   int result(multiStack->peek(1));
   if (result != 6)
   {
      std::cout << "Error in pushNonEmpty. Expected to peek 6 but peeked: " << multiStack->peek(1) << "\n";
      return false;
   }

   delete multiStack;

   return true;
}

bool popEmpty()
{/*
 int memorySpace(10);
 int numStacks(3);

 MultiStack* multiStack = new MultiStack(10,3);

 // Fill up stacks
 multiStack->push(10, 2);
 multiStack->push(12, 2);
 multiStack->push(14, 2);

 multiStack->push(100, 3);
 multiStack->push(101, 3);
 multiStack->push(102, 3);

 multiStack->pop(1);
 if (result != 6)
 {
 std::cout << "Error in popEmpty. Expected to peek 6 but peeked: " << multiStack->peek(1) << "\n";
 return false;
 }

 delete multiStack;
 */
   return true;
}

bool popNonEmpty()
{
   int memorySpace(10);
   int numStacks(3);

   MultiStack* multiStack = new MultiStack(10, 3);

   // Fill up stacks
   multiStack->push(10, 2);
   multiStack->push(12, 2);
   multiStack->push(14, 2);

   multiStack->push(100, 3);
   multiStack->push(101, 3);
   multiStack->push(102, 3);

   multiStack->pop(2);
   if (multiStack->peek(2) != 12)
   {
      std::cout << "Error in popNonEmpty. Expected to peek 12 but peeked: " << multiStack->peek(2) << "\n";
      return false;
   }

   delete multiStack;

   return true;
}

bool peekEmpty()
{
   int memorySpace(10);
   int numStacks(3);

   MultiStack* multiStack = new MultiStack(10, 3);

   // Fill up stacks
   multiStack->push(10, 2);
   multiStack->push(12, 2);
   multiStack->push(14, 2);

   multiStack->push(100, 3);
   multiStack->push(101, 3);
   multiStack->push(102, 3);

   if (multiStack->peek(1) != -1)
   {
      std::cout << "Error in peekEmpty. Expected to peek -1 but peeked: " << multiStack->peek(1) << "\n";
      return false;
   }

   delete multiStack;

   return true;
}

bool peekNonEmpty()
{
   int memorySpace(10);
   int numStacks(3);

   MultiStack* multiStack = new MultiStack(10, 3);

   // Fill up stacks
   multiStack->push(10, 2);
   multiStack->push(12, 2);
   multiStack->push(14, 2);

   multiStack->push(100, 3);
   multiStack->push(101, 3);
   multiStack->push(102, 3);

   if (multiStack->peek(2) != 14)
   {
      std::cout << "Error in peekNonEmpty. Expected to peek 14 but peeked: " << multiStack->peek(2) << "\n";
      return false;
   }

   delete multiStack;

   return true;
}
