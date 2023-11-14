//-------------------------------------------------------------------------------
struct TDirectionalLight
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float3 direction;  
};

//-------------------------------------------------------------------------------
uniform extern float4x4 gWorldViewProjection;
uniform extern texture gTex0;
uniform extern texture gTex1;
uniform extern texture gTex2;
uniform extern texture gBlendMap;
uniform extern TDirectionalLight gLight;

// todo: make data driven
uniform extern float gTexScale = 24.0f;

sampler Tex0S = sampler_state
{
	Texture = <gTex0>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

sampler Tex1S = sampler_state
{
	Texture = <gTex1>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

sampler Tex2S = sampler_state
{
	Texture = <gTex2>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

sampler BlendMapS = sampler_state
{
	Texture = <gBlendMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};
 
struct OutputVS
{
    float4 posH         : POSITION0;
    float2 tiledTexC    : TEXCOORD0;
    float2 nonTiledTexC : TEXCOORD1;
    float  shade        : TEXCOORD2;
};

OutputVS TerrainVS(float3 posW : POSITION0,
                   float3 normalW : NORMAL0,
                   float2 tex0: TEXCOORD0)
{
	OutputVS outVS = (OutputVS)0;
	
    outVS.shade = saturate(max(0.0f, dot(normalW, gLight.direction)) + 0.3f);
    
	outVS.posH = mul(float4(posW, 1.0f), gWorldViewProjection);
	
	outVS.tiledTexC    = tex0 * gTexScale;
	outVS.nonTiledTexC = tex0; // don't tile the blend map
	
   	return outVS;
}

float4 TerrainPS(float2 tiledTexC : TEXCOORD0, 
                 float2 nonTiledTexC : TEXCOORD1,
                 float shade : TEXCOORD2) : COLOR
{
    float3 c0 = tex2D(Tex0S, tiledTexC).rgb;
    float3 c1 = tex2D(Tex1S, tiledTexC).rgb;
    float3 c2 = tex2D(Tex2S, tiledTexC).rgb;
    
    float3 B = tex2D(BlendMapS, nonTiledTexC).rgb;

    float totalInverse = 1.0f / (B.r + B.g + B.b);
    
    c0 *= B.r * totalInverse;
    c1 *= B.g * totalInverse;
    c2 *= B.b * totalInverse;
    
    float3 final = (c0 + c1 + c2) * shade;
    
    return float4(final, 1.0f);
}

technique TerrainTech
{
    pass P0
    {
        vertexShader = compile vs_2_0 TerrainVS();
        pixelShader  = compile ps_2_0 TerrainPS();
    }
}
