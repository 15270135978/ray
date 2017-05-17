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
#include <ray/imgui.h>
#include <imgui.h>

_NAME_BEGIN

float2 ImVec2ToFloat2(ImVec2 vec2)
{
	return float2(vec2.x, vec2.y);
}

float4 ImVec4ToFloat4(ImVec4 vec4)
{
	return float4(vec4.x, vec4.y, vec4.z, vec4.w);
}

GuiStyle::GuiStyle() noexcept
{
}

IMGUI::IMGUI() noexcept
{
}

IMGUI::~IMGUI() noexcept
{
}

void
IMGUI::newFrame() noexcept
{
	ImGui::NewFrame();
}

void
IMGUI::render() noexcept
{
	ImGui::Render();
}

void
IMGUI::shutdown() noexcept
{
	ImGui::Shutdown();
}

void
IMGUI::showUserGuide() noexcept
{
	ImGui::ShowUserGuide();
}

void
IMGUI::showStyleEditor(GuiStyle* ref) noexcept
{
	ImGui::ShowStyleEditor();
}

void
IMGUI::showTestWindow(bool* isOpened) noexcept
{
	if (!isOpened)
		ImGui::ShowTestWindow();
	else
		ImGui::ShowTestWindow(isOpened);
}

void
IMGUI::showMetricsWindow(bool* isOpened) noexcept
{
	if (!isOpened)
		ImGui::ShowMetricsWindow();
	else
		ImGui::ShowMetricsWindow(isOpened);
}

bool
IMGUI::begin(const char* name, bool* isOpened, GuiWindowFlags flags) noexcept
{
	return ImGui::Begin(name, isOpened, flags);
}

bool
IMGUI::begin(const char* name, bool* isOpened, const float2& size_on_first_use, float alpha, GuiWindowFlags flags) noexcept
{
	return ImGui::Begin(name, isOpened, (const ImVec2&)size_on_first_use, alpha, flags);
}

void
IMGUI::end() noexcept
{
	ImGui::End();
}

bool
IMGUI::beginChild(const char* str_id, const float2& size, bool border, GuiWindowFlags extraFlags) noexcept
{
	return ImGui::BeginChild(str_id, (ImVec2&)size, border, extraFlags);
}

bool
IMGUI::beginChild(GuiID id, const float2& size, bool border, GuiWindowFlags extraFlags) noexcept
{
	return ImGui::BeginChild((ImGuiID)id, (ImVec2&)size, border, extraFlags);
}

void
IMGUI::endChild() noexcept
{
	return ImGui::EndChild();
}

float2
IMGUI::getContentRegionMax() noexcept
{
	return ImVec2ToFloat2(ImGui::GetContentRegionMax());
}

float2
IMGUI::getContentRegionAvail() noexcept
{
	return ImVec2ToFloat2(ImGui::GetContentRegionAvail());
}

float
IMGUI::getContentRegionAvailWidth() noexcept
{
	return ImGui::GetContentRegionAvailWidth();
}

float2
IMGUI::getWindowContentRegionMin() noexcept
{
	return ImVec2ToFloat2(ImGui::GetWindowContentRegionMin());
}

float2
IMGUI::getWindowContentRegionMax() noexcept
{
	return ImVec2ToFloat2(ImGui::GetWindowContentRegionMax());
}

float
IMGUI::getWindowContentRegionWidth() noexcept
{
	return ImGui::GetWindowContentRegionWidth();
}

float2
IMGUI::getWindowPos() noexcept
{
	return ImVec2ToFloat2(ImGui::GetWindowPos());
}

float2
IMGUI::getWindowSize() noexcept
{
	return ImVec2ToFloat2(ImGui::GetWindowSize());
}

float
IMGUI::getWindowWidth() noexcept
{
	return ImGui::GetWindowWidth();
}

float
IMGUI::getWindowHeight() noexcept
{
	return ImGui::GetWindowHeight();
}

bool
IMGUI::isWindowCollapsed() noexcept
{
	return ImGui::IsWindowCollapsed();
}

void
IMGUI::setWindowFontScale(float scale) noexcept
{
	ImGui::SetWindowFontScale(scale);
}

void
IMGUI::setNextWindowPos(const float2& pos, GuiSetCondFlags cond) noexcept
{
	ImGui::SetNextWindowPos((const ImVec2&)pos, cond);
}

void
IMGUI::setNextWindowPosCenter(GuiSetCondFlags cond) noexcept
{
	ImGui::SetNextWindowPosCenter(cond);
}

void
IMGUI::setNextWindowSize(const float2& size, GuiSetCondFlags cond) noexcept
{
	ImGui::SetNextWindowSize((const ImVec2&)size);
}

void
IMGUI::setNextWindowSizeConstraints(const float2& min, const float2& max) noexcept
{
	ImGui::SetNextWindowSizeConstraints((const ImVec2&)min, (const ImVec2&)max);
}

void
IMGUI::setNextWindowContentSize(const float2& size) noexcept
{
	ImGui::SetNextWindowContentSize((const ImVec2&)size);
}

void
IMGUI::setNextWindowContentWidth(float width) noexcept
{
	ImGui::SetNextWindowContentWidth(width);
}

void
IMGUI::setNextWindowCollapsed(bool collapsed, GuiSetCondFlags cond) noexcept
{
	ImGui::SetNextWindowCollapsed(collapsed, cond);
}

