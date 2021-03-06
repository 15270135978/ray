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
#include "vk_shader.h"
#include "vk_device.h"
#include "vk_system.h"

#if defined(__WINDOWS__)
#	include <d3dcompiler.h>
#endif

#include <sstream>

_NAME_BEGIN

const TBuiltInResource defaultOptions = 
{
	/* .MaxLights = */ 32,
	/* .MaxClipPlanes = */ 6,
	/* .MaxTextureUnits = */ 32,
	/* .MaxTextureCoords = */ 32,
	/* .MaxVertexAttribs = */ 64,
	/* .MaxVertexUniformComponents = */ 4096,
	/* .MaxVaryingFloats = */ 64,
	/* .MaxVertexTextureImageUnits = */ 32,
	/* .MaxCombinedTextureImageUnits = */ 80,
	/* .MaxTextureImageUnits = */ 32,
	/* .MaxFragmentUniformComponents = */ 4096,
	/* .MaxDrawBuffers = */ 32,
	/* .MaxVertexUniformVectors = */ 128,
	/* .MaxVaryingVectors = */ 8,
	/* .MaxFragmentUniformVectors = */ 16,
	/* .MaxVertexOutputVectors = */ 16,
	/* .MaxFragmentInputVectors = */ 15,
	/* .MinProgramTexelOffset = */ -8,
	/* .MaxProgramTexelOffset = */ 7,
	/* .MaxClipDistances = */ 8,
	/* .MaxComputeWorkGroupCountX = */ 65535,
	/* .MaxComputeWorkGroupCountY = */ 65535,
	/* .MaxComputeWorkGroupCountZ = */ 65535,
	/* .MaxComputeWorkGroupSizeX = */ 1024,
	/* .MaxComputeWorkGroupSizeY = */ 1024,
	/* .MaxComputeWorkGroupSizeZ = */ 64,
	/* .MaxComputeUniformComponents = */ 1024,
	/* .MaxComputeTextureImageUnits = */ 16,
	/* .MaxComputeImageUniforms = */ 8,
	/* .MaxComputeAtomicCounters = */ 8,
	/* .MaxComputeAtomicCounterBuffers = */ 1,
	/* .MaxVaryingComponents = */ 60,
	/* .MaxVertexOutputComponents = */ 64,
	/* .MaxGeometryInputComponents = */ 64,
	/* .MaxGeometryOutputComponents = */ 128,
	/* .MaxFragmentInputComponents = */ 128,
	/* .MaxImageUnits = */ 8,
	/* .MaxCombinedImageUnitsAndFragmentOutputs = */ 8,
	/* .MaxCombinedShaderOutputResources = */ 8,
	/* .MaxImageSamples = */ 0,
	/* .MaxVertexImageUniforms = */ 0,
	/* .MaxTessControlImageUniforms = */ 0,
	/* .MaxTessEvaluationImageUniforms = */ 0,
	/* .MaxGeometryImageUniforms = */ 0,
	/* .MaxFragmentImageUniforms = */ 8,
	/* .MaxCombinedImageUniforms = */ 8,
	/* .MaxGeometryTextureImageUnits = */ 16,
	/* .MaxGeometryOutputVertices = */ 256,
	/* .MaxGeometryTotalOutputComponents = */ 1024,
	/* .MaxGeometryUniformComponents = */ 1024,
	/* .MaxGeometryVaryingComponents = */ 64,
	/* .MaxTessControlInputComponents = */ 128,
	/* .MaxTessControlOutputComponents = */ 128,
	/* .MaxTessControlTextureImageUnits = */ 16,
	/* .MaxTessControlUniformComponents = */ 1024,
	/* .MaxTessControlTotalOutputComponents = */ 4096,
	/* .MaxTessEvaluationInputComponents = */ 128,
	/* .MaxTessEvaluationOutputComponents = */ 128,
	/* .MaxTessEvaluationTextureImageUnits = */ 16,
	/* .MaxTessEvaluationUniformComponents = */ 1024,
	/* .MaxTessPatchComponents = */ 120,
	/* .MaxPatchVertices = */ 32,
	/* .MaxTessGenLevel = */ 64,
	/* .MaxViewports = */ 16,
	/* .MaxVertexAtomicCounters = */ 0,
	/* .MaxTessControlAtomicCounters = */ 0,
	/* .MaxTessEvaluationAtomicCounters = */ 0,
	/* .MaxGeometryAtomicCounters = */ 0,
	/* .MaxFragmentAtomicCounters = */ 8,
	/* .MaxCombinedAtomicCounters = */ 8,
	/* .MaxAtomicCounterBindings = */ 1,
	/* .MaxVertexAtomicCounterBuffers = */ 0,
	/* .MaxTessControlAtomicCounterBuffers = */ 0,
	/* .MaxTessEvaluationAtomicCounterBuffers = */ 0,
	/* .MaxGeometryAtomicCounterBuffers = */ 0,
	/* .MaxFragmentAtomicCounterBuffers = */ 1,
	/* .MaxCombinedAtomicCounterBuffers = */ 1,
	/* .MaxAtomicCounterBufferSize = */ 16384,
	/* .MaxTransformFeedbackBuffers = */ 4,
	/* .MaxTransformFeedbackInterleavedComponents = */ 64,
	/* .MaxCullDistances = */ 8,
	/* .MaxCombinedClipAndCullDistances = */ 8,
	/* .MaxSamples = */ 4,
	/* .limits = */{
		/* .nonInductiveForLoops = */ 1,
		/* .whileLoops = */ 1,
	/* .doWhileLoops = */ 1,
	/* .generalUniformIndexing = */ 1,
	/* .generalAttributeMatrixVectorIndexing = */ 1,
	/* .generalVaryingIndexing = */ 1,
	/* .generalSamplerIndexing = */ 1,
	/* .generalVariableIndexing = */ 1,
	/* .generalConstantMatrixVectorIndexing = */ 1,
	} };

