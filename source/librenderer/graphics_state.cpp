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
#include <ray/graphics_state.h>

_NAME_BEGIN

__ImplementSubInterface(GraphicsState, GraphicsChild, "GraphicsState")

RenderBlendState::RenderBlendState() noexcept
	: blendEnable(false)
	, blendSeparateEnable(false)
	, blendOp(BlendOperation::Add)
	, blendSrc(BlendFactor::SrcAlpha)
	, blendDest(BlendFactor::OneMinusSrcAlpha)
	, blendAlphaOp(BlendOperation::Add)
	, blendAlphaSrc(BlendFactor::SrcAlpha)
	, blendAlphaDest(BlendFactor::OneMinusSrcAlpha)
	, colorWriteMask(ColorMask::COLORMASK_RGBA)
{
}

RenderRasterState::RenderRasterState() noexcept
	: cullMode(CullMode::Back)
	, fillMode(FillMode::SolidMode)
	, primitiveType(VertexType::Triangle)
	, scissorTestEnable(false)
	, srgbEnable(false)
	, multisampleEnable(false)
{
}

RenderDepthState::RenderDepthState() noexcept
	: depthEnable(true)
	, depthWriteMask(true)
	, depthFunc(CompareFunction::Lequal)
	, depthBiasEnable(false)
	, depthSlopScaleBias(0)
	, depthBias(0)
{
}

RenderStencilState::RenderStencilState() noexcept
	: stencilEnable(false)
	, stencilRef(0)
	, stencilFunc(CompareFunction::Always)
	, stencilReadMask(0xFFFFFFFF)
	, stencilWriteMask(0xFFFFFFFF)
	, stencilFail(StencilOperation::Keep)
	, stencilZFail(StencilOperation::Keep)
	, stencilPass(StencilOperation::Keep)
	, stencilTwoEnable(false)
	, stencilTwoFunc(CompareFunction::Always)
	, stencilTwoReadMask(0xFFFFFFFF)
	, stencilTwoWriteMask(0xFFFFFFFF)
	, stencilTwoFail(StencilOperation::Keep)
	, stencilTwoZFail(StencilOperation::Keep)
	, stencilTwoPass(StencilOperation::Keep)
{
}

GraphicsStateDesc::GraphicsStateDesc() noexcept
{
}

GraphicsStateDesc::~GraphicsStateDesc() noexcept
{
}

void
GraphicsStateDesc::setBlendState(const RenderBlendState& state) noexcept
{
	_blendState = state;
}

void
GraphicsStateDesc::setRasterState(const RenderRasterState& state) noexcept
{
	_rasterState = state;
}

void
GraphicsStateDesc::setDepthState(const RenderDepthState& state) noexcept
{
	_depthState = state;
}

void
GraphicsStateDesc::setStencilState(const RenderStencilState& state) noexcept
{
	_stencilState = state;
}

RenderBlendState&
GraphicsStateDesc::getBlendState() noexcept
{
	return _blendState;
}

RenderRasterState&
GraphicsStateDesc::getRasterState() noexcept
{
	return _rasterState;
}

RenderDepthState&
GraphicsStateDesc::getDepthState() noexcept
{
	return _depthState;
}

RenderStencilState&
GraphicsStateDesc::getStencilState() noexcept
{
	return _stencilState;
}

const RenderBlendState&
GraphicsStateDesc::getBlendState() const noexcept
{
	return _blendState;
}

const RenderRasterState&
GraphicsStateDesc::getRasterState() const noexcept
{
	return _rasterState;
}

const RenderDepthState&
GraphicsStateDesc::getDepthState() const noexcept
{
	return _depthState;
}

const RenderStencilState&
GraphicsStateDesc::getStencilState() const noexcept
{
	return _stencilState;
}

GraphicsState::GraphicsState() noexcept
{
}

GraphicsState::~GraphicsState() noexcept
{
}

_NAME_END