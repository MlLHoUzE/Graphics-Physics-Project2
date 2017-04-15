#include "cPlayer.h"
#include "Input.h"
#include "Render.h"


cPlayer* cPlayer::m_pTheOnePlayer = 0;

cPlayer::cPlayer()
{
	this->m_physicsInfo.speed = 5.f;
	this->m_physicsInfo.angularSpeed = 5.f;
}

cPlayer* cPlayer::getInstance(void)
{
	if (cPlayer::m_pTheOnePlayer == 0)
	{
		cPlayer::m_pTheOnePlayer = new cPlayer();
	}
	return cPlayer::m_pTheOnePlayer;
}

void cPlayer::shutDown(void)
{
	if (cPlayer::m_pTheOnePlayer != 0)
	{
		delete cPlayer::m_pTheOnePlayer;
	}
	return;
}

void cPlayer::GetNextPosition(glm::vec3& position, float distance)
{
	position = m_physicsInfo.position + m_physicsInfo.velocity * distance;
}

void cPlayer::SetPhysicsInfo(sPhysicsInfo physicsInfo)
{
	m_physicsInfo = physicsInfo;
}

void cPlayer::SetRenderingInfo(sRenderingInfo renderingInfo)
{
	m_renderingInfo = renderingInfo;
}

void cPlayer::GetPhysicsInfo(sPhysicsInfo& physicsInfo)
{
	physicsInfo = m_physicsInfo;
}
void cPlayer::GetRenderingInfo(sRenderingInfo& renderingInfo)
{
	renderingInfo = m_renderingInfo;
}

void cPlayer::Update(float dt)
{
	
	bool pressW = nInput::IsKeyPressed::W();
	bool pressS = nInput::IsKeyPressed::S();
	bool pressA = nInput::IsKeyPressed::A();
	bool pressD = nInput::IsKeyPressed::D();
	bool pressQ = nInput::IsKeyPressed::Q();
	bool pressE = nInput::IsKeyPressed::E();

	
	//camera controls:
	//up/down = zoom in/zoom out
	//left/right = pan left/pan right
	glm::vec3 up(0.f, 1.f, 0.f);
	glm::vec3 forward(0.f, 0.f, 1.f);
	forward = m_physicsInfo.orientation * forward;
	float linearSpeed = m_physicsInfo.speed;
	float angularSpeed = m_physicsInfo.angularSpeed;
	//movement controls:
	// w/s = forward / backward
	if (pressW != pressS)
	{
		linearSpeed = pressW ? m_physicsInfo.speed : -m_physicsInfo.speed;

		//m_transform = glm::translate(m_transform, glm::vec3(0.0f, 0.0f, linearSpeed * dt));
		//SetPosition(glm::vec3(linearSpeed, 0.f, 0.f));
		m_physicsInfo.velocity = forward * linearSpeed;
	}
	
	/*if (physicsInfo.position.x < gAreaInfo->Min.x)
	{
		physicsInfo.position.x = gAreaInfo->Max.x;
	}
	else if (physicsInfo.position.x > gAreaInfo->Max.x)
	{
		physicsInfo.position.x = gAreaInfo->Min.x;
	}

	if (physicsInfo.position.z < gAreaInfo->Min.z)
	{
		physicsInfo.position.z = gAreaInfo->Max.z;
	}
	else if (physicsInfo.position.z > gAreaInfo->Max.z)
	{
		physicsInfo.position.z = gAreaInfo->Min.z;
	}*/

	if (pressA != pressD)
	{
		if (pressD) angularSpeed *= -1.f;
		m_physicsInfo.orientation = glm::rotate(m_physicsInfo.orientation, angularSpeed * dt, up);
		//m_transform = glm::rotate(m_transform, angularSpeed*dt, glm::vec3(0.f, 1.f, 0.f));
	}

	if (pressQ != pressE)
	{
		linearSpeed = pressQ ? m_physicsInfo.speed : -m_physicsInfo.speed;
		//m_transform = glm::rotate(m_transform, angularSpeed*dt, glm::vec3(0.f, 1.f, 0.f));
		m_physicsInfo.velocity = up * linearSpeed;
	}
	


	m_physicsInfo.position = m_physicsInfo.position + (m_physicsInfo.velocity * dt);

}

void cPlayer::render()
{
	if (!this->getParent())
	{
		DrawObject(this, m_renderingInfo.modelMatrix);
	}
	else
	{
		glm::mat4 parentModelMat;
		this->m_parent->GetWorldMatrix(parentModelMat);
		DrawObject(this, parentModelMat);
	}
}

void cPlayer::SetWorldMatrix(glm::mat4 matModel)
{
	this->m_worldMatrix = matModel;
}

void cPlayer::GetWorldMatrix(glm::mat4& matModel)
{
	matModel = this->m_worldMatrix;
}

void cPlayer::PreRender()
{
	if (m_physicsInfo.bIsStatic) return;
	m_renderingInfo.modelMatrix = glm::mat4_cast(m_physicsInfo.orientation);
	m_renderingInfo.modelMatrix[3] = glm::vec4(m_physicsInfo.position, 1.f);
}

void cPlayer::setWireframe(bool bWireframe)
{
	this->m_renderingInfo.bIsWireframe = bWireframe;
}

void cPlayer::setUseLighting(bool bUseLighting)
{
	this->m_renderingInfo.bUseDebugColors = bUseLighting;
}