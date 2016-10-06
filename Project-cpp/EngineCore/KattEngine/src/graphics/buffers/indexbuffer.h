#pragma once
#ifndef _INDEXBUFFER_H
	#define _INDEXBUFFER_H
#endif

#include <GL/glew.h>

namespace kattengine {
	namespace graphics {

		class IndexBuffer
		{
		private:
			GLuint m_BufferID;
			GLuint m_Count;

		public:
			IndexBuffer(GLushort* data, GLsizei count);
			IndexBuffer(GLuint* data, GLsizei count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline GLuint getCount() const { return m_Count; }

		};
	}
}