/*
 * $Id$
 *
 *
 * SQUID Web Proxy Cache          http://www.squid-cache.org/
 * ----------------------------------------------------------
 *
 *  Squid is the result of efforts by numerous individuals from
 *  the Internet community; see the CONTRIBUTORS file for full
 *  details.   Many organizations have provided support for Squid's
 *  development; see the SPONSORS file for full details.  Squid is
 *  Copyrighted (C) 2001 by the Regents of the University of
 *  California; see the COPYRIGHT file for full details.  Squid
 *  incorporates software developed and/or copyrighted by other
 *  sources; see the CREDITS file for full details.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 */
#ifndef SQUID_TYPELENGTHVALUE_H
#define SQUID_TYPELENGTHVALUE_H

class StoreEntry;

// WTF?
typedef class StoreMeta tlv;

/* for size_t, SQUIDCEXTERN */
#include "config.h"

/**
 \ingroup SwapStoreAPI
 \todo AYJ: for critical lists like this we should use A=64,B=65 etc to enforce and reserve values.
 \note NOTE!  We must preserve the order of this list!
 *
 \section StoreSwapMeta Store "swap meta" Description
 \par
 * "swap meta" refers to a section of meta data stored at the beginning
 * of an object that is stored on disk.  This meta data includes information
 * such as the object's cache key (MD5), URL, and part of the StoreEntry
 * structure.
 *
 \par
 * The meta data is stored using a TYPE-LENGTH-VALUE format.  That is,
 * each chunk of meta information consists of a TYPE identifier, a
 * LENGTH field, and then the VALUE (which is LENGTH octets long).
 */
enum {
    /**
     * Just a placeholder for the zeroth value. It is never used on disk.
     */
    STORE_META_VOID,

    /**
     \deprecated
     * This represents the case when we use the URL as the cache
     * key, as Squid-1.1 does.  Currently we don't support using
     * a URL as a cache key, so this is not used.
     */
    STORE_META_KEY_URL,

    /**
     \deprecated
     * For a brief time we considered supporting SHA (secure
     * hash algorithm) as a cache key.  Nobody liked it, and
     * this type is not currently used.
     */
    STORE_META_KEY_SHA,

    /**
     * This represents the MD5 cache key that Squid currently uses.
     * When Squid opens a disk file for reading, it can check that
     * this MD5 matches the MD5 of the user's request.  If not, then
     * something went wrong and this is probably the wrong object.
     */
    STORE_META_KEY_MD5,

    /**
     * The object's URL.  This also may be matched against a user's
     *  request for cache hits to make sure we got the right object.
     */
    STORE_META_URL,

    /**
     * This is the "standard metadata" for an object.
     * Really its just this middle chunk of the StoreEntry structure:
     \code
        time_t timestamp;
        time_t lastref;
        time_t expires;
        time_t lastmod;
        uint64_t swap_file_sz;
        uint16_t refcount;
        uint16_t flags;
     \endcode
     */
    STORE_META_STD,

    /**
     * Reserved for future hit-metering (RFC 2227) stuff
     */
    STORE_META_HITMETERING,

    /// \todo DOCS: document.
    STORE_META_VALID,

    /**
     * Stores Vary request headers
     */
    STORE_META_VARY_HEADERS,

    /**
     * Updated version of STORE_META_STD, with support for  >2GB objects.
     * As STORE_META_STD except that the swap_file_sz is a 64-bit integer instead of 32-bit.
     */
    STORE_META_STD_LFS,

    /**
     \deprecated
     * Object size, not implemented, squid26 compatibility
     */
    STORE_META_OBJSIZE,

    STORE_META_STOREURL,	/* the store url, if different to the normal URL */
    STORE_META_VARY_ID,		/* Unique ID linking variants */
    STORE_META_END
};

/// \ingroup SwapStoreAPI
class StoreMeta
{
public:
    static bool validType(char);
    static int const MaximumTLVLength;
    static int const MinimumTLVLength;
    static StoreMeta *Factory(char type, size_t len, void const *value);
    static StoreMeta **Add(StoreMeta **tail, StoreMeta *aNode);
    static void FreeList(StoreMeta **head);

    virtual char getType() const = 0;
    virtual bool validLength(int) const;
    virtual bool checkConsistency(StoreEntry *) const;
    virtual ~StoreMeta() {}

    int length;
    void *value;
    tlv *next;
};

/// \ingroup SwapStoreAPI
SQUIDCEXTERN char *storeSwapMetaPack(tlv * tlv_list, int *length);
/// \ingroup SwapStoreAPI
SQUIDCEXTERN tlv *storeSwapMetaBuild(StoreEntry * e);
/// \ingroup SwapStoreAPI
SQUIDCEXTERN void storeSwapTLVFree(tlv * n);

#endif /* SQUID_TYPELENGTHVALUE_H */
