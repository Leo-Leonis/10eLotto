#ifndef SCHEDINA_HPP
#define SCHEDINA_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

class Schedina {
private:
  std::vector<int> ten_;
  float bet_;
  bool oro_;
  bool doppio_oro_;
  bool extra_;
  float extra_bet_;
  bool gong_;
  int gong_n_;
  float total_bet_;

public:
  Schedina() {}
  Schedina(const std::vector<int> &numbers, float bet, bool oro,
           bool doppio_oro, bool extra, float extra_bet, bool gong, int gong_n)
      : bet_{bet}, oro_{oro}, doppio_oro_{doppio_oro}, extra_{extra},
        extra_bet_{extra_bet}, gong_{gong}, gong_n_{gong_n} {
    for (int i = 0; i < static_cast<int>(numbers.size()); i++) {
      ten_.push_back(numbers[i]);
    }
    if (doppio_oro_ == 1)
      oro_ = 1;
    if (extra_bet_ > bet_) {
      throw std::runtime_error("ERRROR: extra_bet cannot be higher than bet");
    }
    total_bet_ = bet_ * (1 + oro_ + doppio_oro_ + gong_) + extra_bet_;
  }

  /// @brief ritorna la vettore dei numeri scelti della schedina
  /// @return std::vector<int>
  std::vector<int> get_ten() const { return ten_; }

  float get_bet() const { return bet_; }

  bool has_oro() const { return oro_; }

  bool has_doppio_oro() const { return doppio_oro_; }

  bool has_extra() const { return extra_; }

  float get_extra_bet() const { return extra_bet_; }

  bool has_gong() const { return gong_; }

  int get_gong_n() const { return gong_n_; }

  float get_total_bet() const { return total_bet_; }

  void print_schedina() const {
    std::cout << "\n///////////////////////////////////////////\n\n";
    this->print_ten();
    if (doppio_oro_ == 1) {
      std::cout << " Doppio oro: SÌ (" << bet_ << "€)" << '\n';
      std::cout << "        Oro: SÌ (" << bet_ << "€)" << '\n';
    } else if (oro_ == 1) {
      std::cout << " Doppio oro: NO" << '\n';
      std::cout << "        Oro: SÌ (" << bet_ << "€)" << '\n';
    } else {
      std::cout << " Doppio oro: NO" << '\n';
      std::cout << "        Oro: NO" << '\n';
    }

    if (extra_ == 1) {
      std::cout << "      Extra: SÌ (" << extra_bet_ << "€)" << '\n';
    } else {
      std::cout << "      Extra: NO" << '\n';
    }

    if (gong_ == 1) {
      std::cout << "       Gong: SÌ (" << gong_n_ << ", " << bet_ << "€)" << '\n';
    } else {
      std::cout << "       Gong: NO" << '\n';
    }
    std::cout << '\n' << "TOTAL BET: " << total_bet_ << "€" << '\n';
    std::cout << "\n///////////////////////////////////////////\n\n";
  }

  void print_ten() const {
    std::cout << "La schedina è quindi: ";
    for (int i : ten_) {
      std::cout << i << ' ';
    }
    std::cout << '\n';
  }
};

#endif