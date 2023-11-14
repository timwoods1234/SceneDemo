//-------------------------------------------------------------------------------
// Standard2D.fx
// for UI and 2D
//-------------------------------------------------------------------------------

struct TMaterial {
    float4   diffuse;
    float4   ambient;
    float4   spec;
    float4   emissive;
    float    specPower;
};

//-------------------------------------------------------------------------------
uniform extern texture gTex;
uniform extern float4x4 gWorldViewProjection;
uniform extern TMaterial gMtrl;

//-------------------------------------------------------------------------------
sampler TexS = sampler_state
{
	Texture = <gTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP; 
    AddressV  = WRAP;
};

//-------------------------------------------------------------------------------
void StandardTexVS(float3 pos0         : POSITION0,
              float2 tex0         : TEXCOORD0,
              out float4 oPos0    : POSITION0,
              out float2 oTex0    : TEXCOORD0)
{
	oPos0 = mul(float4(pos0, 1.0f), gWorldViewProjection);
	oTex0 = tex0;
}

//-------------------------------------------------------------------------------
float4 StandardTexPS(float2 tex0    : TEXCOORD0) : COLOR
{
	float3 diffuse = gMtrl.diffuse;

	float4 texColor = tex2D(TexS, tex0); 

	float3 litColor = diffuse * texColor.rgb;

	return float4(litColor, gMtrl.diffuse.a * texColor.a);
}

//-------------------------------------------------------------------------------
technique StandardTex
{
    pass P0
    {
        vertexShader = compile vs_2_0 StandardTexVS();
        pixelShader  = compile ps_2_0 StandardTexPS();
    }
}

