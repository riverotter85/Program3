/*
	Filename: RadixSortDriver.cpp
	Modified By: Logan Davis
	Last Date Modified: 10/26/2016
*/

#include "RadixSort.h"
#include "CD.h"
using CSC2110::CD;
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include "Text.h"
using CSC2110::String;

#include <iostream>
using namespace std;

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      delete cd;
   }
   delete iter;
}

int main()
{
   ListArray<CD>* list = CD::readCDs("cds.txt");
   int size = list->size();

   CD** cds = new CD*[size];

   ListArrayIterator<CD>* iter = list->iterator();
   int count = 0;
   while(iter->hasNext())
   {
      CD* cd = iter->next();
      cds[count] = cd;
      count++;
   }
   delete iter;

   //DO THIS
   //test both radix sort methods using the cds array
   cout << "Sorting CD list in ascending order...";
   CD** ascSortedCDs = RadixSort<CD>::radixSort(cds, size, 100, true, &CD::getRadixChar);
   
   cout << "done!" << endl;
   cout << "Press ENTER to display ascending CD list." << endl;
   cin.get();
   
   // Display items in ascending order
   for (int i = 0; i < size; i++)
   {
	   CD* currCD = ascSortedCDs[i];
	   String* CDKey = currCD->getKey();
	   CDKey->displayString();
	   cout << endl;
   }
   cout << endl;
   
   cout << "Sorting CD list in desceding order...";
   CD** descSortedCDs = RadixSort<CD>::radixSort(cds, size, 100, false, &CD::getRadixChar);
   
   cout << "done!" << endl;
   cout << "Press ENTER to display descending CD list." << endl;
   cin.get();
   
   // Display items in descending order
   for (int i = 0; i < size; i++)
   {
	   CD* currCD = descSortedCDs[i];
	   String* CDKey = currCD->getKey();
	   CDKey->displayString();
	   cout << endl;
   }

   delete[] cds;

   deleteCDs(list);
   delete list;

   return 0;
}
