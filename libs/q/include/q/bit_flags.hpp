/*
 * Copyright 2016 Gustaf Räntilä
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

#ifndef LIBQ_BIT_FLAGS_HPP
#define LIBQ_BIT_FLAGS_HPP

#include <q/type_traits.hpp>

namespace q {

/**
 * Editable bitmap with a certain compile-time known number of bits.
 *
 * Consumes only as many bytes as necessary.
 */
template< std::size_t Bits >
class bit_flags
{
public:
	typedef std::integral_constant<
		std::size_t,
		( Bits + 7 ) / 8
	> byte_size;

	bit_flags( )
	{
		std::memset( bytes, 0, byte_size::value );
	}

	void set( std::size_t index, bool value = true )
	{
		if ( index + 1 > Bits )
			throw std::out_of_range( "Bit is out of range" );

		std::size_t byte_index = index / 8;
		std::size_t bit_index = 7 - ( index - byte_index * 8 );
		std::uint8_t bit_byte = std::uint8_t( 1 ) << bit_index;

		if ( value )
			bytes[ byte_index ] |= bit_byte;
		else
			bytes[ byte_index ] &= ~bit_byte;
	}

	void unset( std::size_t index )
	{
		if ( index + 1 > Bits )
			throw std::out_of_range( "Bit is out of range" );

		set( index, false );
	}

	bool is_set( std::size_t index ) const
	{
		if ( index + 1 > Bits )
			throw std::out_of_range( "Bit is out of range" );

		std::size_t byte_index = index / 8;
		std::size_t bit_index = 7 - ( index - byte_index * 8 );
		std::uint8_t bit_byte = std::uint8_t( 1 ) << bit_index;

		return bytes[ byte_index ] & bit_byte;
	}

private:
	std::uint8_t bytes[ byte_size::value ];
};

template< typename... T >
class bit_flags_of_types
: bit_flags< sizeof...( T ) >
{
public:
	typedef q::arguments< T... > args;

	static_assert(
		are_all_unique< T... >::value,
		"bit flag types must be unique"
	);

	template< typename First, typename... Rest >
	typename std::enable_if<
		args::template has< First >::value
		and
		( sizeof...( Rest ) > 0 )
	>::type
	set_by_type( bool value = true )
	{
		this->set( args::template index_of< First >::value, value );
		set_by_type< Rest... >( value );
	}

	template< typename First >
	typename std::enable_if<
		args::template has< First >::value
	>::type
	set_by_type( bool value = true )
	{
		this->set( args::template index_of< First >::value, value );
	}

	template< typename... U >
	typename std::enable_if<
		sizeof...( U ) == 0
	>::type
	set_by_type( bool = true )
	{ }

	template< typename First, typename... Rest >
	typename std::enable_if<
		args::template has< First >::value
		and
		( sizeof...( Rest ) > 0 )
	>::type
	unset_by_type( )
	{
		this->unset( args::template index_of< First >::value );
		unset_by_type< Rest... >( );
	}

	template< typename First >
	typename std::enable_if<
		args::template has< First >::value
	>::type
	unset_by_type( )
	{
		this->unset( args::template index_of< First >::value );
	}

	template< typename... U >
	typename std::enable_if<
		sizeof...( U ) == 0
	>::type
	unset_by_type( )
	{ }

	template< typename U >
	typename std::enable_if<
		args::template has< U >::value,
		bool
	>::type
	is_set_by_type( ) const
	{
		return this->is_set( args::template index_of< U >::value );
	}
};

} // namespace q

#endif // LIBQ_BIT_FLAGS_HPP
