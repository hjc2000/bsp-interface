#pragma once

namespace bsp
{
	class IGpioPin
	{
	public:
		virtual void Initialize() = 0;
		virtual void SetAsDefaultMode() = 0;
	};
}
