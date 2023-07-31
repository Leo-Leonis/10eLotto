#ifndef EXTRACTION_EVENT_HPP
#define EXTRACTION_EVENT_HPP

#include "Schedina.hpp"
#include <vector>

class Extraction_event {
private:
  std::vector<int> twenty_ = std::vector<int>(20);
  std::vector<int> fifteen_ = std::vector<int>(15);
  std::vector<int> oro_ = std::vector<int>(2);

public:
  Extraction_event(std::vector<int> numbers);

  /// @brief controlla se una schedina è vincente o no
  /// @param scheda la schedina da controllare
  /// @return 1 se è vincente, 0 se non lo è
  bool check_win(Schedina scheda);
};

#endif