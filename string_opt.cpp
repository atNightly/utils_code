#include <array>
#include <cinttypes>
#include <sstream>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

namespace Localization
{
	using StringID = int32_t;
	enum class Languages
	{
		EN_US,
		EN_GB,
		Number
	};

	const StringID STRING_COLOR{0};
	
	class Manager
	{
	  private:
		using Strings = std::unordered_map<StringID,std::string>;
		using StringPacks = std::array<Strings,static_cast<size_t>(Languages::Number)>;
		StringPacks m_StringPacks;
		Strings* m_CurrentStringPack{nullptr};
		uint32_t m_LanguageIndex;
	  public:
		Manager();
		void SetLanaguage(Languages language);
		std::string GetString(StringID stringId) const;
	};
};

using namespace Localization;
//初始化,建立STRING_COLOR和Languages的关系
Manager::Manager()
{
	static const uint32_t INDEX_EN_US { static_cast<uint32_t>(Languages::EN_US)};
	m_StringPacks[INDEX_EN_US][STRING_COLOR] = "COLOR";
	
	static const uint32_t INDEX_EN_GB{ static_cast<uint32_t>(Languages::EN_GB)};
	m_StringPacks[INDEX_EN_GB][STRING_COLOR] = "COLOUR";

	SetLanaguage(Languages::EN_US); // 设置当前的语言
}


void Manager::SetLanaguage(Languages language)
{
	m_CurrentStringPack = &(m_StringPacks[static_cast<uint32_t>(language)]);
}

std::string Manager::GetString(StringID stringId) const //通过StringId获取对应的字符串
{
	stringstream resultStream;
	resultStream << "!!!";
	resultStream << stringId;
	resultStream << "!!!";

	string result{resultStream.str()};

	auto iter = m_CurrentStringPack->find(stringId);
	if (iter != m_CurrentStringPack->end())
	{
		result = iter->second;
	}

	return result;
}



int main()
{
	Localization::Manager localizationManager;
	string color{localizationManager.GetString(Localization::STRING_COLOR)};
	cout << "EN_US Localized string: " << color.c_str() << endl;
	localizationManager.SetLanaguage(Localization::Languages::EN_GB);
	color = localizationManager.GetString(Localization::STRING_COLOR);
	cout << "EN_GB Localized: " << color.c_str() << endl;

	color = localizationManager.GetString(1);
	cout << color.c_str() << endl;
	return 0;
}
