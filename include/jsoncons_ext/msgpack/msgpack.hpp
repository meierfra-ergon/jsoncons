// Copyright 2013 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#ifndef JSONCONS_MSGPACK_MSGPACK_HPP
#define JSONCONS_MSGPACK_MSGPACK_HPP

#include <string>
#include <sstream>
#include <vector>
#include <istream>
#include <cstdlib>
#include <memory>
#include <limits>
#include <cassert>
#include <jsoncons/json.hpp>
#include <jsoncons/config/binary_detail.hpp>
#include <jsoncons_ext/msgpack/msgpack_serializer.hpp>
#include <jsoncons_ext/msgpack/msgpack_reader.hpp>

namespace jsoncons { namespace msgpack {

// encode_msgpack

template<class Json>
void encode_msgpack(const Json& j, std::basic_ostream<typename Json::char_type>& os)
{
    typedef typename Json::char_type char_type;
    basic_msgpack_serializer<char_type> serializer(os);
    j.dump(serializer);
}

template<class Json>
void encode_msgpack(const Json& j, std::vector<uint8_t>& v)
{
    typedef typename Json::char_type char_type;
    basic_msgpack_serializer<char_type,jsoncons::detail::bytes_result> serializer(v);
    j.dump(serializer);
}

// decode_msgpack

template<class Json>
Json decode_msgpack(const std::vector<uint8_t>& v)
{
    jsoncons::json_decoder<Json> decoder;
    msgpack_reader parser(v, decoder);
    std::error_code ec;
    parser.read(ec);
    if (ec)
    {
        throw parse_error(ec,parser.line_number(),parser.column_number());
    }
    return decoder.get_result();
}
  
#if !defined(JSONCONS_NO_DEPRECATED)
template<class Json>
std::vector<uint8_t> encode_msgpack(const Json& j)
{
    std::vector<uint8_t> v;
    encode_msgpack(j, v);
    return v;
}
#endif

}}

#endif
