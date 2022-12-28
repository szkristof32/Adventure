#include "Shader.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

#include "WhizzEngine/Core/Log.h"
#include "WhizzEngine/Utils/FileUtils.h"

namespace WhizzEngine
{

	Shader::Shader(const std::string& filepath)
	{
		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		CreateProgram(&shaderSources[GL_VERTEX_SHADER], &shaderSources[GL_FRAGMENT_SHADER]);
	}

	std::unordered_map<GLenum, std::string> Shader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
			if (eol == std::string::npos)
			{
				WZ_CORE_ERROR("Syntax error");
				return shaderSources;
			}
			size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
			std::string type = source.substr(begin, eol - begin);
			GLenum glType = type == "vertex" ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
			if (nextLinePos == std::string::npos)
			{
				WZ_CORE_ERROR("Syntax error");
				return shaderSources;
			}
			pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

			shaderSources[glType] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	Shader::Shader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSrc)
	{
		CreateProgram(&vertexSource, &fragmentSrc);
	}

	void Shader::CreateProgram(const std::string* vertexSrc, const std::string* fragmentSrc)
	{
		const char* v = vertexSrc->c_str();
		GLuint vertexId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexId, 1, &v, NULL);
		glCompileShader(vertexId);
		int success;
		glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLsizei logLength;
			GLchar log[1024];
			glGetShaderInfoLog(vertexId, sizeof(log), &logLength, log);
			WZ_CORE_ERROR("Errors occured during vertex shader compiling.\n{0}", log);
		}

		const char* f = fragmentSrc->c_str();
		GLuint fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentId, 1, &f, NULL);
		glCompileShader(fragmentId);
		glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLsizei logLength;
			GLchar log[1024];
			glGetShaderInfoLog(fragmentId, sizeof(log), &logLength, log);
			WZ_CORE_ERROR("Errors occured during fragment shader compiling.\n{0}", log);
		}

		m_RenderID = glCreateProgram();
		glAttachShader(m_RenderID, vertexId);
		glAttachShader(m_RenderID, fragmentId);
		//TODO: bind attribs
		glLinkProgram(m_RenderID);
		glGetProgramiv(m_RenderID, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLsizei logLength;
			GLchar log[1024];
			glGetProgramInfoLog(m_RenderID, sizeof(log), &logLength, log);
			WZ_CORE_ERROR("Errors occured during shader linking.\n{0}", log);
		}
		glDetachShader(m_RenderID, vertexId);
		glDetachShader(m_RenderID, fragmentId);
		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);
	}

	Shader::~Shader()
	{
		Stop();
		glDeleteProgram(m_RenderID);
	}

	void Shader::Start() const
	{
		glUseProgram(m_RenderID);
	}

	void Shader::Stop() const
	{
		glUseProgram(0);
	}

	GLint Shader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocations.count(name))
			return m_UniformLocations[name];
		GLint location = glGetUniformLocation(m_RenderID, name.c_str());
		m_UniformLocations[name] = location;
		return location;
	}

	void Shader::LoadInt(const std::string& name, int value)
	{
		int location = GetUniformLocation(name);
		glUniform1i(location, value);
	}

	void Shader::LoadIntArray(const std::string& name, int* values, u32 size)
	{
		for (u8 i = 0; i < size; ++i)
		{
			std::stringstream ss;
			ss << name << "[" << i << "]";
			LoadInt(ss.str(), values[i]);
		}
	}

	void Shader::LoadFloat(const std::string& name, float value)
	{
		int location = GetUniformLocation(name);
		glUniform1f(location, value);
	}

	void Shader::LoadFloatArray(const std::string& name, float* values, u32 size)
	{
		for (u8 i = 0; i < size; ++i)
		{
			std::stringstream ss;
			ss << name << "[" << i << "]";
			LoadFloat(ss.str(), values[i]);
		}
	}

	void Shader::LoadFloat2(const std::string& name, const glm::vec2& value)
	{
		int location = GetUniformLocation(name);
		glUniform2f(location, value.x, value.y);
	}

	void Shader::LoadFloat2Array(const std::string& name, glm::vec2* values, u32 size)
	{
		for (u8 i = 0; i < size; ++i)
		{
			std::stringstream ss;
			ss << name << "[" << i << "]";
			LoadFloat2(ss.str(), values[i]);
		}
	}

	void Shader::LoadFloat3(const std::string& name, const glm::vec3& value)
	{
		int location = GetUniformLocation(name);
		glUniform3f(location, value.x, value.y, value.z);
	}

	void Shader::LoadFloat3Array(const std::string& name, glm::vec3* values, u32 size)
	{
		for (u8 i = 0; i < size; ++i)
		{
			std::stringstream ss;
			ss << name << "[" << i << "]";
			LoadFloat3(ss.str(), values[i]);
		}
	}

	void Shader::LoadFloat4(const std::string& name, const glm::vec4& value)
	{
		int location = GetUniformLocation(name);
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void Shader::LoadFloat4Array(const std::string& name, glm::vec4* values, u32 size)
	{
		for (u8 i = 0; i < size; ++i)
		{
			std::stringstream ss;
			ss << name << "[" << i << "]";
			LoadFloat4(ss.str(), values[i]);
		}
	}

	void Shader::LoadMat4(const std::string& name, const glm::mat4& value)
	{
		int location = GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::LoadMat4Array(const std::string& name, glm::mat4* values, u32 size)
	{
		for (u8 i = 0; i < size; ++i)
		{
			std::stringstream ss;
			ss << name << "[" << i << "]";
			LoadMat4(ss.str(), values[i]);
		}
	}

}