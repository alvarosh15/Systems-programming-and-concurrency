#include <stdio.h>
#include <stdlib.h>
#include "userList.h"

T_user * createUser(char *name, int uid, char *dir) {
    T_user * user = malloc(sizeof(struct user));
    user -> uid_ = uid;
    user -> userName_ = *name;  
    user -> homeDirectory_ = *dir;
}

T_userList createUserList() {
    T_userList * lista = malloc(sizeof(struct userList));
    lista -> head_ = NULL; 
    lista -> tail_ = NULL;
    lista -> numberOfUsers_ = 0;
    return *lista;
}

int addUser(T_userList * lista, T_user* usuario) {
    int ok = 0;

    if(lista == NULL) {
        lista -> head_ = usuario;
        lista -> tail_ = NULL;
        lista -> numberOfUsers_ = 1;
    } else {
        int nombre = 0;
        int uid = 0;
        T_user * ptr = lista -> head_;
        while(nombre == 0 && uid == 0 && ptr -> previousUser_ != NULL) {
            if(ptr -> userName_ == usuario -> userName_) {
                nombre = 1;
            } 
            if(ptr -> uid_ == usuario -> uid_) {
                uid = 1;
            } 
            ptr = ptr -> previousUser_;
        }
    }

    return ok;
}

int getUid(T_userList list, char *userName) {
    int uid = -1;

    T_userList ptr = *list;
    while(uid == -1 && ptr -> tail_ != NULL) {
        if(ptr -> userName_ == *userName) {
            uid = ptr -> uid_;
        } 
        ptr = ptr -> previousUser_;
    }

    return uid;
}
int deleteUser(T_userList *list, char* userName) ;
void printUserList(T_userList list, int reverse) ;
