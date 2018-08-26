#ifndef _LIBSECURITY_HMACPROVIDER_H_
#define _LIBSECURITY_HMACPROVIDER_H_

#include "cryptoalgorithms.h"
#include <vector>
#include <openssl/hmac.h>

namespace filesafe
{
    class HmacProvider
    {
    public:
        HmacProvider(
            const HmacAlgorithm& alg
        );

        void Init(
            const std::vector<uint8_t>& key
        );

        void Update(
            const std::vector<uint8_t>& buf
        );

        std::vector<uint8_t> Final();

        static bool Verify(
            const std::vector<uint8_t>& payloadBuf,
            const std::vector<uint8_t>& expectedBuf
        );

        ~HmacProvider();

    private:
        HmacAlgorithm m_macAlg;
        HMAC_CTX m_ctx;
        
    };
}

#endif  //  _LIBSECURITY_HMACPROVIDER_H_