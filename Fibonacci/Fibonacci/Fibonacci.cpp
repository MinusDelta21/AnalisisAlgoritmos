
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

int main()
{
  int number = 0;

  std::cout << "Enter the position in sequence: ";
  std::cin >> number;

  //get the start time
  auto startTime = high_resolution_clock::now();
  //Call Non recursive fibonacci function.
  int result = Fibonacci(number);
  //Get end time.
  auto endTime = high_resolution_clock::now();
  //Calculate elapsed time.
  duration<double> duration = endTime - startTime;

  PrintResult(result, duration.count());

  startTime = high_resolution_clock::now();
  //Call Non recursive fibonacci function.
  result = RecursiveFibonacci(number);
  //Get end time.
  endTime = high_resolution_clock::now();
  //Calculate elapsed time.
  duration = endTime - startTime;
  PrintResult(result, duration.count());

  return 0;
}

