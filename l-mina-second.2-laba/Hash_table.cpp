#include "Hash_table.h"

int Hash_table::hash(std::string key)
{
    const int p = 31;
    int hash = 0;
    int p_pow = 1;
    for (char c : key) {
        if (c != ' ')
        {
            hash = (hash + (c - 'a' + 1) * p_pow) % MAX_SIZE;
            p_pow = (p_pow * p) % MAX_SIZE;
        }
    }
    return hash;
}

int Hash_table::find_free_pos(int pos)
{
    while (table[pos] && table[pos]->get_used()) {
        pos = (pos + 1) % MAX_SIZE;
    }
    return pos;
}

Hash_table::Hash_table()
{
    table = new Hash_item * [MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) {
        table[i] = nullptr;
    }
}

void Hash_table::fill(std::ifstream& file)
{
    if (file.is_open())
    {
        std::string word;
        while (file >> word)
            if (!insert(word))
            {
                printf("Все слова не влезли\n");
                break;
            }
        printf("\nЗаполнено\n\n");
    }
}



void Hash_table::print()
{
    if (is_empty())
    {
        printf("\n\nТаблица пуста\n\n");
        return;
    }
    printf("\n------------------------------------------\n");
    for (int i{}; i < MAX_SIZE; ++i)
    {
        Hash_item* current = table[i];
        if (current && current->get_used())
        {   
            current->print();
            if (i % 3 == 0) { std::cout << std::endl; }
        }
    }
    printf("\n------------------------------------------\n");

}

int Hash_table::search(std::string words)
{
    int pos = hash(words);
    int start_pos = pos;
    do {
        if (table[pos] && table[pos]->compare_key(words) && table[pos]->get_used())
            return pos;
        pos = (pos + 1) % MAX_SIZE;
    } while (pos != start_pos);
    return -1;
}
bool Hash_table::insert(std::string new_key)
{
    bool result;
    if (cur_size == MAX_SIZE)
        result = false;
    else {
        int srch = search(new_key);
        if (srch != -1)
        {
            result = true;
            table[srch]->count_plus();
        }
        else {
            int pos = hash(new_key);
            pos = find_free_pos(pos);
            table[pos] = new Hash_item(new_key);
            cur_size++;
            result = true;
        }
    }
    return result;
}

bool Hash_table::del(std::string words)
{
    int finded = search(words);
    if (finded == -1)
    { 
        printf("\nТакой элемент не найден\n");
        return false; 

    }
    if (!cur_size)
    {
        printf("\nТаблица пуста\n");
        return false;
    }
    Hash_item* current = table[finded];
    if (current->get_count() == 1) { current->set_used(false); cur_size--; }
    else current->count_minus();
    printf("\nЭлемент удален\n\n");
    return true;
    
}

void Hash_table::clear()
{
    if (is_empty())
    {
        printf("\n\nТаблица пуста\n\n");
        return;
    }
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (table[i])
        {
            delete table[i];
            table[i] = nullptr;
        }
    }
}
