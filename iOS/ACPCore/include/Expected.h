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

#ifndef ADOBEMOBILE_UTIL_EXPECTED_H
#define ADOBEMOBILE_UTIL_EXPECTED_H

#include <type_traits>
#include "Object.h"
#include "SdkError.h"

namespace AdobeMarketingMobile {

    /**
     *  Expected<> is a template class that can contain either a Value type or an Error type which defaults to SdkError.
     *  The name is taken from a talk by Andrei Alexandrescu here:
     *  https://channel9.msdn.com/Shows/Going+Deep/C-and-Beyond-2012-Andrei-Alexandrescu-Systematic-Error-Handling-in-C
     *  although the implementation is very different. This can be used to avoid having to throw exceptions or have out
     *  params in many situations. This class also avoids the extra allocation overhead of using std::shared_ptr while
     *  providing for a richer error.
     *
     *  Notes about usage:
     *      * Value type (V) cannot be the same as the Error type (E)
     *      * std::exception (and derived classes) may not work for Error type (E) without further work
     *
     *  EXAMPLE USAGE:
     *
     *  Expected<std::shared_ptr<RemoteFileInterface>> GetFile(const std::string& url);
     *  ...
     *  if (auto result = GetFile(url)) {
     *      auto file = result.Value(); // type is const std::shared_ptr<RemoteFileInterface>&
     *      ...
     *  }
     *  else {
     *      auto error = result.Error(); // type is const SdkError&
     *      ...
     *  }
     *
     */
    template<typename V, typename E = SdkError>
    class Expected {
    public:
        Expected() = default;

        Expected(const V& value) : initialized_(true), has_value_(true) {
            new (&data_) V(value);
        }

        Expected(const E& error) : initialized_(true), has_value_(false) {
            new (&data_) E(error);
        }

        Expected(const Expected<V, E>& exp) : initialized_(exp.initialized_), has_value_(exp.has_value_) {
            if (has_value_) {
                new (&data_) V(exp.ConstValue());
            } else if (initialized_) {
                new (&data_) E(exp.Error());
            }
        }

        Expected<V, E>& operator=(const Expected<V, E>& exp) {
            Expected<V, E> temp(exp);
            initialized_ = std::move(temp.initialized_);
            has_value_ = std::move(temp.has_value_);
            data_ = std::move(temp.data_);
            temp.initialized_ = false; // Ensure temp destruction does NOT call Value or Error destructors
            return *this;
        }

        ~Expected() {
            if (initialized_) {
                if (has_value_) {
                    V* value = reinterpret_cast<V*>(&data_);
                    value->~V();
                } else {
                    E* error = reinterpret_cast<E*>(&data_);
                    error->~E();
                }
            }
        }

        explicit operator bool() const {
            return has_value_;
        }

        bool operator!() const {
            return !has_value_;
        }

        V& Value() {
            if (!initialized_ || !has_value_) {
                ADOBE_THROW(ErrorCodes::STD_BAD_CAST, "Value type not available.");
            }

            return *(reinterpret_cast<V*>(&data_));
        }

        const V& ConstValue() const {
            if (!initialized_ || !has_value_) {
                ADOBE_THROW(ErrorCodes::STD_BAD_CAST, "Value type not available.");
            }

            return *(reinterpret_cast<const V*>(&data_));
        }

        const E& Error() const {
            if (!initialized_ || has_value_) {
                ADOBE_THROW(ErrorCodes::STD_BAD_CAST, "Error type not available.");
            }

            return *(reinterpret_cast<const E*>(&data_));
        }

    private:
        static constexpr const std::size_t DATA_SIZE{ sizeof(V) > sizeof(E) ? sizeof(V) : sizeof(E) };
        static constexpr const std::size_t DATA_ALIGNMENT{ alignof(V) > alignof(E) ? alignof(V) : alignof(E) };
        typename std::aligned_storage<DATA_SIZE, DATA_ALIGNMENT>::type data_;
        bool initialized_ = false;
        bool has_value_ = false;
    };

    /**
     *  Expected<void> is a template class that can contain only an SdkError type. There is no Value.
     *
     *  EXAMPLE USAGE:
     *
     *  Expected<void> GetFile(const std::string& url) {
     *      if(success) { return {}; }
     *      else { return { SdkError("bad news") }; }
     *  }
     *  ...
     *  if (auto result = GetFile(url)) {
     *      ...
     *  }
     *  else {
     *      auto error = result.Error(); // type is const SdkError&
     *      ...
     *  }
     *
     */
    template <>
    class Expected<void, SdkError> {
    public:
        Expected() : initialized_(true), has_value_(true) {
        }

        Expected(const SdkError& error) : initialized_(true), has_value_(false) {
            new (&data_) SdkError(error);
        }

        Expected(const Expected<void, SdkError>& exp) : initialized_(exp.initialized_), has_value_(exp.has_value_) {
            if (initialized_ && !has_value_) {
                new (&data_) SdkError(exp.Error());
            }
        }

        Expected<void, SdkError>& operator=(const Expected<void, SdkError>& exp) {
            Expected<void, SdkError> temp(exp);
            initialized_ = std::move(temp.initialized_);
            has_value_ = std::move(temp.has_value_);
            data_ = std::move(temp.data_);
            temp.initialized_ = false; // Ensure temp destruction does NOT call Value or Error destructors
            return *this;
        }

        ~Expected() {
            if (initialized_) {
                if (!has_value_) {
                    SdkError* error = reinterpret_cast<SdkError*>(&data_);
                    error->~SdkError();
                }
            }
        }

        explicit operator bool() const {
            return has_value_;
        }

        bool operator!() const {
            return !has_value_;
        }

        const SdkError& Error() const {
            if (!initialized_ || has_value_) {
                ADOBE_THROW(ErrorCodes::STD_BAD_CAST, "Error type not available.");
            }

            return *(reinterpret_cast<const SdkError*>(&data_));
        }

    private:
        static constexpr const std::size_t DATA_SIZE{ sizeof(SdkError) };
        static constexpr const std::size_t DATA_ALIGNMENT{ alignof(SdkError) };
        typename std::aligned_storage<DATA_SIZE, DATA_ALIGNMENT>::type data_;
        bool initialized_ = false;
        bool has_value_ = false;
    };

} /* end of namespace AdobeMarketingMobile */

#endif /*ADOBEMOBILE_UTIL_EXPECTED_H*/
