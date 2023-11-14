
uniform extern float4x4 gWorldViewProjection;
uniform extern texture  gEnvironmentMap;

sampler EnvMapS = sampler_state
{
    Texture   = <gEnvironmentMap>;
    MinFilter = LINEAR; 
    MagFilter = LINEAR;
    MipFilter = LINEAR;
    AddressU  = WRAP;
    AddressV  = WRAP;
};

void SkyVS(float3 posL : POSITION0, 
           out float4 oPosH : POSITION0, 
           out float3 oEnvTex : TEXCOORD0)
{
    oPosH = mul(float4(posL, 1.0f), gWorldViewProjection).xyww; 
    
    oEnvTex = posL;
}

float4 SkyPS(float3 envTex : TEXCOORD0) : COLOR
{
    return texCUBE(EnvMapS, envTex);
}

technique SkyTech
{
    pass P0
    {
        vertexShader = compile vs_2_0 SkyVS();
        pixelShader  = compile ps_2_0 SkyPS();
		CullMode = None;
		ZFunc = Always;
		StencilEnable = true;
		StencilFunc   = Always;
		StencilPass   = Replace;
		StencilRef    = 0;
    }
}

