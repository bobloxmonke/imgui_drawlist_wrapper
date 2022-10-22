#pragma once

#include <stdint.h>
#include <imgui/imgui_internal.h>

struct vec2_t
{
    float x, y;

    vec2_t() { x = y = 0.0f; }
    vec2_t(const ImVec2& im_vec) { x = im_vec.x; y = im_vec.y; }
    vec2_t(float _x, float _y) { x = _x; y = _y; }
    vec2_t(float scalar) { x = scalar; y = scalar; }

    operator ImVec2() const { return ImVec2(x, y); }

    vec2_t operator+(const vec2_t& vector) const { return vec2_t(x + vector.x, y + vector.y); }
    vec2_t operator-(const vec2_t& vector) const { return vec2_t(x - vector.x, y - vector.y); }
    vec2_t operator*(const vec2_t& vector) const { return vec2_t(x * vector.x, y * vector.y); }
    vec2_t operator/(const vec2_t& vector) const { return vec2_t(x / vector.x, y / vector.y); }

    vec2_t operator+(const float& scalar) const { return vec2_t(x + scalar, y + scalar); }
    vec2_t operator-(const float& scalar) const { return vec2_t(x - scalar, y - scalar); }
    vec2_t operator*(const float& scalar) const { return vec2_t(x * scalar, y * scalar); }
    vec2_t operator/(const float& scalar) const { return vec2_t(x / scalar, y / scalar); }
};

struct color_t
{
    float r, g, b, a;

    color_t() { r = g = b = a = 0.0f; }
    color_t(const ImVec4& im_color) { r = im_color.x; g = im_color.y; b = im_color.z; a = im_color.w; };
    color_t(float _r, float _g, float _b) { r = _r; g = _g; b = _b; a = 1.0f; }
    color_t(float _r, float _g, float _b, float _a) { r = _r; g = _g; b = _b; a = _a; }
    color_t(float scalar) { r = g = b = a = scalar; };
    color_t(float scalar, float _a) { r = g = b = scalar; a = _a; };

    operator ImVec4() const { return ImVec4(r, g, b, a); }
    operator ImU32() const { return ImGui::ColorConvertFloat4ToU32(*this); }
};

enum e_render_flags : uint32_t
{
    render_flags_none = 0,

    render_flags_closed = 1 << 0,

    render_flags_round_corners_top_left = 1 << 4,
    render_flags_round_corners_top_right = 1 << 5,
    render_flags_round_corners_bottom_left = 1 << 6,
    render_flags_round_corners_bottom_right = 1 << 7,
    render_flags_round_corners_none = 1 << 8,
    render_flags_round_corners_top = render_flags_round_corners_top_left | render_flags_round_corners_top_right,
    render_flags_round_corners_bottom = render_flags_round_corners_bottom_left | render_flags_round_corners_bottom_right,
    render_flags_round_corners_left = render_flags_round_corners_bottom_left | render_flags_round_corners_top_left,
    render_flags_round_corners_right = render_flags_round_corners_bottom_right | render_flags_round_corners_bottom_left,
    render_flags_round_corners_all = render_flags_round_corners_top_left | render_flags_round_corners_top_right | render_flags_round_corners_bottom_left | render_flags_round_corners_bottom_right,
    render_flags_round_corners_default = render_flags_round_corners_all,
    render_flags_round_corners_mask = render_flags_round_corners_all | render_flags_round_corners_none,

    render_flags_shadow_cut_out_shape_background = 1 << 9,

    render_flags_centered_x = 1 << 10,
    render_flags_centered_y = 1 << 11,
    render_flags_centered = render_flags_centered_x | render_flags_centered_y,
};

namespace render
{
	inline ImDrawList* draw_list;


    // utility functions
	bool set_draw_list(ImDrawList* draw_list);

    vec2_t get_text_size(const char* text);

    void push_clip_rect(const vec2_t& clip_rect_min, const vec2_t& clip_rect_max, bool intersect_with_current_clip_rect = false);
    void pop_clip_rect();

    // actual drawing functions
    void draw_line(const vec2_t& p1, const vec2_t& p2, const color_t& color, float thickness = 1.0f);
    void draw_rect(const vec2_t& pos, const vec2_t& size, const color_t& color, float rounding = 0.0f, float thickness = 1.0f, uint32_t flags = 0);
    void draw_rect_filled(const vec2_t& pos, const vec2_t& size, const color_t& color, float rounding = 0.0f, uint32_t flags = 0);
    void draw_rect_filled_multicolor(const vec2_t& pos, const vec2_t& size, const color_t& color_upr_left, const color_t& col_upr_right, const color_t& col_bot_right, const color_t& col_bot_left, uint32_t flags = 0);
    void draw_text(const vec2_t& pos, const color_t& color, const char* text, uint32_t flags = 0);
    void draw_triangle(const vec2_t& p1, const vec2_t& p2, const vec2_t& p3, const color_t& color, float thickness = 1.0f);
    void draw_triangle_filled(const vec2_t& p1, const vec2_t& p2, const vec2_t& p3, const color_t& color);
    void draw_circle(const vec2_t& center, float radius, const color_t& color, uint32_t num_segments = 0, float thickness = 1.0f);
    void draw_circle_filled(const vec2_t& center, float radius, const color_t& color, uint32_t num_segments = 0);

    // TODO:

    //IMGUI_API void  AddQuad(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness = 1.0f);
    //IMGUI_API void  AddQuadFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col);
    //IMGUI_API void  AddNgon(const ImVec2& center, float radius, ImU32 col, int num_segments, float thickness = 1.0f);
    //IMGUI_API void  AddNgonFilled(const ImVec2& center, float radius, ImU32 col, int num_segments);
    //IMGUI_API void  AddText(const ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL, float wrap_width = 0.0f, const ImVec4* cpu_fine_clip_rect = NULL);
    //IMGUI_API void  AddPolyline(const ImVec2* points, int num_points, ImU32 col, ImDrawFlags flags, float thickness);
    //IMGUI_API void  AddConvexPolyFilled(const ImVec2* points, int num_points, ImU32 col);
    //IMGUI_API void  AddBezierCubic(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness, int num_segments = 0); // Cubic Bezier (4 control points)
    //IMGUI_API void  AddBezierQuadratic(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col, float thickness, int num_segments = 0);               // Quadratic Bezier (3 control points)
    //IMGUI_API void  AddImage(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min = ImVec2(0, 0), const ImVec2& uv_max = ImVec2(1, 1), ImU32 col = IM_COL32_WHITE);
    //IMGUI_API void  AddImageQuad(ImTextureID user_texture_id, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& uv1 = ImVec2(0, 0), const ImVec2& uv2 = ImVec2(1, 0), const ImVec2& uv3 = ImVec2(1, 1), const ImVec2& uv4 = ImVec2(0, 1), ImU32 col = IM_COL32_WHITE);
    //IMGUI_API void  AddImageRounded(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max, ImU32 col, float rounding, ImDrawFlags flags = 0);
}