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
}

template < typename T >
Matrix44Base<T>::Matrix44Base(T element[16]) {
    for (Size i = 0; i < 16; ++i) {
        cols_[i / 4][i % 4] = element[i];
    }
}

template < typename T >
Matrix44Base<T>::Matrix44Base(RowOrder,
    const Vec4 &row0,
    const Vec4 &row1,
    const Vec4 &row2,
    const Vec4 &row3) {
    const Vec4 *rows[4] = {&row0, &row1, &row2, &row3};
    for (Size row = 0; row < 4; ++row) {
        for (Size col = 0; col < 4; ++col) {
            cols_[col][row] = (*rows[row])[col];
        }
    }
}

template < typename T >
Matrix44Base<T>::Matrix44Base(ColOrder,
    const Vec4 &col0,
    const Vec4 &col1,
    const Vec4 &col2,
    const Vec4 &col3) {
    cols_[0] = col0;
    cols_[1] = col1;
    cols_[2] = col2;
    cols_[3] = col3;
}

template < typename T >
String Matrix44Base< T >::toString() const {
    std::stringstream ss;
    ss << std::endl;
    for (Int32 row = 0; row < 4; ++row) {
        if (row == 0) {
            ss << "Matrix44( ";
        } else {
            ss << "          ";
        }
        for (Int32 col = 0; col < 4; ++col) {
            ss << cols_[col][row] << ", ";
        }
        if (row == 3) {
            ss << ")" << std::endl;
        } else {
            ss << std::endl;
        }
    }
    return ss.str();
}

template < typename T >
Vector4Base<T> * Matrix44Base< T >::operator[](Size index) {
    return cols_[index];
}

template < typename T >
const Vector4Base<T> * Matrix44Base< T >::operator[](Size index) const {
    return cols_[index];
}

template < typename T >
T Matrix44Base<T>::operator()(Size row, Size col) const {
    return cols_[col][row];
}

template < typename T >
Bool Matrix44Base<T>::operator==(const Matrix44Base &rhs) {
    return (cols_[0] == rhs.cols_[0] && cols_[1] == rhs.cols_[1] && cols_[2] == rhs.cols_[2] && cols_[3] == rhs.cols_[3]);
}

template < typename T >
Bool Matrix44Base<T>::operator!=(const Matrix44Base &rhs) {
    return !(*this == rhs);
}

