#include <iostream>
#include <iomanip>
#include <list>
#include <string>

enum ANIMAL_TYPE {
   ANIMAL_TYPE_CAT = 0,
   ANIMAL_TYPE_DOG = 1,
   ANIMAL_TYPE_LAST = 2
};

class Animal {
public:
   Animal(
      int storageStamp,
      ANIMAL_TYPE animalType,
      const std::string& name)
      :
      m_storageStamp(storageStamp),
      m_animalType(animalType),
      m_name(name)
   {

   }

   Animal& operator=(const Animal& animal)
   {
      this->m_animalType = animal.m_animalType;
      this->m_storageStamp = animal.m_storageStamp;
      this->m_name = animal.m_name;

      return *this;
   }

   int storageStampGet()
   {
      return m_storageStamp;
   }

   ANIMAL_TYPE animalTypeGet()
   {
      return m_animalType;
   }

   std::string nameGet()
   {
      return m_name;
   }


private:
   int m_storageStamp;
   ANIMAL_TYPE m_animalType;
   std::string m_name;
};

class AnimalShelter {
public:
   AnimalShelter()
      :
      m_currentStorageStamp(0)
   {
   }

   void enqueue(
      ANIMAL_TYPE animalType,
      const std::string& name)
   {
      // Could add error checking here using ANIMAL_TYPE_LAST to make sure 
      // no one tries to add animals who aren't cats or dogs.
      Animal newAnimal(m_currentStorageStamp, animalType, name);

      if (animalType == ANIMAL_TYPE_CAT)
      {
         m_cats.push_back(newAnimal);
      }
      else
      {
         m_dogs.push_back(newAnimal);
      }

      ++m_currentStorageStamp;
   }

   Animal dequeueAny()
   {
      if (m_cats.front().storageStampGet() < m_dogs.front().storageStampGet())
      {
         Animal adoptedCat(m_cats.front());
         m_cats.pop_front();
         return adoptedCat;
      }
      else
      {
         Animal adoptedDog(m_dogs.front());
         m_dogs.pop_front();
         return adoptedDog;
      }
   }

   Animal dequeueCat()
   {
      Animal adoptedCat(m_cats.front());
      m_cats.pop_front();
      return adoptedCat;
   }

   Animal dequeueDog()
   {
      Animal adoptedDog(m_dogs.front());
      m_dogs.pop_front();
      return adoptedDog;
   }

   void currentResidentsPrint()
   {
      std::cout << "Printing cats:\n";
      for (std::list<Animal>::iterator it = m_cats.begin(); it != m_cats.end(); it++)
      {
         std::cout << "Name: " << std::setw(8) << it->nameGet() << "        Storage Stamp: " << std::setw(2) << it->storageStampGet() << "\n";
      }

      std::cout << "\nPrinting dogs:\n";
      for (std::list<Animal>::iterator it = m_dogs.begin(); it != m_dogs.end(); it++)
      {
         std::cout << "Name: " << std::setw(8) << it->nameGet() << "        Storage Stamp: " << std::setw(2) << it->storageStampGet() << "\n";
      }
   }

private:
   int m_currentStorageStamp;

   std::list<Animal> m_cats;
   std::list<Animal> m_dogs;
};

bool tests();

int main()
{
   if (tests())
   {
      std::cout << "\n\n\n******** All tests passed.\n";
   }
   else
   {
      std::cout << "\n\n\n******** At least one test failed!\n";
   }

   int k;
   std::cin >> k;
   return 0;
}

