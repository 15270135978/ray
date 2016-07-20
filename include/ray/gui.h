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
#ifndef _H_GUI_WIDGET_ALIGN_H_
#define _H_GUI_WIDGET_ALIGN_H_

#include <ray/math.h>

#if (defined(__clang__) || defined(__GNUC__)) && !defined(__MINGW32__) && !defined(__MINGW64__)
#	define PRINTFARGS(FMT) __attribute__((format(printf, FMT, (FMT+1))))
#else
#	define PRINTFARGS(FMT)
#endif

_NAME_BEGIN

enum GuiCol
{
	GuiColText,
	GuiColTextDisabled,
	GuiColWindowBg,
	GuiColChildWindowBg,
	GuiColPopupBg,
	GuiColBorder,
	GuiColBorderShadow,
	GuiColFrameBg,
	GuiColFrameBgHovered,
	GuiColFrameBgActive,
	GuiColTitleBg,
	GuiColTitleBgCollapsed,
	GuiColTitleBgActive,
	GuiColMenuBarBg,
	GuiColScrollbarBg,
	GuiColScrollbarGrab,
	GuiColScrollbarGrabHovered,
	GuiColScrollbarGrabActive,
	GuiColComboBg,
	GuiColCheckMark,
	GuiColSliderGrab,
	GuiColSliderGrabActive,
	GuiColButton,
	GuiColButtonHovered,
	GuiColButtonActive,
	GuiColHeader,
	GuiColHeaderHovered,
	GuiColHeaderActive,
	GuiColColumn,
	GuiColColumnHovered,
	GuiColColumnActive,
	GuiColResizeGrip,
	GuiColResizeGripHovered,
	GuiColResizeGripActive,
	GuiColCloseButton,
	GuiColCloseButtonHovered,
	GuiColCloseButtonActive,
	GuiColPlotLines,
	GuiColPlotLinesHovered,
	GuiColPlotHistogram,
	GuiColPlotHistogramHovered,
	GuiColTextSelectedBg,
	GuiColModalWindowDarkening,  // darken entire screen when a modal window is active
	GuiColCOUNT
};

enum GuiInputTextFlagBits
{
	GuiInputTextFlagCharsDecimalBit = 1 << 0,
	GuiInputTextFlagCharsHexadecimalBit = 1 << 1,
	GuiInputTextFlagCharsUppercaseBit = 1 << 2,
	GuiInputTextFlagCharsNoBlankBit = 1 << 3,
	GuiInputTextFlagAutoSelectAllBit = 1 << 4,
	GuiInputTextFlagEnterReturnsTrueBit = 1 << 5,
	GuiInputTextFlagCallbackCompletionBit = 1 << 6,
	GuiInputTextFlagCallbackHistoryBit = 1 << 7,
	GuiInputTextFlagCallbackAlwaysBit = 1 << 8,
	GuiInputTextFlagCallbackCharFilterBit = 1 << 9,
	GuiInputTextFlagAllowTabInputBit = 1 << 10,
	GuiInputTextFlagCtrlEnterForNewLineBit = 1 << 11,
	GuiInputTextFlagNoHorizontalScrollBit = 1 << 12,
	GuiInputTextFlagAlwaysInsertModeBit = 1 << 13,
	GuiInputTextFlagReadOnlyBit = 1 << 14,
	GuiInputTextFlagPasswordBit = 1 << 15,
	GuiInputTextFlagMultilineBit = 1 << 20
};

typedef std::uint32_t GuiInputTextFlags;

enum GuiWindowFlagBits
{
	GuiWindowFlagNoTitleBarBit = 1 << 0,
	GuiWindowFlagNoResizeBit = 1 << 1,
	GuiWindowFlagNoMoveBit = 1 << 2,
	GuiWindowFlagNoScrollbarBit = 1 << 3,
	GuiWindowFlagNoScrollWithMouseBit = 1 << 4,
	GuiWindowFlagNoCollapseBit = 1 << 5,
	GuiWindowFlagAlwaysAutoResizeBit = 1 << 6,
	GuiWindowFlagShowBordersBit = 1 << 7,
	GuiWindowFlagNoSavedSettingsBit = 1 << 8,
	GuiWindowFlagNoInputsBit = 1 << 9,
	GuiWindowFlagMenuBarBit = 1 << 10,
	GuiWindowFlagHorizontalScrollbarBit = 1 << 11,
	GuiWindowFlagNoFocusOnAppearingBit = 1 << 12,
	GuiWindowFlagNoBringToFrontOnFocusBit = 1 << 13,
	GuiWindowFlagAlwaysVerticalScrollbarBit = 1 << 14,
	GuiWindowFlagAlwaysHorizontalScrollbarBit = 1 << 15,
	GuiWindowFlagAlwaysUseWindowPaddingBit = 1 << 16
};

