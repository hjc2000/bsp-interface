#include "RmaFlash.h"

bsp::RmaFlash::RmaFlash(std::string const &name, base::Span const &span)
{
    _name = name;
    _span = span;
}

std::string bsp::RmaFlash::Name()
{
    return _name;
}

size_t bsp::RmaFlash::SectorSize() const
{
    return 1;
}

int32_t bsp::RmaFlash::SectorCount() const
{
    return _span.Size();
}

int32_t bsp::RmaFlash::ProgrammingSize() const
{
    return 1;
}

void bsp::RmaFlash::Erase()
{
    _span.FillWith(0xff);
}

void bsp::RmaFlash::EraseSector(int32_t sector_index)
{
    _span[sector_index] = 0xff;
}

void bsp::RmaFlash::Program(size_t addr, uint8_t const *buffer)
{
    _span[addr] = *buffer;
}

void bsp::RmaFlash::Read(size_t addr, uint8_t *buffer, int32_t count)
{
    std::copy(_span.Buffer() + addr,
              _span.Buffer() + addr + count,
              buffer);
}
