#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include "Extraction_event.hpp"
#include "Schedina.hpp"

// void program(int type = 0) { return; }

// int argc = numero di argomenti (compreso "./a.out")
// char* argv[] = array di string degli argomenti
int main(int const argc, char const *const *argv) {
  std::random_device rd;
  std::mt19937 g(rd());

  std::vector<int> ninty = std::vector<int>(90);
  // creo i numeri
  std::iota(ninty.begin(), ninty.end(), 1);

  bool doppio_oro_s;
  bool oro_s;
  bool extra_s;
  bool gong_s;

  // quantità dei numeri della schedina (ten)
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

  std::string opt;
  std::cout << "random numbers? (\"1\" for yes, other key for no)" << '\n';
  std::cin >> opt;
  if (opt == "1") {
    std::shuffle(ninty.begin(), ninty.end(), g);
    for (int i = 0; i < numbers; i++) {
      ten[i] = ninty[i];
    }
  } else {
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
          std::cout
              << "ATTENZIONE: numero già inserito. Riprova a inserire il ";
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
  }
  std::sort(ten.begin(), ten.end());

  /* std::cout << "Giocare il Doppio Oro? (\"1\" for yes) ";
  std::cin >> doppio_oro_s;
  if (doppio_oro_s == 1) {
    std::cout << "random? (\"1\" for yes)";
    //TODO FINIRE QUESTA PARTE (SELEZIONE)
  }
  std::cout << "Giocare l'Oro? (\"1\" for yes)";
  std::cin >> oro_s;
  std::cout << "Giocare l'Extra? (\"1\" for yes)";
  std::cin >> extra_s;
  std::cout << "Giocare il gong? (\"1\" for yes)";
  std::cin >> gong_s;
 */
  std::cout << '\n' << "la schedina è quindi: ";
  for (int i : ten) {
    std::cout << i << ' ';
  }
  std::cout << "\n\n";

  Schedina scheda(ten, 1, 0, 0, 0, 0, 0, 0);
  ///*TEST TEST TEST*/ std::cout << "QUESTO è UNA PROVA////////////\n";

  // numero di iterazioni (estrazioni)
  int iterations;
  std::cout << "iterazioni (minimo 1): ";
  std::cin >> iterations;
  if (iterations < 1) {
    std::cout
        << "il minimo è 1, per colpa tua la quantità è stata riportata a 1."
        << '\n';
  }
  std::cout << '\n';

  // numero di vincite totale di tutte le iterazioni fatte
  int win_n = 0;
  // array di quanti numberi beccati
  std::vector<int> categ(numbers + 1);

  // ciclo iterazioni
  for (int n_it = 0; n_it < iterations; n_it++) {
    // randomizzo l'ordine
    std::shuffle(ninty.begin(), ninty.end(), g);

    Extraction_event extraction(ninty, 0);
    int count = extraction.numbers_in_common(scheda);
    categ[count]++;

    // se si mette l'opzione "-pr" (Print Result) si stampano i risultati per
    // tutte le estrazioni
    if (argc > 1 && std::string(argv[1]) == "-pr") {

      std::cout << "estrazione n. " << n_it + 1 << '\n' << '\n';

      /* // stampa il vettore
      std::cout << "il vettore ninty è: ";
      for (int i : ninty) {
        std::cout << i << ' ';
      }
      std::cout << "\n\n"; */

      extraction.print_twenty();
      if (scheda.has_doppio_oro() || scheda.has_oro()) {
        extraction.print_doppio_oro();
      }
      if (scheda.has_extra()) {
        extraction.print_extra();
      }
      if (scheda.has_gong()) {
        extraction.print_gong_n();
      }

      if (extraction.check_win(scheda)) {
        std::cout << "(" << count << " su " << numbers << ", \033[32m"
                  << "schedina vincente"
                  << "\033[0m)"
                  << "\n";
        win_n++;
      } else {
        std::cout << "(" << count << " su " << numbers << ", \033[31m"
                  << "schedina non vincente"
                  << "\033[0m)"
                  << "\n";
      }
      std::cout << "\n--------------------------------------------\n" << '\n';
    }

    if (argc == 1 || (argc > 1 && std::string(argv[1]) != "-pr")) {

      if (extraction.check_win(scheda)) {
        win_n++;
      }
      // print number of progress in order to give feedback
      std::cout
          << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
             "\b\b\b\b\b\b\b\b\b\b\b\b"
          << "events generated: " << n_it << '(' << 100 * n_it / iterations
          << "%)";
    }
  } // end iterations

  std::cout << '\n'
            << '\n'
            << "esito di " << iterations << " estrazioni. Vincite: " << win_n
            << "/" << iterations << " = "
            << static_cast<float>(win_n) * 100 / static_cast<float>(iterations)
            << '%' << "\n\n";

  std::cout << "risultati per quantità numeri presi: \n\n";
  for (int i = 0; i < numbers + 1; i++) {
    std::cout << "     " << categ[i] << " x " << i << " numeri ("
              << static_cast<float>(categ[i]) / static_cast<float>(iterations) *
                     100
              << "%)" << '\n';
  }

  return 0;
}