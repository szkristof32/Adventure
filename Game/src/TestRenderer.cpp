#include "TestRenderer.h"

TestRenderer::TestRenderer(WhizzEngine::Ref<WhizzEngine::Shader> shader)
	: Renderer(shader)
{
}

void TestRenderer::Render(WhizzEngine::Ref<WhizzEngine::VertexArray> vao)
{
	m_Shader->Start();
	vao->Bind();
	vao->Draw();
	vao->Unbind();
	m_Shader->Stop();
}