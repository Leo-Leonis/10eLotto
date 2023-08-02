#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include "Extraction_event.hpp"
#include "Schedina.hpp"

// void program(int type = 0) { return; }

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
    std::cout << "inserire i " << numbers << " numeri (da 1 a 90):\n";
    int n_check;
    for (int i = 0; i < numbers; i++) {
      std::cout << "n. " << i + 1 << ": ";
      std::cin >> n_check;
      if (std::count(ten.begin(), ten.end(), n_check) != 0) {
        std::cout << "ATTENZIONE: numero già inserito. Riprova a inserire il ";
        i--;
      } else if (n_check < 1 || n_check > 90) {
        std::cout << "ATTENZIONE: valore fuori range (da 1 a 90). Riprova a "
                     "inserire il ";
        i--;
      } else {
        ten[i] = n_check;
      }
    }
  }
  std::cout << '\n' << "la schedina è quindi: ";
  for (int i : ten) {
    std::cout << i << ' ';
  }
  std::cout << "\n\n";

  Schedina scheda(ten, 1, 0, 0, 0, 0, 0, 0);
  ///*TEST TEST TEST*/ std::cout << "QUESTO è UNA PROVA////////////\n";

  int iterations;
  std::cout << "iterazioni (minimo 1): ";
  std::cin >> iterations;
  if (iterations < 1) {
    std::cout
        << "il minimo è 1, per colpa tua la quantità è stata riportata a 1."
        << '\n';
  }
  std::cout << '\n';

  int win_n = 0;

  // ciclo iterazioni
  for (int i = 0; i < iterations; i++) {
    // randomizzo l'ordine
    std::shuffle(ninty.begin(), ninty.end(), g);

    Extraction_event extraction(ninty, 0);

    // stampa il vettore
    std::cout << "il vettore ninty è: ";
    for (int i : ninty) {
      std::cout << i << ' ';
    }
    std::cout << "\n\n";

    extraction.print_twenty();
    extraction.print_doppio_oro();
    extraction.print_extra();
    extraction.print_gong_n();

    if (extraction.check_win(scheda)) {
      std::cout << "(\033[32m"
                << "schedina vincente"
                << "\033[0m)"
                << "\n";
      win_n++;
    } else {
      std::cout << "(\033[31m"
                << "schedina non vincente"
                << "\033[0m)"
                << "\n";
    }

    std::cout << '\n';
  }
  std::cout << "esito di " << iterations << " estrazioni. Vincite: " << win_n
            << "/" << iterations << " = "
            << static_cast<float>(win_n) * 100 / static_cast<float>(iterations)
            << '%' << "\n\n\n";

  return 0;
}