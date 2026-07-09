#pragma once
#include "Engine/BaseObject.h"
#include "Engine/FBX.h"

class Tank : public BaseObject {
private:
	FBX* fbx_;
public:

	Tank();
	~Tank();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};

