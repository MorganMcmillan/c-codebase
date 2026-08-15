#ifndef CLASS_IMPLICIT_H
#define CLASS_IMPLICIT_H

// This is a version of class.h where instead of macros taking in the
// class name, they instead use a defined macro.

// To use this library, CLASS must be defined as:
// `#define CLASS(x) ClassName##x`
// The x is needed to join names to the class name.
// Always remember to undefine these at the end of your file.

// This works because macros can call other macros, and macros that join no
// value simply spit out the left value.
// Note: this does not work on interfaces.

// Note: this library makes heavy use of an implicit self.
// `self` is always a pointer to the class/interface.

// --------------------
// Classes
// --------------------

// Define a class' fields.

#define fields(fields) typedef struct fields CLASS()

// Defines a class constructor.
// Expected to be followed by a {} function body.

#define constructor(...) CLASS() CLASS(_new)(__VA_ARGS__)

// Defines a class constructor without any extra arguments
// Expected to be followed by a {} function body.

#define constructor0() CLASS() Class(_new)(void)

// Defines a class destructor.
// This should free all allocated memory and resources associated with the
// instance.

#define destructor() void CLASS(_destroy)(Class * self)

// Alternative to calling `Class_new`. Unlike C++, this allocates on the heap,
// not the stack.

#define new(...) CLASS(_new)(__VA_ARGS__)

// Shorthand for initializing a class struct.

#define make(...) (CLASS()) {__VA_ARGS__}

// Calls the class destructor.

#define delete(Class, self) Class##_destroy(self)

// Calls the class destructor and then free.
// Used with classes that are allocated on the heap.

#define delete_and_free(Class, self)                                           \
    Class##_destroy(self);                                                     \
    free(self)

// Defines a class method
// Expected to be preceded by the return type, and followed by a {} function
// body.

#define method(name, ...) CLASS(_##name)(CLASS() * self, __VA_ARGS__)

// Defines a class method without any extra arguments.

#define method0(name) CLASS(_##name)(CLASS() * self)

// Calls a method belonging to the current class.

#define call(name, ...) CLASS(_##name)(self, __VA_ARGS__)

// Calls a method belonging to the current class without any extra arguments.

#define call0(name) CLASS(_##name)(self)

// Downcasts pointer of `self` to its superclass.

#define super() (&self->super)
//
// Downcasts pointer of `self` to its nth superclass.

#define super_n(n) (&self->super##n)

// Explicitly downcasts this instance to its superclass.

#define downcast(name) (&((name)->super))

// Explicitly downcasts this instance to its nth superclass.
// For use with multiple inheritance, where superclasses are named `super1`,
// `super2`, etc.

#define downcast_n(name, n) (&((name)->super##n))

// Explicitly downcasts one pointer type to another.

#define downcast_ptr(Class, name) (Class *)name

// Explicitly downcasts one pointer type to another, and assigns it to a new
// variable.

#define downcast_declare(Class, new_name, name) Class *new_name = (Class *)name

// --------------------
// Getters and setters
// --------------------

// Defines a getter method.

#define getter(name, type) type CLASS(_get_##name)(CLASS() * self)

// Defines a setter method.

#define setter(name, type) void CLASS(_set_##name)(CLASS() * self, type value)

// Defines a default getter method.

#define default_getter(name, type)                                             \
    type CLASS(_get_##name)(CLASS() * self) { return self->name; }

// Defines a default setter method.

#define default_setter(name, type)                                             \
    void CLASS(_set_##name)(CLASS() * self, type value) { self->name = value; }

// --------------------
// Interfaces and virtual methods
// --------------------

// Defines an interface as a class-vtable pointer pair.

#define interface(Interface, vtable_def)                                            \
    typedef struct vtable_def Interface##_vtable;                                   \
    typedef struct {                                                           \
        void *super;                                                           \
        Interface##_vtable *vtable;                                                 \
    } Interface

// Defines a concrete interface method.

#define imethod(Interface, name, ...)                                          \
    Interface##_##name(Interface *self, __VA_ARGS__)

// Defines a concrete interface method without any extra arguments

#define imethod0(Interface, name) Interface##_##name(Interface *self)

// Declares/defines a virtual method for a class-vtable pair.

#define virtual(name, ...) (*name)(void *self, __VA_ARGS__)

// Declares/defines a virtual method for a class-vtable pair, without any
// arguments.

#define virtual0(name) (*name)(void *self)

// Casts a function to a virtual table entry.

#define vcast(name, ret_type, ...) (ret_type (*)(void *, __VA_ARGS__)) name

// Casts a function to a virtual table entry, without extra arguments.

#define vcast0(name, ret_type) (ret_type (*)(void *)) name

// Calls a virtual method.
// This is meant only to be called inside an interface method.

#define vcall(self, name, ...)                                                 \
    (*self->vtable->name)((void *)self->super, __VA_ARGS__)

// Calls a virtual method without any extra arguments.
// This is meant only to be called inside an interface method.

#define vcall0(self, name) (*self->vtable->name)((void *)self->super)

// Calls a virtual method as the interface, not the inner data.

#define vcall_dyn(self, name, ...)                                             \
    (*self->vtable->name)((void *)self, __VA_ARGS__)

// Calls a virtual method as the interface, not the inner data,
// without any extra argumens.

#define vcall_dyn0(self, name) (*self->vtable->name)((void *)self)

// Gets a virtual constant from the vtable.

#define vget(self, name) self->vtable->name

// Foreward declares an implementation of an interface.

#define declare_impl(Class, Interface)                                         \
    extern Interface##_vtable Class##_##Interface##_vtable

// Defines an implementation of an interface.

#define impl(Class, Interface, ...)                                            \
    Interface##_vtable Class##_##Interface##_vtable =                          \
        (Interface##_vtable)__VA_ARGS__

// Creates an instance of an interface.
// This is similar to Rust's `dyn` keyword, which describes a type of trait
// object.

#define dyn(Interface, Class, value)                                           \
    (Interface) { .super = value, .vtable = &Class##_##Interface##_vtable }

#endif /* CLASS_H */
