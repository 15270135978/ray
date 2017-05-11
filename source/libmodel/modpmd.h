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
#ifndef _H_MODEL_PMD_H_
#define _H_MODEL_PMD_H_

#include <ray/model.h>

_NAME_BEGIN

#define BONE_TYPE_ROTATE      0
#define BONE_TYPE_ROTATE_MOVE 1
#define BONE_TYPE_IK          2
#define BONE_TYPE_UNKNOWN     3
#define BONE_TYPE_LINK_HEAD   6
#define BONE_TYPE_NONE        7

#define PMD_NUM_TOON 10

#pragma pack(push)
#pragma pack(push,1)

typedef Vector2 PMD_Vector2;
typedef Vector3 PMD_Vector3;
typedef Vector4 PMD_Vector4;

typedef Vector3 PMD_Color3;
typedef Vector4 PMD_Color4;

typedef char          PMD_char;
typedef std::int8_t   PMD_int8_t;
typedef std::uint8_t  PMD_uint8_t;
typedef std::uint16_t PMD_uint16_t;
typedef std::uint32_t PMD_uint32_t;

typedef float PMD_Float;

struct PMD_Header
{
	PMD_uint8_t Magic[3];      // ʼ��ΪPmd

	PMD_Float   Version;       // �汾 1.0f

	PMD_uint8_t ModelName[20]; // ģ������

	PMD_uint8_t Comment[256];  // ģ��˵��
};

struct PMD_BoneIndex
{
	PMD_uint16_t Bone1; // ����1

	PMD_uint16_t Bone2; // ����2
};

typedef PMD_uint32_t PMD_VertexCount;

struct PMD_Vertex
{
	PMD_Vector3 Position;     // ��������

	PMD_Vector3 Normal;       // ���㷨��

	PMD_Vector2 UV;           // ������ͼ����

	PMD_BoneIndex Bone;       // ��������

	PMD_uint8_t  Weight;      // Ȩ��

	PMD_uint8_t  NonEdgeFlag; // �ޱ߱�־��˵����������ֽڲ�Ϊ0ʱNonEdgeFlag=true��
};

typedef PMD_uint32_t PMD_IndexCount;

typedef PMD_uint16_t PMD_Index; //��������

typedef PMD_uint32_t PMD_MaterialCount;

struct PMD_Material
{
	PMD_Color3   Diffuse;         // �����

	PMD_Float    Opacity;         // ��͸����

	PMD_Float    Shininess;       // �����

	PMD_Color3   Specular;        // �����

	PMD_Color3   Ambient;         // ������

	PMD_uint8_t  ToonIndex;       // �з��ţ���ͨ��ɫ������

	PMD_uint8_t  Edge;            // �Ƿ���ߣ������ֽ� > 0ʱΪtrue

	PMD_uint32_t FaceVertexCount; // ����������

	PMD_char     TextureName[20]; // �������������ƣ�ʹ��*�ָ�  ö�٣�NONE��ADD��MUL
};

struct PMD_BoneName
{
	PMD_uint8_t Name[20];
};

typedef PMD_uint16_t PMD_BoneCount;

struct PMD_Bone
{
	PMD_BoneName Name;     // ��������

	PMD_uint16_t Parent;   // ���׹���

	PMD_uint16_t Child;    // ���ӵ�

	PMD_uint8_t  Type;     // ���ͣ�ö�٣�Rotate,RotateMove,IK, Unknown, IKLink, RotateEffect, IKTo, Unvisible, Twist,RotateRatio��

	PMD_uint16_t IKCount;  // IK�������˶�ѧ����ֵ

	PMD_Vector3  Position; // ����λ��
};

typedef PMD_uint16_t PMD_Link;
typedef PMD_uint16_t PMD_IKCount;

struct PMD_IK
{
	PMD_uint16_t IK;

	PMD_uint16_t Target;

	PMD_uint8_t  LinkCount;

	PMD_uint16_t LoopCount;

	PMD_Float    Weight;

	std::vector<PMD_Link> LinkList; // LinkList[LinkCount];
};

struct PMD_MorphVertex
{
	PMD_uint32_t Index;    // Ƥ����Ӧ����ɶ���

	PMD_Vector3  Offset;   // ����λ��
};

struct PMD_MorphName
{
	PMD_uint8_t Name[20];
};

typedef PMD_uint16_t PMD_MorphCount;

struct PMD_Morph
{
	PMD_MorphName Name;        // ��������

	PMD_uint32_t VertexCount; // ���麬�еĶ�������

	PMD_uint8_t  Category;    // ����

	std::vector<PMD_MorphVertex>  VertexList;    // FaceVertex[VertexCount];  // ������������ж�����Ϣ
};

