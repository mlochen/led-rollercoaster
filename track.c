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

#include "track.h"

#include <math.h>
#include <stdint.h>

/* height measures of equally spaced points on the track in mm */
int16_t h[] = { 24,  46,  65,  95, 133, 167, 190, 185, 164, 135,
			   107,  98, 106, 148, 177, 211, 247, 285, 319, 354,
			   395, 423, 466, 502, 530, 546, 553, 562, 571, 581,
			   584, 585, 565, 529, 484, 435, 386, 337, 288, 242,
			   203, 159, 137, 134, 121, 101,  78,  53,  30,  25,
			    63, 110, 145, 157, 151, 132, 114, 103,  96,  77,
			    54,  63,  96, 134, 170, 205, 238, 271, 297, 313,
			   323, 328, 332, 335, 333, 317, 323, 323, 326, 338,
			   365, 405, 452, 491, 494, 498, 488, 488, 468, 435,
			   389, 345, 309, 279, 252, 217, 173, 127,  78,  36};

#define H_LEN (sizeof(h) / sizeof(h[0]))
#define STEP_LENGTH (TRACK_LENGTH / H_LEN)

double track__get_height(double pos)
{
	if (pos < 0.0f || pos >= 1.0f)
	{
		return -1.0f;
	}
	uint8_t i = floor(pos * H_LEN);
	int16_t h1 = h[i];
	int16_t h2 = (i == H_LEN - 1) ? h[0] : h[i + 1];

	int16_t h_diff = h2 - h1;
	double track_pos = pos * TRACK_LENGTH;
	return h1 + ((h_diff * (track_pos - (i * STEP_LENGTH))) / STEP_LENGTH);
}

double track__get_gradient(double pos)
{
	if (pos < 0.0f || pos >= 1.0f)
	{
		return -1.0f;
	}
	uint8_t i = floor(pos * H_LEN);
	int16_t h1 = h[i];
	int16_t h2 = (i == H_LEN - 1) ? h[0] : h[i + 1];
	return asin((double)(h2 - h1) / STEP_LENGTH);
}
