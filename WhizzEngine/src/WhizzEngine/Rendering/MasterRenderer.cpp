#include "MasterRenderer.h"

namespace WhizzEngine {

	void MasterRenderer::Render(Ref<VertexArray> vao)
	{
		for (Ref<Renderer> renderer : m_Renderers)
		{
			renderer->Render(vao);
		}
	}

	Renderer::Renderer(Ref<Shader> shader)
		: m_Shader(shader)
	{
	}

}