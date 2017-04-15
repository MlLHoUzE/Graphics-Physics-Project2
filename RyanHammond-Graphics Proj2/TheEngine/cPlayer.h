#ifndef _cPlayer_HG_
#define _cPlayer_HG_

#include <glm\vec3.hpp>
#include "sPhysicsInfo.h"
#include "sRenderingInfo.h"
#include "cSceneNode.h"

class cPlayer : public cSceneNode
{
public:

	virtual ~cPlayer() {}
	static cPlayer* getInstance(void);
	static void shutDown(void);


	virtual void GetNextPosition(glm::vec3& position, float distance);
	virtual void SetPhysicsInfo(sPhysicsInfo physicsInfo);
	virtual void SetRenderingInfo(sRenderingInfo renderingInfo);
	virtual void GetPhysicsInfo(sPhysicsInfo& physicsInfo);
	virtual void GetRenderingInfo(sRenderingInfo& renderingInfo);

	virtual void SetWorldMatrix(glm::mat4 matModel);
	virtual void GetWorldMatrix(glm::mat4& matModel);
	virtual void Update(float dt);

	virtual void PreRender();

	void setWireframe(bool bWireframe);
	void setUseLighting(bool bUseLighting);

	void render();


	
private:
	cPlayer();
	sPhysicsInfo m_physicsInfo;
	sRenderingInfo m_renderingInfo;
	static cPlayer* m_pTheOnePlayer;
	glm::mat4 m_worldMatrix;
};

#endif