struct PMD_NodeName
{
	PMD_uint8_t Name[50];
};

struct PMD_BoneToNode
{
	PMD_uint16_t Bone;

	PMD_uint8_t  Node;
};

typedef PMD_uint16_t PMD_Expression;

struct PMD_ToonName
{
	PMD_uint8_t Name[20];
};

struct PMD_Description
{
	PMD_uint8_t ModelName[20];

	PMD_uint8_t Comment[256];

	std::vector<PMD_BoneName> BoneName;  // Name[BoneCount];

	std::vector<PMD_MorphName> FaceName;  // Name[PMD_FrameWindow.ExpressionListCount];

	std::vector<PMD_NodeName> FrameName; // Name[PMD_FrameWindow.NodeNameCount];
};

typedef PMD_uint16_t PMD_ToonCount;

struct PMD_Toon
{
	PMD_uint8_t Name[100];
};

typedef PMD_uint32_t PMD_BodyCount;

struct PMD_Body
{
	PMD_uint8_t  Name[20];

	PMD_uint16_t bone;

	PMD_uint8_t group;
	PMD_uint16_t groupMask;
	PMD_uint8_t shape; // 0:Circle 1:Square 2:Capsule

	PMD_Vector3 scale;
	PMD_Vector3 position;
	PMD_Vector3 rotate;

	PMD_Float mass;
	PMD_Float movementDecay; // movement reduction
	PMD_Float rotationDecay; // rotation reduction
	PMD_Float elasticity;    // recoil
	PMD_Float friction;      // strength of friction

	PMD_uint8_t physicsOperation; //0:Follow Bone (static), 1:Physics Calc. (dynamic), 2: Physics Calc. + Bone position matching
};

typedef PMD_uint32_t PMD_JointCount;

struct PMD_Joint
{
	PMD_uint8_t  Name[20];

	PMD_uint32_t relatedRigidBodyIndexA; //-1 if irrelevant
	PMD_uint32_t relatedRigidBodyIndexB;

	PMD_Vector3 position;
	PMD_Vector3 rotation;

	PMD_Vector3 movementLowerLimit;
	PMD_Vector3 movementUpperLimit;

	PMD_Vector3 rotationLowerLimit; //-> radian angle
	PMD_Vector3 rotationUpperLimit; //-> radian angle

	PMD_Vector3 springMovementConstant;
	PMD_Vector3 springRotationConstant;
};

#pragma pack(pop)

struct PMD
{
	PMD_Header                Header;

	PMD_VertexCount           numVertices;
	PMD_IndexCount            numIndices;
	PMD_MaterialCount         numMaterials;
	PMD_IKCount               numIKs;
	PMD_BoneCount             numBones;
	PMD_MorphCount            numMorphs;
	PMD_ToonCount             numToons;
	PMD_BodyCount             numRigidbodys;
	PMD_JointCount            numJoints;
	PMD_uint8_t               numExpression;
	PMD_uint8_t               numNodeNames;
	PMD_uint32_t              numNodeBones;

	std::vector<PMD_Vertex>   VertexList;
	std::vector<PMD_Index>    IndexList;
	std::vector<PMD_Material> MaterialList;
	std::vector<PMD_Bone>     BoneList;
	std::vector<PMD_IK>       IkList;
	std::vector<PMD_Morph>    MorphList;
	std::vector<PMD_Toon>     ToonList;
	std::vector<PMD_Body>     rigidbodys;
	std::vector<PMD_Joint>    joints;
	std::vector<PMD_Expression> ExpressionList;   // ExpressionList[ExpressionListCount]; // ��ȡ���1����ӦƤ������
	std::vector<PMD_NodeName>   NodeNameList;     // NodeNameList[NodeNameCount];
	std::vector<PMD_BoneToNode> BoneToNodeList;   // BoneToNodeList[BoneToNodeCount];

	PMD_uint8_t               HasDescription;
	PMD_Description           Description;
};

class PMDHandler final : public ModelHandler
{
public:
	PMDHandler() noexcept;
	~PMDHandler() noexcept;

	bool doCanRead(StreamReader& stream) const noexcept;
	bool doCanSave(ModelType type) const noexcept;

	bool doLoad(StreamReader& stream, PMD& pmd) noexcept;
	bool doLoad(StreamReader& stream, Model& model) noexcept;

	bool doSave(StreamWrite& stream, const PMD& model) noexcept;
	bool doSave(StreamWrite& stream, const Model& model) noexcept;

private:
	PMDHandler(const PMDHandler&) = delete;
	PMDHandler& operator=(const PMDHandler&) = delete;
};

_NAME_END

#endif