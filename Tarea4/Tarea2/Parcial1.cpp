/*****************************************************************************/
/**
* @file    Parcial1.cpp
* @authors    Santiago Toll (santiago.toll97@gmail.com)
* @date    June 2019
* @brief   Examen parcial de Analisis de algoritmos(Primer parcial)
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
#include <algorithm>

using std::cout;
using std::endl;

using std::string;
using std::chrono::high_resolution_clock;
using::std::chrono::duration;
using std::vector;


/************************************************************************/
/* Generador de arreglo con valores random                              */
/************************************************************************/
vector<float> randomArray(int  size)
{
  vector<float> vector;
  for (int i = 0; i < size; i++)
  {
    vector.push_back((rand() % 1000 + 1) + (float)rand() / RAND_MAX);
  }
  return vector;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void printVector(vector<float> vector) {
  int size = vector.size();
  cout << "<";
  for (int i = 0; i < size; i++) {
    if (i < size - 1) {
      cout << vector.at(i);
      cout << ", ";
    }
    else {
      cout << vector.at(i);
    }

  }
  cout << ">" << endl << endl;
}

void insertion(vector<float>& vector) {
  if (vector.size() < 2) {
    return;
  }
  int size = vector.size();
  //Number that is being looked for
  float key;
  //Current index being checked
  float current;
  for (int i = 1; i < size; i++) {
    //Assign key
    key = vector[i];
    //Set current index
    current = i - 1;
    //Move elements
    while (current >= 0 && vector[current] > key) {
      vector[current + 1] = vector[current];
      current = current - 1;
    }
    //Assign new key
    vector[current + 1] = key;
  }
}
              
void f_benchmark(int testSize, int iterations, std::function<void(vector<float>&)> func, string fileName) {
  //Create vectors that will be used for benchmarking.
  const vector<float> randomVector = randomArray(testSize);


  vector<float> usedVector;

  //Create duration variables for each case.
  duration<float, std::micro> duration;
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
  fileText += "Random";
  fileText += "\n";

  //Iterate case for every input size up to test size.
  for (int element = 0; element < testSize; element++)
  {
    //Iterate to get average amount of time it takes to execute function.
    for (int iteration = 0; iteration < iterations; iteration++)
    {
      //Testing best case.
      //Testing average case.
      ///Set the current vector.
      usedVector = randomVector;
      usedVector.resize(element);
      startTime = high_resolution_clock::now();
      func(usedVector);
      endTime = high_resolution_clock::now();
      duration = (endTime - startTime);
      averageDuration += duration.count();


    }
    //Get average time.
    averageDuration /= iterations;

    //Write duration on file.
    fileText += std::to_string(element);
    fileText += ", ";
    fileText += std::to_string(averageDuration);
    fileText += "\n";
  }
  file.open(fileName);
  file.clear();
  file << fileText;
  file.close();

}

int main() {
  vector<float> testVector;
  f_benchmark(500, 10, insertion, "insertion.csv");
  printVector(testVector);
  return 0;
}