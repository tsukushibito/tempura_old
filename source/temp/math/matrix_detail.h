/**
 * @file matrix_detail.h
 * @brief matrix detail
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-09-06
 */
#pragma once
#ifndef GUARD_be201c12c0d94ac2a9d39acad49e25c5
#define GUARD_be201c12c0d94ac2a9d39acad49e25c5

#include "temp/math/matrix.h"

namespace temp {
namespace math {

template < typename T >
Matrix44Base< T >::Matrix44Base() {
    for (auto &&col : m_) {
        for (auto &&elem : col) {
            elem = (T)0;
        }
    }
}

template < typename T >
Matrix44Base< T >::Matrix44Base(T _11, T _21, T _31, T _41, T _12, T _22, T _32, T _42, T _13, T _23, T _33, T _43, T _14, T _24,
                                T _34, T _44) {
    T temp[] = { _11, _21, _31, _41, _12, _22, _32, _42, _13, _23, _33, _43, _14, _24, _34, _44 };
    for (Int32 col = 0; col < 4; ++col) {
        for (Int32 row = 0; row < 4; ++row) {
            m_[col][row] = temp[4 * col + row];
        }
    }
}

template < typename T >
Matrix44Base< T >::Matrix44Base(const Vector4Base< T > &col1, const Vector4Base< T > &col2, const Vector4Base< T > &col3,
                                const Vector4Base< T > &col4) {
    col_[0] = col1;
    col_[1] = col2;
    col_[2] = col3;
    col_[3] = col4;
}

template < typename T >
String Matrix44Base< T >::toString() const {
    std::stringstream ss;
    for (Int32 col = 0; col < 4; ++col) {
        if (col == 0) {
            ss << "Matrix44( ";
        } else {
            ss << "          ";
        }
        for (Int32 row = 0; row < 4; ++row) {
            ss << m_[col][row] << ", ";
        }
        if (col == 3) {
            ss << ")" << std::endl;
        } else {
            ss << std::endl;
        }
    }
    return ss.str();
}

template < typename T >
T * Matrix44Base< T >::operator[](Size index) {
    return m_[index];
}

template < typename T >
const T * Matrix44Base< T >::operator[](Size index) const {
    return m_[index];
}

template < typename T >
Bool Matrix44Base<T>::operator==(const Matrix44Base &rhs) {
    return (col_[0] == rhs.col_[0] && col_[1] == rhs.col_[1] && col_[2] == rhs.col_[2] && col_[3] == rhs.col_[3]);
}

template < typename T >
Bool Matrix44Base<T>::operator!=(const Matrix44Base &rhs) {
    return !(*this == rhs);
}

template < typename T >
Matrix44Base<T> operator*(const Matrix44Base<T> &lhs, Float32 rhs) {
    auto temp = lhs;
    for(Size i = 0; i < 4; ++i) {
        temp.col_[i] = temp.col_[i] * rhs;
    }
    return temp;
}

template < typename T >
Matrix44Base<T> operator*(Float32 &lhs, const Matrix44Base<T> &rhs) {
    return rhs * lhs;
}

template < typename T >
Matrix44Base<T> operator/(const Matrix44Base<T> &lhs, Float32 rhs) {
    return lhs * (1 / rhs);
}

template < typename T >
Vector4Base<T> operator*(const Vector4Base<T> &lhs, const Matrix44Base<T> &rhs) {
    T x = Vector4Base<T>::dot(lhs, rhs.col_[0]);
    T y = Vector4Base<T>::dot(lhs, rhs.col_[1]);
    T z = Vector4Base<T>::dot(lhs, rhs.col_[2]);
    T w = Vector4Base<T>::dot(lhs, rhs.col_[3]);
    return Vector4Base<T>(x, y, z, w);
}

template < typename T >
Matrix44Base<T> operator*(const Matrix44Base<T> &lhs, const Matrix44Base<T> &rhs) {
    Matrix44Base<T> retVal;
    for(Int32 row = 0; row < 4; ++row) {
        for(Int32 col = 0; col < 4; ++col) {
            retVal.m_[col][row] = Vector4Base<T>::dot(lhs.row(row), rhs.col_[col]);
        }
    }

    return retVal;
}

template < typename T >
Float32 Matrix44Base< T >::determinant() const {
#if 0
    Matrix44Base<T> temp = *this;

    //三角行列を作成
    for (Int32 i = 0; i < 4 - 1; ++i) {
        // avoiding divide with zero
        if(temp.col_[i][i] == 0.0f) {
            // find swap col
            Int32 swap_col = -1;
            for(Int32 j = i + 1; j < 4; ++j) {
                if(temp.col_[j][i] != 0.0f) {
                    swap_col = j;
                    break;
                }
            }
            if (swap_col == -1) {
                continue;
            }
            else {
                auto temp_col = temp.col_[i];
                temp.col_[i] = temp.col_[swap_col];
                temp.col_[swap_col] = temp_col;
            }
        }
        TEMP_ASSERT(temp.col_[i][i] != 0.0f, "");

        for(Int32 target = i + 1; target < 4; ++target) {
            auto buf = ( temp.col_[target][i] / temp.col_[i][i] ) * temp.col_[i];
            temp.col_[target] = temp.col_[target] - buf;
        }
    }

    //対角部分の積
    Float32 det = 1.0f;
    for (Int32 i = 0; i < 4; i++) {
        det *= temp[i][i];
    }
    return det;
#else
    Float32 det 
        = (m_[0][0] * m_[1][1] * m_[2][2] * m_[3][3]) + (m_[0][0] * m_[1][2] * m_[2][3] * m_[3][1]) + (m_[0][0] * m_[1][3] * m_[2][1] * m_[3][2]) 
        + (m_[0][1] * m_[1][0] * m_[2][3] * m_[3][2]) + (m_[0][1] * m_[1][2] * m_[2][1] * m_[3][3]) + (m_[0][1] * m_[1][3] * m_[2][2] * m_[3][0])
        + (m_[0][2] * m_[1][0] * m_[2][1] * m_[3][3]) + (m_[0][2] * m_[1][1] * m_[2][3] * m_[3][0]) + (m_[0][2] * m_[1][3] * m_[2][0] * m_[3][1])
        + (m_[0][3] * m_[1][0] * m_[2][2] * m_[3][1]) + (m_[0][3] * m_[1][1] * m_[2][0] * m_[3][2]) + (m_[0][3] * m_[1][2] * m_[2][1] * m_[3][0])
        - (m_[0][0] * m_[1][1] * m_[2][3] * m_[3][2]) - (m_[0][0] * m_[1][2] * m_[2][1] * m_[3][3]) - (m_[0][0] * m_[1][3] * m_[2][2] * m_[3][1])
        - (m_[0][1] * m_[1][0] * m_[2][2] * m_[3][3]) - (m_[0][1] * m_[1][2] * m_[2][3] * m_[3][0]) - (m_[0][1] * m_[1][3] * m_[2][0] * m_[3][2])
        - (m_[0][2] * m_[1][0] * m_[2][3] * m_[3][1]) - (m_[0][2] * m_[1][1] * m_[2][0] * m_[3][3]) - (m_[0][2] * m_[1][3] * m_[2][1] * m_[3][0])
        - (m_[0][3] * m_[1][0] * m_[2][1] * m_[3][2]) - (m_[0][3] * m_[1][1] * m_[2][2] * m_[3][0]) - (m_[0][3] * m_[1][2] * m_[2][0] * m_[3][1]);
    return det;
#endif
}

template < typename T >
Optional<Matrix44Base< T > > Matrix44Base< T >::inverse() const {
    auto det = determinant();
    if (det == 0) {
        return Optional<Matrix44Base<T> >();
    }

    Matrix44Base<T> temp;
    auto &&m = temp.m_;
    m[0][0] 
        = (m_[1][1] * m_[2][2] * m_[3][3]) + (m_[1][2] * m_[2][3] * m_[3][1]) + (m_[1][3] * m_[2][1] * m_[3][2]) 
        - (m_[1][1] * m_[2][3] * m_[3][2]) - (m_[1][2] * m_[2][1] * m_[3][3]) - (m_[1][3] * m_[2][2] * m_[3][1]);
    m[0][1] 
        = (m_[0][1] * m_[2][3] * m_[3][2]) + (m_[0][2] * m_[2][1] * m_[3][3]) + (m_[0][3] * m_[2][2] * m_[3][1]) 
        - (m_[0][1] * m_[2][2] * m_[3][3]) - (m_[0][2] * m_[2][3] * m_[3][1]) - (m_[0][3] * m_[2][1] * m_[3][2]);
    m[0][2] 
        = (m_[0][1] * m_[1][2] * m_[3][3]) + (m_[0][2] * m_[1][3] * m_[3][1]) + (m_[0][3] * m_[1][1] * m_[3][2]) 
        - (m_[0][1] * m_[1][3] * m_[3][2]) - (m_[0][2] * m_[1][1] * m_[3][3]) - (m_[0][3] * m_[1][2] * m_[3][1]);
    m[0][3] 
        = (m_[0][1] * m_[1][3] * m_[2][2]) + (m_[0][2] * m_[1][1] * m_[2][3]) + (m_[0][3] * m_[1][2] * m_[2][1]) 
        - (m_[0][1] * m_[1][2] * m_[2][3]) - (m_[0][2] * m_[1][3] * m_[2][1]) - (m_[0][3] * m_[1][1] * m_[2][2]);

    m[1][0] 
        = (m_[1][0] * m_[2][3] * m_[3][2]) + (m_[1][2] * m_[2][0] * m_[3][3]) + (m_[1][3] * m_[2][2] * m_[3][0]) 
        - (m_[1][0] * m_[2][2] * m_[3][3]) - (m_[1][2] * m_[2][3] * m_[3][0]) - (m_[1][3] * m_[2][0] * m_[3][2]);
    m[1][1] 
        = (m_[0][0] * m_[2][2] * m_[3][3]) + (m_[0][2] * m_[2][3] * m_[3][0]) + (m_[0][3] * m_[2][0] * m_[3][2]) 
        - (m_[0][0] * m_[2][3] * m_[3][2]) - (m_[0][2] * m_[2][0] * m_[3][3]) - (m_[0][3] * m_[2][2] * m_[3][0]);
    m[1][2] 
        = (m_[0][0] * m_[1][3] * m_[3][2]) + (m_[0][2] * m_[1][0] * m_[3][3]) + (m_[0][3] * m_[1][2] * m_[3][0]) 
        - (m_[0][0] * m_[1][2] * m_[3][3]) - (m_[0][2] * m_[1][3] * m_[3][0]) - (m_[0][3] * m_[1][0] * m_[3][2]);
    m[1][3] 
        = (m_[0][0] * m_[1][2] * m_[2][3]) + (m_[0][2] * m_[1][3] * m_[2][0]) + (m_[0][3] * m_[1][0] * m_[2][2]) 
        - (m_[0][0] * m_[1][3] * m_[2][2]) - (m_[0][2] * m_[1][0] * m_[2][3]) - (m_[0][3] * m_[1][2] * m_[2][0]);

    m[2][0] 
        = (m_[1][0] * m_[2][1] * m_[3][3]) + (m_[1][1] * m_[2][3] * m_[3][0]) + (m_[1][3] * m_[2][0] * m_[3][1]) 
        - (m_[1][0] * m_[2][3] * m_[3][1]) - (m_[1][1] * m_[2][0] * m_[3][3]) - (m_[1][3] * m_[2][1] * m_[3][0]);
    m[2][1] 
        = (m_[0][0] * m_[2][3] * m_[3][1]) + (m_[0][1] * m_[2][0] * m_[3][3]) + (m_[0][3] * m_[2][1] * m_[3][0]) 
        - (m_[0][0] * m_[2][1] * m_[3][3]) - (m_[0][1] * m_[2][3] * m_[3][0]) - (m_[0][3] * m_[2][0] * m_[3][1]);
    m[2][2] 
        = (m_[0][0] * m_[1][1] * m_[3][3]) + (m_[0][1] * m_[1][3] * m_[3][0]) + (m_[0][3] * m_[1][0] * m_[3][1]) 
        - (m_[0][0] * m_[1][3] * m_[3][1]) - (m_[0][1] * m_[1][0] * m_[3][3]) - (m_[0][3] * m_[1][1] * m_[3][0]);
    m[2][3] 
        = (m_[0][0] * m_[1][3] * m_[2][1]) + (m_[0][1] * m_[1][0] * m_[2][3]) + (m_[0][3] * m_[1][1] * m_[2][0]) 
        - (m_[0][0] * m_[1][1] * m_[2][3]) - (m_[0][1] * m_[1][3] * m_[2][0]) - (m_[0][3] * m_[1][0] * m_[2][1]);

    m[3][0] 
        = (m_[1][0] * m_[2][2] * m_[3][1]) + (m_[1][1] * m_[2][0] * m_[3][2]) + (m_[1][2] * m_[2][1] * m_[3][0]) 
        - (m_[1][0] * m_[2][1] * m_[3][2]) - (m_[1][1] * m_[2][2] * m_[3][0]) - (m_[1][2] * m_[2][0] * m_[3][1]);
    m[3][1] 
        = (m_[0][0] * m_[2][1] * m_[3][2]) + (m_[0][1] * m_[2][2] * m_[3][0]) + (m_[0][2] * m_[2][0] * m_[3][1]) 
        - (m_[0][0] * m_[2][2] * m_[3][1]) - (m_[0][1] * m_[2][0] * m_[3][2]) - (m_[0][2] * m_[2][1] * m_[3][0]);
    m[3][2] 
        = (m_[0][0] * m_[1][2] * m_[3][1]) + (m_[0][1] * m_[1][0] * m_[3][2]) + (m_[0][2] * m_[1][1] * m_[3][0]) 
        - (m_[0][0] * m_[1][1] * m_[3][2]) - (m_[0][1] * m_[1][2] * m_[3][0]) - (m_[0][2] * m_[1][0] * m_[3][1]);
    m[3][3] 
        = (m_[0][0] * m_[1][1] * m_[2][2]) + (m_[0][1] * m_[1][2] * m_[2][0]) + (m_[0][2] * m_[1][0] * m_[2][1]) 
        - (m_[0][0] * m_[1][2] * m_[2][1]) - (m_[0][1] * m_[1][0] * m_[2][2]) - (m_[0][2] * m_[1][1] * m_[2][0]);
    return Optional<Matrix44Base<T>>(temp / det);
}

template < typename T >
Matrix44Base< T > Matrix44Base< T >::transpose() const {}

template < typename T >
Vector4Base< T > Matrix44Base< T >::row(Size index) const {
    TEMP_ASSERT(index >=0 && index < 4, "invalid index!");
    return Vector4Base<T>(col_[0][index], col_[1][index], col_[2][index], col_[3][index]);
}

template < typename T >
const Matrix44Base<T> Matrix44Base<T>::kZero;
template < typename T >
const Matrix44Base<T> Matrix44Base<T>::kIdentity 
    = Matrix44Base<T>(
            1.0f, 0.0f, 0.0f, 0.0f, 
            0.0f, 1.0f, 0.0f, 0.0f, 
            0.0f, 0.0f, 1.0f, 0.0f, 
            0.0f, 0.0f, 0.0f, 1.0f);

} // namespace math
} // namespace temp
#endif // GUARD_be201c12c0d94ac2a9d39acad49e25c5
