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
#include <string.h>
#include <Arduino.h>
#include "error.h"
//#include "ionlib/log.h"

static const PROGMEM char ion_error_SUCCESS_str[] = "No error occurred";
static const PROGMEM char ion_error_UNKNOWN_str[] = "An unknown error occurred";
static const PROGMEM char ion_error_PARAMETER_str[] = "Parameter was invalid";
static const PROGMEM char ion_error_PARAMETER_VALUE_str[] = "Parameter value was out of range";
static const PROGMEM char ion_error_SOCKET_str[] = "Socket error";
static const PROGMEM char ion_error_QUEUE_EMPTY_str[] = "Queue was empty";
static const PROGMEM char ion_error_QUEUE_FULL_str[] = "Queue was full";
static const PROGMEM char ion_error_TIMEOUT_str[] = "A timeout ocurred";
static const PROGMEM char ion_error_ABANDONED_str[] = "A mutex was abandoned";

static const PROGMEM ion::Error all_errors[ion::Error::COUNT] = {
    { ion::Error::SUCCESS, ion_error_SUCCESS_str },
    { ion::Error::UNKNOWN,ion_error_UNKNOWN_str },
    { ion::Error::PARAMETER,ion_error_PARAMETER_str },
    { ion::Error::PARAMETER_VALUE,ion_error_PARAMETER_VALUE_str },
    { ion::Error::SOCKET, ion_error_SOCKET_str },
    { ion::Error::QUEUE_EMPTY, ion_error_QUEUE_EMPTY_str },
    { ion::Error::QUEUE_FULL, ion_error_QUEUE_FULL_str },
    { ion::Error::TIMEOUT, ion_error_TIMEOUT_str },
    { ion::Error::ABANDONED, ion_error_ABANDONED_str }
};

ion::Error::Error(ion::Error::status_t id, const char* explanation)
{
    this->id_ = id;
    this->explanation_ = explanation;
}

ion::Error::Error(ion::Error::status_t id)
{
    this->id_ = id;
}
ion::Error ion::Error::Get(ion::Error::status_t status)
{
    return all_errors[status];
}

bool ion::Error::operator <(const ion::Error & rhs) const
{
    return (rhs.id_ < this->id_);
}

bool ion::Error::operator==(const ion::Error & rhs) const
{
    return (rhs.id_ == this->id_);
}
bool ion::Error::operator==(const ion::Error::status_t& rhs) const
{
    return this->id_ == rhs;
}
bool ion::Error::operator!=(const ion::Error & rhs) const
{
    return (rhs.id_ != this->id_);
}
bool ion::Error::operator!=(const ion::Error::status_t& rhs) const
{
    return this->id_ != rhs;
}

const char* ion::Error::str() const
{
    return explanation_;
}
