#ifndef SHADER_H
#define SHADER_H

#include <map>
#include "base/object.h"

namespace engine_render
{

class Vector;
class ShaderParameter;
class ConstantBuffer;

class Shader : public Object
{
public:

    enum ShaderType
    {
		UnknownShaderType = 0,
        VertexShader,
        TessellationControlShader,      // Hull Shader in DirectX
        TessellationEvaluationShader,   // Domain Shader in DirectX
        GeometryShader,
        PixelShader,
        ComputeShader,
    };

    typedef std::map< std::string, std::string > ShaderMacros;

    virtual ShaderType GetType() const = 0;
	virtual bool LoadShaderFromString( ShaderType type, const std::string& source, const std::wstring& sourceFileName, const ShaderMacros& shaderMacros, const std::string& entryPoint, const std::string& profile ) = 0;
    virtual bool LoadShaderFromFile( ShaderType type, const std::wstring& fileName, const ShaderMacros& shaderMacros, const std::string& entryPoint, const std::string& profile ) = 0;
    virtual ShaderParameter& GetShaderParameterByName( const std::string& name ) const = 0;
    virtual ShaderParameter& operator[]( const std::string& name ) const
    {
        return GetShaderParameterByName( name );
    }
	virtual std::string GetLatestProfile( ShaderType type ) = 0;
    virtual void Bind() = 0;
    virtual void UnBind() = 0;
    virtual void Dispatch( const Vector* numGroups ) = 0;
};
} // namespace engine_render

#endif