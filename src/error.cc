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
