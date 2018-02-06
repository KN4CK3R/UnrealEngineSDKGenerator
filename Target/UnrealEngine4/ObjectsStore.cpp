#include "PatternFinder.hpp"
#include "ObjectsStore.hpp"

#include "EngineClasses.hpp"

// This class contains the class which allows the generator access to global objects list.

class FUObjectItem
{
public:
	UObject* Object;
	int32_t Flags;
	int32_t ClusterIndex;
	int32_t SerialNumber;
};

class TUObjectArray
{
public:
	FUObjectItem* Objects;
	int32_t MaxElements;
	int32_t NumElements;
};

class FUObjectArray
{
public:
	int32_t Dummy1;
	int32_t Dummy2;
	int32_t Dummy3;
	int32_t Dummy4;

	TUObjectArray ObjObjects;
};

FUObjectArray* GlobalObjects = nullptr;

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
	return GlobalObjects->ObjObjects.NumElements;
}

UEObject ObjectsStore::GetById(size_t id) const
{
	return GlobalObjects->ObjObjects.Objects[id].Object;
}
