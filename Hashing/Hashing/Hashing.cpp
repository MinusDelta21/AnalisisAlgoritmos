// Hashing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <vector>
#include <string.h>
#include <iostream>
#include <ctime>
#include <random>
using std::vector;
using std::string;

struct HashTable {
  vector<vector<float>> hashTable;
  int size;
  int primeNumber;

  int GenerateRandomPrime() {
    vector<int> primes;
    //Insert some prime numbers
    primes.push_back(3);
    primes.push_back(5);
    primes.push_back(7);
    primes.push_back(11);
    primes.push_back(13);
    primes.push_back(17);
    primes.push_back(19);
    //Pick a random prime number
    std::srand(std::time(0));
    primeNumber = primes[0 + rand() % ((primes.size() + 1) - 0)];
  }

  void init(int inputSize) {
    size = inputSize;
    hashTable.resize(size);
    GenerateRandomPrime();
  }

  void insert(int key, int obj) {
    hashTable[key].push_back(obj);
  }

  void multiplicationHash(int obj) {

    const long long bitObject = 2317448506;

    int key = obj * int(1432261944);
    key = (key & bitObject) >> (32 - primeNumber);
    hashTable[key %size].push_back(obj);
  }

  void divisionHash(int obj) {
    int hashed = 0;
    int halfSize = size / 2;
    float arg1 = 0.0f;
    float arg2 = 0.0f;

    //first argument for insertion
    arg1 = obj % (halfSize);
    //second argument for insertion
    arg2 = std::floor(obj % size);

    hashTable[static_cast<int>(arg1 + arg2) % hashTable.size()].push_back(obj);
  }

  void universalHash(int obj) {
    int key = static_cast<int>((std::rand() % hashTable.size() * obj + 1 + std::rand() % (hashTable.size() - 1) * (obj >> 32) + primeNumber) >> 32);
    hashTable[key % size].push_back(obj);
  }


};



int main()
{
  HashTable hashTable;
  hashTable.GenerateRandomPrime();

    std::cout << "Hello World!\n"; 
}