typedef std::uint32_t GuiWindowFlags;

enum GuiAlignFlagBits
{
	GuiAlignFlagLeftBit = 1 << 0,
	GuiAlignFlagCenterBit = 1 << 1,
	GuiAlignFlagRightBit = 1 << 2,
	GuiAlignFlagTopBit = 1 << 3,
	GuiAlignFlagVCenterBit = 1 << 4,
	GuiAlignFlagDefaultBit = GuiAlignFlagLeftBit | GuiAlignFlagTopBit
};

typedef std::uint32_t GuiAlignFlags;

enum GuiSetCondFlagBits
{
	GuiSetCondFlagAlwaysBit = 1 << 0,
	GuiSetCondFlagOnceBit = 1 << 1,
	GuiSetCondFlagFirstUseEverBit = 1 << 2,
	GuiSetCondFlagAppearingBit = 1 << 3
};

typedef std::uint32_t GuiSetCondFlags;

enum GuiTreeNodeFlagBits
{
	GuiTreeNodeFlagSelectedBit = 1 << 0,
	GuiTreeNodeFlagFramedBit = 1 << 1,
	GuiTreeNodeFlagAllowOverlapModeBit = 1 << 2,
	GuiTreeNodeFlagNoTreePushOnOpenBit = 1 << 3,
	GuiTreeNodeFlagNoAutoOpenOnLogBit = 1 << 4,
	GuiTreeNodeFlagDefaultOpenBit = 1 << 5,
	GuiTreeNodeFlagOpenOnDoubleClickBit = 1 << 6,
	GuiTreeNodeFlagOpenOnArrowBit = 1 << 7,
	GuiTreeNodeFlagLeafBit = 1 << 8,
	GuiTreeNodeFlagBulletBit = 1 << 9,
	GuiTreeNodeFlagCollapsingHeaderBit = GuiTreeNodeFlagFramedBit | GuiTreeNodeFlagNoAutoOpenOnLogBit
};

typedef std::uint32_t GuiTreeNodeFlags;

enum GuiSelectableFlagBits
{
	GuiSelectableFlagDontClosePopupsBit = 1 << 0,
	GuiSelectableFlagSpanAllColumnsBit = 1 << 1,
	GuiSelectableFlagAllowDoubleClickBit = 1 << 2
};

typedef std::uint32_t GuiSelectableFlags;

enum GuiMouseCursor
{
	GuiMouseCursorArrow = 0,
	GuiMouseCursorTextInput,         // When hovering over InputText, etc.
	GuiMouseCursorMove,              // Unused
	GuiMouseCursorResizeNS,          // Unused
	GuiMouseCursorResizeEW,          // When hovering over a column
	GuiMouseCursorResizeNESW,        // Unused
	GuiMouseCursorResizeNWSE,        // When hovering over the bottom-right corner of a window
	GuiMouseCursorCount_
};

enum GuiColorEditMode
{
	GuiColorEditModeUserSelect = -2,
	GuiColorEditModeUserSelectShowButton = -1,
	GuiColorEditModeRGB = 0,
	GuiColorEditModeHSV = 1,
	GuiColorEditModeHEX = 2
};

enum GuiStyleVar
{
	GuiStyleVarAlpha,               // float
	GuiStyleVarWindowPadding,       // ImVec2
	GuiStyleVarWindowRounding,      // float
	GuiStyleVarWindowMinSize,       // ImVec2
	GuiStyleVarChildWindowRounding, // float
	GuiStyleVarFramePadding,        // ImVec2
	GuiStyleVarFrameRounding,       // float
	GuiStyleVarItemSpacing,         // ImVec2
	GuiStyleVarItemInnerSpacing,    // ImVec2
	GuiStyleVarIndentSpacing,       // float
	GuiStyleVarGrabMinSize          // float
};

