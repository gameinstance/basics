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

#ifndef BASICS_ERROR
#define BASICS_ERROR

#include <cstdio>
#include <cstring>


/*******************************************************************************************************
 *
 * @file   error.hh
 *
 * @brief  A lightweight, appendable message carying, C++ error component.
 *
 */


namespace basics {


class error {
public:
	explicit error(const char *message);
	template<typename ...ARGS>
	error(const char *format, ARGS ... args);

	void dump() const;

	template<typename ...ARGS>
	void append(const char *format, ARGS ... args);
	void append(const char *message);

private:
	static const constexpr size_t _buffer_max_size = 256;

	char _message[_buffer_max_size];

	inline void _append_delimiter();
	template<typename ...ARGS>
	inline void _format_nothrow(const char *format, ARGS ...args);
};


/******************************************************************************************************/


template<typename ...ARGS>
error::error(const char *format, ARGS ... args)
	: _message{}
{
	_format_nothrow(format, args...);
}


template<typename ...ARGS>
void error::append(const char *format, ARGS ... args)
{
	_append_delimiter();

	_format_nothrow(format, args...);
}


inline void error::_append_delimiter()
{
	if (std::strlen(_message) + 3 > _buffer_max_size)
		return;

	std::strcat(_message, "; ");
}


template<typename ...ARGS>
inline void error::_format_nothrow(const char *format, ARGS ...args)
{
	std::snprintf(_message + std::strlen(_message), _buffer_max_size - std::strlen(_message), format,
																							args...);
}


} // namespace basics

#endif // BASICS_ERROR
