#include <vector>
#include "Extraction_event.hpp"
#include "Schedina.hpp"

Extraction_event::Extraction_event(std::vector<int> numbers) {
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

bool Extraction_event::check_win(Schedina scheda) {

}