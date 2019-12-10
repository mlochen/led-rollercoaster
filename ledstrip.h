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

#ifndef __LEDSTRIP_H__
#define __LEDSTRIP_H__

#include <stdint.h>

#define LED_COUNT 300

void ledstrip__init(void);
void ledstrip__clear(void);
void ledstrip__add(uint8_t n);
void ledstrip__sub(uint8_t n);
void ledstrip__set_led(uint16_t led, uint8_t r, uint8_t g, uint8_t b);
void ledstrip__show(void);

#endif
