// Exercise 08: Rule of Zero with Composition
//
// PROBLEM:
//   When every member of a class is a well-behaved type (string, vector,
//   unique_ptr, shared_ptr, etc.), the compiler-generated special members
//   automatically do the right thing:
//     - Copy constructor copies each member.
//     - Move constructor moves each member.
//     - Destructor destroys each member.
//
//   This means you don't need to write ANY special members. The class just
//   works. This is the ideal we should aim for.
//
// TODO:
//   1. Implement the Document constructor.
//   2. Implement add_section: append a section to the sections vector.
//   3. Implement section_count and get_section.
//   The class should NOT have any custom destructor, copy, or move operations.
//   The compiler-generated defaults are correct because all members (string,
//   vector) handle their own resources.
//
// WHY:
//   Rule of Zero is the preferred default in modern C++. Design your members
//   so that composition gives you correct behavior for free. Save the Rule
//   of Five for the rare cases where you truly need custom resource management.

#pragma once

#include <string>
#include <vector>
#include <testkit/testkit.h>

struct Section {
    std::string title;
    std::string body;
};

class Document {
    std::string title_;
    std::string author_;
    std::vector<Section> sections_;

public:
    // Constructor: initialize title and author.
    Document(std::string title, std::string author) {
        TODO();
    }

    // No destructor, copy, or move operations needed!
    // The compiler generates correct ones from string and vector members.

    const std::string& title() const { return title_; }
    const std::string& author() const { return author_; }

    // Add a section to the document.
    void add_section(std::string title, std::string body) {
        TODO();
    }

    std::size_t section_count() const {
        TODO();
    }

    const Section& get_section(std::size_t index) const {
        TODO();
    }
};
