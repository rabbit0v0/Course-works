#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP
#define M 100

#include "exceptions.hpp"
#include "utility.hpp"

#include <cstddef>

namespace sjtu {

    template<class T>
    class deque {
    public:
        size_t totalsize;
        class node{
        public:
            T* data;
            node* pre;
            node* next;
            node(){
                data = NULL;
                pre = NULL;
                next = NULL;
            }
            ~node(){
                if (data != NULL)
                    delete data;
            }
        };
        class block{
        public:
            size_t thissize;
            block* pre;
            block* next;
            node* chain;
            block(){
                thissize = 0;
                pre = NULL;
                next = NULL;
                chain = new node;
            }
            
            block(const block &other){
                thissize = other.thissize;
                pre = NULL;
                next = NULL;
                chain = new node;
                node* tem = other.chain;
                node* now = chain;
                while(tem->next != NULL){
                    node* newone = new node;
                    newone->data = new T(*(tem->next->data));//??????????????
                    now->next = newone;
                    newone->pre = now;
                    now = newone;
                    tem = tem->next;
                }
            }
            ~block(){
                node* now = chain;
                while (now->next != NULL){
                    now = now->next;
                    delete now->pre;
                }
                delete now;
            }
        };
        block* head;
        block* tail;
        class const_iterator;
        class iterator {
        private:
            /**
             * TODO add data members
             *   just add whatever you want.
             */
        public:
            deque* thedeque;
            block* theblock;
            node* thenode;
            iterator(){
                thedeque = NULL;
                theblock = NULL;
                thenode = NULL;
            }
            iterator(const const_iterator &other) {
                thedeque = other.thedeque;
                theblock = other.theblock;
                thenode = other.thenode;
                // TODO
            }
            iterator(const iterator &other) {
                thedeque = other.thedeque;
                theblock = other.theblock;
                thenode = other.thenode;
            }
            /**
             * return a new iterator which pointer n-next elements
             *   even if there are not enough elements, the behaviour is **undefined**.
             * as well as operator-
             */
            iterator operator+(const int &n) const {
                if (n < 0){
                    int N = -n;
                    int k = 0;
                    iterator newone = *this;
                    newone.thedeque = thedeque;
                    block* now = theblock;
                    node* tem = thenode;
                    if(now == thedeque->tail){
                        now = now->pre;
                        tem = now->chain;
                        while(tem->next != NULL){
                            tem = tem->next;
                        }
                        k++;
                    }
                    if (now == thedeque->head)
                        throw invalid_iterator();
                    while (k < N){
                        if (tem->pre == now->chain || tem->pre == NULL)
                            break;
                        tem = tem->pre;
                        k++;
                    }
                    if (k == N){
                        newone.theblock = now;
                        newone.thenode = tem;
                        return newone;
                    }
                    while(k < N && now->pre != NULL){
                        now = now->pre;
                        k += now->thissize;
                    }
                    if(now == thedeque->head){
                        throw invalid_iterator();
                    }////////or invalid?
                    k -= now->thissize;
                    tem = now->chain;
                    while(tem->next != NULL)
                        tem = tem->next;
                    k++;
                    if (k == N){
                        newone.theblock = now;
                        newone.thenode = tem;
                        return newone;
                    }
                    while(k < N){
                        tem = tem->pre;
                        k++;
                    }
                    newone.theblock = now;
                    newone.thenode = tem;
                    return newone;
                    //TODO
                }
                if(n == 0)
                    return *this;
                iterator newone = *this;
                newone.thedeque = thedeque;
                block* now = theblock;
                node* tem = thenode;
                int k = 0;
                while(k < n){
                    if (tem->next == NULL)
                        break;
                    tem = tem->next;
                    k++;
                }
                if (k == n){
                    newone.theblock = now;
                    newone.thenode = tem;
                    return newone;
                }
                while(k < n && now->next != NULL){
                    now = now->next;
                    k += now->thissize;
                }
                if(now == thedeque->tail){
                    newone.theblock = thedeque->tail;
                    newone.thenode = thedeque->tail->chain;
                    return newone;
                }
                k -= now->thissize;
                tem = now->chain;
                while(k < n){
                    tem = tem->next;
                    k++;
                }
                newone.theblock = now;
                newone.thenode = tem;
                return newone;
                //TODO
            }
            iterator operator-(const int &n) const {
                if (n < 0){
                    int N = -n;
                    iterator newone = *this;
                    newone.thedeque = thedeque;
                    block* now = theblock;
                    node* tem = thenode;
                    int k = 0;
//            if(now == thedeque->tail || now == thedeque->head)
//                throw invalid_iterator();
                    while(k < N){
                        if (tem->next == NULL)
                            break;
                        tem = tem->next;
                        k++;
                    }
                    if (k == N){
                        newone.theblock = now;
                        newone.thenode = tem;
                        return newone;
                    }
                    while(k < N && now->next != NULL){
                        now = now->next;
                        k += now->thissize;
                    }
                    if(now == thedeque->tail){
                        newone.theblock = thedeque->tail;
                        newone.thenode = thedeque->tail->chain;
                        return newone;
                    }
                    k -= now->thissize;
                    tem = now->chain;
                    while(k < N){
                        tem = tem->next;
                        k++;
                    }
                    newone.theblock = now;
                    newone.thenode = tem;
                    return newone;
                }
                if(n == 0)
                    return *this;
                int k = 0;
                iterator newone = *this;
                newone.thedeque = thedeque;
                block* now = theblock;
                node* tem = thenode;
                while(now->pre != NULL && now->thissize == 0){
                    now = now->pre;
                    tem = now->chain;
                    while(tem->next != NULL){
                        tem = tem->next;
                    }
                    k++;
                }
                if (now == thedeque->head)
                    throw invalid_iterator();
                while (k < n){
                    if (tem->pre == now->chain)
                        break;
                    tem = tem->pre;
                    k++;
                }
                if (k == n){
                    newone.theblock = now;
                    newone.thenode = tem;
                    return newone;
                }
                while(k < n && now->pre != NULL){
                    now = now->pre;
                    k += now->thissize;
                }
                if(now == thedeque->head){
                    newone.theblock = thedeque->head;
                    newone.thenode = NULL;
                    return newone;
                }////////or invalid?
                k -= now->thissize;
                tem = now->chain;
                while(tem->next != NULL)
                    tem = tem->next;
                k++;
                if (k == n){
                    newone.theblock = now;
                    newone.thenode = tem;
                    return newone;
                }
                while(k < n){
                    tem = tem->pre;
                    k++;
                }
                newone.theblock = now;
                newone.thenode = tem;
                return newone;
                //TODO
            }
            // return th distance between two iterator,
            // if these two iterators points to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const {
                if (rhs.thedeque != thedeque)
                    throw invalid_iterator();
                int k = 0;
                node* tem = thenode;
                block* now = theblock;
                if (now == rhs.theblock){
                    while (tem != NULL){
                        if (tem == rhs.thenode)
                            break;
                        tem = tem->next;
                        k--;
                    }
                    if (tem == NULL){
                        k = 0;
                        tem = thenode;
                        while (tem != rhs.thenode){
                            tem = tem->pre;
                            k++;
                        }
                    }
                    return k;
                }
                while(now != thedeque->head){
                    if (now == rhs.theblock)
                        break;
                    now = now->pre;
                }
                if (now == thedeque->head){
                    now = theblock;
                    while(tem->next != NULL){
                        tem = tem->next;
                        k--;
                    }
                    while (now != rhs.theblock){
                        now = now->next;
                        k -= now->thissize;
                    }
                    k += now->thissize;
                    tem = rhs.thenode;
                    k--;
                    if (tem == thedeque->tail->chain){
                        return k;
                    }
                    while(tem->pre != now->chain){
                        tem = tem->pre;
                        k--;
                    }
                    return k;
                }
                else{
                    now = theblock;
                    if (now == thedeque->tail){
                        now = now->pre;
                        tem = now->chain;
                        while(tem->next != NULL){
                            tem = tem->next;
                        }
                        k++;
                    }
                    while(tem->pre != now->chain){
                        tem = tem->pre;
                        k++;
                    }
                    while(now != rhs.theblock){
                        now = now->pre;
                        k += now->thissize;
                    }
                    k -= now->thissize;
                    tem = rhs.thenode;
                    k++;
                    while(tem->next != NULL){
                        tem = tem->next;
                        k++;
                    }
                    return k;
                }
                //TODO
            }
            iterator operator+=(const int &n) {
                *this = this->operator+(n);
                return *this;
                //TODO
            }
            iterator operator-=(const int &n) {
                *this = this->operator-(n);
                return *this;
            }
            /**
             * TODO iter++
             */
            iterator operator++(int) {
                if(*this == thedeque->end()){
                    throw index_out_of_bound();
                }
                iterator newone = *this;
                if (thenode->next == NULL){
                    theblock = theblock->next;
                    if (theblock == thedeque->tail){
                        thenode = theblock->chain;
                        return newone;
                    }
                    thenode = theblock->chain->next;
                    return newone;
                }
                thenode = thenode->next;
                return newone;
            }
            /**
             * TODO ++iter
             */
            iterator& operator++() {
//                added here
                if(*this == thedeque->end()){
                    throw index_out_of_bound();
                }
                if (thenode->next == NULL){
                    theblock = theblock->next;
                    if (theblock == thedeque->tail){
                        thenode = theblock->chain;
                        return *this;
                    }
                    while(theblock->chain->next == NULL){
                        theblock = theblock->next;
                    }
                    thenode = theblock->chain->next;
                    return *this;
                }
                thenode = thenode->next;
                return *this;
            }
            /**
             * TODO iter--
             */
            iterator operator--(int) {
//                added here
                if(*this == thedeque->begin()){
                    throw index_out_of_bound();
                }
                iterator newone = *this;
                if (theblock == thedeque->tail){
                    theblock = thedeque->tail->pre;
                    thenode = theblock->chain;
                    while(thenode->next != NULL){
                        thenode = thenode->next;
                    }
                    return newone;
                }
                if (thenode->pre == theblock->chain){
                    theblock = theblock->pre;
                    thenode = theblock->chain;
                    while(thenode->next != NULL){
                        thenode = thenode->next;
                    }
                    return newone;
                }
                thenode = thenode->pre;
                return newone;
            }
            /**
             * TODO --iter
             */
            iterator& operator--() {
//                added here
                if(*this == thedeque->begin()){
                    throw index_out_of_bound();
                }
                if (theblock == thedeque->tail){
                    theblock = thedeque->tail->pre;
                    thenode = theblock->chain;
                    while(thenode->next != NULL){
                        thenode = thenode->next;
                    }
                    return *this;
                }

                if (thenode->pre == theblock->chain){
                    theblock = theblock->pre;
                    thenode = theblock->chain;
                    while(thenode->next != NULL){
                        thenode = thenode->next;
                    }
                    return *this;
                }
                thenode = thenode->pre;
                return *this;
            }
            /**
             * TODO *it
             */
            T& operator*() const {
                if(*this == thedeque->end()){
                    throw index_out_of_bound();
                }
                return *(thenode->data);
            }
            /**
             * TODO it->field
             */
            T* operator->() const noexcept {
                return thenode->data;
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            bool operator==(const iterator &rhs) const {
                return(rhs.thedeque == thedeque && rhs.theblock == theblock && rhs.thenode == thenode);
            }
            bool operator==(const const_iterator &rhs) const {
                return(rhs.thedeque == thedeque && rhs.theblock == theblock && rhs.thenode == thenode);
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return(rhs.thedeque != thedeque || rhs.theblock != theblock || rhs.thenode!= thenode);
            }
            bool operator!=(const const_iterator &rhs) const {
                return(rhs.thedeque != thedeque || rhs.theblock != theblock || rhs.thenode != thenode);
            }
        };
        class const_iterator {
        private:
            /**
             * TODO add data members
             *   just add whatever you want.
             */
        public:
            deque* thedeque;
            block* theblock;
            node* thenode;
            const_iterator(){
                thedeque = NULL;
                theblock = NULL;
                thenode = NULL;
            }
            const_iterator(const const_iterator &other) {
                thedeque = other.thedeque;
                theblock = other.theblock;
                thenode = other.thenode;
                // TODO
            }
            const_iterator(const iterator &other) {
                thedeque = other.thedeque;
                theblock = other.theblock;
                thenode = other.thenode;
            }
            /**
             * return a new iterator which pointer n-next elements
             *   even if there are not enough elements, the behaviour is **undefined**.
             * as well as operator-
             */
            const_iterator operator+(const int &n) const {
                if (n < 0){
                    int N = -n;
                    int k = 0;
                    const_iterator newone = *this;
                    newone.thedeque = thedeque;
                    block* now = theblock;
                    node* tem = thenode;
                    if(now == thedeque->tail){
                        now = now->pre;
                        tem = now->chain;
                        while(tem->next != NULL){
                            tem = tem->next;
                        }
                        k++;
                    }
                    if (now == thedeque->head)
                        throw invalid_iterator();
                    while (k < N){
                        if (tem->pre == now->chain || tem->pre == NULL)
                            break;
                        tem = tem->pre;
                        k++;
                    }
                    if (k == N){
                        newone.theblock = now;
                        newone.thenode = tem;
                        return newone;
                    }
                    while(k < N && now->pre != NULL){
                        now = now->pre;
                        k += now->thissize;
                    }
                    if(now == thedeque->head){
                        throw invalid_iterator();
                    }////////or invalid?
                    k -= now->thissize;
                    tem = now->chain;
                    while(tem->next != NULL)
                        tem = tem->next;
                    k++;
                    if (k == N){
                        newone.theblock = now;
                        newone.thenode = tem;
                        return newone;
                    }
                    while(k < N){
                        tem = tem->pre;
                        k++;
                    }
                    newone.theblock = now;
                    newone.thenode = tem;
                    return newone;
                    //TODO
                }
                if(n == 0)
                    return *this;
                const_iterator newone = *this;
                newone.thedeque = thedeque;
                block* now = theblock;
                node* tem = thenode;
                int k = 0;
                while(k < n){
                    if (tem->next == NULL)
                        break;
                    tem = tem->next;
                    k++;
                }
                if (k == n){
                    newone.theblock = now;
                    newone.thenode = tem;
                    return newone;
                }
                while(k < n && now->next != NULL){
                    now = now->next;
                    k += now->thissize;
                }
                if(now == thedeque->tail){
                    newone.theblock = thedeque->tail;
                    newone.thenode = thedeque->tail->chain;
                    return newone;
                }
                k -= now->thissize;
                tem = now->chain;
                while(k < n){
                    tem = tem->next;
                    k++;
                }
                newone.theblock = now;
                newone.thenode = tem;
                return newone;
                //TODO
            }
            const_iterator operator-(const int &n) const {
                if (n < 0){
                    int N = -n;
                    const_iterator newone = *this;
                    newone.thedeque = thedeque;
                    block* now = theblock;
                    node* tem = thenode;
                    int k = 0;
//            if(now == thedeque->tail || now == thedeque->head)
//                throw invalid_iterator();
                    while(k < N){
                        if (tem->next == NULL)
                            break;
                        tem = tem->next;
                        k++;
                    }
                    if (k == N){
                        newone.theblock = now;
                        newone.thenode = tem;
                        return newone;
                    }
                    while(k < N && now->next != NULL){
                        now = now->next;
                        k += now->thissize;
                    }
                    if(now == thedeque->tail){
                        newone.theblock = thedeque->tail;
                        newone.thenode = thedeque->tail->chain;
                        return newone;
                    }
                    k -= now->thissize;
                    tem = now->chain;
                    while(k < N){
                        tem = tem->next;
                        k++;
                    }
                    newone.theblock = now;
                    newone.thenode = tem;
                    return newone;
                }
                if(n == 0)
                    return *this;
                int k = 0;
                const_iterator newone = *this;
                newone.thedeque = thedeque;
                block* now = theblock;
                node* tem = thenode;
                while(now->pre != NULL && now->thissize == 0){
                    now = now->pre;
                    tem = now->chain;
                    while(tem->next != NULL){
                        tem = tem->next;
                    }
                    k++;
                }
                if (now == thedeque->head)
                    throw invalid_iterator();
                while (k < n){
                    if (tem->pre == now->chain)
                        break;
                    tem = tem->pre;
                    k++;
                }
                if (k == n){
                    newone.theblock = now;
                    newone.thenode = tem;
                    return newone;
                }
                while(k < n && now->pre != NULL){
                    now = now->pre;
                    k += now->thissize;
                }
                if(now == thedeque->head){
                    newone.theblock = thedeque->head;
                    newone.thenode = NULL;
                    return newone;
                }////////or invalid?
                k -= now->thissize;
                tem = now->chain;
                while(tem->next != NULL)
                    tem = tem->next;
                k++;
                if (k == n){
                    newone.theblock = now;
                    newone.thenode = tem;
                    return newone;
                }
                while(k < n){
                    tem = tem->pre;
                    k++;
                }
                newone.theblock = now;
                newone.thenode = tem;
                return newone;
                //TODO
            }
            // return th distance between two iterator,
            // if these two iterators points to different vectors, throw invaild_iterator.
            int operator-(const const_iterator &rhs) const {
                if (rhs.thedeque != thedeque)
                    throw invalid_iterator();
                int k = 0;
                node* tem = thenode;
                block* now = theblock;
                if (now == rhs.theblock){
                    while (tem != NULL){
                        if (tem == rhs.thenode)
                            break;
                        tem = tem->next;
                        k--;
                    }
                    if (tem == NULL){
                        k = 0;
                        tem = thenode;
                        while (tem != rhs.thenode){
                            tem = tem->pre;
                            k++;
                        }
                    }
                    return k;
                }
                while(now != thedeque->head){
                    if (now == rhs.theblock)
                        break;
                    now = now->pre;
                }
                if (now == thedeque->head){
                    now = theblock;
                    while(tem->next != NULL){
                        tem = tem->next;
                        k--;
                    }
                    while (now != rhs.theblock){
                        now = now->next;
                        k -= now->thissize;
                    }
                    k += now->thissize;
                    tem = rhs.thenode;
                    k--;
                    if (tem == thedeque->tail->chain){
                        return k;
                    }
                    while(tem->pre != now->chain){
                        tem = tem->pre;
                        k--;
                    }
                    return k;
                }
                else{
                    now = theblock;
                    if (now == thedeque->tail){
                        now = now->pre;
                        tem = now->chain;
                        while(tem->next != NULL){
                            tem = tem->next;
                        }
                        k++;
                    }
                    while(tem->pre != now->chain){
                        tem = tem->pre;
                        k++;
                    }
                    while(now != rhs.theblock){
                        now = now->pre;
                        k += now->thissize;
                    }
                    k -= now->thissize;
                    tem = rhs.thenode;
                    k++;
                    while(tem->next != NULL){
                        tem = tem->next;
                        k++;
                    }
                    return k;
                }
                //TODO
            }
            const_iterator operator+=(const int &n) {
                *this = this->operator+(n);
                return *this;
                //TODO
            }
            const_iterator operator-=(const int &n) {
                *this = this->operator-(n);
                return *this;
            }
            /**
             * TODO iter++
             */
            const_iterator operator++(int) {
                if(*this == thedeque->end()){
                    throw index_out_of_bound();
                }
                const_iterator newone = *this;
                if (thenode->next == NULL){
                    theblock = theblock->next;
                    if (theblock == thedeque->tail){
                        thenode = theblock->chain;
                        return newone;
                    }
                    thenode = theblock->chain->next;
                    return newone;
                }
                thenode = thenode->next;
                return newone;
            }
            /**
             * TODO ++iter
             */
            const_iterator& operator++() {
                if(*this == thedeque->end()){
                    throw index_out_of_bound();
                }
                if (thenode->next == NULL){
                    theblock = theblock->next;
                    if (theblock == thedeque->tail){
                        thenode = theblock->chain;
                        return *this;
                    }
                    while(theblock->chain->next == NULL){
                        theblock = theblock->next;
                    }
                    thenode = theblock->chain->next;
                    return *this;
                }
                thenode = thenode->next;
                return *this;
            }
            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                if(*this == thedeque->begin()){
                    throw index_out_of_bound();
                }
                const_iterator newone = *this;
                if (theblock == thedeque->tail){
                    theblock = thedeque->tail->pre;
                    thenode = theblock->chain;
                    while(thenode->next != NULL){
                        thenode = thenode->next;
                    }
                    return newone;
                }
                if (thenode->pre == theblock->chain){
                    theblock = theblock->pre;
                    thenode = theblock->chain;
                    while(thenode->next != NULL){
                        thenode = thenode->next;
                    }
                    return newone;
                }
                thenode = thenode->pre;
                return newone;
            }
            /**
             * TODO --iter
             */
            const_iterator& operator--() {
                if(*this == thedeque->begin()){
                    throw index_out_of_bound();
                }
                if (theblock == thedeque->tail){
                    theblock = thedeque->tail->pre;
                    thenode = theblock->chain;
                    while(thenode->next != NULL){
                        thenode = thenode->next;
                    }
                    return *this;
                }

                if (thenode->pre == theblock->chain){
                    theblock = theblock->pre;
                    thenode = theblock->chain;
                    while(thenode->next != NULL){
                        thenode = thenode->next;
                    }
                    return *this;
                }
                thenode = thenode->pre;
                return *this;
            }
            /**
             * TODO *it
             */
            T& operator*() const {
                if(*this == thedeque->end()){
                    throw index_out_of_bound();
                }
                return *(thenode->data);
            }
            /**
             * TODO it->field
             */
            T* operator->() const noexcept {
                return thenode->data;
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            bool operator==(const iterator &rhs) const {
                return(rhs.thedeque == thedeque && rhs.theblock == theblock && rhs.thenode == thenode);
            }
            bool operator==(const const_iterator &rhs) const {
                return(rhs.thedeque == thedeque && rhs.theblock == theblock && rhs.thenode == thenode);
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return(rhs.thedeque != thedeque || rhs.theblock != theblock || rhs.thenode!= thenode);
            }
            bool operator!=(const const_iterator &rhs) const {
                return(rhs.thedeque != thedeque || rhs.theblock != theblock || rhs.thenode != thenode);
            }
        };
        /**
         * TODO Constructors
         */
        deque() {
            totalsize = 0;
            head = new block;
            tail = new block;
            head->next = tail;
            tail->pre = head;
        }
        deque(const deque &other) {
            totalsize = other.totalsize;
            head = new block;
            tail = new block;
            block* model = other.head->next;
            block* now = head;
            while (model != other.tail){
                block* newone = new block(*model);
                newone->pre = now;
                now->next = newone;
                model = model->next;
                now = newone;
            }
            now->next = tail;
            tail->pre = now;
        }
        /**
         * TODO Deconstructor
         */
        ~deque() {
            block* now = head->next;
            while(now != NULL){
                delete now->pre;
                now = now->next;
            }
            delete tail;
        }
        /**
         * TODO assignment operator
         */
        deque &operator=(const deque &other) {
            if(&other == this)
                return *this;
            totalsize = other.totalsize;
            block* now = head->next->next;
            while(now != NULL){
                delete now->pre;
                now = now->next;
            }
            head->next = tail;
            tail->pre = head;
            block* model = other.head->next;
            now = head;
            while(model != other.tail){
                block* newone = new block(*model);
                newone->pre = now;
                newone->next = tail;
                now->next = newone;
                tail->pre = newone;
                now = newone;
                model = model->next;
            }
            return *this;
        }
        /**
         * access specified element with bounds checking
         * throw index_out_of_bound if out of bound.
         */
        T & at(const size_t &pos) {
            if (pos > totalsize)
                throw index_out_of_bound();
            int sum = 0;
            block* now = head->next;
            while (now != tail) {
                sum += now->thissize;
                if (sum > pos)
                    break;
                now = now->next;
            }
            if (now == tail)
                throw index_out_of_bound();
            sum -= now->thissize;
            node* tem = now->chain;
            while(sum <= pos){
                tem = tem->next;
                sum++;
            }
            return *(tem->data);
        }
        const T & at(const size_t &pos) const {
            if (pos > totalsize)
                throw index_out_of_bound();
            int sum = 0;
            block* now = head->next;
            while (now != tail) {
                sum += now->thissize;
                if (sum > pos)
                    break;
                now = now->next;
            }
            if (now == tail)
                throw index_out_of_bound();
            sum -= now->thissize;
            node* tem = now->chain;
            while(sum <= pos){
                tem = tem->next;
                sum++;
            }
            return *(tem->data);
        }
        T & operator[](const size_t &pos) {
            if (pos > totalsize)
                throw index_out_of_bound();
            int sum = 0;
            block* now = head->next;
            while (now != tail) {
                sum += now->thissize;
                if (sum > pos)
                    break;
                now = now->next;
            }
            if (now == tail)
                throw index_out_of_bound();
            sum -= now->thissize;
            node* tem = now->chain;
            while(sum <= pos){
                tem = tem->next;
                sum++;
            }
            return *(tem->data);
        }
        const T & operator[](const size_t &pos) const {
            if (pos > totalsize)
                throw index_out_of_bound();
            int sum = 0;
            block* now = head->next;
            while (now != tail) {
                sum += now->thissize;
                if (sum > pos)
                    break;
                now = now->next;
            }
            if (now == tail)
                throw index_out_of_bound();
            sum -= now->thissize;
            node* tem = now->chain;
            while(sum <= pos){
                tem = tem->next;
                sum++;
            }
            return *(tem->data);
        }
        /**
         * access the first element
         * throw container_is_empty when the container is empty.
         */
        const T & front() const {
            if (totalsize == 0)
                throw container_is_empty();
            block* now = head->next;
            while(now->thissize == 0){
                now = now->next;
            }
            return *(now->chain->next->data);
        }
        /**
         * access the last element
         * throw container_is_empty when the container is empty.
         */
        const T & back() const {
            if (totalsize == 0)
                throw container_is_empty();
            block* now = tail->pre;
            while(now->thissize == 0){
                now = now->pre;
            }
            node* res = now->chain;
            while(res->next != NULL){
                res = res->next;
            }
            return *(res->data);
        }
        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            iterator beg;
            beg.thedeque = this;
            beg.theblock = head->next;
            if (head->next == tail)
                beg.thenode = tail->chain;
            else
                beg.thenode = head->next->chain->next;
            return beg;
        }
        const_iterator cbegin() const {
            const_iterator beg;
            beg.thedeque = (deque*)this;
            beg.theblock = head->next;
            if (head->next == tail)
                beg.thenode = tail->chain;
            else
                beg.thenode = head->next->chain->next;
            return beg;
        }
        /**
         * returns an iterator to the end.
         */
        iterator end() {
            iterator tend;
            tend.thedeque = this;
            tend.theblock = tail;
            tend.thenode = tail->chain;
            return tend;
        }
        const_iterator cend() const {
            iterator tend;
            tend.thedeque = (deque*)this;
            tend.theblock = tail;
            tend.thenode = tail->chain;
            return tend;
        }
        /**
         * checks whether the container is empty.
         */
        bool empty() const {
            return (totalsize == 0);
        }
        /**
         * returns the number of elements
         */
        size_t size() const {
            return totalsize;
        }
        /**
         * clears the contents
         */
        void clear() {
            block* now = head->next->next;
            while(now != NULL){
                delete now->pre;
                now = now->next;
            }
            head->next = tail;
            tail->pre = head;
            totalsize = 0;
        }
        /**
         * inserts elements at the specified locat on in the container.
         * inserts value before pos
         * returns an iterator pointing to the inserted value
         *     throw if the iterator is invalid or it point to a wrong place.
         */
        iterator insert(iterator pos, const T &value) {
            if (pos.thedeque != this || pos.theblock == head)
                throw invalid_iterator();
            if (pos.theblock == tail){
                block* newblock = new block;
                newblock->thissize = 1;
                totalsize++;
                node* newone = new node;
                newone->data = new T(value);
                newblock->pre = tail->pre;
                tail->pre->next = newblock;
                tail->pre = newblock;
                newblock->next = tail;
                newblock->chain->next = newone;
                newone->pre = newblock->chain;
                iterator now;
                now.thedeque = this;
                now.theblock = newblock;
                now.thenode = newone;
                return now;
            }
            node* newone = new node;
            newone->data = new T(value);
            pos.thenode->pre->next = newone;
            newone->pre = pos.thenode->pre;
            pos.thenode->pre = newone;
            newone->next = pos.thenode;
            iterator now;
            now.thedeque = this;
            now.theblock = pos.theblock;
            now.thenode = newone;
            if (pos.theblock->thissize == M){
                node* tem = pos.thenode;
                while(tem->next != NULL){
                    tem = tem->next;
                }
                if (pos.theblock->next == pos.thedeque->tail || pos.theblock->next->thissize == M){
                    block* newblock = new block;
                    newblock->thissize = 1;
                    newblock->pre = pos.theblock;
                    newblock->next = pos.theblock->next;
                    pos.theblock->next->pre = newblock;
                    pos.theblock->next = newblock;
                    tem->pre->next = NULL;
                    tem->pre = newblock->chain;
                    newblock->chain->next = tem;
                    pos.theblock->thissize--;
                }
                else{
                    block* ablock = pos.theblock->next;
                    node* tmp = ablock->chain->next;
                    tem->pre->next = NULL;
                    tem->pre = ablock->chain;
                    ablock->chain->next = tem;
                    tem->next = tmp;
                    tmp->pre = tem;
                    ablock->thissize++;
                    pos.theblock->thissize--;
                }
            }
            totalsize++;
            pos.theblock->thissize++;
            return now;
        }
        /**
         * removes specified element at pos.
         * removes the element at pos.
         * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
         * throw if the container is empty, the iterator is invalid or it points to a wrong place.
         */
        iterator erase(iterator pos) {
            iterator res = pos + 1;
            if (totalsize == 0 || pos.theblock->thissize == 0)
                throw container_is_empty();
            if (pos.thedeque != this || pos.theblock == tail || pos.theblock == head || pos.thenode == pos.theblock->chain)
                throw invalid_iterator();
            node* tem = pos.thenode;
            block* now = pos.theblock;
            pos.thenode->pre->next = pos.thenode->next;
            if (pos.thenode->next != NULL){
                pos.thenode->next->pre = pos.thenode->pre;
                tem = pos.thenode->next;
            }
            else{
                pos.thenode->pre->next = NULL;
                if (pos.theblock->next == tail)
                    tem = tail->chain;
                else
                    tem = pos.theblock->next->chain->next;
                now = pos.theblock->next;
            }
            delete pos.thenode;
            pos.thenode = tem;
            totalsize--;
            pos.theblock->thissize--;
            if (pos.theblock->thissize == 0){
                now = pos.theblock->next;
                pos.theblock->pre->next = pos.theblock->next;
                pos.theblock->next->pre = pos.theblock->pre;
                delete pos.theblock;
                pos.theblock = now;
                pos.thenode = now->chain->next;
            }
            return res;
        }
        /**
         * adds an element to the end
         */
        void push_back(const T &value) {
            if (totalsize == 0 || tail->pre->thissize == M){
                block* newone = new block;
                newone->pre = tail->pre;
                tail->pre->next = newone;
                newone->next = tail;
                tail->pre = newone;
                node* anode = new node;
                newone->chain->next = anode;
                anode->pre = newone->chain;
                anode->data = new T(value);
                totalsize++;
                newone->thissize = 1;
            }
            else {
                node *now = tail->pre->chain;
                while (now->next != NULL) {
                    now = now->next;
                }
                node *anode = new node;
                now->next = anode;
                anode->pre = now;
                anode->data = new T(value);
                totalsize++;
                tail->pre->thissize++;
            }
        }
        /**
         * removes the last element
         *     throw when the container is empty.
         */
        void pop_back() {
            if (totalsize == 0)
                throw container_is_empty();
            block* now = tail->pre;
            while(now->thissize == 0)
                now = now->pre;
            node* tem = now->chain;
            while(tem->next != NULL)
                tem = tem->next;
            tem->pre->next = NULL;
            delete tem;
            totalsize--;
            now->thissize--;
            if (now->thissize == 0){
                now->pre->next = now->next;
                now->next->pre = now->pre;
                delete now;
            }
        }
        /**
         * inserts an element to txhe beginning.
         */
        void push_front(const T &value) {
            block* now = head->next;
            if(now->thissize == M || now == tail){
                block* newone = new block;
                now->pre->next = newone;
                newone->pre = now->pre;
                now->pre = newone;
                newone->next = now;
                node* tem = new node;
                newone->chain->next = tem;
                tem->pre = newone->chain;
                tem->data = new T(value);
                totalsize++;
                newone->thissize = 1;
            }
            else{
                node* anode = new node;
                anode->data = new T(value);
                node* tem = head->next->chain;
                if(tem->next == NULL){
                    tem->next = anode;
                    anode->pre = tem;
                }
                else{
                    tem->next->pre = anode;
                    anode->next = tem->next;
                    tem->next = anode;
                    anode->pre = tem;
                }
                head->next->thissize++;
                totalsize++;
            }
        }
        /**
         * removes the first element.
         *     throw when the container is empty.
         */
        void pop_front() {
            if (totalsize == 0)
                throw container_is_empty();
            block* now = head->next;
            while(now->thissize == 0)
                now = now->next;
            if (now->thissize == 1){
                now->pre->next = now->next;
                now->next->pre = now->pre;
                delete now;
                totalsize--;
                return;
            }
            node* tem = now->chain->next;
            tem->next->pre = now->chain;
            now->chain->next = tem->next;
            delete tem;
            totalsize--;
            now->thissize--;
        }
    };

}

#endif
