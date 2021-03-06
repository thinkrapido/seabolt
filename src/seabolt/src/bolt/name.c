/*
 * Copyright (c) 2002-2019 "Neo4j,"
 * Neo4j Sweden AB [http://neo4j.com]
 *
 * This file is part of Neo4j.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "bolt-private.h"
#include "name.h"

int get_address_components(volatile const struct sockaddr_storage* address, char* host_buffer, int host_buffer_size,
        char* port_buffer,
        int port_buffer_size)
{
    int flags = 0;
    int address_size = address->ss_family==AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);

    if (host_buffer!=NULL) {
        flags = flags | NI_NUMERICHOST;
    }
    else {
        host_buffer_size = 0;
    }

    if (port_buffer!=NULL) {
        flags = flags | NI_NUMERICSERV;
    }
    else {
        port_buffer_size = 0;
    }

    return getnameinfo((const struct sockaddr*) address, address_size, host_buffer, host_buffer_size, port_buffer,
            port_buffer_size, flags);
}
