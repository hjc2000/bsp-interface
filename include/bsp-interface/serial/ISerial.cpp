#include "ISerial.h"

using namespace bsp;

#pragma region Stream

bool ISerial::CanRead()
{
    return true;
}

bool ISerial::CanWrite()
{
    return true;
}

bool ISerial::CanSeek()
{
    return false;
}

int64_t ISerial::Length()
{
    return 0;
}

void ISerial::SetLength(int64_t value)
{
    // 不支持的操作
}

void ISerial::Flush()
{
    // Write 方法利用 DMA 直接发送缓冲区，本类没有内部缓冲区，不需要冲洗。
}

int64_t ISerial::Position()
{
    return 0;
}

void ISerial::SetPosition(int64_t value)
{
    // 不支持的操作。
}

#pragma endregion
