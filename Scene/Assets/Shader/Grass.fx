//-------------------------------------------------------------------------------
uniform extern float4x4 gViewProj;
uniform extern texture gTex;
uniform extern float gTime;
uniform extern float3 gCameraPosition;

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
struct OutputVS
{
    float4 posH    : POSITION0;
    float2 tex0    : TEXCOORD0;
    float4 colourOffset : COLOR0;
};

//-------------------------------------------------------------------------------
OutputVS GrassVS(float3 posL : POSITION0,  
                 float3 billboardPosW : TEXCOORD0, 
                 float2 tex0 : TEXCOORD1,  
                 float amplitude : TEXCOORD2,
                 float4 colourOffset : COLOR0)
{
	OutputVS outVS = (OutputVS)0;
	
	float3 look = normalize(gCameraPosition - billboardPosW);
	float3 right = normalize(cross(float3(0.0f, 1.0f, 0.0f), look));
	float3 up = cross(look, right);
	
	float4x4 lookAtMtx;
	lookAtMtx[0] = float4(right, 0.0f);
	lookAtMtx[1] = float4(up, 0.0f);
	lookAtMtx[2] = float4(look, 0.0f);
	lookAtMtx[3] = float4(billboardPosW, 1.0f);
	
	float4 posW = mul(float4(posL, 1.0f), lookAtMtx);

	float sine = amplitude * sin(amplitude * gTime);

	posW.xyz += sine * right;
	
	outVS.colourOffset.r = colourOffset.r + 0.1f * sine;
	outVS.colourOffset.g = colourOffset.g + 0.2f * sine;
	outVS.colourOffset.b = colourOffset.b + 0.1f * sine;
	
	outVS.posH = mul(posW, gViewProj);
	
	outVS.tex0 = tex0;

    return outVS;
}

//-------------------------------------------------------------------------------
float4 GrassPS(float2 tex0 : TEXCOORD0,
               float4 colourOffset : COLOR0) : COLOR
{
	float4 texColor = tex2D(TexS, tex0);
	
	texColor += colourOffset;
	
	return texColor;   
}

//-------------------------------------------------------------------------------
technique Grass
{
    pass P0
    {
        vertexShader = compile vs_2_0 GrassVS();
        pixelShader  = compile ps_2_0 GrassPS();
        
        AlphaRef = 200;
        AlphaFunc = GreaterEqual;
        AlphaTestEnable = true;
        
        CullMode = None;
    }
}

