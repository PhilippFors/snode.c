/*
 * snode.c - a slim toolkit for network communication
 * Copyright (C) 2020 Volker Christian <me@vchrist.at>
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

#ifndef EXPRESS_TLS_WEBAPP_H
#define EXPRESS_TLS_WEBAPP_H

#include "express/WebAppT.h"
#include "http/server/tls/Server.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

namespace express::tls {

    class WebApp : public WebAppT<http::server::tls::Server<express::Request, express::Response>> {
    public:
        using WebAppT<http::server::tls::Server<express::Request, express::Response>>::WebAppT;
    };

    class WebApp6 : public WebAppT<http::server::tls::Server6<express::Request, express::Response>> {
    public:
        using WebAppT<http::server::tls::Server6<express::Request, express::Response>>::WebAppT;
    };

} // namespace express::tls

#endif // EXPRESS_TLS_WEBAPP_H
