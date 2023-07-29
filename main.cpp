#include <array>
#include <iostream>
#include <string>
#include <vector>

class schedina {
private:
  std::vector<int> twenty_ = std::vector<int>(20);
  bool oro_;
  bool doppio_oro_;
  bool extra_;
  bool gong_;
  int gong_n_;

public:
  schedina(std::vector<int> numbers, bool oro, bool doppio_oro, bool gong,
           int gong_n)
      : oro_{oro}, doppio_oro_{doppio_oro}, gong_{gong}, gong_n_{gong_n} {
    for (int i = 0; i < 20; i++) {
      numbers[i] = twenty_[i];
    }
  }
};

class Extraction_event {
private:
  std::vector<int> twenty_ = std::vector<int>(20);
  std::vector<int> fifteen_ = std::vector<int>(15);
  std::vector<int> oro_ = std::vector<int>(2);

public:
  Extraction_event(std::vector<int> numbers) {
    for (int i = 0; i < 2; i++) {
      numbers[i] = twenty_[i];
      numbers[i] = oro_[i];
    }
    for (int i = 2; i < 20; i++) {
      numbers[i] = twenty_[i];
    }
    for (int i = 20; i < 35; i++) {
      numbers[i] = fifteen_[i];
    }
  }

  bool check_win(schedina scheda) {}
};

void program(int type = 0) { return; }