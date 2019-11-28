#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

#include <functional>
#include <cstddef>
#include <iostream>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

    template<
            class Key,
            class T,
            class Compare = std::less<Key>
    > class map {
    public:
        typedef pair<const Key, T> value_type;
        struct node{
            T* data;
            Key* key;
            value_type* val;
            node* lc;
            node* rc;
            node* lkey;
            node* hkey;
            node(){
                lc = NULL;
                rc = NULL;
                key = NULL;
                data = NULL;
                lkey = NULL;
                hkey = NULL;
                val = NULL;
            }
            ~node(){
                if (val != NULL){
                    delete val;
                }
                if (key != NULL){
                    delete key;
                }
                if (data != NULL){
                    delete data;
                }
            }

        };
        node* themax = (node*)-2;
        class search{
        public:
            Compare cmp;
            node* root;
            int size;
            node* insert(node* &now, const Key &key, const T &data, node* low, node* high, bool &flag){
                if (now == NULL){
                    node* tem = new node;
                    tem->key = new Key(key);
                    tem->data = new T(data);
                    if (low != NULL)
                        low->hkey = tem;
                    if (high != NULL)
                        high->lkey = tem;
                    tem->lkey = low;
                    tem->hkey = high;
                    now = tem;
                    flag = 1;
                    size++;
                    return tem;
                }
                else if (cmp(key, *(now->key))){
                    return insert(now->lc, key, data, low, now, flag);
                }
                else if (cmp(*(now->key), key)){
                    return insert (now->rc, key, data, now, high, flag);
                }
                else
                    return now;
            }
            node* find(node* now, Key key){
                if (now == NULL)
                    return NULL;
                if (!cmp(*(now->key), key) && !cmp(key, *(now->key)))
                    return now;
                else if (now->lc != NULL && cmp(key, *(now->key)))
                    return find(now->lc, key);
                else if (now->rc != NULL && cmp(*(now->key), key))
                    return find(now->rc, key);
                else
                    return NULL;
            }
            void remove(Key key){
                remove(root, key);
            }

            void remove(node* &now, Key key){
                if (!cmp(*(now->key), key) && !cmp(key, *(now->key))){
                    if (now->lc != NULL && now->rc != NULL){
                        node* tem = now->rc;
                        while(tem->lc != NULL)
                            tem = tem->lc;
                        *(now->data) = *(tem->data);
                        *(now->key) = *(tem->key);
                        remove(now->rc, *(now->key));
                    }
                    else{
                        node* old = now;
                        if (old->lkey != NULL)
                            old->lkey->hkey = old->hkey;
                        if (old->hkey != NULL)
                            old->hkey->lkey = old->lkey;
                        now = (now->lc != NULL)? now->lc : now->rc;
                        delete old;
                        size--;
                    }
                }
                else if (cmp(key, *(now->key)))
                    remove(now->lc, key);
                else
                    remove(now->rc, key);
            }

            void dfsadd(node* now, node* model){
                if (model->lc != NULL){
                    node* newnode = new node;
                    newnode->key = new Key(*(model->lc->key));
                    newnode->data = new T(*(model->lc->data));
                    now->lc = newnode;
                    newnode->lkey = now->lkey;
                    newnode->hkey = now;
                    if (now->lkey == NULL)
                        now->lkey = newnode;
                    else{
                        now->lkey->hkey = newnode;
                        now->lkey = newnode;
                    }
                    dfsadd(newnode, model->lc);
                }
                if (model->rc != NULL){
                    node* newnode = new node;
                    newnode->key = new Key(*(model->rc->key));
                    newnode->data = new T(*(model->rc->data));
                    now->rc = newnode;
                    newnode->lkey = now;
                    newnode->hkey = now->hkey;
                    if (now->hkey == NULL)
                        now->hkey = newnode;
                    else{
                        now->hkey->lkey = newnode;
                        now->hkey = newnode;
                    }
                    dfsadd(newnode, model->rc);
                }
            }

            search(){
                size = 0;
                root = NULL;
            }

            search (const search &other){
                size = other.size;
                node* model = other.root;
                if (model == NULL) {
                    root = NULL;
                    return;
                }
                root = new node;
                root->key = new Key(*(model->key));
                root->data = new T(*(model->data));
                dfsadd(root, model);
            }

            void dfsedelete(node* now){
                if (now->lc != NULL){
                    dfsedelete(now->lc);
                    now->lc = NULL;
                }
                if (now->rc != NULL){
                    dfsedelete(now->rc);
                    now->rc = NULL;
                }
                delete now;
            }

            ~search(){
                if (root != NULL)
                    dfsedelete(root);
                size = 0;
            }
            void travers(node* root){
                if(root == NULL)
                    return;
                if(root->lc != NULL){
                    travers(root->lc);
                }
                std::cout<<root->key->val<<'\t';
                if(root->rc != NULL){
                    travers(root->rc);
                }
            }
        };
        search* tree;

        class const_iterator;
        class iterator {
        public:
            map* themap;
            node* thenode;
            iterator() {
                themap = NULL;
                thenode = NULL;
                // TODO
            }
            iterator(const iterator &other) {
                themap = other.themap;
                thenode = other.thenode;
                // TODO
            }

            iterator operator++(int) {
                iterator newone(*this);
                if (thenode->hkey == NULL)
                    thenode = themap->themax;
                else
                    thenode = thenode->hkey;
                return newone;
            }

            iterator & operator++() {
                if (thenode->hkey == NULL)
                    thenode = themap->themax;
                else
                    thenode = thenode->hkey;
                return *this;
            }

            iterator operator--(int) {
                iterator newone(*this);
                if (thenode == themap->themax){
                    node* now = themap->tree->root;
                    while(now->hkey != NULL)
                        now = now->hkey;
                    thenode = now;
                }
                else
                    thenode = thenode->lkey;
                return newone;
            }

            iterator & operator--() {
                if (thenode == themap->themax){
                    node* now = themap->tree->root;
                    while(now->hkey != NULL)
                        now = now->hkey;
                    thenode = now;
                }
                else
                    thenode = thenode->lkey;
                return *this;
            }

            value_type & operator*() const {
                thenode->val = new value_type(*(thenode->key), *(thenode->data));
                return *(thenode->val);
            }
            bool operator==(const iterator &rhs) const {
                return (thenode == rhs.thenode && themap == rhs.themap);
            }
            bool operator==(const const_iterator &rhs) const {
                return (thenode == rhs.thenode && themap == rhs.themap);
            }

            bool operator!=(const iterator &rhs) const {
                return (themap != rhs.themap || thenode != rhs.thenode);
            }
            bool operator!=(const const_iterator &rhs) const {
                return (themap != rhs.themap || thenode != rhs.thenode);
            }

            value_type* operator->() const noexcept {
                if (thenode->val == NULL)
                    thenode->val = new value_type(*(thenode->key), *(thenode->data));
                return thenode->val;
            }
        };
        class const_iterator {
            // it should has similar member method as iterator.
            //  and it should be able to construct from an iterator.
        private:
            // data members.
        public:
            map* themap;
            node* thenode;
            const_iterator() {
                themap = NULL;
                thenode = NULL;
                // TODO
            }
            const_iterator(const const_iterator &other) {
                themap = other.themap;
                thenode = other.thenode;
                // TODO
            }
            const_iterator(const iterator &other) {
                themap = other.themap;
                thenode = other.thenode;
                // TODO
            }
            // And other methods in iterator.
            const_iterator operator++(int) {
                const_iterator newone(*this);
                if (thenode->hkey == NULL)
                    thenode = themap->themax;
                else
                    thenode = thenode->hkey;
                return newone;
            }

            const_iterator & operator++() {
                if (thenode->hkey == NULL)
                    thenode = themap->themax;
                else
                    thenode = thenode->hkey;
                return *this;
            }

            const_iterator operator--(int) {
                const_iterator newone(*this);
                if (thenode == themap->themax){
                    node* now = themap->tree->root;
                    while(now->hkey != NULL)
                        now = now->hkey;
                    thenode = now;
                }
                else
                    thenode = thenode->lkey;
                return newone;
            }

            const_iterator & operator--() {
                if (thenode == themap->themax){
                    node* now = themap->tree->root;
                    while(now->hkey != NULL)
                        now = now->hkey;
                    thenode = now;
                }
                else
                    thenode = thenode->lkey;
                return *this;
            }

            value_type & operator*() const {
                thenode->val = new value_type(*(thenode->key), *(thenode->data));
                return *(thenode->val);
            }
            bool operator==(const iterator &rhs) const {
                return (thenode == rhs.thenode && themap == rhs.themap);
            }
            bool operator==(const const_iterator &rhs) const {
                return (thenode == rhs.thenode && themap == rhs.themap);
            }

            bool operator!=(const iterator &rhs) const {
                return (themap != rhs.themap || thenode != rhs.thenode);
            }
            bool operator!=(const const_iterator &rhs) const {
                return (themap != rhs.themap || thenode != rhs.thenode);
            }//problem exist when compare with cend

            value_type* operator->() const noexcept {
                thenode->val = new value_type(*(thenode->key), *(thenode->data));
                return thenode->val;
            }
        };

        map() {
            tree = new search;
        }
        map(const map &other) {
            tree = new search (*(other.tree));
        }

        map & operator=(const map &other) {
            delete tree;
            tree = new search(*(other.tree));
            return *this; // return value;
        }

        ~map() {
            delete tree;
        }

        T & at(const Key &key) {
            //boundary?
            node* pos;
            pos = tree->find(tree->root, key);
            if (pos == NULL)
                throw index_out_of_bound();
            return *(pos->data);
        }
        const T & at(const Key &key) const {
            node* pos;
            pos = tree->find(tree->root, key);
            if (pos == NULL)
                throw index_out_of_bound();
            return *(pos->data);
        }

        T & operator[](const Key &key) {
            //bound
            bool tmp = 0;
            node* pos;
            pos = tree->find(tree->root, key);
            if (pos == NULL)
                pos = tree->insert(tree->root, key, T(), NULL, NULL, tmp);
            return *(pos->data);
        }

        const T & operator[](const Key &key) const {
            //bound
            node* pos;
            pos = tree->find(tree->root, key);//这样用？？
            if (pos == NULL)
                throw index_out_of_bound();
            return pos->data;
        }

        iterator begin() {//if empty, return end
            iterator newone;
            newone.themap = this;
            if (tree->size == 0){
                newone.thenode = themax;
                return newone;
            }
            node* findnode = tree->root;
            while(findnode->lc != NULL)
                findnode = findnode->lc;
            newone.thenode = findnode;
            return newone;
        }
        const_iterator cbegin() const {
            const_iterator newone;
            newone.themap = (map*)this;
            if (tree->size == 0){
                newone.thenode = themax;
                return newone;
            }
            node* findnode = tree->root;
            if (tree->size == 0)
                return newone;
            while(findnode->lc != NULL)
                findnode = findnode->lc;
            newone.thenode = findnode;
            return newone;
        }

        iterator end() {
            iterator newone;
            newone.thenode = themax;
            newone.themap = this;
            return newone;
        }
        const_iterator cend() const {
            const_iterator newone;
            newone.thenode = themax;
            newone.themap = (map*)this;
            return newone;
        }

        bool empty() const {
            return tree->size == 0;
        }

        size_t size() const {
            return tree->size;
        }

        void clear() {
            if (tree->root != NULL)
                tree->dfsedelete(tree->root);
            tree->root = NULL;
            tree->size = 0;
        }

        pair<iterator, bool> insert(const value_type &value) {
            iterator newone;
            newone.themap = this;
            bool flag = 0;
            newone.thenode = tree->insert(tree->root, value.first, value.second, NULL, NULL, flag);
            pair<iterator, bool> newpair;
            newpair.first = newone;
            newpair.second = flag;
            return newpair;
        }

        void erase(iterator pos) {
            if (pos.thenode == NULL)
                throw invalid_iterator();
            tree->remove(*(pos.thenode->key));
        }

        size_t count(const Key &key) const {
            node* newone = tree->find(tree->root, key);
            if (newone == NULL)
                return 0;
            return 1;
        }

        iterator find(const Key &key) {
            iterator newone;
            node* anode = tree->find(tree->root, key);
            newone.thenode = anode;
            newone.themap = this;
            return newone;
        }
        const_iterator find(const Key &key) const {
            const_iterator newone;
            node* anode = tree->find(tree->root, key);
            newone.thenode = anode;
            newone.themap = (map*)this;
            return newone;
        }
    };

}

#endif
