#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <Windows.h>


class Hash_table
{
private:
    class Hash_item
    {
    private:
        std::string key{ "" }; //пара слов
        int count{ 1 }; //количество вхождений
        bool used{ true }; //false - удалено, true - не удалено
    public:
        Hash_item(std::string _key) { key = _key; }
        void count_plus() { count++; }
        void count_minus() { count--; }
        void set_used(bool value) { used = value; };
        bool compare_key(std::string new_key) { return key == new_key; }
        bool get_used() { return used; }
        int get_count() { return count; }
        std::string get_key() { return key; }

        void print() { std::cout << key << ":" << count << " | "; }
    };
    const int MAX_SIZE = 100;
    int cur_size = 0;
    Hash_item** table;

    int hash(std::string key);
    int find_free_pos(int pos);

public:
    Hash_table();
    void fill(std::ifstream& file);
    ~Hash_table() 
    {
        clear();
        delete table;
    }

    std::map<std::string, int> task();

    void print();
    int search(std::string words);
    bool insert(std::string new_key);
    bool del(std::string words);
    void clear();



};