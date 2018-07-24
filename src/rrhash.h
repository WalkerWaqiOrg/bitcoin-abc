// Copyright (c) 2018-2018 Walker Waqi
// Copyright (c) 2018-2018 The RRC developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_RRHASH_H
#define BITCOIN_RRHASH_H

#include "hash.h"
#include <dlfcn.h>

#define RRHASH_LIB_PATH         "./librrhash.so"
#define RRHASH_LIB_PATH_WIN     "./librrhash.dll"
#define RRHASH_LIB_FUNC         "run_all"

typedef void (*RUN_RRHASH_FUNC)(const char *data, size_t length, unsigned char *hash);

class CRRHash {
private:
    void*               rrhash_handle_;
    RUN_RRHASH_FUNC     rrhash_func;

public:
    CRRHash()
    {
#ifdef WIN32
	    rrhash_handle_ = dlopen(RRHASH_LIB_PATH_WIN, RTLD_LAZY);
#else
	    rrhash_handle_ = dlopen(RRHASH_LIB_PATH, RTLD_LAZY);
#endif
        if (!rrhash_handle_) {
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }

        rrhash_func = (RUN_RRHASH_FUNC)dlsym(rrhash_handle_, RRHASH_LIB_FUNC);
        if (dlerror() != NULL)  {
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }
    }

    ~CRRHash()
    {
        if (rrhash_handle_) {
            dlclose(rrhash_handle_);
        }
    }

    void Hash(const char *data, size_t length, unsigned char *hash)
    {
        rrhash_func(data, length, hash);
    }
};

/** A writer stream (for serialization) that computes a 256-bit hash. */
class CRRHashWriter {
private:
    CHash256 ctx;

    const int nType;
    const int nVersion;

    CRRHash hash_;
    std::string buffer;

public:
    CRRHashWriter(int nTypeIn, int nVersionIn)
        : nType(nTypeIn), nVersion(nVersionIn) {}

    int GetType() const { return nType; }
    int GetVersion() const { return nVersion; }

    void write(const char *pch, size_t size) {
        // ctx.Write((const uint8_t *)pch, size);
        buffer.append(pch,size);
    }

    // invalidates the object
    uint256 GetHash() {
        uint256 result;
        // ctx.Finalize((uint8_t *)&result);
	    hash_.Hash(buffer.data(), buffer.length(), (unsigned char*)&result);
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
