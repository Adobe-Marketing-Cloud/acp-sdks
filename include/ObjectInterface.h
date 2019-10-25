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

#ifndef ADOBEMOBILE_CORE_OBJECTINTERFACE_H
#define ADOBEMOBILE_CORE_OBJECTINTERFACE_H

#include <memory>

namespace AdobeMarketingMobile {

    class ToStringOptions;

    /**
     * @class ObjectInterface
     * ObjectInterface is the root base class for pure virtual interfaces (Java-style interfaces) in the SDK.
     *
     * HOW TO IMPLEMENT AN INTERFACE
     * -----------------------------
     *
     * When implementing an interface, PUBLIC VIRTUAL inheritance must be used for interface:
     *
     * Example:
     *
     *   class AInterface : public virtual ObjectInterface {};
     *   class BInterface : public virtual ObjectInterface {};
     *   class ABImplementation :
     *     public Object, // <-- Object inheritance is public non-virtual
     * 	   public virtual AInterface, // <-- interface inheritance is public virtual
     * 	   public virtual BInterface  // <-- interface inheritance is public virtual
     *   {}
     *
     * WHEN TO DERIVE FROM OBJECT INTERFACE
     * ------------------------------------
     *
     * All pure virtual classes should be derived from Object (either directly or via a base class).
     *
     * Pure virtual classes may not have any data members. A class that defines data members should be derived
     * from Object or be a POD class. See Object for additional details.
     *
     * HOW TO DERIVE FROM OBJECT INTERFACE
     * -----------------------------------
     *
     * When defining a direct subclass of ObjectInterface, PUBLIC VIRTUAL inheritance must be used:
     *
     * Example:
     *
     *   class MyInterface : public virtual ObjectInterface {
     *   };
     *
     * The same is true for descendent classes:
     *
     * Example:
     *
     *   class AInterface : public virtual ObjectInterface {};
     *   class BInterface : public virtual AInterface {}; // <-- public virtual inheritance
     *
     * Multiple inheritance from Object Interface is allowed, but again must be public virtual:
     *
     * Example:
     *
     *   class AInterface : public virtual ObjectInterface {};
     *   class BInterface : public virtual ObjectInterface {};
     *   class CInterface : public virtual AInterface, public virtual BInterface {}; // <-- public virtual inheritance
     *
     * WHY DERIVE FROM OBJECT INTERFACE
     * --------------------------------
     *
     * ObjectInterface provides subclasses a number of benefits:
     * - ObjectInterface prevents common C++ errors. Subclasses automatically have a virtual destructor and do not generate the copy and move functions.
     * - Subclasses are automatically compatible with ObjectToSharedPtr, which lets you get a shared_ptr from a raw ptr in a safe way.
     * - Instances can be treated polymorphically, which allows them to be stored into maps and other data structures.
     *
     * PASSING AROUND INSTANCES
     * ------------------------
     *
     * ObjectInterfaces are intended be passed by pointer or reference.
     *
     * CONVERTING REFERENCES AND RAW PTRS TO SHARED PTRS
     * -------------------------------------------------
     *
     * To convert an ObjectInterface pointer or reference to a std::shared_ptr, use ObjectToSharedPtr:
     *
     *   class AInterface : public virtual ObjectInterface {};
     *
     *   void example1(AInterface* a) {
     *     auto aSharedPtr = ObjectToSharedPtr(*a); // aSharedPtr is a std::shared_ptr<AInterface>
     *   }
     *
     *   void example2(AInterface& a) {
     *     auto aSharedPtr = ObjectToSharedPtr(a); // aSharedPtr is a std::shared_ptr<AInterface>
     *   }
     *
     * EQUALITY
     * --------
     * AdobeMarketingMobile::IsEqual(...) can be used to check if two interface instances are equal. See
     * ObjectInterface::Equals(...) and AdobeMarketingMobile::IsEqual(...).
     */
    class ObjectInterface {
    public:
        virtual ~ObjectInterface() {}

        /**
         * ObjectInterfaces are not copyable, as they should be passed by pointer or reference.
         * Subclasses that need copy functionality should add a method to the subclass that will perform the copy.
         */
        ObjectInterface(const ObjectInterface&) = delete;
        ObjectInterface& operator=(const ObjectInterface&) = delete;

