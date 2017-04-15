#ifndef _cCamera_HG_
#define _cCamera_HG_

//#include "externals.h"
#include <glm\vec4.hpp>
#include <glm\mat4x4.hpp>
#include <glm\vec3.hpp>
#include "cSceneNode.h"
//class iCamera
//{
//public:
//	virtual ~iCamera() {}
//	virtual void GetProjectionMatrix(glm::mat4& projOut) = 0;
//	virtual void GetViewMatrix(glm::mat4& viewOut) = 0;
//	virtual void GetEyePosition(glm::vec4& eyeOut) = 0;
//};

class cCamera : public cSceneNode
{
public:
	cCamera();
	~cCamera();

	void GetProjectionMatrix(glm::mat4& projOut);
	void GetViewMatrix(glm::mat4& viewOut);
	void GetEyePosition(glm::vec4& eyeOut);
	void WindowResize(int width, int height);

	void Update(float dt);
	void SetTargetTransform(glm::mat4& targetTransform);
	void SetOffset(glm::vec3 offset);

	
private:
	void UpdateView();
	int m_width;
	int m_height;
	glm::mat4 m_targetTransform;
	glm::vec3 m_offset;
	
	float m_zoomSpeed;
	float m_distance;
	float m_maxDistance;
	float m_minDistance;
	glm::mat4 m_viewMatrix;

	glm::vec3 m_panOffset;
	float m_panSpeed;
	float m_panDistance;
	float m_panMax;
	float m_panMin;

	

};

#endif