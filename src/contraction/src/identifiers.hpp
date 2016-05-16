#pragma once
#include <set>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>

template <typename T>
class Identifiers {
 public:
    const std::set<T>& ids() const;
    //! \brief Returns a boolean value true or false, to indicate whether the set is empty
    inline bool empty() const { return m_ids.empty(); }
    bool has(const T other) const;
    bool isDisjoint(const T other) const;
    bool isDisjoint(const Identifiers<T> &other) const;
    void insert(const Identifiers<T> &other);
    void insert(const T &other);
    bool operator ==(const Identifiers<T> &other) const;
    Identifiers<T> operator +(const T &other) const;
    Identifiers<T> operator *(const T &other) const;
    Identifiers<T> operator -(const T &other) const;
    Identifiers<T> operator +(const Identifiers<T> &other) const;
    Identifiers<T> operator *(const Identifiers<T> &other) const;
    Identifiers<T> operator -(const Identifiers<T> &other) const;
    Identifiers<T>& operator +=(const T &other);
    Identifiers<T>& operator *=(const T &other);
    Identifiers<T>& operator -=(const T &other);
    Identifiers<T>& operator +=(const Identifiers<T> &other);
    Identifiers<T>& operator *=(const Identifiers<T> &other);
    Identifiers<T>& operator -=(const Identifiers<T> &other);
    template<T>
    friend std::ostringstream& operator << (std::ostringstream& os, const Identifiers<T>& identifiers);
 private:
    std::set<T> m_ids;
};

//! \brief Returns a set of identifiers of type *set<T>*
template <typename T>
const std::set<T>& Identifiers<T>::ids() const {
    return m_ids;
}

//! \brief Returns a boolean value true or false
/*!
  @param [IN] *other* is an identifier of type *T*
  Returns:
  true: If *other* is in this set
  false: Otherwise
  */
template <typename T>
bool Identifiers<T>::has(const T other) const {
    return (m_ids.find(other) != m_ids.end());
}

//! \brief Returns a boolean value true or false
/*!
  @param [IN] *other* is an identifier of type *T*
  Returns:
  true: If *other* is not in this set
  false: Otherwise
  */
template <typename T>
bool Identifiers<T>::isDisjoint(const T other) const {
    return (m_ids.find(other) == m_ids.end());
}

//! \brief Returns a boolean value true or false
/*!
  @param [IN] *other* is set of identifiers of type *Identifiers<T>*
  Returns:
  true: If *other* and this set are disjoint
  false: otherwise
  */
template <typename T>
bool Identifiers<T>::isDisjoint(const Identifiers<T> &other) const {
    for (auto identifier : other.ids()) {
        if (!(m_ids.find(identifier) == m_ids.end())) {
            return false;
        }
    }
    return true;
}

//! \brief Inserts a set of identifiers of type *Identifiers<T>* to this set
/*!
  @param [IN] *other* is a set of identifiers
  */
template <typename T>
void Identifiers<T>::insert(const Identifiers<T> &other) {
    #if 0
    std::cout << "Before Insertion" << std::endl;
    for (auto identifier : m_ids) {
        std::cout << identifier << ", ";
    }
    std::cout << std::endl;
    #endif
    m_ids.insert(other.ids().begin(), other.ids().end());
     #if 0
    std::cout << "After Insertion" << std::endl;
    for (auto identifier : m_ids) {
        std::cout << identifier << ", ";
    }
    std::cout << std::endl;
    #endif
}

//! \brief Inserts an identifier of type *T* to this set
/*!
  @param [IN] *other* is an identifier of type *T*
  */
template <typename T>
void Identifiers<T>::insert(const T &other) {
    #if 0
    std::cout << "Before Insertion" << std::endl;
    for (auto identifier : m_ids) {
        std::cout << identifier << ", ";
    }
    std::cout << std::endl;
    #endif
    m_ids.insert(other);
    #if 0
    std::cout << "After Insertion" << std::endl;
    for (auto identifier : m_ids) {
        std::cout << identifier << ", ";
    }
    std::cout << std::endl;
    #endif
}

//! \brief Returns a boolean value 
/*!
  @param [IN] *other* is a set of identifiers of type *Identifiers<T>*
  Returns:
  true: If *other* and this set are equivalent
  false: Otherwise
  */
template <typename T>
bool Identifiers<T>::operator ==(const Identifiers<T> &other) const {
    return std::equal(m_ids.begin(),m_ids.end(),other.ids().begin());
}


//! \brief Returns a set of identifiers of type *Identifiers<T>* 
/*!
  @param [IN] *other* is an identifier of type *T*
  Returns the set union of *other* with this set
  */
template <typename T>
Identifiers<T> Identifiers<T>::operator +(const T &other) const {
    Identifiers<T> union_ids;
    union_ids.insert(*this);
    union_ids.insert(other);
    return union_ids;
}

//! \brief Returns a set of identifiers of type *Identifiers<T>* 
/*!
  @param [IN] *other* is an identifier of type *T*
  Returns the set intersection of *other* with this set
  */
