/* **************************************************************************
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

#ifndef ADOBEMOBILE_PLATFORMSHIM_LOCALSTORAGESERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_LOCALSTORAGESERVICEINTERFACE_H

#include <cstdio>
#include <map>
#include <memory>
#include <vector>
#include "ObjectInterface.h"

namespace AdobeMarketingMobile {
    /**
     * Interface for the DataStore object containing persistent key-value pairs
     */
    class DataStoreInterface : public virtual ObjectInterface {
    public:
        /**
         * Set or update an int value
         *
         * @param key std::string key name
         * @param value int value
         */
        virtual void SetInt(const std::string& key, int32_t value) = 0;

        /**
         * Get int value for key
         *
         * @param key std::string key name
         * @param default_value int the default value to return if key does not exist
         * @return persisted value if it exists, default_value otherwise
         */
        virtual int32_t GetInt(const std::string& key, int32_t default_value) const = 0;

        /**
         * Set or update a std::string value for key
         *
         * @param key std::string key name
         * @param value std::string The string value to store
         */
        virtual void SetString(const std::string& key, const std::string& value) = 0;

        /**
         * Get String value for key
         *
         * @param key std::string key name
         * @param default_value std::string the default value to return if key does not exist
         * @return persisted value if it exists, default_value otherwise
         */
        virtual std::string GetString(const std::string& key, const std::string& default_value) const = 0;

        /**
         * Set or update a double value for key
         *
         * @param key std::string key name
         * @param value The double value to store
         */
        virtual void SetDouble(const std::string& key, double value) = 0;

        /**
         * Get double value for key
         *
         * @param key std::string key name
         * @param default_value double the default value to return if key does not exist
         * @return persisted value if it exists, default_value otherwise
         */
        virtual double GetDouble(const std::string& key, double default_value) const = 0;

        /**
         * Set or update a long value for key
         *
         * @param key std::string key name
         * @param value The long value to store
         */
        virtual void SetLong(const std::string& key, int64_t value) = 0;

        /**
         * Get long value for key
         *
         * @param key std::string key name
         * @param default_value long the default value to return if key does not exist
         * @return persisted value if it exists, default_value otherwise
         */
        virtual int64_t GetLong(const std::string& key, int64_t default_value) const = 0;

        /**
         * Set or update a float value for key
         *
         * @param key std::string key name
         * @param value The float value to store
         */
        virtual void SetFloat(const std::string& key, float value) = 0;

        /**
         * Get float value for key
         *
         * @param key std::string key name
         * @param default_value float the default value to return if key does not exist
         * @return persisted value if it exists, default_value otherwise
         */
        virtual float GetFloat(const std::string& key, float default_value) const = 0;

        /**
         * Set or update a boolean value for key
         *
         * @param key std::string key name
         * @param value The bool value to store
         */
        virtual void SetBoolean(const std::string& key, bool value) = 0;

        /**
         * Get boolean value for key
         *
         * @param key std::string key name
         * @param default_value boolean the default value to return if key does not exist
         * @return persisted value if it exists, default_value otherwise
         */
        virtual bool GetBoolean(const std::string& key, bool default_value) const = 0;

        /**
         * Set or update a Vector value for key
         *
         * @param key std::string key name
         * @param value Vector to set or update
         */
        virtual void SetVector(const std::string& key, const std::vector<std::string>& value) = 0;

        /**
         * Get Vector value for key
         *
         * @param key std::string key name
         * @return persisted value if it exists, an empty vector otherwise
         */
        virtual std::vector<std::string> GetVector(const std::string& key) const = 0;

        /**
         * Set or update a Map value for key
         *
         * @param key std::string key name
         * @param value Map to set or update
         */
        virtual void SetMap(const std::string& key, const std::map<std::string, std::string>& value) = 0;

        /**
         * Get Map value for key
         *
         * @param key std::string key name
         * @return persisted value if it exists, an empty map otherwise
         */
        virtual std::map<std::string, std::string> GetMap(const std::string& key) const = 0;

        /**
         * Check if the DataStore contains key
         *
         * @param key std::string key name
         * @return true if key exists, false otherwise
         */
        virtual bool Contains(const std::string& key) const = 0;

        /**
         * Remove persisted value for key
         *
         * @param key std::string key name
         */
        virtual void Remove(const std::string& key) = 0;

        /**
         * Remove all key-value pairs from this DataStore
         */
        virtual void RemoveAll() = 0;
    };

    class LocalStorageServiceInterface : public virtual ObjectInterface {
    public:
        /**
         * Get a DataStore containing persistent key-value pairs
         *
         * @param data_store_name name of the DataStore
         * @return DataStore object containing persisted data for dataStoreName. A new DataStore will be created if it doesn't exist
         */
        virtual std::shared_ptr<DataStoreInterface> GetDataStore(const std::string& data_store_name) = 0;
    };


} //namespace
#endif /* ADOBEMOBILE_PLATFORMSHIM_LOCALSTORAGESERVICEINTERFACE_H */
