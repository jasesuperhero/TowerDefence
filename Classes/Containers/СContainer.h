//
//  СContainer.h
//  HelloCpp
//
//  Created by Daniel on 18.11.13.
//
//

#ifndef __HelloCpp___Container__
#define __HelloCpp___Container__

#include <iostream>
#include <cmath>

typedef unsigned int size_type;

template<class T>
class CContainer
{
private:
    T* array;
    size_type cur_size;
    size_type cap_size;
    const size_type MUL = 2;
    const size_type MAX_SIZE = 10000000;
    
    size_type getCapacity(size_type x) {
        return pow(2, (int)(log(x)/log(2)) + 1);
    }
    
    friend class inputIterator;
    friend class iterator;
    friend class const_iterator;
    
public:
    class inputIterator;
    class iterator;
    class const_iterator;
    
    /** Класс итератора ввода */
    class inputIterator
    {
    private:
        CContainer* vec;
        unsigned int index;
        
        friend class iterator;
        friend class const_iterator;
        friend class CContainer;
        
    public:
        /** Конструкторы */
        inputIterator() : vec(NULL), index(0) {
        }
        inputIterator(CContainer& aCContainer, bool b = false) : vec(&aCContainer) {
            if(b) index = vec->size();
            else index = 0;
        }
        inputIterator(const inputIterator& it) : vec(it.vec), index(it.index) {
        }
        inputIterator(const iterator& it) : vec(it.vec), index(it.index) {
        }
        /** Деструктор */
        ~inputIterator() {
        }
        
        /** Перегрузка операторов */
        inputIterator& operator=(const inputIterator& it) {
            vec = it.vec;
            index = it.index;
            return *this;
        }
        inputIterator& operator++() {
            if(index + 1 > vec->size()) throw "Index is out of bound";
            ++index;
            return *this;
        }
        inputIterator& operator++(int) {
            return operator ++();
        }
        
        T& current() const {
            return (*vec)[index];
        }
        T& operator*() const {
            return current();
        }
        T* operator->() const {
            return &current();
        }
        
        inline bool operator==(const iterator& it) const {
            return index == it.index;
        }
        inline bool operator!=(const iterator& it) const {
            return index != it.index;
        }
        inline bool operator==(const const_iterator& it) const {
            return index == it.index;
        }
        inline bool operator!=(const const_iterator& it) const {
            return index != it.index;
        }
        inline bool operator==(const inputIterator& it) const {
            return index == it.index;
        }
        inline bool operator!=(const inputIterator& it) const {
            return index != it.index;
        }
    };
    
    class iterator
    {
    private:
        CContainer* vec;
        unsigned int index;
        
        friend class const_iterator;
        friend class inputIterator;
        friend class CContainer;
        
    public:
        /** Конструкторы */
        iterator() : vec(NULL), index(0) {
        }
        iterator(CContainer& aCContainer, bool b = false) : vec(&aCContainer) {
            if(b) index = vec->size();
            else index = 0;
        }
        iterator(const iterator& it) : vec(it.vec), index(it.index) {
        }
        iterator(const inputIterator& it) : vec(it.vec), index(it.index) {
        }
        /** Деструктор */
        ~iterator() {
        }
        
        /** Перегрузка операторов */
        iterator& operator=(const iterator& it) {
            vec = it.vec;
            index = it.index;
            return *this;
        }
        iterator& operator=(const inputIterator& it) {
            vec = it.vec;
            index = it.index;
            return *this;
        }
        iterator& operator++() {
            if(index + 1 > vec->size()) throw "Index is out of bound";
                ++index;
            return *this;
        }
        iterator& operator++(int) {
            return operator ++();
        }
        iterator& operator--() {
            if(index - 1 < 0) throw "Index is out of bound";
                --index;
            return *this;
        }
        iterator& operator--(int) {
            return operator --();
        }
        iterator& operator+=(unsigned int amount) {
            if(index + amount > vec->size()) throw "Index is out of bound";
                index += amount;
            return *this;
        }
        iterator& operator-=(unsigned int amount) {
            if(index - amount < 0) throw "Index is out of bound";
                index -= amount;
            return *this;
        }
        iterator operator+(unsigned int amount) const {
            iterator it(*this);
            it += amount;
            return it;
        }
        iterator operator-(unsigned int amount) const {
            iterator it(*this);
            it -= amount;
            return it;
        }
        
        T& current() const {
            return (*vec)[index];
        }
        T& operator*() const {
            return current();
        }
        T* operator->() const {
            return &current();
        }
        
