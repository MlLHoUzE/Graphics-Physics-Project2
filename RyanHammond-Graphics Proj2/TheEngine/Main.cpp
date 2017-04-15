#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include "Globals.h"
//GLM STUFF
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "cShaderManager.h"


#include "cPlayer.h"
#include "cMediator.h"

#include "JsonHelp.h"


#include "sEntityDesc.h"

#include "Input.h"

//#include "global.h"

//#include "LoadMesh.h"
//#include "LoadTexture.h"
//#include "Update.h"
//#include "iMediator.h"
//#include "cMediator.h"
//#include "JsonHelp.h"

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main(void)
{
	//GLFWwindow* g_window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	g_window = glfwCreateWindow(1200, 800, "The Engine", NULL, NULL);
	if (!g_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	std::string jsonFileName = "Scene.json";
	Json::Value json;
	std::string errs;

	if (!JsonHelp::Load(jsonFileName, json, errs))
	{
		std::cout << "couldn't load JSON file." << std::endl;
		std::cout << errs << std::endl;
	}

	glfwMakeContextCurrent(g_window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	::g_pShaderManager = new cShaderManager();

	cShaderManager::cShader verShader;
	cShaderManager::cShader fragShader;

	verShader.fileName = "phongVert.glsl";
	fragShader.fileName = "phongFrag.glsl";
	::g_pShaderManager->setBasePath("assets//shaders//");
	if (!::g_pShaderManager->createProgramFromFile("phong", verShader, fragShader))
	{
		std::cout << ::g_pShaderManager->getLastError() << std::endl;
		std::cout.flush();

		return -1;
	}
	GLuint shaderProgramID = ::g_pShaderManager->getIDFromFriendlyName("phong");

	::g_pMeshManager = new cMeshTypeManager();
	::g_pMeshManager->SetBaseFilePath("assets//models//");
	::g_pMeshManager->ScaleEverythingToBoundingBoxOnLoad(true, 1.0f);

	//TODO: Load files here
	//::g_pMeshManager->LoadPlyFileIntoGLBuffer
	//done in mediator
	::g_pTextureManager = new cBasicTextureManager();
	::g_pTextureManager->SetBasePath("Assets//textures//");
	//TODO: Load Textures
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("bear_texture.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("deer_texture.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("boar_texture.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("grass_texture.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("dirt_texture.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("brick_texture.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("FenceActual.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("FenceAlphaMask.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("metal.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("gold.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("rusty.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("graffiti.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	//create the SceneGraph
	g_pSceneGraph = cSceneGraph::getInstance();

	g_pPlayer = cPlayer::getInstance();
	/*g_pMeshManager->LoadPlyFileIntoGLBuffer(shaderProgramID, "Utah_Teapot.ply");
	sRenderingInfo renderingInfo;
	renderingInfo.meshName = "Utah_Teapot.ply";
	renderingInfo.texture00Name = "brickTexture_square_1024pixels.bmp";
	renderingInfo.bIsImposter = false;
	renderingInfo.bIsVisible = true;
	renderingInfo.bIsWireframe = false;
	renderingInfo.bUseDebugColors = false;
	renderingInfo.color = (glm::vec4(1.f, 1.f, 1.f, 1.f));
	renderingInfo.scale = 7.f;
	g_pPlayer->SetRenderingInfo(renderingInfo);*/
	if (!JsonHelp::Set(json["Player"], *g_pPlayer))
	{
		std::cout << "Couldn't Load the Player" << std::endl;
	}

	{
		unsigned int testVAO;
		int testNumIndices;
		float testUnitScale;
		sRenderingInfo renderingInfo;
		g_pPlayer->GetRenderingInfo(renderingInfo);
		if (!g_pMeshManager->LookUpMeshInfo(renderingInfo.meshName, testVAO, testNumIndices, testUnitScale))//check if this mesh has already been loaded
		{
			//if it hasn't been loaded
			g_pMeshManager->LoadPlyFileIntoGLBuffer(shaderProgramID, renderingInfo.meshName);
		}
	}
	g_pSceneGraph->addSceneNode(g_pPlayer);

	//create camera
	g_pCamera = new cCamera();
	if (!JsonHelp::Set(json["Camera"], *g_pCamera))
	{
		std::cout << "Couldn't load the camera" << std::endl;
	}
	//g_pCamera->SetOffset(glm::vec3(0.f, 15.f, -15.f));
	g_pSceneGraph->addSceneNode(g_pCamera);

	cMediator* pMediator = new cMediator();

	sEntityDesc entityDesc;
	if (!JsonHelp::Set(json["Entity"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}
	
	pMediator->createEntity(&entityDesc);
	if (!JsonHelp::Set(json["Entity2"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);

	if (!JsonHelp::Set(json["Entity3"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);

	if (!JsonHelp::Set(json["Entity4"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);

	if (!JsonHelp::Set(json["Entity5"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);

	if (!JsonHelp::Set(json["Entity6"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);

	if (!JsonHelp::Set(json["Entity7"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);

	if (!JsonHelp::Set(json["Entity8"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);
	if (!JsonHelp::Set(json["Entity9"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);
	if (!JsonHelp::Set(json["Entity10"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);
	if (!JsonHelp::Set(json["Entity11"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);

	//ground
	/*for (int i = -5; i < 5; i++)
	{
		for (int j = -5; j < 5; j++)
		{
			sEntityDesc groundDesc;
			groundDesc.meshName = "cube.ply";
			groundDesc.texture00Name = "dirt_texture.bmp";
			groundDesc.position = glm::vec3(j*10, -5.f, i*10);
			groundDesc.scale = 10;
			groundDesc.typeOfEntity = "Ground";
			groundDesc.color = glm::vec4(1.f, 1.f, 0.f, 1.f);

			pMediator->createEntity(&groundDesc);
		}
	}*/
	sEntityDesc groundDesc;
	groundDesc.meshName = "cube.ply";
	groundDesc.texture00Name = "dirt_texture.bmp";
	groundDesc.position = glm::vec3(0.f, -50.f, 0.f);
	groundDesc.scale = 100;
	groundDesc.typeOfEntity = "Ground";
	groundDesc.color = glm::vec4(0.f, 0.f, 0.f, 1.f);

	pMediator->createEntity(&groundDesc);


	GLint locID_lightPosition = -1;
	GLint locID_lightDiffuse = -1;
	GLint locID_lightAttenuation = -1;

	GLint locID_lightPosition2 = -1;
	GLint locID_lightDiffuse2 = -1;
	GLint locID_lightAttenuation2 = -1;

	GLint locID_lightPosition3 = -1;
	GLint locID_lightDiffuse3 = -1;
	GLint locID_lightAttenuation3 = -1;

	GLint locID_lightPosition4 = -1;
	GLint locID_lightDiffuse4 = -1;
	GLint locID_lightAttenuation4 = -1;

	GLint locID_lightPosition5 = -1;
	GLint locID_lightDiffuse5 = -1;
	GLint locID_lightAttenuation5 = -1;

	GLint locID_lightPosition6 = -1;
	GLint locID_lightDiffuse6 = -1;
	GLint locID_lightAttenuation6 = -1;

	GLint locID_lightPosition7 = -1;
	GLint locID_lightDiffuse7 = -1;
	GLint locID_lightAttenuation7 = -1;

	GLint locID_lightPosition8 = -1;
	GLint locID_lightDiffuse8 = -1;
	GLint locID_lightAttenuation8 = -1;

	GLint locID_lightPosition9 = -1;
	GLint locID_lightDiffuse9 = -1;
	GLint locID_lightAttenuation9 = -1;

	locID_matModel = glGetUniformLocation(shaderProgramID, "matModel");
	locID_matView = glGetUniformLocation(shaderProgramID, "matView");
	locID_matProj = glGetUniformLocation(shaderProgramID, "matProj");

	locID_lightPosition = glGetUniformLocation(shaderProgramID, "theLights[0].position");
	locID_lightDiffuse = glGetUniformLocation(shaderProgramID, "theLights[0].diffuse");
	locID_lightAttenuation = glGetUniformLocation(shaderProgramID, "theLights[0].attenuation");

	locID_lightPosition2 = glGetUniformLocation(shaderProgramID, "theLights[1].position");
	locID_lightDiffuse2 = glGetUniformLocation(shaderProgramID, "theLights[1].diffuse");
	locID_lightAttenuation2 = glGetUniformLocation(shaderProgramID, "theLights[1].attenuation");

	locID_lightPosition3 = glGetUniformLocation(shaderProgramID, "theLights[2].position");
	locID_lightDiffuse3 = glGetUniformLocation(shaderProgramID, "theLights[2].diffuse");
	locID_lightAttenuation3 = glGetUniformLocation(shaderProgramID, "theLights[2].attenuation");

	locID_lightPosition4 = glGetUniformLocation(shaderProgramID, "theLights[3].position");
	locID_lightDiffuse4 = glGetUniformLocation(shaderProgramID, "theLights[3].diffuse");
	locID_lightAttenuation4 = glGetUniformLocation(shaderProgramID, "theLights[3].attenuation");

	locID_lightPosition5 = glGetUniformLocation(shaderProgramID, "theLights[4].position");
	locID_lightDiffuse5 = glGetUniformLocation(shaderProgramID, "theLights[4].diffuse");
	locID_lightAttenuation5 = glGetUniformLocation(shaderProgramID, "theLights[4].attenuation");

	locID_lightPosition6 = glGetUniformLocation(shaderProgramID, "theLights[5].position");
	locID_lightDiffuse6 = glGetUniformLocation(shaderProgramID, "theLights[5].diffuse");
	locID_lightAttenuation6 = glGetUniformLocation(shaderProgramID, "theLights[5].attenuation");

	locID_lightPosition7 = glGetUniformLocation(shaderProgramID, "theLights[6].position");
	locID_lightDiffuse7 = glGetUniformLocation(shaderProgramID, "theLights[6].diffuse");
	locID_lightAttenuation7 = glGetUniformLocation(shaderProgramID, "theLights[6].attenuation");

	locID_lightPosition8 = glGetUniformLocation(shaderProgramID, "theLights[7].position");
	locID_lightDiffuse8 = glGetUniformLocation(shaderProgramID, "theLights[7].diffuse");
	locID_lightAttenuation8 = glGetUniformLocation(shaderProgramID, "theLights[7].attenuation");

	locID_lightPosition9 = glGetUniformLocation(shaderProgramID, "theLights[8].position");
	locID_lightDiffuse9 = glGetUniformLocation(shaderProgramID, "theLights[8].diffuse");
	locID_lightAttenuation9 = glGetUniformLocation(shaderProgramID, "theLights[8].attenuation");

	UniformLoc_ID_objectColour = glGetUniformLocation(shaderProgramID, "objectColour");
	UniformLoc_ID_isWireframe = glGetUniformLocation(shaderProgramID, "isWireframe");
	UniformLoc_ID_bUseDebugDiffuseNoLighting = glGetUniformLocation(shaderProgramID, "bUseDebugDiffuseNoLighting");


	UniformLoc_alpha = glGetUniformLocation(shaderProgramID, "alpha");

	UniformLoc_texSamp2D_00 = glGetUniformLocation(shaderProgramID, "texSamp2D_00");
	UniformLoc_texSamp2D_01 = glGetUniformLocation(shaderProgramID, "texSamp2D_01");
	UniformLoc_texSamp2D_02 = glGetUniformLocation(shaderProgramID, "texSamp2D_02");
	UniformLoc_texSamp2D_03 = glGetUniformLocation(shaderProgramID, "texSamp2D_03");

	UniformLoc_bUseTextureAsDiffuse = glGetUniformLocation(shaderProgramID, "bUseTextureAsDiffuse");
	UniformLoc_bUseLighting = glGetUniformLocation(shaderProgramID, "bUseLighting");

	UniformLoc_bIsImposterBlackIsAlpha = glGetUniformLocation(shaderProgramID, "bIsImposterBlackIsAlpha");
	UniformLoc_bUseAlphaMask = glGetUniformLocation(shaderProgramID, "bUseAlphaMask");

	glEnable(GL_DEPTH_TEST);
	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(g_window))
	{
		float ratio;
		int width, height;
		glm::mat4 matProjection;

		glfwGetFramebufferSize(g_window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 matView(1.0f);

		g_pCamera->GetProjectionMatrix(matProjection);
		//matProjection = glm::perspective(0.6f, ratio, 0.01f, 10000.0f);
		g_pCamera->GetViewMatrix(matView);

		glm::vec4 eye;
		g_pCamera->GetEyePosition(eye);
		//pass this to shader?

		static const float MAXDELTATIME = 0.1f;
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();
		if (deltaTime > MAXDELTATIME)
		{
			deltaTime = MAXDELTATIME;
		}

		//update everything in the scene graph
		g_pSceneGraph->updateObjects(g_pSceneGraph->getRoot(), deltaTime);

		bool pressF = nInput::IsKeyPressed::F();
		bool pressG = nInput::IsKeyPressed::G();
		bool pressC = nInput::IsKeyPressed::C();
		bool pressV = nInput::IsKeyPressed::V();
		if (pressF)
		{
			g_pSceneGraph->setWireframe(true, g_pSceneGraph->getRoot());
		}
		if (pressG)
		{
			g_pSceneGraph->setWireframe(false, g_pSceneGraph->getRoot());
		}
		if (pressC)
		{
			g_pSceneGraph->setUseLighting(true, g_pSceneGraph->getRoot());
		}
		if (pressV)
		{
			g_pSceneGraph->setUseLighting(false, g_pSceneGraph->getRoot());
		}

		//physics step

		//collision step

		glUniformMatrix4fv(locID_matProj, 1, GL_FALSE,
			(const GLfloat*)glm::value_ptr(matProjection));

		// This is set once at the start of the "scene" draw.
		glUniformMatrix4fv(locID_matView, 1, GL_FALSE,
			(const GLfloat*)glm::value_ptr(matView));

		glUniform4f(locID_lightPosition, lightPos.x, lightPos.y, lightPos.z, 1.0f);
		//glUniform4f(locID_lightDiffuse, 1.0, 1.0f, 1.0f, 1.0f);
		glUniform4f(locID_lightDiffuse, lightDiffuse.x, lightDiffuse.y, lightDiffuse.z, 1.0f);
		glUniform4f(locID_lightAttenuation, ::lightConstAtten, ::lightLinearAtten, ::lightQuadAtten, 1.0f);

		glUniform4f(locID_lightPosition2, lightPos2.x, lightPos2.y, lightPos2.z, 1.0f);
		glUniform4f(locID_lightDiffuse2, lightDiffuse.x, lightDiffuse.y, lightDiffuse.z, 1.0f);
		glUniform4f(locID_lightAttenuation2, ::lightConstAtten, ::lightLinearAtten, ::lightQuadAtten, 1.0f);

		glUniform4f(locID_lightPosition3, lightPos3.x, lightPos3.y, lightPos3.z, 1.0f);
		//glUniform4f(locID_lightDiffuse, 1.0, 1.0f, 1.0f, 1.0f);
		glUniform4f(locID_lightDiffuse3, lightDiffuse2.x, lightDiffuse2.y, lightDiffuse2.z, 1.0f);
		glUniform4f(locID_lightAttenuation3, ::lightConstAtten, ::lightLinearAtten, ::lightQuadAtten, 1.0f);

		glUniform4f(locID_lightPosition4, lightPos4.x, lightPos4.y, lightPos4.z, 1.0f);
		//glUniform4f(locID_lightDiffuse, 1.0, 1.0f, 1.0f, 1.0f);
		glUniform4f(locID_lightDiffuse4, lightDiffuse2.x, lightDiffuse2.y, lightDiffuse2.z, 1.0f);
		glUniform4f(locID_lightAttenuation4, ::lightConstAtten, ::lightLinearAtten, ::lightQuadAtten, 1.0f);

		glUniform4f(locID_lightPosition5, lightPos5.x, lightPos5.y, lightPos5.z, 1.0f);
		//glUniform4f(locID_lightDiffuse, 1.0, 1.0f, 1.0f, 1.0f);
		glUniform4f(locID_lightDiffuse5, lightDiffuse3.x, lightDiffuse3.y, lightDiffuse3.z, 1.0f);
		glUniform4f(locID_lightAttenuation5, ::lightConstAtten, ::lightLinearAtten, ::lightQuadAtten, 1.0f);

		glUniform4f(locID_lightPosition6, lightPos6.x, lightPos6.y, lightPos6.z, 1.0f);
		//glUniform4f(locID_lightDiffuse, 1.0, 1.0f, 1.0f, 1.0f);
		glUniform4f(locID_lightDiffuse6, lightDiffuse3.x, lightDiffuse3.y, lightDiffuse3.z, 1.0f);
		glUniform4f(locID_lightAttenuation6, ::lightConstAtten, ::lightLinearAtten, ::lightQuadAtten, 1.0f);

		glUniform4f(locID_lightPosition7, lightPos7.x, lightPos7.y, lightPos7.z, 1.0f);
		//glUniform4f(locID_lightDiffuse, 1.0, 1.0f, 1.0f, 1.0f);
		glUniform4f(locID_lightDiffuse7, lightDiffuse4.x, lightDiffuse4.y, lightDiffuse4.z, 1.0f);
		glUniform4f(locID_lightAttenuation7, ::lightConstAtten, ::lightLinearAtten, ::lightQuadAtten, 1.0f);

		glUniform4f(locID_lightPosition8, lightPos8.x, lightPos8.y, lightPos8.z, 1.0f);
		//glUniform4f(locID_lightDiffuse, 1.0, 1.0f, 1.0f, 1.0f);
		glUniform4f(locID_lightDiffuse8, lightDiffuse4.x, lightDiffuse4.y, lightDiffuse4.z, 1.0f);
		glUniform4f(locID_lightAttenuation8, ::lightConstAtten, ::lightLinearAtten, ::lightQuadAtten, 1.0f);

		glUniform4f(locID_lightPosition9, lightPos9.x, lightPos9.y, lightPos9.z, 1.0f);
		//glUniform4f(locID_lightDiffuse, 1.0, 1.0f, 1.0f, 1.0f);
		glUniform4f(locID_lightDiffuse9, 1.0f, 1.0f, 1.0f, 1.0f);
		glUniform4f(locID_lightAttenuation9, ::lightConstAtten9, ::lightLinearAtten9, ::lightQuadAtten9, 1.0f);

		//draw sceneGraph
		g_pSceneGraph->draw(g_pSceneGraph->getRoot());

		glfwSwapBuffers(g_window);

		glfwPollEvents();
	}
	delete ::g_pMeshManager;
	delete ::g_pCamera;
	delete ::g_pPlayer;
//	delete ::g_pSceneGraph;
	delete ::g_pShaderManager;
	delete ::g_pTextureManager;

	glfwDestroyWindow(g_window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	system("pause");
	return 0;
}