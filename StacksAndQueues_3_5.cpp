#include <iostream>

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
      --m_top;
   }

   int peek()
   {
      return m_array[m_top];
   }

   bool isEmpty()
   {
      return m_top == -1;
   }

private:
   int m_top;
   int m_array[100];
};

void sort(
   Stack& regStack);

void print(
   Stack& regStack);

int main()
{
   Stack stack;
   stack.push(4);
   stack.push(1);
   stack.push(5);
   stack.push(2);
   stack.push(3);
   stack.push(7);

   std::cout << "First printing stack at beginning:\n";
   print(stack);

   sort(stack);
   std::cout << "Printing stack after sorting:\n";
   print(stack);


   int k;
   std::cin >> k;
   return 0;
}

void print(
   Stack& regStack)
{
   Stack tempStack;
   std::cout << "Printing stack:\n";
   while (!regStack.isEmpty())
   {
      tempStack.push(regStack.peek());
      std::cout << regStack.peek() << "\n";
      regStack.pop();
   }
   while (!tempStack.isEmpty())
   {
      regStack.push(tempStack.peek());
      tempStack.pop();
   }
   std::cout << "\n\n";
}

void sort(
   Stack& regStack)
{
   Stack tempStack;
   while (!regStack.isEmpty())
   {
      int temp(regStack.peek());
      regStack.pop();
      // Insert each element in regStack in sorted order into tempStack
      while (!tempStack.isEmpty() && tempStack.peek() > temp)
      {
         regStack.push(tempStack.peek());
         tempStack.pop();
      }
      tempStack.push(temp);
   }
   // Copy the elements from tempStack back into regStack
   while (!tempStack.isEmpty())
   {
      regStack.push(tempStack.peek());
      tempStack.pop();
   }
}


















