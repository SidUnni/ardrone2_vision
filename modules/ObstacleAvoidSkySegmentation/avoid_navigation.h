/*
 * Copyright (C) 2012-2013
 *
 * This file is part of Paparazzi.
 *
 * Paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * Paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#ifndef AVOID_NAVIGATION_H_
#define AVOID_NAVIGATION_H_

#include <std.h>

struct AvoidNavigationStruct {
  uint8_t mode; ///< 0 = nothing, 1 =  climb, 2 = sideways, ...
  //float meters_climbed;
  int climb_extra_when_clear_timer;

  // settings
  int setting_climb_extra_climb_timer;
  int setting_climb_bin_threshold;
  float setting_climb_speed;
};

/** global VIDEO state */
extern struct AvoidNavigationStruct avoid_navigation_data;


void init_avoid_navigation(void);
void run_avoid_navigation_onvision(void);


#endif /* AVOID_NAVIGATION_H_ */
