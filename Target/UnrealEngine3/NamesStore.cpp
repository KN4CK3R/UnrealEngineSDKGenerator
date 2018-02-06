#include <windows.h>

#include "PatternFinder.hpp"
#include "NamesStore.hpp"

#include "EngineClasses.hpp"

// This class contains the class which allows the generator access to global names list.

class FNameEntry
{
public:
	uint32_t Index;
	char UnknownData00[0x0C];
	wchar_t WideName[1024];

	int32_t GetIndex() const
	{
		return Index;
	}

	const wchar_t* GetWideName() const
	{
		return WideName;
	}

	std::string GetName() const
	{
		const auto length = std::wcslen(WideName);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(WideName, WideName + length, '?', &str[0]);

		return str;
	}
};

TArray<FNameEntry*>* GlobalNames = nullptr;

bool NamesStore::Initialize()
{
	// TODO: Here you need to tell the class where the global names list is. You can use the function 'FindPattern()' to make this dynamic.

	GlobalNames = reinterpret_cast<decltype(GlobalNames)>(0x12341234);

	return true;
}

void* NamesStore::GetAddress()
{
	return GlobalNames;
}

size_t NamesStore::GetNamesNum() const
{
	return GlobalNames->Num();
}

bool NamesStore::IsValid(size_t id) const
{
	return GlobalNames->IsValidIndex(id) && (*GlobalNames)[id] != nullptr;
}

std::string NamesStore::GetById(size_t id) const
{
	return (*GlobalNames)[id]->GetName();
}