        inline bool operator==(const inputIterator& it) const {
            return index == it.index;
        }
        inline bool operator!=(const inputIterator& it) const {
            return index != it.index;
        }
        inline bool operator<(const inputIterator& it) const {
            return index < it.index;
        }
        inline bool operator>(const inputIterator& it) const {
            return index > it.index;
        }
        inline bool operator<=(const inputIterator& it) const {
            return index <= it.index;
        }
        inline bool operator>=(const inputIterator& it) const {
            return index >= it.index;
        }
        inline bool operator==(const iterator& it) const {
            return index == it.index;
        }
        inline bool operator!=(const iterator& it) const {
            return index != it.index;
        }
        inline bool operator<(const iterator& it) const {
            return index < it.index;
        }
        inline bool operator>(const iterator& it) const {
            return index > it.index;
        }
        inline bool operator<=(const iterator& it) const {
            return index <= it.index;
        }
        inline bool operator>=(const iterator& it) const {
            return index >= it.index;
        }
        inline bool operator==(const const_iterator& it) const {
            return index == it.index;
        }
        inline bool operator!=(const const_iterator& it) const {
            return index != it.index;
        }
        inline bool operator<(const const_iterator& it) const {
            return index < it.index;
        }
        inline bool operator>(const const_iterator& it) const {
            return index > it.index;
        }
        inline bool operator<=(const const_iterator& it) const {
            return index <= it.index;
        }
        inline bool operator>=(const const_iterator& it) const {
            return index >= it.index;
        }
    };
    
    class const_iterator
    {
    private:
        const CContainer* vec;
        unsigned int index;
        
    public:
        /** Конструкторы */
        const_iterator() : index(0) {
        }
        const_iterator(const CContainer& aCContainer, bool b = false) : vec(&aCContainer) {
            if(b) index = vec->size();
            else index = 0;
        }
        const_iterator(const const_iterator& it) : vec(it.vec), index(it.index) {
        }
        const_iterator(const iterator& it) : vec(it.vec), index(it.index) {
        }
        const_iterator(const inputIterator& it) : vec(it.vec), index(it.index) {
        }
        /** Деструктор */
        ~const_iterator() {
        }
        
        /** Перегруженные операторы */
        const_iterator& operator=(const const_iterator& it) {
            vec = it.vec;
            index = it.index;
            return *this;
        }
        const_iterator& operator=(const inputIterator& it) {
            vec = it.vec;
            index = it.index;
            return *this;
        }
        const_iterator& operator=(const iterator& it) {
            vec = it.vec;
            index = it.index;
            return *this;
        }
        const_iterator& operator++() {
            if(index + 1 > vec->size()) throw "Index is out of bound";
            ++index;
            return *this;
        }
        const_iterator& operator++(int) {
            return operator ++();
        }
        const_iterator& operator--() {
            if(index - 1 < 0) throw "Index is out of bound";
            --index;
            return *this;
        }
        const_iterator& operator--(int) {
            return operator --();
        }
        const_iterator& operator+=(unsigned int amount) {
            if(index + amount > vec->size()) throw "Index is out of bound";
            index += amount;
            return *this;
        }
        const_iterator& operator-=(unsigned int amount) {
            if(index - amount < 0) throw "Index is out of bound";
            index -= amount;
            return *this;
        }
        const_iterator operator+(unsigned int amount) const {
            const_iterator it(*this);
            it += amount;
            return it;
        }
        const_iterator operator-(unsigned int amount) const {
            const_iterator it(*this);
            it -= amount;
            return it;
        }
        
        const T& current() const {
            return (*vec)[index];
        }
        const T& operator*() const {
            return current();
        }
        const T* operator->() const {
            return &current();
        }
        
        inline bool operator==(const inputIterator& it) const {
            return index == it.index;
        }
        inline bool operator!=(const inputIterator& it) const {
            return index != it.index;
        }
        inline bool operator<(const inputIterator& it) const {
            return index < it.index;
        }
        inline bool operator>(const inputIterator& it) const {
            return index > it.index;
        }
        inline bool operator<=(const inputIterator& it) const {
            return index <= it.index;
        }
        inline bool operator>=(const inputIterator& it) const {
            return index >= it.index;
        }
        inline bool operator==(const iterator& it) const {
            return index == it.index;
        }
        inline bool operator!=(const iterator& it) const {
            return index != it.index;
        }
        inline bool operator<(const iterator& it) const {
            return index < it.index;
        }
        inline bool operator>(const iterator& it) const {
            return index > it.index;
        }
        inline bool operator<=(const iterator& it) const {
            return index <= it.index;
        }
        inline bool operator>=(const iterator& it) const {
            return index >= it.index;
        }
        inline bool operator==(const const_iterator& it) const {
            return index == it.index;
        }
        inline bool operator!=(const const_iterator& it) const {
            return index != it.index;
        }
        inline bool operator<(const const_iterator& it) const {
            return index < it.index;
        }
        inline bool operator>(const const_iterator& it) const {
            return index > it.index;
        }
        inline bool operator<=(const const_iterator& it) const {
            return index <= it.index;
        }
        inline bool operator>=(const const_iterator& it) const {
            return index >= it.index;
        }
    };
    
