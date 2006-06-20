#ifndef guard_array_traits_hpp
#define guard_array_traits_hpp
/**
 * @file
 *
 * @brief Implement the element manipulation traits for types with
 * array-like semantics.
 *
 * $Id$
 *
 * @author Carlos O'Ryan
 */

#include <algorithm>
#include "tao/Array_VarOut_T.h"

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

namespace TAO
{
namespace details
{

template <typename T_array_traits>
struct array_traits
{
  typedef typename T_array_traits::value_type value_type;
  typedef typename T_array_traits::value_type const const_value_type;
  typedef typename T_array_traits::slice_type slice_type;
  typedef typename T_array_traits::tag_type tag_type;

  inline static void copy (slice_type * _tao_to, const slice_type * _tao_from)
  {
    TAO::Array_Traits<value_type,slice_type,tag_type>::copy (_tao_to, _tao_from);
  }

  inline static void free (slice_type * value)
  {
    TAO::Array_Traits<value_type,slice_type,tag_type>::free (value);
  }

  inline static slice_type * alloc (void)
  {
    return TAO::Array_Traits<value_type,slice_type,tag_type>::alloc ();
  }

  inline static slice_type * dup(
      const slice_type * value)
  {
    return TAO::Array_Traits<value_type,slice_type,tag_type>::dup (value);
  }

  inline static void zero_range(
      value_type * begin, value_type * end)
  {
    std::for_each(
        begin, end, &TAO::Array_Traits<value_type,slice_type,tag_type>::zero);
  }

  inline static void initialize_range(
      value_type * begin, value_type * end)
  {
    std::for_each(
        begin, end, &TAO::Array_Traits<value_type,slice_type,tag_type>::zero);
  }

  inline static void copy_range(
      value_type * begin, value_type * end, value_type *dst)
  {
    for(value_type * i = begin; i != end; ++i, ++dst)
    {
      TAO::Array_Traits<value_type,slice_type,tag_type>::copy(*dst, *i);
    }
  }
};

} // namespace details
} // namespace CORBA

TAO_END_VERSIONED_NAMESPACE_DECL

#endif // guard_array_traits_hpp
