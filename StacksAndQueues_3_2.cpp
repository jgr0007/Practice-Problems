#include <iostream>

namespace {
   const int ARRAY_SIZE(100);
}

// Not doing stack overflow this problem - I did it on the last problem.

class StackWithMin {
public:

   StackWithMin()
      :
      m_regStackTop(-1),
      m_minStackTop(-1)
   {
      memoryInit();
   }

   void push(
      int newData)
   {
      if (isEmpty())
      {
         m_minStack[m_minStackTop + 1] = newData;
         ++m_minStackTop;
      }
      else
      {
         if (newData < m_minStack[m_minStackTop])
         {
            m_minStack[m_minStackTop + 1] = newData;
            ++m_minStackTop;
         }
      }

      m_regStack[m_regStackTop + 1] = newData;
      ++m_regStackTop;
   }

   void pop()
   {
      if (isEmpty())
      {
         std::cout << "Warning, stack is empty. Nothing to pop.\n";
      }
      else
      {
         if (m_regStack[m_regStackTop] == m_minStack[m_minStackTop])
         {
            --m_minStackTop;
         }

         --m_regStackTop;
      }
   }

   int peek()
   {
      if (isEmpty())
      {
         std::cout << "Warning, stack is empty. Nothing to peek.\n";
         return -1;
      }
      else
      {
         return m_regStack[m_regStackTop];
      }
   }

   int min()
   {
      if (isEmpty())
      {
         std::cout << "Warning, stack is empty. Nothing to min().\n";
         return -1;
      }
      else
      {
         return m_minStack[m_minStackTop];
      }
   }

   bool isEmpty()
   {
      return m_regStackTop < 0;
   }

private:

   void memoryInit()
   {
      for (int i = 0; i< ARRAY_SIZE; i++)
      {
         m_regStack[i] = -1;
         m_minStack[i] = -1;
      }
   }

   // Holds all pushed client elements.
   int m_regStackTop;
   // Holds mins of regStack, where minStackTop is least value min.
   int m_minStackTop;

   // Minimum element stored in regStack. Also the top of minStack.
   int m_min;

   int m_regStack[ARRAY_SIZE];
   int m_minStack[ARRAY_SIZE];
};

bool testSequenceOne();

int main()
{
   std::cout << "********Testing StackWithMin:\n";
   if (testSequenceOne())
   {
      std::cout << "All Tests Passed.\n";
   }
   else
   {
      std::cout << "Error, At Least One Test Failed.\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

bool testSequenceOne()
{
   StackWithMin* stack = new StackWithMin();

   stack->push(6);
   stack->push(4);
   stack->push(7);
   stack->push(3);
   stack->push(2);
   stack->push(8);

   if (stack->peek() != 8)
   {
      std::cout << "Error Test One, Expecting to peek 8, but peeked: " << stack->peek() << ".\n";
      return false;
   }
   if (stack->min() != 2)
   {
      std::cout << "Error Test One, Expecting to min() 2, but minned: " << stack->min() << ".\n";
      return false;
   }

   stack->pop();

   if (stack->peek() != 2 || stack->min() != 2)
   {
      std::cout << "Error Test One, After popping 8.\n";
      return false;
   }

   stack->pop();

   if (stack->peek() != 3 || stack->min() != 3)
   {
      std::cout << "Error Test One, After popping 2.\n";
      return false;
   }

   stack->pop();

   if (stack->peek() != 7 || stack->min() != 4)
   {
      std::cout << "Error Test One, After popping 3.\n";
      return false;
   }

   stack->pop();

   if (stack->peek() != 4 || stack->min() != 4)
   {
      std::cout << "Error Test One, After popping 7.\n";
      return false;
   }

   stack->pop();

   if (stack->peek() != 6 || stack->min() != 6)
   {
      std::cout << "Error Test One, After popping 4.\n";
      return false;
   }

   stack->pop();

   if (stack->peek() != -1 || stack->min() != -1)
   {
      std::cout << "Error Test One, After popping 6.\n";
      return false;
   }

   stack->push(5);
   stack->push(7);

   if (stack->peek() != 7 || stack->min() != 5)
   {
      std::cout << "Error Test One, After pushing 7.\n";
      return false;
   }

   stack->push(3);

   if (stack->peek() != 3 || stack->min() != 3)
   {
      std::cout << "Error Test One, After pushing 3.\n";
      return false;
   }

   delete stack;
   return true;
}