struct GuiStyle
{
	float       Alpha;
	float2      WindowPadding;
	float2      WindowMinSize;
	float       WindowRounding;
	GuiAlignFlags  WindowTitleAlign;
	float       ChildWindowRounding;
	float2      FramePadding;
	float       FrameRounding;
	float2      ItemSpacing;
	float2      ItemInnerSpacing;
	float2      TouchExtraPadding;
	float       IndentSpacing;
	float       ColumnsMinSpacing;
	float       ScrollbarSize;
	float       ScrollbarRounding;
	float       GrabMinSize;
	float       GrabRounding;
	float2      DisplayWindowPadding;
	float2      DisplaySafeAreaPadding;
	bool        AntiAliasedLines;
	bool        AntiAliasedShapes;
	float       CurveTessellationTol;
	float4      Colors[GuiCol::GuiColCOUNT];

	GuiStyle() noexcept;
};

typedef void* GuiTextureID;
typedef std::uint32_t GuiID;

class EXPORT Gui final
{
public:
	Gui() noexcept;
	~Gui() noexcept;

	void          newFrame() noexcept;
	void          render() noexcept;
	void          shutdown() noexcept;
	void          showUserGuide() noexcept;
	void          showStyleEditor(GuiStyle* style = nullptr) noexcept;
	void          showTestWindow(bool* isOpened = nullptr) noexcept;
	void		  showMetricsWindow(bool* isOpened = nullptr) noexcept;

	bool          begin(const char* name, bool* isOpened = nullptr, GuiWindowFlags flags = 0) noexcept;
	bool          begin(const char* name, bool* isOpened, const float2& size_on_first_use, float bg_alpha = -1.0f, GuiWindowFlags flags = 0) noexcept;
	void          end() noexcept;
	bool          beginChild(const char* str_id, const float2& size = float2::Zero, bool border = false, GuiWindowFlags extraFlags = 0) noexcept;
	bool          beginChild(GuiID id, const float2& size = float2::Zero, bool border = false, GuiWindowFlags extraFlags = 0) noexcept;
	void          endChild() noexcept;
	float2        getContentRegionMax() noexcept;
	float2        getContentRegionAvail() noexcept;
	float         getContentRegionAvailWidth() noexcept;
	float2        getWindowContentRegionMin() noexcept;
	float2        getWindowContentRegionMax() noexcept;
	float         getWindowContentRegionWidth() noexcept;
	float2        getWindowPos() noexcept;
	float2        getWindowSize() noexcept;
	float         getWindowWidth() noexcept;
	float         getWindowHeight() noexcept;
	bool          isWindowCollapsed() noexcept;
	void          setWindowFontScale(float scale) noexcept;

	void          setNextWindowPos(const float2& pos, GuiSetCondFlags cond = 0) noexcept;
	void          setNextWindowPosCenter(GuiSetCondFlags cond = 0) noexcept;
	void          setNextWindowSize(const float2& size, GuiSetCondFlags cond = 0) noexcept;
	void          setNextWindowSizeConstraints(const float2& size_min, const float2& size_max) noexcept;
	void          setNextWindowContentSize(const float2& size) noexcept;
	void          setNextWindowContentWidth(float width) noexcept;
	void          setNextWindowCollapsed(bool collapsed, GuiSetCondFlags cond = 0) noexcept;
	void          setNextWindowFocus() noexcept;
	void          setWindowPos(const float2& pos, GuiSetCondFlags cond = 0) noexcept;
	void          setWindowSize(const float2& size, GuiSetCondFlags cond = 0) noexcept;
	void          setWindowCollapsed(bool collapsed, GuiSetCondFlags cond = 0) noexcept;
	void          setWindowFocus() noexcept;
	void          setWindowPos(const char* name, const float2& pos, GuiSetCondFlags cond = 0) noexcept;
	void          setWindowSize(const char* name, const float2& size, GuiSetCondFlags cond = 0) noexcept;
	void          setWindowCollapsed(const char* name, bool collapsed, GuiSetCondFlags cond = 0) noexcept;
	void          setWindowFocus(const char* name) noexcept;

