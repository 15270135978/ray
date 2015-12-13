// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2015.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#ifndef _H_MODEL_PMX_H_
#define _H_MODEL_PMX_H_

#include <ray/model.h>

_NAME_BEGIN

#pragma pack(push)
#pragma pack(push,1)

enum
{
	PMX_BDEF1,
	PMX_BDEF2,
	PMX_BDEF4,
	PMX_SDEF,
	PMX_QDEF
};

#define PMX_VERSION_2_0   2.0
#define PMX_BONE_INDEX    1 << 0
#define PMX_BONE_MOVE     1 << 1
#define PMX_BONE_IK       1 << 5
#define PMX_BONE_PARENT   1 << 8
#define PMX_BONE_AXIS     1 << 10
#define PMX_BONE_ROTATE   1 << 11

typedef Vector2 PMX_Vector2;
typedef Vector3 PMX_Vector3;
typedef Vector4 PMX_Vector4;

typedef Vector3 PMX_Color3;
typedef Vector4 PMX_Color4;

typedef char          PMX_char;
typedef std::int8_t   PMX_int8_t;
typedef std::uint8_t  PMX_uint8_t;
typedef std::uint16_t PMX_uint16_t;
typedef std::uint32_t PMX_uint32_t;

typedef float PMX_Float;

struct PMX_Header
{
	PMX_uint8_t Magic[3];  // ʼ��ΪPMX

	PMX_uint8_t Offset;    // ʼ��Ϊ 0x20

	PMX_Float   Version;   // �汾

	PMX_uint8_t DataSize;  // ʼ�� 0x08

	PMX_uint8_t Encode;    // 0x00 UTF-16(LE) 0x01 UTF-8

	PMX_uint8_t UVCount;   // ׷�ӵ�UV ( 1 ~ 4 )

	PMX_uint8_t VertexIndexSize;   // ( 1 or 2 or 4 )

	PMX_uint8_t TextureIndexSize;  // ( 1 or 2 or 4 )

	PMX_uint8_t MaterialIndexSize; // ( 1 or 2 or 4 )

	PMX_uint8_t BoneIndexSize;     // ( 1 or 2 or 4 )

	PMX_uint8_t MorphIndexSize;    // ( 1 or 2 or 4 )

	PMX_uint8_t BodyIndexSize;     // ( 1 or 2 or 4 )
};

struct PMX_Description
{
	PMX_uint32_t JapanModelLength;

	std::vector<PMX_char> JapanModelName;

	PMX_uint32_t EnglishModelLength;

	std::vector<PMX_char> EnglishModelName;

	PMX_uint32_t JapanCommentLength;

	std::vector<PMX_char> JapanCommentName;

	PMX_uint32_t EnglishCommentLength;

	std::vector<PMX_char> EnglishCommentName;
};

struct PMX_BoneWeight
{
	PMX_BoneWeight()
		: Bone1(0)
		, Bone2(0)
		, Bone3(0)
		, Bone4(0)
		, Weight1(0)
		, Weight2(0)
		, Weight3(0)
		, Weight4(0)
	{
	}

	PMX_uint16_t Bone1;    // ��������

	PMX_uint16_t Bone2;    // ��������

	PMX_uint16_t Bone3;    // ��������

	PMX_uint16_t Bone4;    // ��������

	PMX_Float Weight1;     // Ȩ��

	PMX_Float Weight2;     // Ȩ��

	PMX_Float Weight3;     // Ȩ��

	PMX_Float Weight4;     // Ȩ��

	PMX_Vector3 SDEF_C;

	PMX_Vector3 SDEF_R0;

	PMX_Vector3 SDEF_R1;
};

typedef PMX_uint32_t PMX_VertexCount;

struct PMX_Vertex
{
	PMX_Vector3 Position; // ��������

	PMX_Vector3 Normal;   // ���㷨��

	PMX_Vector2 UV;       // ������ͼ����

	PMX_Vector4 addUV;    // ������������

	PMX_uint8_t Type;     // ���η�ʽ 0:BDEF1 1:BDEF2 2:BDEF4 3:SDEF

	PMX_BoneWeight BoneWeight; // ����

	PMX_Float   edge;      // ����
};

typedef PMX_uint32_t PMX_IndexCount;

typedef PMX_uint32_t PMX_Index; //��������

typedef PMX_uint32_t PMX_TextureCount;

struct PMX_Name
{
	PMX_uint32_t length;

	std::wstring name;
};

typedef PMX_Name PMX_Texture;
typedef PMX_uint32_t PMX_MaterialCount;

