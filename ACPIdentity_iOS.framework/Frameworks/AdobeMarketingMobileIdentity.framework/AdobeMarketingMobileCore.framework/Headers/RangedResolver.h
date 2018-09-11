/* **************************************************************************
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

#ifndef ADOBEMOBILE_CORE_RANGEDRESOLVER_H
#define ADOBEMOBILE_CORE_RANGEDRESOLVER_H

#import <map>
#import <memory>
#import "Log.h"
#import "Object.h"

namespace AdobeMarketingMobile {

    /**
     * @note This class is not thread-safe. It is strongly recommended to implement a locking scheme when calling any of these class methods.
     *
     * States will always be one of the following:
     *
     * - A `DATA` state is a normal, valid shared state.
     * - The `PENDING` state is a state that is "on the way" and will eventually be resolved.
     * - The `INVALID` state is a special state that indicates that the state is not valid.
     * - The `NEXT` state is a special "marker" state that indicates that this state is equal to the next DATA/PENDING/INVALID state.
     * - The `PREV` state is a special "marker" state that indicates that this state is equal to the previous state.
     *
     * Modules will be able to perform the following operations:
     *
     * - Create can insert a `DATA`, `PENDING`, or `INVALID` state.
     * - Update can change a PENDING state to a...
     *  + DATA state upon successful asynchronous operations.
     *  + INVALID state for asynchronous operations that invalidate the shared state.
     *  + NEXT state for asynchronous operations that should return the next state.
     *  + PREV state for asynchronous operations that should revert to the previous state.
     * - Get for a version v should...
     *  + If the state at version *v* is DATA, PENDING, or INVALID, return it.
     *  + If the state at version *v* is NEXT, return the first state after *v* that is either DATA, PENDING, or INVALID.
     *   + If there are no such states after *v*, return PENDING.
     *  + If the state at version *v* is PREV, return Get(*v_prev*) where *v_prev* is the version of the first state with version < *v* that is either DATA, PENDING, INVALID, or NEXT.
     *   + If there are no such states before *v*, return PENDING.
     *  + If no state has exactly version *v*, return Get(*v_prev*) where *v_prev* is the version of the first state with version < *v*.
     *   + If there are no such states before *v*, return PENDING.
     *
     * Notice that:
     * - Get(*v*) will always return DATA, PENDING, or INVALID.
     * - Only PENDING states can be updated.
     * - Once a state is DATA or INVALID, Gets for that state will always return the same value. This prevents history from changing.
     *
     * Under this solution, asynchronous operations would typically follow this process:
     * - Create(version, PENDING)
     * - Initiate the operation
     * - When the operation completes,
     *  + If the operation succeeds, Update(version, <the new shared state>)
     *  + Else (the operation failed):
     *   + If state should use the previous valid shared state, Update(version, PREV)
     *   + If state should use the next valid shared state, Update(version, NEXT)
     *   + If state should be invalid, Update(version, INVALID)
     */
    template<class T>
    class RangedResolver : public Object {

    public:

        /**
         * @brief Creates a new Ranged Resolver instance.
         *
         * Creates a new RangedResolver instance using the given special marker objects. The special state markers
         * must be unique with each other and should be unique within your system.
         *
         * @param pending_state a unique marker object indicating a state will eventuall be resolved
         * @param invalid_state a unique marker object indication a state is not valid
         * @param next_state a unique marker object indicating the state is equal to the next valid state
         * @param previous_state a unique marker object indicating the state is equal to the previous valid state
         */
        RangedResolver(const std::shared_ptr<T>& pending_state,
                       const std::shared_ptr<T>& invalid_state,
                       const std::shared_ptr<T>& next_state,
                       const std::shared_ptr<T>& previous_state);

        /**
         * Deconstructs this Ranged Resolver. Clears the list of states.
         */
        ~RangedResolver();

        /**
         * @brief Add new state for a specific version.
         *
         * Adds a new shared state to the list for the given version.
         * Only adds the state if the version is greater than the previous state's version.
         * Only adds the state if it is equal to DATA, PENDING, or INVALID.
         *
         * @param version the version of this state to add
         * @param state the state to add
         * @returns true if the state was added
         */
        bool Add(const int32_t version, const std::shared_ptr<T>& state);

        /**
         * @brief Update an existing state.
         *
         * Update an existing PENDING state at the specified version.
         * @note Only existing PENDING states may be updated.
         *
         * @param version the version of the state to update
         * @param state the state to replace the existing state
         * @returns true if the state was updated
         */
        bool Update(const int32_t version, const std::shared_ptr<T>& state);

        /**
         * @brief Resolves the given version to a shared state.
         *
         * Resolves the given version by traversing the list of shared states, returning the appropriate state.
         * + If the state at version *v* is DATA, PENDING, or INVALID, return it.
         * + If the state at version *v* is NEXT, return the first state after *v* that is either DATA, PENDING, or INVALID.
         *  + If there are no such states after *v*, return PENDING.
         * + If the state at version *v* is PREV, return Get(*v_prev*) where *v_prev* is the version of the first state with version < *v* that is either DATA, PENDING, INVALID, or NEXT.
         *  + If there are no such states before *v*, return PENDING.
         * + If no state has exactly version *v*, return Get(*v_prev*) where *v_prev* is the version of the first state with version < *v*.
         *  + If there are no such states before *v*, return PENDING.
         *
         * @param version the version to resolve to a state
         * @returns a state of either EventData, RangedResolver::PENDING, or RangedResolver::INVALID
         */
        const std::shared_ptr<T>& Get(const int32_t version);

        /**
         * @brief Determines if there are any valid states contained within this RangedResolver.
         *
         * A valid state is any value other than INVALID, NEXT, or PREV.
         * A PENDING state is considered valid as it is the expectation of data.
         *
         * @return true if this RangedResolver constains any value which is not INVALID, NEXT, or PREV
         */
        bool ContainsValidState() const;

    private:
        const std::shared_ptr<T>& PENDING; ///< state that is "on the way" and will eventually be resolved.
        const std::shared_ptr<T>&
        INVALID; ///< special "marker" state that indicates that this state is equal to the previous state.
        const std::shared_ptr<T>&
        NEXT; ///< special "marker" state that indicates that this state is equal to the next DATA/PENDING/INVALID state.
        const std::shared_ptr<T>& PREV; ///< special state that indicates that the state is not valid.

        typedef typename std::map<int32_t, std::shared_ptr<T>>::iterator states_it; ///< iterator type over states map

        /**
         * Iterate over the map of states starting at the given states iterator to find the first valid state.
         * Returns the state value (DATA, PENDING, or INVALID).
         * If the state is equal to the end of the states map, returns PENDING.
         *
         * @param it an iterator
         * @returns state value of DATA, PENDING, or INVALID
         */
        const std::shared_ptr<T>& Resolve(states_it it) const;

        std::map<int32_t, std::shared_ptr<T>> states_; ///< map of state version and data
    };

}

