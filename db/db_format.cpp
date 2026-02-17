//
// Created by 吴远澎 on 2026/2/16.
//

#include "db_format.h"
#include <cassert>
#include <cstring>

#if defined(__APPLE__)
    #include <libkern/OSByteOrder.h>
    #define htole64(x) OSSwapHostToLittleInt64(x)
    #define le64toh(x) OSSwapLittleToHostInt64(x)
#else
    #include <endian.h>
#endif


int internal_key_comparator(const InternalKey& key1, const InternalKey& key2)
{
    const std::string& rep1 = key1.data();
    const std::string& rep2 = key2.data();

    assert(rep1.size() > 8);
    assert(rep2.size() > 8);

    int compare = rep1.compare(0, rep1.length() - 8, rep2, 0, rep2.length() - 8);
    if (compare) { return compare; }

    SequenceNumber trailer1 = 0;
    std::memcpy(&trailer1, rep1.data() + rep1.size() - 8, sizeof(SequenceNumber));
    trailer1 = le64toh(trailer1);

    SequenceNumber trailer2 = 0;
    std::memcpy(&trailer2, rep2.data() + rep2.size() - 8, sizeof(SequenceNumber));
    trailer2 = le64toh(trailer2);

    if (trailer1 > trailer2) { return -1; }
    if (trailer1 < trailer2) { return 1; }
    return 0;
}

bool InternalKey::operator==(const InternalKey& key) const
{
    return encoded_key_ == key.encoded_key_;
}

bool InternalKey::operator!=(const InternalKey& key) const
{
    return encoded_key_ != key.encoded_key_;
}

bool InternalKey::operator<(const InternalKey& key) const
{
    return internal_key_comparator(*this, key) < 0;
}

bool InternalKey::operator>(const InternalKey& key) const
{
    return key < *this;
}

std::string InternalKey::pack_trailer(SequenceNumber sequence_number, ValueType value_type)
{
    assert(sequence_number < (1ULL << 56));
    std::string result(8, '\0');
    const SequenceNumber packed = sequence_number << 8 | static_cast<SequenceNumber>(value_type);
    const SequenceNumber le = htole64(packed);
    std::memcpy(result.data(), &le, 8);
    return result;
}


InternalKey::InternalKey(const std::string& key, SequenceNumber sequence_number, ValueType value_type)
{
    assert(key.length() > 0);
    encoded_key_.reserve(key.length() + 8);
    encoded_key_.append(key);
    encoded_key_.append(pack_trailer(sequence_number, value_type));
}
