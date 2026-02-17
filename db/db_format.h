//
// Created by 吴远澎 on 2026/2/16.
//

#ifndef MY_TOY_DB_DB_FORMAT_H
#define MY_TOY_DB_DB_FORMAT_H

#include <string>

#include "types.h"

class InternalKey;
int internal_key_comparator(const InternalKey& k1, const InternalKey& k2);

class InternalKey
{
public:
    InternalKey() = default;
    InternalKey(const std::string& key, SequenceNumber sequence_number, ValueType value_type);
    const std::string& data() const { return encoded_key_; }
    bool operator<(const InternalKey& key) const;
    bool operator>(const InternalKey& key) const;
    bool operator==(const InternalKey& key) const;
    bool operator!=(const InternalKey& key) const;

private:
    std::string encoded_key_;
    static std::string pack_trailer(SequenceNumber sequence_number, ValueType value_type);

};

#endif //MY_TOY_DB_DB_FORMAT_H
