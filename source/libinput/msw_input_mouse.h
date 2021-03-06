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
#ifndef _H_MSW_INPUT_MOUSE_H_
#define _H_MSW_INPUT_MOUSE_H_

#include <ray/input_mouse.h>

_NAME_BEGIN

class EXPORT MSWInputMouse final : public DefaultInputMouse
{
	__DeclareSubClass(MSWInputMouse, DefaultInputMouse)
public:
	MSWInputMouse() noexcept;
	MSWInputMouse(CaptureObject window) noexcept;
	~MSWInputMouse() noexcept;

	InputMousePtr clone() const noexcept;

	void getPosition(InputButton::mouse_t& x, InputButton::mouse_t& y) const noexcept;

	bool isButtonDown(InputButton::Code key) const noexcept;
	bool isButtonUp(InputButton::Code key) const noexcept;
	bool isButtonPressed(InputButton::Code key) const noexcept;

private:
	void onShowMouse() noexcept;
	void onHideMouse() noexcept;

	void onChangePosition(InputButton::mouse_t x, InputButton::mouse_t y) noexcept;

	void onInputEvent(const InputEvent& event) noexcept;

private:
	MSWInputMouse(const MSWInputMouse&) = delete;
	MSWInputMouse& operator=(const MSWInputMouse&) = delete;

private:
	bool _focusWindow;
	CaptureObject _window;
};

_NAME_END

#endif