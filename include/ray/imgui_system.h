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
#ifndef _H_IMGUI_SYSTEM_H_
#define _H_IMGUI_SYSTEM_H_

#include <ray/gui_system.h>
#include <ray/render_types.h>

_NAME_BEGIN

class EXPORT IMGUISystem final : public GuiSystem
{
	__DeclareSingleton(IMGUISystem)
public:
	IMGUISystem() noexcept;
	~IMGUISystem() noexcept;

	bool open() except;
	void close() noexcept;

	bool injectMouseMove(int _absx, int _absy, int _absz) noexcept;
	bool injectMousePress(int _absx, int _absy, GuiInputButton::Code _id) noexcept;
	bool injectMouseRelease(int _absx, int _absy, GuiInputButton::Code _id) noexcept;
	bool injectKeyPress(GuiInputKey::Code _key, GuiInputChar _char) noexcept;
	bool injectKeyRelease(GuiInputKey::Code _key) noexcept;

	bool isFocusMouse() const noexcept;
	bool isFocusKey() const noexcept;
	bool isCaptureMouse() const noexcept;

	void setViewport(std::uint32_t w, std::uint32_t h) noexcept;
	void getViewport(std::uint32_t& w, std::uint32_t& h) noexcept;

	void setFramebufferScale(std::uint32_t w, std::uint32_t h) noexcept;
	void getFramebufferScale(std::uint32_t& w, std::uint32_t& h) noexcept;

	GuiWidgetPtr createWidget(const rtti::Rtti* rtti);
	template<typename T>
	typename std::enable_if<std::is_base_of<GuiWidget, T>::value, std::shared_ptr<T>>::type createWidget()
	{
		return std::dynamic_pointer_cast<T>(this->createWidget(T::getRtti()));
	}

	void render(float delta) except;

private:
	IMGUISystem(const IMGUISystem&) noexcept = delete;
	IMGUISystem& operator=(const IMGUISystem&) noexcept = delete;

private:
	MaterialPtr _material;
	MaterialTechPtr _materialTech;
	MaterialParamPtr _materialDecal;
	MaterialParamPtr _materialProj;

	GraphicsDataPtr _vbo;
	GraphicsDataPtr _ibo;
	GraphicsTexturePtr _texture;
};

_NAME_END

#endif