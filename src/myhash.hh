/**************************************************************
 * header for myhash class used to keep peers who made transactions with.
 * by Ganghee Jang
 **************************************************************
 */

#ifndef __MY_HASH_CLASS__
#define __MY_HASH_CLASS__

#include <unordered_map>
#include <utility>
#include <vector>
#include <iostream>
#include <set>

class myHash {
private:
    std::unordered_map<int, std::set<int> > trading_peers;

    bool threeLevelSearch(int id1, int id2);

public:
    myHash() {
        trading_peers.reserve(100000);
    }

    ~myHash() {
    }

    bool isTrader(int id1){
        std::unordered_map<int, std::set<int> >::const_iterator Iter = trading_peers.find (id1);
        if (Iter == trading_peers.end()) return false;
        else return true;
    }

    void addTradingPeer(int id1, int id2);

    int numTradingPeers(int id1){
        std::unordered_map<int, std::set<int> >::const_iterator Iter1 = trading_peers.find(id1);
        if (Iter1 == trading_peers.end()) return 0;
        else return Iter1->second.size();
    }

    int getTotalTraders() {
        return trading_peers.size();
    }

    void printTable(); //debugging purpose. Do not use with Big data set!!!
    void histNumTraders();

    bool feature1(int id1, int id2);
    bool feature2(int id1, int id2);
    bool feature3_dfs(int id1, int id2);
    bool feature3_bfs(int id1, int id2);
};

#endif
