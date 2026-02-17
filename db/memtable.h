//
// Created by 吴远澎 on 2026/2/16.
//

#ifndef MY_TOY_DB_MEMTABLE_H
#define MY_TOY_DB_MEMTABLE_H
#include "Status.h"

class MemTable
{
public:
    virtual ~MemTable() = default;
    MemTable();

    virtual Status get() = 0;
    virtual Status put() = 0;

};

#endif //MY_TOY_DB_MEMTABLE_H