// SubsequenceDNA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*****************************************************************************/
/**
* @file    SubsequenceDNA.cpp
* @authors    Santiago Toll (santiago.toll97@gmail.com)
* @date    August 2019
* @brief   Find the longest subsequence in two given DNA Secuences.
*
* @bug     No known bugs.
*/
/*****************************************************************************/

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>



using std::vector;
using std::string;
using std::cout;

using std::chrono::high_resolution_clock;
using::std::chrono::duration;


char firstSequence[] = "ttcggtccgcctcacccaag";
                       

char secondSequence[] = "acgcgggcgctagagcctgc";

const int firstLenght = 21;
const int secondLenght = 21;

string currentLongest;

int Max(int first, int second)
{
  return (first > second) ? first : second;
}
/************************************************************************/
/* Longest Common Subsequence(Brute Force)                              */
/************************************************************************/
int BruteLCS(string first, string second,int firstSize,int secondSize) {
  if (firstSize == 0 || secondSize == 0) 
  {
    return 0;
  }

  else if (first[firstSize - 1] == second[secondSize - 1]) 
  {
    return 1 + BruteLCS(first, second, firstSize - 1, secondSize - 1);
  }
  else 
  {
    return Max(BruteLCS(first, second, firstSize, secondSize - 1), BruteLCS(first, second, firstSize - 1, secondSize));
  }

}
/************************************************************************/
/* Longest Common Subsequence(Dynamic Programming)                      */
/************************************************************************/
int DynamicLCS(char * first, char * second)
{
  int lcs[firstLenght+1][secondLenght+1];
  int i, j;

  for (i = 0; i <= firstLenght; i++)
  {
    for (j = 0; j <= secondLenght; j++)
    {
      if (i == 0 || j == 0)
        lcs[i][j] = 0;

      else if (first[i - 1] == second[j - 1])
        lcs[i][j] = lcs[i - 1][j - 1] + 1;

      else
        lcs[i][j] = Max(lcs[i - 1][j], lcs[i][j - 1]);
    }
  }
  return lcs[firstLenght][secondLenght]-1;
}
/************************************************************************/
/* Print Longest Common Subsequence (Dynamic Programming)               */
/************************************************************************/
int PrintLCS(char * first, char * second)
{
  int lcs[firstLenght + 1][secondLenght + 1];
  int i, j;

  for (i = 0; i <= firstLenght; i++)
  {
    for (j = 0; j <= secondLenght; j++)
    {
      if (i == 0 || j == 0)
        lcs[i][j] = 0;

      else if (first[i - 1] == second[j - 1])
        lcs[i][j] = lcs[i - 1][j - 1] + 1;

      else
        lcs[i][j] = Max(lcs[i - 1][j], lcs[i][j - 1]);
    }
    const int index = lcs[firstLenght + 1][secondLenght + 1];

    int i, j;
    for (i = firstLenght, j = secondLenght; i > 0 && j > 0;) {
      if (first[i - 1] == second[j - 1])
      {
        //Insert char at the beginning of string.
        currentLongest.insert(currentLongest.begin(), first[i - 1]);
        i--;
        j--;
      }
      else if (lcs[i - 1][j] > lcs[i][j - 1])
      {
        i--;
      }
      else
      {
        j--;
      }
    }
  }
  currentLongest.resize(lcs[firstLenght][secondLenght] - 1);
  return lcs[firstLenght][secondLenght] - 1;
}

/************************************************************************/
/* Driver Function                                                      */
/************************************************************************/
int main()
{
  //SetSequences();
  std::cout << "First Sequence: " << firstSequence << std::endl << std::endl;
  std::cout << "Second Sequence: " << secondSequence << std::endl << std::endl;
  
  //Brute Force Test
  std::cout << "Brute Force Test" << std::endl;
  auto startTime = high_resolution_clock::now();
  int longest = BruteLCS(firstSequence,secondSequence,strlen(firstSequence),strlen(secondSequence));
  auto endTime = high_resolution_clock::now();
  duration<float, std::milli> duration = (endTime - startTime);
  cout << "LCS lenght: " << longest << std::endl;
  cout << "Duration = " << duration.count() << "ms" << std::endl;
  
  //Dynamic Programming Test
  std::cout << std::endl << "Dynamic Programming Test" << std::endl;

  startTime = high_resolution_clock::now();
  longest = DynamicLCS(firstSequence, secondSequence);
  endTime = high_resolution_clock::now();
  duration = (endTime - startTime);
  cout << "LCS lenght: " << longest << std::endl;
  cout << "Duration = " << duration.count() << "ms" << std::endl;

  //Print LCS(Dynamic Programming)
  std::cout << std::endl << "Print LCS(Dynamic Programming) Test" << std::endl;
  startTime = high_resolution_clock::now();
  longest = PrintLCS(firstSequence, secondSequence);
  endTime = high_resolution_clock::now();
  duration = (endTime - startTime);
  cout << "Longest Common Substring: " + currentLongest << std::endl;
  cout << "LCS lenght: " << longest << std::endl;
  cout << "Duration = " << duration.count() << "ms" << std::endl;
}