void
IMGUI::setNextWindowFocus() noexcept
{
	ImGui::SetNextWindowFocus();
}

void
IMGUI::setWindowPos(const float2& pos, GuiSetCondFlags cond) noexcept
{
	ImGui::SetWindowPos((const ImVec2&)pos, cond);
}

void
IMGUI::setWindowSize(const float2& size, GuiSetCondFlags cond) noexcept
{
	ImGui::SetWindowSize((const ImVec2&)size, cond);
}

void
IMGUI::setWindowCollapsed(bool collapsed, GuiSetCondFlags cond) noexcept
{
	ImGui::SetWindowCollapsed(collapsed, cond);
}

void
IMGUI::setWindowFocus() noexcept
{
	ImGui::SetWindowFocus();
}

void
IMGUI::setWindowPos(const char* name, const float2& pos, GuiSetCondFlags cond) noexcept
{
	ImGui::SetWindowPos(name, (const ImVec2&)pos, cond);
}

void
IMGUI::setWindowSize(const char* name, const float2& size, GuiSetCondFlags cond) noexcept
{
	ImGui::SetWindowSize(name, (const ImVec2&)size, cond);
}

void
IMGUI::setWindowCollapsed(const char* name, bool collapsed, GuiSetCondFlags cond) noexcept
{
	ImGui::SetWindowCollapsed(name, collapsed, cond);
}

void
IMGUI::setWindowFocus(const char* name) noexcept
{
	ImGui::SetWindowFocus();
}

float
IMGUI::getScrollX() noexcept
{
	return ImGui::GetScrollX();
}

float
IMGUI::getScrollY() noexcept
{
	return ImGui::GetScrollY();
}

float
IMGUI::getScrollMaxX() noexcept
{
	return ImGui::GetScrollMaxX();
}

float
IMGUI::getScrollMaxY() noexcept
{
	return ImGui::GetScrollMaxY();
}

void
IMGUI::setScrollX(float scroll_x) noexcept
{
	ImGui::SetScrollX(scroll_x);
}

void
IMGUI::setScrollY(float scroll_y) noexcept
{
	ImGui::SetScrollY(scroll_y);
}

void
IMGUI::setScrollHere(float center_y_ratio) noexcept
{
	ImGui::SetScrollHere(center_y_ratio);
}

void
IMGUI::setScrollFromPosY(float pos_y, float center_y_ratio) noexcept
{
	ImGui::SetScrollFromPosY(pos_y, center_y_ratio);
}

void
IMGUI::setKeyboardFocusHere(int offset) noexcept
{
	ImGui::SetKeyboardFocusHere(offset);
}

void
IMGUI::pushStyleColor(GuiCol idx, const float4& col) noexcept
{
	ImGui::PushStyleColor(idx, (ImVec4&)col);
}

void
IMGUI::popStyleColor(int count) noexcept
{
	ImGui::PopStyleColor(count);
}

void
IMGUI::pushStyleVar(GuiStyleVar idx, float val) noexcept
{
	ImGui::PushStyleVar(idx, val);
}

void
IMGUI::pushStyleVar(GuiStyleVar idx, const float2& val) noexcept
{
	ImGui::PushStyleVar(idx, (ImVec2&)val);
}

void
IMGUI::popStyleVar(int count) noexcept
{
	ImGui::PopStyleVar(count);
}

float
IMGUI::getFontSize() noexcept
{
	return ImGui::GetFontSize();
}

float2
IMGUI::getFontTexUvWhitePixel() noexcept
{
	return ImVec2ToFloat2(ImGui::GetFontTexUvWhitePixel());
}

std::uint32_t
IMGUI::getColorU32(GuiCol idx, float alpha_mul) noexcept
{
	return ImGui::GetColorU32(idx, alpha_mul);
}

std::uint32_t
IMGUI::getColorU32(const float4& col) noexcept
{
	return ImGui::GetColorU32((ImVec4&)col);
}

void
IMGUI::pushItemWidth(float item_width) noexcept
{
	ImGui::PushItemWidth(item_width);
}

void
IMGUI::popItemWidth() noexcept
{
	ImGui::PopItemWidth();
}

float
IMGUI::calcItemWidth() noexcept
{
	return ImGui::CalcItemWidth();
}

void
IMGUI::pushTextWrapPos(float wrap_pos_x) noexcept
{
	ImGui::PushTextWrapPos();
}

void
IMGUI::popTextWrapPos() noexcept
{
	ImGui::PopTextWrapPos();
}

void
IMGUI::pushAllowKeyboardFocus(bool v) noexcept
{
	ImGui::PushAllowKeyboardFocus(v);
}

void
IMGUI::popAllowKeyboardFocus() noexcept
{
	ImGui::PopAllowKeyboardFocus();
}

void
IMGUI::pushButtonRepeat(bool repeat) noexcept
{
	ImGui::PushButtonRepeat(repeat);
}

void
IMGUI::popButtonRepeat() noexcept
{
	ImGui::PopButtonRepeat();
}

void
IMGUI::separator() noexcept
{
	ImGui::Separator();
}

void
IMGUI::sameLine(float pos_x, float spacing_w) noexcept
{
	ImGui::SameLine(pos_x, spacing_w);
}

void
IMGUI::newLine() noexcept
{
	ImGui::NewLine();
}

void
IMGUI::spacing() noexcept
{
	ImGui::Spacing();
}

