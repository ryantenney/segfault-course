// Exercise 06: shared_ptr Aliasing Constructor
//
// The aliasing constructor creates a shared_ptr that shares ownership with
// an existing shared_ptr, but points to a different object (typically a
// member of the owned object). The syntax is:
//
//   std::shared_ptr<Member> alias(owner, &owner->member);
//
// The alias keeps the *owner* alive (shares its reference count), but
// dereferencing the alias yields the *member*. This is useful when you
// need a shared_ptr to a sub-object without a separate allocation.
//
// TODO:
//   Implement the functions below using the aliasing constructor.

#pragma once

#include <memory>
#include <string>
#include <testkit/testkit.h>

struct Address {
    std::string city;
    std::string zip;
};

struct Person {
    std::string name;
    Address address;
};

// Create a shared_ptr<Person> with the given name, city, and zip.
inline std::shared_ptr<Person> make_person(const std::string& name,
                                           const std::string& city,
                                           const std::string& zip) {
    TODO();
}

// Return a shared_ptr<Address> that aliases the person's address member.
// The returned pointer must share ownership with the person pointer.
inline std::shared_ptr<Address> get_address_ptr(const std::shared_ptr<Person>& person) {
    TODO();
}

// Return a shared_ptr<std::string> that aliases the person's name member.
inline std::shared_ptr<std::string> get_name_ptr(const std::shared_ptr<Person>& person) {
    TODO();
}
