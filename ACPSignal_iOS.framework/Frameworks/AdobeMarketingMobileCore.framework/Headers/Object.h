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

#ifndef ADOBEMOBILE_CORE_OBJECT_H
#define ADOBEMOBILE_CORE_OBJECT_H

#include "ObjectInterface.h"

namespace AdobeMarketingMobile {

    /**
     * @class Object
     * Object is the root base class for most classes in the SDK.
     *
     * WHEN TO DERIVE FROM OBJECT
     * --------------------------
     *
     * Most classes in the SDK should be derived from Object (either directly or via a base class). Generally, if a class is not an interface,
     * enum class, or a POD class, it should derive from Object.
     *
     * More formally, the following classes must be derived from Object:
     * - Any class that has any data members, except POD classes. A POD class is a struct with no inheritance or virtual members.
     * - Any class that is intended to be used as a base class, except pure virtual classes (interfaces). Pure virtual classes should
     * be derived from ObjectInterface.
     *
     * HOW TO DERIVE FROM OBJECT
     * -------------------------
     *
     * When defining a direct subclass of Object, public non-virtual inheritance must be used:
     *
     *   class MyClass : public Object {
     *   };
     *
     * The same is true for descendent classes:
     *
     *   class A : public Object {};
     *   class B : public A {}; // <-- public non-virtual inheritance
     *
     * Subclasses must derive from Object exactly once. That is, multiple inheritance from Object is not allowed:
     *
     *   class A : public Object {};
     *   class B : public Object {};
     *   class C : public A, public B {}; // <-- NOT ALLOWED!!!
     *
     * WHY DERIVE FROM OBJECT
     * ----------------------
     *
     * Object provides subclasses a number of benefits:
     * - Objects are compatible with ObjectToSharedPtr, which retrieves a shared_ptr from a raw ptr in a safe way.
     * - Objects get all the benefits of Object Interface, including:
     *     - Preventing common C++ errors. Subclasses automatically have a virtual destructor and do not generate the copy and move functions.
     *     - Allows instances to be treated polymorphically, which allows instances to be stored into maps and other data structures.
     *
     *
     * CREATING AND PASSING AROUND OBJECTS
     * -----------------------------------
     *
     * Objects are typically created on the heap, using std::make_shared:
     *
     *   class A : public Object {
     *   public:
     *     A();
     *     SomeMethod();
     *   };
     *
     *   void foo() {
     *     auto anInstanceOfA = std::make_shared<A>();
     *     anInstanceOfA->SomeMethod();
     *   }
     *
     * Some classes may provide factory functions to create instances.
     *
     * Objects are intended be passed by pointer or reference:
     *
     *   class A : public Object {
     *   public:
     *     A();
     *     SomeMethod();
     *   };
     *
     *   void foo() {
     *     auto anInstanceOfA = std::make_shared<A>();
     *     bar(*anInstanceOfA);
     *   }
     *
     *   void bar(A& anInstanceOfA) {
     *     anInstanceOfA->SomeMethod();
     *   }
     *
     * CONVERTING REFERENCES AND RAW PTRS TO SHARED PTRS
     * -------------------------------------------------
     *
     * To convert an Object pointer or reference to a std::shared_ptr, use ObjectToSharedPtr:
     *
     *   class A : public Object {};
     *
     *   void example1(A* a) {
     *     auto aSharedPtr = ObjectToSharedPtr(*a); // aSharedPtr is a std::shared_ptr<AInterface>
     *   }
     *
     *   void example2(A& a) {
     *     auto aSharedPtr = ObjectToSharedPtr(a); // aSharedPtr is a std::shared_ptr<AInterface>
     *   }
     *
     * EQUALITY
     * --------
     * AdobeMarketingMobile::IsEqual(...) can be used to check if two objects are equal. Subclasses
     * can override Object::Equals to provide a custom definiton of equality. See ObjectInterface.
     */
    class Object :
        public std::enable_shared_from_this<Object>,
        public virtual ObjectInterface {
    public:
        Object() {}

        /**
         * @see ObjectInterface
         */
        bool Equals(const ObjectInterface& right) const override;

        /**
         * @see ObjectInterface
         */
        std::shared_ptr<ObjectInterface> SharedPtrToThisObjectInterface() override final;

        /**
         * @see StringUtils::ToString()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;
    };
}

#endif //ADOBEMOBILE_CORE_OBJECT_H
