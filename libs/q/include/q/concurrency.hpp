/*
 * Copyright 2015 Gustaf Räntilä
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LIBQ_CONCURRENCY_HPP
#define LIBQ_CONCURRENCY_HPP

#include <q/types.hpp>
#include <q/type_traits.hpp>

namespace q {

class concurrency
{
public:
	enum other
	{
		infinity
	};

	concurrency( other value = other::infinity )
	: value_( std::numeric_limits< std::size_t >::max( ) )
	{ }

	concurrency( std::size_t value )
	: value_( value )
	{ }

	operator std::size_t( ) const
	{
		return value_;
	}

	std::size_t get( ) const
	{
		return value_;
	}

private:
	std::size_t value_;
};

} // namespace q

#endif // LIBQ_CONCURRENCY_HPP