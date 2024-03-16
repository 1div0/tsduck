//----------------------------------------------------------------------------
//
// TSDuck - The MPEG Transport Stream Toolkit
// Copyright (c) 2005-2024, Thierry Lelegard
// BSD-2-Clause license, see LICENSE.txt file or https://tsduck.io/license
//
//----------------------------------------------------------------------------
//!
//!  @file
//!  AES-128 block cipher
//!
//----------------------------------------------------------------------------

#pragma once
#include "tsBlockCipher.h"
#include "tsECB.h"
#include "tsCBC.h"

namespace ts {
    //!
    //! AES-128 block cipher
    //! @ingroup crypto
    //!
    class TSDUCKDLL AES128: public BlockCipher
    {
        TS_NOCOPY(AES128);
    public:
        AES128();                                 //!< Constructor.
        static constexpr size_t BLOCK_SIZE = 16;  //!< AES-128 block size in bytes.
        static constexpr size_t KEY_SIZE = 16;    //!< AES-128 key size in bytes.

    protected:
        TS_BLOCK_CIPHER_DECLARE_PROPERTIES(AES128);

        //! Constructor for subclasses which add some properties, such as chaining mode.
        //! @param [in] props Constant reference to a block of properties of this block cipher.
        AES128(const BlockCipherProperties& props);

#if defined(TS_WINDOWS)
        virtual void getAlgorithm(::BCRYPT_ALG_HANDLE& algo, size_t& length) const override;
#else
        virtual const EVP_CIPHER* getAlgorithm() const override;
#endif
    };

    //
    // Chaining blocks specializations, when implemented in the system cryptographic library.
    //
    //! @cond nodoxygen
#if !defined(TS_WINDOWS)

    template<>
    class ECB<AES128>: public AES128
    {
        TS_NOCOPY(ECB);
    public:
        ECB();
    protected:
        TS_BLOCK_CIPHER_DECLARE_PROPERTIES(ECB);
        ECB(const BlockCipherProperties& props);
        virtual const EVP_CIPHER* getAlgorithm() const override;
    };
#endif

    // Specialization for AES-128-CBC is currently disabled, see:
    // https://stackoverflow.com/questions/78172656/openssl-how-to-encrypt-new-message-with-same-key-without-evp-encryptinit-ex-a
#if 0
    template<>
    class CBC<AES128>: public AES128
    {
        TS_NOCOPY(CBC);
    public:
        CBC();
    protected:
        TS_BLOCK_CIPHER_DECLARE_PROPERTIES(CBC);
        CBC(const BlockCipherProperties& props);
        virtual const EVP_CIPHER* getAlgorithm() const override;
    };

#endif
    //! @endcond
}
