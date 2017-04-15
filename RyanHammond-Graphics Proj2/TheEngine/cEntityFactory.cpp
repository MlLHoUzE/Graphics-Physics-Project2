#include "cEntityFactory.h"

//include the types of entities here
#include "cEntity.h"

iEntity* cEntityFactory::CreateEntity(std::string typeOfEntity)
{
	iEntity* pEntityToReturn = 0;

	if (typeOfEntity == "Enemy")
	{
		pEntityToReturn = new cEntity();
	}
	else if (typeOfEntity == "Ground")
	{
		pEntityToReturn = new cEntity();
		sPhysicsInfo physicsInfo;
		physicsInfo.bIsStatic = true;
		pEntityToReturn->SetPhysicsInfo(physicsInfo);
	}

	return pEntityToReturn;
}