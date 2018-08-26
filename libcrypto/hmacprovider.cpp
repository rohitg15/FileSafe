#include "hmacprovider.h"

namespace filesafe
{
    HmacProvider::HmacProvider(
        const HmacAlgorithm& alg
    ) : 
        m_macAlg(alg)
    {}

    void HmacProvider::Init(
        const std::vector<uint8_t>& key    
    )
    {
        HMAC_CTX_init(&m_ctx);
        if ( !HMAC_Init_ex(&m_ctx, key.data(), key.size(), m_macAlg.GetHashCtx(), NULL) )
        {
            throw std::runtime_error("HMAC initialization failed!");
        }
    }

    void HmacProvider::Update(
        const std::vector<uint8_t>& buf
    )
    {
        if (buf.size() > 0)
        {
            if ( !HMAC_Update(&m_ctx, buf.data(), buf.size()) )
            {
                throw std::runtime_error("HMAC update failed!");
            }
        }
    }

    std::vector<uint8_t> HmacProvider::Final()
    {
        uint32_t retDigestSizeBytes = 0;
        std::vector<uint8_t> digest;
        digest.resize(m_macAlg.GetDigestSizeBytes());

        if ( !HMAC_Final(&m_ctx, digest.data(), &retDigestSizeBytes) )
        {
            throw std::runtime_error("HMAC final failed!");
        }
        return digest;  //  check for RVO
    }

    bool HmacProvider::Verify(
        const std::vector<uint8_t>& payloadBuf,
        const std::vector<uint8_t>& expectedBuf
    )
    {
        if (payloadBuf.size() != expectedBuf.size())
        {
            return false;
        }

        uint32_t res = 0;
        for (int i = 0; i < expectedBuf.size(); ++i)
        {
            res |= (static_cast<uint32_t>(expectedBuf[i]) - static_cast<uint32_t>(payloadBuf[i]));
        }
        return (res == 0);
    }

    HmacProvider::~HmacProvider()
    {
        HMAC_CTX_cleanup(&m_ctx);
    }
}