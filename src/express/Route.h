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

#ifndef EXPRESS_ROUTE_H
#define EXPRESS_ROUTE_H

#include "express/MountPoint.h" // IWYU pragma: export

namespace express {

    class State;
    class Dispatcher;

} // namespace express

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <memory>
#include <string>

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

namespace express {

    class Route {
    public:
        Route();
        Route(const std::string& method, const std::string& relativeMountPath, const std::shared_ptr<Dispatcher>& dispatcher);

        bool dispatch(express::State& state, const std::string& parentMountPath);

    protected:
        bool dispatch(express::State& state);

        MountPoint mountPoint;
        std::shared_ptr<Dispatcher> dispatcher;
    };

} // namespace express

#endif // EXPRESS_ROUTE_H