struct PMX_Material
{
	PMX_Name    Name;

	PMX_Name    EnglishName;

	PMX_Color3  Diffuse;

	PMX_Float   Opacity;

	PMX_Color3  Specular;

	PMX_Float   Shininess;

	PMX_Color3  Ambient;

	PMX_uint8_t Flag;

	PMX_Vector4 EdgeColor;

	PMX_Float   EdgeSize;

	PMX_uint8_t TextureIndex;

	PMX_uint8_t SphereTextureIndex;

	PMX_uint16_t ToonIndex;

	PMX_uint8_t ToonFlag;

	PMX_uint32_t SphereMode;

	PMX_uint32_t FaceVertexCount;
};

typedef PMX_uint32_t PMX_BoneCount;

struct PMX_IK
{
	PMX_uint16_t BoneIndex;

	PMX_uint8_t RotateLimited;

	PMX_Vector3 MinimumRadian;

	PMX_Vector3 MaximumRadian;
};

struct PMX_Bone
{
	PMX_Name    Name;

	PMX_Name    EnglishName;

	PMX_Vector3 Position;

	PMX_uint16_t Parent;

	PMX_uint32_t Level;

	PMX_uint16_t Flag;

	PMX_uint16_t ConnectedBoneIndex;

	PMX_uint16_t ProvidedParentBoneIndex;

	PMX_Float  ProvidedRatio;

	PMX_Vector3 Offset;

	PMX_Vector3 AxisDirection;

	PMX_Vector3 DimentionXDirection;

	PMX_Vector3 DimentionZDirection;

	PMX_uint16_t IKTargetBoneIndex;

	PMX_uint32_t IKLoopCount;

	PMX_Float IKLimitedRadian;

	PMX_uint32_t IKLinkCount;

	std::vector<PMX_IK> IKList;
};

struct PMX_MorphVertex
{
	PMX_uint32_t Index;

	PMX_Vector3  Offset;
};

struct PMX_MorphBone
{
	PMX_uint32_t BoneIndex;

	PMX_Float Weight;

	PMX_Vector3 Position;

	PMX_Vector3 Rotate;
};

struct PMX_MorphMaterial
{
	PMX_uint32_t Index;

	PMX_Float Opacity;

	PMX_Color3  Diffuse;

	PMX_Float   Shininess;

	PMX_Color3  Specular;

	PMX_Color3  Ambient;

	PMX_Vector4 EdgeColor;

	PMX_Float   EdgeSize;

	PMX_Color4  Tex;

	PMX_Color4  Unknown;

	PMX_Color4  Toon;
};

typedef PMX_uint32_t PMX_MorphCount;

struct PMX_DisplayIndex
{
	PMX_uint8_t Type;

	PMX_uint32_t BoneIndex;

	PMX_uint32_t MorphIndex;
};

struct PMX_DisplaySlot
{
	PMX_uint32_t DisplayCount;

	std::vector<PMX_DisplayIndex> Slots;
};

#pragma pack(pop)

struct PMX_Morph
{
	PMX_uint32_t Length;

	PMX_uint8_t Name[20];

	PMX_uint32_t  Unknown;

	PMX_uint8_t  OffsetSize;

	PMX_uint8_t  MorphType;

	PMX_uint32_t MorphCount;

	std::vector<PMX_MorphVertex>  VertexList;

	std::vector<PMX_MorphBone> BoneList;

	std::vector<PMX_MorphMaterial> MaterialList;
};

struct PMX
{
	PMX_Header Header;

	PMX_Description Description;

	PMX_VertexCount VertexCount;

	std::vector<PMX_Vertex> VertexList;

	PMX_IndexCount IndexCount;

	std::vector<PMX_Index> IndexList;

	PMX_TextureCount TextureCount;

	std::vector<PMX_Texture> TextureList;

	PMX_MaterialCount MaterialCount;

	std::vector<PMX_Material> MaterialList;

	PMX_BoneCount BoneCount;

	std::vector<PMX_Bone> BoneList;

	PMX_MorphCount            MorphCount;

	std::vector<PMX_Morph>    MorphList;

	PMX_DisplaySlot DisplaySlot;
};

class PMXHandler : public ModelHandler
{
public:
	virtual bool doCanRead(StreamReader& stream) const noexcept;

	virtual bool doLoad(Model& model, StreamReader& stream) noexcept;
	virtual bool doSave(Model& model, StreamWrite& stream) noexcept;
};

_NAME_END

#endif
