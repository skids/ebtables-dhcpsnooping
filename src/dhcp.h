/**
 *  This file is part of ebtables-dhcpsnoopingd.
 *
 *  Ebtables-dhcpsnoopingd is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Ebtables-dhcpsnoopingd is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ebtables-dhcpsnoopingd.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 *  (C) 2013, Michael Braun <michael-dev@fami-braun.de>
 */

#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

enum t_lease_update_src { UPDATED_LEASE_FROM_DHCP, UPDATED_LEASE_FROM_UDP, UPDATED_LEASE_FROM_SQL };

typedef void* (*is_local_cb)(const uint8_t* mac, const char* ifname);
typedef int (*update_lease_cb)(const char* ifname, const uint8_t* mac, const struct in_addr* ip, uint32_t* expiresAt);
typedef void (*updated_lease_cb)(const uint8_t* mac, const struct in_addr* yip, const char* ifname, const uint32_t expiresAt, const enum t_lease_update_src reason);
typedef void (*lease_cb)(const struct in_addr* yip, const uint8_t* mac, const char* ifname, const uint32_t expiresAt);
typedef void (*lease_lookup_by_mac_cb)(const char* ifname, const uint8_t* mac, lease_cb cb);

void add_is_local_hook(is_local_cb cb);
int is_local (const uint8_t* mac, const char* ifname);
void add_update_lease_hook(update_lease_cb cb);
int update_lease(const char* ifname, const uint8_t* mac, const struct in_addr* ip, uint32_t* expiresAt);
void add_updated_lease_hook(updated_lease_cb cb);
void updated_lease(const uint8_t* mac, const struct in_addr* yip, const char* ifname, const uint32_t expiresAt, const enum t_lease_update_src reason);
void add_lease_lookup_by_mac(lease_lookup_by_mac_cb cb);
void lease_lookup_by_mac(const char* ifname, const uint8_t* mac, lease_cb cb);

