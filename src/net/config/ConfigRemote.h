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

#ifndef NET_CONFIGREMOTE_H
#define NET_CONFIGREMOTE_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include "utils/Config.h"

#endif // DOXYGEN_SHOULD_SKIP_THIS

namespace net::config {

    template <typename SocketAddressT>
    class ConfigRemote {
    protected:
        ConfigRemote() = default;
        virtual ~ConfigRemote() = default;

        using SocketAddress = SocketAddressT;

    public:
        const SocketAddress& getRemoteAddress() {
            if (!initialized) {
                utils::Config::instance().parse(true); // Try command line parsing in case Address is not initialized using setLocalAddress

                remoteAddress = getAddress();
                initialized = true;
            } else if (!updated) {
                updateFromCommandLine();
                updated = true;
            }

            return remoteAddress;
        }

        void setRemoteAddress(const SocketAddress& remoteAddress) {
            this->remoteAddress = remoteAddress;
            this->initialized = true;
        }

    private:
        virtual void updateFromCommandLine() = 0;

        virtual SocketAddress getAddress() const = 0;
        virtual bool isPresent() const = 0;

    protected:
        SocketAddress remoteAddress;

    private:
        bool initialized = false;
        bool updated = false;
    };

} // namespace net::config

#endif // CONFIGREMOTE_H