#include "Biblioteca.h"
// SETTERS
void setUser(User *usuario, char *nome, char *email){
  strcpy(usuario->nome, nome);
  strcpy(usuario->email, email);
}

void setBook(Book *livro, char *titulo, char *autor, int anoPublicacao, int codigo, bool status, char *usuarioEmail){
  strcpy(livro->titulo,titulo);
  strcpy(livro->autor,autor);
  livro->anoPublicacao = anoPublicacao;
  livro->codigo = codigo;
  livro->status = status;
  strcpy(livro->usuario.email,usuarioEmail);
}

//Métodos
void linhaLimpa(char *linhas){
  linhas[strcspn(linhas, "\n")] = 0;
  //https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
}
//
void salvarLivro(Book *livro){
  FILE *pnt_arq = fopen("livros.txt", "a");
  if (pnt_arq == NULL)
  {
    printf("Erro ao abrir livros salvos");
    return;
  }
  linhaLimpa(livro->titulo);
  linhaLimpa(livro->autor);
  linhaLimpa(livro->usuario.email);

  fprintf(pnt_arq, "%s,%s,%d,%d,%d,%s\n", livro->titulo,livro->autor,livro->anoPublicacao,livro->codigo,livro->status?1:0,livro->usuario.email);
  fclose(pnt_arq);
  //https://linguagemc.com.br/arquivos-em-c-categoria-usando-arquivos/
}
//
void salvarUsuario(User *usuario){
  FILE *pnt_arq = fopen("usuarios.txt","a");
  if (pnt_arq == NULL)
  {
    printf("Erro ao abrir usuários salvos");
    return;
  }
  linhaLimpa(usuario->nome);
  linhaLimpa(usuario->email);

  fprintf(pnt_arq, "%s,%s\n", usuario->nome, usuario->email);
  fclose(pnt_arq);
  //https://linguagemc.com.br/arquivos-em-c-categoria-usando-arquivos/
}
//
void lerArquivos(char *nomeArquivo) {
  FILE *pont_arq;
  char c;

  pont_arq = fopen(strcat(nomeArquivo,".txt"), "r");
  if (pont_arq == NULL) {
    printf("Erro ao tentar abrir o arquivo %s!\n", nomeArquivo);
    return;
  }

  printf("\nDados do arquivo: %s:\n", nomeArquivo); 

  while ((c = fgetc(pont_arq)) != EOF) { //vai fazer a leitura dos caracteres enquanto não for o final do arquivo
      printf("%c", c);        
  }
  printf("\n");
  fclose(pont_arq);
  //https://linguagemc.com.br/arquivos-em-c-categoria-usando-arquivos/
}

void cadastraUsuario(User *usuario){
    printf("\nCadastro de Usuário:\n");
    printf("Digite o nome do usuário\n");
    fgets(usuario->nome, sizeof(usuario->nome),stdin);
    //
    printf("Digite o e-mail do usuário\n");
    fgets(usuario->email, sizeof(usuario->email),stdin);
    //
    setUser(usuario, usuario->nome, usuario->email);
    //
    salvarUsuario(usuario);
    //
    printf("Usuário salvo com sucesso!");
}

void cadastraLivro(Book *livro){
    printf("\nCadastro de Livro:\n");
    printf("Digite o titulo: \n");
    fgets(livro->titulo, sizeof(livro->titulo), stdin);
    printf("Digite o autor:\n");
    fgets(livro->autor, sizeof(livro->autor), stdin);
    printf("Digite o ano da publicação:\n");
    scanf("%d", &livro->anoPublicacao);
    printf("Digite o código:\n");
    scanf("%d",&livro->codigo);
    while (getchar() != '\n' && getchar() != EOF);
    printf("Digite o email do usuário:\n");
    fgets(livro->usuario.email,sizeof(livro->usuario.email),stdin);
    livro->status = true;
    //
    setBook(livro,livro->titulo,livro->autor,livro->anoPublicacao,livro->codigo,livro->status,livro->usuario.email);
    //
    salvarLivro(livro);
    //
    printf("\nLivro cadastrado com sucesso!\n");
}
