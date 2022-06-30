/*
 * snode.c - a slim toolkit for network communication
 * Copyright (C) 2020, 2021, 2022 Volker Christian <me@vchrist.at>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "net/l2/stream/SocketServer.hpp"
#include "net/l2/stream/tls/config/ConfigSocketServer.h" // IWYU pragma: keep
#include "net/stream/ServerSocket.hpp"                   // IWYU pragma: keep

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#endif // DOXYGEN_SHOULD_SKIP_THIS

template class net::l2::stream::SocketServer<net::l2::stream::tls::config::ConfigSocketServer>;
template class net::stream::ServerSocket<net::l2::stream::tls::config::ConfigSocketServer, net::l2::stream::Socket>;
template class net::SocketConfig<net::l2::stream::tls::config::ConfigSocketServer>;
