//#define BX_CONFIG_DEBUG true
//#define ENTRY_CONFIG_IMPLEMENT_MAIN 1

// Debug
// 
// Additional Include
// $(ProjectDir)lib\$(Configuration)\glfw;$(ProjectDir)lib\$(Configuration)\bgfx;$(ProjectDir)lib\$(Configuration)\bimg;$(ProjectDir)lib\$(Configuration)\bnet;$(ProjectDir)lib\$(Configuration)\bx;%(AdditionalLibraryDirectories)
// 
// Dependencies
// bgfx$(Configuration).lib
// bimg$(Configuration).lib
// bx$(Configuration).lib
// 
// Release
// 
// Additional Include
// $(ProjectDir)lib\$(Configuration)\glfw;$(ProjectDir)lib\$(Configuration)\bgfx;$(ProjectDir)lib\$(Configuration)\bimg;$(ProjectDir)lib\$(Configuration)\bnet;$(ProjectDir)lib\$(Configuration)\bx;%(AdditionalLibraryDirectories)
// Depend
// bgfx$(Configuration).lib
// bimg$(Configuration).lib
// bx$(Configuration).lib

#include <iostream>
//#include <filesystem>
//namespace fs = std::filesystem;

//#include <stdio.h>

#include <bx/bx.h>
//#include <bx/math.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <glm/matrix.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

//#define STB_IMAGE_IMPLEMENTATION
//#include <stb/stb_image.h>

//#include "util/util.hpp"
//#include "my_util.h"
 
#include "bgfx/examples/common/common.h"
#include "bgfx/examples/common/bgfx_utils.h"

#include "CubeQuad.h"

// Properties -> Build Events -> Post-Build Events -> Command Line
// xcopy "$(SolutionDir)src\res" "$(TargetDir)res" / E / I / Y


static bool s_showStats = false;

static void glfw_errorCallback(int error, const char* description)
{
	fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

static void glfw_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F1 && action == GLFW_RELEASE)
		s_showStats = !s_showStats;
}

int main(int argc, char** argv)
{
	// Create a GLFW window without an OpenGL context.
	glfwSetErrorCallback(glfw_errorCallback);

	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(1600, 900, "Hello bgfx!", nullptr, nullptr); // glfwGetPrimaryMonitor(), nullptr

	if (!window)
		return 1;

	glfwSetKeyCallback(window, glfw_keyCallback);

	// Initialize bgfx using the native window handle and window resolution.
	bgfx::Init init;

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
	init.platformData.ndt = glfwGetX11Display();
	init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window);
#elif BX_PLATFORM_OSX
	init.platformData.nwh = glfwGetCocoaWindow(window);
#elif BX_PLATFORM_WINDOWS
	init.platformData.nwh = glfwGetWin32Window(window);
