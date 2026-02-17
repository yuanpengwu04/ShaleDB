//
// Created by 吴远澎 on 2026/2/16.
//

#ifndef MY_TOY_DB_TYPES_H
#define MY_TOY_DB_TYPES_H
#include <cstdint>

using SequenceNumber = uint64_t;

enum ValueType
{
    kTypeDeletion = 0,
    kTypeValue,
};

#endif //MY_TOY_DB_TYPES_H