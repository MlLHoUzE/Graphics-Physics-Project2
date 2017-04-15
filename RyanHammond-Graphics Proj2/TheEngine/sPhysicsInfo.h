#ifndef _sPhysicsInfo_HG_
#define _sPhysicsInfo_HG_

#include <glm\glm.hpp>
#include <glm\vec3.hpp> // glm::vec3
#include <glm\gtc\quaternion.hpp>

struct sPhysicsInfo {
	sPhysicsInfo() : bIsStatic(false) {}
	glm::vec3 position;
	glm::quat orientation;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	bool bIsStatic;
	glm::quat angularVelocity;
	float speed;
	float angularSpeed;
};

#endif