void
IMGUI::dummy(const float2& size) noexcept
{
	ImGui::Dummy((ImVec2&)size);
}

void
IMGUI::indent(float indent_w) noexcept
{
	ImGui::Indent(indent_w);
}

void
IMGUI::unindent(float indent_w) noexcept
{
	ImGui::Unindent(indent_w);
}

void
IMGUI::beginGroup() noexcept
{
	ImGui::BeginGroup();
}

void
IMGUI::endGroup() noexcept
{
	ImGui::EndGroup();
}

float2
IMGUI::getCursorPos() noexcept
{
	return ImVec2ToFloat2(ImGui::GetCursorPos());
}

float
IMGUI::getCursorPosX() noexcept
{
	return ImGui::GetCursorPosX();
}

float
IMGUI::getCursorPosY() noexcept
{
	return ImGui::GetCursorPosY();
}

void
IMGUI::setCursorPos(const float2& local_pos) noexcept
{
	ImGui::SetCursorPos((ImVec2&)local_pos);
}

void
IMGUI::setCursorPosX(float x) noexcept
{
	ImGui::SetCursorPosX(x);
}

void
IMGUI::setCursorPosY(float y) noexcept
{
	ImGui::SetCursorPosY(y);
}

float2
IMGUI::getCursorStartPos() noexcept
{
	return ImVec2ToFloat2(ImGui::GetCursorStartPos());
}

float2
IMGUI::getCursorScreenPos() noexcept
{
	return ImVec2ToFloat2(ImGui::GetCursorScreenPos());
}

void
IMGUI::setCursorScreenPos(const float2& pos) noexcept
{
	return ImGui::SetCursorScreenPos((ImVec2&)pos);
}

void
IMGUI::alignFirstTextHeightToWidgets() noexcept
{
	ImGui::AlignFirstTextHeightToWidgets();
}

float
IMGUI::getTextLineHeight() noexcept
{
	return ImGui::GetTextLineHeight();
}

float
IMGUI::getTextLineHeightWithSpacing() noexcept
{
	return ImGui::GetTextLineHeightWithSpacing();
}

float
IMGUI::getItemsLineHeightWithSpacing() noexcept
{
	return ImGui::GetItemsLineHeightWithSpacing();
}

void
IMGUI::columns(int count, const char* id, bool border) noexcept
{
	ImGui::Columns(count, id, border);
}

void
IMGUI::pushID(const char* str_id_begin, const char* str_id_end) noexcept
{
	ImGui::PushID(str_id_begin, str_id_end);
}

void
IMGUI::pushID(const void* ptr_id) noexcept
{
	ImGui::PushID(ptr_id);
}

void
IMGUI::pushID(int int_id) noexcept
{
	ImGui::PushID(int_id);
}

void
IMGUI::popID() noexcept
{
	ImGui::PopID();
}

GuiID
IMGUI::getID(const char* str_id) noexcept
{
	return ImGui::GetID(str_id);
}

GuiID
IMGUI::getID(const char* str_id_begin, const char* str_id_end) noexcept
{
	return ImGui::GetID(str_id_begin, str_id_end);
}

GuiID
IMGUI::getID(const void* ptr_id) noexcept
{
	return ImGui::GetID(ptr_id);
}

void
IMGUI::text(const char* fmt, ...) noexcept
{
	va_list args;
	va_start(args, fmt);
	ImGui::TextV(fmt, args);
	va_end(args);
}

void
IMGUI::textV(const char* fmt, va_list args) noexcept
{
	ImGui::TextV(fmt, args);
}

void
IMGUI::textColored(const float4& col, const char* fmt, ...) noexcept
{
	va_list args;
	va_start(args, fmt);
	ImGui::TextColoredV((ImVec4&)col, fmt, args);
	va_end(args);
}

void
IMGUI::textColoredV(const float4& col, const char* fmt, va_list args) noexcept
{
	ImGui::TextColoredV((ImVec4&)col, fmt, args);
}

void
IMGUI::textDisabled(const char* fmt, ...) noexcept
{
	va_list args;
	va_start(args, fmt);
	ImGui::TextDisabledV(fmt, args);
	va_end(args);
}

void
IMGUI::textDisabledV(const char* fmt, va_list args) noexcept
{
	ImGui::TextDisabledV(fmt, args);
}

void
IMGUI::textWrapped(const char* fmt, ...) noexcept
{
	va_list args;
	va_start(args, fmt);
	ImGui::TextWrappedV(fmt, args);
	va_end(args);
}

void
IMGUI::textWrappedV(const char* fmt, va_list args) noexcept
{
	ImGui::TextWrappedV(fmt, args);
}

void
IMGUI::textUnformatted(const char* text, const char* text_end) noexcept
{
	ImGui::TextUnformatted(text, text_end);
}

void
IMGUI::labelText(const char* label, const char* fmt, ...) noexcept
{
	va_list args;
	va_start(args, fmt);
	ImGui::LabelTextV(label, fmt, args);
	va_end(args);
}

void
IMGUI::labelTextV(const char* label, const char* fmt, va_list args) noexcept
{
	ImGui::LabelTextV(label, fmt, args);
}

void
IMGUI::bullet() noexcept
{
	ImGui::Bullet();
}

void
IMGUI::bulletText(const char* fmt, ...) noexcept
{
	va_list args;
	va_start(args, fmt);
	ImGui::BulletTextV(fmt, args);
	va_end(args);
}

