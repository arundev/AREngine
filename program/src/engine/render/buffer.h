#ifndef buffer_h
#define buffer_h

#include "base/object.h"
#include "shader.h"
#include "shader_parameter.h"

namespace engine_render
{

class Buffer : public Object
{
public:
   
    enum BufferType
    {
        Unknown = 0,
        VertexBuffer,
        IndexBuffer,
        StructuredBuffer,
        ConstantBuffer
    };

    virtual bool Bind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) = 0;
    virtual void UnBind(unsigned int id, Shader::ShaderType shaderType, ShaderParameter::Type parameterType) = 0;
    virtual void Copy(const Buffer* other) = 0;
    virtual BufferType GetType() const = 0;
    virtual unsigned int GetElementCount() const = 0;
};

} // namespace engine_render

#endif