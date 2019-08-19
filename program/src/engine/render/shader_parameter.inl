template<>
void ShaderParameter::Set<ConstantBuffer>( ConstantBuffer* value );

template<>
void ShaderParameter::Set<Texture>(Texture* value );

template<>
void ShaderParameter::Set<SamplerState>(SamplerState* value );

template<>
void ShaderParameter::Set<StructuredBuffer>(StructuredBuffer* value );

template<typename T>
void ShaderParameter::Set( T* value )
{
    //BOOST_STATIC_ASSERT_MSG( false, "This function must be specialized.");
}