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
  bool status //disponível ou emprestado
  User usuario;
};
typedef struct tbook Book;
//Usuário
User setUser(*User, char,char);
//
char getUser(User);
//

//Liros
Book setBook(*book, char,char, int, int, bool, User);
