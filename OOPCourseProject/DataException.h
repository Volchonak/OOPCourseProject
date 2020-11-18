#ifndef DATAEXCEPTION_H
#define DATAEXCEPTION_H

#include <exception>
#include <string>

using std::exception;
class DataException: public exception
{
public:
    DataException(const std::string& message);
    DataException(const char* message);
    DataException(const DataException& ) = default;
    ~DataException() = default;
    const char* what() const override;

};

#endif // DATAEXCEPTION_H
