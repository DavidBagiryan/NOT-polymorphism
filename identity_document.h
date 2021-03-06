#pragma once

#include <iostream>
#include <string>

using namespace std::string_view_literals;

struct vtable;

extern const vtable vtable_IdentityDocument;

class IdentityDocument {
    friend vtable;
public:
    IdentityDocument()
        : vtable_ptr(&vtable_IdentityDocument)
        , unique_id_(++unique_id_count_) 
    {
        std::cout << "IdentityDocument::Ctor() : "sv << unique_id_ << std::endl;
    }
    
    IdentityDocument(const vtable* vtable_ptr)
        : vtable_ptr(vtable_ptr)
        , unique_id_(++unique_id_count_) 
    {
        std::cout << "IdentityDocument::Ctor() : "sv << unique_id_ << std::endl;
    }

    ~IdentityDocument() {
        --unique_id_count_;
        std::cout << "IdentityDocument::Dtor() : "sv << unique_id_ << std::endl;
    }

    IdentityDocument(const IdentityDocument& other)
        : vtable_ptr(&vtable_IdentityDocument)
        , unique_id_(++unique_id_count_) 
    {
        std::cout << "IdentityDocument::CCtor() : "sv << unique_id_ << std::endl;
    }

    IdentityDocument& operator=(const IdentityDocument&) = delete;

    void PrintID_() const {
        std::cout << "IdentityDocument::PrintID() : "sv << unique_id_ << std::endl;
    }
    void PrintID() const;

    void Delete_() {
        delete this;
    }
    void Delete();

    static void PrintUniqueIDCount() {
        std::cout << "unique_id_count_ : "sv << unique_id_count_ << std::endl;
    }
    
protected:
    const vtable* vtable_ptr;
    
    int GetID() const {
        return unique_id_;
    }

private:
    static int unique_id_count_;
    int unique_id_;
};

int IdentityDocument::unique_id_count_ = 0;

struct vtable {
    vtable (void (IdentityDocument::* const PrintID)() const,
            void (IdentityDocument::* const Delete)()) 
        : PrintID(PrintID)
        , Delete(Delete) 
    { 
    }
    
    void (IdentityDocument::* const PrintID)() const;
    void (IdentityDocument::* const Delete)();
};

const vtable vtable_IdentityDocument(&IdentityDocument::PrintID_, &IdentityDocument::Delete_);

void IdentityDocument::PrintID() const {
    return (this->*(vtable_ptr->PrintID))();
}

void IdentityDocument::Delete() {
    return (this->*(vtable_ptr->Delete))();
}