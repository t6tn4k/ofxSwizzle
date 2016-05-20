#ifndef OFX_SWIZZLE_DETAIL_HAS_DUPLICATED_HPP
#define OFX_SWIZZLE_DETAIL_HAS_DUPLICATED_HPP

#include <iterator>
#include <utility>

namespace ofxSwizzle { namespace detail { namespace {

template <std::size_t... Indices>
constexpr auto has_duplicated(std::index_sequence<Indices...>) noexcept
{
    std::size_t const a[]{Indices...};
    for (auto i = std::begin(a); i < std::end(a); ++i)
    {
        for (auto j = std::begin(a); j < i; ++j)
        {
            if (*i == *j)
            {
                return true;
            }
        }
    }
    return false;
}

} } } // namespace ofxSwizzle::detail::<unnamed>

#endif // #ifndef OFX_SWIZZLE_DETAIL_HAS_DUPLICATED_HPP
