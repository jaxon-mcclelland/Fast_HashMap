#ifndef __HASHMAP
#define __HASHMAP

#define DEFAULT_LOAD_FACTOR 0.90

#include <vector>

using std::pair;
using std::vector;


// power of two hash table
template <class K, class V>
class HashMap {
    public:
        HashMap();
        ~HashMap();
        void clear();
        bool insert(const std::pair<K,V>& element);
        bool erase(const K& key);
        V operator[](const K& key) const;

        int get_capacity() const;
        double get_load_factor() const;
        int get_num_items() const;

    private:
        // returns the bucket index of an element
        unsigned int _hash(const K& key) const;
        
        // rehashes the entire table
        void _rehash();

        // find a slot in the hash table with a lower psl value than the new key
        bool _find_slot(const std::pair<K,V>& element, int psl, unsigned int idx);

        // shift keys up from idx after an item has been deleted where idx represents an empty slot to be filled
        void _shift_keys(unsigned int deleted_idx);

        unsigned int max_capacity = 0;
        unsigned int num_items = 0;
        unsigned int hash_const_a = 5;
        unsigned int hash_const_b = 9;
        vector<pair<pair<K,V>,int>> base_table;
};



template <class K, class V>
HashMap<K,V>::HashMap() {
    max_capacity = 16;
    num_items = 0;
    base_table = vector<pair<pair<K,V>, int>>(max_capacity, {{-1, -1}, -1});
}

template <class K, class V>
HashMap<K,V>::~HashMap() {
    base_table.clear();
}

// TODO: Implement move constructor and copy constructor

template <class K, class V>
void HashMap<K,V>::clear() {
    base_table.clear();
    this->base_table.resize(16);
    this->max_capacity = 16;
}

template <class K, class V>
bool HashMap<K,V>::insert(const std::pair<K,V>& element) {
    if(get_load_factor() > DEFAULT_LOAD_FACTOR) {
        _rehash();
    }
    int idx = _hash(element.first);
    if(base_table[idx].second == -1) {
        base_table[idx] = {element, idx};
    } else if(!_find_slot(element, 1, ++idx)) {
            return false;
    }
    ++num_items;
    return true;
}

template <class K, class V>
bool HashMap<K,V>::erase(const K& key) {
    unsigned int idx = _hash(key);
    for(; idx < this->max_capacity; ++idx) {
        if(base_table[idx].first.first == key) {
            _shift_keys(idx);
            --num_items;
            return true;
        }
        if(base_table[idx].second < 1) {
            return false;
        }
    }
    return true;
}

template <class K, class V>
V HashMap<K,V>::operator[](const K& key) const {
    unsigned int idx = _hash(key);
    while(idx < this->max_capacity && base_table[idx].second > 0) {
        if(base_table[idx].first.first == key) {
            return base_table[idx].first.second;
        }
        ++idx;
    }
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
unsigned int HashMap<K,V>::_hash(const K& key) const {
        
    unsigned int hash_code = ((hash_const_a * key + hash_const_b));

    int hash_val = hash_code & ((hash_code << 5) | (hash_code << 12));
    return hash_val & (this->max_capacity - 1);    
    
}

template <class K, class V>
void HashMap<K,V>::_rehash() {
    auto new_table = base_table;
    base_table.clear();
    this->max_capacity = this->max_capacity << 1;
    base_table.resize(this->max_capacity, {{-1, -1}, -1});
    hash_const_a = (hash_const_a << 1) + 1;
    hash_const_b = (hash_const_b << 1) + 1;
    for(auto itr:new_table) {
        if(itr.second != -1) {
            insert(itr.first);
        } 
    }
}

template <class K, class V>
bool HashMap<K,V>::_find_slot(const std::pair<K,V>& element, int psl, unsigned int idx) {
    for(; idx < this->max_capacity; ++idx) {
        if(base_table[idx].second == -1) {
            base_table[idx] = {element, psl};
            return true;
        } else if(base_table[idx].second < psl) {
            std::pair<K,V> original_occupant = base_table[idx].first;
            int original_psl = base_table[idx].second;
            base_table[idx] = {element, psl};
            _find_slot(original_occupant, ++original_psl, ++idx);
            return true;
        }
        ++psl;
    }
    return false;
}

template <class K, class V>
void HashMap<K,V>::_shift_keys(unsigned int deleted_idx) {
    while(deleted_idx < this->max_capacity - 1 && base_table[deleted_idx].second > 0) {
        base_table[deleted_idx] = base_table[++deleted_idx];
    }
}



#endif
