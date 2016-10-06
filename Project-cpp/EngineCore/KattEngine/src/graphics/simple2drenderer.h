#pragma once
#ifndef _SIMPLE2DRENDERER_H
	#define _SIMPLE2DRENDERER_H
#endif

#ifndef _RENDERER2D_H
	#include "renderer2d.h"
#endif
#ifndef _STATIC_SPRITE_H
	#include "static_sprite.h"
#endif
#include <deque>

namespace kattengine {
	namespace graphics {

		class Simple2DRenderer : public Renderer2D
		{
		private:
			std::deque<const StaticSprite*> m_RenderQueue;

		public:
			void submit(const Renderable2D* renderable) override;
			void flush() override;

		};

	}
}