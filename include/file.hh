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

#ifndef BASICS_FILE
#define BASICS_FILE

#include <cstdint>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "error.hh"


/*******************************************************************************************************
 *
 * @file  file.hh
 *
 * @brief A streaming I/O pair of shallow C++ wrappers of ::fopen, ::fread, ::fwrite, ::fseek, ::ftell.
 *
 */


namespace basics {
namespace file {


enum mode: uint8_t {
	read,
	write_read,
	write_truncate,
	write_read_truncate,
	write_append,
	write_read_append,
};

enum whence: uint8_t {
	set,
	cur,
	end,
};

static constexpr const char* mode_map[] = {"r", "r+", "w", "w+", "a", "a+"};
static constexpr const int whence_map[] = {SEEK_SET, SEEK_CUR, SEEK_END};


template<size_t BUFFER_SIZE = 1024>
class input {
public:
	input(const char *pathname);
	~input();

	inline bool eos();
	inline char get();

	inline void seek(long offset, whence w);
	inline unsigned long tell();

private:
	static const constexpr char *_name = "basics::file::input";

	FILE *_file;
	char _buffer[BUFFER_SIZE];
	size_t _pos;
	size_t _count;

	inline void _get();
};


template<size_t BUFFER_SIZE = 1024>
class output {
public:
	output(const char *pathname, bool overwrite = false);
	~output();

	inline void put(char value);
	inline void flush();

	inline void seek(long offset, whence w);
	inline unsigned long tell();

private:
	static const constexpr char *_name = "basics::file::output";

	FILE *_file;
	char _buffer[BUFFER_SIZE];
	size_t _pos;

	inline void _put();
};


/******************************************************************************************************/


template<size_t BUFFER_SIZE>
input<BUFFER_SIZE>::input(const char *pathname)
	: _file{::fopen(pathname, mode_map[mode::read])},
	  _buffer{}, _pos{0}, _count{0}
{
	if (_file == nullptr)
		throw error{"%s failed to open file '%s'", _name, pathname};
}


template<size_t BUFFER_SIZE>
input<BUFFER_SIZE>::~input()
{
	::fclose(_file);
}


template<size_t BUFFER_SIZE>
inline bool input<BUFFER_SIZE>::eos()
{
	if (_pos >= _count)
		_get();

	return (_pos >= _count);
}


template<size_t BUFFER_SIZE>
inline char input<BUFFER_SIZE>::get()
{
	if (_pos >= _count)
		_get();

	if (_pos >= _count)
		throw error{"%s::get() premature eos", _name};

	return _buffer[_pos++];
}


template<size_t BUFFER_SIZE>
inline void input<BUFFER_SIZE>::seek(long offset, whence w)
{
	if (::fseek(_file, offset, whence_map[w]) < 0)
		throw error{"%s::seek() %s", _name, strerror(errno)};
}


template<size_t BUFFER_SIZE>
inline unsigned long input<BUFFER_SIZE>::tell()
{
	auto res = ::ftell(_file);
	if (res < 0)
		throw error{"%s::tell() %s", _name, strerror(errno)};

	return res;
}


template<size_t BUFFER_SIZE>
inline void input<BUFFER_SIZE>::_get()
{
	auto count = ::fread(_buffer, 1, BUFFER_SIZE, _file);
	if (count > 0) {
		_pos = 0;
		_count = count;
	}
}


template<size_t BUFFER_SIZE>
output<BUFFER_SIZE>::output(const char *pathname, bool overwrite)
	: _file{::fopen(pathname, mode_map[overwrite? write_truncate : write_append])},
	  _buffer{}, _pos{0}
{
	if (_file == nullptr)
		throw error{"%s failed to open file '%s'", _name, pathname};
}


template<size_t BUFFER_SIZE>
output<BUFFER_SIZE>::~output()
{
	::fclose(_file);
}


template<size_t BUFFER_SIZE>
inline void output<BUFFER_SIZE>::put(char value)
{
	_buffer[_pos++] = value;

	if (_pos >= BUFFER_SIZE)
		_put();
}


template<size_t BUFFER_SIZE>
inline void output<BUFFER_SIZE>::flush()
{
	if (_pos > 0)
		_put();

	if (::fflush(_file) != 0)
		throw error{"%s::flush() %s", _name, strerror(errno)};
}


template<size_t BUFFER_SIZE>
inline void output<BUFFER_SIZE>::seek(long offset, whence w)
{
	if (::fseek(_file, offset, whence_map[w]) < 0)
		throw error{"%s::seek() %s", _name, strerror(errno)};
}


template<size_t BUFFER_SIZE>
inline unsigned long output<BUFFER_SIZE>::tell()
{
	auto res = ::ftell(_file);
	if (res < 0)
		throw error{"%s::tell() %s", _name, strerror(errno)};

	return res;
}


template<size_t BUFFER_SIZE>
inline void output<BUFFER_SIZE>::_put()
{
	if (::fwrite(_buffer, 1, _pos, _file) != _pos)
		throw error{"%s::put() %s", _name, strerror(errno)};

	_pos = 0;
}


} // namespace file
} // namespace basics

#endif // BASICS_FILE
