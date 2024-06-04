#pragma once

namespace bsp
{
	template<typename T>
	class HandleWrapper
	{
	public:
		virtual T &Handle() = 0;

		T *operator->()
		{
			return &Handle();
		}

		operator T *()
		{
			return &Handle();
		}
	};
}