        /**
         * ObjectInterfaces are not movable, as they should be passed by pointer or reference.
         * Subclasses that need move functionality should add a method to the subclass that will perform the move.
         */
        ObjectInterface(ObjectInterface&&) = delete;
        ObjectInterface&& operator=(ObjectInterface&&) = delete;

        /**
         * Instead of calling this function directly, since IsEqual checks for null.
         *
         * Subclasses can override this to provide a custom definition of equality. When implementing Equals, it is
         * suggested that implementers:
         * - Make sure that the operation is order independent: `this.Equals(someObject) == someObject.Equals(*this);`
         * - If necessary, check the type of right using `dynamic_cast<SomeSubclass*>(right)` and comparing against nullptr.
         *
         * The default implementation of Object::Equals is true only if both objects are the same instance.
         *
         * Example:
         *
         *    class Person : public Object {
         *    public:
         *       explicit Person(const std::string& name) : name_{ name } {}
         *
         *       bool Equals(const ObjectInterface& right) override {
         *         const Person* rightPerson = dynamic_cast<const Person*>(right);
         *         return right != nullptr && // right must be a Person
         *                rightPerson.name_ == name; // right must have the same name as this
         *       }
         *    };
         */
        virtual bool Equals(const ObjectInterface& right) const = 0;

        /**
         * Internal use only. See ObjectToSharedPtr for a method that will convert raw ptrs to smart ptrs.
         * Returns a std::shared_ptr to this.
         */
        virtual std::shared_ptr<ObjectInterface> SharedPtrToThisObjectInterface() = 0;

        /**
         * Converts this to a string. Equivalent to calling `StringUtils::ToString(*this)`.
         *
         * @return a string respresentation of this
         *
         * @see StringUtils::ToString()
         */
        std::string ToString() const;

        /**
         * Converts this to a string. Equivalent to calling `StringUtils::ToString(*this, options)`.
         *
         * @return a string representation of this
         *
         * @see StringUtils::ToString()
         */
        std::string ToString(const ToStringOptions& options) const;

        /**
         * Called by StringUtils::ToString() to actually convert this object to a string. Only subclasses and
         * StringUtils::ToString() should invoke this method. Others should not invoke this method directly, and instead
         * call StringUtils::ToString() to conver this object to a string.
         *
         * Subclasses can override this method to provide a custom string representation. To get the superclass string
         * representation implementations should invoke ToStringImpl on their base class directly. Objects are
         * encouraged to format their representations as JSON.
         *
         * @see StringUtils::ToString()
         *
         * @param options - options for the string representation
         *
         * @return a string representation of this
         */
        virtual std::string ToStringImpl(const ToStringOptions& options) const = 0;

    protected:
        ObjectInterface() {}
    };

    /**
     * Converts an instance to a std::shared_ptr. Useful for converting this or other raw ptrs to shared_ptrs.
     *
     * Argument must be an instance derived from Object or Object Interface. See Object Interface.
     */
    template<typename T>
    std::shared_ptr <T> ObjectToSharedPtr(T& o);
    template<>
    std::shared_ptr <ObjectInterface> ObjectToSharedPtr(ObjectInterface& o);

