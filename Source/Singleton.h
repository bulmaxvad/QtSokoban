#ifndef SIGLETON_H
#define SIGLETON_H

// This idea takes from https://stackoverflow.com/questions/1008019/c-singleton-design-pattern

template<class T>
class Singleton
{
public:
    static T& get()
    {
        static T instance; // Guaranteed to be destroyed.
        return instance;
    }

    //~ T& operator()() const { return Singleton<T>::get(); }
//~ private:
    Singleton() // Constructor? (the {} brackets) are needed here.
    {}

public:
    Singleton(T const&)       = delete;
    void operator =(T const&) = delete;

    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status
};

#endif // SIGLETON_H
