#include "Extraction_event.hpp"
#include "Schedina.hpp"
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

// conta i numeri degli integers in comune con il vettore entrante
int countIntegersInCommon(const std::vector<int> &vec1,
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
}

int getValueFromTable(const std::string& filename, int row, int column) {
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

Extraction_event::Extraction_event(std::vector<int> numbers) {
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
  std::vector<int> ten = scheda.get_ten();
  int const size = ten.size();
  int count = countIntegersInCommon(ten, twenty_);
  int win_f = getValueFromTable("twenty.txt", size, count);
}