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

#include "rollercoaster.h"
#include "../track.h"
#include "../ledstrip.h"

#include <math.h>
#include <stdlib.h>

#define N 3                     /* number of lights */
#define G 1.0f                  /* gravity factor */

struct dot {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	double pos; 		/* m */
	double speed;       /* m/s */
	double mass;        /* kg */
	double friction;    /* coefficient of friction */
	double timeout;
};

static struct dot dot[N];

static void dot_init(struct dot *dot);
static void dot_update(struct dot *dot, double dt);

void rollercoaster__init(void)
{
	for (uint8_t i = 0; i < N; i++)
	{
		dot_init(&dot[i]);
	}
}

void rollercoaster__update(double dt)
{
	/* fade out in 125ms */
	ledstrip__sub(255 * dt * 8);

	for (uint8_t i = 0; i < N; i++)
	{
		dot_update(&dot[i], dt);
	}

	ledstrip__show();
}

static void dot_init(struct dot *dot)
{
	uint8_t rgb = 0xB2 >> (rand() % 6);
	dot->r = ((rgb & 4) >> 2) * 255;
	dot->g = ((rgb & 2) >> 1) * 255;
	dot->b = ((rgb & 1) >> 0) * 255;
	dot->pos = rand() / ((double)RAND_MAX + 1);
	dot->speed = ((rand() % 190) * 0.01f + 0.1f) * ((rand() & 1) ? 1 : -1);
	dot->mass = 10.0f;
	dot->friction = 0.1f;
	dot->timeout = 0.0f;
}

static void dot_update(struct dot *dot, double dt)
{
	double f_g = dot->mass * G;
	double f_n = f_g * sin(track__get_gradient(dot->pos));
	double f_r = fabs(f_n * dot->friction);

	double a = (-f_n - ((dot->speed > 0) ? f_r : -f_r)) / dot->mass;
	double oldspeed = dot->speed;
	dot->speed += a * dt;
	dot->pos += dot->speed * dt / (TRACK_LENGTH / 1000.0f);

	while (dot->pos >= 1.0f)
	{
		dot->pos -= 1.0f;
	}
	while (dot->pos < 0.0f)
	{
		dot->pos += 1.0f;
	}

	/* direction changed */
	if (oldspeed * dot->speed < 0)
	{
		/* reinitialize the dot when the time between
		 * two direction changes is less than 1s */
		if (dot->timeout < 1)
		{
			dot_init(dot);
		}
		else
		{
			dot->timeout = 0;
		}
	}
	dot->timeout += dt;

	uint16_t ledpos = (dot->pos * LED_COUNT);
	uint16_t ledposa = (ledpos == LED_COUNT - 1) ? 0 : ledpos + 1;
	uint16_t ledposb = (ledpos == 0) ? LED_COUNT - 1 : ledpos - 1;

	ledstrip__set_led(ledposb, dot->r, dot->g, dot->b);
	ledstrip__set_led(ledpos, dot->r, dot->g, dot->b);
	ledstrip__set_led(ledposa, dot->r, dot->g, dot->b);
}
