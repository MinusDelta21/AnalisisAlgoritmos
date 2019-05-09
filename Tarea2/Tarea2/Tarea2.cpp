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
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <string>
#include <chrono>
#include <string>

using std::cout;
using std::endl;

using std::string;
using std::chrono::high_resolution_clock;
using::std::chrono::duration;
using std::vector;

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

/************************************************************************/
/* Bubble Sort functions                                                */
/************************************************************************/
void bubbleSort(vector<int>& vector) {
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
  if (low < high) {
    int partitionIndex = partition(vector, low, high);
    //Recursivity to travel the binary tree
    quickSort(vector, low, partitionIndex - 1);
    quickSort(vector, partitionIndex + 1, high);
  }
}

int main()
{
  vector<int> testVector;
  testVector = randomVector(40,0,9);
  printVector(testVector);
  
  cout << "Sorted vector: " << endl;
  auto startTime = high_resolution_clock::now();
  //bubbleSort(testVector);
  quickSort(testVector,0,testVector.size()-1);
  auto endTime = high_resolution_clock::now();
  duration<float, std::micro> duration = endTime - startTime;
  printVector(testVector);
  cout << "Elapsed time: ";
  cout << duration.count() << endl;
  return 0;
}
