#include "schedina.hpp"
#include <vector>

class Extraction_event {
private:
  std::vector<int> twenty_ = std::vector<int>(20);
  std::vector<int> fifteen_ = std::vector<int>(15);
  std::vector<int> oro_ = std::vector<int>(2);

public:
  Extraction_event(std::vector<int> numbers);

  bool check_win(Schedina scheda);
};