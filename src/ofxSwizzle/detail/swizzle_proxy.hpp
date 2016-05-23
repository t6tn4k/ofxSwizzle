#ifndef OFX_SWIZZLE_DETAIL_SWIZZLE_PROXY_HPP
#define OFX_SWIZZLE_DETAIL_SWIZZLE_PROXY_HPP

#include <array>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include "./fwd.hpp"
#include "./has_duplicated.hpp"
#include "./is_nothrow_swappable.hpp"
#include "./vector_traits.hpp"

namespace ofxSwizzle { namespace detail {

template <typename T, std::size_t N, typename Indices>
class swizzle_proxy_base;

template <typename T, std::size_t N, typename Indices, bool IsConst>
class swizzle_proxy_iterator;

template <typename T, std::size_t N, std::size_t... Indices, bool IsConst>
class swizzle_proxy_iterator<T, N, std::index_sequence<Indices...>, IsConst>
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = std::conditional_t<IsConst, T const, T>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = value_type const&;
    using pointer = value_type*;
    using const_pointer = value_type const*;

private:
    using index_type = std::index_sequence<Indices...>;
    static constexpr std::size_t index_array[] = {Indices...};

    friend ofxSwizzle::detail::swizzle_proxy_base<T, N, index_type>;

    size_type index = 0;
    pointer holder = nullptr;

    constexpr swizzle_proxy_iterator(pointer ptr, size_type i)
        : holder(ptr), index(i)
    {
    }

public:
    constexpr swizzle_proxy_iterator() = default;
    constexpr swizzle_proxy_iterator(swizzle_proxy_iterator const&) = default;
    constexpr swizzle_proxy_iterator(swizzle_proxy_iterator&&) = default;

    ~swizzle_proxy_iterator() = default;

    constexpr auto operator=(swizzle_proxy_iterator const&) & -> swizzle_proxy_iterator& = default;
    constexpr auto operator=(swizzle_proxy_iterator&&) & -> swizzle_proxy_iterator& = default;

    constexpr auto operator==(swizzle_proxy_iterator const& other) const noexcept -> bool
    {
        return index == other.index && holder == other.holder;
    }

    constexpr auto operator!=(swizzle_proxy_iterator const& other) const noexcept -> bool
    {
        return !(*this == other);
    }

    constexpr auto operator*() -> reference
    {
        return holder[index_array[index]];
    }

    constexpr auto operator*() const -> const_reference
    {
        return holder[index_array[index]];
    }

    constexpr auto operator->() -> pointer
    {
        return holder + index_array[index];
    }

    constexpr auto operator->() const -> const_pointer
    {
        return holder + index_array[index];
    }

    constexpr auto operator++() noexcept -> swizzle_proxy_iterator&
    {
        ++index;
        return *this;
    }

