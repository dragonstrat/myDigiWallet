/******************************************************
 * Implementation for some member functions of the myHash class
 * by Ganghee Jang
 ******************************************************
 */

#include "myhash.hh"

void
myHash::addTradingPeer(int id1, int id2){
    if (id1 == id2) return;

    std::unordered_map<int, std::set<int> >::iterator Iter1, Iter2;

    Iter1 = trading_peers.find(id1);
    Iter2 = trading_peers.find(id2);

    if (Iter1 == trading_peers.end()){
        std::set<int> tempList;
        trading_peers[id1] = tempList;
        trading_peers[id1].insert(id2);
    } else {
        trading_peers[id1].insert(id2);
    }

    if (Iter2 == trading_peers.end()){
        std::set<int> tempList;
        trading_peers[id2] = tempList;
        trading_peers[id2].insert(id1);
    } else {
        trading_peers[id2].insert(id1);
    }
}


void
myHash::printTable(){
    std::unordered_map<int, std::set<int> >::const_iterator IterTable;
    std::set<int>::const_iterator IterList;
    std::cout << "<Print Table>\n";
    for (IterTable = trading_peers.begin(); IterTable != trading_peers.end() ; IterTable++){
        std::cout << IterTable->first << ": ";
        for (IterList = IterTable->second.begin(); IterList != IterTable->second.end(); IterList++) {
            std::cout << *IterList << " ";
        }
        std::cout << std::endl;
    }
}


void
myHash::histNumTraders(){
    int* histogram;
    int maxHist = 20;
    int official_seller = 100;
    histogram = new int[maxHist+2]; // hist(0) for the trader with more than official seller trading peers.
                                    // hist(max+1) for between maxHist and official seller

    for (int iter = 0; iter < (maxHist + 2); iter++ ) {
        histogram[iter] = 0; // initialization
    }
    
    std::unordered_map<int, std::set<int> >::const_iterator IterTable;

    for (IterTable = trading_peers.begin(); IterTable != trading_peers.end() ; IterTable++){
        int num_peers = IterTable->second.size();
        if (num_peers > official_seller) histogram[0]++;
        else if (num_peers < 1) continue;
        else if ((num_peers > maxHist)&&( num_peers <= official_seller)) histogram[maxHist+1]++;
        else histogram[num_peers]++;
    }

    std::cout << "Total Traders: " << trading_peers.size() << std::endl << std::endl;
    for (int i = 0; i < maxHist; i++)
        std::cout <<"\t" << i+1 << "\t" << histogram[i+1] << std::endl;
    std::cout <<"more than " << maxHist << "\t" << histogram[maxHist+1] << std::endl;
    std::cout <<"more than " << official_seller<< "\t" << histogram[0] << std::endl;

    delete[] histogram;
}

bool
myHash::feature1(int id1, int id2){
    std::set<int>::iterator searchResult;
    searchResult = trading_peers[id1].find(id2);
    if (searchResult == trading_peers[id1].end()) return false;
    else return true;
}

bool
myHash::feature2(int id1, int id2){

    int id1_num_peers, id2_num_peers;

    id1_num_peers = trading_peers[id1].size();
    id2_num_peers = trading_peers[id2].size();

    int source, target;
    if (id1_num_peers > id2_num_peers){
        source = id2;
        target = id1;
    } else {
        source = id1;
        target = id2;
    }

    std::set<int>::iterator level1_peers;
    level1_peers = trading_peers[source].begin();

    for (; level1_peers != trading_peers[source].end(); level1_peers++) {
      std::set<int>::iterator searchResult = trading_peers[*level1_peers].find(target);

      if (searchResult != trading_peers[*level1_peers].end()) {
        return true;
      }
    }
    return false;

}

// Depth First Search version
bool
myHash::feature3_dfs(int id1, int id2){
// we know that id1 and id2 are not in neighborhood until level 2.

    int id1_num_peers, id2_num_peers;

    id1_num_peers = trading_peers[id1].size();
    id2_num_peers = trading_peers[id2].size();

    int source, target;
    if (id1_num_peers > id2_num_peers){
        source = id2;
        target = id1;
    } else {
        source = id1;
        target = id2;
    }

    std::set<int>::iterator level1_peers, level2_peers, level3_peers;
    level1_peers = trading_peers[source].begin();
    for(; level1_peers!= trading_peers[source].end(); level1_peers++){
        level2_peers = trading_peers[*level1_peers].begin();
        for(; level2_peers!= trading_peers[*level1_peers].end(); level2_peers++){
            level3_peers = trading_peers[*level2_peers].begin();
            if (*level3_peers == target) return true;
            for(; level3_peers!= trading_peers[*level2_peers].end(); level3_peers++){
                std::set<int>::iterator searchResult = trading_peers[*level3_peers].find(target);
                if (searchResult != trading_peers[*level3_peers].end()) return true;
            }
        }
    }
    return false;
}

bool
myHash::threeLevelSearch(int id1, int id2){

    int id1_num_peers, id2_num_peers;

    id1_num_peers = trading_peers[id1].size();
    id2_num_peers = trading_peers[id2].size();

    int source, target;
    if (id1_num_peers > id2_num_peers){
        source = id2;
        target = id1;
    } else {
        source = id1;
        target = id2;
    }

    std::set<int>::iterator level1_peers;

    level1_peers = trading_peers[source].begin();

    for ( ; level1_peers != trading_peers[source].end(); level1_peers++){
        if (feature2(*level1_peers, target)) {
            return true;
        }
    }
    return false;
}


// Breadth First Search version
bool
myHash::feature3_bfs(int id1, int id2){
// we know that id1 and id2 are not in neighborhood until level 2.

    int id1_num_peers, id2_num_peers;

    id1_num_peers = trading_peers[id1].size();
    id2_num_peers = trading_peers[id2].size();

    int source, target;
    if (id1_num_peers > id2_num_peers){
        source = id2;
        target = id1;
    } else {
        source = id1;
        target = id2;
    }

    std::set<int>::iterator level1_peers;

    level1_peers = trading_peers[source].begin();

    for ( ; level1_peers != trading_peers[source].end(); level1_peers++){
        if (threeLevelSearch(*level1_peers, target)) {
            return true;
        }
    }
    return false;
}

