// compilazione: g++ -Wall -Wextra -fsanitize=address main.cpp
// Extraction_event.cpp

#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include "Extraction_event.hpp"
#include "Schedina.hpp"

// void program(int type = 0) { return; }

///*TEST TEST TEST*/ std::cout << "QUESTO è UNA PROVA////////////\n";

// int argc = numero di argomenti (compreso "./a.out")
// char* argv[] = array di string degli argomenti
int main(int const argc, char const *const *argv) {
  std::random_device rd;
  std::mt19937 g(rd());
  std::uniform_int_distribution<int> distr(1, 91);
  // distr(rd) per un numero random

  std::vector<int> ninty = std::vector<int>(90);
  // creo i numeri
  std::iota(ninty.begin(), ninty.end(), 1);

  float bet;
  bool oro_s;
  bool doppio_oro_s;
  bool extra_s;
  float extra_bet;
  bool gong_s;
  int gong_n;

  // quantità dei numeri della schedina (ten)
  int numbers;
  // vettore di dieci numeri
  std::vector<int> ten;

  if (argc > 2) {
    if (argv[2] == std::string("-last")) {
      std::ifstream ifile("last_settings.txt");
      std::string s;
      if (ifile.good()) {
        ifile >> numbers;
        ten = std::vector<int>(numbers);
        for (int i = 0; i != numbers; i++) {
          ifile >> ten[i];
        }
        ifile >> bet;
        ifile >> oro_s;
        ifile >> doppio_oro_s;
        ifile >> extra_s;
        ifile >> extra_bet;
        ifile >> gong_s;
        ifile >> gong_n;
        ifile >> s;
        if (s != "STOP") {
          throw std::runtime_error{"Errore nella lettura dei parametri. Per "
                                   "favore rigenerare il file "
                                   "\"last_settings.txt\"."};
        }
      } else { // altrimenti se non è stato trovato il file last_settings.txt...
        throw std::runtime_error{"File \"last_settings.txt\" inesistente. Per "
                                 "favore rigenerare file."};
      }
    }
  } else { // altrimenti inserimento manuale dei parametri
    std::cout << "quantità di numeri della schedina (da 1 a 10): ";
    std::cin >> numbers;
    if (numbers < 1) {
      std::cout
          << "il minimo è 1, per colpa tua la quantità è stata riportata a 1."
          << '\n';
      numbers = 1;
    } else if (numbers > 10) {
      std::cout << "il massimo è 10, per colpa tua la quantità è stata "
                   "riportata a 10."
                << '\n';
      numbers = 10;
    }
    std::cout << '\n';

    ten = std::vector<int>(numbers);
    std::string opt;
    std::cout << "randomizzo? (\"1\" for yes, other key for no)" << '\n';
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
        // numero provvisorio da inserire
        int n_check;
        for (int i = 0; i < numbers; i++) {
          std::cout << "n. " << i + 1 << ": ";
          std::cin >> n_check;
          if (std::count(ten.begin(), ten.end(), n_check) != 0) {
            std::cout
                << "ATTENZIONE: numero già inserito. Riprova a inserire il ";
            i--;
          } else if (n_check < 1 || n_check > 90) {
            std::cout
                << "ATTENZIONE: valore fuori range (da 1 a 90). Riprova a "
                   "inserire il ";
            i--;
          } else {
            ten[i] = n_check;
          }
        }
      }
    }
    std::sort(ten.begin(), ten.end());

    // inserimento opzioni gioco
    std::cout << "Quanto vuoi giocare? (multiplo di 0.50€)\n";
    std::cin >> bet;
    if (bet < 1.f) {
      throw std::runtime_error("Il bet deve essere al minimo 1.");
    } else if (fmodf(bet, 0.5f) != 0.f) {
      throw std::runtime_error("Il bet deve essere un multiplo di 0.50€.");
    }
    std::cout << "Giocare il Doppio Oro? (\"1\" for yes)\n";
    std::cin >> doppio_oro_s;
    if (doppio_oro_s == 0) {
      std::cout << "Giocare l'Oro? (\"1\" for yes)\n";
      std::cin >> oro_s;
    }
    std::cout << "Giocare l'Extra? (\"1\" for yes)\n";
    std::cin >> extra_s;
    if (extra_s == 1) {
      std::cout << "Quanto vuoi giocare nell'Extra? (multiplo di 0.50€)\n";
      std::cin >> extra_bet;
      if (extra_bet > bet) {
        throw std::runtime_error(
            "L'Extra non può essere più alto del 10eLotto.");
      }
      if (fmodf(extra_bet, 0.5f) != 0.f) {
        throw std::runtime_error("L'Extra deve essere un multiplo di 0.50€.");
      }
    } else {
      extra_bet = 0.f;
    }
    std::cout << "Giocare il Gong? (\"1\" for yes)\n";
    std::cin >> gong_s;
    if (gong_s == 1) {
      std::string c;
      std::cout << "randomizzo? (\"1\" for yes)\n";
      std::cin >> c;
      if (c == "1") {
        gong_n = distr(rd);
      } else {
        std::cout << "Inserire in numero gong: ";
        std::cin >> gong_n;
      }
    }
  }

  Schedina scheda(ten, bet, oro_s, doppio_oro_s, extra_s, extra_bet, gong_s,
                  gong_n);
  // riepilogo schedina
  scheda.print_schedina();

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

  float win_reg[iterations];
  float total_spent_money =
      static_cast<float>(iterations) * scheda.get_total_bet();
  win_reg[0] = total_spent_money;

  // numero di vincite totale di tutte le iterazioni fatte
  int win_n = 0;
  // soldi di vincita totale
  float total_won_money = 0.f;
  // quantità di soldi vinti correnti
  float money_won = 0.f;
  // array di quanti numberi beccati
  std::vector<int> categ(numbers + 1);

  // ciclo iterazioni
  for (int n_it = 0; n_it < iterations; n_it++) {

    // randomizzo l'ordine
    std::shuffle(ninty.begin(), ninty.end(), g);

    Extraction_event extraction(ninty, distr(rd));
    int count = extraction.numbers_in_common(scheda);
    /* int count_extra = extraction.numbers_in_common_extra(scheda);
    int count_doppio_oro = extraction.numbers_in_common_doppio_oro(scheda); */
    categ[count]++;

    money_won = extraction.get_win(scheda);
    total_won_money += money_won;

    win_reg[n_it + 1] = win_reg[n_it] - scheda.get_total_bet() + money_won;

    // se si mette l'opzione "-pr" (Print Result) si stampano i risultati per
    // tutte le estrazioni
    if (argc > 1 && std::string(argv[1]) == "-pr") {

      // stampa informazioni estrazione
      std::cout << "estrazione n. " << n_it + 1 << '\n' << '\n';

      /* // stampa il vettore
      std::cout << "il vettore ninty è: ";
      for (int i : ninty) {
        std::cout << i << ' ';
      }
      std::cout << "\n\n"; */

      extraction.print_twenty();
      if (doppio_oro_s || oro_s) {
        extraction.print_doppio_oro();
      }
      if (extra_s) {
        extraction.print_extra();
      }
      if (gong_s) {
        extraction.print_gong_n();
      }

      extraction.print_results(scheda, win_n);

      std::cout << "\n--------------------------------------------\n" << '\n';

    } else if (argc == 1 || (argc > 1 && std::string(argv[1]) != "-pr")) {

      if (money_won != 0) {
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
            << "Esito di " << iterations << " estrazioni. Vincite: " << win_n
            << "/" << iterations << " = "
            << static_cast<float>(win_n) * 100 / static_cast<float>(iterations)
            << '%' << "\n\n";

  std::cout << "Risultati per quantità numeri presi: \n\n";
  for (int i = 0; i < numbers + 1; i++) {
    std::cout << "     " << categ[i] << " x " << i << " numeri ("
              << static_cast<float>(categ[i]) / static_cast<float>(iterations) *
                     100
              << "%)" << '\n';
  }
  std::cout << '\n' << '\n';

  std::cout << "Soldi spesi: " << scheda.get_total_bet() << "€ * " << iterations
            << " estrazioni = " << total_spent_money << "€" << '\n';

  std::cout << "Soldi vinti: " << total_won_money << "€ ("
            << total_won_money / total_spent_money * 100
            << "% rispetto al totale speso)" << '\n';

  std::cout << "     Ricavo: " << total_won_money - total_spent_money << "€ ("
            << (total_won_money - total_spent_money) * 100 / total_spent_money
            << "% rispetto al totale speso)" << '\n';

  std::ofstream ofile("last_settings.txt");
  ofile << numbers << " ";
  for (int i : ten) {
    ofile << i << " ";
  }
  ofile << bet << " " << oro_s << " " << doppio_oro_s << " " << extra_s << " "
        << extra_bet << " " << gong_s << " " << gong_n << " "
        << "STOP" << '\n';

  std::ofstream ofile2("progress.txt");
  for (int i = 0; i != iterations + 1; i++) {
    ofile2 << i << '\t' << win_reg[i] << '\n';
  }
  std::cout << '\n' << '\n';
  return 0;
}