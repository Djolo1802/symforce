/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#include <lcm/lcm_coretypes.h>

#ifndef __codegen_cpp_test_values_vec_t_hpp__
#define __codegen_cpp_test_values_vec_t_hpp__

#include <ostream>
#include <array>
#include "lcmtypes/eigen_lcm/Vector4d.hpp"

namespace codegen_cpp_test
{

class values_vec_t
{
    public:
        double x;

        double y;

        ::eigen_lcm::Vector4d rot;

        std::array< ::eigen_lcm::Vector4d, 3 > rot_vec;

        std::array< double, 3 > scalar_vec;

        std::array< std::array< ::eigen_lcm::Vector4d, 3 >, 3 > list_of_lists;

    public:
        values_vec_t() = default;

        /**
         * Member constructor
         */
        inline values_vec_t(
            const double& x_arg,
            const double& y_arg,
            const ::eigen_lcm::Vector4d& rot_arg,
            const std::array< ::eigen_lcm::Vector4d, 3 >& rot_vec_arg,
            const std::array< double, 3 >& scalar_vec_arg,
            const std::array< std::array< ::eigen_lcm::Vector4d, 3 >, 3 >& list_of_lists_arg
        );

        /**
         * Encode a message into binary form.
         *
         * @param buf The output buffer.
         * @param offset Encoding starts at thie byte offset into @p buf.
         * @param maxlen Maximum number of bytes to write.  This should generally be
         *  equal to getEncodedSize().
         * @return The number of bytes encoded, or <0 on error.
         */
        inline __lcm_buffer_size encode(void *buf, __lcm_buffer_size offset, __lcm_buffer_size maxlen) const;

        /**
         * Check how many bytes are required to encode this message.
         */
        inline __lcm_buffer_size getEncodedSize() const;

        /**
         * Decode a message from binary form into this instance.
         *
         * @param buf The buffer containing the encoded message.
         * @param offset The byte offset into @p buf where the encoded message starts.
         * @param maxlen The maximum number of bytes to read while decoding.
         * @return The number of bytes decoded, or <0 if an error occured.
         */
        inline __lcm_buffer_size decode(const void *buf, __lcm_buffer_size offset, __lcm_buffer_size maxlen);

        /**
         * Retrieve the 64-bit fingerprint identifying the structure of the message.
         * Note that the fingerprint is the same for all instances of the same
         * message type, and is a fingerprint on the message type definition, not on
         * the message contents.
         */
        inline static int64_t getHash();

        using type_name_array_t = const char[13];

        inline static constexpr type_name_array_t* getTypeNameArrayPtr();

        /**
         * Returns "values_vec_t"
         */
        inline static constexpr const char* getTypeName();

        /**
         * Returns "codegen_cpp_test"
         */
        inline static constexpr const char * getPackageName();

        // LCM support functions. Users should not call these
        inline __lcm_buffer_size _encodeNoHash(void *buf, __lcm_buffer_size offset, __lcm_buffer_size maxlen) const;
        inline __lcm_buffer_size _getEncodedSizeNoHash() const;
        inline __lcm_buffer_size _decodeNoHash(const void *buf, __lcm_buffer_size offset, __lcm_buffer_size maxlen);
#if !defined(SKYDIO_DISABLE_LCM_NO_INLINE)
        __attribute__((noinline))
#endif
        static uint64_t _computeHash(const __lcm_hash_ptr *p)
        {
            const __lcm_hash_ptr *fp;
            for(fp = p; fp != NULL; fp = fp->parent)
                if(fp->v == values_vec_t::getHash)
                    return 0;
            const __lcm_hash_ptr cp = { p, values_vec_t::getHash };

            uint64_t hash = 0xe7b60b55c8cf5417LL +
                ::eigen_lcm::Vector4d::_computeHash(&cp) +
         ::eigen_lcm::Vector4d::_computeHash(&cp) +
         ::eigen_lcm::Vector4d::_computeHash(&cp);

            return (hash<<1) + ((hash>>63)&1);
        }

        // Comparison operators.
        inline bool operator==(const values_vec_t& other) const;
        inline bool operator!=(const values_vec_t& other) const;

