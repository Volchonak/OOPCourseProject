#include "DataException.h"


DataException::DataException(const std::string& message) noexcept
{
    m_message = message;
}
DataException::DataException(const char* message) noexcept
{
    m_message = message;
}
const char* DataException::what() const noexcept
{
    return m_message.c_str();
}
