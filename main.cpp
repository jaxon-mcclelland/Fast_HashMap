#include <map>
#include <string>
#include <chrono>
#include <cassert>
#include "HashMap.h"
#include <iostream>
#include <fstream>

using std::string;

void testHash(HashMap<int, int> *hash, std::ofstream &myfile)
{

    myfile << "current size: " << hash->get_capacity() << " bucket count: " << hash->get_num_items()
           << " load factor: " << hash->get_load_factor() << std::endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000; ++i)
    {
        assert(hash->insert(std::make_pair(i, i)));
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    myfile << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    begin = std::chrono::steady_clock::now();
    assert((*hash)[97] == 97);
    end = std::chrono::steady_clock::now();
    myfile << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    begin = std::chrono::steady_clock::now();
    hash->erase(97);
    end = std::chrono::steady_clock::now();
    myfile << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    begin = std::chrono::steady_clock::now();
    assert((*hash)[1000] == 1000);
    end = std::chrono::steady_clock::now();
    myfile << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

    myfile << "current size: " << hash->get_capacity() << " bucket count: " << hash->get_num_items()
           << " load factor: " << hash->get_load_factor() << std::endl;
    hash->clear();
}

int main(int argc, char *argv[])
{
    
    std::ofstream myfile;
    myfile.open("../output.txt");
    HashMap<int, int> cHash(101);
    testHash(&cHash, myfile);
    myfile.close();
    
    return 0;
}