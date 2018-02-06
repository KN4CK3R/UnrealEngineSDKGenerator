#pragma once

#include <set>
#include <string>
#include <Windows.h>

// This file contains the needed classes as they are present in the game memory.
// To get these classes use a helper application like ReClass.NET (https://github.com/KN4CK3R/ReClass.NET)

struct FPointer
{
	uintptr_t Dummy;
};

struct FQWord
{
	int A;
	int B;
};

struct FName
{
	int32_t Index;
};

template<class T>
class TArray
{
	friend class FString;

public:
	TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	size_t Num() const
	{
		return Count;
	};

	T& operator[](size_t i)
	{
		return Data[i];
	};

	const T& operator[](size_t i) const
	{
		return Data[i];
	};

	bool IsValidIndex(size_t i) const
	{
		return i < Num();
	}

private:
	T* Data;
	int32_t Count;
	int32_t Max;
};

class FString : public TArray<wchar_t>
{
public:
	std::string ToString() const
	{
		int size = WideCharToMultiByte(CP_UTF8, 0, Data, Count - 1, nullptr, 0, nullptr, nullptr);
		std::string str(size, 0);
		WideCharToMultiByte(CP_UTF8, 0, Data, Count - 1, &str[0], size, nullptr, nullptr);
		return str;
	}
};

struct FScriptDelegate
{
	unsigned char UnknownData[0x0C];
};

class UClass;

class UObject
{
public:
	FPointer VfTableObject;
	int InternalIndex;
	char UnknownData00[0x10];
	UObject* Outer;
	char UnknownData01[0x4];
	FName Name;
	UClass* Class;
};

class UField : public UObject
{
public:
	UField* SuperField;
	UField* Next;
	UField* HashNext;
};

class UEnum : public UField
{
public:
	TArray<FName> Names;
};

class UConst : public UField
{
public:
	FString Value;
};

class UStruct : public UField
{
public:
	char UnknownData00[0x08];
	UField* Children;
	unsigned long PropertySize;
	char UnknownData01[0x2C];
};

class UScriptStruct : public UStruct
{
public:

};

class UFunction : public UStruct
{
public:
	uint32_t FunctionFlags;
	uint16_t iNative;
	char UnknownData00[2];
	uint8_t OperPrecedence;
	uint8_t NumParms;
	uint16_t ParmsSize;
	uint16_t ReturnValueOffset;
	char UnknownData01[2];
	void* Func;
};

class UState : public UStruct
{
public:
	char UnknownData00[0x418];
};

class UClass : public UState
{
public:
	char UnknownData00[0x8C];
};

class UProperty : public UField
{
public:
	unsigned long ArrayDim;
	unsigned long ElementSize;
	unsigned long PropertyFlags;
	unsigned long PropertySize;
	char UnknownData01[0x4];
	unsigned long Offset;
	char UnknownData02[0x20];
};

class UPointerProperty : public UProperty
{
public:

};

class UByteProperty : public UProperty
{
public:
	UEnum* Enum;
};

class UIntProperty : public UProperty
{
public:

};

class UFloatProperty : public UProperty
{
public:

};

class UBoolProperty : public UProperty
{
public:
	unsigned long BitMask;
};

class UObjectProperty : public UProperty
{
public:
	UClass* PropertyClass;
	UObjectProperty* NextReference;
};

class UClassProperty : public UObjectProperty
{
public:
	UClass* MetaClass;
};

class UInterfaceProperty : public UProperty
{
public:
	UClass* InterfaceClass;
};

class UNameProperty : public UProperty
{
public:

};

class UStructProperty : public UProperty
{
public:
	UStruct* Struct;
};

class UStrProperty : public UProperty
{
public:

};

class UArrayProperty : public UProperty
{
public:
	UProperty* Inner;
};

class UMapProperty : public UProperty
{
public:
	UProperty* KeyProp;
	UProperty* ValueProp;
};

class UDelegateProperty : public UProperty
{
public:
	UFunction* SignatureFunction;
};
