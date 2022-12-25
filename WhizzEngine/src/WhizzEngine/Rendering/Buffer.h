#pragma once

#include "WhizzEngine/Core/Core.h"
#include "WhizzEngine/Core/Log.h"

namespace WhizzEngine
{

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static u32 ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float: return 4;
			case ShaderDataType::Float2: return 4 * 2;
			case ShaderDataType::Float3: return 4 * 3;
			case ShaderDataType::Float4: return 4 * 4;
			case ShaderDataType::Mat3: return 4 * 3 * 3;
			case ShaderDataType::Mat4: return 4 * 4 * 4;
			case ShaderDataType::Int: return 4;
			case ShaderDataType::Int2: return 4 * 2;
			case ShaderDataType::Int3: return 4 * 3;
			case ShaderDataType::Int4: return 4 * 4;
			case ShaderDataType::Bool: return 1;
			default:
				WZ_CORE_ERROR("Unknown ShaderDataType!");
				return 0;
		}
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		u32 Size;
		size_t Offset;
		bool Normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		u32 GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float: return 1;
				case ShaderDataType::Float2: return 2;
				case ShaderDataType::Float3: return 3;
				case ShaderDataType::Float4: return 4;
				case ShaderDataType::Mat3: return 3;
				case ShaderDataType::Mat4: return 4;
				case ShaderDataType::Int: return 1;
				case ShaderDataType::Int2: return 2;
				case ShaderDataType::Int3: return 3;
				case ShaderDataType::Int4: return 4;
				case ShaderDataType::Bool: return 1;
				default:
					WZ_CORE_ERROR("Unknown ShaderDataType!");
					return 0;
			}
		}
	};

	class WZ_API BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(std::initializer_list<BufferElement> elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		u32 GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			size_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		u32 m_Stride = 0;
	};

	class WZ_API VertexBuffer
	{
	public:
		VertexBuffer(u32 size);
		VertexBuffer(float* vertices, u32 size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		void SetData(const void* data, u32 size);

		const BufferLayout& GetLayout() const { return m_Layout; }
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
	private:
		u32 m_RenderID;
		BufferLayout m_Layout;
	};

	class WZ_API IndexBuffer
	{
	public:
		IndexBuffer(u32* indices, u32 count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		u32 GetCount() const { return m_Count; }
	private:
		u32 m_RenderID;
		u32 m_Count;
	};

}