__ImplementSubClass(VulkanShader, GraphicsShader, "VulkanShader")
__ImplementSubClass(VulkanProgram, GraphicsProgram, "VulkanProgram")
__ImplementSubClass(VulkanGraphicsAttribute, GraphicsAttribute, "VulkanGraphicsAttribute")
__ImplementSubClass(VulkanGraphicsUniform, GraphicsUniform, "VulkanGraphicsUniform")
__ImplementSubClass(VulkanGraphicsUniformBlock, GraphicsUniformBlock, "VulkanGraphicsUniformBlock")

VulkanGraphicsAttribute::VulkanGraphicsAttribute() noexcept
	: _semanticIndex(0)
	, _bindingPoint(GL_INVALID_INDEX)
	, _type(GraphicsFormat::GraphicsFormatUndefined)
{
}

VulkanGraphicsAttribute::~VulkanGraphicsAttribute() noexcept
{
}

void
VulkanGraphicsAttribute::setSemantic(const std::string& semantic) noexcept
{
	_semantic = semantic;
}

const std::string&
VulkanGraphicsAttribute::getSemantic() const noexcept
{
	return _semantic;
}

void
VulkanGraphicsAttribute::setSemanticIndex(std::uint32_t index) noexcept
{
	_semanticIndex = index;
}

std::uint32_t
VulkanGraphicsAttribute::getSemanticIndex() const noexcept
{
	return _semanticIndex;
}

void
VulkanGraphicsAttribute::setType(GraphicsFormat type) noexcept
{
	_type = type;
}

GraphicsFormat
VulkanGraphicsAttribute::getType() const noexcept
{
	return _type;
}

void
VulkanGraphicsAttribute::setBindingPoint(std::uint32_t bindingPoint) noexcept
{
	_bindingPoint = bindingPoint;
}

std::uint32_t
VulkanGraphicsAttribute::getBindingPoint() const noexcept
{
	return _bindingPoint;
}

VulkanGraphicsUniform::VulkanGraphicsUniform() noexcept
	: _offset(0)
	, _bindingPoint(GL_INVALID_INDEX)
	, _type(GraphicsUniformType::GraphicsUniformTypeNone)
	, _stageFlags(0)
{
}

VulkanGraphicsUniform::~VulkanGraphicsUniform() noexcept
{
}

void
VulkanGraphicsUniform::setName(const std::string& name) noexcept
{
	_name = name;
}

const std::string&
VulkanGraphicsUniform::getName() const noexcept
{
	return _name;
}

void
VulkanGraphicsUniform::setSamplerName(const std::string& name) noexcept
{
	_samplerName = name;
}

const std::string&
VulkanGraphicsUniform::getSamplerName() const noexcept
{
	return _samplerName;
}

void
VulkanGraphicsUniform::setType(GraphicsUniformType type) noexcept
{
	_type = type;
}

GraphicsUniformType
VulkanGraphicsUniform::getType() const noexcept
{
	return _type;
}

void
VulkanGraphicsUniform::setOffset(std::uint32_t offset) noexcept
{
	_offset = offset;
}

std::uint32_t
VulkanGraphicsUniform::getOffset() const noexcept
{
	return _offset;
}

void
VulkanGraphicsUniform::setBindingPoint(std::uint32_t bindingPoint) noexcept
{
	_bindingPoint = bindingPoint;
}

std::uint32_t
VulkanGraphicsUniform::getBindingPoint() const noexcept
{
	return _bindingPoint;
}

void
VulkanGraphicsUniform::setShaderStageFlags(GraphicsShaderStageFlags flags) noexcept
{
	_stageFlags = flags;
}

GraphicsShaderStageFlags
VulkanGraphicsUniform::getShaderStageFlags() const noexcept
{
	return _stageFlags;
}

VulkanGraphicsUniformBlock::VulkanGraphicsUniformBlock() noexcept
	: _size(0)
	, _bindingPoint(GL_INVALID_INDEX)
	, _type(GraphicsUniformType::GraphicsUniformTypeUniformBuffer)
	, _stageFlags(0)
{
}

VulkanGraphicsUniformBlock::~VulkanGraphicsUniformBlock() noexcept
{
}

void
VulkanGraphicsUniformBlock::setName(const std::string& name) noexcept
{
	_name = name;
}

