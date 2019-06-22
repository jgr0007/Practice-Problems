#include <iostream>

// Template these classes to deal with sizes besides int?

class Stack {
public:
   Stack()
      :
      m_top(-1)
   {
   }

   void push(
      int newData)
   {
      m_array[m_top + 1] = newData;
      ++m_top;
   }

   void pop()
   {
      if (isEmpty())
      {
         std::cout << "Warning, cannot pop empty stack. Doing nothing.\n";
      }
      else
      {
         --m_top;
      }
   }

   int peek()
   {
      if (isEmpty())
      {
         std::cout << "Warning, cannot peek empty stack. Returning -1.\n";
         return -1;
      }
      else
      {
         return m_array[m_top];
      }
   }

   int size()
   {
      return m_top + 1;
   }

   bool isEmpty()
   {
      return m_top == -1;
   }

private:
   int m_top;
   int m_array[100];
};

class Queue {
public:

   void add(
      int newData)
   {
      m_regStack.push(newData);
   }

   void remove()
   {
      int regStackSize(m_regStack.size());
      if (regStackSize == 0)
      {
         std::cout << "Warning, cannot remove from empty queue. Doing nothing.\n";
      }
      else
      {
         // Move all but the bottom element from regStack to the temp stack
         for (int i = regStackSize; i > 1; --i)
         {
            m_tempStack.push(m_regStack.peek());
            m_regStack.pop();
         }

         // Pop that element from regStack
         m_regStack.pop();

         // Move all elements from temp stack back to regStack
         for (int i = m_tempStack.size(); i > 0; --i)
         {
            m_regStack.push(m_tempStack.peek());
            m_tempStack.pop();
         }
      }
   }

   int peek()
   {
      int regStackSize(m_regStack.size());
      int peekVal(-1);

      if (regStackSize == 0)
      {
         std::cout << "Warning, cannot peek from empty queue. Returning -1.\n";
      }
      else
      {
         // Move all but the bottom element from regStack to the temp stack
         for (int i = regStackSize; i > 1; --i)
         {
            m_tempStack.push(m_regStack.peek());
            m_regStack.pop();
         }

         // Pop that element from regStack
         peekVal = m_regStack.peek();

         // Move all elements from temp stack back to regStack
         for (int i = m_tempStack.size(); i > 0; --i)
         {
            m_regStack.push(m_tempStack.peek());
            m_tempStack.pop();
         }
      }

      return peekVal;
   }

   bool isEmpty()
   {
      return m_regStack.isEmpty();
   }

private:

   Stack m_regStack;
   Stack m_tempStack;
};

bool tests();

int main()
{
   if (tests())
   {
      std::cout << "********\n\nAll tests passed.\n";
   }
   else
   {
      std::cout << "********\n\nAt least one test failed.\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

bool tests()
{
   Queue queue;

   queue.add(1);
   queue.add(3);
   queue.add(4);
   queue.add(2);
   queue.add(5);

   if (queue.peek() != 1)
   {
      std::cout << "Error, expected to peek 1 at front of queue but peeked: " << queue.peek() << ".\n";
      return false;
   }

   queue.remove();

   if (queue.peek() != 3)
   {
      std::cout << "Error, expected to peek 3 at front of queue but peeked: " << queue.peek() << ".\n";
      return false;
   }

   queue.remove();
   queue.remove();

   if (queue.peek() != 2)
   {
      std::cout << "Error, expected to peek 2 at front of queue but peeked: " << queue.peek() << ".\n";
      return false;
   }

   queue.add(7);
   if (queue.peek() != 2)
   {
      std::cout << "Error, expected to peek 2 at front of queue but peeked: " << queue.peek() << ".\n";
      return false;
   }

   queue.remove();
   queue.remove();
   
   if (queue.peek() != 7)
   {
      std::cout << "Error, expected to peek 7 at front of queue but peeked: " << queue.peek() << ".\n";
      return false;
   }

   queue.remove();

   if (queue.isEmpty() == false)
   {
      std::cout << "Error, expected isEmpty() to return true but returned false.\n";
      return false;
   }

   if (queue.peek() != -1)
   {
      std::cout << "Error, the queue is supposed to be empty but still hasthe number: " << queue.peek() << " in it.\n";
      return false;
   }

   return true;
}









