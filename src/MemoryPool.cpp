#pragma once
#include "GameObject.h"
class MemoryPool {
private:
	// Make array pool of fixed size (10 objects)
	// Now when we need a new pig we don't need any vector resizing
	GameObject* pool[10];
}