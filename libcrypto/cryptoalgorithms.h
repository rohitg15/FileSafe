#ifndef _LIBCRYPTO_ALGORITHMS_H_
#define _LIBCRYPTO_ALGORITHMS_H_

#include <openssl/evp.h>

namespace filesafe
{
    enum class HmacAlgorithmType
    {
        HMAC_SHA_512,
        HMAC_SHA_256
    };

    enum class EncryptionAlgorithmType
    {
        AES_CTR_256,
        AES_CBC_256
    };

    class HmacAlgorithm
    {
    public:
        HmacAlgorithm(
            HmacAlgorithmType algType
        );

        uint32_t GetKeySizeBits() const;

        uint32_t GetKeySizeBytes() const;

        uint32_t GetDigestSizeBits() const;

        uint32_t GetDigestSizeBytes() const;

        const EVP_MD* GetHashCtx() const;

    private:
        uint32_t m_keySizeBits;
        uint32_t m_digestSizeBits;
        const EVP_MD* m_hash;
    };
}

#endif  //  _LIBCRYPTO_ALGORITHMS_H_
