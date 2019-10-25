/*
Copyright 2017 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

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
