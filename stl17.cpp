#include <cinttypes>
#include <functional>
#include <string>
#include <unordered_set>

using namespace std;

class SetObject;

//给hash容器做模板特化
namespace std
{
	template<>
	class hash<SetObject>
	{
		public:
			template<typename... Args> //可变的模板参数
			size_t operator()(Args&&... setObject)const
			{
				return hash<string>()((forward<Args...>(setObject...)).GetName());
			}
	};
}


