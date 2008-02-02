/*
Heroes of Wesnoth - http://heroesofwesnoth.sf.net
Copyright (C) 2007  Jon Ander Peñalba <jonan88@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>
*/

/// @file
/// Funtion to control general game loops.
/// @author Jonan

#ifndef LOOP_HPP
#define LOOP_HPP

/// Controls a general game loop.
///
/// -no detailed description-
///
/// @param[in] function Funtion to execute in the loop.
void loop(int (*function)(void));

#endif // LOOP_HPP
