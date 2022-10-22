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

void render::rect(const vec2_t& pos, const vec2_t& size, const color_t& color, float rounding, float thickness, uint32_t flags)
{
	vec2_t new_pos = pos;

	if (flags & render_flags_centered)
	{
		vec2_t rect_size = size;

		if (!(flags & render_flags_centered_x)) rect_size.x = 0.0f;
		else if (!(flags & render_flags_centered_y)) rect_size.y = 0.0f;

		new_pos = (new_pos - rect_size / 2.0f);
	}

	render::draw_list->AddRect(new_pos, new_pos + size, color, rounding, flags, thickness);
}

void render::rect_filled(const vec2_t& pos, const vec2_t& size, const color_t& color, float rounding, uint32_t flags)
{
	vec2_t new_pos = pos;

	if (flags & render_flags_centered)
	{
		vec2_t rect_size = size;

		if (!(flags & render_flags_centered_x)) rect_size.x = 0.0f;
		else if (!(flags & render_flags_centered_y)) rect_size.y = 0.0f;

		new_pos = (new_pos - rect_size / 2.0f);
	}

	render::draw_list->AddRectFilled(new_pos, new_pos + size, color, rounding, flags);
}

void render::rect_filled_multicolor(const vec2_t& pos, const vec2_t& size, const color_t& col_upr_left, const color_t& col_upr_right, const color_t& col_bot_right, const color_t& col_bot_left, uint32_t flags)
{
	vec2_t new_pos = pos;

	if (flags & render_flags_centered)
	{
		vec2_t rect_size = size;

		if (!(flags & render_flags_centered_x)) rect_size.x = 0.0f;
		else if (!(flags & render_flags_centered_y)) rect_size.y = 0.0f;

		new_pos = (new_pos - rect_size / 2.0f);
	}

	render::draw_list->AddRectFilledMultiColor(new_pos, new_pos + size, col_upr_left, col_upr_right, col_bot_right, col_bot_left);
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