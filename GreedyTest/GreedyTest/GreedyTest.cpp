// GreedyTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

int coins[4] = { 1,2,5,10 };
int numMonedas = 0;

void Greedy(int amount) {
  while (amount >= coins[3])
  {
    amount -= coins[3];
    std::cout << "Moneda de 10" << std::endl;
  }
  while (amount >= coins[2])
  {
    amount -= coins[2];
    std::cout << "Moneda de 5" << std::endl;
  }
  while (amount >= coins[1])
  {
    amount -= coins[1];
    std::cout << "Moneda de 2" << std::endl;
  }
  while (amount >= coins[0])
  {
    amount -= coins[0];
    std::cout << "Moneda de 1" << std::endl;
  }
}
void RecursiveGreedy(int amount) {
  if (amount == 0) {
    return;
  }
  numMonedas++;
  if (amount >= coins[3]) {
    amount -= coins[3];
    std::cout << "Moneda de 10" << std::endl;
    RecursiveGreedy(amount);
  }
  else if (amount >= coins[2]) {
    amount -= coins[2];
    std::cout << "Moneda de 5" << std::endl;
    RecursiveGreedy(amount);
   
  }
  else if (amount >= coins[1]) {
    amount -= coins[1];
    std::cout << "Moneda de 2" << std::endl;
    RecursiveGreedy(amount);
  }
  else if (amount >= coins[0]) {
    amount -= coins[0];
    std::cout << "Moneda de 1" << std::endl;
    RecursiveGreedy(amount);

  }
}
int main()
{
  int amount = 72;
  Greedy(amount);
  std::cout <<std::endl;
  RecursiveGreedy(amount);
  std::cout << std::endl<< "Numero de monedas = " << numMonedas <<std::endl;

}