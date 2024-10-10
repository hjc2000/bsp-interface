#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/dma/IDmaChannel.h>
#include <memory>

/// @brief 构造一个 bsp::IDmaOptions 对象并返回。它可以用来配置 DMA。
/// @return bsp::IDmaOptions 对象
std::shared_ptr<bsp::IDmaOptions> DICreate_DmaOptions();

/// @brief DMA 通道集合。
/// @return
base::IDictionary<std::string, bsp::IDmaChannel *> const &DI_DmaChannelCollection();
