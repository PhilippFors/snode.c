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

#ifndef CORE_SELECT_DESCRIPTOREVENTDISPATCHER_H
#define CORE_SELECT_DESCRIPTOREVENTDISPATCHER_H

#include "core/DescriptorEventDispatcher.h"
#include "core/system/select.h" // IWYU pragma: keep
#include "utils/Timeval.h"

namespace core {
    class EventReceiver;
} // namespace core

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include <list>
#include <map>

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

namespace core::select {

    class DescriptorEventDispatcher : public core::DescriptorEventDispatcher {
        DescriptorEventDispatcher(const DescriptorEventDispatcher&) = delete;
        DescriptorEventDispatcher& operator=(const DescriptorEventDispatcher&) = delete;

    private:
        class FdSet {
        public:
            FdSet();

            void set(int fd);
            void clr(int fd);
            int isSet(int fd) const;
            void zero();
            fd_set& get();

        protected:
            fd_set registered;
            fd_set active;
        };

    public:
        DescriptorEventDispatcher() = default;

        void enable(EventReceiver* eventReceiver) override;
        void disable(EventReceiver* eventReceiver) override;
        void suspend(EventReceiver* eventReceiver) override;
        void resume(EventReceiver* eventReceiver) override;

        int getMaxFd() const;
        fd_set& getFdSet();

        utils::Timeval getNextTimeout(const utils::Timeval& currentTime) const;

        void observeEnabledEvents() override;
        void dispatchActiveEvents(const utils::Timeval& currentTime) override;
        void unobserveDisabledEvents(const utils::Timeval& currentTime) override;
        void stop() override;

    private:
        unsigned long getEventCounter() const override;

        class EventReceiverList : public std::list<EventReceiver*> {
        public:
            using std::list<EventReceiver*>::begin;
            using std::list<EventReceiver*>::end;
            using std::list<EventReceiver*>::front;

            bool contains(EventReceiver* descriptorEventReceiver) const;
        };

        std::map<int, EventReceiverList> enabledEventReceiver;
        std::map<int, EventReceiverList> observedEventReceiver;
        std::map<int, EventReceiverList> disabledEventReceiver;

        FdSet fdSet;

        unsigned long eventCounter = 0;
    };

} // namespace core::select

#endif // CORE_SELECT_DESCRIPTOREVENTDISPATCHER_H