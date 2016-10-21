// ---------
// Vector2.h
// ---------

#ifndef Vector_h
#define Vector_h

#include <algorithm> // copy, fill, swap
#include <cstddef>   // ptrdiff_t, size_t
#include <utility>  // !=

using std::rel_ops::operator!=;

template <typename T>
class my_vector {
    friend bool operator == (const my_vector& lhs, const my_vector& rhs) {
        return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.begin(), rhs.begin());}

    public:
        using value_type      = T;

        using size_type       = std::size_t;
        using difference_type = std::ptrdiff_t;

        using       pointer   =       value_type*;
        using const_pointer   = const value_type*;

        using       reference =       value_type&;
        using const_reference = const value_type&;

        using       iterator  =       pointer;
        using const_iterator  = const_pointer;

    private:
        pointer _b;
        pointer _e;

    public:
        explicit my_vector (size_type s = 0, const_reference v = T()) :
                _b ((s == 0) ? nullptr : new T[s]),
                _e ((s == 0) ? nullptr : _b + s) {
            std::fill(_b, _e, v);}

        my_vector (std::initializer_list<T> rhs) :
                _b ((rhs.size() == 0) ? nullptr : new T[rhs.size()]),
                _e ((rhs.size() == 0) ? nullptr : _b + rhs.size()) {
            std::copy(rhs.begin(), rhs.end(), _b);}

        my_vector (const my_vector& rhs) :
                _b (rhs.size() == 0 ? nullptr : new T[rhs.size()]),
                _e (rhs.size() == 0 ? nullptr : _b + rhs.size()) {
            std::copy(rhs._b, rhs._e, _b);}

        my_vector& operator = (my_vector rhs) {
            std::swap(_b, rhs._b);
            std::swap(_e, rhs._e);
            return *this;}

        ~my_vector () {
            delete [] _b;}

        reference operator [] (size_type i) {
            return _b[i];}

        const_reference operator [] (size_type i) const {
            return (*const_cast<my_vector*>(this))[i];}

        iterator begin () {
            return _b;}

        const_iterator begin () const {
            return const_cast<my_vector*>(this)->begin();}

        iterator end () {
            return _e;}

        const_iterator end () const {
            return const_cast<my_vector*>(this)->end();}

        size_type size () const {
            return _e - _b;}};

#endif // Vector_h
