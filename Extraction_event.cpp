#include "Extraction_event.hpp"
#include "Schedina.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

// conta la quantità di numeri (int) in comune con il vettore entrante
int countIntegersInCommon(const std::vector<int> &ten,
                          const std::vector<int> &twenty) {
  int count = 0;
  for (const int target : ten) {
    if (std::count(twenty.cbegin(), twenty.cend(), target) != 0)
      count++;
  }
  return count;
}

/// @brief Ritorna il valore del numero tabulato nel file nella cartella wins/
/// @param filename la stringa del file
/// @param row la riga (quantità di numeri scelti) DA SOTTRARRE DI UNO
/// @param column la colonna (quantità di numeri beccati)
int getValueFromTable(const std::string &filename, int row, int column) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Impossibile aprire il file " << filename << std::endl;
    return -1;
  }

  int value = -1;
  std::string line;

  // Scorrere fino alla riga desiderata
  for (int i = 0; i <= row; ++i) {
    if (!std::getline(file, line)) {
      std::cerr << "Riga non trovata." << std::endl;
      return -1;
    }
  }

  // Leggere il valore nella colonna desiderata
  std::istringstream iss(line);
  for (int i = 0; i <= column; ++i) {
    if (!(iss >> value)) {
      std::cerr << "Colonna non trovata." << std::endl;
      return -1;
    }
  }

  return value;
}

Extraction_event::Extraction_event(const std::vector<int> &numbers, int gong_n)
    : gong_n_{gong_n} {
  for (int i = 0; i < 2; i++) {
    twenty_[i] = numbers[i];
    oro_[i] = numbers[i];
  }
  for (int i = 2; i < 20; i++) {
    twenty_[i] = numbers[i];
  }
  for (int i = 20; i < 35; i++) {
    fifteen_[i - 20] = numbers[i];
  }
  std::sort(twenty_.begin(), twenty_.end());
  std::sort(fifteen_.begin(), fifteen_.end());
}

bool Extraction_event::check_win(const Schedina &scheda) const {
  // gong
  if (scheda.has_gong() && scheda.get_gong_n() == gong_n_) {
    return 1;
  }

  // vettore dei numeri scelti
  std::vector<int> ten = scheda.get_ten();
  // quantità dei numeri scelti
  int const size = ten.size();
  // quantità dei numeri beccati
  int count = countIntegersInCommon(ten, twenty_);
  int count_extra = countIntegersInCommon(ten, fifteen_);

  // se la schedina ha il doppio oro e ne ha beccato almeno uno, allora...
  if (scheda.has_doppio_oro() && countIntegersInCommon(ten, oro_) != 0) {
    return 1;
  } // altrimenti se la schedina ha solo l'oro e l'ha preso, allora...
  else if (scheda.has_oro() &&
           std::count(ten.cbegin(), ten.cend(), oro_[0]) == 1) {
    return 1;
  }

  // se la schedina ha l'extra e ne ha preso il numero sufficiente allora...
  if (scheda.has_extra() &&
      getValueFromTable("wins/extra.txt", size - 1, count_extra) != 0) {
    return 1;
  }

  // se nel gioco classico ha preso il numero sufficiente di numeri allora...
  if (getValueFromTable("wins/twenty.txt", size - 1, count) == 0) {
    return 0;
  } else {
    return 1;
  }
}

