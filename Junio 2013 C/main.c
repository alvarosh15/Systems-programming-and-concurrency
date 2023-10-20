//
//  main.c
//  junio2013
//

#include <stdio.h>
#include "userList.h"

int main(int argc, const char * argv[])
{

    T_userList lista_de_usuarios ;
    
    lista_de_usuarios = createUserList() ;
    
    printUserList(lista_de_usuarios, 0) ;
    
    T_user* usuario = createUser("pepe", 1, "/home/pepe") ;
    addUser(&lista_de_usuarios, usuario) ;

    usuario = createUser("paco", 4, "/home/paco") ;
    addUser(&lista_de_usuarios, usuario) ;

    usuario = createUser("lola", 5, "/home/lola") ;
    addUser(&lista_de_usuarios, usuario) ;

    printUserList(lista_de_usuarios, 0) ;
    printUserList(lista_de_usuarios, 1) ;
    
    printf("El UID del usuario %s es: %d\n", "pepe", getUid(lista_de_usuarios, "pepe"));

    printf("El UID del usuario %s es: %d\n", "paco", getUid(lista_de_usuarios, "paco"));

    deleteUser(&lista_de_usuarios, "lola") ;
    
    printUserList(lista_de_usuarios, 0) ;
    printUserList(lista_de_usuarios, 1) ;
 
    usuario = createUser("martin", 5, "/home/martin") ;
    addUser(&lista_de_usuarios, usuario) ;
    printUserList(lista_de_usuarios, 0) ;

    usuario = createUser("manuel", 5, "/home/manuel") ;
    addUser(&lista_de_usuarios, usuario) ;
    printUserList(lista_de_usuarios, 0) ;
    
    usuario = createUser("paco", 15, "/home/paco") ;
    addUser(&lista_de_usuarios, usuario) ;
    printUserList(lista_de_usuarios, 0) ;


    printf("Fin del programa\n") ;

    return 0;
}

