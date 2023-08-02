#include "Extraction_event.hpp"
#include "Schedina.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
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

bool Extraction_event::check_win(Schedina scheda) {
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
           std::count(ten.begin(), ten.end(), oro_[0] == 1)) {
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

// TODO: IMPLEMENTARE QUESTO
int Extraction_event::numbers_in_common(Schedina scheda) {

}

int Extraction_event::numbers_in_common_extra(Schedina scheda) {

}

void Extraction_event::print_twenty() {
  std::cout << "I numeri sono: ";
  for (int i : twenty_) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

void Extraction_event::print_doppio_oro() {
  std::cout << "L'oro e il doppio oro sono: ";
  std::cout << "ORO: " << oro_[0] << "; DOPPIO ORO: " << oro_[1] << '\n';
}
void Extraction_event::print_extra() {
  std::cout << "Gli extra sono: ";
  for (int i : fifteen_) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

void Extraction_event::print_gong_n() {
  std::cout << "il numero gong è:" << gong_n_ << '\n';
}