    /**
     * bool IsEqual(left, right) compares two Objects (or ObjectInterfaces) and returns true if left.Equals(right).
     *
     * See ObjectInterface for information on how to correctly implement Object::Equals.
     *
     * IsEqual accepts multiple different types for left and right. left and right can be:
     *   - Object/ObjectInterface instances (or subclasses),
     *   - shared_ptrs to Objects/ObjectInterfaces (or subclasses)
     *   - raw pointers to Objects/ObjectInterfaces (or subclasses)
     *
     * If left and right are pointers or shared_ptrs, nullptr values will be treated specially. If both left and right are nullptr,
     * IsEqual returns true. If only one of left or right is nullptr, IsEqual returns false.
     *
     * Examples:
     *
     *    class Person : public Object {
     *    public:
     *       explicit Person(const std::string& name) : name_{ name } {}
     *
     *       bool Equals(const ObjectInterface& right) override {
     *         const Person* rightPerson = dynamic_cast<const Person*>(right);
     *         return right != nullptr && // right must be a Person
     *                rightPerson.name_ == name; // right must have the same name as this
     *       }
     *    };
     *
     *    void AnExampleUsage() {
     *      std::shared_ptr<Person> fred1 = std::make_shared<Person>("fred");
     *      std::shared_ptr<Person> fred2 = std::make_shared<Person>("fred");
     *      std::shared_ptr<Person> susan = std::make_shared<Person>("susan");
     *      std::shared_ptr<Object> rock = std::make_shared<Object>();
     *      std::shared_ptr<Person> nullPointer;
     *
     *      IsEqual(fred1, fred1); // true
     *      IsEqual(fred1, susan); // false
     *      IsEqual(fred1, rock); // false
     *      IsEqual(fred1, fred2); // returns true because IsEqual compares by name
     *      IsEqual(fred1, nullPointer); // false
     *      IsEqual(nullPointer, nullPointer); // true
     *
     *      // you can also pass in Object instances directly
     *      IsEqual(*fred1, *fred2); // false
     *      IsEqual(*fred1, *rock); // false
     *
     *      // ... or raw ptrs to Objects
     *      IsEqual(fred1.get(), fred2.get()); // false
     *      IsEqual(fred1.get(), rock.get()); // false
     *      IsEqual(fred1.get(), nullptr); // false
     *    }
     */
    template<typename TLeft, typename TRight>
    bool IsEqual(const std::shared_ptr<TLeft>& left, const std::shared_ptr<TRight>& right);
    template<typename TLeft, typename TRight>
    bool IsEqual(const TLeft* left, const std::shared_ptr<TRight>& right);
    template<typename TLeft, typename TRight>
    bool IsEqual(const std::shared_ptr<TLeft>& left, const TRight* right);
    bool IsEqual(const ObjectInterface* left, const ObjectInterface* right);
    bool IsEqual(const ObjectInterface& left, const ObjectInterface& right);

    /**
     * @private
     *
     * `ToStringImpl` for `ObjectInterface`.
     */
    void ToStringImpl(std::ostream& the_stream, const ObjectInterface& value, const ToStringOptions& options);
}

/////////////////////////////////////////
// template and inline implementations //
/////////////////////////////////////////

namespace AdobeMarketingMobile {
    template<typename T>
    std::shared_ptr <T> ObjectToSharedPtr(T& o) {
        static_assert(std::is_base_of<ObjectInterface, T>::value, "Type of o must be derived from ObjectInterface.");
        return std::dynamic_pointer_cast<T>(o.SharedPtrToThisObjectInterface());
    }

    template<typename TLeft, typename TRight>
    bool IsEqual(const std::shared_ptr<TLeft>& left, const std::shared_ptr<TRight>& right) {
        static_assert(std::is_base_of<ObjectInterface, TLeft>::value, "Type of left must be derived from ObjectInterface.");
        static_assert(std::is_base_of<ObjectInterface, TRight>::value, "Type of right must be derived from ObjectInterface.");
        return IsEqual(left.get(), right.get());
    }

    template<typename TLeft, typename TRight>
    bool IsEqual(const TLeft* left, const std::shared_ptr<TRight>& right) {
        static_assert(std::is_base_of<ObjectInterface, TLeft>::value, "Type of left must be derived from ObjectInterface.");
        static_assert(std::is_base_of<ObjectInterface, TRight>::value, "Type of right must be derived from ObjectInterface.");
        return IsEqual(left, right.get());
    }

    template<typename TLeft, typename TRight>
    bool IsEqual(const std::shared_ptr<TLeft>& left, const TRight* right) {
        static_assert(std::is_base_of<ObjectInterface, TLeft>::value, "Type of left must be derived from ObjectInterface.");
        static_assert(std::is_base_of<ObjectInterface, TRight>::value, "Type of right must be derived from ObjectInterface.");
        return IsEqual(left.get(), right);
    }
}

#endif //ADOBEMOBILE_CORE_OBJECTINTERFACE_H