bool tests()
{
   AnimalShelter shelter;

   shelter.enqueue(ANIMAL_TYPE_CAT, "Lucy");
   shelter.enqueue(ANIMAL_TYPE_DOG, "Dan");
   shelter.enqueue(ANIMAL_TYPE_DOG, "Steve");
   shelter.enqueue(ANIMAL_TYPE_DOG, "Matt");
   shelter.enqueue(ANIMAL_TYPE_DOG, "Nick");
   shelter.enqueue(ANIMAL_TYPE_CAT, "Sheri");
   shelter.enqueue(ANIMAL_TYPE_DOG, "Ron");
   shelter.enqueue(ANIMAL_TYPE_CAT, "Marsha");
   shelter.enqueue(ANIMAL_TYPE_DOG, "Scott");
   shelter.enqueue(ANIMAL_TYPE_CAT, "Trish");
   shelter.enqueue(ANIMAL_TYPE_DOG, "Peter");
   shelter.enqueue(ANIMAL_TYPE_CAT, "Larissa");

   std::cout << "Shelter residents at beginning of test:\n\n";
   shelter.currentResidentsPrint();

   Animal newAdoption(shelter.dequeueAny());
   if (newAdoption.animalTypeGet() != ANIMAL_TYPE_CAT || newAdoption.nameGet() != "Lucy")
   {
      std::cout << "Expected to adopt Lucy but got: " << newAdoption.nameGet();
      return false;
   }

   newAdoption = shelter.dequeueAny();
   if (newAdoption.animalTypeGet() != ANIMAL_TYPE_DOG || newAdoption.nameGet() != "Dan")
   {
      std::cout << "Expected to adopt Dan but got: " << newAdoption.nameGet();
      return false;
   }

   newAdoption = shelter.dequeueCat();
   if (newAdoption.animalTypeGet() != ANIMAL_TYPE_CAT || newAdoption.nameGet() != "Sheri")
   {
      std::cout << "Expected to adopt Sheri but got: " << newAdoption.nameGet();
      return false;
   }

   newAdoption = shelter.dequeueDog();
   if (newAdoption.animalTypeGet() != ANIMAL_TYPE_DOG || newAdoption.nameGet() != "Steve")
   {
      std::cout << "Expected to adopt Steve but got: " << newAdoption.nameGet();
      return false;
   }

   newAdoption = shelter.dequeueDog();
   if (newAdoption.animalTypeGet() != ANIMAL_TYPE_DOG || newAdoption.nameGet() != "Matt")
   {
      std::cout << "Expected to adopt Matt but got: " << newAdoption.nameGet();
      return false;
   }

   newAdoption = shelter.dequeueAny();
   if (newAdoption.animalTypeGet() != ANIMAL_TYPE_DOG || newAdoption.nameGet() != "Nick")
   {
      std::cout << "Expected to adopt Nick but got: " << newAdoption.nameGet();
      return false;
   }

   newAdoption = shelter.dequeueAny();
   if (newAdoption.animalTypeGet() != ANIMAL_TYPE_DOG || newAdoption.nameGet() != "Ron")
   {
      std::cout << "Expected to adopt Ron but got: " << newAdoption.nameGet();
      return false;
   }

   newAdoption = shelter.dequeueDog();
   if (newAdoption.animalTypeGet() != ANIMAL_TYPE_DOG || newAdoption.nameGet() != "Scott")
   {
      std::cout << "Expected to adopt Scott but got: " << newAdoption.nameGet();
      return false;
   }

   newAdoption = shelter.dequeueAny();
   if (newAdoption.animalTypeGet() != ANIMAL_TYPE_CAT || newAdoption.nameGet() != "Marsha")
   {
      std::cout << "Expected to adopt Marsha but got: " << newAdoption.nameGet();
      return false;
   }

   newAdoption = shelter.dequeueAny();
   if (newAdoption.animalTypeGet() != ANIMAL_TYPE_CAT || newAdoption.nameGet() != "Trish")
   {
      std::cout << "Expected to adopt Trish but got: " << newAdoption.nameGet();
      return false;
   }

   newAdoption = shelter.dequeueCat();
   if (newAdoption.animalTypeGet() != ANIMAL_TYPE_CAT || newAdoption.nameGet() != "Larissa")
   {
      std::cout << "Expected to adopt Larissa but got: " << newAdoption.nameGet();
      return false;
   }

   newAdoption = shelter.dequeueDog();
   if (newAdoption.animalTypeGet() != ANIMAL_TYPE_DOG || newAdoption.nameGet() != "Peter")
   {
      std::cout << "Expected to adopt Peter but got: " << newAdoption.nameGet();
      return false;
   }

   return true;
}