    /** Итераторы контейнера */
    iterator begin() {
        return iterator(*this);
    }
    iterator end() noexcept {
        return iterator(*this, true);
    }
    const_iterator cbegin() const {
        return const_iterator(*this);
    }
    const_iterator cend() const {
        return const_iterator(*this, true);
    }
    
    /** Конструкторы */
    CContainer() : array(NULL), cur_size(0), cap_size(0) {}
    CContainer(size_type n, const T& val = T()) : cur_size(n) {
        cap_size = getCapacity(cur_size);
        array = new T[cap_size];
        for (int i = 0; i < cur_size; i++)
            array[i] = val;
    }
    
    CContainer(inputIterator first, inputIterator last) : cur_size(last.index - first.index), cap_size(getCapacity(cur_size)){
        array = new T[cap_size];
        for (int i; first != last; first++, i++)
            array[i] = *first;
    }
    
    CContainer(const CContainer& x) : cur_size(x.size()), cap_size(getCapacity(x.size())) {
        array = new T[cap_size];
        for (int i = 0; i < cur_size; i++)
            array[i] = x.array[i];
    }
    
    CContainer(const CContainer& x, size_type size, const T& val = T()) : cur_size(size), cap_size(getCapacity(size)) {
        array = new T[cap_size];
        for (int i = 0; i < cur_size && i < x.cur_size; i++)
            array[i] = x.array[i];
        for (int i = x.cur_size; i < cur_size; i ++)
            array[i] = val;
    }
    
    /** Деструктор */
    ~CContainer() {
        this->clear();
    }
    
    /** Перегрузка операторов */
    CContainer& operator =(const CContainer& x) {
        this->clear();
        cur_size = x.cur_size;
        cap_size = getCapacity(cur_size);
        array = new T[cap_size];
        for (int i = 0; i < cur_size; i++)
            array[i] = x.array[i];
    }
    
    /** Размерность контейнера */
    size_type size() const {
        return cur_size;
    }
    size_type max_size() const {
        return MAX_SIZE;
    }
    void resize(size_type n, const T val = T()) {
        *this = CContainer(*this, n, val);
    }
    size_type capacity() const {
        return cap_size;
    }
    bool empty() const {
        return cur_size == 0;
    }
    
    /** Доступ к элементам */
    T& operator[](size_type n) {
        return this->at(n);
    }
    const T& operator[](size_type n) const {
        return this->at(n);
    }
    T& at (size_type n) {
        if(n >= cur_size) throw "Out of range";
        return array[n];
    }
    const T& at (size_type n) const {
        if(n >= cur_size) throw "Out of range";
        return array[n];
    }
    T& front() {
        return array[0];
    }
    const T& front() const {
        return array[0];
    }
    T& back() {
        return array[cur_size-1];
    }
    const T& back() const {
        return array[cur_size-1];
    }
    
    /** Изменение состояния контейнера */
    void assign(inputIterator first, inputIterator last) {
        *this = CContainer(first, last);
    }
    
    void assign(size_type n, const T& val) {
        *this = CContainer(n, val);
    }
    
    void push_back(const T& val) {
        if (cur_size == MAX_SIZE) throw "CContainer overflow";
        if (cap_size != cur_size) {
            array[cur_size++] = val;
            return;
        }
        *this = CContainer(*this, cur_size + 1, val);
    }
    void pop_back() {
        array[--cur_size] = T();
    }
    
    iterator insert(iterator position, const T& val) {
        if (cur_size == MAX_SIZE) throw "CContainer overflow";
        if (cur_size == cap_size) *this = CContainer(*this, cur_size + 1);
        else cur_size++;
        for(iterator it = position; it + 1 != end(); it++) *(it + 1) = *it;
        *position = val;
        return position;
    }
    
    iterator insert(iterator position, inputIterator first, inputIterator last) {
        unsigned int n = last.index - first.index;
        if(cur_size+n-1 == MAX_SIZE) throw "CContainer overflow";
        if(cur_size+n >= cap_size) *this = CContainer(*this, cur_size + n);
        else cur_size += n;
        for(iterator it = end()-n-1; it != position; it--) *(it+n) = *it;
        *(position+n) = *position;
        for(iterator it = position; first != last; it++, first++) *it = *first;
        return position;
    }
    
    iterator erase(iterator position) {
        for(iterator it = position; it+1 != end(); it++) *it = *(it+1);
        cur_size--;
        return position;
    }
    
    iterator erase(iterator first, iterator last) {
        unsigned int n = last.index - first.index;
        for(iterator it = first; it+n != end(); it++) *it = *(it+n);
        cur_size -= n;
        return first;
    }
    
    void swap(CContainer& x) {
        CContainer buf(x);
        x = *this;
        *this = buf;
    }
    
    void clear() {
        delete[] array;
        array = NULL;
        cur_size = 0;
        cap_size = 0;
    }
    
};

#endif /* defined(__HelloCpp___Container__) */
