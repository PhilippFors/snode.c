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

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#include "Request.h"

#include "http_utils.h"

namespace express {

    Request::Request(const http::Request& req)
        : http::Request(req)
        , originalUrl(req.url) {
        url = httputils::str_split_last(originalUrl, '?').first;
        path = httputils::str_split_last(url, '/').first;
        if (path.empty()) {
            path = "/";
        }
    }

    std::string& Request::param(const std::string& id) {
        return params[id];
    }

} // namespace express
