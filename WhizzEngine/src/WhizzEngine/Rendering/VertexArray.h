#pragma once

#include "Buffer.h"

#include <memory>

namespace WhizzEngine
{

	class WZ_API VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;
		void Draw() const;
		void EnableAttribs(bool enable, u32 count) const;

		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		const Ref<IndexBuffer>& GetIndexBuffers() const { return m_IndexBuffer; }
	private:
		u32 m_RenderID;
		u32 m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}