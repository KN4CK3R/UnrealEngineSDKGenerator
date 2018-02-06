#include "PatternFinder.hpp"
#include "ObjectsStore.hpp"

#include "EngineClasses.hpp"

// This class contains the class which allows the generator access to global objects list.

TArray<UObject*>* GlobalObjects = nullptr;

bool ObjectsStore::Initialize()
{
	// TODO: Here you need to tell the class where the global object list is. You can use the function 'FindPattern()' to make this dynamic.

	GlobalObjects = reinterpret_cast<decltype(GlobalObjects)>(0x12341234);

	return true;
}

void* ObjectsStore::GetAddress()
{
	return GlobalObjects;
}

size_t ObjectsStore::GetObjectsNum() const
{
	return GlobalObjects->Num();
}

UEObject ObjectsStore::GetById(size_t id) const
{
	return (*GlobalObjects)[id];
}
