#include "Exception.h"


Exception::Exception(const std::string& message) noexcept
{
    m_message = message;
}
Exception::Exception(const char* message) noexcept
{
    m_message = message;
}
Exception::Exception(const Exception& obj)
{
    m_message = obj.m_message;
}
Exception::Exception(Exception&& obj)
{
    m_message = std::move(obj.m_message);
}

const char* Exception::what() const noexcept
{
    return m_message.c_str();
}