    constexpr auto operator++(int) noexcept -> swizzle_proxy_iterator&
    {
        swizzle_proxy_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    constexpr auto operator--() noexcept -> swizzle_proxy_iterator&
    {
        --index;
        return *this;
    }

    constexpr auto operator--(int) noexcept -> swizzle_proxy_iterator&
    {
        swizzle_proxy_iterator tmp(*this);
        --(*this);
        return tmp;
    }

    constexpr auto operator+=(difference_type n) noexcept -> swizzle_proxy_iterator&
    {
        index += n;
        return *this;
    }

    constexpr auto operator-=(difference_type n) noexcept -> swizzle_proxy_iterator&
    {
        index -= n;
        return *this;
    }

    constexpr auto operator+(difference_type n) noexcept -> swizzle_proxy_iterator
    {
        swizzle_proxy_iterator iter(*this);
        return iter += n;
    }

    constexpr auto operator-(difference_type n) noexcept -> swizzle_proxy_iterator
    {
        swizzle_proxy_iterator iter(*this);
        return iter -= n;
    }

    constexpr auto operator-(swizzle_proxy_iterator const& other) noexcept -> difference_type
    {
        return static_cast<difference_type>(index_array[index])
            - static_cast<difference_type>(other.index_array[other.index]);
    }

    constexpr auto operator[](size_type i) -> reference
    {
        return holder[index_array[index + i]];
    }

    constexpr auto operator[](size_type i) const -> const_reference
    {
        return holder[index_array[index + i]];
    }

    constexpr auto operator<(swizzle_proxy_iterator const& other) noexcept -> bool
    {
        return index < other.index;
    }

    constexpr auto operator>(swizzle_proxy_iterator const& other) noexcept -> bool
    {
        return other < *this;
    }

    constexpr auto operator<=(swizzle_proxy_iterator const& other) noexcept -> bool
    {
        return !(other < *this);
    }

    constexpr auto operator>=(swizzle_proxy_iterator const& other) noexcept -> bool
    {
        return !(*this < other);
    }

    constexpr auto swap(swizzle_proxy_iterator& other) & noexcept
    {
        using std::swap;
        swap(index, other.index);
        swap(holder, other.holder);
    }
};

template <typename T, std::size_t N, std::size_t... Indices, bool IsConst>
constexpr std::size_t ofxSwizzle::detail::swizzle_proxy_iterator<
    T, N, std::index_sequence<Indices...>, IsConst>::index_array[];

template <typename T, std::size_t N, typename Indices, bool IsConst>
inline constexpr auto swap(
    ofxSwizzle::detail::swizzle_proxy_iterator<T, N, Indices, IsConst>& lhs,
    ofxSwizzle::detail::swizzle_proxy_iterator<T, N, Indices, IsConst>& rhs) noexcept
{
    lhs.swap(rhs);
}

template <std::size_t... Indices>
constexpr auto in_range(std::size_t min, std::size_t sup, std::index_sequence<Indices...>)
{
    for (auto i : {Indices...})
    {
        if (i < min || sup <= i)
        {
            return false;
        }
    }
    return true;
}

template <typename T, std::size_t N, std::size_t... Indices>
class swizzle_proxy_base<T, N, std::index_sequence<Indices...>>
{
private:
    using index_type = std::index_sequence<Indices...>;

    static_assert(ofxSwizzle::detail::in_range(0, N, index_type()), "Index out of range");

protected:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = T const&;
    using pointer = T*;
    using const_pointer = T const*;

    static constexpr size_type vector_size = sizeof...(Indices);

    using iterator
        = ofxSwizzle::detail::swizzle_proxy_iterator<T, N, index_type, false>;
    using const_iterator
        = ofxSwizzle::detail::swizzle_proxy_iterator<T, N, index_type, true> const;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    value_type elems[N];

protected:
    constexpr swizzle_proxy_base() = default;
    constexpr swizzle_proxy_base(swizzle_proxy_base const&) = default;
    constexpr swizzle_proxy_base(swizzle_proxy_base&&) = default;

    ~swizzle_proxy_base() = default;

    using proxy_type = ofxSwizzle::detail::swizzle_proxy<
        T, N, index_type, !ofxSwizzle::detail::has_duplicated(index_type())>;

    using convertible_type = std::conditional_t<
        !std::is_convertible<value_type, float>::value,
        proxy_type,
        std::conditional_t<
            vector_size == 2,
            ofVec2f,
            std::conditional_t<
                vector_size == 3,
                ofVec3f,
                std::conditional_t<
                    vector_size == 4,
                    ofVec4f,
                    proxy_type>>>>;

    operator convertible_type() const
        noexcept(std::is_nothrow_constructible<convertible_type,
            decltype(Indices, std::declval<value_type const&>())...>::value)
    {
        return convertible_type(elems[Indices]...);
    }

    constexpr auto empty() const noexcept -> bool
    {
        return vector_size == 0;
    }

    constexpr auto size() const noexcept -> size_type
    {
        return vector_size;
    }

    constexpr auto max_size() const noexcept -> size_type
    {
        return vector_size;
    }

    constexpr auto data() noexcept -> pointer
    {
        return elems;
    }

    constexpr auto data() const noexcept -> const_pointer
    {
        return elems;
    }

    constexpr auto begin() noexcept -> iterator
    {
        return iterator(elems, 0);
    }

    constexpr auto begin() const noexcept -> const_iterator
    {
        return const_iterator(elems, 0);
    }

    constexpr auto end() noexcept -> iterator
    {
        return iterator(elems, vector_size);
    }

    constexpr auto end() const noexcept -> const_iterator
    {
        return const_iterator(elems, vector_size);
    }

