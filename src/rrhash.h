// Copyright (c) 2018-2018 Walker Waqi
// Copyright (c) 2018-2018 The RRC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_RRHASH_H
#define BITCOIN_RRHASH_H

#include "hash.h"
#include "cryptonote_lib/hash.h"
#include <string>

/** A writer stream (for serialization) that computes a 256-bit hash. */
class CRRHashWriter {
private:
    std::string buffer;

    const int nType;
    const int nVersion;

public:
    CRRHashWriter(int nTypeIn, int nVersionIn)
        : nType(nTypeIn), nVersion(nVersionIn) {}

    int GetType() const { return nType; }
    int GetVersion() const { return nVersion; }

    void write(const char *pch, size_t size) {
        buffer.append(pch,size);
    }

    // invalidates the object
    uint256 GetHash() {
        uint256 result;
	    crypto::cn_slow_hash((const void *)buffer.data(), buffer.length(), *(crypto::hash*)&result);
        return result;
    }

    template <typename T> CRRHashWriter &operator<<(const T &obj) {
        // Serialize to this stream
        ::Serialize(*this, obj);
        return (*this);
    }
};

/**
 * Reads data from an underlying stream, while hashing the read data.
 */
template <typename Source> class CRRHashVerifier : public CRRHashWriter {
private:
    Source *source;

public:
    CRRHashVerifier(Source *source_)
        : CRRHashWriter(source_->GetType(), source_->GetVersion()),
          source(source_) {}

    void read(char *pch, size_t nSize) {
        source->read(pch, nSize);
        this->write(pch, nSize);
    }

    void ignore(size_t nSize) {
        char data[1024];
        while (nSize > 0) {
            size_t now = std::min<size_t>(nSize, 1024);
            read(data, now);
            nSize -= now;
        }
    }

    template <typename T> CRRHashVerifier<Source> &operator>>(T &obj) {
        // Unserialize from this stream
        ::Unserialize(*this, obj);
        return (*this);
    }
};

/** Compute the 256-bit hash of an object's serialization. */
template <typename T>
uint256 SerializeRRHash(const T &obj, int nType = SER_GETHASH,
                      int nVersion = PROTOCOL_VERSION) {
    CRRHashWriter ss(nType, nVersion);
    ss << obj;
    return ss.GetHash();
}

#endif // BITCOIN_RRHASH_H
