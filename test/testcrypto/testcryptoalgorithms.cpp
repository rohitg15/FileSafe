#include "testcryptoalgorithms.h"

HmacAlgorithmTest::HmacAlgorithmTest() {};

HmacAlgorithmTest::~HmacAlgorithmTest() {};

void HmacAlgorithmTest::SetUp() {};

void HmacAlgorithmTest::TearDown() {};

TEST_F(HmacAlgorithmTest, TestHmacSha256)
{
    filesafe::HmacAlgorithm alg(filesafe::HmacAlgorithmType::HMAC_SHA_256);

    ASSERT_TRUE( 256 == alg.GetKeySizeBits() );
    ASSERT_TRUE( 32 == alg.GetKeySizeBytes() );
    ASSERT_TRUE( 256 == alg.GetDigestSizeBits() );
    ASSERT_TRUE( 32 == alg.GetDigestSizeBytes() );
    ASSERT_TRUE( NULL != alg.GetHashCtx() );
}

TEST_F(HmacAlgorithmTest, TestHmacSha512)
{
    filesafe::HmacAlgorithm alg(filesafe::HmacAlgorithmType::HMAC_SHA_512);

    ASSERT_TRUE( 512 == alg.GetKeySizeBits() );
    ASSERT_TRUE( 64 == alg.GetKeySizeBytes() );
    ASSERT_TRUE( 512 == alg.GetDigestSizeBits() );
    ASSERT_TRUE( 64 == alg.GetDigestSizeBytes() );
    ASSERT_TRUE( NULL != alg.GetHashCtx() );
}