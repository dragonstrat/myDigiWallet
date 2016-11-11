/*******************************
 * main.cc
 * by Ganghee Jang
 *******************************
 */

#include <iostream>
#include <fstream>
#include <iomanip>

#include "myutilities.hh"
#include "myhash.hh"

// below library is to get statistics
#include <ctime>

using namespace std;

int main (int argc, char* argv[]) {

  // terminate if proper number of arguments are not given.
  if ( argc != 6 ) {
    cout<<"usage: "<< argv[0] <<"<batch file name> <stream file name> <output 1> <output 2> <output 3>\n";
    return -1;
  }

  ifstream batchPayment (argv[1]);
  ifstream streamPayment (argv[2]);

  ofstream output1(argv[3]);
  ofstream output2(argv[4]);
  ofstream output3(argv[5]);

  myHash traderTable;

  string line;
  string id1, id2;

  if (!output1.is_open()) {
    std::cout << "Error opening output1.txt file!\n";
    return -1;
  }
  if (!output2.is_open()) {
    std::cout << "Error opening output2.txt file!\n";
    return -1;
  }
  if (!output3.is_open()) {
    std::cout << "Error opening output3.txt file!\n";
    return -1;
  }


  if (batchPayment.is_open()) {
    // to bypass first line.
    getline(batchPayment,line);
    int status = -1;
    int id1, id2;
    while ( getline(batchPayment,line) ) {
      status =  findFieldData(line, id1, id2);

      // error when 0, -1..
      if ((status == 0)||(status == -1)) {
        std::cout << "exit while batch processing with status " << status << std::endl;
        std::cout << "-1 means trader id is out of scope of type interger.";
        std::cout << "0 means invalid input.";
        exit(1);
      }

      traderTable.addTradingPeer(id1,id2);
      
    }

    batchPayment.close();
  }
  else cout << "Unable to open batch payment file.";

  if (streamPayment.is_open()) {
    // to bypass first line.
    getline(streamPayment,line);
    int status = -1;
    int id1, id2;
    while ( getline(streamPayment,line) ) {

      status =  findFieldData(line, id1, id2);

      // error when 0, -1..
      if ((status == 0)||(status == -1)) {
        std::cout << "exit while stream processing with status " << status << std::endl;
        std::cout << "-1 means trader id is out of scope of type interger.";
        std::cout << "0 means invalid input.";
        exit(1);
      }

      if ((traderTable.isTrader(id1)==false)||(traderTable.isTrader(id2)==false)) {
        output1 << "unverified" << std::endl;
        output2 << "unverified" << std::endl;
        output3 << "unverified" << std::endl;
      } else {
        if (traderTable.feature1(id1,id2)) {
          output1 << "trusted" << std::endl;
          output2 << "trusted" << std::endl;
          output3 << "trusted" << std::endl;
        } else {
          if (traderTable.feature2(id1, id2)) {
            output1 << "unverified" << std::endl;
            output2 << "trusted" << std::endl;
            output3 << "trusted" << std::endl;
          } else {
            if (traderTable.feature3_bfs(id1,id2)) {
              output1 << "unverified" << std::endl;
              output2 << "unverified" << std::endl;
              output3 << "trusted" << std::endl;
            } else {
              output1 << "unverified" << std::endl;
              output2 << "unverified" << std::endl;
              output3 << "unverified" << std::endl;
            }
          }
        }
      }

      traderTable.addTradingPeer(id1,id2);
      
    }

    streamPayment.close();
  }
  else cout << "Unable to open steam payment file.";

  output1.close();
  output2.close();
  output3.close();

  return 0;
}
