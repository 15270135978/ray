// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2017.
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
#ifndef _H_RENDER_PIPELINE_FRAMEBUFFER_H_
#define _H_RENDER_PIPELINE_FRAMEBUFFER_H_

#include <ray/render_types.h>

_NAME_BEGIN

class EXPORT RenderPipelineFramebuffer : public rtti::Interface
{
	__DeclareSubInterface(RenderPipelineController, rtti::Interface)
public:
	RenderPipelineFramebuffer() noexcept;
	RenderPipelineFramebuffer(const GraphicsFramebufferPtr& framebuffer) noexcept;
	virtual ~RenderPipelineFramebuffer() noexcept;

	virtual void setFramebuffer(GraphicsFramebufferPtr&& texture) noexcept;
	virtual void setFramebuffer(const GraphicsFramebufferPtr& texture) noexcept;
	virtual const GraphicsFramebufferPtr& getFramebuffer() const noexcept;

protected:
	virtual void onResolutionChange() noexcept;
	virtual void onResolutionChangeDPI() noexcept;

	virtual void onRenderBefore() noexcept;
	virtual void onRenderPipeline(const CameraPtr& camera) noexcept;
	virtual void onRenderAfter() noexcept;

private:
	RenderPipelineFramebuffer(const RenderPipelineFramebuffer&) noexcept = delete;
	RenderPipelineFramebuffer& operator=(const RenderPipelineFramebuffer&) noexcept = delete;

private:
	GraphicsFramebufferPtr _framebuffer;
};

_NAME_END

#endif