	float         getScrollX() noexcept;
	float         getScrollY() noexcept;
	float         getScrollMaxX() noexcept;
	float         getScrollMaxY() noexcept;
	void          setScrollX(float scroll_x) noexcept;
	void          setScrollY(float scroll_y) noexcept;
	void          setScrollHere(float center_y_ratio = 0.5f) noexcept;
	void          setScrollFromPosY(float pos_y, float center_y_ratio = 0.5f) noexcept;
	void          setKeyboardFocusHere(int offset = 0) noexcept;

	void          pushStyleColor(GuiCol idx, const float4& col) noexcept;
	void          popStyleColor(int count = 1) noexcept;
	void          pushStyleVar(GuiStyleVar idx, float val) noexcept;
	void          pushStyleVar(GuiStyleVar idx, const float2& val) noexcept;
	void          popStyleVar(int count = 1) noexcept;
	float         getFontSize() noexcept;
	float2        getFontTexUvWhitePixel() noexcept;
	std::uint32_t getColorU32(GuiCol idx, float alpha_mul = 1.0f) noexcept;
	std::uint32_t getColorU32(const float4& col) noexcept;

	void          pushItemWidth(float item_width) noexcept;
	void          popItemWidth() noexcept;
	float         calcItemWidth() noexcept;
	void          pushTextWrapPos(float wrap_pos_x = 0.0f) noexcept;
	void          popTextWrapPos() noexcept;
	void          pushAllowKeyboardFocus(bool v) noexcept;
	void          popAllowKeyboardFocus() noexcept;
	void          pushButtonRepeat(bool repeat) noexcept;
	void          popButtonRepeat() noexcept;

	void          separator() noexcept;
	void          sameLine(float pos_x = 0.0f, float spacing_w = -1.0f) noexcept;
	void          newLine() noexcept;
	void          spacing() noexcept;
	void          dummy(const float2& size) noexcept;
	void          indent(float indent_w = 0.0f) noexcept;
	void          unindent(float indent_w = 0.0f) noexcept;
	void          beginGroup() noexcept;
	void          endGroup() noexcept;
	float2        getCursorPos() noexcept;
	float         getCursorPosX() noexcept;
	float         getCursorPosY() noexcept;
	void          setCursorPos(const float2& local_pos) noexcept;
	void          setCursorPosX(float x) noexcept;
	void          setCursorPosY(float y) noexcept;
	float2        getCursorStartPos() noexcept;
	float2        getCursorScreenPos() noexcept;
	void          setCursorScreenPos(const float2& pos) noexcept;
	void          alignFirstTextHeightToWidgets() noexcept;
	float         getTextLineHeight() noexcept;
	float         getTextLineHeightWithSpacing() noexcept;
	float         getItemsLineHeightWithSpacing() noexcept;

	void          columns(int count = 1, const char* id = nullptr, bool border = true) noexcept;

	void          pushID(const char* str_id_begin, const char* str_id_end) noexcept;
	void          pushID(const void* ptr_id) noexcept;
	void          pushID(int int_id) noexcept;
	void          popID() noexcept;
	GuiID         getID(const char* str_id) noexcept;
	GuiID         getID(const char* str_id_begin, const char* str_id_end) noexcept;
	GuiID         getID(const void* ptr_id) noexcept;

