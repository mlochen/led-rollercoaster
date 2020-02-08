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

#include "colorwave.h"
#include "../ledstrip.h"
#include "../track.h"

#include <math.h>

static double h_min;
static double h_max;

void colorwave__init(void)
{
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
        double h = track__get_height((double)i / LED_COUNT);
        h_min = (h < h_min) ? h : h_min;
        h_max = (h > h_max) ? h : h_max;
    }
}

void colorwave__update(double dt)
{
    static double t = 0;
    t += 2 * dt;
    if (t > 2 * M_PI)
    {
        t -= 2 * M_PI;
    }

    double sin_t = (sin(t) + 1) / 2;

    /* fade out in 250ms */
    ledstrip__sub(255 * dt * 4);

    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
        double h = track__get_height((double)i / LED_COUNT);
        double hf = (h - h_min) / (h_max - h_min);
        double diff = ((hf - sin_t) < 0) ? -(hf - sin_t) : (hf - sin_t);
        if (diff < 0.05f)
        {
            ledstrip__set_led(i, 255, 0, 0);
        }
    }
    ledstrip__show();
}

