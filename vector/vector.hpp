//
//  vector.hpp
//  STL
//
//  Created by 施晓钰 on 2017/3/31.
//  Copyright © 2017年 幺幺. All rights reserved.
//

#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"
#include <climits>
#include <cstddef>
#include <vector>
#include <stdlib.h>

namespace sjtu {
    /**
     * a data container like std::vector
     * store data in a successive memory and support random access.
     */
    template<typename T>
    class vector {
    private:
        int maxsize, current_size;
        T* l;
    public:
        /**
         * TODO
         * a type for actions of the elements of a vector, and you should write
         *   a class named const_iterator with same interfaces.
         */
        /**
         * you can see RandomAccessIterator at CppReference for help.
         */
        class const_iterator;
        class iterator {
        private:
            /**
             * TODO add data members
             *   just add whatever you want.
             */
        public:
            int no;
            vector* vec;
            iterator(int n = 0, vector* m = NULL){
                no = n;
                vec = m;
            }
            /**
             * return a new iterator which pointer n-next elements
             *   even if there are not enough elements, just return the answer.
             * as well as operator-
             */
            iterator operator+(const int &n) const {
                return iterator(no + n, vec);
                //TODO
            }
            iterator operator-(const int &n) const {
                return iterator(no - n, vec);
                //TODO
            }
            // return the distance between two iterator,
            // if these two iterators points to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const {
                if (rhs.vec != vec){
                    throw invalid_iterator();
                }
                int dis = no - rhs.no;
                return dis;
                //TODO
            }
            iterator operator+=(const int &n) {
                no += n;
                return *this;
                //TODO
            }
            iterator operator-=(const int &n) {
                no -= n;
                return *this;
                //TODO
            }
            /**
             * TODO iter++
             */
            iterator operator++(int) {
                return iterator(no++, vec);
            }
            /**
             * TODO ++iter
             */
            iterator& operator++() {
                ++no;
                return *this;
            }
            /**
             * TODO iter--
             */
            iterator operator--(int) {
                return iterator(no--, vec);
            }
            /**
             * TODO --iter
             */
            iterator& operator--() {
                no--;
                return *this;
            }
            /**
             * TODO *it
             */
            T& operator*() const{
                return vec->l[no];
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            
            
            bool operator==(const iterator &rhs) const {
                return (vec == rhs.vec && no == rhs.no);
            }
            bool operator==(const const_iterator &rhs) const {
                return (vec == rhs.vec && no == rhs.no);
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return (vec != rhs.vec || no != rhs.no);
            }
            bool operator!=(const const_iterator &rhs) const {
                return (vec != rhs.vec || no != rhs.no);
            }
        };
        /**
         * TODO
         * has same function as iterator, just for a const object.
         */
        class const_iterator {
        private:
            /**
             * TODO add data members
             *   just add whatever you want.
             */
        public:
            int no;
            vector* vec;
            const_iterator(int n = 0, vector* m = NULL){
                no = n;
                vec = m;
            }
            /**
             * return a new iterator which pointer n-next elements
             *   even if there are not enough elements, just return the answer.
             * as well as operator-
             */
            const_iterator operator+(const int &n) const {
                return const_iterator(no + n, vec);
                //TODO
            }
            const_iterator operator-(const int &n) const {
                return const_iterator(no - n, vec);
                //TODO
            }
            // return the distance between two iterator,
            // if these two iterators points to different vectors, throw invaild_iterator.
            int operator-(const const_iterator &rhs) const {
                if (rhs.vec != vec){
                    throw invalid_iterator();
                }
                int dis = no - rhs.no;
                return dis;
                //TODO
            }
            const_iterator operator+=(const int &n) {
                no += n;
                return *this;
                //TODO
            }
            const_iterator operator-=(const int &n) {
                no -= n;
                return *this;
                //TODO
            }
            /**
             * TODO iter++
             */
            const_iterator operator++(int) {
                return const_iterator(no++, vec);
            }
            /**
             * TODO ++iter
             */
            const_iterator& operator++() {
                ++no;
                return *this;
            }
            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                return const_iterator(no--, vec);
            }
            /**
             * TODO --iter
             */
            const_iterator& operator--() {
                --no;
                return *this;
            }
            /**
             * TODO *it
             */
            T& operator*() const{
                return vec->l[no];
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            bool operator==(const iterator &rhs) const {
                return (vec == rhs.vec && no == rhs.no);
            }
            bool operator==(const const_iterator &rhs) const {
                return (vec == rhs.vec && no == rhs.no);
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return (vec != rhs.vec || no != rhs.no);
            }
            bool operator!=(const const_iterator &rhs) const {
                return (vec != rhs.vec || no != rhs.no);
            }
        };
        
        
        
        
        
        
        /**
         * TODO Constructs
         * Atleast three: default constructor, copy constructor and a constructor for std::vector
         */
        vector(int a = 1000, int b = 0){
            maxsize = a;
            current_size = b;
            l = (T*) malloc(maxsize * sizeof(T));
            memset(l, 0, maxsize * sizeof(T));
        }
        vector(const vector &other){
            maxsize = other.maxsize;
            current_size = other.current_size;
            l = (T*) malloc(maxsize * sizeof(T));
            memset(l, 0, maxsize * sizeof(T));
            for (int i = 0; i < current_size; ++i){
                l[i] = other.l[i];
            }
        }
        template<class c>
        vector(const c &other){
            current_size = other.size();
            maxsize = other.size();
            l = (T*) malloc(maxsize * sizeof(T));
            memset(l, 0, maxsize * sizeof(T));
            for (int i = 0; i < maxsize; ++i){
                l[i] = other[i];
            }
        }
        /**
         * TODO Destructor
         */
        ~vector() {
            for (int i = 0; i < maxsize; ++i){
                l[i].~T();
            }
            free(l);
        }
        /**
         * TODO Assignment operator
         */
        vector &operator=(const vector &other) {
            for (int i = 0; i < maxsize; ++i){
                l[i].~T();
            }
            free(l);
            current_size = other.current_size;
            maxsize = other.maxsize;
            l = (T*) malloc(maxsize * sizeof(T));
            memset(l, 0, maxsize * sizeof(T));
            for (int i = 0; i < current_size; ++i){
                l[i] = other.l[i];
            }
            return *this;
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         */
        T & at(const size_t &pos) {
            if (pos >= current_size || pos < 0){
                throw index_out_of_bound();
            }
            return l[pos];
        }
        const T & at(const size_t &pos) const {
            if (pos >= current_size || pos < 0){
                throw index_out_of_bound();
            }
            return l[pos];
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T & operator[](const size_t &pos) {
            if (pos >= current_size || pos < 0){
                throw index_out_of_bound();
            }
            return l[pos];
        }
        const T & operator[](const size_t &pos) const {
            if (pos >= current_size || pos < 0){
                throw index_out_of_bound();
            }
            return l[pos];
        }
        /**
         * access the first element.
         * throw container_is_empty if size == 0
         */
        const T & front() const {
            if (current_size == 0){
                throw container_is_empty();
            }
            return l[0];
        }
        /**
         * access the last element.
         * throw container_is_empty if size == 0
         */
        const T & back() const {
            if (current_size == 0){
                throw container_is_empty();
            }
            return l[current_size - 1];
        }
        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            return iterator(0, this);
        }
        const_iterator cbegin() const {
            return const_iterator(0, const_cast<vector*>(this));
        }
        /**
         * returns an iterator to the end.
         */
        iterator end() {
            return iterator(current_size, this);
        }
        const_iterator cend() const {
            return const_iterator(current_size, const_cast<vector*>(this));
        }
        /**
         * checks whether the container is empty
         */
        bool empty() const {
            return current_size == 0;
        }
        /**
         * returns the number of elements
         */
        size_t size() const {
            return current_size;
        }
        /**
         * returns the number of elements that can be held in currently allocated storage.
         */
        size_t capacity() const {
            return maxsize;
        }
        /**
         * clears the contents
         */
        void clear() {
            current_size = 0;
        }
        /**
         * inserts value before pos
         * returns an iterator pointing to the inserted value.
         */
        iterator insert(iterator pos, const T &value) {
            if (pos.no < 0 || pos.no > current_size)
                throw index_out_of_bound();
            if (current_size == maxsize){
                T* tem = (T*) malloc(2 * maxsize * sizeof(T));
                memset(tem, 0, 2 * maxsize * sizeof(T));
                for (int i = 0; i < pos.no; ++i){
                    tem[i] = l[i];
                }
                for (int i = pos.no; i < maxsize; ++i){
                    tem[i + 1] = l[i];
                }
                tem[pos.no] = value;
                for (int i = 0; i < maxsize; ++i){
                    l[i].~T();
                }
                free(l);
                l = tem;
                maxsize *= 2;
                current_size++;
                return iterator(pos.no, this);
            }
            for (int i = current_size - 1; i >= pos.no; --i){
                l[i + 1] = l[i];
            }
            current_size++;
            l[pos.no] = value;
            return iterator(pos.no, this);
        }
        /**
         * inserts value at index ind.
         * after inserting, this->at(ind) == value is true
         * returns an iterator pointing to the inserted value.
         * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
         */
        iterator insert(const size_t &ind, const T &value) {
            if (ind > current_size || ind < 0)
                throw index_out_of_bound();
            if (current_size == maxsize){
                T* tem = (T*) malloc(2 * maxsize * sizeof(T));
                memset(tem, 0, 2 * maxsize * sizeof(T));
                for (int i = 0; i < ind; ++i){
                    tem[i] = l[i];
                }
                for (int i = ind; i < maxsize; ++i){
                    tem[i + 1] = l[i];
                }
                tem[ind] = value;
                for (int i = 0; i < maxsize; ++i){
                    l[i].~T();
                }
                free(l);
                l = tem;
                maxsize *= 2;
                current_size++;
                return iterator(ind, this);
            }
            for (int i = current_size - 1; i >= ind; --i){
                l[i + 1] = l[i];
            }
            current_size++;
            l[ind] = value;
            return iterator(ind, this);
        }
        /**
         * removes the element at pos.
         * return an iterator pointing to the following element.
         * If the iterator pos refers the last element, the end() iterator is returned.
         */
        iterator erase(iterator pos) {
            if (pos.no < 0 || pos.no >= current_size)
                throw index_out_of_bound();
            for (int i = pos.no; i < current_size - 1; ++i){
                l[i] = l[i + 1];
            }
            current_size--;
            if (pos.no == current_size)
                return end();
            return iterator(pos.no, this);
        }
        /**
         * removes the element with index ind.
         * return an iterator pointing to the following element.
         * throw index_out_of_bound if ind >= size
         */
        iterator erase(const size_t &ind) {
            if (ind >= current_size || ind < 0){
                throw index_out_of_bound();
            }
            for (int i = ind; i < current_size - 1; ++i){
                l[i] = l[i + 1];
            }
            current_size--;
            if (ind == current_size)
                return end();
            return iterator(ind, this);
        }
        /**
         * adds an element to the end.
         */
        void push_back(const T &value) {
            if (current_size == maxsize){
                T* tem = (T*) malloc(2 * maxsize * sizeof(T));
                memset(tem, 0, 2 * maxsize * sizeof(T));
                for (int i = 0; i < maxsize; ++i){
                    tem[i] = l[i];
                }
                tem[maxsize] = value;
                for (int i = 0; i < maxsize; ++i){
                    l[i].~T();
                }
                free(l);
                l = tem;
                maxsize *= 2;
                current_size++;
                return;
            }
            l[current_size] = value;
            current_size++;
        }
        /**
         * remove the last element from the end.
         * throw container_is_empty if size() == 0
         */
        void pop_back() {
            if (empty()){
                throw container_is_empty();
            }
            erase(current_size - 1);
        }
    };
    
    
}

#endif