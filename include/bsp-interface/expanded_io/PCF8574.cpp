#include "PCF8574.h"

bsp::PCF8574::PCF8574(std::string const &name, bsp::IIicHost *iic_host, uint8_t address)
{
    _name = name;
    _iic_host = iic_host;
}
