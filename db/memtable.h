//
// Created by 吴远澎 on 2026/2/16.
//

#ifndef MY_TOY_DB_MEMTABLE_H
#define MY_TOY_DB_MEMTABLE_H
#include "status.h"

class MemTable
{
public:
    virtual ~MemTable() = default;
    MemTable();

    virtual status get() = 0;
    virtual status put() = 0;

};

#endif //MY_TOY_DB_MEMTABLE_H