	void          text(const char* fmt, ...) PRINTFARGS(1) noexcept;
	void          textV(const char* fmt, va_list args) noexcept;
	void          textColored(const float4& col, const char* fmt, ...) PRINTFARGS(2) noexcept;
	void          textColoredV(const float4& col, const char* fmt, va_list args) noexcept;
	void          textDisabled(const char* fmt, ...) PRINTFARGS(1) noexcept;
	void          textDisabledV(const char* fmt, va_list args) noexcept;
	void          textWrapped(const char* fmt, ...) PRINTFARGS(1) noexcept;
	void          textWrappedV(const char* fmt, va_list args) noexcept;
	void          textUnformatted(const char* text, const char* text_end = nullptr) noexcept;
	void          labelText(const char* label, const char* fmt, ...) PRINTFARGS(2) noexcept;
	void          labelTextV(const char* label, const char* fmt, va_list args) noexcept;
	void          bullet() noexcept;
	void          bulletText(const char* fmt, ...) PRINTFARGS(1) noexcept;
	void          bulletTextV(const char* fmt, va_list args) noexcept;
	bool          button(const char* label, const float2& size = float2::Zero) noexcept;
	bool          smallButton(const char* label) noexcept;
	bool          invisibleButton(const char* str_id, const float2& size) noexcept;
	void          image(GuiTextureID user_texture_id, const float2& size, const float2& uv0 = float2::Zero, const float2& uv1 = float2(1, 1), const float4& tint_col = float4(1, 1, 1, 1), const float4& border_col = float4(0, 0, 0, 0)) noexcept;
	bool          imageButton(GuiTextureID user_texture_id, const float2& size, const float2& uv0 = float2::Zero, const float2& uv1 = float2(1, 1), int frame_padding = -1, const float4& bg_col = float4(0, 0, 0, 0), const float4& tint_col = float4(1, 1, 1, 1)) noexcept;
	bool          checkbox(const char* label, bool* v) noexcept;
	bool          checkboxFlags(const char* label, unsigned int* flags, unsigned int flags_value) noexcept;
	bool          radioButton(const char* label, bool active) noexcept;
	bool          radioButton(const char* label, int* v, int v_button) noexcept;
	bool          combo(const char* label, int* current_item, const char** items, int items_count, int height_in_items = -1) noexcept;
	bool          combo(const char* label, int* current_item, const char* items_separated_by_zeros, int height_in_items = -1) noexcept;
	bool          combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items = -1) noexcept;
	bool          colorButton(const float4& col, bool small_height = false, bool outline_border = true) noexcept;
	bool          colorEdit3(const char* label, float col[3]) noexcept;
	bool          colorEdit4(const char* label, float col[4], bool show_alpha = true) noexcept;
	void          colorEditMode(GuiColorEditMode mode) noexcept;
	void          plotLines(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = nullptr, float scale_min = FLT_MAX, float scale_max = FLT_MAX, const float2& graph_size = float2::Zero, int stride = sizeof(float)) noexcept;
	void          plotLines(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = nullptr, float scale_min = FLT_MAX, float scale_max = FLT_MAX, const float2& graph_size = float2::Zero) noexcept;
	void          plotHistogram(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = nullptr, float scale_min = FLT_MAX, float scale_max = FLT_MAX, const float2& graph_size = float2::Zero, int stride = sizeof(float)) noexcept;
	void          plotHistogram(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = nullptr, float scale_min = FLT_MAX, float scale_max = FLT_MAX, const float2& graph_size = float2::Zero) noexcept;
	void          progressBar(float fraction, const float2& size_arg = float2(-1, 0), const char* overlay = nullptr) noexcept;

	bool          dragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f) noexcept;
	bool          dragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f) noexcept;
	bool          dragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f) noexcept;
	bool          dragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f) noexcept;
	bool          dragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", const char* display_format_max = nullptr, float power = 1.0f) noexcept;
	bool          dragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f") noexcept;
	bool          dragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f") noexcept;
	bool          dragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f") noexcept;
	bool          dragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f") noexcept;
	bool          dragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f", const char* display_format_max = nullptr) noexcept;

	bool          inputText(const char* label, char* buf, size_t buf_size, GuiInputTextFlags flags = 0) noexcept;
	bool          inputTextMultiline(const char* label, char* buf, size_t buf_size, const float2& size = float2::Zero, GuiInputTextFlags flags = 0) noexcept;
	bool          inputFloat(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, int decimal_precision = -1, GuiInputTextFlags extraFlags = 0) noexcept;
	bool          inputFloat2(const char* label, float v[2], int decimal_precision = -1, GuiInputTextFlags extraFlags = 0) noexcept;
	bool          inputFloat3(const char* label, float v[3], int decimal_precision = -1, GuiInputTextFlags extraFlags = 0) noexcept;
	bool          inputFloat4(const char* label, float v[4], int decimal_precision = -1, GuiInputTextFlags extraFlags = 0) noexcept;
	bool          inputInt(const char* label, int* v, int step = 1, int step_fast = 100, GuiInputTextFlags extraFlags = 0) noexcept;
	bool          inputInt2(const char* label, int v[2], GuiInputTextFlags extraFlags = 0) noexcept;
	bool          inputInt3(const char* label, int v[3], GuiInputTextFlags extraFlags = 0) noexcept;
	bool          inputInt4(const char* label, int v[4], GuiInputTextFlags extraFlags = 0) noexcept;

	bool          sliderFloat(const char* label, float* v, float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f) noexcept;
	bool          sliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f) noexcept;
	bool          sliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f) noexcept;
	bool          sliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f) noexcept;
	bool          sliderAngle(const char* label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f) noexcept;
	bool          sliderInt(const char* label, int* v, int v_min, int v_max, const char* display_format = "%.0f") noexcept;
	bool          sliderInt2(const char* label, int v[2], int v_min, int v_max, const char* display_format = "%.0f") noexcept;
	bool          sliderInt3(const char* label, int v[3], int v_min, int v_max, const char* display_format = "%.0f") noexcept;
	bool          sliderInt4(const char* label, int v[4], int v_min, int v_max, const char* display_format = "%.0f") noexcept;
	bool          vSliderFloat(const char* label, const float2& size, float* v, float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f) noexcept;
	bool          vSliderInt(const char* label, const float2& size, int* v, int v_min, int v_max, const char* display_format = "%.0f") noexcept;

	bool          treeNode(const char* label) noexcept;
	bool          treeNode(const char* str_id, const char* fmt, ...) PRINTFARGS(2) noexcept;
	bool          treeNode(const void* ptr_id, const char* fmt, ...) PRINTFARGS(2) noexcept;
	bool          treeNodeV(const char* str_id, const char* fmt, va_list args) noexcept;
	bool          treeNodeV(const void* ptr_id, const char* fmt, va_list args) noexcept;
	bool          treeNodeEx(const char* label, GuiTreeNodeFlags flags = 0) noexcept;
	bool          treeNodeEx(const char* str_id, GuiTreeNodeFlags flags, const char* fmt, ...) PRINTFARGS(3) noexcept;
	bool          treeNodeEx(const void* ptr_id, GuiTreeNodeFlags flags, const char* fmt, ...) PRINTFARGS(3) noexcept;
	bool          treeNodeExV(const char* str_id, GuiTreeNodeFlags flags, const char* fmt, va_list args) noexcept;
	bool          treeNodeExV(const void* ptr_id, GuiTreeNodeFlags flags, const char* fmt, va_list args) noexcept;
	void          treePush(const char* str_id = nullptr) noexcept;
	void          treePush(const void* ptr_id = nullptr) noexcept;
	void          treePop() noexcept;
	void          treeAdvanceToLabelPos() noexcept;
	float         getTreeNodeToLabelSpacing() noexcept;
	void          setNextTreeNodeOpen(bool is_open, GuiSetCondFlags cond = 0) noexcept;
	bool          collapsingHeader(const char* label, GuiTreeNodeFlags flags = 0) noexcept;
	bool          collapsingHeader(const char* label, bool* isOpened, GuiTreeNodeFlags flags = 0) noexcept;

	bool          selectable(const char* label, bool selected = false, GuiSelectableFlags flags = 0, const float2& size = float2::Zero) noexcept;
	bool          selectable(const char* label, bool* p_selected, GuiSelectableFlags flags = 0, const float2& size = float2::Zero) noexcept;
	bool          listBox(const char* label, int* current_item, const char** items, int items_count, int height_in_items = -1) noexcept;
	bool          listBox(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items = -1) noexcept;
	bool          listBoxHeader(const char* label, const float2& size = float2::Zero) noexcept;
	bool          listBoxHeader(const char* label, int items_count, int height_in_items = -1) noexcept;
	void          listBoxFooter() noexcept;

	void          value(const char* prefix, bool b) noexcept;
	void          value(const char* prefix, int v) noexcept;
	void          value(const char* prefix, unsigned int v) noexcept;
	void          value(const char* prefix, float v, const char* float_format = nullptr) noexcept;
	void          valueColor(const char* prefix, const float4& v) noexcept;
	void          valueColor(const char* prefix, std::uint32_t v) noexcept;

	void          setTooltip(const char* fmt, ...) PRINTFARGS(1) noexcept;
	void          setTooltipV(const char* fmt, va_list args) noexcept;
	void          beginTooltip() noexcept;
	void          endTooltip() noexcept;

	bool          beginMainMenuBar() noexcept;
	void          endMainMenuBar() noexcept;
	bool          beginMenuBar() noexcept;
	void          endMenuBar() noexcept;
	bool          beginMenu(const char* label, bool enabled = true) noexcept;
	void          endMenu() noexcept;
	bool          menuItem(const char* label, const char* shortcut = nullptr, bool selected = false, bool enabled = true) noexcept;
	bool          menuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled = true) noexcept;

	void          openPopup(const char* str_id) noexcept;
	bool          beginPopup(const char* str_id) noexcept;
	bool          beginPopupModal(const char* name, bool* isOpened = nullptr, GuiWindowFlags extraFlags = 0) noexcept;
	bool          beginPopupContextItem(const char* str_id, int mouse_button = 1) noexcept;
	bool          beginPopupContextWindow(bool also_over_items = true, const char* str_id = nullptr, int mouse_button = 1) noexcept;
	bool          beginPopupContextVoid(const char* str_id = nullptr, int mouse_button = 1) noexcept;
	void          endPopup() noexcept;
	void          closeCurrentPopup() noexcept;

	void          pushClipRect(const float2& clip_rect_min, const float2& clip_rect_max, bool intersect_with_current_clip_rect) noexcept;
	void          popClipRect() noexcept;

	bool          isItemHovered() noexcept;
	bool          isItemHoveredRect() noexcept;
	bool          isItemActive() noexcept;
	bool          isItemClicked(int mouse_button = 0) noexcept;
	bool          isItemVisible() noexcept;
	bool          isAnyItemHovered() noexcept;
	bool          isAnyItemActive() noexcept;
	float2        getItemRectMin() noexcept;
	float2        getItemRectMax() noexcept;
	float2        getItemRectSize() noexcept;
	void          setItemAllowOverlap() noexcept;
	bool          isWindowHovered() noexcept;
	bool          isWindowFocused() noexcept;
	bool          isRootWindowFocused() noexcept;
	bool          isRootWindowOrAnyChildFocused() noexcept;
	bool          isRootWindowOrAnyChildHovered() noexcept;
	bool          isRectVisible(const float2& size) noexcept;
	bool          isPosHoveringAnyWindow(const float2& pos) noexcept;
	float         getTime() noexcept;
	int           getFrameCount() noexcept;
	const char*   getStyleColName(GuiCol idx) noexcept;
	float2        calcItemRectClosestPoint(const float2& pos, bool on_edge = false, float outward = +0.0f) noexcept;
	float2        calcTextSize(const char* text, const char* text_end = nullptr, bool hide_text_after_double_hash = false, float wrap_width = -1.0f) noexcept;
	void          calcListClipping(int items_count, float items_height, int* out_items_display_start, int* out_items_display_end) noexcept;

	bool          beginChildFrame(GuiID id, const float2& size, GuiWindowFlags extraFlags = 0) noexcept;
	void          endChildFrame() noexcept;

	float4        colorConvertU32ToFloat4(std::uint32_t in) noexcept;
	std::uint32_t colorConvertFloat4ToU32(const float4& in) noexcept;
	void          colorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v) noexcept;
	void          colorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b) noexcept;

	bool          isKeyDown(int key_index) noexcept;
	bool          isKeyPressed(int key_index, bool repeat = true) noexcept;
	bool          isKeyReleased(int key_index) noexcept;
	bool          isMouseDown(int button) noexcept;
	bool          isMouseClicked(int button, bool repeat = false) noexcept;
	bool          isMouseDoubleClicked(int button) noexcept;
	bool          isMouseReleased(int button) noexcept;
	bool          isMouseHoveringWindow() noexcept;
	bool          isMouseHoveringAnyWindow() noexcept;
	bool          isMouseHoveringRect(const float2& min, const float2& max, bool clip = true) noexcept;
	bool          isMouseDragging(int button = 0, float lock_threshold = -1.0f) noexcept;
	float2        getMousePos() noexcept;
	float2        getMousePosOnOpeningCurrentPopup() noexcept;
	float2        getMouseDragDelta(int button = 0, float lock_threshold = -1.0f) noexcept;
	void          resetMouseDragDelta(int button = 0) noexcept;
	void          setMouseCursor(GuiMouseCursor type) noexcept;
	void          captureKeyboardFromApp(bool capture = true) noexcept;
	void          captureMouseFromApp(bool capture = true) noexcept;

private:
	Gui(const Gui&) = delete;
	Gui& operator=(const Gui&) = delete;
};

_NAME_END

#endif