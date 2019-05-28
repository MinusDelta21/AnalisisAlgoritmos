/*****************************************************************************/
/**
* @file    Tarea2.cpp
* @authors    Santiago Toll (santiago.toll97@gmail.com)
* @date    May 2019
* @brief   Implementation of some sorting algorithms.
*
* @bug     No known bugs.
*/
/*****************************************************************************/

#include "pch.h"
#include <chrono>
#include <ctime>
#include <functional>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::endl;

using std::string;
using std::chrono::high_resolution_clock;
using::std::chrono::duration;
using std::vector;

/************************************************************************/
/* Sorted Enum                                                          */
/************************************************************************/
enum SORT_METHOD {
  ASCENDING,
  DESCENDING,
  RANDOM
};

/************************************************************************/
/* Vector Generator functions                                           */
/************************************************************************/
vector<int> ascendingVector(int size) {
  vector<int> returnVector;
  for (int i = 0; i < size; i++) {
    returnVector.push_back(i);
  }
  return returnVector;
}

vector<int> descendingingVector(int size) {
  vector<int> returnVector;
  for (int i = size; i > 0; i--) {
    returnVector.push_back(i);
  }
  return returnVector;
}

vector<int> randomVector(int size,int min, int max) {
  vector<int> returnVector;
  std::srand(std::time(0));
  for (int i = 0; i < size; i++) {
    int random =  min + rand() % ((max + 1)-min); //Generate a random numbver between min and max(inclusive).

    returnVector.push_back(random);
  }
  return returnVector;
}

/************************************************************************/
/* Vector Print functions                                               */
/************************************************************************/
void printVector(vector<int> vector) {
  int size = vector.size();
  cout << "<";
  for (int i = 0; i < size; i++) {
    if (i < size-1) {
      cout << vector.at(i);
      cout << ", ";
    }
    else {
      cout << vector.at(i);
    }
    
  }
  cout << ">"<< endl <<endl;
}

void printIndex(int index) {
  cout << "Found desired number at index: " << index << endl;
}
/************************************************************************/
/* Bubble Sort functions                                                */
/************************************************************************/
void bubbleSort(vector<int>& vector) {
  if (vector.size() < 2) {
    return;
  }
  int size = vector.size(); //Save the vector size to make this efficient.
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size-1; j++) {
      if (vector[j] > vector[j + 1]) {
        std::swap(vector[j], vector[j + 1]); // Swap the positions.
      }
    }
  }
}

/************************************************************************/
/* Quick Sort functions                                                 */
/************************************************************************/
int partition(vector<int>& vector, int low, int high) {
  int pivot = vector[high]; // Find the pivot for this iteration.
  int i = low - 1;
  for (int j = low; j < high; j++) {
    if (vector[j] < pivot) {
      i++;
      std::swap(vector[i], vector[j]); // Swap the positions
    }
  }
  std::swap(vector[i + 1], vector[high]); // Swap the positions
  return(i + 1);
}

void quickSort(vector<int>& vector, int low, int high) {
  if (vector.size() < 2) {
    return;
  }
  if (low < high) {
    int partitionIndex = partition(vector, low, high);
    //Recursivity to travel the binary tree
    quickSort(vector, low, partitionIndex - 1);
    quickSort(vector, partitionIndex + 1, high);
  }
}
void quickSortCall(vector<int>& vector) {
  quickSort(vector, 0, vector.size() - 1);
}
/************************************************************************/
/* Heap sort functions                                                  */
/************************************************************************/
void heapify(vector<int>& vector, int root, int size) {
  int largest = root;
  int leftChild = (2 * root) + 1;
  int rightChild = (2 * root) + 2;
  //Check if children are smaller than root
  //Left child
  if (leftChild < size && vector[leftChild] > vector[largest]) {
    largest = leftChild;
  }
  //Right child
  if (rightChild < size && vector[rightChild] > vector[largest]) {
    largest = rightChild;
  }
  //If root is not the largest
  if (largest != root) {
    std::swap(vector[root], vector[largest]);
    //Make this recursive
    heapify(vector, largest, size);
  }
}

