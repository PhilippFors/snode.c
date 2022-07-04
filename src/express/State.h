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

#ifndef EXPRESS_DISPATCHER_STATE_H
#define EXPRESS_DISPATCHER_STATE_H

namespace express {

    class Request;
    class Response;
    class Route;
    class RootRoute;

    namespace dispatcher {

        class RouterDispatcher;
        class ApplicationDispatcher;
        class MiddlewareDispatcher;

    } // namespace dispatcher

} // namespace express

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <string>

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

namespace express {

    class State {
    private:
    public:
        explicit State(RootRoute* rootRoute);
        State(Request& request, Response& response);

        void setCurrentRoute(Route* newCurrentRoute);

        Request* getRequest() const;
        Response* getResponse() const;

        int getFlags() const;

        bool breakDispatch(Route& route);

        void setRootRoute(RootRoute* rootRoute) {
            this->rootRoute = rootRoute;

            lastRoute = currentRoute;
            currentRoute = nullptr;
        }

        enum Flags { NON = 0, INH = 1 << 0, NXT = 1 << 1 };

    private:
        RootRoute* rootRoute = nullptr;

        Request* request = nullptr;
        Response* response = nullptr;

        Route* lastRoute = nullptr;
        Route* currentRoute = nullptr;

        mutable int flags = NON;

        friend class Next;
    };

    class Next {
    public:
        explicit Next(State& state);
        void operator()(const std::string& how = "") const;

    private:
        State state;
    };

} // namespace express

#endif // EXPRESS_DISPATCHER_STATE_H
