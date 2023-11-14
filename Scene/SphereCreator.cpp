#include "TEngine.h"

#include "SphereCreator.h"
#include "PosVertex.h"

//-------------------------------------------------------------------------------
void SphereCreator::CreateSphere(TMesh& mesh)
{
	PosVertex vertices[12];
	unsigned short indices[60];

	float t = (1.0f + sqrtf(5.0f)) / 2.0f;

	vertices[0].position.Set(-1, t, 0);
	vertices[1].position.Set(1, t, 0);
	vertices[2].position.Set(-1, -t, 0);
	vertices[3].position.Set(1, -t, 0);
	vertices[4].position.Set(0, -1, t);
	vertices[5].position.Set(0, 1, t);
	vertices[6].position.Set(0, -1, -t);
	vertices[7].position.Set(0, 1, -t);
	vertices[8].position.Set(t, 0, -1);
	vertices[9].position.Set(t, 0, 1);
	vertices[10].position.Set(-t, 0, -1);
	vertices[11].position.Set(-t, 0, 1);

	indices[0] = 0; indices[1] = 11; indices[2] = 5;
	indices[3] = 0; indices[4] = 5; indices[5] = 1;
	indices[6] = 0; indices[7] = 1; indices[8] = 7;
	indices[9] = 0; indices[10] = 7; indices[11] = 10;
	indices[12] = 0; indices[13] = 10; indices[14] = 11;
	indices[15] = 1; indices[16] = 5; indices[17] = 9;
	indices[18] = 5; indices[19] = 11; indices[20] = 4;
	indices[21] = 11; indices[22] = 10; indices[23] = 2;
	indices[24] = 10; indices[25] = 7; indices[26] = 6;
	indices[27] = 7; indices[28] = 1; indices[29] = 8;
	indices[30] = 3; indices[31] = 9; indices[32] = 4;
	indices[33] = 3; indices[34] = 4; indices[35] = 2;
	indices[36] = 3; indices[37] = 2; indices[38] = 6;
	indices[39] = 3; indices[40] = 6; indices[41] = 8;
	indices[42] = 3; indices[43] = 8; indices[44] = 9;
	indices[45] = 4; indices[46] = 9; indices[47] = 5;
	indices[48] = 2; indices[49] = 4; indices[50] = 11;
	indices[51] = 6; indices[52] = 2; indices[53] = 10;
	indices[54] = 8; indices[55] = 6; indices[56] = 7;
	indices[57] = 9; indices[58] = 8; indices[59] = 1;

	TSkin* skin = TSkin::Acquire();
	TMaterial material;

	material.ambientColor.Set(0, 1, 0, 1);
	material.diffuseColor.Set(0, 1, 0, 1);
	material.specularColor.Set(1, 1, 1, 1);
	material.emissiveColor.Set(1, 1, 1, 1);
	material.power = 8.0f;

	skin->SetMaterial(material);

	mesh.SetVertices(&vertices[0], 12);
	mesh.SetIndices(&indices[0], 60);
	mesh.SetSkin(skin);

	TSkin::Release(skin);
}