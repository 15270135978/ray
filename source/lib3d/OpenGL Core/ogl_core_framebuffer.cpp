// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2014.
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
#include "ogl_core_framebuffer.h"
#include "ogl_core_texture.h"
#include "ogl_framebuffer.h"
#include "ogl_device.h"

_NAME_BEGIN

__ImplementSubClass(OGLCoreFramebuffer, GraphicsFramebuffer, "OGLCoreFramebuffer")

OGLCoreFramebuffer::OGLCoreFramebuffer() noexcept
	: _fbo(GL_NONE)
{
}

OGLCoreFramebuffer::~OGLCoreFramebuffer() noexcept
{
	this->close();
}

bool
OGLCoreFramebuffer::setup(const GraphicsFramebufferDesc& framebufferDesc) noexcept
{
	assert(GL_NONE == _fbo);
	assert(framebufferDesc.getGraphicsFramebufferLayout());
	assert(framebufferDesc.getGraphicsFramebufferLayout()->isInstanceOf<OGLFramebufferLayout>());
	assert(framebufferDesc.getWidth() > 0 && framebufferDesc.getHeight() > 0);

	glCreateFramebuffers(1, &_fbo);
	if (_fbo == GL_NONE)
	{
		this->getDevice()->downcast<OGLDevice>()->message("glCreateFramebuffers() fail");
		return false;
	}

	GLenum drawCount = 0;
	GLenum drawBuffers[GL_COLOR_ATTACHMENT15 - GL_COLOR_ATTACHMENT0];

	const auto& textureComponents = framebufferDesc.getGraphicsFramebufferLayout()->getGraphicsFramebufferLayoutDesc().getComponents();
	const auto& colorAttachments = framebufferDesc.getColorAttachments();
	if (colorAttachments.size() > (sizeof(drawBuffers) / sizeof(drawBuffers[0])))
	{
		this->getDevice()->downcast<OGLDevice>()->message("The color attachment in framebuffer is out of range.");
		return false;
	}

	for (std::size_t i = 0; i < textureComponents.size(); i++)
	{
		auto type = textureComponents[i].getAttachType();
		switch (type)
		{
		case GraphicsImageLayout::GraphicsImageLayoutGeneral:
			break;
		case GraphicsImageLayout::GraphicsImageLayoutColorAttachmentOptimal:
		{
			GLint slot = GL_COLOR_ATTACHMENT0 + textureComponents[i].getAttachSlot();
			GLint mipLevel = colorAttachments[drawCount].getBindingLevel();
			GLint layer = colorAttachments[drawCount].getBindingLayer();

			if (!this->bindRenderTexture(colorAttachments[drawCount].getBindingTexture(), slot, mipLevel, layer))
				return false;

			drawBuffers[drawCount++] = slot;
		}
		break;
		case GraphicsImageLayout::GraphicsImageLayoutDepthStencilAttachmentOptimal:
		case GraphicsImageLayout::GraphicsImageLayoutDepthStencilReadOnlyOptimal:
		{
			const auto& depthStencilAttachment = framebufferDesc.getDepthStencilAttachment();
			if (!depthStencilAttachment.getBindingTexture())
			{
				this->getDevice()->downcast<OGLDevice>()->message("Need depth or stencil texture.");
				return false;
			}

			auto texture = depthStencilAttachment.getBindingTexture();
			auto format = texture->getGraphicsTextureDesc().getTexFormat();
			auto level = depthStencilAttachment.getBindingLevel();
			auto layer = depthStencilAttachment.getBindingLayer();

			if (OGLTypes::isDepthStencilFormat(format))
			{
				if (!this->bindRenderTexture(texture, GL_DEPTH_STENCIL_ATTACHMENT, level, layer))
					return false;
			}
			else if (OGLTypes::isDepthFormat(format))
			{
				if (!this->bindRenderTexture(texture, GL_DEPTH_ATTACHMENT, level, layer))
					return false;
			}
			else if (OGLTypes::isStencilFormat(format))
			{
				if (!this->bindRenderTexture(texture, GL_STENCIL_ATTACHMENT, level, layer))
					return false;
			}
			else
			{
				this->getDevice()->downcast<OGLDevice>()->message("Invalid texture format");
				return false;
			}
		}
		case GraphicsImageLayout::GraphicsImageLayoutShaderReadOnlyOptimal:
			break;
		case GraphicsImageLayout::GraphicsImageLayoutTransferSrcOptimal:
			break;
		case GraphicsImageLayout::GraphicsImageLayoutTransferDstOptimal:
			break;
		case GraphicsImageLayout::GraphicsImageLayoutPreinitialized:
			break;
		case GraphicsImageLayout::GraphicsImageLayoutPresentSrcKhr:
			break;
		default:
			break;
		}
	}

	glNamedFramebufferDrawBuffers(_fbo, drawCount, drawBuffers);

	_framebufferDesc = framebufferDesc;
	return OGLCheck::checkError();
}

void
OGLCoreFramebuffer::close() noexcept
{
	if (_fbo != GL_NONE)
	{
		glDeleteFramebuffers(1, &_fbo);
		_fbo = GL_NONE;
	}
}

GLuint
OGLCoreFramebuffer::getInstanceID() noexcept
{
	return _fbo;
}

bool
OGLCoreFramebuffer::bindRenderTexture(GraphicsTexturePtr renderTexture, GLenum attachment, GLint level, GLint layer) noexcept
{
	assert(renderTexture);

	auto texture = renderTexture->downcast<OGLCoreTexture>();
	auto textureID = texture->getInstanceID();
	auto& textureDesc = renderTexture->getGraphicsTextureDesc();

	if (textureDesc.getTexDim() == GraphicsTextureDim::GraphicsTextureDim2DArray ||
		textureDesc.getTexDim() == GraphicsTextureDim::GraphicsTextureDimCube ||
		textureDesc.getTexDim() == GraphicsTextureDim::GraphicsTextureDimCubeArray)
	{
		glNamedFramebufferTextureLayer(_fbo, attachment, textureID, level, layer);
	}
	else
	{
		glNamedFramebufferTexture(_fbo, attachment, textureID, level);
	}

	return OGLCheck::checkError();
}

const GraphicsFramebufferDesc&
OGLCoreFramebuffer::getGraphicsFramebufferDesc() const noexcept
{
	return _framebufferDesc;
}

void
OGLCoreFramebuffer::setDevice(const GraphicsDevicePtr& device) noexcept
{
	_device = device;
}

GraphicsDevicePtr
OGLCoreFramebuffer::getDevice() noexcept
{
	return _device.lock();
}

_NAME_END