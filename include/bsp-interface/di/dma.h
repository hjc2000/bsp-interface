#pragma once
#include <base/container/IDictionary.h>
#include <bsp-interface/dma/IDmaChannel.h>
#include <memory>

/// @brief DMA 通道集合。
/// @return
base::IDictionary<std::string, bsp::dma::IDmaChannel *> const &DI_DmaChannelCollection();