template <typename T>
Identifiers<T> Identifiers<T>::operator *(const T &other) const {
    Identifiers<T> intersect_ids;
    intersect_ids.insert(*this);
    intersect_ids *= other;
    return intersect_ids;
}

//! \brief Returns a set of identifiers of type *Identifiers<T>* 
/*!
  @param [IN] *other* is an identifier of type *T*
  Returns the set difference between this set and *other*
  */
template <typename T>
Identifiers<T> Identifiers<T>::operator -(const T &other) const {
    Identifiers<T> diff_ids;
    diff_ids.insert(*this);
    diff_ids -= other;
    return diff_ids;
}

//! \brief Returns a set of identifiers of type *Identifiers<T>* 
/*!
  @param [IN] *other* is a set of identifiers of type *Identifiers<T>*
  Returns the set union of *other* with this set
  */
template <typename T>
Identifiers<T> Identifiers<T>::operator +(const Identifiers<T> &other) const {
    Identifiers<T> union_ids;
    union_ids.insert(*this);
    union_ids.insert(other);
    return union_ids;
}

//! \brief Returns a set of identifiers of type *Identifiers<T>* 
/*!
  @param [IN] *other* is a set of identifiers of type *Identifiers<T>*
  Returns the set intersection of *other* with this set
  */
template <typename T>
Identifiers<T> Identifiers<T>::operator *(const Identifiers<T> &other) const {
    Identifiers<T> intersect_ids;
    intersect_ids.insert(*this);
    intersect_ids *= other;
    return intersect_ids;
}

//! \brief Returns a set of identifiers of type *Identifiers<T>* 
/*!
  @param [IN] *other* is a set of identifiers of type *Identifiers<T>*
  Returns the set difference between this set and *other*
  */
template <typename T>
Identifiers<T> Identifiers<T>::operator -(const Identifiers<T> &other) const {
    Identifiers<T> diff_ids;
    diff_ids.insert(*this);
    diff_ids -= other;
    return diff_ids;
}


//! \brief Returns a set of identifiers of type *Identifiers<T>&* 
/*!
  @param [IN] *other* is an identifiers of type *T*
  Replaces this set with the set union of *other* with this set
  */
template <typename T>
Identifiers<T>& Identifiers<T>::operator +=(const T &other) {
    this->insert(other);
    return *this;
}

//! \brief Returns a set of identifiers of type *Identifiers<T>&* 
/*!
  @param [IN] *other* is an identifiers of type *T*
  Replaces this set with the set intersection of *other* with this set
  */
template <typename T>
Identifiers<T>& Identifiers<T>::operator *=(const T &other) {
    if (m_ids.find(other) != m_ids.end()) {
        m_ids.clear();
        m_ids.insert(other);
    } else {
        m_ids.clear();
    }
    return *this;
}

//! \brief Returns a set of identifiers of type *Identifiers<T>&* 
/*!
  @param [IN] *other* is a set of identifiers of type *T*
  Replaces this set with the set difference between this set and *other*
  */
template <typename T>
Identifiers<T>& Identifiers<T>::operator -=(const T &other) {
    if (m_ids.find(other) != m_ids.end()) {
        m_ids.erase(m_ids.find(other));
    }
    return *this;
}


//! \brief Returns a set of identifiers of type *Identifiers<T>&* 
/*!
  @param [IN] *other* is a set of identifiers of type *Identifiers<T>*
  Replaces this set with the set union of *other* with this set
  */
template <typename T>
Identifiers<T>& Identifiers<T>::operator +=(const Identifiers<T> &other) {
    this->insert(other);
    return *this;
}

//! \brief Returns a set of identifiers of type *Identifiers<T>&* 
/*!
  @param [IN] *other* is a set of identifiers of type *Identifiers<T>*
  Replaces this set with the set intersection of *other* with this set
  */
template <typename T>
Identifiers<T>& Identifiers<T>::operator *=(const Identifiers<T> &other) {
    for (auto identifier : m_ids) {
        if (other.ids().find(identifier) == other.ids().end()) {
            m_ids.erase(m_ids.find(identifier));
        }
    }
    return *this;
}

//! \brief Returns a set of identifiers of type *Identifiers<T>&* 
/*!
  @param [IN] *other* is a set of identifiers of type *Identifiers<T>*
  Replaces this set with the set difference between this set and *other*
  */
template <typename T>
Identifiers<T>& Identifiers<T>::operator -=(const Identifiers<T> &other) {
    for (auto identifier : m_ids) {
        if (other.ids().find(identifier) != other.ids().end()) {
            m_ids.erase(m_ids.find(identifier));
        }
    }
    return *this;
}

//! \brief Prints the set of identifiers
template <typename T>
std::ostringstream& operator << (std::ostringstream& os, const Identifiers<T>& identifiers) {
    os << "Set : {";
    for (auto identifier : identifiers.ids()) {
        os << identifier << ", ";
    }
    os << "}";
    return os;
}