#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct tuser {
  char email[100];
  char nome[150];
};
typedef struct tuser User;

struct tbook{
  char titulo[100];
  char autor[150];
  int anoPublicacao;
  int codigo; //id unico
  bool status; //disponível(true) ou emprestado(false)
  User usuario;
};
typedef struct tbook Book;
//
//Usuarios
void setUser(User *, char*,char*);
//
char getUser(User);
//
//Livros
void setBook(Book *, char*,char*, int, int, bool, char*);

//Funções
void linhaLimpa(char *);
//
void salvarLivro(Book *);
//
void salvarUsuario(User *);
//
void lerArquivos(char *);
//
void cadastraUsuario(User *);
//
void cadastraLivro(Book *);