    constexpr auto cbegin() const noexcept -> const_iterator
    {
        return const_iterator(elems, 0);
    }

    constexpr auto cend() const noexcept -> const_iterator
    {
        return const_iterator(elems, vector_size);
    }

    auto rbegin() noexcept -> reverse_iterator
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
        return end();
    }

    auto crbegin() const -> const_reverse_iterator
    {
        return end();
    }

    auto crend() const -> const_reverse_iterator
    {
        return begin();
    }

    constexpr auto at(size_type i) -> reference
    {
        if (i >= size())
        {
            throw std::out_of_range("Index out of range");
        }
        return begin()[i];
    }

    constexpr auto at(size_type i) const -> const_reference
    {
        if (i >= size())
        {
            throw std::out_of_range("Index out of range");
        }
        return cbegin()[i];
    }

    constexpr auto operator[](size_type i) -> reference
    {
        return begin()[i];
    }

    constexpr auto operator[](size_type i) const -> const_reference
    {
        return begin()[i];
    }

    constexpr auto front() -> reference
    {
        return *begin();
    }

    constexpr auto front() const -> const_reference
    {
        return *cbegin();
    }

    constexpr auto back() -> reference
    {
        return *end();
    }

    constexpr auto back() const -> const_reference
    {
        return *cend();
    }

    constexpr auto fill(value_type const& value)
        noexcept(std::is_nothrow_copy_assignable<value_type>::value)
    {
        for (auto i : {Indices...})
        {
            (*this)[i] = value;
        }
    }
};

template <typename T, std::size_t N, std::size_t Index>
class swizzle_proxy<T, N, std::index_sequence<Index>, true>
{
    static_assert(Index < N, "Index out of range");

private:
    using value_type = T;
    value_type elems[N];

public:
    constexpr swizzle_proxy() = default;
    constexpr swizzle_proxy(swizzle_proxy const&) = default;
    constexpr swizzle_proxy(swizzle_proxy&&) = default;

    ~swizzle_proxy() = default;

    constexpr auto operator=(value_type const& other) &
        noexcept(std::is_nothrow_copy_assignable<value_type>::value)
        -> swizzle_proxy&
    {
        elems[Index] = other;
        return *this;
    }

    constexpr auto operator=(value_type&& other) &
        noexcept(std::is_nothrow_move_assignable<value_type>::value)
        -> swizzle_proxy&
    {
        elems[Index] = std::move(other);
        return *this;
    }

    constexpr operator value_type() const&
        noexcept(std::is_nothrow_copy_constructible<value_type>::value)
    {
        return elems[Index];
    }

    constexpr operator value_type() &&
        noexcept(std::is_nothrow_move_constructible<value_type>::value)
    {
        return std::move(elems[Index]);
    }

