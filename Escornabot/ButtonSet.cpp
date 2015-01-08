// ButtonSet.cpp
/*

Copyright (C) 2014 Bricolabs - http://bricolabs.cc

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
USA.

See LICENSE.txt for details

*/

#include "ButtonSet.h"
#include "EventManager.h"
#include <Arduino.h>

extern EventManager* EVENTS;

//////////////////////////////////////////////////////////////////////

ButtonSet::ButtonSet()
{
	for (int b = 0; b < 6; b++)
		this->_button_statuses[b] = 0;
}

//////////////////////////////////////////////////////////////////////

void ButtonSet::pressed(BUTTON button)
{
	button--;
	if (_button_statuses[button] == 0)
	{
		_button_statuses[button] = millis();
	}
}

//////////////////////////////////////////////////////////////////////

void ButtonSet::released(BUTTON button)
{
	button--;
	if (_button_statuses[button] != 0)
	{
		uint32_t pressed_millis = millis() - _button_statuses[button];

		if (pressed_millis > BUTTON_MIN_PRESSED)
		{
			if (pressed_millis < BUTTON_LONG_PRESSED)
			{
				EVENTS->indicateButtonPressed(button + 1);
			}
			else
			{
				EVENTS->indicateButtonLongPressed(button + 1);
			}

			_button_statuses[button] = 0;
		}
	}
}

//////////////////////////////////////////////////////////////////////


// EOF