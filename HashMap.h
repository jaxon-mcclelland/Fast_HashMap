#ifndef __HASHMAP
#define __HASHMAP

#define mult_const 0.625292
#define load_factor 0.75

#include <vector>

using std::pair;
using std::vector;



template <class K, class V>
class HashMap {
    public:
        HashMap(int tableSize = 20);
        ~HashMap();
        void clear();
        bool insert(std::pair<K,V> element, bool rehash_if_collision = true);
        bool erase(const K& key);
        V operator[](const K& key) const;

        int get_capacity() const;
        double get_load_factor() const;
        int get_num_items() const;

    private:
        // returns the bucket index of an element
        int hash(const K& key) const;
        
        // rehashes the entire table
        void rehash();

        int max_capacity = 0;
        int num_items = 0;
        vector<pair<K,V>> base_table;
        


};



template <class K, class V>
HashMap<K,V>::HashMap(int tableSize = 20) {
    max_capacity = tableSize;
    num_items = 0;
    base_table = vector<pair<K,V>>(max_capacity);
}

template <class K, class V>
HashMap<K,V>::~HashMap() {
    base_table.clear();
}

// TODO: Implement move constructor and copy constructor

template <class K, class V>
void HashMap<K,V>::clear() {
    base_table.clear();
}

template <class K, class V>
bool HashMap<K,V>::insert(std::pair<K,V> element, bool rehash_if_collision = true) {
    int idx = hash(element.first);

}

template <class K, class V>
bool HashMap<K,V>::erase(const K& key) {
    return false;
}

template <class K, class V>
V HashMap<K,V>::operator[](const K& key) const {
    return {};
}

/// *** PUBLIC GETTER FUNCTIONS *** /// 

template <class K, class V>
int HashMap<K,V>::get_capacity() const {
    return max_capacity;
}

template <class K, class V>
double HashMap<K,V>::get_load_factor() const {
    return max_capacity == 0 ? 0.0 : (double)num_items / max_capacity;
}

template <class K, class V>
int HashMap<K,V>::get_num_items() const {
    return num_items;
}

/// *** PRIVATE METHODS *** ///

template <class K, class V>
int HashMap<K,V>::hash(const K& key) const {
    return max_capacity * ((mult_const * key) % 1);
}

template <class K, class V>
void HashMap<K,V>::rehash() {
    return;
}


#endif