    constexpr auto swap(swizzle_proxy& other) &
        noexcept(
            (std::is_nothrow_move_constructible<value_type>::value
                && std::is_nothrow_move_assignable<value_type>::value)
            || (std::is_nothrow_copy_constructible<value_type>::value
                && std::is_nothrow_copy_assignable<value_type>::value))
    {
        auto tmp = std::move_if_noexcept(elems[Index]);
        elems[Index] = static_cast<value_type>(std::move_if_noexcept(other));
        other = std::move_if_noexcept(tmp);
    }
};

template <typename T, std::size_t N, typename Indices>
class swizzle_proxy<T, N, Indices, false>
    : private ofxSwizzle::detail::swizzle_proxy_base<T, N, Indices>
{
private:
    using base_type = ofxSwizzle::detail::swizzle_proxy_base<T, N, Indices>;

public:
    using typename base_type::value_type;
    using typename base_type::size_type;
    using typename base_type::difference_type;
    using typename base_type::reference;
    using typename base_type::const_reference;
    using typename base_type::pointer;
    using typename base_type::const_pointer;
    using typename base_type::iterator;
    using typename base_type::const_iterator;
    using typename base_type::reverse_iterator;
    using typename base_type::const_reverse_iterator;

    using base_type::vector_size;

    constexpr swizzle_proxy() = default;
    constexpr swizzle_proxy(swizzle_proxy const&) = default;
    constexpr swizzle_proxy(swizzle_proxy&&) = default;

    ~swizzle_proxy() = default;

    auto operator=(swizzle_proxy const&) = delete;
    auto operator=(swizzle_proxy&&) = delete;

    using base_type::operator typename base_type::convertible_type;

    using base_type::empty;
    using base_type::size;
    using base_type::max_size;
    using base_type::data;
    using base_type::at;
    using base_type::operator[];
    using base_type::front;
    using base_type::back;
    using base_type::begin;
    using base_type::end;
    using base_type::cbegin;
    using base_type::cend;
    using base_type::rbegin;
    using base_type::rend;
    using base_type::crbegin;
    using base_type::crend;
    using base_type::fill;

    constexpr auto swap(swizzle_proxy& other) &
        noexcept(ofxSwizzle::detail::is_nothrow_swappable_v<value_type>)
    {
        using std::swap;
        for (size_type i = 0; i < size(); ++i)
        {
            swap((*this)[i], other[i]);
        }
    }
};

template <typename T, std::size_t N, typename Indices>
class swizzle_proxy<T, N, Indices, true>
    : private ofxSwizzle::detail::swizzle_proxy_base<T, N, Indices>
{
private:
    using base_type = ofxSwizzle::detail::swizzle_proxy_base<T, N, Indices>;

public:
    using typename base_type::value_type;
    using typename base_type::size_type;
    using typename base_type::difference_type;
    using typename base_type::reference;
    using typename base_type::const_reference;
    using typename base_type::pointer;
    using typename base_type::const_pointer;
    using typename base_type::iterator;
    using typename base_type::const_iterator;
    using typename base_type::reverse_iterator;
    using typename base_type::const_reverse_iterator;

    using base_type::vector_size;

    constexpr swizzle_proxy() = default;
    constexpr swizzle_proxy(swizzle_proxy const&) = default;
    constexpr swizzle_proxy(swizzle_proxy&&) = default;

    ~swizzle_proxy() = default;

    auto operator=(ofxSwizzle::detail::vec<value_type, vector_size> const& other) &
        noexcept(std::is_nothrow_copy_assignable<value_type>::value)
        -> swizzle_proxy&
    {
        for (size_type i = 0; i < size(); ++i)
        {
            (*this)[i] = other[i];
        }
        return *this;
    }

    auto operator=(ofxSwizzle::detail::vec<value_type, vector_size>&& other) &
        noexcept(std::is_nothrow_move_assignable<value_type>::value)
        -> swizzle_proxy&
    {
        for (size_type i = 0; i < size(); ++i)
        {
            (*this)[i] = std::move(other[i]);
        }
        return *this;
    }

    using base_type::operator typename base_type::convertible_type;

    using base_type::empty;
    using base_type::size;
    using base_type::max_size;
    using base_type::data;
    using base_type::at;
    using base_type::operator[];
    using base_type::front;
    using base_type::back;
    using base_type::begin;
    using base_type::end;
    using base_type::cbegin;
    using base_type::cend;
    using base_type::rbegin;
    using base_type::rend;
    using base_type::crbegin;
    using base_type::crend;
    using base_type::fill;

    constexpr auto swap(swizzle_proxy& other) &
        noexcept(ofxSwizzle::detail::is_nothrow_swappable_v<value_type>)
    {
        using std::swap;
        for (size_type i = 0; i < size(); ++i)
        {
            swap((*this)[i], other[i]);
        }
    }
};

template <
    typename T,
    std::size_t N1, typename Indices1,
    std::size_t N2, typename Indices2>
constexpr auto swap(
    ofxSwizzle::detail::swizzle_proxy<T, N1, Indices1, true>& lhs,
    ofxSwizzle::detail::swizzle_proxy<T, N2, Indices2, true>& rhs)
    noexcept(ofxSwizzle::detail::is_nothrow_swappable_v<T>)
    -> std::enable_if_t<Indices1::size() == Indices2::size()>
{
    using std::swap;
    for (std::size_t i = 0; i < Indices1::size(); ++i)
    {
        swap(lhs[i], rhs[i]);
    }
}

} } // namespace ofxSwizzle::detail

#endif // #ifndef OFX_SWIZZLE_DETAIL_SWIZZLE_PROXY_HPP