const std::string&
VulkanGraphicsUniformBlock::getName() const noexcept
{
	return _name;
}

void
VulkanGraphicsUniformBlock::setType(GraphicsUniformType type) noexcept
{
	_type = type;
}

GraphicsUniformType
VulkanGraphicsUniformBlock::getType() const noexcept
{
	return _type;
}

void
VulkanGraphicsUniformBlock::setBlockSize(std::uint32_t size) noexcept
{
	_size = size;
}

std::uint32_t
VulkanGraphicsUniformBlock::getBlockSize() const noexcept
{
	return _size;
}

void
VulkanGraphicsUniformBlock::setShaderStageFlags(GraphicsShaderStageFlags flags) noexcept
{
	_stageFlags = flags;
}

GraphicsShaderStageFlags
VulkanGraphicsUniformBlock::getShaderStageFlags() const noexcept
{
	return _stageFlags;
}

void
VulkanGraphicsUniformBlock::addGraphicsUniform(GraphicsUniformPtr uniform) noexcept
{
	_uniforms.push_back(uniform);
}

void
VulkanGraphicsUniformBlock::removeGraphicsUniform(GraphicsUniformPtr uniform) noexcept
{
	auto it = std::find(_uniforms.begin(), _uniforms.end(), uniform);
	if (it != _uniforms.end())
		_uniforms.erase(it);
}

const GraphicsUniforms&
VulkanGraphicsUniformBlock::getGraphicsUniforms() const noexcept
{
	return _uniforms;
}

void
VulkanGraphicsUniformBlock::setBindingPoint(std::uint32_t bindingPoint) noexcept
{
	_bindingPoint = bindingPoint;
}

std::uint32_t
VulkanGraphicsUniformBlock::getBindingPoint() const noexcept
{
	return _bindingPoint;
}

VulkanShader::VulkanShader() noexcept
{
}

VulkanShader::~VulkanShader() noexcept
{
	this->close();
}

bool
VulkanShader::setup(const GraphicsShaderDesc& shaderDesc) noexcept
{
	_shaderDesc = shaderDesc;
	return true;
}

void
VulkanShader::close() noexcept
{
}

void
VulkanShader::setDevice(GraphicsDevicePtr device) noexcept
{
	_device = device;
}

GraphicsDevicePtr
VulkanShader::getDevice() noexcept
{
	return _device.lock();
}

const GraphicsShaderDesc&
VulkanShader::getGraphicsShaderDesc() const noexcept
{
	return _shaderDesc;
}

VulkanStageShader::VulkanStageShader() noexcept
	: _shader(VK_NULL_HANDLE)
{
}

VulkanStageShader::~VulkanStageShader() noexcept
{
}

bool
VulkanStageShader::setup(const GraphicsShaderDesc& shaderDesc, std::uint32_t startLocation) noexcept
{
	assert(_shader == VK_NULL_HANDLE);

	if (shaderDesc.getByteCodes().empty())
		return false;

	std::string codes = shaderDesc.getByteCodes();

	if (shaderDesc.getLanguage() == GraphicsShaderLang::GraphicsShaderLangHLSL)
	{
		if (!HlslCodes2GLSL(shaderDesc.getStage(), startLocation, shaderDesc.getByteCodes().data(), codes))
		{
			VK_PLATFORM_LOG("Can't conv hlsl to glsl.");
			return false;
		}
	}
	else if (shaderDesc.getLanguage() == GraphicsShaderLang::GraphicsShaderLangHLSLbytecodes)
	{
		if (!HlslByteCodes2GLSL(shaderDesc.getStage(), startLocation, shaderDesc.getByteCodes().data(), codes))
		{
			VK_PLATFORM_LOG("Can't conv hlslbytecodes to glsl.");
			return false;
		}
	}

	std::vector<std::uint32_t> bytecodes;
	if (!GLSLtoSPV(VulkanTypes::asShaderStage(shaderDesc.getStage()), codes.c_str(), bytecodes))
	{
		VK_PLATFORM_LOG("Can't conv glsl to spv.");
		return false;
	}

	VkShaderModuleCreateInfo info;
	info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	info.pNext = nullptr;
	info.codeSize = bytecodes.size() * sizeof(std::uint32_t);
	info.pCode = bytecodes.data();
	info.flags = 0;

	if (vkCreateShaderModule(this->getDevice()->downcast<VulkanDevice>()->getDevice(), &info, nullptr, &_shader) != VK_SUCCESS)
	{
		VK_PLATFORM_LOG("vkCreateShaderModule() fail.");
		return false;
	}

	_shaderDesc = shaderDesc;
	_shaderDesc.setByteCodes(std::move(codes));
	_shaderDesc.setLanguage(GraphicsShaderLang::GraphicsShaderLangGLSL);
	return true;
}

void
VulkanStageShader::close() noexcept
{
	if (_shader != VK_NULL_HANDLE)
	{
		vkDestroyShaderModule(this->getDevice()->downcast<VulkanDevice>()->getDevice(), _shader, nullptr);
		_shader = VK_NULL_HANDLE;
	}
}

VkShaderModule 
VulkanStageShader::getShaderModule() const noexcept
{
	return _shader;
}

