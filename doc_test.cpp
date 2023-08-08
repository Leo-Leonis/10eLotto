// g++ -Wall -Wextra -fsanitize=address Extraction_event.cpp doc_test.cpp -o doctest

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "Extraction_event.hpp"
#include "Schedina.hpp"
#include "doctest.h"

TEST_CASE("Extraction check") {
  std::vector<int> ninty = {
      11, 82, 31, 24, 21, 36, 65, 45, 43, 89, 34, 40, 52, 60, 25, 83, 42, 16,
      49, 64, 29, 80, 70, 33, 39, 23, 12, 75, 9,  54, 37, 73, 69, 90, 19, 71,
      87, 3,  85, 4,  72, 88, 27, 84, 32, 17, 57, 28, 2,  20, 86, 44, 15, 56,
      68, 48, 81, 38, 14, 8,  67, 61, 74, 22, 26, 76, 18, 10, 62, 51, 6,  1,
      46, 47, 35, 79, 5,  7,  59, 58, 41, 50, 55, 13, 53, 78, 30, 77, 66, 63};
  Extraction_event extraction(ninty, 58);
  SUBCASE("Extraction check 1") {
    Schedina scheda({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 1, 1, 1, 1, 1, 1, 1);
    CHECK(extraction.check_win(scheda) == true);
    CHECK(extraction.numbers_in_common(scheda) == 0);
    CHECK(extraction.numbers_in_common_doppio_oro(scheda) == 0);
    CHECK(extraction.numbers_in_common_extra(scheda) == 1);
    CHECK(extraction.check_gong(scheda) == false);
  }
}