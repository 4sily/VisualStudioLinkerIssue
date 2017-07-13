#pragma once

// disable conversion from CString with boost::lexical_cast

namespace ATL
{
  template< typename BaseType, class StringTraits >
  class CStringT;
}

namespace boost
{
  template<typename T, typename BaseType, typename StringTraits>
  void lexical_cast(const ATL::CStringT<BaseType, StringTraits>&);
}