template < typename T >
Matrix44Base<T> operator*(const Matrix44Base<T> &lhs, Float32 rhs) {
    auto temp = lhs;
    for(Size i = 0; i < 4; ++i) {
        temp.cols_[i] = temp.cols_[i] * rhs;
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
    T x = Vector4Base<T>::dot(lhs, rhs.cols_[0]);
    T y = Vector4Base<T>::dot(lhs, rhs.cols_[1]);
    T z = Vector4Base<T>::dot(lhs, rhs.cols_[2]);
    T w = Vector4Base<T>::dot(lhs, rhs.cols_[3]);
    return Vector4Base<T>(x, y, z, w);
}

template < typename T >
Matrix44Base<T> operator*(const Matrix44Base<T> &lhs, const Matrix44Base<T> &rhs) {
    Matrix44Base<T> retVal;
    for(Int32 row = 0; row < 4; ++row) {
        for(Int32 col = 0; col < 4; ++col) {
            retVal.cols_[col][row] = Vector4Base<T>::dot(lhs.row(row), rhs.cols_[col]);
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
	const auto &m = cols_;
    Float32 det 
        = (m[0][0] * m[1][1] * m[2][2] * m[3][3]) + (m[0][0] * m[1][2] * m[2][3] * m[3][1]) + (m[0][0] * m[1][3] * m[2][1] * m[3][2]) 
        + (m[0][1] * m[1][0] * m[2][3] * m[3][2]) + (m[0][1] * m[1][2] * m[2][1] * m[3][3]) + (m[0][1] * m[1][3] * m[2][2] * m[3][0])
        + (m[0][2] * m[1][0] * m[2][1] * m[3][3]) + (m[0][2] * m[1][1] * m[2][3] * m[3][0]) + (m[0][2] * m[1][3] * m[2][0] * m[3][1])
        + (m[0][3] * m[1][0] * m[2][2] * m[3][1]) + (m[0][3] * m[1][1] * m[2][0] * m[3][2]) + (m[0][3] * m[1][2] * m[2][1] * m[3][0])
        - (m[0][0] * m[1][1] * m[2][3] * m[3][2]) - (m[0][0] * m[1][2] * m[2][1] * m[3][3]) - (m[0][0] * m[1][3] * m[2][2] * m[3][1])
        - (m[0][1] * m[1][0] * m[2][2] * m[3][3]) - (m[0][1] * m[1][2] * m[2][3] * m[3][0]) - (m[0][1] * m[1][3] * m[2][0] * m[3][2])
        - (m[0][2] * m[1][0] * m[2][3] * m[3][1]) - (m[0][2] * m[1][1] * m[2][0] * m[3][3]) - (m[0][2] * m[1][3] * m[2][1] * m[3][0])
        - (m[0][3] * m[1][0] * m[2][1] * m[3][2]) - (m[0][3] * m[1][1] * m[2][2] * m[3][0]) - (m[0][3] * m[1][2] * m[2][0] * m[3][1]);
    return det;
#endif
}

template < typename T >
Optional<Matrix44Base< T > > Matrix44Base< T >::inverse() const {
    auto det = determinant();
    if (det == 0) {
        return Optional<Matrix44Base<T> >();
    }

	const auto &m = cols_;
    Matrix44Base<T> temp;
    auto &&tm = temp.cols_;
    tm[0][0] 
        = (m[1][1] * m[2][2] * m[3][3]) + (m[1][2] * m[2][3] * m[3][1]) + (m[1][3] * m[2][1] * m[3][2]) 
        - (m[1][1] * m[2][3] * m[3][2]) - (m[1][2] * m[2][1] * m[3][3]) - (m[1][3] * m[2][2] * m[3][1]);
    tm[0][1] 
        = (m[0][1] * m[2][3] * m[3][2]) + (m[0][2] * m[2][1] * m[3][3]) + (m[0][3] * m[2][2] * m[3][1]) 
        - (m[0][1] * m[2][2] * m[3][3]) - (m[0][2] * m[2][3] * m[3][1]) - (m[0][3] * m[2][1] * m[3][2]);
    tm[0][2] 
        = (m[0][1] * m[1][2] * m[3][3]) + (m[0][2] * m[1][3] * m[3][1]) + (m[0][3] * m[1][1] * m[3][2]) 
        - (m[0][1] * m[1][3] * m[3][2]) - (m[0][2] * m[1][1] * m[3][3]) - (m[0][3] * m[1][2] * m[3][1]);
    tm[0][3] 
        = (m[0][1] * m[1][3] * m[2][2]) + (m[0][2] * m[1][1] * m[2][3]) + (m[0][3] * m[1][2] * m[2][1]) 
        - (m[0][1] * m[1][2] * m[2][3]) - (m[0][2] * m[1][3] * m[2][1]) - (m[0][3] * m[1][1] * m[2][2]);

    tm[1][0] 
        = (m[1][0] * m[2][3] * m[3][2]) + (m[1][2] * m[2][0] * m[3][3]) + (m[1][3] * m[2][2] * m[3][0]) 
        - (m[1][0] * m[2][2] * m[3][3]) - (m[1][2] * m[2][3] * m[3][0]) - (m[1][3] * m[2][0] * m[3][2]);
    tm[1][1] 
        = (m[0][0] * m[2][2] * m[3][3]) + (m[0][2] * m[2][3] * m[3][0]) + (m[0][3] * m[2][0] * m[3][2]) 
        - (m[0][0] * m[2][3] * m[3][2]) - (m[0][2] * m[2][0] * m[3][3]) - (m[0][3] * m[2][2] * m[3][0]);
    tm[1][2] 
        = (m[0][0] * m[1][3] * m[3][2]) + (m[0][2] * m[1][0] * m[3][3]) + (m[0][3] * m[1][2] * m[3][0]) 
        - (m[0][0] * m[1][2] * m[3][3]) - (m[0][2] * m[1][3] * m[3][0]) - (m[0][3] * m[1][0] * m[3][2]);
    tm[1][3] 
        = (m[0][0] * m[1][2] * m[2][3]) + (m[0][2] * m[1][3] * m[2][0]) + (m[0][3] * m[1][0] * m[2][2]) 
        - (m[0][0] * m[1][3] * m[2][2]) - (m[0][2] * m[1][0] * m[2][3]) - (m[0][3] * m[1][2] * m[2][0]);

    tm[2][0] 
        = (m[1][0] * m[2][1] * m[3][3]) + (m[1][1] * m[2][3] * m[3][0]) + (m[1][3] * m[2][0] * m[3][1]) 
        - (m[1][0] * m[2][3] * m[3][1]) - (m[1][1] * m[2][0] * m[3][3]) - (m[1][3] * m[2][1] * m[3][0]);
    tm[2][1] 
        = (m[0][0] * m[2][3] * m[3][1]) + (m[0][1] * m[2][0] * m[3][3]) + (m[0][3] * m[2][1] * m[3][0]) 
        - (m[0][0] * m[2][1] * m[3][3]) - (m[0][1] * m[2][3] * m[3][0]) - (m[0][3] * m[2][0] * m[3][1]);
    tm[2][2] 
        = (m[0][0] * m[1][1] * m[3][3]) + (m[0][1] * m[1][3] * m[3][0]) + (m[0][3] * m[1][0] * m[3][1]) 
        - (m[0][0] * m[1][3] * m[3][1]) - (m[0][1] * m[1][0] * m[3][3]) - (m[0][3] * m[1][1] * m[3][0]);
    tm[2][3] 
        = (m[0][0] * m[1][3] * m[2][1]) + (m[0][1] * m[1][0] * m[2][3]) + (m[0][3] * m[1][1] * m[2][0]) 
        - (m[0][0] * m[1][1] * m[2][3]) - (m[0][1] * m[1][3] * m[2][0]) - (m[0][3] * m[1][0] * m[2][1]);

    tm[3][0] 
        = (m[1][0] * m[2][2] * m[3][1]) + (m[1][1] * m[2][0] * m[3][2]) + (m[1][2] * m[2][1] * m[3][0]) 
        - (m[1][0] * m[2][1] * m[3][2]) - (m[1][1] * m[2][2] * m[3][0]) - (m[1][2] * m[2][0] * m[3][1]);
    tm[3][1] 
        = (m[0][0] * m[2][1] * m[3][2]) + (m[0][1] * m[2][2] * m[3][0]) + (m[0][2] * m[2][0] * m[3][1]) 
        - (m[0][0] * m[2][2] * m[3][1]) - (m[0][1] * m[2][0] * m[3][2]) - (m[0][2] * m[2][1] * m[3][0]);
    tm[3][2] 
        = (m[0][0] * m[1][2] * m[3][1]) + (m[0][1] * m[1][0] * m[3][2]) + (m[0][2] * m[1][1] * m[3][0]) 
        - (m[0][0] * m[1][1] * m[3][2]) - (m[0][1] * m[1][2] * m[3][0]) - (m[0][2] * m[1][0] * m[3][1]);
    tm[3][3] 
        = (m[0][0] * m[1][1] * m[2][2]) + (m[0][1] * m[1][2] * m[2][0]) + (m[0][2] * m[1][0] * m[2][1]) 
        - (m[0][0] * m[1][2] * m[2][1]) - (m[0][1] * m[1][0] * m[2][2]) - (m[0][2] * m[1][1] * m[2][0]);
    return Optional<Matrix44Base<T>>(temp / det);
}

template < typename T >
Matrix44Base< T > Matrix44Base< T >::transpose() const {
    return Matrix44Base<T>(ColOrder(), row(0), row(1), row(2), row(3));
}

template < typename T >
Vector4Base< T > Matrix44Base< T >::row(Size index) const {
    TEMP_ASSERT(index >=0 && index < 4, "invalid index!");
    return Vector4Base<T>(cols_[0][index], cols_[1][index], cols_[2][index], cols_[3][index]);
}

template < typename T >
const Matrix44Base<T> Matrix44Base<T>::kZero;
template < typename T >
const Matrix44Base<T> Matrix44Base<T>::kIdentity 
    = Matrix44Base<T>(ColOrder(),
            Vec4(1.0f, 0.0f, 0.0f, 0.0f), 
            Vec4(0.0f, 1.0f, 0.0f, 0.0f), 
            Vec4(0.0f, 0.0f, 1.0f, 0.0f), 
            Vec4(0.0f, 0.0f, 0.0f, 1.0f));

} // namespace math
} // namespace temp
#endif // GUARD_be201c12c0d94ac2a9d39acad49e25c5
