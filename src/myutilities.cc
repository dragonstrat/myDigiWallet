/*******************************
 * Implementation for utility functions
 * by Ganghee Jang
 *******************************
 */

#include "myutilities.hh"

// return -1 when out of range exception occurs.
// return 0 when fails for wrong format of input transaction
// return 1 when successful
int findFieldData(std::string& linebuffer, int& id1, int& id2) {
  std::size_t beginid1 = 0;
  std::size_t endid1 = 0;
  std::size_t endid2 = 0;

  int comma_count = 0;
  for (size_t iter = 0; iter < linebuffer.length(); iter++) {
    if (linebuffer.at(iter) == ',') {
        if (comma_count == 0) {
          beginid1 = iter + 1;
          comma_count++;
        } else if (comma_count == 1) {
          endid1 = iter - 1;
          comma_count++;
        } else if (comma_count == 2) {
          endid2 = iter - 1;
          break;
        }
    }
  }

  if ((comma_count != 2)||((endid1-beginid1)<1)||((endid2-endid1)<3)) return 0;

  std::string result1(linebuffer, beginid1, endid1 - beginid1 + 1);
  std::string result2(linebuffer, endid1 + 2, endid2 - endid1 - 1);

  try {
    id1 = std::stoi(result1);
    id2 = std::stoi(result2);
  }
  catch (const std::out_of_range& oor) {
    return -1;
  }

  return 1;
}
