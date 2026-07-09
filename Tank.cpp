#include "Tank.h"
#include "Ground.h"
#include "Engine/ObjectManager.h"
#include "Engine/LoggerManager.h"
#include "Engine/InputManager.h"

using namespace DirectX;

namespace {
	const XMVECTOR FOWARD_VECTOR = { 0.0f, 0.0f, 1.0f };
	const float SPEED = 0.1f;
}

Tank::Tank()
	: BaseObject("Tank") {
	fbx_ = nullptr;
}

Tank::~Tank() {
}

void Tank::Init() {
	fbx_ = new FBX("Asset/Tank.fbx");
	fbx_->Init();
}

void Tank::Update() {
	XMVECTOR postionVec = XMLoadFloat3(&postion_);
	XMVECTOR moveVec = XMVector3TransformCoord(FOWARD_VECTOR, XMMatrixRotationY(rotation_.y));

	if (InputManager::IsPushKey(DIK_W)) {
		postionVec = postionVec + SPEED * moveVec;
	}
	if (InputManager::IsPushKey(DIK_S)) {
		postionVec = postionVec - SPEED * moveVec;
	}
	if (InputManager::IsPushKey(DIK_A)) {
		rotation_.y -= XMConvertToRadians(1.0f);
	}
	if (InputManager::IsPushKey(DIK_D)) {
		rotation_.y += XMConvertToRadians(1.0f);
	}

	postion_ = { XMVectorGetX(postionVec), XMVectorGetY(postionVec), XMVectorGetZ(postionVec) };

	Ground* ground = (Ground*)ObjectManager::GetDrawObject<Ground>();
	if (ground != nullptr) {
		float distance = 0.0f;
		XMFLOAT3 rayDir = { 0.0f, -1.0f, 0.0f };
		if (FBX::Raycast(ground->GetFBX(), postion_, rayDir, distance)) {
			postion_.y = postion_.y + rayDir.y * distance;
		}
	}

	if (fbx_ != nullptr) {
		fbx_->SetPosition(postion_);
		fbx_->SetRotation(rotation_);
		fbx_->SetScale(scale_);
		fbx_->Update();
	}
}

void Tank::Draw() {
	if (fbx_ != nullptr) {
		fbx_->Draw();
	}
}

void Tank::Release() {
}
