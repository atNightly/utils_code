#include <cinttypes>
#include <functional>
#include <string>
#include <unordered_set>

using namespace std;

class SetObject;

namespace std
{
	template<>
	class hash<SetObject>
	{
		public:
			template<typename... Args>
			size_t operator()(Args&&... setObject)const
			{
				return hash<string>()((forward<Args...>(setObject...)).GetName());
			}
	};
}


