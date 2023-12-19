﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)  throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)  throw out_of_range("Vector too large");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
     if (s > MAX_VECTOR_SIZE)  throw out_of_range("Vector too large");
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      if (this == &v) return;
      T* tmp = new T[v.sz];
      pMem = tmp;
      sz = v.sz;
      std::copy(v.pMem, v.pMem+ sz, pMem);

  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      pMem == nullptr;
      swap(*this,v);
  }
  ~TDynamicVector()
  {
      //delete[] pMem;
      pMem = nullptr;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      
      if (this == &v) return *this;
      if (sz != v.sz) {
          T* tmp = new T[v.sz];
          delete[] pMem;
          sz = v.sz;
          pMem = tmp;
      }
      for (size_t i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }
      //std::copy(v.pMem, v.pMem + sz, pMem);
      return *this;
      
       
      /*if (this == &v) return *this;
      TDynamicVector tmp(v);
      swap(*this, tmp);
      return *this;
      */

  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      TDynamicVector tmp(v);
      swap(*this, tmp);
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind >= sz) throw out_of_range("index>size");
      if (ind < 0) throw out_of_range("index<0");
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind >= sz) throw out_of_range("index>size");
      if (ind < 0) throw out_of_range("index<0");
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz) throw out_of_range("index>size");
      if (ind < 0) throw out_of_range("index<0");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz) throw out_of_range("index>size");
      if (ind < 0) throw out_of_range("index<0");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this == &v) return true;
      if (sz != v.sz) return false;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) return false;
      }
      return true;
  }

  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (this == &v) return false;
      if (sz != v.sz) return true;

      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) return true;
      }
      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] + val;
      }
      return tmp;
  }
  TDynamicVector operator-(T val)
  {

      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] - val;
      }
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] *val;
      }
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw "Different sizes";
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] + v.pMem[i];
      }
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw "Different sizes";
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] - v.pMem[i];
      }
      return tmp;
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
      if (sz != v.sz) throw "Different sizes";
      T tmp = pMem[0] * v.pMem[0];
      for (size_t i = 1; i < sz; i++) {
          tmp = tmp + pMem[i] * v.pMem[i];
      }
      return tmp;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  using TDynamicVector<TDynamicVector<T>>::size;
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (s > MAX_MATRIX_SIZE)  throw out_of_range("Matrix too large");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  

  // сравнение
  
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return false;
      for (size_t i = 0; i < m.sz; i++) {
      if (pMem[i] != m.pMem[i]) return false;
      }
      //---------------------------------------------------------!!!!!!!!!!!!!!!
      return true;
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return true;
      for (size_t i = 0; i < m.sz; i++) {
          if (pMem[i] != m.pMem[i]) return true;
      }
      //---------------------------------------------------------!!!!!!!!!!!!!!!
      return false;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      for (size_t j = 0; j < sz; j++)
          for (size_t i = 0; i < sz; i++) {
              pMem[i][j] = pMem[i][j]*val;
          }
      //---------------------------------------------------------!!!!!!!!!!!!!!!
      return this;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.sz) throw "Different sizes";
      TDynamicVector<T> tmp(v.sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = tmp.pMem[i] * v.pMem[i];
      }

      return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw "Different sizes";
      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] + m.pMem[i];
      }
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw "Different sizes";
      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] - m.pMem[i];
      }
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw "Different sizes";
      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              for (size_t k = 0; k < sz; k++) {
                  tmp.pMem[i][j] +=pMem[i][k] * m.pMem[k][j];
              }
      return tmp;
  }
  TDynamicMatrix operator/(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw "Different sizes";
      TDynamicMatrix<T> tmp(m.sz);
      for (size_t j = 0; j < m.sz; j++)
          for (size_t i = 0; i < m.sz; i++) {
              tmp.pMem[j][i] = m.pMem[i][j];
          }
      TDynamicMatrix tmp2(sz);
      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              for (size_t k = 0; k < sz; k++) {
                  tmp2.pMem[i][j] += pMem[i][k] * tmp.pMem[k][j];
              }
      return tmp2;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      //---------------------------------------------------------!!!!!!!!!!!!!!!
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      //---------------------------------------------------------!!!!!!!!!!!!!!!
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < v.sz; j++)
              ostr << v.pMem[i][j]<<" ";
          ostr << endl;
      }
      return ostr;
  }
};

#endif
