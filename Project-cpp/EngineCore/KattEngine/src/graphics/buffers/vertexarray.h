#pragma once
#ifndef _VERTEXARRAY_H
	#define _VERTEXARRAY_H
#endif

#include <vector>
#include <GL/glew.h>

#ifndef _BUFFER_H
	#include "buffer.h"
#endif

namespace kattengine {
	namespace graphics {

		class VertexArray
		{
		private:
			GLuint m_ArrayID;
			std::vector<Buffer*> m_Buffers;

		public:
			VertexArray();
			~VertexArray();

			void addBuffer(Buffer* buffer, GLuint index);
			void bind() const;
			void unbind() const;

		};

	}
}