#include "AttackSpawner.h"
#include "SpriteRenderer.h"
#include "../GameWorld.h"
#include "../Enum/ObjectTag.h"
#include <string>

using namespace sf;


void AttackSpawner::CreateAttack()
{
	if (*canAttack)
	{
		//TODO: tjek hvis den ryger ud af scope.
		GameObject* go = new GameObject();
		SpriteRenderer* sr = new SpriteRenderer(TextureTag::ATTACK_SHEET);
		//sr->SetSprite(TextureTag::ATTACK_SHEET);
		go->AddComponent(sr);
		go->AddComponent(new Attack(*objectTag, *gameObject->GetPosition(), *gameObject->GetDirection(), *attackCooldown));

		go->Awake();
		go->Start();

		(*GameWorld::GetInstance()->GetGameObjects()).push_back(go);

		*attackTimer = 0.0f;
		*canAttack = false;
	}
}


AttackSpawner::AttackSpawner(ObjectTag objectTag)
{
	this->objectTag = new ObjectTag();
	*this->objectTag = objectTag;

	attackCooldown = new float;
	attackTimer = new float;

	canAttack = new bool;
}

AttackSpawner::~AttackSpawner()
{
	delete objectTag;
	objectTag = nullptr;

	delete attackCooldown;
	attackCooldown = nullptr;

	delete attackTimer;
	attackTimer = nullptr;

	delete canAttack;
	canAttack = nullptr;
}


void AttackSpawner::Awake()
{
	*attackCooldown = 500.0f;
	*attackTimer = 0.0f;

	*canAttack = true;
}

void AttackSpawner::Start()
{
}

void AttackSpawner::Update(Time* timePerFrame)
{
	*attackTimer += timePerFrame->asMilliseconds();

	if (*attackTimer >= *attackCooldown)
	{
		*canAttack = true;
	}
}

void AttackSpawner::Destroy()
{
}

ComponentTag AttackSpawner::ToEnum()
{
	return ComponentTag::ATTACKSPAWNER;
}
