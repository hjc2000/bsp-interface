#pragma once

namespace bsp
{
    /// @brief DMA 的数据传输方向。
    enum class IDmaOptionsDirection
    {
        PeripheralToMemory,
        MemoryToPeripheral,
        MomoryToMemory,
    };

    /// @brief DMA 优先级
    enum class IDmaOptionsPriority
    {
        Low,
        Medium,
        High,
        VeryHigh,
    };

    class IDmaOptions
    {
    public:
        /// @brief DMA 拷贝数据的方向。
        /// @return
        virtual IDmaOptionsDirection Direction() const = 0;
        virtual void SetDirection(IDmaOptionsDirection value) = 0;

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
        virtual IDmaOptionsPriority Priority() const = 0;
        virtual void SetPriority(IDmaOptionsPriority value) = 0;
    };
} // namespace bsp
