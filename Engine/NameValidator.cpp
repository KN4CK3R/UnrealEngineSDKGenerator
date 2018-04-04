#include "NameValidator.hpp"

#include <cctype>
#include <unordered_set>

#include "ObjectsStore.hpp"

std::string MakeValidName(std::string&& name)
{
	static std::unordered_set<char> disallowedChars = {
		' ', '?', '+', '-', ':', '/', '^', '(', ')', '[',
		']', '<', '>', '&', '.', '#', '\'', '"', '%',
	};

	static std::unordered_set<std::string> disallowedWords = {
		"alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
		"bool", "break", "case", "catch", "char", "char16_t", "char32_t", "class",
		"compl", "const", "constexpr", "const_cast", "continue", "decltype", "default",
		"delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export",
		"extern", "false", "float", "for", "friend", "goto", "if", "inline", "int",
		"long", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr",
		"operator", "or", "or_eq", "private", "protected", "public", "register",
		"reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_assert",
		"static_cast", "struct", "switch", "template", "this", "thread_local", "throw",
		"true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
		"virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
	};

	std::string valid(name);

	for (auto i = 0u; i < name.length(); ++i)
	{
		if (disallowedChars.find(valid[i]) != disallowedChars.end())
		{
			valid[i] = '_';
		}
	}

	if (!valid.empty())
	{
		if (std::isdigit(valid[0]) || disallowedWords.find(valid) != disallowedWords.end())
		{
			valid = '_' + valid;
		}
	}

	return valid;
}

std::string SimplifyEnumName(std::string&& name)
{
	const auto index = name.find_last_of(':');
	if (index == std::string::npos)
	{
		return name;
	}

	return name.substr(index + 1);
}

template<typename T>
std::string MakeUniqueCppNameImpl(const T& t)
{
	std::string name;
	if (ObjectsStore().CountObjects<T>(t.GetName()) > 1)
	{
		name += MakeValidName(t.GetOuter().GetName()) + "_";
	}
	return name + MakeValidName(t.GetName());
}

std::string MakeUniqueCppName(const UEConst& c)
{
	return MakeUniqueCppNameImpl(c);
}

std::string MakeUniqueCppName(const UEEnum& e)
{
	auto name = MakeUniqueCppNameImpl(e);
	if (!name.empty() && name[0] != 'E')
	{
		name = 'E' + name;
	}
	return name;
}

std::string MakeUniqueCppName(const UEStruct& ss)
{
	std::string name;
	if (ObjectsStore().CountObjects<UEStruct>(ss.GetName()) > 1)
	{
		name += MakeValidName(ss.GetOuter().GetNameCPP()) + "_";
	}
	return name + MakeValidName(ss.GetNameCPP());
}
