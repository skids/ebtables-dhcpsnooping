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
 *  (C) 2017, Brian S. Julin <bri@abrij.org>
 */

#include "config.h"
#ifdef __USE_NFTABLES__
#include "debug.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include "ether_ntoa.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef NFSETPREFIX
#define NFSETPREFIX "dhcpsnoop-leases-"
#endif
#ifndef NFTABLE
#define NFTABLE "dhcpsnoop"
#endif
#ifndef NFTABLES
#define NFTABLES "nft"
#endif

void nftables_run(const char* cmd) {
	eprintf(DEBUG_GENERAL, "run \"%s\"", cmd);
	if (system(cmd)) {
		eprintf(DEBUG_ERROR, "cmd \"%s\" failed", cmd);
	} else {
		eprintf(DEBUG_GENERAL, "cmd \"%s\" ok", cmd);
	}
}

void nftables_add(const struct in_addr* yip, const uint8_t* mac, const char* ifname) {
	char cmd[65535];

	assert(yip); assert(mac); assert(ifname);
	eprintf(DEBUG_VERBOSE, "add nftables element: MAC: %s IP: %s VLAN: %s", ether_ntoa_z((struct ether_addr *)mac), inet_ntoa(*yip), ifname);

	snprintf(cmd, sizeof(cmd), NFTABLES " add element bridge " NFTABLE " " NFSETPREFIX "%s { %s . %s }",
	         ifname, ether_ntoa_z((struct ether_addr *)mac), inet_ntoa(*yip));
	nftables_run(cmd);
}

void nftables_del(const struct in_addr* yip, const uint8_t* mac, const char* ifname) {
	char cmd[65535];

	assert(yip); assert(mac); assert(ifname);
	eprintf(DEBUG_VERBOSE, "delete nftables element: MAC: %s IP: %s VLAN: %s", ether_ntoa_z((struct ether_addr *)mac), inet_ntoa(*yip), ifname);

	snprintf(cmd, sizeof(cmd), NFTABLES " delete element bridge " NFTABLE " " NFSETPREFIX "%s { %s . %s }",
	         ifname, ether_ntoa_z((struct ether_addr *)mac), inet_ntoa(*yip));
	nftables_run(cmd);
}
#endif