VkShaderStageFlagBits 
VulkanStageShader::getShaderStage() const noexcept
{
	return VulkanTypes::asShaderStage(_shaderDesc.getStage());
}

const GraphicsParams& 
VulkanStageShader::getParams() const noexcept
{
	return _parameters;
}

const GraphicsParams&
VulkanStageShader::getArrayParams() const noexcept
{
	return _arrays;
}

const GraphicsAttributes& 
VulkanStageShader::getAttributes() const noexcept
{
	return _attributes;
}

const GraphicsShaderDesc& 
VulkanStageShader::getGraphicsShaderDesc() const noexcept
{
	return _shaderDesc;
}

void
VulkanStageShader::setDevice(GraphicsDevicePtr device) noexcept
{
	_device = device->downcast_pointer<VulkanDevice>();
}

GraphicsDevicePtr
VulkanStageShader::getDevice() noexcept
{
	return _device.lock();
}

bool
VulkanStageShader::HlslCodes2GLSL(GraphicsShaderStageFlagBits stage, std::uint32_t startLocation, const std::string& codes, std::string& out)
{
#if defined(_BUILD_PLATFORM_WINDOWS)
	std::string profile;
	if (stage == GraphicsShaderStageFlagBits::GraphicsShaderStageVertexBit)
		profile = "vs_4_0";
	else if (stage == GraphicsShaderStageFlagBits::GraphicsShaderStageFragmentBit)
		profile = "ps_4_0";

	ID3DBlob* binary = nullptr;
	ID3DBlob* error = nullptr;

	D3DCreateBlob(4096, &binary);
	D3DCreateBlob(4096, &error);

	HRESULT hr = D3DCompile(
		codes.data(),
		codes.size(),
		nullptr,
		nullptr,
		nullptr,
		"main",
		profile.c_str(),
		D3DCOMPILE_OPTIMIZATION_LEVEL3,
		0,
		&binary,
		&error
	);

	if (hr != S_OK)
	{
		std::string line;
		std::size_t index = 1;
		std::ostringstream ostream;
		std::istringstream istream(codes);

		ostream << (const char*)error->GetBufferPointer() << std::endl;
		while (std::getline(istream, line))
		{
			ostream << index << '\t' << line << std::endl;
			index++;
		}

		VK_PLATFORM_LOG(ostream.str().c_str());
		return false;
	}

	return HlslByteCodes2GLSL(stage, startLocation, (char*)binary->GetBufferPointer(), out);
#else
	return false;
#endif
}

bool
VulkanStageShader::HlslByteCodes2GLSL(GraphicsShaderStageFlagBits stage, std::uint32_t startLocation, const char* codes, std::string& out)
{
	std::uint32_t flags = HLSLCC_FLAG_COMBINE_TEXTURE_SAMPLERS | HLSLCC_FLAG_INOUT_APPEND_SEMANTIC_NAMES | HLSLCC_FLAG_UNIFORM_BUFFER_OBJECT;
	if (stage == GraphicsShaderStageFlagBits::GraphicsShaderStageGeometryBit)
		flags = HLSLCC_FLAG_GS_ENABLED;
	else if (stage == GraphicsShaderStageFlagBits::GraphicsShaderStageTessControlBit)
		flags = HLSLCC_FLAG_TESS_ENABLED;
	else if (stage == GraphicsShaderStageFlagBits::GraphicsShaderStageTessEvaluationBit)
		flags = HLSLCC_FLAG_TESS_ENABLED;

	GLSLShader shader;
	GLSLCrossDependencyData dependency;
	GlExtensions extensition;
	extensition.ARB_explicit_uniform_location = true;
	extensition.ARB_explicit_attrib_location = true;
	extensition.ARB_shading_language_420pack = true;

	if (!TranslateHLSLFromMem(codes, flags, GLLang::LANG_440, startLocation, &extensition, &dependency, &shader))
	{
		FreeGLSLShader(&shader);
		return false;
	}

	for (std::uint32_t i = 0; i < shader.reflection.ui32NumInputSignatures; i++)
	{
		auto attribute = shader.reflection.psInputSignatures[i];

		auto attrib = std::make_shared<VulkanGraphicsAttribute>();
		attrib->setSemantic(attribute.SemanticName);
		attrib->setSemanticIndex(attribute.ui32SemanticIndex);
		attrib->setBindingPoint(i);

		if (attribute.eComponentType == INOUT_COMPONENT_TYPE::INOUT_COMPONENT_UINT32)
			attrib->setType(GraphicsFormat::GraphicsFormatR32G32B32UInt);
		else if (attribute.eComponentType == INOUT_COMPONENT_TYPE::INOUT_COMPONENT_SINT32)
			attrib->setType(GraphicsFormat::GraphicsFormatR32G32B32SInt);
		else if (attribute.eComponentType == INOUT_COMPONENT_TYPE::INOUT_COMPONENT_FLOAT32)
			attrib->setType(GraphicsFormat::GraphicsFormatR32G32B32SFloat);
		else
			continue;

		_attributes.push_back(attrib);
	}

	for (std::uint32_t i = 0; i < shader.reflection.ui32NumResourceBindings; i++)
	{
		auto resourceType = shader.reflection.psResourceBindings[i].eType;

		if (resourceType != ResourceType::RTYPE_SAMPLER)
		{
			auto param = std::make_shared<VulkanGraphicsUniform>();
			param->setName(shader.reflection.psResourceBindings[i].Name);
			param->setType(HlslResTypeToUniformType(resourceType));

			_parameters.push_back(param);
		}
	}

	for (std::uint32_t i = 0; i < shader.reflection.ui32NumConstantBuffers; i++)
	{
		for (std::uint32_t j = 0; j < shader.reflection.psConstantBuffers[i].ui32NumVars; j++)
		{
			auto elements = shader.reflection.psConstantBuffers[i].asVars[j].sType.Elements;
			if (elements > 0)
			{
				auto param = std::make_shared<VulkanGraphicsUniform>();
				param->setName(shader.reflection.psConstantBuffers[i].asVars[j].Name);

				_arrays.push_back(param);
			}
		}
	}

	out = shader.sourceCode;
	FreeGLSLShader(&shader);
	return true;
}

