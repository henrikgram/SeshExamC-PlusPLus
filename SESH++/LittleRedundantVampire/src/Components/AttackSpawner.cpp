#include "AttackSpawner.h"
#include "SpriteRenderer.h"
#include "../GameWorld.h"
#include "../Enum/ObjectTag.h"
#include <string>
#include "AnimationComponent.h"

using namespace sf;


void AttackSpawner::CreateAttack()
{
	if (canAttack)
	{
		//TODO: tjek hvis den ryger ud af scope.
		GameObject* go = new GameObject();
		SpriteRenderer* sr = new SpriteRenderer();

		sr->isSpriteSheet = true;
		sr->currentImage = new Vector2u(1, 1);
		sr->imageCount = new Vector2u(2, 3);

		sr->SetSprite(TextureTag::PLAYER_ATTACK_SHEET);
		go->AddComponent(sr);

		go->AddComponent(new Attack(objectTag, *gameObject->GetPosition(), *gameObject->GetDirection(), attackCooldown));

		AnimationComponent* aC = new AnimationComponent(sr, *sr->imageCount, 200.0f, (*sr->currentImage).x);
		go->AddComponent(aC);

		SpriteRenderer& srRef = *sr;
		AnimationController* acController = new AnimationController(srRef, "3", "2", "3", "1", "1");
		go->AddComponent(acController);
		acController->ChangeAnimation.Attach(aC);
		
		go->Awake();
		go->Start();

		(*GameWorld::GetInstance()->GetGameObjects()).push_back(go);

		attackTimer = 0.0f;
		canAttack = false;
	}
}


AttackSpawner::AttackSpawner(ObjectTag objectTag)
{
	this->objectTag = objectTag;
}

AttackSpawner::~AttackSpawner()
{

}


void AttackSpawner::Awake()
{
	attackCooldown = 500.0f;
	attackTimer = 0.0f;

	canAttack = true;
}

void AttackSpawner::Start()
{
}

void AttackSpawner::Update(Time* timePerFrame)
{
	attackTimer += timePerFrame->asMilliseconds();

	if (attackTimer >= attackCooldown)
	{
		canAttack = true;
	}
}

void AttackSpawner::Destroy()
{
}

ComponentTag AttackSpawner::ToEnum()
{
	return ComponentTag::ATTACK_SPAWNER;
}
