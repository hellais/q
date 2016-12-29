/*
 * Copyright 2014 Gustaf Räntilä
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

#ifndef LIBQIO_INTERNAL_INTERNALS_HPP
#define LIBQIO_INTERNAL_INTERNALS_HPP

#include <q-io/event.hpp>
#include <q-io/dispatcher.hpp>
#include <q-io/dns.hpp>
#include <q-io/tcp_socket.hpp>
#include <q-io/server_socket.hpp>
#include <q-io/timer_task.hpp>

#include <queue>

#include "impl/dispatcher.hpp"
#include "impl/server_socket.hpp"
#include "impl/tcp_socket.hpp"

#include "uv.hpp"

#include <unistd.h>

#ifdef LIBQ_ON_WINDOWS
#	include <winsock2.h>
#	define ioctl ioctlsocket
#else
#	include <sys/ioctl.h>
#endif

namespace q { namespace io {


// TODO: Reconsider, potentially remove
struct event::pimpl
{
	std::weak_ptr< dispatcher > dispatcher;
};

} } // namespace io, namespace q

#endif // LIBQIO_INTERNAL_INTERNALS_HPP