GraphicsUniformType
VulkanStageShader::HlslResTypeToUniformType(ResourceType type) noexcept
{
	switch (type)
	{
	case RTYPE_CBUFFER:
		return GraphicsUniformType::GraphicsUniformTypeUniformBuffer;
	case RTYPE_TBUFFER:
		return GraphicsUniformType::GraphicsUniformTypeUniformTexelBuffer;
	case RTYPE_TEXTURE:
		return GraphicsUniformType::GraphicsUniformTypeSamplerImage;
	case RTYPE_SAMPLER:
		return GraphicsUniformType::GraphicsUniformTypeSampler;
	case RTYPE_STRUCTURED:
		return GraphicsUniformType::GraphicsUniformTypeUniformBuffer;
	case RTYPE_UAV_RWSTRUCTURED:
		return GraphicsUniformType::GraphicsUniformTypeUniformBuffer;
	default:
		assert(false);
		return GraphicsUniformType::GraphicsUniformTypeNone;
	}
}

bool
VulkanStageShader::GLSLtoSPV(const VkShaderStageFlagBits shader_type, const char *pshader, std::vector<unsigned int> &spirv)
{
	EShLanguage stage = EShLangVertex;
	if (shader_type == VK_SHADER_STAGE_VERTEX_BIT)
		stage = EShLangVertex;
	else if (shader_type == VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT)
		stage = EShLangTessControl;
	else if (shader_type == VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT)
		stage = EShLangTessEvaluation;
	else if (shader_type == VK_SHADER_STAGE_GEOMETRY_BIT)
		stage = EShLangGeometry;
	else if (shader_type == VK_SHADER_STAGE_FRAGMENT_BIT)
		stage = EShLangFragment;
	else if (shader_type == VK_SHADER_STAGE_COMPUTE_BIT)
		stage = EShLangCompute;

	glslang::TShader shader(stage);
	glslang::TProgram program;

	const char *shaderStrings[1];
	shaderStrings[0] = pshader;
	shader.setStrings(shaderStrings, 1);

	EShMessages messages = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);
	if (!shader.parse(&defaultOptions, 440, false, messages))
	{
		VK_PLATFORM_LOG(shader.getInfoLog());
		VK_PLATFORM_LOG(shader.getInfoDebugLog());
		return false;
	}

	program.addShader(&shader);

	if (!program.link(messages))
	{
		VK_PLATFORM_LOG(program.getInfoLog());
		VK_PLATFORM_LOG(program.getInfoDebugLog());
		return false;
	}

	glslang::GlslangToSpv(*program.getIntermediate(stage), spirv);
	return true;
}

VulkanProgram::VulkanProgram() noexcept
{
}

VulkanProgram::~VulkanProgram() noexcept
{
}

