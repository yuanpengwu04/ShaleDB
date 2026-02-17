//
// Created by 吴远澎 on 2026/2/16.
//

#ifndef MY_TOY_DB_STATUS_H
#define MY_TOY_DB_STATUS_H
#include <string>

class Status
{
public:
    static Status ok() { return Status(kOk, ""); }
    static Status not_found(const std::string& message) { return Status(kNotFound, message); }
    static Status failed(const std::string& message) { return Status(kFailed, message); }

    enum Code
    {
        kOk = 0,
        kNotFound,
        kFailed,
    };

private:
    Status(Code code, const std::string& message);
};

#endif //MY_TOY_DB_STATUS_H