void
IMGUI::bulletTextV(const char* fmt, va_list args) noexcept
{
	ImGui::BulletTextV(fmt, args);
}

bool
IMGUI::button(const char* label, const float2& size) noexcept
{
	return ImGui::Button(label, (ImVec2&)size);
}

bool
IMGUI::smallButton(const char* label) noexcept
{
	return ImGui::SmallButton(label);
}

bool
IMGUI::invisibleButton(const char* str_id, const float2& size) noexcept
{
	return ImGui::InvisibleButton(str_id, (ImVec2&)size);
}

void
IMGUI::image(GuiTextureID user_texture_id, const float2& size, const float2& uv0, const float2& uv1, const float4& tint_col, const float4& border_col) noexcept
{
	ImGui::Image(user_texture_id, (ImVec2&)size, (ImVec2&)uv0, (ImVec2&)uv1, (ImVec4&)tint_col, (ImVec4&)border_col);
}

bool
IMGUI::imageButton(GuiTextureID user_texture_id, const float2& size, const float2& uv0, const float2& uv1, int frame_padding, const float4& bg_col, const float4& tint_col) noexcept
{
	return ImGui::ImageButton(user_texture_id, (ImVec2&)size, (ImVec2&)uv0, (ImVec2&)uv1, frame_padding, (ImVec4&)bg_col, (ImVec4&)tint_col);
}

bool
IMGUI::checkbox(const char* label, bool* v) noexcept
{
	return ImGui::Checkbox(label, v);
}

bool
IMGUI::checkboxFlags(const char* label, unsigned int* flags, unsigned int flags_value) noexcept
{
	return ImGui::CheckboxFlags(label, flags, flags_value);
}

bool
IMGUI::radioButton(const char* label, bool active) noexcept
{
	return ImGui::RadioButton(label, active);
}

bool
IMGUI::radioButton(const char* label, int* v, int v_button) noexcept
{
	return ImGui::RadioButton(label, v, v_button);
}

bool
IMGUI::combo(const char* label, int* current_item, const char** items, int items_count, int height_in_items) noexcept
{
	return ImGui::Combo(label, current_item, items, items_count, height_in_items);
}

bool
IMGUI::combo(const char* label, int* current_item, const char* items_separated_by_zeros, int height_in_items) noexcept
{
	return ImGui::Combo(label, current_item, items_separated_by_zeros, height_in_items);
}

bool
IMGUI::combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items) noexcept
{
	return ImGui::Combo(label, current_item, items_getter, data, items_count, height_in_items);
}

bool
IMGUI::colorButton(const float4& col, bool small_height, bool outline_border) noexcept
{
	return ImGui::ColorButton((ImVec4&)col, small_height, outline_border);
}

bool
IMGUI::colorEdit3(const char* label, float col[3]) noexcept
{
	return ImGui::ColorEdit3(label, col);
}

bool
IMGUI::colorEdit4(const char* label, float col[4], bool show_alpha) noexcept
{
	return ImGui::ColorEdit4(label, col, show_alpha);
}

void
IMGUI::colorEditMode(GuiColorEditMode mode) noexcept
{
	ImGui::ColorEditMode(mode);
}

void
IMGUI::plotLines(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, const float2& graph_size, int stride) noexcept
{
	ImGui::PlotLines(label, values, values_count, values_offset, overlay_text, scale_min, scale_max, (ImVec2&)graph_size, stride);
}

void
IMGUI::plotLines(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, const float2& graph_size) noexcept
{
	ImGui::PlotLines(label, values_getter, data, values_count, values_offset, overlay_text, scale_min, scale_max, (ImVec2&)graph_size);
}

void
IMGUI::plotHistogram(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, const float2& graph_size, int stride) noexcept
{
	ImGui::PlotHistogram(label, values, values_count, values_offset, overlay_text, scale_min, scale_max, (ImVec2&)graph_size, stride);
}

void
IMGUI::plotHistogram(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, const float2& graph_size) noexcept
{
	ImGui::PlotHistogram(label, values_getter, data, values_count, values_offset, overlay_text, scale_min, scale_max);
}

void
IMGUI::progressBar(float fraction, const float2& size_arg, const char* overlay) noexcept
{
	ImGui::ProgressBar(fraction, (ImVec2&)size_arg, overlay);
}

bool
IMGUI::dragFloat(const char* label, float* v, float v_speed, float v_min, float v_max, const char* display_format, float power) noexcept
{
	return ImGui::DragFloat(label, v, v_speed, v_min, v_max, display_format, power);
}

bool
IMGUI::dragFloat2(const char* label, float v[2], float v_speed, float v_min, float v_max, const char* display_format, float power) noexcept
{
	return ImGui::DragFloat2(label, v, v_speed, v_min, v_max, display_format, power);
}

bool
IMGUI::dragFloat3(const char* label, float v[3], float v_speed, float v_min, float v_max, const char* display_format, float power) noexcept
{
	return ImGui::DragFloat3(label, v, v_speed, v_min, v_max, display_format, power);
}

bool
IMGUI::dragFloat4(const char* label, float v[4], float v_speed, float v_min, float v_max, const char* display_format, float power) noexcept
{
	return ImGui::DragFloat4(label, v, v_speed, v_min, v_max, display_format, power);
}

