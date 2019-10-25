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
#ifndef ADOBEMOBILE_PLATFORMSHIM_DEFAULTTHREADINGSERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_DEFAULTTHREADINGSERVICEINTERFACE_H

#include "ThreadingServiceInterface.h"

namespace AdobeMarketingMobile {
    /**
     * A default implementation of ThreadingServiceInterface.
     *
     * Implemented using TaskExecutorInterface::Create.
     *
     * CreateSequentialTaskExecutor returns a TaskExecutorInterface with exactly 1 thread.
     * CreateParallelTaskExecutor returns returns a dynamic TaskExecutorInterface with at least 1 thread, but no thread maximum.
     */
    class DefaultThreadingServiceInterface : public virtual ThreadingServiceInterface {
    public:
        /**
         * @return a new DefaultThreadingServiceInterface
         */
        static std::shared_ptr<DefaultThreadingServiceInterface> Create();
    };
}

#endif /* ADOBEMOBILE_PLATFORMSHIM_DEFAULTTHREADINGSERVICEINTERFACE_H */