#endif

	int width, height;
	glfwGetWindowSize(window, &width, &height);
	init.type = bgfx::RendererType::OpenGL; // automatically choose a renderer.
	//init.callback = m_callback;
	init.resolution.width = (uint32_t)width;
	init.resolution.height = (uint32_t)height;
	init.resolution.reset = BGFX_RESET_VSYNC;


	// Call bgfx::renderFrame before bgfx::init to signal to bgfx not to create a render thread.
	// Most graphics APIs must be used on the same thread that created the window.
	bgfx::renderFrame();

	if (!bgfx::init(init))
		return 1;





	

	const bgfx::ViewId mainView = 0;

	
	// Reset window
	bgfx::reset(width, height, BGFX_RESET_VSYNC);

	// Enable debug text.
	bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

	// Set view rectangle for 0th view
	bgfx::setViewRect(mainView, 0, 0, bgfx::BackbufferRatio::Equal);

	// Clear the view rect
	bgfx::setViewClear(mainView,
		BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
		0x88aaffff, 1.0f, 0);



	auto sampler = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);


	//auto texture = loadTexture("res/cobble.tga"); //res/cobble.tga

	/*auto texture = bgfx::createTexture2D(
		bgfx::BackbufferRatio::Equal,
		true,
		1,
		bgfx::TextureFormat::RGBA8I
	);*/

	//fs::path path = fs::current_path().concat("\\res\\textures\\cobble.tga");

	auto text = loadTexture("res/textures/cobble.dds");

	//auto tex = load_texture(path.string());

	//auto a = tex.unwrap();

	//std::cout << "Val X: " << tex.unwrap()._Myfirst._Val.x << std::endl;
	//std::cout << "Val Y: " << tex.unwrap()._Myfirst._Val.y << std::endl;

	//bgfx::TextureHandle texture = load_texture(path.string());

	{
		/*int w;
		int h;
		int comp;
		unsigned char* image;

		fs::path path = fs::current_path().concat("\\res\\textures\\cobble.tga");*/


		/*std::cout << "The current path " << p << " decomposes into:\n" OLD
			<< "root-path " << p.root_path() << '\n'
			<< "relative path " << p.relative_path() << '\n';*/

		//std::string fullPath = path + rel; OLD

		//std::cout << "Path: " << path << std::endl; OLD

		//std::cout << "S Path: " << path.string() << std::endl; OLD

		//std::cout << "C Path: " << path.string().c_str() << std::endl; OLD
		
		
		
		//image = stbi_load(path.string().c_str(), &w, &h, &comp, STBI_rgb_alpha); //STBI_rgb_alpha


		//if (image == nullptr)
		//{
		//	throw(std::string("Failed to load texture"));
		//	//std::cout << "ERROR: " << stbi_failure_reason() << std::endl; OLD
		//}

		//size_t len = w * h * comp;// * sizeof(char);

		//if (comp == 3)
		//	texture = bgfx::createTexture2D(w, h, false, 1, bgfx::TextureFormat::RGB8, BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE, bgfx::copy(image, len));
		//else if (comp == 4)
		//	texture = bgfx::createTexture2D(w, h, false, 1, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE, bgfx::copy(image, len));



		//auto textureMem = bgfx::copy(image, len); BAD
		//texture = bgfx::createTexture(textureMem); BAD
		

		//stbi_image_free(image);
	}



	QuadVerts::init();
	auto vertexBuff = bgfx::createVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_quadVertices, sizeof(s_quadVertices)),
		QuadVerts::quad_layout
	);

	auto indexBuff = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_quadTriList, sizeof(s_quadTriList))
	);

	auto shaderProgram = loadProgram("res/shaders/vs_tex.gl", "res/shaders/fs_tex.gl");







	// Set empty primitive on screen
	bgfx::touch(mainView);

	//float bearing = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Handle window resize.
		int oldWidth = width, oldHeight = height;
		glfwGetWindowSize(window, &width, &height);

		if (width != oldWidth || height != oldHeight) {
			bgfx::reset((uint32_t)width, (uint32_t)height, BGFX_RESET_VSYNC);
			bgfx::setViewRect(mainView, 0, 0, bgfx::BackbufferRatio::Equal);
		}








		

		//std::cout << view << std::endl;

		const bx::Vec3 atBX = { 0.0f, 0.0f,   0.0f };
		const bx::Vec3 eyeBX = { 0.0f, 0.0f, 10.0f };

		float viewBX[16];
		bx::mtxLookAt(viewBX, eyeBX, atBX);





		glm::vec3 eye(0.0f, 0.0f, 10.0f);
		glm::vec3 center(0.0f, 0.0f, 0.0f);

		glm::vec3 up(0.0f, 1.0f, 0.0f);
		glm::mat4 view = glm::lookAt(eye, center, up);
		view = glm::inverse(view);



		/*
		printf("BX:-------------------------------------\n");

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				printf("[%.2f]", viewBX[i * 4 + j]);
			}
			printf("\n");
		}

		printf("GLM:-------------------------------------\n");

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				printf("[%.2f]", view[i][j]);
			}
			printf("\n");
		}

		printf("\n\n\n\n");
		*/



		float proj[16];
		bx::mtxProj(proj,
			60.0f,
			float(width) / float(height),
			0.1f, 100.0f,
			bgfx::getCaps()->homogeneousDepth);

		bgfx::setViewTransform(mainView, viewBX, proj);
		//bgfx::setViewTransform(mainView, glm::value_ptr(view), proj);

		bgfx::touch(0);


		float mtx[16];
		bx::mtxRotateY(mtx, 0.0f);

		// position x,y,z
		mtx[12] = 0.0f;
		mtx[13] = 0.0f;
		mtx[14] = 0.0f;

		// Set model matrix for rendering.
		bgfx::setTransform(mtx);

		


















		//bgfx::setState(BGFX_STATE_DEFAULT);

		// This dummy draw call is here to make sure that view 0 is cleared if no other draw calls are submitted to view 0.
		//bgfx::touch(0);


		//bgfx::setState(BGFX_STATE_DEFAULT);

		//bgfx::setVertexBuffer(0, m_vbh);// - USED
		//bgfx::setVertexBuffer(0, vertexBuf, 0, (sizeof(verts) / (sizeof(float))), vertexLayoutHandle);
		//bgfx::setIndexBuffer(m_ibh);// - USED

		//{
		//	glm::mat4 view;

		//	{
		//		float pitch = 0.0f;
		//		bearing += 0.01f;

		//		std::cout << "Bearing: " << bearing << std::endl;

		//		// define your up vector
		//		glm::vec3 upVector = glm::vec3(0, 1, 0);
		//		// rotate around to a given bearing: yaw
		//		glm::mat4 camera = glm::rotate(glm::mat4(), bearing, upVector);
		//		// Define the 'look up' axis, should be orthogonal to the up axis
		//		glm::vec3 pitchVector = glm::vec3(1, 0, 0);
		//		// rotate around to the required head tilt: pitch
		//		camera = glm::rotate(camera, pitch, pitchVector);

		//		// now get the view matrix by taking the camera inverse
		//		view = glm::inverse(camera);
		//	}

		//	/*float viewArr[16];
		//	const float* pSource = (const float*)glm::value_ptr(pMat4);
		//	for (int i = 0; i < 16; ++i)
		//		viewArr[i] = pSource[i];*/

		//	float proj[16];
		//	bx::mtxProj(proj, 110.0f, float(width) / float(height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

		//	bgfx::setViewTransform(0, &view[0][0], proj);
		//}



		//bgfx::setTexture(0, sampler, texture);
		//bgfx::setTexture(0, sampler, texture, BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE);




		// Set vertex and index buffer.
		bgfx::setVertexBuffer(0, vertexBuff);
		bgfx::setIndexBuffer(indexBuff);


		// Set render states.
		bgfx::setState(BGFX_STATE_DEFAULT);

		bgfx::submit(0, shaderProgram);// - USED



		// Use debug font to print information about this example.
		//bgfx::dbgTextClear();

		const bgfx::Stats* stats = bgfx::getStats();

		// Enable stats or debug text.
		bgfx::setDebug(s_showStats ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);

		// Advance to next frame. Process submitted rendering primitives.
		bgfx::frame();
	}


	bgfx::destroy(shaderProgram);// - USED

	// bgfx::destroy(vertexShaderData);
	// bgfx::destroy(fragmentShaderData);

	bgfx::destroy(vertexBuff);// - USED
	bgfx::destroy(indexBuff);// - USED

	bgfx::shutdown();
	glfwTerminate();
	return 0;
}