bool
IMGUI::dragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed, float v_min, float v_max, const char* display_format, const char* display_format_max, float power) noexcept
{
	return ImGui::DragFloatRange2(label, v_current_min, v_current_max, v_speed, v_min, v_max, display_format, display_format_max);
}

bool
IMGUI::dragInt(const char* label, int* v, float v_speed, int v_min, int v_max, const char* display_format) noexcept
{
	return ImGui::DragInt(label, v, v_speed, v_min, v_max, display_format);
}

bool
IMGUI::dragInt2(const char* label, int v[2], float v_speed, int v_min, int v_max, const char* display_format) noexcept
{
	return ImGui::DragInt2(label, v, v_speed, v_min, v_max, display_format);
}

bool
IMGUI::dragInt3(const char* label, int v[3], float v_speed, int v_min, int v_max, const char* display_format) noexcept
{
	return ImGui::DragInt3(label, v, v_speed, v_min, v_max, display_format);
}

bool
IMGUI::dragInt4(const char* label, int v[4], float v_speed, int v_min, int v_max, const char* display_format) noexcept
{
	return ImGui::DragInt4(label, v, v_speed, v_min, v_max, display_format);
}

bool
IMGUI::dragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed, int v_min, int v_max, const char* display_format, const char* display_format_max) noexcept
{
	return ImGui::DragIntRange2(label, v_current_min, v_current_max, v_speed, v_min, v_max, display_format);
}

bool
IMGUI::inputText(const char* label, char* buf, size_t buf_size, GuiInputTextFlags flags) noexcept
{
	return ImGui::InputText(label, buf, buf_size, flags);
}

bool
IMGUI::inputTextMultiline(const char* label, char* buf, size_t buf_size, const float2& size, GuiInputTextFlags flags) noexcept
{
	return ImGui::InputTextMultiline(label, buf, buf_size, (const ImVec2&)size, flags);
}

bool
IMGUI::inputFloat(const char* label, float* v, float step, float step_fast, int decimal_precision, GuiInputTextFlags extraFlags) noexcept
{
	return ImGui::InputFloat(label, v, step, step_fast, decimal_precision, extraFlags);
}

bool
IMGUI::inputFloat2(const char* label, float v[2], int decimal_precision, GuiInputTextFlags extraFlags) noexcept
{
	return ImGui::InputFloat2(label, v, decimal_precision, extraFlags);
}

bool
IMGUI::inputFloat3(const char* label, float v[3], int decimal_precision, GuiInputTextFlags extraFlags) noexcept
{
	return ImGui::InputFloat3(label, v, decimal_precision, extraFlags);
}

bool
IMGUI::inputFloat4(const char* label, float v[4], int decimal_precision, GuiInputTextFlags extraFlags) noexcept
{
	return ImGui::InputFloat4(label, v, decimal_precision, extraFlags);
}

bool
IMGUI::inputInt(const char* label, int* v, int step, int step_fast, GuiInputTextFlags extraFlags) noexcept
{
	return ImGui::InputInt(label, v, step, step_fast, extraFlags);
}

bool
IMGUI::inputInt2(const char* label, int v[2], GuiInputTextFlags extraFlags) noexcept
{
	return ImGui::InputInt2(label, v, extraFlags);
}

bool
IMGUI::inputInt3(const char* label, int v[3], GuiInputTextFlags extraFlags) noexcept
{
	return ImGui::InputInt3(label, v, extraFlags);
}

bool
IMGUI::inputInt4(const char* label, int v[4], GuiInputTextFlags extraFlags) noexcept
{
	return ImGui::InputInt4(label, v, extraFlags);
}

bool
IMGUI::sliderFloat(const char* label, float* v, float v_min, float v_max, const char* display_format, float power) noexcept
{
	return ImGui::SliderFloat(label, v, v_min, v_max, display_format, power);
}

bool
IMGUI::sliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* display_format, float power) noexcept
{
	return ImGui::SliderFloat2(label, v, v_min, v_max, display_format, power);
}

bool
IMGUI::sliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* display_format, float power) noexcept
{
	return ImGui::SliderFloat3(label, v, v_min, v_max, display_format, power);
}

bool
IMGUI::sliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* display_format, float power) noexcept
{
	return ImGui::SliderFloat4(label, v, v_min, v_max, display_format, power);
}

bool
IMGUI::sliderAngle(const char* label, float* v_rad, float v_degrees_min, float v_degrees_max) noexcept
{
	return ImGui::SliderAngle(label, v_rad, v_degrees_min, v_degrees_max);
}

bool
IMGUI::sliderInt(const char* label, int* v, int v_min, int v_max, const char* display_format) noexcept
{
	return ImGui::SliderInt(label, v, v_min, v_max, display_format);
}

bool
IMGUI::sliderInt2(const char* label, int v[2], int v_min, int v_max, const char* display_format) noexcept
{
	return ImGui::SliderInt2(label, v, v_min, v_max, display_format);
}

bool
IMGUI::sliderInt3(const char* label, int v[3], int v_min, int v_max, const char* display_format) noexcept
{
	return ImGui::SliderInt3(label, v, v_min, v_max, display_format);
}

bool
IMGUI::sliderInt4(const char* label, int v[4], int v_min, int v_max, const char* display_format) noexcept
{
	return ImGui::SliderInt4(label, v, v_min, v_max, display_format);
}

