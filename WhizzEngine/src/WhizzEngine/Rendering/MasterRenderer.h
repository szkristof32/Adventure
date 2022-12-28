#pragma once

#include "VertexArray.h"
#include "Shader.h"

#include <vector>

namespace WhizzEngine {

	class WZ_API MasterRenderer {
		friend class Renderer;
	public:
		MasterRenderer() = default;
		virtual ~MasterRenderer() = default;

		void Render(Ref<VertexArray> vao);
		void AddRenderer(Ref<Renderer> renderer) { m_Renderers.push_back(renderer); }
	private:
		std::vector<Ref<Renderer>> m_Renderers;
	};

	class WZ_API Renderer {
	public:
		virtual ~Renderer() = default;

		virtual void Render(Ref<VertexArray> vao) = 0;
	protected:
		Renderer(Ref<Shader> shader);
	protected:
		Ref<Shader> m_Shader;
	};

}