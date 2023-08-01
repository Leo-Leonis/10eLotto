#include "Extraction_event.hpp"
#include "Schedina.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

/* int countIntegersInCommon(const std::vector<int> &vec1,
                          const std::vector<int> &vec2) {
  int count = 0;

  // Ordiniamo i vettori per semplificare il controllo delle corrispondenze
  std::vector<int> sortedVec1 = vec1;
  std::sort(sortedVec1.begin(), sortedVec1.end());

  std::vector<int> sortedVec2 = vec2;
  std::sort(sortedVec2.begin(), sortedVec2.end());

  // Troviamo i numeri presenti in entrambi i vettori
  for (size_t i = 0, j = 0; i < sortedVec1.size() && j < sortedVec2.size();) {
    if (sortedVec1[i] < sortedVec2[j]) {
      i++;
    } else if (sortedVec1[i] > sortedVec2[j]) {
      j++;
    } else {
      // Trovato un numero presente in entrambi i vettori
      count++;
      i++;
      j++;
    }
  }

  return count;
} */

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

Extraction_event::Extraction_event(std::vector<int> &numbers, int gong_n)
    : gong_n_{gong_n} {
  for (int i = 0; i < 2; i++) {
    numbers[i] = twenty_[i];
    numbers[i] = oro_[i];
  }
  for (int i = 2; i < 20; i++) {
    numbers[i] = twenty_[i];
  }
  for (int i = 20; i < 35; i++) {
    numbers[i] = fifteen_[i - 20];
  }
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

  // se nel gioco classico ha preso il numero sufficiente di numeri allora...
  if (getValueFromTable("wins/twenty.txt", size - 1, count) == 0) {
    return 0;
  } else {
    return 1;
  }

  // se la schedina ha l'extra e ne ha preso il numero sufficiente allora...
  if (scheda.has_extra() &&
      getValueFromTable("wins/extra.txt", size - 1, count_extra) == 0) {
    return 0;
  } else {
    return 1;
  }
}