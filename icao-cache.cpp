#
/*
 *    Copyright (C) 2010, 2011, 2012
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Programming
 *
 *    This file is part of the qt-1090 program
 *
 *    qt-1090 is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    qt-1090 is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with qt-1090; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	This software is derived from the dump1090.c file
 *	Copyright (C) 2012 by Salvatore Sanfilippo <antirez@gmail.com>
 *
 */
#include	"icao-cache.h"
#include	<stdio.h>
#include	<string.h>

	icaoCache::icaoCache (void) {
}

	icaoCache::~icaoCache (void) {
}


/*	Hash the ICAO address to index our cache of ICAO_CACHE_LEN
 *	elements, that is assumed to be a power of two.
 */
uint32_t	icaoCache::ICAOCacheHashAddress (uint32_t a) {
//      The following three rounds wil make sure that every bit affects
//      every output bit with ~ 50% of probability. */
        a = ((a >> 16) ^ a) * 0x45d9f3b;
        a = ((a >> 16) ^ a) * 0x45d9f3b;
        a = ((a >> 16) ^ a);
        return a & (ICAO_CACHE_LEN - 1);
}

/*
 *	Add the specified entry to the cache of recently
 *	seen ICAO addresses. Note that we also add a timestamp
 *	so that we can make sure that the entry is only valid
 *	for ICAO_CACHE_TTL seconds.
 */
void	icaoCache::addRecentlySeenICAOAddr (uint32_t addr) {
uint32_t h = ICAOCacheHashAddress (addr);
	icao_cache [h]. addr = addr;
	icao_cache [h]. time = (uint32_t) time(NULL);
}

/*
 *	Returns true if the specified ICAO address was seen in a
 *	DF format with proper checksum (not xored with address)
 *	no more than * ICAO_CACHE_TTL seconds ago.
 *	Otherwise returns false.
 */

bool	icaoCache::ICAOAddressWasRecentlySeen (uint32_t addr) {
uint32_t h = ICAOCacheHashAddress (addr);
uint32_t a = icao_cache  [h]. addr;
uint32_t t = icao_cache  [h]. time;

	return a && a == addr && time (NULL) - t <= ICAO_CACHE_TTL;
}


