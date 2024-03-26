/* Copyright (C) 2024  Bogdan-Gabriel Alecu  (GameInstance.com)
 *
 * basics - Essential C++ components for non-trivial applications.
 *
 * This library is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#include "error.hh"
#include <cstring>


namespace basics {


error::error(const char *message)
	: _message{}
{
	std::strncpy(_message, message, _buffer_max_size - 1);
}


void error::dump() const
{
	fprintf(stderr, "ERROR: %s\n", _message);
}


void error::append(const char *message)
{
	_append_delimiter();

	auto message_len = std::strlen(_message);
	if (message_len + 1 >= _buffer_max_size)
		return;

	std::strncat(_message, message, _buffer_max_size - message_len - 1);
}


} // namespace basics
