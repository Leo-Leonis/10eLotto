#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include "Extraction_event.hpp"
#include "Schedina.hpp"

void program(int type = 0) { return; }

int main() {
  std::random_device rd;
  std::mt19937 g(rd());

  std::vector<int> ninty = std::vector<int>(90);
  // creo i numeri
  std::iota(ninty.begin(), ninty.end(), 1);

  int numbers;
  std::cout << "quantità di numeri della schedina (da 1 a 10): ";
  std::cin >> numbers;
  if (numbers < 1) {
    std::cout
        << "il minimo è 1, per colpa tua la quantità è stata riportata a 1."
        << '\n';
    numbers = 1;
  } else if (numbers > 10) {
    std::cout
        << "il massimo è 10, per colpa tua la quantità è stata riportata a 10."
        << '\n';
    numbers = 10;
  }
  std::cout << '\n';

  std::vector<int> ten(numbers);
  if (numbers == 1) {
    std::cout << "inserire il numero: ";
    std::cin >> ten[0];
  } else {
    std::cout << "inserire i " << numbers << " numeri:\n";
    for (int i = 0; i < numbers; i++) {
      std::cout << "n. " << i + 1 << ": ";
      std::cin >> ten[i];
    }
  }
  std::cout << '\n' << "la schedina è quindi: ";
  for (int i : ten) {
    std::cout << i << ' ';
  }
  std::cout << "\n\n";

  int iterations;
  std::cout << "iterazioni (minimo 1): ";
  std::cin >> iterations;
  if (iterations < 1) {
    std::cout
        << "il minimo è 1, per colpa tua la quantità è stata riportata a 1."
        << '\n';
  }
  std::cout << '\n';

  for (int i = 0; i < iterations; i++) {
    // randomizzo l'ordine
    std::shuffle(ninty.begin(), ninty.end(), g);

    /* // stampa il vettore
    for (int i : ninty) {
      std::cout << i << ' ';
    }
    std::cout << "\n\n"; */
  }

  return 0;
}