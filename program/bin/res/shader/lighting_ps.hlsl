#define MAX_LIGHT_NUM 8
#define LIGHT_TYPE_DIRECTIONAL 0
#define LIGHT_TYPE_POINT 1
#define LIGHT_TYPE_SPOT 2

Texture2D g_baseTexture : register(t0);
SamplerState g_sampler : register(s0);

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

cbuffer MaterialPropterties : register(b0)
{
	MaterialData g_material;
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
cbuffer LightProperties : register(b1)
{
	float4 g_eye_position;
	float4 g_global_ambient;
	LightData g_lights[MAX_LIGHT_NUM];
};

//////////////////////////////////////
float4 DoDiffuse(LightData light, float3 L, float3 N)
{
	float NdotL = max(0, dot(N, L));
	return light.color * NdotL;
}

float4 DoSpecular(LightData light, float3 V, float3 L, float3 N)
{
    // Phong lighting.
    float3 R = normalize( reflect( -L, N ) );
    float RdotV = max( 0, dot( R, V ) );

    // Blinn-Phong lighting
    float3 H = normalize( L + V );
    float NdotH = max( 0, dot( N, H ) );

	return light.color * pow(RdotV, g_material.specular_power);
}

float DoAttenuation(LightData light, float d)
{
	return 1.0f / (light.constant_attenuation + light.linear_attenuation * d + light.quadratic_attenuation * d *d );
}

struct LightingResult
{
	float4 diffuse;
	float4 specular;
};

LightingResult DoPointLight(LightData light, float3 V, float4 P, float3 N)
{
	LightingResult result;
	float3 L = (light.position - P).xyz;
	float distance = length(L);
	L = L / distance;

	float attenuation = DoAttenuation(light, distance);
	result.diffuse = DoDiffuse(light, L, N) * attenuation;
	result.specular = DoSpecular(light, V, L, V) * attenuation;

	return result;
}

LightingResult DoDirectionalLight(LightData light, float3 V, float4 P, float3 N)
{
	LightingResult result;
	
	float3 L = - light.direction.xyz;

	result.diffuse = DoDiffuse(light, L, N);
	result.specular = DoSpecular(light, V, L, N);

	return result;
}

float DoSpotCone(LightData light, float3 L)
{
	float mini_cos = cos(light.spot_angle);
	float max_cos = (mini_cos + 1.0f) / 2.0f;
	float cos_angle = dot(light.direction.xyz, -L);
	return smoothstep(mini_cos, max_cos, cos_angle);

}

LightingResult DoSpotLight(LightData light, float3 V, float4 P, float3 N)
{
	LightingResult result;

	float3 L = (light.position - P).xyz;
	float distance = length(L);
	L = L / distance;

	float attenuation = DoAttenuation(light, distance);
	float spot_intensity = DoSpotCone(light, L);

	result.diffuse = DoDiffuse(light, L, N) * attenuation * spot_intensity;
	result.specular = DoSpecular(light, V, L, N) * attenuation * spot_intensity;

	return result;
}

LightingResult ComputeLighting(float4 P, float3 N)
{
	float3 V = normalize(g_eye_position - P).xyz;

	LightingResult total_result = {{0, 0, 0, 0}, {0, 0, 0, 0}};

	[unroll]
	for(int i=0; i<MAX_LIGHT_NUM; i++)
	{
		LightingResult result = {{0, 0, 0, 0}, {0, 0, 0, 0}};
		if(!g_lights[i].enable)
		{
			continue;
		}

		switch(g_lights[i].light_type)
		{
			case LIGHT_TYPE_DIRECTIONAL:
			{
				result = DoDirectionalLight(g_lights[i], V, P, V);
			}
			break;
			case LIGHT_TYPE_POINT:
			{
				result = DoPointLight(g_lights[i], V, P, N);
			}
			break;
			case LIGHT_TYPE_SPOT:
			{
				result = DoSpotLight(g_lights[i], V, P, N);
			}
			break;
		}

        total_result.diffuse += result.diffuse;
        total_result.specular += result.specular;
    }

	total_result.diffuse = saturate(total_result.diffuse);
	total_result.specular = saturate(total_result.specular);

	return total_result;
}

/////////////////////////////////////////
struct PixelInput
{
	float4 position_ws : TEXCOORD1;
	float3 normal_ws : TEXCOORD2;
	float2 tex_coord : TEXCOORD0;
    float4 position : SV_POSITION;
	float4 color : COLOR;
};

float4 Main(PixelInput input) : SV_TARGET
{
	LightingResult light = ComputeLighting(input.position_ws, normalize(input.normal_ws));

	float4 emissive = g_material.emissive;
	float4 ambient = g_material.ambient * g_global_ambient;
	float4 diffuse = g_material.diffuse * light.diffuse;
	float4 specular = g_material.specular * light.specular;

	float4 tex_color = {1, 1, 1, 1};
	if(g_material.use_texture)
	{
		tex_color = g_baseTexture.Sample(g_sampler, input.tex_coord);
	}

	float4 final_color = (emissive + ambient + diffuse + specular) * tex_color;
	//float4 final_color = {1.0f, 0.0f, 0.0f, 1.0f};
	return final_color;
}