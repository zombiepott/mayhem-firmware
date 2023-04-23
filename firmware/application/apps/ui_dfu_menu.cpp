/*
 * Copyright (C) 2023 Bernd Herzog
 *
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "ui_dfu_menu.hpp"
#include "portapack_shared_memory.hpp"

namespace ui {

DfuMenu::DfuMenu(NavigationView& nav) : nav_ (nav) {
	add_children({
		&text_head,
		&labels,
		&text_info_line_1,
		&text_info_line_2,
		&text_info_line_3,
		&text_info_line_4,
		&text_info_line_5,
		&text_info_line_6,
		&text_info_line_7
	});
}

void DfuMenu::paint(Painter& painter) {
	auto now = chTimeNow();
	auto idle_ticks = chThdGetTicks(chSysGetIdleThread());
	
	static systime_t last_time;
	static systime_t last_last_time;

	auto time_elapsed = now - last_time;
	auto idle_elapsed = idle_ticks - last_last_time;

	last_time = now;
	last_last_time = idle_ticks;

	text_info_line_1.set(to_string_dec_uint(chCoreStatus(), 6));
	text_info_line_2.set(to_string_dec_uint((uint32_t)get_free_stack_space(), 6));
	text_info_line_3.set(to_string_dec_uint((time_elapsed - idle_elapsed) / 10, 6));
	text_info_line_4.set(to_string_dec_uint(shared_memory.m4_heap_usage, 6));
	text_info_line_5.set(to_string_dec_uint(shared_memory.m4_stack_usage, 6));
	text_info_line_6.set(to_string_dec_uint(shared_memory.m4_cpu_usage, 6));
	text_info_line_7.set(to_string_dec_uint(chTimeNow()/1000, 6));

	constexpr auto margin = 5;

	painter.fill_rectangle(
		{
			{6 * CHARACTER_WIDTH - margin, 3 * LINE_HEIGHT - margin},
			{15 * CHARACTER_WIDTH + margin * 2, 9 * LINE_HEIGHT + margin * 2}
		},
		ui::Color::black()
	);

	painter.fill_rectangle(
		{
			{5 * CHARACTER_WIDTH - margin, 3 * LINE_HEIGHT - margin},
			{CHARACTER_WIDTH, 9 * LINE_HEIGHT + margin * 2}
		},
		ui::Color::dark_cyan()
	);

	painter.fill_rectangle(
		{
			{21 * CHARACTER_WIDTH + margin, 3 * LINE_HEIGHT - margin},
			{CHARACTER_WIDTH, 9 * LINE_HEIGHT + margin * 2}
		},
		ui::Color::dark_cyan()
	);

	painter.fill_rectangle(
		{
			{5 * CHARACTER_WIDTH - margin, 3 * LINE_HEIGHT - margin - 8},
			{17 * CHARACTER_WIDTH + margin * 2, 8}
		},
		ui::Color::dark_cyan()
	);

	painter.fill_rectangle(
		{
			{5 * CHARACTER_WIDTH - margin, 12 * LINE_HEIGHT + margin},
			{17 * CHARACTER_WIDTH + margin * 2, 8}
		},
		ui::Color::dark_cyan()
	);
}

} /* namespace ui */
