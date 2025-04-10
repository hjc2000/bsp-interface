#include "key.h"
#include "KeyScanner.h"

namespace
{
	class Initializer
	{
	public:
		Initializer()
		{
			bsp::di::key::KeyScanner();
		}
	};

	Initializer volatile _key_scanner_hjc_init{};

} // namespace

bsp::IKeyScanner &bsp::di::key::KeyScanner()
{
	static bsp::KeyScanner o{};
	return o;
}
