 // ---------
// Vector3.h
// ---------

#ifndef Vector_h
#define Vector_h

#include <algorithm>        // equal, lexicographical_compare, swap
#include <cstddef>          // ptrdiff_t, size_t
#include <initializer_list> // initializer_list
#include <memory>           // allocator
#include <stdexcept>        // out_of_range
#include <utility>          // !=, <=, >, >=

#include "Memory.h"  // my_destroy, my_uninitialized_copy, my_uninitialized_fill

/*
namespace std     {
namespace rel_ops {

template <typename T>
inline bool operator != (const T& lhs, const T& rhs) {
    return !(lhs == rhs);}

template <typename T>
inline bool operator <= (const T& lhs, const T& rhs) {
    return !(rhs < lhs);}

template <typename T>
inline bool operator > (const T& lhs, const T& rhs) {
    return (rhs < lhs);}

template <typename T>
inline bool operator >= (const T& lhs, const T& rhs) {
    return !(lhs < rhs);}

} // rel_ops
} // std;
*/

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;

template <typename T, typename A = std::allocator<T>>
class my_vector {
    friend bool operator == (const my_vector& lhs, const my_vector& rhs) {
        return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());}

    friend bool operator < (const my_vector& lhs, const my_vector& rhs) {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

    public:
        using allocator_type  = A;
        using value_type      = typename allocator_type::value_type;

        using size_type       = typename allocator_type::size_type;
        using difference_type = typename allocator_type::difference_type;

        using       pointer   = typename allocator_type::pointer;
        using const_pointer   = typename allocator_type::const_pointer;

        using       reference = typename allocator_type::reference;
        using const_reference = typename allocator_type::const_reference;

        using       iterator  = typename allocator_type::pointer;
        using const_iterator  = typename allocator_type::const_pointer;

    private:
        A       _a;
        pointer _b;
        pointer _e;

    public:
        explicit my_vector (size_type s = 0, const_reference v = T(), const A& a = A()) :
                _a (a),
                _b (s == 0 ? nullptr : _a.allocate(s)),
                _e (s == 0 ? nullptr : _b + s) {
            my_uninitialized_fill(_a, _b, _e, v);}

        my_vector (std::initializer_list<T> rhs, const A& a = A()) :
                _a (a),
                _b (rhs.size() == 0 ? nullptr : _a.allocate(rhs.size())),
                _e (rhs.size() == 0 ? nullptr : _b + rhs.size()) {
            my_uninitialized_copy(_a, rhs.begin(), rhs.end(), _b);}

        my_vector (const my_vector& rhs) :
                _a (rhs._a),
                _b (rhs.size() == 0 ? nullptr : _a.allocate(rhs.size())),
                _e (rhs.size() == 0 ? nullptr : _b + rhs.size()) {
            my_uninitialized_copy(_a, rhs._b, rhs._e, _b);}

        my_vector& operator = (my_vector rhs) {
            std::swap(_b, rhs._b);
            std::swap(_e, rhs._e);
            return *this;}

        ~my_vector () {
            my_destroy(_a, _b, _e);
            _a.deallocate(_b, size());}

        reference operator [] (size_type i) {
            return _b[i];}

        const_reference operator [] (size_type i) const {
            return (*const_cast<my_vector*>(this))[i];}

        reference at (size_type i) {
            if (i >= size())
                throw std::out_of_range("my_vector::at index out of range");
            return (*this)[i];}

        const_reference at (size_type i) const {
            return const_cast<my_vector*>(this)->at(i);}

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
