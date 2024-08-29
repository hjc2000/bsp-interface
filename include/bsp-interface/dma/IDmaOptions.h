#pragma once
#include <string>

namespace bsp
{
    /// @brief DMA 的数据传输方向。
    enum class IDmaOptions_Direction
    {
        PeripheralToMemory,
        MemoryToPeripheral,
        MomoryToMemory,
    };

    /// @brief DMA 优先级
    enum class IDmaOptions_Priority
    {
        Low,
        Medium,
        High,
        VeryHigh,
    };

    /// @brief DMA 选项。
    class IDmaOptions
    {
    public:
        /// @brief DMA 拷贝数据的方向。
        /// @return
        virtual IDmaOptions_Direction Direction() const = 0;
        virtual void SetDirection(IDmaOptions_Direction value) = 0;

        /// @brief DMA 拷贝数据的过程中，是否自动递增外设数据指针。
        /// @return 返回 true 表示递增，返回 false 表示不递增。
        virtual bool PeripheralIncrement() const = 0;
        virtual void SetPeripheralIncrement(bool value) = 0;

        /// @brief DMA 拷贝数据的过程中，是否自动递增内存数据指针。
        /// @return 返回 true 表示递增，返回 false 表示不递增。
        virtual bool MemoryIncrement() const = 0;
        virtual void SetMemoryIncrement(bool value) = 0;

        /// @brief 外设数据对齐的字节数
        /// @return
        virtual int PeripheralDataAlignment() const = 0;
        virtual void SetPeripheralDataAlignment(int value) = 0;

        /// @brief 内存数据对齐的字节数。
        /// @return
        virtual int MemoryDataAlignment() const = 0;
        virtual void SetMemoryDataAlignment(int value) = 0;

        /// @brief DMA 优先级。
        /// @return
        virtual IDmaOptions_Priority Priority() const = 0;
        virtual void SetPriority(IDmaOptions_Priority value) = 0;

        /// @brief 此 DMA 要被连接到哪里
        /// @return
        virtual std::string Parent() const = 0;

        /// @brief 此 DMA 要被连接到哪里
        /// @param value
        virtual void SetParent(std::string value) = 0;
    };
} // namespace bsp
