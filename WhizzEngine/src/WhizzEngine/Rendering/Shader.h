#pragma once

#include "WhizzEngine/Core/Core.h"

#include <string>
#include <unordered_map>
#include <map>
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace WhizzEngine
{

	class WZ_API Shader
	{
	public:
		Shader(const std::string& filepath);
		Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~Shader();

		void Start() const;
		void Stop() const;

		void LoadInt(const std::string& name, int value);
		void LoadIntArray(const std::string& name, int* values, u32 count);
		void LoadFloat(const std::string& name, float value);
		void LoadFloatArray(const std::string& name, float* values, u32 count);
		void LoadFloat2(const std::string& name, const glm::vec2& value);
		void LoadFloat2Array(const std::string& name, glm::vec2* values, u32 count);
		void LoadFloat3(const std::string& name, const glm::vec3& value);
		void LoadFloat3Array(const std::string& name, glm::vec3* values, u32 count);
		void LoadFloat4(const std::string& name, const glm::vec4& value);
		void LoadFloat4Array(const std::string& name, glm::vec4* values, u32 count);
		void LoadMat4(const std::string& name, const glm::mat4& value);
		void LoadMat4Array(const std::string& name, glm::mat4* values, u32 count);

		const std::string& GetName() const { return m_Name; }
	private:
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void CreateProgram(const std::string* vertexSrc, const std::string* fragmentSource);
		GLint GetUniformLocation(const std::string& name);
	private:
		u32 m_RenderID;
		std::string m_FilePath;
		std::string m_Name;

		std::map<std::string, GLint> m_UniformLocations;
	};

}