#include <windows.h>

#include "PatternFinder.hpp"
#include "NamesStore.hpp"

#include "EngineClasses.hpp"

// This class contains the class which allows the generator access to global names list.

struct FNameEntry
{
	char UnknownData00[0xC];
	wchar_t Data[0x10];
	
	std::string GetName() const
	{
		const auto length = std::wcslen(Data);
		const auto neededLength = WideCharToMultiByte(CP_UTF8, 0, Data, length, nullptr, 0, nullptr, nullptr);
		std::string str(neededLength, 0);
		WideCharToMultiByte(CP_UTF8, 0, Data, length, &str[0], neededLength, nullptr, nullptr);
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