//////////////////////////////////
// Template Method Definitions
/////////////////////////////////

namespace AdobeMarketingMobile {

    template<class T>
    RangedResolver<T>::RangedResolver(const std::shared_ptr<T>& pending_state,
                                      const std::shared_ptr<T>& invalid_state,
                                      const std::shared_ptr<T>& next_state,
                                      const std::shared_ptr<T>& previous_state) :
        PENDING{pending_state},
        INVALID{invalid_state},
        NEXT{next_state},
        PREV{previous_state} {

        if (PENDING == INVALID
                || PENDING == NEXT
                || PENDING == PREV
                || INVALID == NEXT
                || INVALID == PREV
                || PREV == NEXT) {
            Log::Warning("RangedResolver", "Found equality between marker states! Pending(%p) Invalid(%p) Next(%p) Previous(%p)",
                         PENDING, INVALID, NEXT, PREV);
        }

        // Add initial NEXT state at beginning of map
        // May be replaced when adding a state to version 0
        states_.emplace(-1, NEXT);
    }

    template<class T>
    RangedResolver<T>::~RangedResolver() {
        states_.clear();
    }

    template<class T>
    bool RangedResolver<T>::Add(const int32_t version, const std::shared_ptr<T>& state) {
        // only add states of DATA, PENDING, or INVALID
        if (state == NEXT || state == PREV) {
            return false;
        }

        if (version > states_.rbegin()->first) {
            // Only add higher versions.
            states_.emplace(version, state);
            return true;
        }

        return false;
    }

    template<class T>
    bool RangedResolver<T>::Update(const int32_t version, const std::shared_ptr<T>& state) {
        // Update may only update PENDING states.
        // Return false for updating PENDING with PENDING so it does not trigger a state change event.
        if (state == PENDING) {
            return false;
        }

        auto it = states_.find(version);

        // Only allow updates to PENDING states
        if (it != states_.end() && it->second == PENDING) {
            it->second = state;
            return true;
        }

        return false;
    }

    template<class T>
    const std::shared_ptr<T>& RangedResolver<T>::Get(const int32_t version) {

        // returns an iterator to the first element not less than the given key (ie equal to or greater than)
        auto it = states_.lower_bound(version);

        // didn't find state with given version number, return latest state (which is less than given version)
        if (it == states_.end()) {
            if (it != states_.begin()) {
                return Resolve(std::prev(it)); // greatest shared state (version < event version)

            } else {
                // found no shared states in module map of shared states (iterator equals both end() and begin())
                // this should not occur as the map is created with an initial value
                return PENDING;
            }
        }

        // found state but but not exact match
        if (it->first != version) {
            if (it != states_.begin()) {
                // given version doesn't have shared state, return state not higher than requested for version
                return Resolve(std::prev(it));
            }
            // only found states with higher versions than requested
        }

        return Resolve(it); // exact match to event state or no lower states

    }

    template<class T>
    bool RangedResolver<T>::ContainsValidState() const {
        auto it = states_.begin();

        while (it != states_.end()) {
            if (it->second != INVALID && it->second != NEXT && it->second != PREV) {
                return true; // state is either DATA or PENDING
            }
            it = std::next(it);
        }

        return false; // reached end with no valid entries
    }

    template<class T>
    const std::shared_ptr<T>& RangedResolver<T>::Resolve(states_it it) const {
        // sanity check
        if (it == states_.end()) {
            return PENDING;
        }

        // trace back through states
        while (it->second == PREV) {
            it = std::prev(it);
        }
        // trace forward through states. once we move forward we don't go back.
        while ( it != states_.end() && (it->second == NEXT || it->second == PREV)) {
            it = std::next(it);
        }

        // off end of list and found no valid value
        if (it == states_.end()) {
            return PENDING;
        }

        return it->second;
    }

}


#endif /* ADOBEMOBILE_CORE_RANGEDRESOLVER_H */
