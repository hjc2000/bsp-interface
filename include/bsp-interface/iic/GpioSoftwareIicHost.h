#pragma once
#include "bsp-interface/gpio/IGpioPin.h"
#include "bsp-interface/iic/ISoftwareIicHost.h"

namespace bsp
{
	/// @brief 通过 IGpioPin 实现的软件 IIC 主机接口。
	class GpioSoftwareIicHost :
		public bsp::ISoftwareIicHost
	{
	private:
		std::string _name;
		std::string _scl_pin_name;
		std::string _sda_pin_name;
		bsp::IGpioPin *_scl_pin = nullptr;
		bsp::IGpioPin *_sda_pin = nullptr;
		std::chrono::microseconds _scl_cycle{4};
		int _waiting_for_ack_timeout_cycle = 100;

	public:
		/// @brief 构造函数。
		/// @param name IIC 端口名。
		/// @param scl_pin_name SCL 对应的 IGpioPin 的名称。
		/// @param sda_pin_name SDA 对应的 IGpioPin 的名称。
		GpioSoftwareIicHost(std::string name,
							std::string scl_pin_name,
							std::string sda_pin_name);

		/// @brief 此 IIC 接口的名称。
		/// @return
		std::string Name() const override;

		/// @brief 写 SCL 引脚的值。
		/// @param value
		void WriteSCL(bool value) override;

		/// @brief 更改 SDA 引脚的 IO 方向。
		/// @param value
		void ChangeSDADirection(ISoftwareIicHost_SDADirection value) override;

		/// @brief 写 SDA 引脚的值。
		/// @param value
		void WriteSDA(bool value) override;

		/// @brief 读 SDA 引脚的值。
		/// @return
		bool ReadSDA() const override;

		/// @brief SCL 的周期。
		/// @return
		std::chrono::microseconds SclCycle() const override;

		/// @brief 设置 SCL 的周期。
		/// @param value
		void SetSclCycle(std::chrono::microseconds value) override;

		/// @brief 等待从机的 ACK 信号的超时周期数。单位： SCL 的周期。
		/// @return
		int WaitingForAckTimeoutCycleCount() const override;

		/// @brief 设置等待从机的 ACK 信号的超时周期数。单位： SCL 的周期。
		/// @param value
		void SetWaitingForAckTimeoutCycleCount(int value) override;
	};
} // namespace bsp
