#ifndef _WINDOW_H
	#include "src\graphics\window.h"
#endif
#ifndef _SHADER_H
	#include "src\graphics\shader.h"
#endif
#ifndef _MATHS_H
	#include "src\maths\maths.h"
#endif
#include "src\utils\timer.h"

#ifndef _BUFFER_H
	#include "src\graphics\buffers\buffer.h"
#endif
#ifndef _INDEXBUFFER_H
	#include "src\graphics\buffers\indexbuffer.h"
#endif
#ifndef _VERTEXARRAY_H
	#include "src\graphics\buffers\vertexarray.h"
#endif

#ifndef _RENDERER2D_H
	#include "src\graphics\renderer2d.h"
#endif
#ifndef _SIMPLE2DRENDERER_H
	#include "src\graphics\simple2drenderer.h"
#endif
#ifndef _BATCHRENDERER2D_H
	#include "src\graphics\batchrenderer2d.h"
#endif

#include "src\localization\default.h"

#include "src\graphics\static_sprite.h"
#include "src\graphics\sprite.h"

#include "src\graphics\layers\tilelayer.h"

#include "src\graphics\layers\group.h"
//#include "src\graphics\texture.h"

#include <time.h>

#define BATCH_RENDERER 1
#define INACTIVE 0
#define ACTIVE 1
#define ACTIVE_MAIN 1
#define ACTIVE_SHADER 1

#if ACTIVE_MAIN
int main()
{
	using namespace kattengine;
	using namespace graphics;
	using namespace maths;

	// ~ set Width and Height predefinitions ~ //
	
	windowSize = 3;

	if (windowSize == 1)
		width = 960, height = 540;
	else if (windowSize == 2)
		width = 1280, height = 720;
	else if (windowSize == 3)
		width = 1920, height = 1080;
	else
		width = 1920, height = 1080;

	// ~ create the Window ~ //
	Window window(varMode, width, height);
	
#if ACTIVE_SHADER
	// ~ set shaders config ~ //
	mat4 ortho = mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);

	Shader* s = new Shader(vertLoc, fragLoc);
	Shader& shader = *s;
	shader.enable();
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
#endif

	TileLayer layer(&shader);

	// ~ declare textures ~ //
	Texture* textures[] =
	{
		new Texture("texture1.jpg"),
		new Texture("texture2.jpg"),
		new Texture("texture3.jpg"),
		new Texture("texture4.jpg"),
		new Texture("texture5.jpg"),
		new Texture("texture6.jpg")
	};

	//Texture* texture1 = new Texture("testTexture.jpg");
	//Texture* texture2 = new Texture("test.png");

	// ~ bind sprites to layer ~ //
	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			if (rand() % 4 == 0)
				layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		//	layer.add(new Sprite(x, y, 0.9f, 0.9f, rand() % 2 == 0 ? texture1 : texture2));
			else
				layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 6]));
		}
	}

	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	// ~ bind textures to shader ~ //
	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);
	shader.setUniformMat4("pr_matrix", ortho);

	// ~ framerate declarations ~ //
	Timer time;
	timer = 0;
	frames = 0;

	while (!window.closed())
	{
		window.clear();

		// mouseposition:
//		double mpx, mpy;
		window.getMousePositon(mpx, mpy);
//		std::cout << "x = " << x << ", y = " << y << std::endl;

		shader.enable();
		shader.setUniform2f("light_pos", vec2((float)(mpx * 32.0f / width - 16.0f), (float)(9.0f - mpy * 18.0f / height)));
		layer.render();

#if INACTIVE
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(0, 0);
		glTexCoord2f(0, 1); glVertex2f(0, 4);
		glTexCoord2f(1, 1); glVertex2f(4, 4);
		glTexCoord2f(1, 0); glVertex2f(4, 0);
		glEnd();
#endif

		window.update();

#if INACTIVE
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
			//printf("%f ms\n", time.elapsed() * 1000.0);
		}
#endif
	}

	// ~ delete all textures ~ //
	for (int i = 0; i < 6; i++)
		delete textures[i];
	return 0;
}
#else

int main()
{
	const char* filename = "test.png";

	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unknown, return failure
	if (fif == FIF_UNKNOWN)
		return false;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		return false;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return false;

	for (int i = 0; i < width * height; i++)
	{
		int hex = bits[i] | bits[i + 1] << 8 | bits[i + 2] << 16;
		printf("%x\n", hex);
	}
	FreeImage_Unload(dib);
		
	return 0;
}

#endif