#include "AttackFactory.h"
#include "SpriteRenderer.h"
#include "../Global.h"
#include "../Enum/ObjectTag.h"
#include <string>

using namespace sf;


void AttackFactory::CreateAttack(ObjectTag tag, Vector2f callerPosition, string direction)
{
	//TODO: tjek hvis den ryger ud af scope.
	GameObject* go = new GameObject();
	SpriteRenderer* sr = new SpriteRenderer();

	sr->SetSprite(TextureTag::ATTACK_SHEET);
	go->position = new Vector2<float>(100, 100);
	go->AddComponent(sr);
	//go->AddComponent(new Attack(tag, callerPosition, direction));

	go->Awake();
	go->Start();

	(*Global::GetInstance()->GetGameObjects()).push_back(go);
}

AttackFactory::AttackFactory()
{
}

AttackFactory::~AttackFactory()
{
}
