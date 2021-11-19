/*
 * snode.c - a slim toolkit for network communication
 * Copyright (C) 2020, 2021 Volker Christian <me@vchrist.at>
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

#ifndef NET_SOCKET_IP_TRANSPORT_TCP_LEGACY_IPV4_SOCKETCLIENT_H
#define NET_SOCKET_IP_TRANSPORT_TCP_LEGACY_IPV4_SOCKETCLIENT_H

#include "net/socket/ip/socket/ipv4/stream/ClientSocket.h"   // IWYU pragma: export
#include "net/socket/ip/transport/tcp/legacy/SocketClient.h" // IWYU pragma: export

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#endif // DOXYGEN_SHOULD_SKIP_THIS

namespace net::socket::ip::transport::tcp::legacy::ipv4 {

    template <typename SocketContextFactoryT>
    using SocketClient = net::socket::ip::transport::tcp::legacy::SocketClient<socket::ipv4::stream::ClientSocket, SocketContextFactoryT>;

} // namespace net::socket::ip::transport::tcp::legacy::ipv4

#endif // NET_SOCKET_IP_TRANSPORT_TCP_LEGACY_IPV4_SOCKETCLIENT_H