/*
 * Copyright (C) 2019 Marco Lochen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "rainbow.h"
#include "../ledstrip.h"
#include "../track.h"

#include <math.h>

static double h_min;
static double h_max;

static void mcs2rgb(double d, double *r, double *g, double *b);

void rainbow__init(void)
{
	for (uint16_t i = 0; i < LED_COUNT; i++)
	{
		double h = track__get_height((double)i / LED_COUNT);
		h_min = (h < h_min) ? h : h_min;
		h_max = (h > h_max) ? h : h_max;
	}
}

void rainbow__update(double dt)
{
	static double t = 0;
	t += dt;
	if (t > 3.0f)
	{
		t -= 3.0f;
	}

	for (uint16_t i = 0; i < LED_COUNT; i++)
	{
		double h = track__get_height((double)i / LED_COUNT);
		double hf = (h - h_min) / (h_max - h_min);

		double hc = (hf * 3) + t;
		hc = (hc >= 3) ? (hc - 3) : hc;

		static double r, g, b;
		mcs2rgb(hc, &r, &g, &b);
		ledstrip__set_led(i, r * 255, g * 255, b * 255);
	}
	ledstrip__show();
}

static void mcs2rgb(double d, double *r, double *g, double *b)
{
	uint8_t hi = floor(d);
	double f = d - hi;
	double q = (1 - f);
	switch (hi)
	{
		case 0: *r = f; *g = 0; *b = q; break;
		case 1: *r = q; *g = f; *b = 0; break;
		case 2: *r = 0; *g = q; *b = f; break;
	}
}
