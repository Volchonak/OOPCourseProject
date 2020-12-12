#ifndef DATAEXCEPTION_H
#define DATAEXCEPTION_H

#include <exception>
#include <string>

class Exception: public std::exception
{
public:
    Exception(const std::string& message) noexcept;
    Exception(const char* message) noexcept;
    Exception(const Exception& obj);
    Exception(Exception&& obj);
    virtual const char* what() const noexcept override;

private:
    std::string m_message;
};

#endif // DATAEXCEPTION_H
