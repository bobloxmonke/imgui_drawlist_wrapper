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

    color_t from_hsv(float h, float s, float v, float _a = 1.0f) { float _r, _g, _b; ImGui::ColorConvertHSVtoRGB(h, s, v, _r, _g, _b); return color_t(_r, _g, _b, _a); }
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

    bool set_draw_list(ImDrawList* draw_list);

    vec2_t get_text_size(const char* text);

    void push_clip_rect(const vec2_t& clip_rect_min, const vec2_t& clip_rect_max, bool intersect_with_current_clip_rect = false);
    void pop_clip_rect();

    void line(const vec2_t& p1, const vec2_t& p2, const color_t& color, float thickness = 1.0f);
    void rect(const vec2_t& p_min, const vec2_t& p_max, const color_t& color, float rounding = 0.0f, float thickness = 1.0f, uint32_t flags = 0);
    void rect_filled(const vec2_t& p_min, const vec2_t& p_max, const color_t& color, float rounding = 0.0f, uint32_t flags = 0);
    void rect_filled_multicolor(const vec2_t& p_min, const vec2_t& p_max, const color_t& color_upr_left, const color_t& col_upr_right, const color_t& col_bot_right, const color_t& col_bot_left, uint32_t flags = 0);
    void text(const vec2_t& pos, const color_t& color, const char* text, uint32_t flags = 0);
    void triangle(const vec2_t& p1, const vec2_t& p2, const vec2_t& p3, const color_t& color, float thickness = 1.0f);
    void triangle_filled(const vec2_t& p1, const vec2_t& p2, const vec2_t& p3, const color_t& color);
    void circle(const vec2_t& center, float radius, const color_t& color, uint32_t num_segments = 0, float thickness = 1.0f);
    void circle_filled(const vec2_t& center, float radius, const color_t& color, uint32_t num_segments = 0);
    void image(void* user_texture_id, const vec2_t& pos, const vec2_t& size, const vec2_t& uv_min = vec2_t(0, 0), const vec2_t& uv_max = vec2_t(1, 1), const color_t& color = color_t(1), float rounding = 0.0f, uint32_t flags = 0);
    void polyline(const vec2_t* points, size_t num_points, const color_t& color, float thickness = 1.0f, uint32_t flags = 0);
    void convex_poly_filled(const vec2_t* points, size_t num_points, const color_t& color);
    void ngon(const vec2_t& center, float radius, color_t& color, uint32_t num_segments, float thickness = 1.0f);
    void ngon_filled(const vec2_t& center, float radius, const color_t& color, uint32_t num_segments);
    void quad(const vec2_t& p1, const vec2_t& p2, const vec2_t& p3, const vec2_t& p4, const color_t& color, float thickness = 1.0f);
    void quad_filled(const vec2_t& p1, const vec2_t& p2, const vec2_t& p3, const vec2_t& p4, const color_t& color);

    //void bezier_curve_cubic(const vec2_t& p1, const vec2_t& p2, const vec2_t& p3, const vec2_t& p4, ImU32 col, float thickness, int num_segments = 0);
    //void bezier_curve_quadratic(const vec2_t& p1, const vec2_t& p2, const vec2_t& p3, const color_t& color, float thickness, uint32_t num_segments = 0);
    //void image_quad(void* user_texture_id, const vec2_t& p1, const vec2_t& p2, const vec2_t& p3, const vec2_t& p4, const vec2_t& uv1 = vec2_t(0, 0), const vec2_t& uv2 = vec2_t(1, 0), const vec2_t& uv3 = vec2_t(1, 1), const vec2_t& uv4 = vec2_t(0, 1), const color_t& color = color_t(1));

#ifdef IMGUI_HAS_SHADOWS
    void shadow_rect(const vec2_t& p_min, const vec2_t& p_max, const color_t& color, float shadow_thickness, const vec2_t& shadow_offset = vec2_t(0, 0), float rounding = 0.0f, uint32_t flags = 0);
    void shadow_circle(const vec2_t& center, float radius, const color_t& color, float shadow_thickness, const vec2_t& shadow_offset = vec2_t(0, 0), uint32_t num_segments = 12, uint32_t flags = 0);
    void shadow_convex_poly(const vec2_t* points, size_t num_points, const color_t& color, float shadow_thickness, const vec2_t& shadow_offset = vec2_t(0, 0), uint32_t flags = 0);
    void shadow_ngon(const vec2_t& center, float radius, const color_t& color, float shadow_thickness, const vec2_t& shadow_offset, uint32_t num_segments, uint32_t flags);
#endif
}