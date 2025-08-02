#include<bits/stdc++.h>
#include <chrono>
using namespace std;

#define CACHE_SIZE 32 // in KB
#define BLOCK_SIZE 64 // in B
#define WAYS_CNT 8
#define ADD_BITS 40
#define WRITE_MISS 1

class Cache{
public:
    vector<vector<int>> Status_bits;
    vector<vector<int>> Tag_bits;

    Cache();
    bool search(int tag, int index);
    void set(int tag, int index, int ranWays);
};


int main(){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count(); 
    default_random_engine generator (seed); 

    // Initializes the cache
    Cache* _cache = new Cache();
    int Block_Cnt = (CACHE_SIZE * 1024) / BLOCK_SIZE;
    int SetCnt = Block_Cnt / WAYS_CNT;

    // Breaking the address bits
    int offset_bits = log2(BLOCK_SIZE);
    int index_bits = log2(SetCnt);
    int tag_bits = ADD_BITS - (index_bits + offset_bits);
    int tagMax = (1 << tag_bits);
    int indMax = (1 << index_bits);

    normal_distribution<double> dist_ways(WAYS_CNT / 2, WAYS_CNT / 4);
    normal_distribution<double> distribution((1LL << 39), (1LL << 14));

    // Get desired runtime in seconds
    int duration_seconds;
    cout << "Enter duration in seconds: ";
    cin >> duration_seconds;

    // Capture the start time
    auto start_time = chrono::high_resolution_clock::now();

    int hits = 0, miss = 0, write = 0;

    while (true) {
        // Calculate elapsed time
        auto current_time = chrono::high_resolution_clock::now();
        auto elapsed_time = chrono::duration_cast<chrono::seconds>(current_time - start_time).count();

        // Stop if elapsed time exceeds the set duration
        if (elapsed_time >= duration_seconds) break;

        long long address = (long long)distribution(generator);

        int tag = address >> (index_bits + offset_bits);
        int index = (address >> offset_bits) % indMax;

        // Randomly marking the request as read or write 
        int isWrite = rand() % 2;
        if(isWrite == 1) write++;

        if(_cache->search(tag, index)) {
            hits++;
        }else{
            miss++;            
            if(isWrite == 0){
                int ranWays = (int)dist_ways(generator);
                while (ranWays < 0 || ranWays >= WAYS_CNT) {
                    ranWays = (int)dist_ways(generator);
                }
                _cache->set(tag, index, ranWays);
            }
        }
    }

    // cout << "Write: " << write << endl;
    cout << "Total Hits: " << hits << endl;
    cout << "Total Misses: " << miss << endl;
    cout << "Miss Rate: " << ((double)miss / (hits + miss)) * 100 << endl;

    return 0;
}



// Cache -------------------------------------------------------------------------------

Cache::Cache(){
    int Block_Cnt = (CACHE_SIZE*1024) / BLOCK_SIZE; 
    Status_bits.resize(Block_Cnt/WAYS_CNT, vector<int>(WAYS_CNT, 0));
    Tag_bits.resize(Block_Cnt/WAYS_CNT, vector<int>(WAYS_CNT, 0));
}

bool Cache::search(int tag, int index){
    for(int i=0; i<WAYS_CNT; i++){
        if(Status_bits[index][i] == 1 && Tag_bits[index][i] == tag){
            return true;
        }
    }
    return false;
}

void Cache::set(int tag, int index, int ranWays){
    for(int i=0; i<WAYS_CNT; i++){
        if(Status_bits[index][i] == 0){
            Status_bits[index][i] = 1;
            Tag_bits[index][i] = tag;
            return;
        }
    }
    // if no empty block is available then we have to randomly replace a block
    Status_bits[index][ranWays] = 1;
    Tag_bits[index][ranWays] = tag;
    return;
}