/***********************************
 * Shared Pointers                 *
 * Developer: Matan Spada          *
 * Written: 2022-04-21             *
 *                                 *
 * Approved by:    Ehud            *
 ***********************************/

#include <cstddef>      // std::size_t, NULL


#if (__cplusplus <= 199711L)
 #define noexcept throw()
 #define nullptr NULL
#endif

namespace ilrd_rd1145
{


template <typename T>       
class SharedPtr
{
public:
    // Use dynamic allocation with new (NOT new[])
    explicit SharedPtr(T *ptr = nullptr);                                   
    ~SharedPtr() noexcept;                                                
    SharedPtr(const SharedPtr& other);  // Non-explicit on pupose          
    SharedPtr& operator=(const SharedPtr& other);                           

    template <typename S>                           
    SharedPtr(const SharedPtr<S>& other);                        
    template <typename S>
    SharedPtr& operator=(const SharedPtr<S>& other);                        
    
    T& operator*() const noexcept;                                        
    T* operator->() const noexcept;                                      
    T *Get() const noexcept;                                               
    bool IsShared() const noexcept;                                        
    
    template <typename S>  
    friend class SharedPtr; 

private:
    std::size_t *m_refCount;
    T *m_ptr;
};


/*************** end of class **************/

//CTOR
template <typename T> 
SharedPtr<T>::SharedPtr(T *ptr) : m_refCount(new std::size_t(1)), m_ptr(ptr)
{
   //empty
}


//DTOR
template <typename T> 
SharedPtr<T>::~SharedPtr() noexcept
{
    if(IsShared())
    {
        --*m_refCount;
    }
    else
    {
        delete m_refCount;
        delete m_ptr;
    }
}

//CCTOR
template <typename T> 
SharedPtr<T>::SharedPtr(const SharedPtr& other) : m_refCount(&++(*other.m_refCount)), m_ptr(other.m_ptr)     //refCount takes a ptr, thus we use &
{
    //empty
}


//OPERATOR=
template <typename T> 
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other)
{
    if (this != &other)
    {
        if(0 == --(*m_refCount))
        {
            delete m_refCount;
            delete m_ptr;
        }

        m_refCount = other.m_refCount;
        m_ptr = other.m_ptr;

        ++(*m_refCount);
    }

    return *this;
}


//Shared_ptr s1 = &a;
//Shared_ptr s2 = &b;

// s1 = s2 (s1 = &b)


/*************** class templates members **************/

template <typename T> 
template <typename S>
SharedPtr<T>::SharedPtr(const SharedPtr<S>& other) : m_refCount(&++(*other.m_refCount)), m_ptr(other.m_ptr)      //refCount takes a ptr, thus we use &
{
    //empty
}


template <typename T>
template <typename S>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<S>& other)
{
    if(0 == --(*m_refCount))
    {
        delete m_refCount;
        delete m_ptr;
    }

    m_refCount = other.m_refCount;
    m_ptr = static_cast<T*>(other.m_ptr);

    ++(*m_refCount);

    return *this;
}


/*************** other member functions **************/

template <typename T>
T& SharedPtr<T>::operator*() const noexcept
{
    return *m_ptr;
}


template <typename T>
T* SharedPtr<T>::operator->() const noexcept
{
    return m_ptr;
}


template <typename T>
T* SharedPtr<T>::Get() const noexcept
{
    return m_ptr;
}


template <typename T>
bool SharedPtr<T>::IsShared() const noexcept
{
    return *m_refCount > 1;
}


} // end of irld_rd1145
