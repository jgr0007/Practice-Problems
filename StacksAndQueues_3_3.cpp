#include <iostream>
#include <memory>
#include <vector>

class Stack {

public:

   Stack(
      int stackLimit)
      :
      m_top(-1)
   {
      m_array = new int[stackLimit];
   }

   //Stack(Stack&& other)
   //{
   //   m_array = other.m_array;

   //   other.m_array = 0;
   //}

   //Stack &Stack::operator =(const Stack & other)
   //{
   //   m_array = other.m_array;
   //   return *this;
   //}

   ~Stack()
   {
      // TODO: Why does this destuctor get called? Any why does leaving this code in:
      
      //delete[] m_array;
     
      // ...cause a crash? I think it's a double delete somehow but not sure.
   }

   void push(
      int newData)
   {
      // Won't make this class handle size limits because that is the job of SetOfStacks.
      m_array[m_top + 1] = newData;
      ++m_top;
   }

   void pop()
   {
      // Won't make this class handle size limits because that is the job of SetOfStacks.
      if (isEmpty())
      {
         std::cout << "Warning, empty stack - nothing to pop.\n";
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
         std::cout << "Called peek on an empty array! Returning -1.\n";
         return -1;
      }
      else
      {
         return m_array[m_top];
      }
   }

   bool isEmpty()
   {
      return m_top == -1;
   }

   int size()
   {
      return m_top + 1;
   }

private:
   int m_top;
   int* m_array;

};

class SetOfStacks {

public:
   SetOfStacks(
      int stackLimit)
      :
      m_stackLimit(stackLimit),
      m_topStack(-1)
   {

   }

   void push(
      int newData)
   {
      if (isEmpty())
      {
         m_stacks.emplace_back(m_stackLimit);
         ++m_topStack;
         m_stacks[m_topStack].push(newData);
      }
      else if (m_stacks[m_topStack].size() < m_stackLimit)
      {
         m_stacks[m_topStack].push(newData);
      }
      else
      {
         m_stacks.emplace_back(m_stackLimit);
         ++m_topStack;
         m_stacks[m_topStack].push(newData);
      }
   }

   void pop()
   {
      // First make sure we aren't popping an entirely empty set of stacks. If so, print warning and do nothing.
      if (isEmpty())
      {
         std::cout << "Warning, all stacks are empty. Nothing to pop. Doing nothing.\n";
      }
      // Then see if current stack to pop is only 1 element. If so, remove stack entirely and decrement m_topStack;
      else if (m_stacks[m_topStack].size() == 1)
      {
         m_stacks.pop_back();
         --m_topStack;
      }
      // Otherwise, pop from current stack as normal.
      else
      {
         m_stacks[m_topStack].pop();
      }
   }

   int peek()
   {
      if (isEmpty())
      {
         std::cout << "Warning, all stacks are empty. Nothing to peek. Returning -1.\n";
         return -1;
      }
      else
      {
         return m_stacks[m_topStack].peek();
      }
   }

   bool isEmpty()
   {
      return m_topStack == -1;
   }

   void popAt(
      int stackNum)
   {
      // First make sure that stack is poppable from.
      if (isEmpty())
      {
         std::cout << "Warning, all stacks are empty so cannot popAt anything. Doing nothing.\n";
      }
      else if (m_topStack < stackNum - 1)
      {
         std::cout << "Warning, asked for a stack that does not exist. Doing nothing because can't pop stack that doesn't exist.\n";
      }
      else
      {
         if (m_stacks[stackNum - 1].size() == 1)
         {
            m_stacks.erase(m_stacks.begin()+ (stackNum - 1));
            --m_topStack;
         }
         else
         {
            m_stacks[stackNum - 1].pop();
         }
      }
   }

private:

   int m_stackLimit;
   std::vector<Stack> m_stacks;
   int m_topStack;
};

bool tests();

int main()
{
   if (tests())
   {
      std::cout << "\n\n********All tests passed.\n";
   }
   else
   {
      std::cout << "\n\n********At least one test failed.\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

bool tests()
{
   SetOfStacks set(3);

   std::cout << "Testing empty set.\n";
   if (set.peek() != -1)
   {
      std::cout << "Error with empty set. Expected to peek -1 but peeked: " << set.peek() << ".\n";
      return false;
   }
   if (!set.isEmpty())
   {
      std::cout << "Error with empty set. Expected isEmpty to return true but it returned false.\n";
      return false;
   }
   std::cout << "Next line should print a warning.\n\n";
   set.pop();
   std::cout << "\nNext line should print another warning.\n";
   set.popAt(0);
   std::cout << std::endl;

   // Fill three stacks
   set.push(1);
   set.push(2);
   set.push(3);
   set.push(4);
   set.push(5);
   set.push(6);
   set.push(7);
   set.push(8);
   set.push(9);

   if (set.peek() != 9)
   {
      std::cout << "Error with full set. Expected to peek 9 but peeked: " << set.peek() << ".\n";
      return false;
   }

   // Remove middle stack

   set.popAt(2);
   set.popAt(2);
   set.popAt(2);

   if (set.peek() != 9)
   {
      std::cout << "Error removing middle set. Expected to peek 9 but peeked: " << set.peek() << ".\n";
      return false;
   }

   set.pop();
   if (set.peek() != 8)
   {
      std::cout << "Error removing middle set. Expected to peek 8 but peeked: " << set.peek() << ".\n";
      return false;
   }

   set.pop();
   if (set.peek() != 7)
   {
      std::cout << "Error removing middle set. Expected to peek 7 but peeked: " << set.peek() << ".\n";
      return false;
   }

   std::cout << "\nNext line should print a third warning.\n";
   set.popAt(2);
   std::cout << std::endl;

   // Remove remaining elements
   set.pop();
   set.pop();
   set.pop();

   if (!set.isEmpty())
   {
      std::cout << "Error after clearing set. Expected isEmpty to return true but it returned false.\n";
      return false;
   }

   return true;
}










