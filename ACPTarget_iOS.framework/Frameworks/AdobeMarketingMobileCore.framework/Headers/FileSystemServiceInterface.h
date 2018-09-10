/* ************************************************************************
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

#ifndef ADOBEMOBILE_PLATFORMSHIM_FILESYSTEMSERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_FILESYSTEMSERVICEINTERFACE_H

#include <string>
#include <vector>
#include <chrono>
#include "ObjectInterface.h"

namespace AdobeMarketingMobile {
    namespace ErrorCodes {
        // Platform shim errors
        /**
         * A filesystem error occurred.
         */
        constexpr static const char* FILESYSTEM_ERROR = "filesystem";
    }

    class FileHandlerInterface : public virtual ObjectInterface {
    public:
        /**
         * Return the size of the file pointed to, if it exists.
         * This is a synchronous call.
         *
         * @return size of file if exists, -1 otherwise.
         */
        virtual int64_t Size() = 0;

        /**
         * Return the last-modified date of the file pointed to, if it exists.
         * This is a synchronous call.
         *
         * @return `time_point` representing last-modified date of file if exists, otherwise `time_point` containing 0.
         */
        virtual std::chrono::time_point<std::chrono::system_clock> LastModified() = 0;

        /**
         * Open the file referenced for reading only.
         * This is a synchronous call.
         *
         * @return true if file was opened, false otherwise
         */
        virtual bool OpenForReading() = 0;

        /**
         * Open the file reference for writing. Creates if needed, and truncates existing file at this path.
         * This is a synchronous call.
         *
         * @return true if file was opened, false otherwise
         */
        virtual bool OpenForWriting() = 0;

        /**
         * Move the read/write head for file to the offset. The offset passed must be less than reported Size().
         * This is a synchronous call.
         *
         * @param file_offset the offset from the beginning of the file
         * @return true if file read/write head was moved, false if an error occurred
         */
        virtual bool MoveToOffset(uint64_t file_offset) = 0;

        /**
         * Write some data to the file. The file must have been opened for writing first, or no bytes will be read.
         * This is a synchronous call.
         *
         * @param bytes_to_write the number of bytes to write to the file
         * @param write_buffer the buffer to write to the file
         * @return the number of bytes written to the file
         */
        virtual uint32_t Write(uint32_t bytes_to_write, uint8_t* write_buffer) = 0;

        /**
         * Read some data from the file. The file must have been opened for reading first, or no bytes will be read.
         * This is a synchronous call.
         *
         * @param bytes_to_read the number of bytes to read from the file
         * @param read_buffer the buffer to read into
         * @return the number of bytes read from the file
         */
        virtual uint32_t Read(uint32_t bytes_to_read, uint8_t* read_buffer) = 0;

        /**
         * Close the file. After this call, no more reading or writing is allowed unless the file is opened again.
         * This is a synchronous call.
         *
         * @return true if file was closed, false if an error occurred
         */
        virtual bool Close() = 0;
    };

    class FileSystemServiceInterface : public virtual ObjectInterface {
    public:
        /**
         * Make a new file handler at the given path. The path passed does not need to point to an existing file,
         * but creation will *fail* if path points to an existing directory.
         *
         * @param path the full path to the file, either absolute or relative
         * @return ptr to new FileHandlerInterface if created successfully, nullptr otherwise
         */
        virtual std::shared_ptr<FileHandlerInterface> CreateFileHandler(const std::string& path) = 0;

        /**
         * Make a new directory at the given path. Creates a single directory.
         * It is not assumed creating nonexistent parent directories is supported.
         *
         * @param path the directory pathname, either absolute or relative
         * @return true if the directory was created successfully, false otherwise
         * @throws FILESYSTEM_ERROR if an error is caught by the platform layer
         */
        virtual bool MakeDirectory(const std::string& path) = 0;

        /**
         * Delete the directory denoted by the given path. The directory must be empty in order
         * to be deleted.
         *
         * @param path the directory pathname, either absolute or relative
         * @return bool indicating the directory deletion was successful
         * @throws FILESYSTEM_ERROR if an error is caught by the platform layer
         */
        virtual bool DeleteDirectory(const std::string& path) = 0;

        /**
         * Delete the file denoted by the given path.
         *
         * @param path the file pathname, either absolute or relative
         * @return bool indicating the file deletion was successful
         * @throws FILESYSTEM_ERROR if an error is caught by the platform layer
         */
        virtual bool DeleteFile(const std::string& path) = 0;

        /**
         * Determines if the given pathname denotes a directory.
         *
         * @param path a filesystem pathname, either absolute or relative
         * @return true if the pathname is a directory, false otherwise
         * @throws FILESYSTEM_ERROR if an error is caught by the platform layer.
         */
        virtual bool IsDirectory(const std::string& path) const = 0;

        /**
         * Determines if the given directory path exists on the filesystem.
         *
         * @param path the directory pathname, either absolute or relative
         * @return true if the directory exists on the filesystem, false otherwise
         * @throws FILESYSTEM_ERROR if an error is caught by the platform layer.
         */
        virtual bool DirectoryExists(const std::string& path) const = 0;

        /**
         * Determines if the given directory path is writable by the application.
         *
         * @param path the directory pathname, either absolute or relative
         * @return true if the directory is writable by the application, false otherwise
         * @throws FILESYSTEM_ERROR if an error is caught by the platform layer
         */
        virtual bool DirectoryIsWritable(const std::string& path) const = 0;

        /**
         * Get all file and directory abstract pathnames contained within the given directory path.
         *
         * @param path the directory pathname, either absolute or relative
         * @return list of all file and directory abstract pathnames contained within the given directory
         * @throws FILESYSTEM_ERROR if an error is caught by the platform layer.
         */
        virtual std::vector<std::string> GetDirectoryContents(const std::string& path) const = 0;

        /**
         * Get all file abstract pathnames contained within the given directory path.
         *
         * @param path the directory pathname, either absolute or relative
         * @return list of all file abstract pathnames contained within the given directory
         * @throws FILESYSTEM_ERROR if an error is caught by the platform layer.
         */
        virtual std::vector<std::string> GetDirectoryFiles(const std::string& path) const = 0;

        /**
         * Read the contents of the given file and return as a string.
         * The filepath may be relative or absolute, or this platform's specific file URI scheme.
         *
         * @param filepath the file pathname
         * @return contents of the file pointed to by filepath as a string
         * @throws FILESYSTEM_ERROR if an error is caught by the platform layer.
         */
        virtual std::string ReadStringFromFile(const std::string& filepath) const = 0;

        /**
         * Get the filesystem specific path separator character.
         *
         * @return path separator character
         */
        virtual char GetPathSeparatorChar() const = 0;

        /**
         * Get the filesystem specific path separator as a string.
         *
         * @return path separator character as a string
         */
        virtual std::string GetPathSeparator() const = 0;
    };

}
#endif /* ADOBEMOBILE_PLATFORMSHIM_FILESYSTEMSERVICEINTERFACE_H */
