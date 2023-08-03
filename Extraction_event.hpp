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
  Extraction_event(const std::vector<int> &numbers, int gong_n);

  /// @brief Controlla se una schedina è vincente o no
  /// @param scheda la schedina da controllare
  /// @return 1 se è vincente, 0 se non lo è
  bool check_win(Schedina scheda);

  /// @brief Restituisce il fattore di vincita data una schedina
  /// @param scheda la schedina da controllare
  /// @return Il fattore di vincita data dalla tabella
  int get_win_f(Schedina scheda);

  int numbers_in_common(Schedina scheda);
  int numbers_in_common_extra(Schedina scheda);

  void print_twenty();
  void print_doppio_oro();
  void print_extra();
  void print_gong_n();
};

#endif