void heapSort(vector<int>& vector) {
  if (vector.size() < 2) {
    return;
  }
  int size = vector.size();
  //Rearrange array
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(vector, i, size);
  }
  //Extract element from heap
  for (int i = size-1;i>=0;i--)
  {
  std::swap(vector[0], vector[i]);
  heapify(vector, 0, i);
  }
}

/************************************************************************/
/* Insertion sort                                                       */
/************************************************************************/
void insertionSort(vector<int>& vector) {
  if (vector.size() < 2) {
    return;
  }
  int size = vector.size();
  //Number that is being looked for
  int key;
  //Current index being checked
  int current;
  for (int i = 1; i < size; i++) {
    //Assign key
    key = vector[i];
    //Set current index
    current = i - 1;
    //Move elements
    while (current >= 0 && vector[current] >key) {
      vector[current + 1] = vector[current];
      current = current - 1;
    }
    //Assign new key
    vector[current + 1] = key;
  }
}

/************************************************************************/
/* Merge Sort functions                                                 */
/************************************************************************/
void merge(vector<int>& inputVector, int left, int middle, int right) {
  int leftIndex; //Index of the first subarray.
  int rightIndex; //Index of the second subarray.
  int mergeIndex; //Index of the merged subarray.

  int leftSize = middle - left + 1;
  int rightSize = right - middle;

  vector<int> leftVector, rightVector; //Temporary vectors.

  for (leftIndex = 0; leftIndex < leftSize; leftIndex++) {
    leftVector.push_back(inputVector.at(left + leftIndex));
  }
  for (rightIndex = 0; rightIndex < rightSize; rightIndex++) {
    rightVector.push_back(inputVector.at(middle +1 + rightIndex));
  }
  //Set the indices.
  leftIndex = 0;
  rightIndex = 0;
  mergeIndex = left;

  //Merge the temporary vectors into original.
  while (leftIndex < leftSize && rightIndex < rightSize)
  {
    if (leftVector[leftIndex] <= rightVector[rightIndex]) {
      inputVector[mergeIndex] = leftVector[leftIndex];
      leftIndex++;
    }
    else {
      inputVector[mergeIndex] = rightVector[rightIndex];
      rightIndex++;
    }
  }
  //Copy remaining elements(if any)
  while (leftIndex < leftSize)
  {
    inputVector[mergeIndex] = leftVector[leftIndex];
    leftIndex++;
    mergeIndex++;
  }
  while (rightIndex < rightSize)
  {
    inputVector[mergeIndex] = rightVector[rightIndex];
    rightIndex++;
    mergeIndex++;
  }
}
void mergeSort(vector<int>& vector, int left, int right) {
  if (vector.size() < 2) {
    return;
  }
  if (left < right) {
    int middle = left + (right - left) / 2;
    //Recursivity
    mergeSort(vector, left, middle);
    mergeSort(vector, middle + 1, right);

    merge(vector, left, middle, right);
  }
}
void mergeSortCall(vector<int>& vector) {
  mergeSort(vector, 0, vector.size() - 1);
}
/************************************************************************/
/* Sorted array functions                                               */
/************************************************************************/
int binarySearch(vector<int>& vector,int left, int right, int key) {  
  if (vector.size() <2)
  {
    return -900;
  }
  if (right < left) {
    return -999;
  }

  int mid = left + ((right-left) / 2);
  if (vector[mid] == key) {
    return mid;
  }
  if (vector[mid] > key) {
    return binarySearch(vector, left, mid - 1, key);
  }
  else if (vector[mid] < key) {
    return binarySearch(vector, mid + 1, right, key);
  }
  else {
    return mid;
  }
}
int binarySearchCall(vector<int>& vector, int key) {
  int left = 0;
  int right = vector.size() - 1;
  return binarySearch(vector, left, right, key);
}
/************************************************************************/
/* Unsorted array functions                                             */
/************************************************************************/
int linearSearch(vector<int>& vector, int key) {
  if (vector.size() < 2) {
    return -900;
  }
  int size = vector.size();
  for (int i = 0; i<size; i++)
  {
    if (vector[i] == key) {
      return i;
    }
  }
}
vector<int> linearSearchAll(vector<int>& inputVector, int key) {
  if (inputVector.size() < 2) {
    return ascendingVector(1);
  }
  int size = inputVector.size();
  vector<int> tempVector;
  for (int i = 0; i < size; i++)
  {
    if (inputVector[i] == key) {
      tempVector.push_back(i);
    }
  }
  return tempVector;
}

