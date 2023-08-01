#ifndef EXTRACTION_EVENT_HPP
#define EXTRACTION_EVENT_HPP

#include "Schedina.hpp"
#include <vector>

class Extraction_event {
private:
  // vettore dei venti numeri estratti
  std::vector<int> twenty_ = std::vector<int>(20);

  // vettore degli extra
  std::vector<int> fifteen_ = std::vector<int>(15);
  
  // vettore dell'oro e del doppio oro
  std::vector<int> oro_ = std::vector<int>(2);

  // numero gong
  int const gong_n_;

public:
  Extraction_event(std::vector<int> &numbers, int gong_n);

  /// @brief Controlla se una schedina è vincente o no
  /// @param scheda la schedina da controllare
  /// @return 1 se è vincente, 0 se non lo è
  bool check_win(Schedina scheda);
};

#endif