bool
VulkanProgram::setup(const GraphicsProgramDesc& programDesc) noexcept
{
	glslang::TShader vs(EShLangVertex);
	glslang::TShader fs(EShLangFragment);
	glslang::TShader gs(EShLangGeometry);
	glslang::TShader cs(EShLangCompute);
	glslang::TShader tessControl(EShLangTessControl);
	glslang::TShader tessEvaluation(EShLangTessEvaluation);
	glslang::TShader* shaders[EShLangCount];
	const char* shaderStrings[EShLangCount];

	shaders[EShLangVertex] = &vs;
	shaders[EShLangFragment] = &fs;
	shaders[EShLangGeometry] = &gs;
	shaders[EShLangCompute] = &cs;
	shaders[EShLangTessControl] = &tessControl;
	shaders[EShLangTessEvaluation] = &tessEvaluation;

	glslang::TProgram program;

	std::uint32_t startLocation = 0;
	for (auto& it : programDesc.getShaders())
	{
		auto vulkanShader = std::make_unique<VulkanStageShader>();
		vulkanShader->setDevice(this->getDevice());

		if (!vulkanShader->setup(it->getGraphicsShaderDesc(), startLocation))
			return false;

		startLocation += vulkanShader->getParams().size();

		_activeShaders.push_back(std::move(vulkanShader));
	}

	for (auto& it : _activeShaders)
	{
		const auto& vulkanShaderDesc = it->getGraphicsShaderDesc();

		EShLanguage stage = EShLangVertex;

		auto shaderStage = vulkanShaderDesc.getStage();
		if (shaderStage == GraphicsShaderStageFlagBits::GraphicsShaderStageVertexBit)
			stage = EShLangVertex;
		else if (shaderStage == GraphicsShaderStageFlagBits::GraphicsShaderStageFragmentBit)
			stage = EShLangFragment;
		else if (shaderStage == GraphicsShaderStageFlagBits::GraphicsShaderStageComputeBit)
			stage = EShLangCompute;
		else if (shaderStage == GraphicsShaderStageFlagBits::GraphicsShaderStageGeometryBit)
			stage = EShLangGeometry;
		else if (shaderStage == GraphicsShaderStageFlagBits::GraphicsShaderStageTessControlBit)
			stage = EShLangTessControl;
		else if (shaderStage == GraphicsShaderStageFlagBits::GraphicsShaderStageTessEvaluationBit)
			stage = EShLangTessEvaluation;

		shaderStrings[stage] = vulkanShaderDesc.getByteCodes().c_str();
		shaders[stage]->setStrings(&shaderStrings[stage], 1);
		if (!shaders[stage]->parse(&defaultOptions, 440, false, (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules)))
		{
			VK_PLATFORM_LOG(shaders[stage]->getInfoLog());
			VK_PLATFORM_LOG(shaders[stage]->getInfoDebugLog());
			return false;
		}

		program.addShader(shaders[stage]);
	}

	if (!program.link(EShMessages::EShMsgDefault))
	{
		VK_PLATFORM_LOG(program.getInfoLog());
		VK_PLATFORM_LOG(program.getInfoDebugLog());
		return false;
	}

	program.buildReflection();

	_initActiveAttribute(program, programDesc);
	_initActiveUniformBlock(program, programDesc);
	_initActiveUniform(program, programDesc);

	_programDesc = programDesc;
	return true;
}

void
VulkanProgram::close() noexcept
{
	_activeAttributes.clear();
	_activeParams.clear();
}

const VulkanProgram::ShaderStages&
VulkanProgram::getActiveShaders() const noexcept
{
	return _activeShaders;
}

const GraphicsParams&
VulkanProgram::getActiveParams() const noexcept
{
	return _activeParams;
}

const GraphicsAttributes&
VulkanProgram::getActiveAttributes() const noexcept
{
	return _activeAttributes;
}

void
VulkanProgram::_initActiveAttribute(glslang::TProgram& program, const GraphicsProgramDesc& programDesc) noexcept
{
	VulkanStageShader* vert = nullptr;

	for (auto& shader : _activeShaders)
	{
		if (shader->getShaderStage() == VK_SHADER_STAGE_VERTEX_BIT)
			vert = shader.get();
	}

	if (!vert)
		return;

	auto& attributes = vert->getAttributes();

	std::size_t numAttributes = program.getNumLiveAttributes();
	for (std::size_t i = 0; i < numAttributes; i++)
	{
		std::string name = program.getAttributeName(i);
		std::string semantic;
		std::uint32_t semanticIndex = 0;

		auto it = std::find_if_not(name.rbegin(), name.rend(), [](char ch) { return ch >= '0' && ch <= '9'; });
		if (it != name.rend())
		{
			semantic = name.substr(0, name.rend() - it);
			semanticIndex = std::atoi(name.substr(name.rend() - it).c_str());
		}

		std::size_t off = semantic.find_last_of('_');
		if (off != std::string::npos)
			semantic = semantic.substr(off + 1);
		else
			semantic = semantic;

		for (auto& attrib : attributes)
		{
			if (attrib->getSemantic() == semantic &&
				attrib->getSemanticIndex() == semanticIndex)
			{
				auto activeAttribute = std::make_shared<VulkanGraphicsAttribute>();
				activeAttribute->setSemantic(semantic);
				activeAttribute->setSemanticIndex(semanticIndex);
				activeAttribute->setBindingPoint(attrib->downcast<VulkanGraphicsAttribute>()->getBindingPoint());
				activeAttribute->setType(toGraphicsFormat(program.getAttributeType(i)));

				_activeAttributes.push_back(activeAttribute);

				break;
			}
		}
	}
}

