//
//  users.h
//  junio2013
//
//  Created by Antonio Jesús Nebro Urbaneja on 15/06/13.
//  Copyright (c) 2013 Antonio Jesús Nebro Urbaneja. All rights reserved.
//

#ifndef junio2013_users_h
#define junio2013_users_h

typedef struct user {
    int   uid_           ;
    char *userName_      ;
    char *homeDirectory_ ;
    
    struct user * nextUser_ ;
    struct user * previousUser_ ;
} T_user ;

typedef struct userList {
    T_user * head_ ;
    T_user * tail_ ;
    int numberOfUsers_ ;
} T_userList;

T_user * createUser(char *name, int uid, char *dir) ;
T_userList createUserList() ;
int addUser(T_userList *, T_user*) ;
int getUid(T_userList list, char *userName) ;
int deleteUser(T_userList *list, char* userName) ;
void printUserList(T_userList list, int reverse) ;

#endif
