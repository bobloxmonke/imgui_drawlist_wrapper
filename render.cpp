#include "render.h"

bool render::set_draw_list(ImDrawList* draw_list)
{
	if (draw_list == NULL)
	{
		return false;
	}

	render::draw_list = draw_list;

	return true;
}

vec2_t render::get_text_size(const char* text)
{
	return ImGui::CalcTextSize(text);
}

void render::push_clip_rect(const vec2_t& clip_rect_min, const vec2_t& clip_rect_max, bool intersect_with_current_clip_rect)
{
	render::draw_list->PushClipRect(clip_rect_min, clip_rect_max, intersect_with_current_clip_rect);
}

void render::pop_clip_rect()
{
	render::draw_list->PopClipRect();
}

void render::line(const vec2_t& p1, const vec2_t& p2, const color_t& color, float thickness)
{
	render::draw_list->AddLine(p1, p2, color, thickness);
}

void render::rect(const vec2_t& p_min, const vec2_t& p_max, const color_t& color, float rounding, float thickness, uint32_t flags)
{
	vec2_t new_p_min = p_min;
	vec2_t new_p_max = p_max;

	if (flags & render_flags_centered)
	{
		vec2_t rect_size = (p_max - p_min);

		if (!(flags & render_flags_centered_x)) rect_size.x = 0.0f;
		else if (!(flags & render_flags_centered_y)) rect_size.y = 0.0f;

		new_p_min = (new_p_min - rect_size / 2.0f);
		new_p_max = (new_p_max - rect_size / 2.0f);
	}

	render::draw_list->AddRect(new_p_min, new_p_max, color, rounding, flags, thickness);
}

void render::rect_filled(const vec2_t& p_min, const vec2_t& p_max, const color_t& color, float rounding, uint32_t flags)
{
	vec2_t new_p_min = p_min;
	vec2_t new_p_max = p_max;

	if (flags & render_flags_centered)
	{
		vec2_t rect_size = (p_max - p_min);

		if (!(flags & render_flags_centered_x)) rect_size.x = 0.0f;
		else if (!(flags & render_flags_centered_y)) rect_size.y = 0.0f;

		new_p_min = (new_p_min - rect_size / 2.0f);
		new_p_max = (new_p_max - rect_size / 2.0f);
	}

	render::draw_list->AddRectFilled(new_p_min, new_p_max, color, rounding, flags);
}

void render::rect_filled_multicolor(const vec2_t& p_min, const vec2_t& p_max, const color_t& col_upr_left, const color_t& col_upr_right, const color_t& col_bot_right, const color_t& col_bot_left, uint32_t flags)
{
	vec2_t new_p_min = p_min;
	vec2_t new_p_max = p_max;

	if (flags & render_flags_centered)
	{
		vec2_t rect_size = (p_max - p_min);

		if (!(flags & render_flags_centered_x)) rect_size.x = 0.0f;
		else if (!(flags & render_flags_centered_y)) rect_size.y = 0.0f;

		new_p_min = (new_p_min - rect_size / 2.0f);
		new_p_max = (new_p_max - rect_size / 2.0f);
	}

	render::draw_list->AddRectFilledMultiColor(new_p_min, new_p_max, col_upr_left, col_upr_right, col_bot_right, col_bot_left);
}

void render::gradient_vertical(const vec2_t& p_min, const vec2_t& p_max, const color_t& color_upr, const color_t& color_bot, uint32_t flags)
{
	render::rect_filled_multicolor(p_min, p_max, color_upr, color_upr, color_bot, color_bot, flags);
}

void render::gradient_horizontal(const vec2_t& p_min, const vec2_t& p_max, const color_t& color_left, const color_t& color_right, uint32_t flags)
{
	render::rect_filled_multicolor(p_min, p_max, color_left, color_right, color_right, color_left, flags);
}

void render::text(const vec2_t& pos, const color_t& color, const char* text, uint32_t flags)
{
	vec2_t new_pos = pos;
	 
	if (flags & render_flags_centered)
	{
		vec2_t text_size = render::get_text_size(text);

		if (!(flags & render_flags_centered_x)) text_size.x = 0.0f;
		else if (!(flags & render_flags_centered_y)) text_size.y = 0.0f;

		new_pos = (pos - text_size / 2.0f);
	}

	render::draw_list->AddText(new_pos, color, text);
}

void render::triangle(const vec2_t& p1, const vec2_t& p2, const vec2_t& p3, const color_t& color, float thickness)
{
	render::draw_list->AddTriangle(p1, p2, p3, color, thickness);
}