bool
IMGUI::vSliderFloat(const char* label, const float2& size, float* v, float v_min, float v_max, const char* display_format, float power) noexcept
{
	return ImGui::VSliderFloat(label, (ImVec2&)size, v, v_min, v_max, display_format, power);
}

bool
IMGUI::vSliderInt(const char* label, const float2& size, int* v, int v_min, int v_max, const char* display_format) noexcept
{
	return ImGui::VSliderInt(label, (ImVec2&)size, v, v_min, v_max, display_format);
}

bool
IMGUI::treeNode(const char* label) noexcept
{
	return ImGui::TreeNode(label);
}

bool
IMGUI::treeNode(const char* str_id, const char* fmt, ...) noexcept
{
	bool result = false;
	va_list args;
	va_start(args, fmt);
	result = ImGui::TreeNodeExV(str_id, 0, fmt, args);
	va_end(args);
	return result;
}

bool
IMGUI::treeNode(const void* ptr_id, const char* fmt, ...) noexcept
{
	bool result = false;
	va_list args;
	va_start(args, fmt);
	result = ImGui::TreeNodeExV(ptr_id, 0, fmt, args);
	va_end(args);
	return result;
}

bool
IMGUI::treeNodeV(const char* str_id, const char* fmt, va_list args) noexcept
{
	return ImGui::TreeNodeExV(str_id, 0, fmt, args);
}

bool
IMGUI::treeNodeV(const void* ptr_id, const char* fmt, va_list args) noexcept
{
	return ImGui::TreeNodeExV(ptr_id, 0, fmt, args);
}

bool
IMGUI::treeNodeEx(const char* label, GuiTreeNodeFlags flags) noexcept
{
	return ImGui::TreeNodeEx(label, flags);
}

bool
IMGUI::treeNodeEx(const char* str_id, GuiTreeNodeFlags flags, const char* fmt, ...) noexcept
{
	bool result = false;
	va_list args;
	va_start(args, fmt);
	result = ImGui::TreeNodeEx(str_id, flags, fmt, args);
	va_end(args);
	return result;
}

bool
IMGUI::treeNodeEx(const void* ptr_id, GuiTreeNodeFlags flags, const char* fmt, ...) noexcept
{
	bool result = false;
	va_list args;
	va_start(args, fmt);
	result = ImGui::TreeNodeEx(ptr_id, flags, fmt, args);
	va_end(args);
	return result;
}

bool
IMGUI::treeNodeExV(const char* str_id, GuiTreeNodeFlags flags, const char* fmt, va_list args) noexcept
{
	return ImGui::TreeNodeEx(str_id, flags, fmt, args);
}

bool
IMGUI::treeNodeExV(const void* ptr_id, GuiTreeNodeFlags flags, const char* fmt, va_list args) noexcept
{
	return ImGui::TreeNodeEx(ptr_id, flags, fmt, args);
}

void
IMGUI::treePush(const char* str_id) noexcept
{
	return ImGui::TreePush(str_id);
}

void
IMGUI::treePush(const void* ptr_id) noexcept
{
	return ImGui::TreePush(ptr_id);
}

void
IMGUI::treePop() noexcept
{
	return ImGui::TreePop();
}

void
IMGUI::treeAdvanceToLabelPos() noexcept
{
	return ImGui::TreeAdvanceToLabelPos();
}

float
IMGUI::getTreeNodeToLabelSpacing() noexcept
{
	return ImGui::GetTreeNodeToLabelSpacing();
}

void
IMGUI::setNextTreeNodeOpen(bool is_open, GuiSetCondFlags cond) noexcept
{
	return ImGui::SetNextTreeNodeOpen(is_open, cond);
}

bool
IMGUI::collapsingHeader(const char* label, GuiTreeNodeFlags flags) noexcept
{
	return ImGui::CollapsingHeader(label, flags);
}

bool
IMGUI::collapsingHeader(const char* label, bool* isOpened, GuiTreeNodeFlags flags) noexcept
{
	return ImGui::CollapsingHeader(label, isOpened, flags);
}

bool
IMGUI::selectable(const char* label, bool selected, GuiSelectableFlags flags, const float2& size) noexcept
{
	return ImGui::Selectable(label, selected, flags, (const ImVec2&)size);
}

bool
IMGUI::selectable(const char* label, bool* p_selected, GuiSelectableFlags flags, const float2& size) noexcept
{
	return ImGui::Selectable(label, p_selected, flags, (const ImVec2&)size);
}

bool
IMGUI::listBox(const char* label, int* current_item, const char** items, int items_count, int height_in_items) noexcept
{
	return ImGui::ListBox(label, current_item, items, items_count, height_in_items);
}

bool
IMGUI::listBox(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items) noexcept
{
	return ImGui::ListBox(label, current_item, items_getter, data, items_count, height_in_items);
}

bool
IMGUI::listBoxHeader(const char* label, const float2& size) noexcept
{
	return ImGui::ListBoxHeader(label, (const ImVec2&)size);
}

bool
IMGUI::listBoxHeader(const char* label, int items_count, int height_in_items) noexcept
{
	return ImGui::ListBoxHeader(label, items_count, height_in_items);
}

void
IMGUI::listBoxFooter() noexcept
{
	ImGui::ListBoxFooter();
}

void
IMGUI::value(const char* prefix, bool b) noexcept
{
	ImGui::Value(prefix, b);
}

void
IMGUI::value(const char* prefix, int v) noexcept
{
	ImGui::Value(prefix, v);
}

