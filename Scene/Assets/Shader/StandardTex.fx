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
struct TDirectionalLight
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float3 direction;  
};

//-------------------------------------------------------------------------------
uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInvTrans;
uniform extern float4x4 gWorldViewProjection;
uniform extern float3 gCameraPosition;
uniform extern texture gTex;
uniform extern TMaterial gMtrl;
uniform extern TDirectionalLight gLight;

//-------------------------------------------------------------------------------
sampler TexS = sampler_state
{
	Texture = <gTex>;
	MinFilter = Anisotropic;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	MaxAnisotropy = 8;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

//-------------------------------------------------------------------------------
struct OutputVS
{
    float4 posH    : POSITION0;
    float4 diffuse : COLOR0;
    float4 spec    : COLOR1;
    float2 tex0    : TEXCOORD0;
};

//-------------------------------------------------------------------------------
OutputVS StandardVS(float3 posL : POSITION0, float3 normalL : NORMAL0, float2 tex0: TEXCOORD0)
{
	OutputVS outVS = (OutputVS)0;

	float3 normalW = mul(float4(normalL, 0.0f), gWorldInvTrans).xyz;
	normalW = normalize(normalW);
	
	float3 posW  = mul(float4(posL, 1.0f), gWorld).xyz;
	
	float3 toEye = normalize(gCameraPosition - posW);
	
	float3 r = reflect(-gLight.direction, normalW);
	
	float t  = pow(max(dot(r, toEye), 0.0f), gMtrl.specPower);
	
	float s = max(dot(gLight.direction, normalW), 0.0f);
	
	float3 spec = t*(gMtrl.specular*gLight.specular).rgb;
	float3 diffuse = s*(gMtrl.diffuse*gLight.diffuse).rgb;
	float3 ambient = gMtrl.ambient*gLight.ambient;
	
	outVS.diffuse.rgb = ambient + diffuse;
	outVS.diffuse.a   = gMtrl.diffuse.a;
	outVS.spec = float4(spec, 0.0f);

	outVS.posH = mul(float4(posL, 1.0f), gWorldViewProjection);
	
	outVS.tex0 = tex0;
	
    return outVS;
}

//-------------------------------------------------------------------------------
float4 StandardPS(float4 c : COLOR0, float4 spec : COLOR1, float2 tex0 : TEXCOORD0) : COLOR
{
	float4 texColor = tex2D(TexS, tex0);
	float3 diffuse = c.rgb * texColor.rgb;
    return float4(diffuse + spec.rgb, texColor.a*c.a); 
}

//-------------------------------------------------------------------------------
technique StandardTech
{
    pass P0
    {
        vertexShader = compile vs_2_0 StandardVS();
        pixelShader  = compile ps_2_0 StandardPS();
    }
}
