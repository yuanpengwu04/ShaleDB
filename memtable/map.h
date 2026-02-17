//
// Created by 吴远澎 on 2026/2/16.
//

#ifndef MY_TOY_DB_HASHMAP_H
#define MY_TOY_DB_HASHMAP_H
#include "db/memtable.h"

class MapMemTable : public MemTable
{
public:
    HashMapMemTable();
    ~HashMapMemTable();
private:

};

#endif //MY_TOY_DB_HASHMAP_H