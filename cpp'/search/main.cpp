#include <iostream>
using namespace std;
class Compare{
public:
    bool operator()(int a, int b){
            return a<b;
    }
};
struct node{
    int key;
    node* lc;
    node* rc;
    node* lkey;
    node* hkey;
    node(){
        lc = NULL;
        rc = NULL;
        lkey = NULL;
        hkey = NULL;
    }

};
 class searchcls{
        public:
            Compare cmp;
            node* root;
            int size;
            node* insert(node* & now, int key, node* low, node* high, bool &flag){ // and!!
                size++;// ++ when insert success? and here increase when depth increase.
                if (now == NULL){
                    node* tem = new node;
                    tem->key = key;
                    tem->hkey = tem->lkey = NULL;
                    now = tem;
                    flag = 1;
                    return tem;
                }
                if (cmp(key, now->key)){
                    if (now->lc == NULL){
                        node* tem = new node;
                        tem->key = key;
                        tem->lkey = low;
                        tem->hkey = now;
                        now->lc = tem;
                        now->lkey = tem;
                        flag = 1;
                        return tem;
                    }
                    else
                        insert(now->lc, key, low, now, flag);

                }
                else if (cmp(now->key, key)){
                    if (now->rc == NULL){
                        node* tem = new node;
                        tem->key = key;
                        tem->lkey = now;
                        tem->hkey = high;
                        now->rc = tem;
                        now->hkey = tem;
                        return tem;
                    }
                    else
                        insert (now->rc, key, now, high, flag);
                }
                else
                    return now;
            }
            node* find(node* now, int key){ //modified!
                if (!cmp(now->key, key) && !cmp(key, now->key))
                    return now;
                else if (now->lc != NULL && cmp(key, now->key))
                    return find(now->lc, key);//return!
                else if(now->rc != NULL)
                    return find(now->rc, key);
                else return NULL;
//                if (!cmp(key, now->key) && !cmp(now->key, key) && now->lc == NULL && now->rc == NULL)//????
//                    return NULL;
            }
            void remove(int key){
                node* tmp = root;
                remove(tmp, key);
            }

            void remove(node* &now, int key){
                if (!cmp(now->key, key) && !cmp(key, now->key)){
                    if (now->lc != NULL && now->rc != NULL){
                        node* tem = now->rc;
                        while(tem->lc != NULL)
                            tem = tem->lc;
                        now->key = tem->key;
                        remove(now->rc, now->key);
                    }
                    else{
                        node* old = now;
//                        old->lkey->hkey = old->hkey;
//                        old->hkey->lkey = old->lkey;
                        if(old -> lkey != NULL){
                            old->lkey->hkey = old->hkey;
                        }
                        if(old -> hkey != NULL){
                            old -> hkey->lkey = old -> lkey;
                        }
                        now = (now->lc != NULL)? now->lc : now->rc;
                        delete old;
                        size--;
                    }
                }
                else if (cmp(key, now->key)) // else if
                    remove(now->lc, key);
                else
                    remove(now->rc, key);
            }

            void dfsadd(node* now, node* model){
                if (model->lc != NULL){
                    size++;
                    node* newnode = new node;
                    newnode->key = model->lc->key;
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
                    size++;
                    node* newnode = new node;
                    newnode->key = model->rc->key;
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

            searchcls(){
                size = 0;
                root = NULL;
            }

            searchcls (const searchcls &other){
                size = other.size;
                node* model = other.root;
                node* root = new node;
                root->key = model->key;
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

            ~searchcls(){
                if (root != NULL)
                    dfsedelete(root);
                size = 0;//new
            }
            void travers(node* root){
                if(root->lc != NULL){
                    travers(root->lc);
                }
                cerr<<root->key<<'\t';
                if(root->rc != NULL){
                    travers(root->rc);
                }
            }

        };

int main() {
    searchcls* a = new searchcls;
    bool flag = false;
    a->insert(a->root, 1, NULL, NULL, flag);
    flag = false;
    cerr<<"size: " <<a->size<<endl;
    a->insert(a->root, 15, NULL, NULL, flag);

    cerr<<"size: " <<a->size<<endl;
    flag = false;
    a->insert(a->root, 9, NULL, NULL, flag);

    cerr<<"size: " <<a->size<<endl;
    flag = false;
    a->insert(a->root, 23, NULL, NULL, flag);
    flag = false;
    a->insert(a->root, 0, NULL, NULL, flag);

    a->travers(a->root);
    cerr<<endl<<flag<<endl;

    flag = false;
    a->insert(a->root, 0, NULL, NULL, flag);

    a->travers(a->root);
    cerr<<endl<<flag<<endl;
    cerr<<"size: " <<a->size<<endl;
    a->remove(15);
    a->travers(a->root);
    cerr<<"size: " <<a->size<<endl;

    cerr<<endl;
    node* res = a->find(a->root, 23);
    cerr<<res<<endl;
    cerr<<res->key<<endl;
    res = a->find(a->root, 5);
    cerr<<res<<endl;

    searchcls b(*a);
    delete a;
    cerr<<endl;
    res = b.find(a->root, 23);
    cerr<<res<<endl;
    cerr<<res->key<<endl;
    res = b.find(a->root, 5);
    cerr<<res<<endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}