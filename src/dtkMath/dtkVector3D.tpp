/* dtkVector3D.tpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2008 - Thibaud Kloczko, Inria.
 * Created: Mon Jul 12 16:15:10 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jul 12 16:15:47 2010 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVECTOR3D_TPP
#define DTKVECTOR3D_TPP

#include "dtkVector.h"
#include "dtkMatrixSquared.h"

// /////////////////////////////////////////////////////////////////
// Implementation of the template class dtkVector3D's methods
// /////////////////////////////////////////////////////////////////

template <class T> inline dtkVector3D<T>::dtkVector3D(const dtkMatrix<T>& mat,
                                                      unsigned irowStart,
                                                      unsigned icolStart) : dtkVector<T>(mat, irowStart, icolStart, irowStart + 2)
{
}

template <class T> inline dtkVector3D<T>::dtkVector3D(const T& elem1, 
                                                      const T& elem2,
                                                      const T& elem3) : dtkVector<T>(3U) 
{
    (*this)[0] = elem1;
    (*this)[1] = elem2;
    (*this)[2] = elem3;
}

template <class T> inline void dtkVector3D<T>::mapInto(const dtkMatrix<T>& mat,
                                                       unsigned irowStart,
                                                       unsigned icolStart)
{
    dtkVector<T>::mapInto(mat, irowStart, icolStart, irowStart + 2);
}

template <class T> inline void dtkVector3D<T>::mapInto(const dtkVector<T>& vec,
                                                       unsigned irowStart)
{
    dtkVector<T>::mapInto(vec, irowStart, irowStart + 2);
}

template <class T> inline dtkVector3D<T> dtkVector3D<T>::operator /(const T& value) const
{
    T tTmp = dtkUnity<T>();
    tTmp /= value;
    return (*this)*tTmp;
}

template <class T> inline dtkVector3D<T>& dtkVector3D<T>::operator =(const dtkVector3D<T>& vec3D)
{
    return static_cast<dtkVector3D& >(dtkMatrix<T>::operator=(vec3D));
}

template <class T> inline dtkVector3D<T>& dtkVector3D<T>::operator +=(const dtkVector3D<T>& vec3D)
{
    return static_cast<dtkVector3D& >(dtkMatrix<T>::operator+=(vec3D));
}

template <class T> inline dtkVector3D<T>& dtkVector3D<T>::operator -=(const dtkVector3D<T>& vec3D)
{
    return static_cast<dtkVector3D& >(dtkMatrix<T>::operator-=(vec3D));
}

template <class T> inline dtkVector3D<T>& dtkVector3D<T>::operator *=(const T& value)
{
    return static_cast<dtkVector3D& >(dtkMatrix<T>::operator*=(value));
}

template <class T> inline dtkVector3D<T>& dtkVector3D<T>::operator /=(const T& value)
{
    T tTmp = dtkUnity<T>();
    tTmp /= value;
    return (*this) *= tTmp;
}

template <class T> inline dtkVector3D<T>& dtkVector3D<T>::operator %=(const dtkVector3D<T>& vec)
{
    return (*this) = (*this)%vec;
}

template <class T> dtkVector3D<T> dtkVector3D<T>::operator +(const dtkVector3D<T>& vec3D) const
{
    return dtkVector3D<T>(*this) += vec3D;
}
 
template <class T> dtkVector3D<T> dtkVector3D<T>::operator -(const dtkVector3D<T>& vec3D) const
{
    return dtkVector3D<T>(*this) -= vec3D;
}

template <class T> dtkVector3D<T> dtkVector3D<T>::operator -(void) const
{
    T tTmp = dtkZero<T>();
    tTmp -= dtkUnity<T>();
    return (*this)*tTmp;
}

template <class T> dtkVector3D<T> dtkVector3D<T>::operator *(const T& value) const
{
    return dtkVector3D<T>(*this) *= value;
}

template <class T> T dtkVector3D<T>::operator *(const dtkVector3D<T>& vec) const
{
    return dtkVector<T>::operator*(vec);
}

template <class T> void dtkVector3D<T>:: storeOuterProduct(const dtkVector3D<T>& vec3DLeft,
                                                           const dtkVector3D<T>& vec3DRight)
{
    T vec3DLeft0 = vec3DLeft[0];
    T vec3DLeft1 = vec3DLeft[1];
    T vec3DLeft2 = vec3DLeft[2];

    T vec3DRight0 = vec3DRight[0];
    T vec3DRight1 = vec3DRight[1];
    T vec3DRight2 = vec3DRight[2];

    (*this)[0] = vec3DLeft1*vec3DRight2 - vec3DLeft2*vec3DRight1;
    (*this)[1] = vec3DLeft2*vec3DRight0 - vec3DLeft0*vec3DRight2;
    (*this)[2] = vec3DLeft0*vec3DRight1 - vec3DLeft1*vec3DRight0;
}

template <class T> dtkVector3D<T> dtkVector3D<T>::operator %(const dtkVector3D<T>& vec3D) const
{
    dtkVector3D<T> vec3DResult;
    vec3DResult.storeOuterProduct(*this, vec3D);
    return vec3DResult;
}

template <class T> inline dtkVector3D<T> operator *(const T& value,
                                                    const dtkVector3D<T>& vec3D)
{
    return vec3D*value;
}

template <class T> dtkVector3D<T> operator *(const dtkMatrixSquared<T>& mat,
                                             const dtkVector3D<T>& vec3D)
{
    dtkVector3D<T> vec3DResult;
    vec3DResult.storeProduct(mat, vec3D);
    return vec3DResult;
}

template <class T> inline dtkVector3D<T> dtkDirection(const dtkVector3D<T>& vec3D)
{
    return vec3D.unit();
}

#endif
