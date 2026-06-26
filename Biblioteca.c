#include <stdio.h>
#include "Biblioteca.h"

User setUser(*User usuario, chat nome, char email){
  usuario->nome = nome;
  usuario->email = email;
}
 
Book setBook(*book livro, char titulo, char autor, int anoPublicacao, int codigo, bool status, User usuario){
  livro->titulo = titulo;
  livro->autor = autor;
  livro->anoPublicacao = anoPublicacao;
  livro->codigo = codigo;
  livro->status = status;
  livro->usuario = usuario;
}