        // Ability to print to standard streams as well as the fmt library.
        friend std::ostream& operator<<(std::ostream& stream, const values_vec_t& obj) {
#if defined(SKYMARSHAL_PRINTING_ENABLED)
            stream << "values_vec_t(";
            stream << "x=" << obj.x << ", ";
            stream << "y=" << obj.y << ", ";
            stream << "rot=" << obj.rot << ", ";
            stream << "rot_vec=[";
            for (size_t i = 0; i < obj.rot_vec.size(); ++i) {
                stream << obj.rot_vec[i];
                if (i + 1 < obj.rot_vec.size()) {
                    stream << ", ";
                }
            }
            stream << "]" << ", ";
            stream << "scalar_vec=[";
            for (size_t i = 0; i < obj.scalar_vec.size(); ++i) {
                stream << obj.scalar_vec[i];
                if (i + 1 < obj.scalar_vec.size()) {
                    stream << ", ";
                }
            }
            stream << "]" << ", ";
            stream << "list_of_lists=<MULTIDIMENSIONAL ARRAY std::array< std::array< ::eigen_lcm::Vector4d, 3 >, 3 >>";
            stream << ")";
#else
            stream << "<FORMATTING DISABLED>";
#endif
            return stream;
        }
};

values_vec_t::values_vec_t(
    const double& x_arg,
    const double& y_arg,
    const ::eigen_lcm::Vector4d& rot_arg,
    const std::array< ::eigen_lcm::Vector4d, 3 >& rot_vec_arg,
    const std::array< double, 3 >& scalar_vec_arg,
    const std::array< std::array< ::eigen_lcm::Vector4d, 3 >, 3 >& list_of_lists_arg
) : x(x_arg),
    y(y_arg),
    rot(rot_arg),
    rot_vec(rot_vec_arg),
    scalar_vec(scalar_vec_arg),
    list_of_lists(list_of_lists_arg) {}

__lcm_buffer_size values_vec_t::encode(void *buf, __lcm_buffer_size offset, __lcm_buffer_size maxlen) const
{
    __lcm_buffer_size pos = 0, tlen;
    int64_t hash = (int64_t)getHash();

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->_encodeNoHash(buf, offset + pos, maxlen - pos);
    if (tlen < 0) return tlen; else pos += tlen;

    return pos;
}

__lcm_buffer_size values_vec_t::decode(const void *buf, __lcm_buffer_size offset, __lcm_buffer_size maxlen)
{
    __lcm_buffer_size pos = 0, thislen;

    int64_t msg_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &msg_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (msg_hash != getHash()) return -1;

    thislen = this->_decodeNoHash(buf, offset + pos, maxlen - pos);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

__lcm_buffer_size values_vec_t::getEncodedSize() const
{
    return 8 + _getEncodedSizeNoHash();
}

int64_t values_vec_t::getHash()
{
    static int64_t hash = _computeHash(NULL);
    return hash;
}

constexpr values_vec_t::type_name_array_t* values_vec_t::getTypeNameArrayPtr() {
    return &"values_vec_t";
}

constexpr const char* values_vec_t::getTypeName()
{
    return *values_vec_t::getTypeNameArrayPtr();
}

constexpr const char * values_vec_t::getPackageName()
{
    return "codegen_cpp_test";
}

__lcm_buffer_size values_vec_t::_encodeNoHash(void *buf, __lcm_buffer_size offset, __lcm_buffer_size maxlen) const
{
    __lcm_buffer_size pos = 0, tlen;

    tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->x, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->y, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->rot._encodeNoHash(buf, offset + pos, maxlen - pos);
    if(tlen < 0) return tlen; else pos += tlen;

    for (__lcm_buffer_size a0 = 0; a0 < 3; a0++) {
        tlen = this->rot_vec[a0]._encodeNoHash(buf, offset + pos, maxlen - pos);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->scalar_vec[0], 3);
    if(tlen < 0) return tlen; else pos += tlen;

    for (__lcm_buffer_size a0 = 0; a0 < 3; a0++) {
        for (__lcm_buffer_size a1 = 0; a1 < 3; a1++) {
            tlen = this->list_of_lists[a0][a1]._encodeNoHash(buf, offset + pos, maxlen - pos);
            if(tlen < 0) return tlen; else pos += tlen;
        }
    }

    return pos;
}

__lcm_buffer_size values_vec_t::_decodeNoHash(const void *buf, __lcm_buffer_size offset, __lcm_buffer_size maxlen)
{
    __lcm_buffer_size pos = 0, tlen;

    tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->x, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->y, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->rot._decodeNoHash(buf, offset + pos, maxlen - pos);
    if(tlen < 0) return tlen; else pos += tlen;

    for (__lcm_buffer_size a0 = 0; a0 < 3; a0++) {
        tlen = this->rot_vec[a0]._decodeNoHash(buf, offset + pos, maxlen - pos);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->scalar_vec[0], 3);
    if(tlen < 0) return tlen; else pos += tlen;

    for (__lcm_buffer_size a0 = 0; a0 < 3; a0++) {
        for (__lcm_buffer_size a1 = 0; a1 < 3; a1++) {
            tlen = this->list_of_lists[a0][a1]._decodeNoHash(buf, offset + pos, maxlen - pos);
            if(tlen < 0) return tlen; else pos += tlen;
        }
    }

    return pos;
}

__lcm_buffer_size values_vec_t::_getEncodedSizeNoHash() const
{
    __lcm_buffer_size enc_size = 0;
    enc_size += __double_encoded_array_size(NULL, 1);
    enc_size += __double_encoded_array_size(NULL, 1);
    enc_size += this->rot._getEncodedSizeNoHash();
    for (__lcm_buffer_size a0 = 0; a0 < 3; a0++) {
        enc_size += this->rot_vec[a0]._getEncodedSizeNoHash();
    }
    enc_size += __double_encoded_array_size(NULL, 3);
    for (__lcm_buffer_size a0 = 0; a0 < 3; a0++) {
        for (__lcm_buffer_size a1 = 0; a1 < 3; a1++) {
            enc_size += this->list_of_lists[a0][a1]._getEncodedSizeNoHash();
        }
    }
    return enc_size;
}

bool values_vec_t::operator==(const values_vec_t& other) const {
  return (
          (x==other.x) && 
          (y==other.y) && 
          (rot==other.rot) && 
          (rot_vec==other.rot_vec) && 
          (scalar_vec==other.scalar_vec) && 
          (list_of_lists==other.list_of_lists));
}

bool values_vec_t::operator!=(const values_vec_t& other) const {
  return !(*this==other);
}

}

#endif