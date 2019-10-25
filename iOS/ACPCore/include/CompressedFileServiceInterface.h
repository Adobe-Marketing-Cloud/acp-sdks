/*
Copyright 2018 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

#ifndef ADOBEMOBILE_PLATFORMSHIM_COMPRESSEDFILESERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_COMPRESSEDFILESERVICEINTERFACE_H

#include <string>
#include <vector>
#include "ObjectInterface.h"

namespace AdobeMarketingMobile {
    namespace ErrorCodes {
        // Platform shim errors
        /**
         * A compression support error occurred.
         */
        constexpr static const char* DECOMPRESSION_INIT = "compressed-file.init-failed";
        /**
         * A decompression error occurred.
         */
        constexpr static const char* DECOMPRESSION_ERROR = "compressed-file.decompression-failed";
        /**
         * A filesystem error occurred while decompressing.
         */
        constexpr static const char* DECOMPRESSION_READ = "compressed-file.read-failed";
        /**
         * A filesystem error occurred while decompressing.
         */
        constexpr static const char* DECOMPRESSION_WRITE = "compressed-file.write-failed";
        /**
         * A compression support error occurred.
         */
        constexpr static const char* DECOMPRESSION_CLOSE = "compressed-file.close-failed";
        /**
         * The compressed file is corrupted.
         */
        constexpr static const char* DECOMPRESSION_CORRUPTED = "compressed-file.corrupted";
    }

    enum class CompressedFileType : int32_t {
        ZIP,
        TAR
    };

    class CompressedFileServiceInterface : public virtual ObjectInterface {
    public:

        /**
         * Extract the compressed file found in the {@code compressed_file_path}.
         *
         * <p>
         * The extracted contents will be written to the {@code outputDirectoryPath}. If the file already exists,
         * it will be overwritten. If a platform does not contain support for a particular {@link FileType}, as
         * requested in {@code fileType} argument, then the extract might fail.
         *
         * @param compressed_file_path The path to the compressed file
         * @param file_type The {@link CompressedFileType} of the compressed file
         * @param output_directory_path The output directory where the extracted contents will be stored
         * @return An indication of a successful extraction
         */
        virtual bool Extract(const std::string& compressed_file_path,
                             CompressedFileType file_type,
                             const std::string& output_directory_path) = 0;

    };

}
#endif /* ADOBEMOBILE_PLATFORMSHIM_COMPRESSEDFILESERVICEINTERFACE_H */