void render::triangle_filled(const vec2_t& p1, const vec2_t& p2, const vec2_t& p3, const color_t& color)
{
	render::draw_list->AddTriangleFilled(p1, p2, p3, color);
}

void render::circle(const vec2_t& center, float radius, const color_t& color, uint32_t num_segments, float thickness)
{
	render::draw_list->AddCircle(center, radius, color, num_segments, thickness);
}

void render::circle_filled(const vec2_t& center, float radius, const color_t& color, uint32_t num_segments)
{
	render::draw_list->AddCircleFilled(center, radius, color, num_segments);
}

void render::image(void* texture_id, const vec2_t& pos, const vec2_t& size, const vec2_t& uv_min, const vec2_t& uv_max, const color_t& color, float rounding, uint32_t flags)
{
	render::draw_list->AddImageRounded(texture_id, pos, pos + size, uv_min, uv_max, color, rounding, flags);
}

void render::polyline(const vec2_t* points, size_t num_points, const color_t& color, float thickness, uint32_t flags)
{
	render::draw_list->AddPolyline((ImVec2*)points, num_points, color, flags, thickness);
}

void render::convex_poly_filled(const vec2_t* points, size_t num_points, const color_t& color)
{
	render::draw_list->AddConvexPolyFilled((ImVec2*)points, num_points, color);
}

void render::ngon(const vec2_t& center, float radius, color_t& color, uint32_t num_segments, float thickness)
{
	render::draw_list->AddNgon(center, radius, color, num_segments, thickness);
}

void render::ngon_filled(const vec2_t& center, float radius, const color_t& color, uint32_t num_segments)
{
	render::draw_list->AddNgonFilled(center, radius, color, num_segments);
}

void render::quad(const vec2_t& p1, const vec2_t& p2, const vec2_t& p3, const vec2_t& p4, const color_t& color, float thickness)
{
	render::draw_list->AddQuad(p1, p2, p3, p4, color, thickness);
}

void render::quad_filled(const vec2_t& p1, const vec2_t& p2, const vec2_t& p3, const vec2_t& p4, const color_t& color)
{
	render::draw_list->AddQuadFilled(p1, p2, p3, p4, color);
}

#ifdef IMGUI_HAS_SHADOWS

void render::shadow_rect(const vec2_t& p_min, const vec2_t& p_max, const color_t& color, float shadow_thickness, const vec2_t& shadow_offset, float rounding, uint32_t flags)
{
	vec2_t new_p_min = p_min;
	vec2_t new_p_max = p_max;

	if (flags & render_flags_centered)
	{
		vec2_t rect_size = (p_max - p_min);

		if (!(flags & render_flags_centered_x)) rect_size.x = 0.0f;
		else if (!(flags & render_flags_centered_y)) rect_size.y = 0.0f;

		new_p_min = (new_p_min - rect_size / 2.0f);
		new_p_max = (new_p_max - rect_size / 2.0f);
	}

	render::draw_list->AddShadowRect(new_p_min, new_p_max, color, shadow_thickness, shadow_offset, flags, rounding);
}

void render::shadow_circle(const vec2_t& center, float radius, const color_t& color, float shadow_thickness, const vec2_t& shadow_offset, uint32_t num_segments, uint32_t flags)
{
	render::draw_list->AddShadowCircle(center, radius, color, shadow_thickness, shadow_offset, flags, num_segments);
}

void render::shadow_convex_poly(const vec2_t* points, size_t num_points, const color_t& color, float shadow_thickness, const vec2_t& shadow_offset, uint32_t flags)
{
	render::draw_list->AddShadowConvexPoly((ImVec2*)points, num_points, color, shadow_thickness, shadow_offset, flags);
}

void render::shadow_quad(const vec2_t& p1, const vec2_t& p2, const vec2_t& p3, const vec2_t& p4, const color_t& color, float shadow_thickness, const vec2_t& shadow_offset, float rounding, uint32_t flags)
{
	vec2_t points[] =
	{
		p1, p2, p3, p4
	};

	render::shadow_convex_poly(points, 4, color, shadow_thickness, shadow_offset, flags);
}

void render::shadow_ngon(const vec2_t& center, float radius, const color_t& color, float shadow_thickness, const vec2_t& shadow_offset, uint32_t num_segments, uint32_t flags)
{
	render::draw_list->AddShadowNGon(center, radius, color, shadow_thickness, shadow_offset, flags, num_segments);
}

#endif