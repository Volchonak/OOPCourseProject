#include "DataException.h"


DataException::DataException(const std::string& message) : exception(message.c_str())
{

}
DataException::DataException(const char* message) : exception(message)
{

}
const char* DataException::what() const
{
    return exception::what();
}
