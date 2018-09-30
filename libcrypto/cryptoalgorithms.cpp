#include "cryptoalgorithms.h"
#include <openssl/evp.h>

namespace filesafe
{
    // HmacAlgorithm implementation
    HmacAlgorithm::HmacAlgorithm(
        HmacAlgorithmType algType
    )
    {
        switch (algType)
        {
            case HmacAlgorithmType::HMAC_SHA_256:
            {
                m_hash = EVP_sha256();
                m_keySizeBits = 256;
                m_digestSizeBits = 256;
                break;
            }
            default:
            {
                //  default is HMAC_SHA_512
                m_hash = EVP_sha512();
                m_keySizeBits = 512;
                m_digestSizeBits = 512;
                break;
            }
        }
    }

    const EVP_MD* HmacAlgorithm::GetHashCtx() const
    {
        return m_hash;
    }

    uint32_t HmacAlgorithm::GetKeySizeBits() const
    {
        return m_keySizeBits;
    }

    uint32_t HmacAlgorithm::GetKeySizeBytes() const
    {
        return m_keySizeBits >> 3;
    }

    uint32_t HmacAlgorithm::GetDigestSizeBits() const
    {
        return m_digestSizeBits;
    }

    uint32_t HmacAlgorithm::GetDigestSizeBytes() const
    {
        return m_digestSizeBits >> 3;
    }
}