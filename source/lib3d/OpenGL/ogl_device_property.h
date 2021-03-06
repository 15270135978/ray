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
#ifndef _H_OGL_DEVICE_PROPERTY_H_
#define _H_OGL_DEVICE_PROPERTY_H_

#include "ogl_types.h"

_NAME_BEGIN

class OGLDeviceProperty final : public GraphicsDeviceProperty
{
public:
	OGLDeviceProperty() noexcept;
	~OGLDeviceProperty() noexcept;

	bool setup() noexcept;
	void close() noexcept;

	void setDevice(const GraphicsDevicePtr& device) noexcept;
	GraphicsDevicePtr getDevice() noexcept;

	const GraphicsDeviceProperties& getGraphicsDeviceProperties() const noexcept;

private:
#if defined(_BUILD_PLATFORM_WINDOWS)
	struct CreateParam
	{
		HWND hwnd;
		HDC hdc;
		HINSTANCE hinstance;
		HGLRC context;

		CreateParam()
			: hwnd(nullptr)
			, hdc(nullptr)
			, hinstance(nullptr)
			, context(nullptr)
		{
		}
	};
#elif defined(_BUILD_PLATFORM_LINUX)
	struct CreateParam
	{
		Display* dpy;
		XVisualInfo* vi;
		GLXContext ctx;
		Colormap cmap;
		Window wnd;
		GLXFBConfig* config;

		CreateParam()
			: dpy(nullptr)
			, vi(nullptr)
			, ctx(nullptr)
			, cmap(0)
			, wnd(0)
			, config(0)
		{
		}
	};
#elif defined(_BUILD_PLATFORM_APPLE)
	struct CreateParam
	{
		CGLContextObj ctx;
		CGLContextObj octx;

		CreateParam()
			: ctx(nullptr)
			, ctx(nullptr)
		{
		}
	};
#endif

private:
	bool setupGLEnvironment(CreateParam& param) noexcept;
	void closeGLEnvironment(const CreateParam& param) noexcept;

	bool initDeviceProperties() noexcept;

	bool initTextureSupports() noexcept;
	bool initTextureDimSupports() noexcept;
	bool initVertexSupports() noexcept;
	bool initShaderSupports() noexcept;

private:
	OGLDeviceProperty(const OGLDeviceProperty&) = delete;
	OGLDeviceProperty& operator=(const OGLDeviceProperty&) = delete;

private:
	GraphicsDeviceWeakPtr _device;
	GraphicsDeviceProperties _deviceProperties;
};

_NAME_END

#endif