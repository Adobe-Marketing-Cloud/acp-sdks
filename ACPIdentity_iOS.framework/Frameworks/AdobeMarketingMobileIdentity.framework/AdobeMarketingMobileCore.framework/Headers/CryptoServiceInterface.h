/***************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2017 Adobe Systems Incorporated
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Adobe Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Adobe Systems Incorporated and its
 * suppliers and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 **************************************************************************/

#ifndef ADOBEMOBILE_PLATFORMSHIM_CRYPTOSERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_CRYPTOSERVICEINTERFACE_H

#include <string>
#include "ObjectInterface.h"

namespace AdobeMarketingMobile {
    class UuidInterface : public virtual ObjectInterface {
    public:
        /**
         * Get ASCII string representation of a random 128-bit UUID (Universally Unique Identifier)
         * The generated UUID must conform to RFC 4122 version 4 ( https://tools.ietf.org/html/rfc4122 )
         * Random UUID ASCII string example: "5DCD537D-A351-408E-92D7-EBCBC69FEF44"
         */
        virtual std::string GetString() const = 0;

        /**
         * Get UUID bytes
         *
         * @param uuid_bytes 16 byte buffer
         */
        virtual void GetBytes(unsigned char* uuid_bytes) const = 0;
    };

    class CryptoServiceInterface : public virtual ObjectInterface {
    public:
        /**
         * Generate a random 128-bit UUID (Universally Unique Identifier)
         * The generated UUID must conform to RFC 4122 version 4 ( https://tools.ietf.org/html/rfc4122 )
         * Random UUID ASCII string example: "5DCD537D-A351-408E-92D7-EBCBC69FEF44"
         *
         * @return UuidInterface shared_ptr
         */
        virtual std::shared_ptr<UuidInterface> GetRandomUuid() const = 0;

        /**
         * Get SHA-256 hash value for string ( https://tools.ietf.org/html/rfc4634 )
         * SHA-256 hash example:
         * input: "5DCD537D-A351-408E-92D7-EBCBC69FEF44"
         * output: "521FF623340269FD77EBC5BD19E459DCD6A3BFD89A8FBCD10E0B11672914E36B"
         *
         * @return string representation of sha-256 hash value
         */
        virtual std::string GetSha256Hash(const std::string& str) const = 0;
    };
}

#endif /* ADOBEMOBILE_PLATFORMSHIM_CRYPTOSERVICEINTERFACE_H */
