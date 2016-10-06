#pragma once
#ifndef _BUFFER_H
	#define _BUFFER_H
#endif

#include <GL/glew.h>

namespace kattengine {
	namespace graphics {

		class Buffer
		{
		private:
			GLuint m_BufferID;
			GLuint m_ComponentCount;

		public:
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			~Buffer();

			void bind() const;
			void unbind() const;

			inline GLuint getComponentCount() const { return m_ComponentCount; }
		
		};
	}
}