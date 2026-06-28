#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// Structs
struct tuser
{
  char email[100];
  char nome[150];
};
typedef struct tuser User;
//
struct tbook
{
  char titulo[100];
  char autor[150];
  int anoPublicacao;
  int codigo;  // id unico
  bool status; // disponível(true) ou emprestado(false)
  User usuario;
};
typedef struct tbook Book;
//
struct nodeTree
{
  Book livros;
  struct nodeTree *left;
  struct nodeTree *right;
};
typedef struct nodeTree Node;
// Arvore
Node *initTree();
//
Node *creatNode(Book newBook);
//
Node *insertTree(Node *, Book);
//
Node *searchTree(Node *, int);
//
void showInOrder(Node *);
//
Node *loadTree(Node *, char *);
//
void freeNode(Node *);
// Usuarios
void setUser(User *, char *, char *);
//
char getUser(User);
//
// Livros
void setBook(Book *, char *, char *, int, int, bool, char *);
// Funções
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
// Buscas
void buscaPorCodigo(Node *, int, int *);
//
void buscarPorAutor(Node *, char *, int *);
//
int buscarUsuarioPorEmail(char *);
//
int buscarUsuarioPorNome(char *);
//
void buscarLivrosEmprestados(Node *, char *, int *);
//
void updateBook(Node *, int);
//
void updateUser(char *);
//
void regravarArquivoLivros(Node *);
//
void salvarArquivoNovo(Node *, FILE *);
//
void exclusionUser(char *);
//
Node *exclusionBook(Node *, int);
//
void lendingBook(Node *, int, char *);