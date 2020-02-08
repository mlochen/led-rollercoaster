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

#include "stars.h"
#include "../ledstrip.h"

#include <stdlib.h>

#define STAR_RATE 100          /* stars per second */

void stars__init(void)
{
}

void stars__update(double dt)
{
    static double t = 0;
    t += dt;

    /* fade out in 500ms */
    ledstrip__sub(255 * dt * 2);

    while(t > (1.0f / STAR_RATE))
    {
        ledstrip__set_led(rand() % LED_COUNT, 255, 255, 255);
        t -= (1.0f / STAR_RATE);
    }
    ledstrip__show();
}

