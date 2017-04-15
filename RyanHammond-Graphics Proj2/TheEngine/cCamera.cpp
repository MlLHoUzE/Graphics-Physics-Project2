#include "cCamera.h"
#include "Globals.h"
#include "Input.h"
#include <glm\gtc\matrix_transform.hpp>

cCamera::cCamera()
{
	m_width = 1000;
	m_height = 1000;

	m_zoomSpeed = 20.f;
	m_distance = 40.f;
	m_minDistance = 5.f;
	m_maxDistance = 50.f;
	m_offset = glm::vec3(0.f, 10.f, -10.f);
	m_offset = glm::normalize(m_offset);

	m_panOffset = glm::vec3(0.1f, 0.0f, 0.0f);
	m_panOffset = glm::normalize(m_panOffset);
	m_panSpeed = 0.01f;
	m_panDistance = 0.f;
	m_panMax = 0.5f;
	m_panMin = -0.5f;
}
cCamera::~cCamera()
{

}

void cCamera::GetProjectionMatrix(glm::mat4& projOut)
{
	// set up the projection matrix
	projOut = glm::perspective(0.8f, (float)m_width / (float)m_height, 0.1f, 100000.f);

	
}
void cCamera::GetViewMatrix(glm::mat4& viewOut)
{
	viewOut = m_viewMatrix;
}

void cCamera::GetEyePosition(glm::vec4& eyeOut)
{
	eyeOut.x = m_viewMatrix[3].x;
	eyeOut.y = m_viewMatrix[3].y;
	eyeOut.z = m_viewMatrix[3].z;
	eyeOut.w = 1.f;
}

void cCamera::WindowResize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void cCamera::Update(float dt)
{

	glm::mat4 playerModelMat;
	g_pPlayer->GetWorldMatrix(playerModelMat);
	SetTargetTransform(playerModelMat);
	bool pressUp = nInput::IsKeyPressed::UP();
	bool pressDown = nInput::IsKeyPressed::DOWN();
	bool pressLeft = nInput::IsKeyPressed::LEFT();
	bool pressRight = nInput::IsKeyPressed::RIGHT();
	//bool pressUp = glfwGetKey(gWindow, GLFW_KEY_UP) == GLFW_PRESS;
	//bool pressDown = glfwGetKey(gWindow, GLFW_KEY_DOWN) == GLFW_PRESS;

	if (pressDown != pressUp)	//if pressing both do nothing, if pressing neither do nothing
	{
		float zoomSpeed = m_zoomSpeed;
		if (pressUp) zoomSpeed *= -1.f;
		m_distance += zoomSpeed * dt;
		if (m_distance < m_minDistance) m_distance = m_minDistance;
		if (m_distance > m_maxDistance) m_distance = m_maxDistance;
	}

	/*if (pressRight != pressLeft)
	{
		float panSpeed = mPanSpeed;
		if (pressRight) panSpeed *= -1.f;
		mPanDistance += panSpeed * dt;
		if (mPanDistance < mPanMin) mPanDistance = mPanMin;
		if (mPanDistance > mPanMax) mPanDistance = mPanMax;
	}*/

	if (pressRight)
	{
		//mPanDistance -= mPanSpeed;
		m_offset.x -= m_panSpeed;
		if (m_offset.x < m_panMin) m_offset.x = m_panMin;
	}
	if (pressLeft)
	{
		m_offset.x += m_panSpeed;
		if (m_offset.x > m_panMax) m_offset.x = m_panMax;
	}

	

	UpdateView();
}

void cCamera::UpdateView()
{
	glm::vec3 up(0.f, 1.f, 0.f);

	glm::vec4 eye4(m_targetTransform[3].x, m_targetTransform[3].y, m_targetTransform[3].z, 1.f);
	// set up the view matrix
	glm::vec3 target(m_targetTransform[3].x, m_targetTransform[3].y, m_targetTransform[3].z);
	glm::vec4 offset(m_offset.x, m_offset.y, m_offset.z, 0.f);
	offset = m_targetTransform * offset;
	offset = glm::normalize(offset) * m_distance;	//in case of scaling renormalize
	glm::vec3 eye(target.x + offset.x, target.y + offset.y, target.z + offset.z);
	m_viewMatrix = glm::lookAtRH(eye, target, up);
}
void cCamera::SetTargetTransform(glm::mat4& targetTransform)
{
	m_targetTransform = targetTransform;
}

void cCamera::SetOffset(glm::vec3 offset)
{
	m_offset = offset;
}