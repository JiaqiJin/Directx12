#include <iostream>

#include <rttr/registration.h>
using namespace rttr;

struct MyStruct 
{ 
    MyStruct() {}; 
    void func(double) {};
    int data; 
};

RTTR_REGISTRATION
{
    registration::class_<MyStruct>("MyStruct")
            .constructor<>()(rttr::policy::ctor::as_raw_ptr)
            .property("data", &MyStruct::data)
            .method("func", &MyStruct::func);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    {
        type t = type::get<MyStruct>();
        for (auto& prop : t.get_properties())
            std::cout << "name: " << prop.get_name() << std::endl;

        for (auto& meth : t.get_methods())
            std::cout << "name: " << meth.get_name() << std::endl;
    }

    {
        type t = type::get_by_name("MyStruct");

        variant var = t.create(); 

        constructor ctor = t.get_constructor();
        var = ctor.invoke();
        std::cout << var.get_type().get_name();

        auto ptr = var.get_value<MyStruct*>();
        ptr->data = 1;
        ptr->func(1.0);
    }


    return 0;
}