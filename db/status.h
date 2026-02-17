//
// Created by 吴远澎 on 2026/2/16.
//

#ifndef MY_TOY_DB_STATUS_H
#define MY_TOY_DB_STATUS_H
#include <string>

class status
{
public:
    static status ok() { return status(kOk, ""); }
    static status not_found(const std::string& message) { return status(kNotFound, message); }
    static status failed(const std::string& message) { return status(kFailed, message); }

    enum Code
    {
        kOk = 0,
        kNotFound,
        kFailed,
    };

private:
    status(Code code, const std::string& message);
};

#endif //MY_TOY_DB_STATUS_H