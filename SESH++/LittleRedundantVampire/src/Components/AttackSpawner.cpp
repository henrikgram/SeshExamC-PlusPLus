#include "AttackSpawner.h"
#include "SpriteRenderer.h"
#include "../GameWorld.h"
#include "../Enum/ObjectTag.h"
#include <string>

using namespace sf;


void AttackSpawner::CreateAttack(string direction)
{
	if (canAttack)
	{
		cout << "\n" << "Attack started" << "\n";

		//TODO: tjek hvis den ryger ud af scope.
		GameObject* go = new GameObject();
		SpriteRenderer* sr = new SpriteRenderer();

		sr->SetSprite(TextureTag::ATTACK_SHEET);
		go->position = new Vector2<float>(100, 100);
		go->AddComponent(sr);
		go->AddComponent(new Attack(objectTag, Vector2f((*gameObject->position).x, (*gameObject->position).y), direction, *attackLength));

		go->Awake();
		go->Start();

		(*GameWorld::GetInstance()->GetGameObjects()).push_back(go);
	}
}


AttackSpawner::AttackSpawner(ObjectTag objectTag)
{
	this->objectTag = new ObjectTag();
	*this->objectTag = objectTag;

	attackLength = new float;
	attackTimer = new float;

	canAttack = new bool;
}

AttackSpawner::~AttackSpawner()
{
	delete objectTag;
	objectTag = nullptr;

	delete attackLength;
	attackLength = nullptr;

	delete attackTimer;
	attackTimer = nullptr;

	delete canAttack;
	canAttack = nullptr;
}


void AttackSpawner::Awake()
{
	*attackLength = 2500.0f;
	*attackTimer = 0.0f;

	*canAttack = true;
}

void AttackSpawner::Start()
{
}

void AttackSpawner::Update(Time* timePerFrame)
{
	*attackTimer += timePerFrame->asMilliseconds();

	if (attackTimer >= attackLength)
	{
		*canAttack = true;
		*attackTimer = 0.0f;
	}
	else
	{
		*canAttack = false;
	}
}

void AttackSpawner::Destroy()
{
}

ComponentTag AttackSpawner::ToEnum()
{
	return ComponentTag::ATTACKSPAWNER;
}