void 
VulkanProgram::_initActiveUniform(glslang::TProgram& program, const GraphicsProgramDesc& programDesc) noexcept
{
	std::size_t numUniforms = program.getNumLiveUniformVariables();
	for (std::size_t i = 0; i < numUniforms; i++)
	{
		auto type = program.getUniformType(i);
		if (type == GL_SAMPLER_2D ||
			type == GL_SAMPLER_2D_ARRAY ||
			type == GL_SAMPLER_3D ||
			type == GL_SAMPLER_CUBE ||
			type == GL_SAMPLER_CUBE_MAP_ARRAY)
		{
			std::string name = program.getUniformName(i);

			auto uniform = std::make_shared<VulkanGraphicsUniform>();
			uniform->setType(GraphicsUniformType::GraphicsUniformTypeSamplerImage);
			uniform->setShaderStageFlags(GraphicsShaderStageFlagBits::GraphicsShaderStageFragmentBit);

			auto pos = name.find("_X_");
			if (pos != std::string::npos)
			{
				uniform->setName(name.substr(0, pos));
				uniform->setSamplerName(name.substr(pos + 3));
			}
			else
			{
				uniform->setName(std::move(name));
			}

			std::uint32_t bindingPoint = 0;
			for (auto& it : _activeShaders)
			{
				for (auto& param : it->getParams())
				{
					if (param->getName() == uniform->getName())
						break;
					bindingPoint++;
				}
			}

			uniform->setBindingPoint(bindingPoint);

			_activeParams.push_back(uniform);
		}
	}
}

void 
VulkanProgram::_initActiveUniformBlock(glslang::TProgram& program, const GraphicsProgramDesc& programDesc) noexcept
{
	std::size_t numUniformBlock = program.getNumLiveUniformBlocks();
	for (std::size_t i = 0; i < numUniformBlock; i++)
	{
		auto index = program.getUniformBlockIndex(i);
		if (index == -1)
			continue;

		std::string name = program.getUniformBlockName(i);

		auto uniformBlock = std::make_shared<VulkanGraphicsUniformBlock>();
		uniformBlock->setName(name);
		uniformBlock->setType(GraphicsUniformType::GraphicsUniformTypeUniformBuffer);
		uniformBlock->setBindingPoint(index);
		uniformBlock->setBlockSize(program.getUniformBlockSize(i));
		uniformBlock->setShaderStageFlags(GraphicsShaderStageFlagBits::GraphicsShaderStageAll);
		
		if (name != "Globals")
			continue;

		std::size_t numUniformsInBlock = program.getNumLiveUniformVariables();
		for (std::size_t uniformIndex = 0; uniformIndex < numUniformsInBlock; uniformIndex++)
		{
			auto type = program.getUniformType(uniformIndex);
			if (type != GL_SAMPLER_2D &&
				type != GL_SAMPLER_2D_ARRAY &&
				type != GL_SAMPLER_3D &&
				type != GL_SAMPLER_CUBE &&
				type != GL_SAMPLER_CUBE_MAP_ARRAY)
			{
				auto uniformName = program.getUniformName(uniformIndex);

				bool isArray = false;

				for (auto& shader : _activeShaders)
				{
					auto& params = shader->getArrayParams();
					for (auto& param : params)
					{
						if (param->getName() == uniformName)
						{
							isArray = true;
							break;
						}
					}

					if (isArray)
						break;
				}

				auto uniform = std::make_shared<VulkanGraphicsUniform>();
				uniform->setName(uniformName);
				uniform->setType(toGraphicsUniformType(uniformName, type, isArray));
				uniform->setBindingPoint(uniformIndex);
				uniform->setOffset(program.getUniformBufferOffset(uniformIndex));

				uniformBlock->addGraphicsUniform(uniform);
			}
		}

		_activeParams.push_back(uniformBlock);
	}
}

GraphicsFormat
VulkanProgram::toGraphicsFormat(int type) noexcept
{
	if (type == GL_BOOL)
		return GraphicsFormat::GraphicsFormatR8UInt;
	else if (type == GL_UNSIGNED_INT)
		return GraphicsFormat::GraphicsFormatR8UInt;
	else if (type == GL_UNSIGNED_INT_VEC2)
		return GraphicsFormat::GraphicsFormatR8G8UInt;
	else if (type == GL_UNSIGNED_INT_VEC3)
		return GraphicsFormat::GraphicsFormatR8G8B8UInt;
	else if (type == GL_UNSIGNED_INT_VEC4)
		return GraphicsFormat::GraphicsFormatR8G8B8A8UInt;
	else if (type == GL_INT)
		return GraphicsFormat::GraphicsFormatR8SInt;
	else if (type == GL_INT_VEC2)
		return GraphicsFormat::GraphicsFormatR8G8SInt;
	else if (type == GL_INT_VEC3)
		return GraphicsFormat::GraphicsFormatR8G8B8SInt;
	else if (type == GL_INT_VEC4)
		return GraphicsFormat::GraphicsFormatR8G8B8A8SInt;
	else if (type == GL_FLOAT)
		return GraphicsFormat::GraphicsFormatR32SFloat;
	else if (type == GL_FLOAT_VEC2)
		return GraphicsFormat::GraphicsFormatR32G32SFloat;
	else if (type == GL_FLOAT_VEC3)
		return GraphicsFormat::GraphicsFormatR32G32B32SFloat;
	else if (type == GL_FLOAT_VEC4)
		return GraphicsFormat::GraphicsFormatR32G32B32A32SFloat;
	else if (type == GL_FLOAT_MAT2)
		return GraphicsFormat::GraphicsFormatR32G32B32A32SFloat;
	else if (type == GL_FLOAT_MAT3)
		return GraphicsFormat::GraphicsFormatR32G32B32A32SFloat;
	else if (type == GL_FLOAT_MAT4)
		return GraphicsFormat::GraphicsFormatR32G32B32A32SFloat;
	else
	{
		VK_PLATFORM_ASSERT(false, "Invlid attrib format");
		return GraphicsFormat::GraphicsFormatUndefined;
	}
}

