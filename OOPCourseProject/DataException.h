#ifndef DATAEXCEPTION_H
#define DATAEXCEPTION_H

#include <exception>
#include <string>

using std::exception;
class DataException: public exception
{
public:
    DataException(const std::string& message) noexcept;
    DataException(const char* message) noexcept;
    DataException(const DataException& ) = default;
    ~DataException() = default;
    virtual const char* what() const noexcept override;

private:
    std::string m_message;
};

#endif // DATAEXCEPTION_H
