#include <WhizzEngine.h>

using namespace WhizzEngine;

int main(int argc, char** argv)
{
	GameManager::Init();

	float vertices[] = {
		-0.5f, 0.5f, -1.0f,		0, 0,
		-0.5f, -0.5f, -1.0f,	0, 1,
		0.5f, 0.5f, -1.0f,		1, 0,
		0.5f, -0.5f, -1.0f,		1, 1
	};
	BufferLayout layout = {
		{ ShaderDataType::Float3, "in_position" },
		{ ShaderDataType::Float2, "in_textureCoord" }
	};
	u32 indices[] = {
		0, 1, 2,
		2, 1, 3
	};

	Ref<VertexArray> vao = CreateRef<VertexArray>();
	Ref<VertexBuffer> vbo = CreateRef<VertexBuffer>(vertices, sizeof(vertices));
	vbo->SetLayout(layout);
	vao->AddVertexBuffer(vbo);
	Ref<IndexBuffer> ibo = CreateRef<IndexBuffer>(indices, sizeof(indices));
	vao->SetIndexBuffer(ibo);

	Ref<Shader> shader = CreateRef<Shader>("res/shaders/basicShader.glsl");

	while (!GameManager::ShouldClose())
	{
		shader->Start();
		vao->Bind();
		vao->Draw();
		vao->Unbind();
		shader->Stop();
		GameManager::Update();
	}

	GameManager::CleanUp();
}