void
IMGUI::value(const char* prefix, unsigned int v) noexcept
{
	ImGui::Value(prefix, v);
}

void
IMGUI::value(const char* prefix, float v, const char* float_format) noexcept
{
	ImGui::Value(prefix, v, float_format);
}

void
IMGUI::valueColor(const char* prefix, const float4& v) noexcept
{
	ImGui::ValueColor(prefix, (const ImVec4&)v);
}

void
IMGUI::valueColor(const char* prefix, std::uint32_t v) noexcept
{
	ImGui::ValueColor(prefix, v);
}

void
IMGUI::setTooltip(const char* fmt, ...) noexcept
{
	va_list args;
	va_start(args, fmt);
	ImGui::SetTooltipV(fmt, args);
	va_end(args);
}

void
IMGUI::setTooltipV(const char* fmt, va_list args) noexcept
{
	ImGui::SetTooltipV(fmt, args);
}

void
IMGUI::beginTooltip() noexcept
{
	ImGui::BeginTooltip();
}

void
IMGUI::endTooltip() noexcept
{
	ImGui::EndTooltip();
}

bool
IMGUI::beginMainMenuBar() noexcept
{
	return ImGui::BeginMainMenuBar();
}

void
IMGUI::endMainMenuBar() noexcept
{
	ImGui::EndMainMenuBar();
}

bool
IMGUI::beginMenuBar() noexcept
{
	return ImGui::BeginMenuBar();
}

void
IMGUI::endMenuBar() noexcept
{
	return ImGui::EndMenuBar();
}

bool
IMGUI::beginMenu(const char* label, bool enabled) noexcept
{
	return ImGui::BeginMenu(label, enabled);
}

void
IMGUI::endMenu() noexcept
{
	return ImGui::EndMenu();
}

bool
IMGUI::menuItem(const char* label, const char* shortcut, bool selected, bool enabled) noexcept
{
	return ImGui::MenuItem(label, shortcut, selected, enabled);
}

bool
IMGUI::menuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled) noexcept
{
	return ImGui::MenuItem(label, shortcut, p_selected, enabled);
}

void
IMGUI::openPopup(const char* str_id) noexcept
{
	return ImGui::OpenPopup(str_id);
}

bool
IMGUI::beginPopup(const char* str_id) noexcept
{
	return ImGui::BeginPopup(str_id);
}

bool
IMGUI::beginPopupModal(const char* name, bool* isOpened, GuiWindowFlags extraFlags) noexcept
{
	return ImGui::BeginPopupModal(name, isOpened, extraFlags);
}

bool
IMGUI::beginPopupContextItem(const char* str_id, int mouse_button) noexcept
{
	return ImGui::BeginPopupContextItem(str_id, mouse_button);
}

bool
IMGUI::beginPopupContextWindow(bool also_over_items, const char* str_id, int mouse_button) noexcept
{
	return ImGui::BeginPopupContextWindow(also_over_items, str_id, mouse_button);
}

bool
IMGUI::beginPopupContextVoid(const char* str_id, int mouse_button) noexcept
{
	return ImGui::BeginPopupContextVoid(str_id, mouse_button);
}

void
IMGUI::endPopup() noexcept
{
	return ImGui::EndPopup();
}

void
IMGUI::closeCurrentPopup() noexcept
{
	return ImGui::CloseCurrentPopup();
}

void
IMGUI::pushClipRect(const float2& clip_rect_min, const float2& clip_rect_max, bool intersect_with_current_clip_rect) noexcept
{
	return ImGui::PushClipRect((const ImVec2&)clip_rect_min, (const ImVec2&)clip_rect_max, intersect_with_current_clip_rect);
}

void
IMGUI::popClipRect() noexcept
{
	return ImGui::PopClipRect();
}

bool
IMGUI::isItemHovered() noexcept
{
	return ImGui::IsItemHovered();
}

bool
IMGUI::isItemHoveredRect() noexcept
{
	return ImGui::IsItemHoveredRect();
}

bool
IMGUI::isItemActive() noexcept
{
	return ImGui::IsItemActive();
}

bool
IMGUI::isItemClicked(int mouse_button) noexcept
{
	return ImGui::IsItemClicked();
}

bool
IMGUI::isItemVisible() noexcept
{
	return ImGui::IsItemVisible();
}

bool
IMGUI::isAnyItemHovered() noexcept
{
	return ImGui::IsAnyItemHovered();
}

bool
IMGUI::isAnyItemActive() noexcept
{
	return ImGui::IsAnyItemActive();
}

float2
IMGUI::getItemRectMin() noexcept
{
	return ImVec2ToFloat2(ImGui::GetItemRectMin());
}

float2
IMGUI::getItemRectMax() noexcept
{
	return ImVec2ToFloat2(ImGui::GetItemRectMax());
}

float2
IMGUI::getItemRectSize() noexcept
{
	return ImVec2ToFloat2(ImGui::GetItemRectSize());
}

void
IMGUI::setItemAllowOverlap() noexcept
{
	return ImGui::SetItemAllowOverlap();
}

bool
IMGUI::isWindowHovered() noexcept
{
	return ImGui::IsWindowHovered();
}

bool
IMGUI::isWindowFocused() noexcept
{
	return ImGui::IsWindowFocused();
}

bool
IMGUI::isRootWindowFocused() noexcept
{
	return ImGui::IsRootWindowFocused();
}

