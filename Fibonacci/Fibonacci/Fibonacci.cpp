
/*****************************************************************************/
/**
* @file       Fibonacci.cpp
* @authors    Santiago Toll (santiago.toll97@gmail.com)
* @date       May 2019
* @brief      Fibonacci in c++
*
* @bug     No known bugs.
*/
/*****************************************************************************/

/************************************************************************/
/*
 * Includes
 */
 /************************************************************************/
#include "pch.h"
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::string;
using std::chrono::high_resolution_clock;
using::std::chrono::duration;


/************************************************************************/
/* Fibonacci using recursivity.                                         */
/************************************************************************/
int
RecursiveFibonacci(int numberber)
{
  if (numberber <= 1)
  {
    return numberber;
  }
  else
  {
    return RecursiveFibonacci(numberber - 1) + RecursiveFibonacci(numberber - 2);
  }
}

/************************************************************************/
/* Fibonacci(non recursive)                                             */
/************************************************************************/
int
Fibonacci(int n)
{
  //initialize variable
  int n1 = 0, n2 = 1;

  if (n <= 1)
  {
    return n;
  }
  else
  {
    int tmp = 0;
    for (int i = 0; i < n - 1; ++i)
    {
      tmp = n1 + n2;
      n1 = n2;
      n2 = tmp;
    }
    return tmp;
  }
}

/************************************************************************/
/* Function used to print results                                       */
/************************************************************************/
void
PrintResult(int result, double duration)
{
  std::string  text = "Result: " + std::to_string(result) + "\n" +
    "Elapsed time: " + std::to_string(duration) + "\n";
  std::cout << text << std::endl;
}

/************************************************************************/
/* Write .csv                                                           */
/************************************************************************/
void
writeCSV(vector<int> position, vector<double> time, string fileName) {
  std::ofstream file;
  file.open(fileName);
  file.clear();
  for (int i = 0; i < position.size(); i++) {
    file << position[i] << ", ";
    file << time[i] << "\n";
  }
  
  file.close();
}
int main()
{
  int number = 0;
  vector<int> numbers;
  vector<double> times;
  std::cout << "Enter the position in sequence: ";
  std::cin >> number;

  //get the start time
  //Call Non recursive fibonacci function.
  int result;
  double accumulatedDuration = 0;
  for (int i = 0; i < number; i++) {
    auto startTime = high_resolution_clock::now();
    result = Fibonacci(i);
    //Get end time.
    auto endTime = high_resolution_clock::now();
    numbers.push_back(result);
    //Calculate elapsed time.
    duration<double, std::micro> duration = endTime - startTime;
    accumulatedDuration += duration.count();
    times.push_back(accumulatedDuration);
    PrintResult(result, accumulatedDuration);
  }
  writeCSV(numbers, times, "Fibonacci.csv");

  accumulatedDuration = 0;
  numbers.clear();
  times.clear();
  for (int i = 0; i < number; i++) {
    auto startTime = high_resolution_clock::now();
    result = RecursiveFibonacci(i);
    //Get end time.
    auto endTime = high_resolution_clock::now();
    numbers.push_back(result);
    //Calculate elapsed time.
    duration<double, std::micro> duration = endTime - startTime;
    accumulatedDuration += duration.count();
    times.push_back(accumulatedDuration);
    PrintResult(result, accumulatedDuration);
  }
  writeCSV(numbers, times, "RecursiveFibonacci.csv");

  return 0;
}

