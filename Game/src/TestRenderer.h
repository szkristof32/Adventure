#pragma once

#include <WhizzEngine.h>

class TestRenderer : public WhizzEngine::Renderer {
public:
	TestRenderer(WhizzEngine::Ref<WhizzEngine::Shader> shader);
	virtual ~TestRenderer() = default;

	virtual void Render(WhizzEngine::Ref<WhizzEngine::VertexArray> vao) override;
};