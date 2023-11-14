//-------------------------------------------------------------------------------
struct TMaterial
{
    float4   diffuse;
    float4   ambient;
    float4   specular;
    float4   emissive;
    float    specPower;
};

//-------------------------------------------------------------------------------
uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInvTrans;
uniform extern float4x4 gWorldViewProjection;
uniform extern float3 gCameraPosition;
uniform extern TMaterial gMtrl;

//-------------------------------------------------------------------------------
struct OutputVS
{
    float4 posH    : POSITION0;
    float4 diffuse : COLOR0;
};

//-------------------------------------------------------------------------------
OutputVS StandardVS(float3 posL : POSITION0, float3 normalL : NORMAL0, float2 tex0: TEXCOORD0)
{
	OutputVS outVS = (OutputVS)0;
	
	outVS.diffuse.rgb = gMtrl.diffuse.rgb;

	outVS.posH = mul(float4(posL, 1.0f), gWorldViewProjection);
	
    return outVS;
}

//-------------------------------------------------------------------------------
float4 StandardPS(float4 c : COLOR0) : COLOR
{
    return c;
}

//-------------------------------------------------------------------------------
technique DiffuseRGB
{
    pass P0
    {
        vertexShader = compile vs_2_0 StandardVS();
        pixelShader  = compile ps_2_0 StandardPS();
    }
}
