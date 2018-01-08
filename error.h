/*
This file is part of Ionlib.  Copyright (C) 2016  Tim Sweet

Ionlib is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Ionlib is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Ionlib.If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef ION_ERROR_H_
#define ION_ERROR_H_
#include <Arduino.h>

#define MAX_ERROR_STR_LEN (33)
namespace ion
{
    class Error
    {
    public:
        enum status_t : byte
        {
            SUCCESS,
            UNKNOWN,
            PARAMETER,
            PARAMETER_VALUE,
            SOCKET,
            //Queue
            QUEUE_EMPTY,
            QUEUE_FULL,
            //semaphores
            TIMEOUT,
            ABANDONED,
            COUNT
        };
        Error() : Error(ion::Error::Get(ion::Error::SUCCESS))
        {
        }
        Error(Error::status_t id, const char* explanation);
        static Error Get(Error::status_t status);

        bool operator==(const ion::Error& rhs) const;
        bool operator==(const ion::Error::status_t& rhs) const;
        bool operator!=(const ion::Error& rhs) const;
        bool operator!=(const ion::Error::status_t& rhs) const;
        bool operator <(const ion::Error& rhs) const;
        bool success()
        {
            return id_ == SUCCESS;
        }
        const char* str() const;
    private:
        Error(Error::status_t id);
        Error::status_t id_;

        const PROGMEM char * explanation_;
    };
};
#endif //ION_ERROR_H_