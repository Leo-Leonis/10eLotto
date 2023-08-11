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

  /// @brief Controlla se una schedina è vincente o no.
  /// @param scheda la schedina da controllare
  /// @return 1 se è vincente, 0 se non lo è
  bool check_win(const Schedina &scheda) const;

  /// @brief Restituisce la vincita di una schedina.
  /// @param scheda la schedina da controllare
  /// @return Il fattore di vincita data dalla tabella
  float get_win(const Schedina &scheda) const;

  int numbers_in_common(const Schedina &scheda) const;
  int numbers_in_common_extra(const Schedina &scheda) const;
  int numbers_in_common_doppio_oro(const Schedina &scheda) const;
  bool check_oro(const Schedina &scheda) const;
  bool check_gong(const Schedina &scheda) const;

  void print_twenty() const;
  void print_doppio_oro() const;
  void print_extra() const;
  void print_gong_n() const;

  /// @brief Stampa i risultati delle schedina, con: quantità di numeri presi,
  /// doppio oro, extra e gong.
  /// @param scheda la schedina da controllare
  /// @param win_n il numero totale di vincite
  void print_results(const Schedina &scheda, int &win_n) const;
};

#endif