bool
IMGUI::isRootWindowOrAnyChildFocused() noexcept
{
	return ImGui::IsRootWindowOrAnyChildFocused();
}

bool
IMGUI::isRootWindowOrAnyChildHovered() noexcept
{
	return ImGui::IsRootWindowOrAnyChildHovered();
}

bool
IMGUI::isRectVisible(const float2& size) noexcept
{
	return ImGui::IsRectVisible((const ImVec2&)size);
}

bool
IMGUI::isPosHoveringAnyWindow(const float2& pos) noexcept
{
	return ImGui::IsPosHoveringAnyWindow((const ImVec2&)pos);
}

float
IMGUI::getTime() noexcept
{
	return ImGui::GetTime();
}

int
IMGUI::getFrameCount() noexcept
{
	return ImGui::GetFrameCount();
}

const char*
IMGUI::getStyleColName(GuiCol idx) noexcept
{
	return ImGui::GetStyleColName(idx);
}

float2
IMGUI::calcItemRectClosestPoint(const float2& pos, bool on_edge, float outward) noexcept
{
	return ImVec2ToFloat2(ImGui::CalcItemRectClosestPoint((ImVec2&)(pos), on_edge, outward));
}

float2
IMGUI::calcTextSize(const char* text, const char* text_end, bool hide_text_after_double_hash, float wrap_width) noexcept
{
	return ImVec2ToFloat2(ImGui::CalcTextSize(text, text_end, hide_text_after_double_hash, wrap_width));
}

void
IMGUI::calcListClipping(int items_count, float items_height, int* out_items_display_start, int* out_items_display_end) noexcept
{
	return ImGui::CalcListClipping(items_count, items_height, out_items_display_start, out_items_display_end);
}

bool
IMGUI::beginChildFrame(GuiID id, const float2& size, GuiWindowFlags extraFlags) noexcept
{
	return ImGui::BeginChildFrame(id, (const ImVec2&)size, extraFlags);
}

void
IMGUI::endChildFrame() noexcept
{
	return ImGui::EndChildFrame();
}

float4
IMGUI::colorConvertU32ToFloat4(std::uint32_t in) noexcept
{
	return ImVec4ToFloat4(ImGui::ColorConvertU32ToFloat4(in));
}

std::uint32_t
IMGUI::colorConvertFloat4ToU32(const float4& in) noexcept
{
	return ImGui::ColorConvertFloat4ToU32((const ImVec4&)in);
}

void
IMGUI::colorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v) noexcept
{
	return ImGui::ColorConvertRGBtoHSV(r, g, b, out_h, out_s, out_v);
}

void
IMGUI::colorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b) noexcept
{
	return ImGui::ColorConvertHSVtoRGB(h, s, v, out_r, out_g, out_b);
}

bool
IMGUI::isKeyDown(int key_index) noexcept
{
	return ImGui::IsKeyDown(key_index);
}

bool
IMGUI::isKeyPressed(int key_index, bool repeat) noexcept
{
	return ImGui::IsKeyPressed(key_index, repeat);
}

bool
IMGUI::isKeyReleased(int key_index) noexcept
{
	return ImGui::IsKeyReleased(key_index);
}

bool
IMGUI::isMouseDown(int button) noexcept
{
	return ImGui::IsMouseDown(button);
}

bool
IMGUI::isMouseClicked(int button, bool repeat) noexcept
{
	return ImGui::IsMouseClicked(button, repeat);
}

bool
IMGUI::isMouseDoubleClicked(int button) noexcept
{
	return ImGui::IsMouseDoubleClicked(button);
}

bool
IMGUI::isMouseReleased(int button) noexcept
{
	return ImGui::IsMouseReleased(button);
}

bool
IMGUI::isMouseHoveringWindow() noexcept
{
	return ImGui::IsMouseHoveringWindow();
}

bool
IMGUI::isMouseHoveringAnyWindow() noexcept
{
	return ImGui::IsMouseHoveringAnyWindow();
}

bool
IMGUI::isMouseHoveringRect(const float2& min, const float2& max, bool clip) noexcept
{
	return ImGui::IsMouseHoveringRect((const ImVec2&)min, (const ImVec2&)max, clip);
}

bool
IMGUI::isMouseDragging(int button, float lock_threshold) noexcept
{
	return ImGui::IsMouseDragging();
}

float2
IMGUI::getMousePos() noexcept
{
	return ImVec2ToFloat2(ImGui::GetMousePos());
}

float2
IMGUI::getMousePosOnOpeningCurrentPopup() noexcept
{
	return ImVec2ToFloat2(ImGui::GetMousePosOnOpeningCurrentPopup());
}

float2
IMGUI::getMouseDragDelta(int button, float lock_threshold) noexcept
{
	return ImVec2ToFloat2(ImGui::GetMouseDragDelta());
}

void
IMGUI::resetMouseDragDelta(int button) noexcept
{
	return ImGui::ResetMouseDragDelta();
}

void
IMGUI::setMouseCursor(GuiMouseCursor type) noexcept
{
	return ImGui::SetMouseCursor(type);
}

void
IMGUI::captureKeyboardFromApp(bool capture) noexcept
{
	return ImGui::CaptureKeyboardFromApp(capture);
}

void
IMGUI::captureMouseFromApp(bool capture) noexcept
{
	return ImGui::CaptureMouseFromApp(capture);
}

_NAME_END