/************************************************************************/
/* Benchmarking functions                                               */
/************************************************************************/
template <typename ...Args>
void benchmark(int testSize, int iterations, std::function<void(vector<int>&)> func, string fileName) {
  //Create vectors that will be used for benchmarking.
  const vector<int> bestVector = ascendingVector(testSize);
  const vector<int> worstVector = descendingingVector(testSize);
  const vector<int> averageVector = randomVector(testSize, 0, 9);
  vector<int> usedVector;

  //Create duration variables for each case.
  duration<float, std::micro> duration;

  float bestDuration  = 0;
  float worstDuration = 0;
  float averageDuration = 0;

  //Create start and end time so it doesn't happen on every loop.
  auto startTime = high_resolution_clock::now();
  auto endTime = high_resolution_clock::now();

  //Initialize file stream.
  std::ofstream file;
  string fileText;

  //Write function name at file start.
  fileText += fileName;
  fileText += "\n";
  fileText += "Elements";
  fileText += ", ";
  fileText += "Best";
  fileText += ", ";
  fileText += "Worst";
  fileText += ", ";
  fileText += "Average"; 
  fileText += "\n";

  //Iterate case for every input size up to test size.
  for (int element =0; element < testSize;element++)
  {
    //Iterate to get average amount of time it takes to execute function.
    for (int iteration =0; iteration < iterations; iteration++)
    {
      //Testing best case.
      ///Set the current vector.
      usedVector = bestVector;
      usedVector.resize(element);
      startTime = high_resolution_clock::now();
      func(usedVector);
      endTime = high_resolution_clock::now();
      duration = (endTime - startTime);
      bestDuration += duration.count();

      //Testing worst case.
      ///Set the current vector.
      usedVector = worstVector;
      usedVector.resize(element);
      startTime = high_resolution_clock::now();
      func(usedVector);
      endTime = high_resolution_clock::now();
      duration = (endTime - startTime);
      worstDuration += duration.count();

      //Testing average case.
      ///Set the current vector.
      usedVector = averageVector;
      usedVector.resize(element);
      startTime = high_resolution_clock::now();
      func(usedVector);
      endTime = high_resolution_clock::now();
      duration = (endTime - startTime);
      averageDuration += duration.count();
    }
    //Get average time.
    bestDuration /= iterations;
    worstDuration /= iterations;
    averageDuration /= iterations;

    //Write duration on file.
    fileText += std::to_string(element);
    fileText += ", ";
    fileText += std::to_string(bestDuration);
    fileText += ", ";
    fileText += std::to_string(worstDuration);
    fileText += ", ";
    fileText += std::to_string(averageDuration);
    fileText += "\n";
  }
  file.open(fileName);
  file.clear();
  file << fileText;
  file.close();

}


/************************************************************************/
/* Main function(where algorithms are tested)                           */
/************************************************************************/
int main()
{
  vector<int> testVector = randomVector(500,0,9);
  printVector(testVector);
  printIndex(binarySearchCall(testVector, 5));
  printIndex(linearSearch(testVector, 5));
  printVector(linearSearchAll(testVector, 5));

  //benchmark(500, 10, bubbleSort, "BubbleSort");
  //benchmark(500, 10, quickSortCall, "QuickSort");
  //benchmark(500, 10, heapSort, "HeapSort");
  //benchmark(500, 10, insertionSort, "InsertionSort");
  //benchmark(500, 10, mergeSortCall, "MergeSort");
  return 0;
}
