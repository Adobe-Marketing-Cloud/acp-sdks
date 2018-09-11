/* ************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2018 Adobe Systems Incorporated
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
