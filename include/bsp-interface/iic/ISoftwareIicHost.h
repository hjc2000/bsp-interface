#pragma once
#include <bsp-interface/iic/IIicHost.h>

namespace bsp
{
	/// @brief SDA 方向枚举。
	enum class ISoftwareIicHost_SDADirection
	{
		Input,
		Output,
	};

	/// @brief 通过软件模拟的 IIC 总线主机接口。
	class ISoftwareIicHost :
		public bsp::IIicHost
	{
	private:
		/// @brief 发送应答信号。
		void SendAcknowledgment();

		/// @brief 发送非应答信号。
		void SendNotAcknowledgment();

		/// @brief 等待应答信号。
		/// @return 成功等到应答信号返回 true，没有等到返回 false.
		bool WaitForAcknowledgment();

		/// @brief 发送一位数据。
		/// @param value
		void SendBit(bool value);

		/// @brief 接收一个位。
		/// @return
		bool ReceiveBit();

	public:
		/* #region 接口 */

		///
		/// @brief 此 IIC 接口的名称。
		///
		/// @return
		///
		virtual std::string Name() const override = 0;

		///
		/// @brief 写 SCL 引脚的值。
		///
		/// @param value
		///
		virtual void WriteSCL(bool value) = 0;

		///
		/// @brief 更改 SDA 引脚的 IO 方向。
		///
		/// @param value
		///
		virtual void ChangeSDADirection(ISoftwareIicHost_SDADirection value) = 0;

		///
		/// @brief 写 SDA 引脚的值。
		///
		/// @param value
		///
		virtual void WriteSDA(bool value) = 0;

		///
		/// @brief 读 SDA 引脚的值。
		///
		/// @return
		///
		virtual bool ReadSDA() const = 0;

		///
		/// @brief SCL 的周期。
		///
		/// @note 实现的例子见 GpioSoftwareIicHost 类。GpioSoftwareIicHost 类只是简单地
		/// 用字段来储存本属性。
		///
		/// @return
		///
		virtual std::chrono::microseconds SclCycle() const override = 0;

		///
		/// @brief 设置 SCL 的周期。
		///
		/// @note 实现的例子见 GpioSoftwareIicHost 类。GpioSoftwareIicHost 类只是简单地
		/// 用字段来储存本属性。
		///
		/// @param value
		///
		virtual void SetSclCycle(std::chrono::microseconds value) override = 0;

		///
		/// @brief 等待从机的 ACK 信号的超时周期数。单位： SCL 的周期。
		///
		/// @note 实现的例子见 GpioSoftwareIicHost 类。GpioSoftwareIicHost 类只是简单地
		/// 用字段来储存本属性。
		///
		/// @return
		///
		virtual int WaitingForAckTimeoutCycleCount() const override = 0;

		///
		/// @brief 设置等待从机的 ACK 信号的超时周期数。单位： SCL 的周期。
		///
		/// @note 实现的例子见 GpioSoftwareIicHost 类。GpioSoftwareIicHost 类只是简单地
		/// 用字段来储存本属性。
		///
		/// @param value
		///
		virtual void SetWaitingForAckTimeoutCycleCount(int value) override = 0;
		/* #endregion */

		///
		/// @brief 发送 IIC 启动信号。
		///
		void SendStartingSignal() override;

		///
		/// @brief 发送 IIC 停止信号。
		///
		void SendStoppingSignal() override;

		///
		/// @brief 发送一个字节。
		/// @param value
		///
		void SendByte(uint8_t value) override;

		///
		/// @brief 读取 1 个字节。
		///
		/// @param send_nack 读取完这个字节后是否发送 nack 信号终止读取。传入 true 则发送 nack 信号，
		/// 传入 false 则发送 ack 信号，表示希望继续读取。
		///
		/// @return
		///
		uint8_t ReceiveByte(bool send_nack) override;
	};
} // namespace bsp
