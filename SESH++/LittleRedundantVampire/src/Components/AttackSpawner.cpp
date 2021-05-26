#include "AttackSpawner.h"
#include "SpriteRenderer.h"
#include "../GameWorld.h"
#include "../Enum/ObjectTag.h"
#include <string>
#include "AnimationComponent.h"

using namespace sf;


void AttackSpawner::CreateAttack(TextureTag textureTag, ObjectTag objectTag)
{
	if (canAttack)
	{
		*gameObject->GetIsMovable() = false;

		GameObject* go = new GameObject();
		SpriteRenderer* sr;

		*go->GetPosition() = *gameObject->GetPosition();
		*go->GetDirection() = *gameObject->GetDirection();

		//TODO: Attack doesn't really work. You can hold down Space and keep the attack on. It also doesn't show the proper sprite image right now.
		int initialRow = 0;

		//Which animation row to go with based on the direction og the attack.
		switch (*go->GetDirection())
		{
		case 'L':
			initialRow = 0;
			break;
		case 'R':
			initialRow = 0;
			break;
		case 'U':
			initialRow = 1;
			break;
		case 'D':
			initialRow = 2;
			break;
		}

		sr = new SpriteRenderer(textureTag, Vector2u(1, (initialRow) + 1), Vector2u(1, 3));
		this->objectTag = objectTag;

		go->AddComponent(sr);

		AnimationComponent* aC = new AnimationComponent(sr, sr->GetImageCount(), 0.0f, initialRow);
		go->AddComponent(aC);

		SpriteRenderer& srRef = *sr;
		AnimationController* acController = new AnimationController(srRef, "2", "1", "2", "0", "0");
		go->AddComponent(acController);
		acController->AttachListenerToChangeAnimation(aC);

		go->AddComponent(new Attack(this->objectTag, attackCooldown));

		go->Awake();
		go->Start();

		GameWorld::GetInstance()->AddToGameObjects(go);

		attackTimer = 0.0f;
		canAttack = false;
	}
}

AttackSpawner::AttackSpawner(ObjectTag objectTag)
{
	this->objectTag = objectTag;

	attackCooldown = 250.0f;
	attackTimer = 0.0f;

	canAttack = true;
}

AttackSpawner::~AttackSpawner()
{

}

void AttackSpawner::Awake()
{
}

void AttackSpawner::Start()
{
}

void AttackSpawner::Update(Time* timePerFrame)
{
	attackTimer += timePerFrame->asMilliseconds();

	//Makes it so the caller can't attack constantly.
	if (attackTimer >= attackCooldown)
	{
		canAttack = true;
		*gameObject->GetIsMovable() = true;
	}
}

void AttackSpawner::Destroy()
{
	AttackSpawner::~AttackSpawner();
}

ComponentTag AttackSpawner::ToEnum()
{
	return ComponentTag::ATTACK_SPAWNER;
}
