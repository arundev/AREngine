
struct VSInputCommon
{
    float4 position : POSITION;
    float4 color : COLOR;
    float4 tex_coord : TEXCOORD0;
    float4 tex_coord2 : TEXCOORD1;
    float4 normal : NORMAL;
    float4 tangent : TANGENT;
    float4 bitangent : BITANGENT;
};


struct PSInputCommon
{
    float4 position_ws : TEXCOORD1;
    float3 normal_ws : TEXCOORD2;
    float2 tex_coord : TEXCOORD0;
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

struct MaterialData
{
    float4 emissive;
    float4 ambient;
    float4 diffuse;
    float4 specular;

    float specular_power;
    bool use_texture;
    float2 padding;
};

struct LightData
{
    float4 position;
    float4 direction;
    float4 color;

    float spot_angle;
    float constant_attenuation;
    float linear_attenuation;
    float quadratic_attenuation;

    int light_type;
    bool enable;
    int2 padding;
};

struct LightingResult
{
    float4 diffuse;
    float4 specular;
};

float4 DoDiffuse(LightData light, float3 L, float3 N)
{
    float NdotL = max(0, dot(N, L));
    return light.color * NdotL;
}

float4 DoSpecular(LightData light, float specular_power, float3 V, float3 L, float3 N)
{
    // Phong lighting.
    float3 R = normalize(reflect(-L, N));
    float RdotV = max(0, dot(R, V));

    // Blinn-Phong lighting
    float3 H = normalize(L + V);
    float NdotH = max(0, dot(N, H));

    return light.color * pow(RdotV, specular_power);
}

float DoAttenuation(LightData light, float d)
{
    return 1.0f / (light.constant_attenuation + light.linear_attenuation * d + light.quadratic_attenuation * d * d);
}

float DoSpotCone(LightData light, float3 L)
{
    float mini_cos = cos(light.spot_angle);
    float max_cos = (mini_cos + 1.0f) / 2.0f;
    float cos_angle = dot(light.direction.xyz, -L);
    return smoothstep(mini_cos, max_cos, cos_angle);

}

LightingResult DoPointLight(LightData light, float specular_power, float3 V, float4 P, float3 N)
{
    LightingResult result;
    float3 L = (light.position - P).xyz;
    float distance = length(L);
    L = L / distance;

    float attenuation = DoAttenuation(light, distance);
    result.diffuse = DoDiffuse(light, L, N) * attenuation;
    result.specular = DoSpecular(light, specular_power, V, L, V) * attenuation;

    return result;
}

LightingResult DoDirectionalLight(LightData light, float specular_power, float3 V, float4 P, float3 N)
{
    LightingResult result;
	
    float3 L = -light.direction.xyz;

    result.diffuse = DoDiffuse(light, L, N);
    result.specular = DoSpecular(light, specular_power, V, L, N);

    return result;
}


LightingResult DoSpotLight(LightData light, float specular_power, float3 V, float4 P, float3 N)
{
    LightingResult result;

    float3 L = (light.position - P).xyz;
    float distance = length(L);
    L = L / distance;

    float attenuation = DoAttenuation(light, distance);
    float spot_intensity = DoSpotCone(light, L);

    result.diffuse = DoDiffuse(light, L, N) * attenuation * spot_intensity;
    result.specular = DoSpecular(light, specular_power, V, L, N) * attenuation * spot_intensity;

    return result;
}
