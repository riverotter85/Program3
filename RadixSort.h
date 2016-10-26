/*
	Filename: RadixSort.h
	Modified By: Logan Davis
	Last Date Modified: 10/26/2016
*/

#if !defined (RADIXSORT_H)
#define RADIXSORT_H

#include "QueueLinked.h"
using CSC2110::QueueLinked;

template < class T >
class RadixSort
{
   private:
      
	  // Pre: bin is the queue containing the copied list contents, curr_char is the character in which
	  //	  binSort compares between items each recursive call, num_chars is the amount of characters
	  //	  binSort will sort by, and getRadixChar is the static method pointer used to compare the
	  //	  contents of each item.
	  // Post: binSort sorts the contents of bin through recursively arranging it according to each
	  //	   character that can be compared.
      static void binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* item, int index));
      
	  // Pre: sort is the copy of the unsorted list passed, n is the number of items in the list,
	  //	  num_chars is the amount of characters radix will sort by, and getRadixChar is the
	  //	  static method pointer used to compare the contents of each item.
	  // Post: sort is arranged in ascending order by collecting the list's contents in a QueueLinked
	  //	   bin, and is sorted by calling the binSort method.
	  static void radixSortAsc(T** sort, int n, int num_chars, char (*getRadixChar) (T* item, int index));  //algorithm 1
      
	  // Pre: sort is the copy of the unsorted list passed, n is the number of items in the list,
	  //	  num_chars is the amount of characters radix will sort by, and getRadixChar is the
	  //	  static method pointer used to compare the contents of each item.
	  // Post: sort is arranged in descending order by collecting the list's contents in a QueueLinked
	  //	   bin, and is sorted by comparing the last character to the first through a backwards
	  //	   loop.
	  static void radixSortDesc(T** sort, int n, int num_chars, char (*getRadixChar) (T* item, int index));  //algorithm 2
 
   public:
      
      // Pre: sort is a list of the type specified (T), num_to_sort is the number of items that
	  //	  the list holds, num_chars is the amount of characters radix will sort by, asc determines
	  //	  whether the list is sorted in ascending (true) or descending (false) order, and
	  //	  getRadixChar is the static method pointer used to compare the contents of each list item.
	  // Post: radixSort creates a copy of the list passed to it, sorts the new list either in
	  //	   ascending or descending order, and returns the sorted list.
      static T** radixSort(T** sort, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index));
};

template < class T >
T** RadixSort<T>::radixSort(T** unsorted, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index))
{
   //DO THIS
   
   // Create a copy of the original list so that it
   // can still be used
   T** copy_list = new T*[num_to_sort];
   for (int i = 0; i < num_to_sort; i++)
   {
	   copy_list[i] = unsorted[i];
   }
   
   if (asc)
   {
	   radixSortAsc(copy_list, num_to_sort, num_chars, getRadixChar); // Ascending sort
   }
   else
   {
	   radixSortDesc(copy_list, num_to_sort, num_chars, getRadixChar); // Descending sort
   }
   
   return copy_list;
}

template < class T >
void RadixSort<T>::radixSortAsc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{
   //DO THIS
   
   // Create a master bin, and add all of the contents of sort to the queue
   QueueLinked<T>* bin = new QueueLinked<T>();
   for (int i = 0; i < n; i++)
   {
	   bin->enqueue(sort[i]);
   }
   
   int begin_char = 1; // 1-based
   binSort(bin, begin_char, num_chars, getRadixChar);
   
   // Add the now-sorted contents of the master bin to the array
   for (int i = 0; i < n; i++)
   {
	   sort[i] = bin->dequeue();
   }
   delete bin;
}

template < class T >
void RadixSort<T>::binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* st, int index))
{
   //DO THIS
   if (curr_char > num_chars || bin->isEmpty())
   {
	   return; // Return if the number of characters exceeded or the corresponding bin has no items to sort
   }
   
   int num_queues = 37;
   QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];
   
   for (int i = 0; i < num_queues; i++)
   {
	   bins[i] = new QueueLinked<T>();
   }
   
   for (int i = 0; i < num_queues; i++)
   {
	   while (!bin->isEmpty())
	   {
		   int index_val;
		   
		   char ascii_val = (*getRadixChar) (bin->peek(), curr_char);
		   
		   if (ascii_val >= 48 && ascii_val <= 57)
		   {
			   index_val = ascii_val - 47; // Digit character
		   }
		   else if (ascii_val >= 65 && ascii_val <= 90)
		   {
			   index_val = ascii_val - 54; // Upper case letter
		   }
		   else if (ascii_val >= 97 && ascii_val <= 122)
		   {
			   index_val = ascii_val - 86; // Lower case letter
		   }
		   else
		   {
			   index_val = 0; // Special case letter
		   }
		   
		   bins[index_val]->enqueue(bin->dequeue()); // Take each item out of the master bin into their corresponding sorting bin
	   }
   }
   
   for (int i = 0; i < num_queues; i++)
   {
	   binSort(bins[i], curr_char + 1, num_chars, getRadixChar); // Sort even further for each index in each bin
	   
	   while (!bins[i]->isEmpty())
	   {
		   bin->enqueue(bins[i]->dequeue()); // Add the sorted items from each bin back to the master bin
	   }
   }
   
   for (int i = 0; i < num_queues; i++)
   {
	   delete bins[i];
   }
   delete[] bins;
}

template < class T >
void RadixSort<T>::radixSortDesc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{
   int num_queues = 37;  //covers letters and digits
   QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];  

   //must instantiate each of the queues
   for (int i = 0; i < num_queues; i++)
   {
      //DO THIS
	  bins[i] = new QueueLinked<T>();
   }

   for (int i = num_chars; i > 0; i--)  //number of times to bin stuff
   {
      //DO THIS
	  for (int j = 0; j < n; j++)
	  {
		  int index_val;
		  
		  char ascii_val = (*getRadixChar) (sort[j], i);
		  
		  if (ascii_val >= 48 && ascii_val <= 57)
		  {
			  index_val = ascii_val - 47; // Digit character
		  }
		  else if (ascii_val >= 65 && ascii_val <= 90)
		  {
			  index_val = ascii_val - 54; // Upper case letter
		  }
		  else if (ascii_val >= 97 && ascii_val <= 122)
		  {
			  index_val = ascii_val - 86; // Lower case letter
		  }
		  else
		  {
			  index_val = 0; // Special case letter
		  }
		  
		  bins[index_val]->enqueue(sort[j]); // Add the item to its corresponding queue
	  }
	  
	  // For each queue, remove every item back into the array and sort them accordingly
	  int counter = 0;
	  for (int k = num_queues - 1; k >= 0; k--)
	  {
		while (!bins[k]->isEmpty())
		{
		  sort[counter] = bins[k]->dequeue();
		  counter++;
		}
	  }
   }

   for (int i = 0; i < num_queues; i++) 
   {
      delete bins[i];
   }

   delete[] bins;
}

#endif
