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

#ifndef BASICS_BASE64
#define BASICS_BASE64

#include <string>


/*******************************************************************************************************
 *
 * @file   base64.hh
 *
 * @brief  A fast C++ base64 decoder component.
 *
 */


namespace basics {
namespace base64 {


std::string decode(const void* data, const size_t len);


}  // namespace base64
}  // namespace basics

#endif // BASICS_BASE64
