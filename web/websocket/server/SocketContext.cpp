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

#include "SocketContext.h"

#include "log/Logger.h"
#include "web/websocket/server/SubProtocol.h"
#include "web/websocket/server/SubProtocolSelector.h"
#include "web/websocket/ws_utils.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#define CLOSE_SOCKET_TIMEOUT 10

namespace web::websocket::server {

    SocketContext::SocketContext(net::socket::stream::SocketConnection* socketConnection, web::websocket::server::SubProtocol* subProtocol)
        : web::websocket::SocketContext(socketConnection, subProtocol, Transmitter::Role::SERVER) {
    }

    SocketContext::~SocketContext() {
        web::websocket::server::SubProtocolSelector::instance()->destroy(subProtocol);
    }

    SocketContext* SocketContext::create(net::socket::stream::SocketConnection* socketConnection,
                                         web::http::server::Request& req,
                                         web::http::server::Response& res) {
        std::string subProtocolName = req.header("sec-websocket-protocol");

        web::websocket::server::SocketContext* context = nullptr;

        web::websocket::server::SubProtocol* subProtocol =
            static_cast<web::websocket::server::SubProtocol*>(web::websocket::server::SubProtocolSelector::instance()->select(subProtocolName));

        if (subProtocol != nullptr) {
            context = new web::websocket::server::SocketContext(socketConnection, subProtocol);

            if (context != nullptr) {
                res.set("Upgrade", "websocket");
                res.set("Connection", "Upgrade");
                res.set("Sec-WebSocket-Protocol", subProtocolName);

                web::websocket::serverWebSocketKey(req.header("sec-websocket-key"), [&res](char* key) -> void {
                    res.set("Sec-WebSocket-Accept", key);
                });

                res.status(101).end(); // Switch Protocol

            } else {
                delete subProtocol;

                res.status(500).end(); // Internal Server Error
            }
        } else {
            res.status(404).end(); // Not Found
        }

        return context;
    }

} // namespace web::websocket::server