int Extraction_event::get_win_f(const Schedina &scheda) const {

  // fattore di vincita totale
  int total_win_f = 0;

  // gong
  if (scheda.has_gong() && scheda.get_gong_n() == gong_n_) {
    total_win_f += getValueFromTable("wins/gong.txt", 0, 0);
  }

  // vettore dei numeri scelti
  std::vector<int> ten = scheda.get_ten();
  // quantità dei numeri scelti
  int const size = ten.size();
  // quantità dei numeri beccati
  int count = countIntegersInCommon(ten, twenty_);
  int count_extra = countIntegersInCommon(ten, fifteen_);
  int count_doppio_oro = countIntegersInCommon(ten, oro_);
  if (count_doppio_oro < 0 || count_doppio_oro > 2) {
    throw std::runtime_error("ERRORE: contati più di due ori.");
  }

  // se la schedina ha il doppio oro e ne ha beccati 2, allora...
  if (scheda.has_doppio_oro() && count_doppio_oro == 2) {
    total_win_f += getValueFromTable("wins/doppio_oro.txt", size - 1, count);
  } // altrimenti se la schedina ha preso un solo oro, allora...
  else if ((scheda.has_doppio_oro() && count_doppio_oro == 1) ||
           (scheda.has_oro() &&
            std::count(ten.cbegin(), ten.cend(), oro_[0]) == 1)) {
    total_win_f += getValueFromTable("wins/oro.txt", size - 1, count);
  } else {
    total_win_f += getValueFromTable("wins/twenty.txt", size - 1, count);
  }

  // se la schedina ha l'extra e ne ha preso il numero sufficiente allora...
  if (scheda.has_extra()) {
    total_win_f += getValueFromTable("wins/extra.txt", size - 1, count_extra);
  }

  return total_win_f;
}

int Extraction_event::numbers_in_common(const Schedina &scheda) const {
  return countIntegersInCommon(scheda.get_ten(), twenty_);
}

int Extraction_event::numbers_in_common_extra(const Schedina &scheda) const {
  return countIntegersInCommon(scheda.get_ten(), fifteen_);
}

int Extraction_event::numbers_in_common_doppio_oro(
    const Schedina &scheda) const {
  return countIntegersInCommon(scheda.get_ten(), oro_);
}

bool Extraction_event::check_oro(const Schedina &scheda) const {
  std::vector<int> ten = scheda.get_ten();
  if (std::count(ten.begin(), ten.end(), oro_[0]) == 1) {
    return true;
  } else {
    return false;
  }
}

bool Extraction_event::check_gong(const Schedina &scheda) const {
  if (scheda.get_gong_n() == gong_n_) {
    return true;
  } else {
    return false;
  }
}

void Extraction_event::print_twenty() const {
  std::cout << "I numeri sono: ";
  for (int i : twenty_) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

void Extraction_event::print_doppio_oro() const {
  std::cout << "\033[93mORO: " << oro_[0]
            << "\033[0m; \033[33mDOPPIO ORO: " << oro_[1] << "\033[0m\n";
}

void Extraction_event::print_extra() const {
  std::cout << "Gli \033[94mextra\033[0m sono: ";
  for (int i : fifteen_) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

void Extraction_event::print_gong_n() const {
  std::cout << "il numero gong è: " << gong_n_ << '\n';
}

void Extraction_event::print_results(const Schedina &scheda, int &win_n) const {
  // stampa esito schedina

  int numbers = scheda.get_ten().size();
  int count = countIntegersInCommon(scheda.get_ten(), twenty_);
  int count_doppio_oro = countIntegersInCommon(scheda.get_ten(), oro_);
  int count_extra = countIntegersInCommon(scheda.get_ten(), fifteen_);

  std::cout << "(" << count << " su " << numbers << ", ";
  if (scheda.has_doppio_oro()) {
    std::cout << "doppio oro " << count_doppio_oro << " su 2, ";
  } else if (scheda.has_oro()) {
    std::cout << "oro ";
    if (this->check_oro(scheda)) {
      std::cout << "PRESO, ";
    } else {
      std::cout << "non preso, ";
    }
  }
  if (scheda.has_extra())
    std::cout << "extra " << count_extra << " su " << numbers << ", ";
  if (scheda.has_gong()) {
    std::cout << "gong: ";
    if (this->check_gong(scheda)) {
      std::cout << "sì, ";
    } else {
      std::cout << "no, ";
    }
  }
  if (this->check_win(scheda)) {
    std::cout << "\033[32m"
              << "schedina vincente"
              << "\033[0m, " << this->get_win_f(scheda) * scheda.get_bet()
              << "€)"
              << "\n";
    win_n++;
  } else {
    std::cout << "\033[31m"
              << "schedina non vincente"
              << "\033[0m)"
              << "\n";
  }
}
