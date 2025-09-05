export module vx.types;

import std;
import glm;

export namespace vx
{
    using void_t    =          void     ;
    using bool_t    =          bool     ;
    using char_t    =          char     ;
    using schar_t   =   signed char     ;
    using uchar_t   = unsigned char     ;
    using int8_t    =   signed char     ;
    using uint8_t   = unsigned char     ;
    using int16_t   =   signed short    ;
    using uint16_t  = unsigned short    ;
    using int32_t   =   signed int      ;
    using uint32_t  = unsigned int      ;
    using int64_t   =   signed long long;
    using uint64_t  = unsigned long long;
    using float32_t =          float    ;
    using float64_t =          double   ;

    using bool32_t  = vx::uint32_t;
    using byte_t    = vx::uint8_t;
    using size_t    = vx::uint64_t;

    enum : vx::bool_t
    {
        false_ = false, 
        true_  = true , 
    };



    template<typename T> using pointer_t   = T*;
    template<typename T> using reference_t = T&;
                         using next_t      = vx::pointer_t<const vx::void_t>;



    template<typename T, vx::uint32_t N>
    using vector_t = glm::vec<N, T, glm::packed_highp>;

    using vector1u = vx::vector_t<vx::uint32_t , 1u>;
    using vector2u = vx::vector_t<vx::uint32_t , 2u>;
    using vector3u = vx::vector_t<vx::uint32_t , 3u>;
    using vector4u = vx::vector_t<vx::uint32_t , 4u>;

    using vector1f = vx::vector_t<vx::float32_t, 1u>;
    using vector2f = vx::vector_t<vx::float32_t, 2u>;
    using vector3f = vx::vector_t<vx::float32_t, 3u>;
    using vector4f = vx::vector_t<vx::float32_t, 4u>;
}
