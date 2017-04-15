#include "Globals.h"

cShaderManager* g_pShaderManager = 0;
cMeshTypeManager* g_pMeshManager = 0;
cBasicTextureManager* g_pTextureManager = 0;
cSceneGraph* g_pSceneGraph = 0;

cPlayer* g_pPlayer = 0;
cCamera* g_pCamera = 0;

GLFWwindow* g_window = 0;

glm::vec3 lightPos(9.f, 15.f, 16.f);		// I just picked these values after moving the light around until it looked "nice"
float lightConstAtten = 0.0f;
float lightLinearAtten = 0.001;
float lightQuadAtten = 0.00111786f;
glm::vec3 lightDiffuse(1.f, 0.8f, 0.f);

glm::vec3 lightPos2(5.f, 15.f, 16.f);		// I just picked these values after moving the light around until it looked "nice"

glm::vec3 lightPos3(9.f, 15.f, -16.f);		// I just picked these values after moving the light around until it looked "nice"
glm::vec3 lightDiffuse2(0.13f, 0.54f, 0.13f);

glm::vec3 lightPos4(5.f, 15.f, -16.f);		// I just picked these values after moving the light around until it looked "nice"

glm::vec3 lightPos5(-9.f, 15.f, -16.f);		// I just picked these values after moving the light around until it looked "nice"
glm::vec3 lightDiffuse3(0.12f, 0.56f, 1.f);

glm::vec3 lightPos6(-9.f, 15.f, -16.f);		// I just picked these values after moving the light around until it looked "nice"

glm::vec3 lightPos7(-9.f, 15.f, 16.f);		// I just picked these values after moving the light around until it looked "nice"
glm::vec3 lightDiffuse4(0.70f, 0.13f, 0.13f);

glm::vec3 lightPos8(-9.f, 15.f, 16.f);		// I just picked these values after moving the light around until it looked "nice"
glm::vec3 lightPos9(0.f, 50.f, 0.f);		// I just picked these values after moving the light around until it looked "nice"
float lightConstAtten9 = 0.0f;
float lightLinearAtten9 = 0.001;
float lightQuadAtten9 = 0.000111786f;


bool bDrawLightDebugSpheres = false;
bool bDrawLightDebugLocation = true;

GLint locID_matModel = -1;		// 
GLint locID_matView = -1;
GLint locID_matProj = -1;

GLint UniformLoc_ID_objectColour = -1;
GLint UniformLoc_ID_isWireframe = -1;
GLint UniformLoc_ID_bUseDebugDiffuseNoLighting = -1;

GLint UniformLoc_alpha = -1;

GLint UniformLoc_texSamp2D_00 = -1;
GLint UniformLoc_texSamp2D_01 = -1;
GLint UniformLoc_texSamp2D_02 = -1;
GLint UniformLoc_texSamp2D_03 = -1;

GLint UniformLoc_bUseTextureAsDiffuse = -1;
GLint UniformLoc_bUseLighting = -1;

GLint UniformLoc_bIsImposterBlackIsAlpha = -1;
GLint UniformLoc_bUseAlphaMask = -1;