GraphicsUniformType
VulkanProgram::toGraphicsUniformType(const std::string& name, int type, bool forceArray) noexcept
{
	if (type == GL_SAMPLER_2D ||
		type == GL_SAMPLER_2D_ARRAY ||
		type == GL_SAMPLER_3D ||
		type == GL_SAMPLER_CUBE ||
		type == GL_SAMPLER_CUBE_MAP_ARRAY)
	{
		return GraphicsUniformType::GraphicsUniformTypeSamplerImage;
	}
	else
	{
		bool isArray = name.find("[0]") != std::string::npos || forceArray;

		if (type == GL_BOOL)
		{
			return GraphicsUniformType::GraphicsUniformTypeBool;
		}
		else if (type == GL_INT)
		{
			if (isArray)
				return GraphicsUniformType::GraphicsUniformTypeIntArray;
			else
				return GraphicsUniformType::GraphicsUniformTypeInt;
		}
		else if (type == GL_INT_VEC2)
		{
			if (isArray)
				return GraphicsUniformType::GraphicsUniformTypeInt2Array;
			else
				return GraphicsUniformType::GraphicsUniformTypeInt2;
		}
		else if (type == GL_INT_VEC3)
		{
			if (isArray)
				return GraphicsUniformType::GraphicsUniformTypeInt3Array;
			else
				return GraphicsUniformType::GraphicsUniformTypeInt3;
		}
		else if (type == GL_INT_VEC4)
		{
			if (isArray)
				return GraphicsUniformType::GraphicsUniformTypeInt4Array;
			else
				return GraphicsUniformType::GraphicsUniformTypeInt4;
		}
		else if (type == GL_UNSIGNED_INT)
		{
			if (isArray)
				return GraphicsUniformType::GraphicsUniformTypeUIntArray;
			else
				return GraphicsUniformType::GraphicsUniformTypeUInt;
		}
		else if (type == GL_UNSIGNED_INT_VEC2)
		{
			if (isArray)
				return GraphicsUniformType::GraphicsUniformTypeUInt2Array;
			else
				return GraphicsUniformType::GraphicsUniformTypeUInt2;
		}
		else if (type == GL_UNSIGNED_INT_VEC3)
		{
			if (isArray)
				return GraphicsUniformType::GraphicsUniformTypeUInt3Array;
			else
				return GraphicsUniformType::GraphicsUniformTypeUInt3;
		}
		else if (type == GL_UNSIGNED_INT_VEC4)
		{
			if (isArray)
				return GraphicsUniformType::GraphicsUniformTypeUInt4Array;
			else
				return GraphicsUniformType::GraphicsUniformTypeUInt4;
		}
		else if (type == GL_FLOAT)
		{
			if (isArray)
				return GraphicsUniformType::GraphicsUniformTypeFloatArray;
			else
				return GraphicsUniformType::GraphicsUniformTypeFloat;
		}
		else if (type == GL_FLOAT_VEC2)
		{
			if (isArray)
				return GraphicsUniformType::GraphicsUniformTypeFloat2Array;
			else
				return GraphicsUniformType::GraphicsUniformTypeFloat2;
		}
		else if (type == GL_FLOAT_VEC3)
		{
			if (isArray)
				return GraphicsUniformType::GraphicsUniformTypeFloat3Array;
			else
				return GraphicsUniformType::GraphicsUniformTypeFloat3;
		}
		else if (type == GL_FLOAT_VEC4)
		{
			if (isArray)
				return GraphicsUniformType::GraphicsUniformTypeFloat4Array;
			else
				return GraphicsUniformType::GraphicsUniformTypeFloat4;
		}
		else if (type == GL_FLOAT_MAT2)
		{
			if (isArray)
				return GraphicsUniformType::GraphicsUniformTypeFloat2x2Array;
			else
				return GraphicsUniformType::GraphicsUniformTypeFloat2x2;
		}
		else if (type == GL_FLOAT_MAT3)
		{
			if (isArray)
				return GraphicsUniformType::GraphicsUniformTypeFloat3x3Array;
			else
				return GraphicsUniformType::GraphicsUniformTypeFloat3x3;
		}
		else if (type == GL_FLOAT_MAT4)
		{
			if (isArray)
				return GraphicsUniformType::GraphicsUniformTypeFloat4x4Array;
			else
				return GraphicsUniformType::GraphicsUniformTypeFloat4x4;
		}
		else
		{
			VK_PLATFORM_ASSERT(false, "Invlid uniform type");
			return GraphicsUniformType::GraphicsUniformTypeNone;
		}
	}
}

const GraphicsProgramDesc&
VulkanProgram::getGraphicsProgramDesc() const noexcept
{
	return _programDesc;
}

void
VulkanProgram::setDevice(GraphicsDevicePtr device) noexcept
{
	_device = device;
}

GraphicsDevicePtr
VulkanProgram::getDevice() noexcept
{
	return _device.lock();
}

_NAME_END