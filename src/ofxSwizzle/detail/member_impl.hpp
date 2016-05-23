#ifndef OFX_SWIZZLE_DETAIL_MEMBER_IMPL_HPP
#define OFX_SWIZZLE_DETAIL_MEMBER_IMPL_HPP

#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include "./fwd.hpp"
#include "./swizzle_impl.hpp"

namespace ofxSwizzle { namespace detail {

template <typename T, std::size_t N>
class member_impl
    : protected swizzle_impl<T, N>
{
private:
    using base_type = swizzle_impl<T, N>;
    using base_type::elems;

protected:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = T const&;
    using pointer = T*;
    using const_pointer = T const*;
    using iterator = T*;
    using const_iterator = T const*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static constexpr size_type vector_size = N;

    member_impl() = default;
    member_impl(member_impl const&) = default;
    member_impl(member_impl&&) = default;

    using base_type::base_type;

    ~member_impl() = default;

    auto operator=(member_impl const&) & -> member_impl& = default;
    auto operator=(member_impl&&) & -> member_impl& = default;

    auto empty() const noexcept -> bool
    {
        return vector_size == 0;
    }

    auto size() const noexcept -> size_type
    {
        return vector_size;
    }

    auto max_size() const noexcept -> size_type
    {
        return vector_size;
    }

    auto data() noexcept -> pointer
    {
        return elems;
    }

    auto data() const noexcept -> const_pointer
    {
        return elems;
    }

    auto at(size_type i) -> reference
    {
        if (i > size())
        {
            throw std::out_of_range("Index out of range");
        }
        return elems[i];
    }

    auto at(size_type i) const -> const_reference
    {
        if (i > size())
        {
            throw std::out_of_range("Index out of range");
        }
        return elems[i];
    }

    auto operator[](size_type i) -> reference
    {
        return elems[i];
    }

    auto operator[](size_type i) const -> const_reference
    {
        return elems[i];
    }

    auto front() -> reference
    {
        return elems[0];
    }

    auto front() const -> const_reference
    {
        return elems[0];
    }

    auto back() -> reference
    {
        return elems[vector_size - 1];
    }

    auto back() const -> const_reference
    {
        return elems[vector_size - 1];
    }

    auto begin() noexcept -> iterator
    {
        return elems;
    }

    auto begin() const noexcept -> const_iterator
    {
        return elems;
    }

    auto end() noexcept -> iterator
    {
        return elems + vector_size;
    }

    auto end() const noexcept -> const_iterator
    {
        return elems + vector_size;
    }

    auto cbegin() const noexcept -> const_iterator
    {
        return elems;
    }

    auto cend() const noexcept -> const_iterator
    {
        return elems + vector_size;
    }

    auto rbegin() -> reverse_iterator
    {
        return end();
    }

    auto rbegin() const -> const_reverse_iterator
    {
        return end();
    }

    auto rend() -> reverse_iterator
    {
        return begin();
    }

    auto rend() const -> const_reverse_iterator
    {
        return begin();
    }

    auto crbegin() const -> const_reverse_iterator
    {
        return end();
    }

    auto crend() const -> const_reverse_iterator
    {
        return begin();
    }

    auto fill(value_type const& value)
        noexcept(std::is_nothrow_copy_assignable<value_type>::value)
    {
        for (auto& x : elems)
        {
            x = value;
        }
    }

    auto swap(ofxSwizzle::detail::vec<value_type, vector_size>& other)
        noexcept(ofxSwizzle::detail::is_nothrow_swappable_v<value_type>)
    {
        using std::swap;
        for (size_type i = 0; i < size(); ++i)
        {
            swap((*this)[i], other[i]);
        }
    }
};

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_MEMBER_IMPL_HPP
