#include "Biblioteca.h"
// SETTERS
void setUser(User *usuario, char *nome, char *email)
{
  strcpy(usuario->nome, nome);
  strcpy(usuario->email, email);
}

void setBook(Book *livro, char *titulo, char *autor, int anoPublicacao, int codigo, bool status, char *usuarioEmail)
{
  strcpy(livro->titulo, titulo);
  strcpy(livro->autor, autor);
  livro->anoPublicacao = anoPublicacao;
  livro->codigo = codigo;
  livro->status = status;
  strcpy(livro->usuario.email, usuarioEmail);
}

// Métodos
void linhaLimpa(char *linhas)
{
  linhas[strcspn(linhas, "\n")] = 0;
  // https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
}
//
void salvarLivro(Book *livro)
{
  FILE *pnt_arq = fopen("livros.txt", "a");
  if (pnt_arq == NULL)
  {
    printf("Erro ao abrir livros salvos");
    return;
  }
  linhaLimpa(livro->titulo);
  linhaLimpa(livro->autor);
  linhaLimpa(livro->usuario.email);

  fprintf(pnt_arq, "%s,%s,%d,%d,%d,%s\n", livro->titulo, livro->autor, livro->anoPublicacao, livro->codigo, livro->status ? 1 : 0, livro->usuario.email);
  fclose(pnt_arq);
  // https://linguagemc.com.br/arquivos-em-c-categoria-usando-arquivos/
}
//
void salvarUsuario(User *usuario)
{
  FILE *pnt_arq = fopen("usuarios.txt", "a");
  if (pnt_arq == NULL)
  {
    printf("Erro ao abrir usuários salvos");
    return;
  }
  linhaLimpa(usuario->nome);
  linhaLimpa(usuario->email);

  fprintf(pnt_arq, "%s,%s\n", usuario->nome, usuario->email);
  fclose(pnt_arq);
  // https://linguagemc.com.br/arquivos-em-c-categoria-usando-arquivos/
}

void cadastraUsuario(User *usuario)
{
  printf("\nCadastro de Usuário:\n");
  printf("Digite o nome do usuário\n");
  fgets(usuario->nome, sizeof(usuario->nome), stdin);
  //
  printf("Digite o e-mail do usuário\n");
  fgets(usuario->email, sizeof(usuario->email), stdin);
  //
  setUser(usuario, usuario->nome, usuario->email);
  //
  salvarUsuario(usuario);
  //
  printf("Usuário salvo com sucesso!");
}

void cadastraLivro(Book *livro)
{
  printf("\nCadastro de Livro:\n");
  printf("Digite o titulo: \n");
  fgets(livro->titulo, sizeof(livro->titulo), stdin);
  printf("Digite o autor:\n");
  fgets(livro->autor, sizeof(livro->autor), stdin);
  printf("Digite o ano da publicação:\n");
  scanf("%d", &livro->anoPublicacao);
  printf("Digite o código:\n");
  scanf("%d", &livro->codigo);
  while (getchar() != '\n' && getchar() != EOF)
  ;
  printf("Digite o email do usuário:\n");
  fgets(livro->usuario.email, sizeof(livro->usuario.email), stdin);
  livro->status = true;
  //
  setBook(livro, livro->titulo, livro->autor, livro->anoPublicacao, livro->codigo, livro->status, livro->usuario.email);
  //
  salvarLivro(livro);
  //
  printf("\nLivro cadastrado com sucesso!\n");
}

void lerArquivos(char *nomeArquivo)
{
  FILE *pont_arq;
  char c;

  pont_arq = fopen(strcat(nomeArquivo, ".txt"), "r");
  if (pont_arq == NULL)
  {
    printf("Erro ao tentar abrir o arquivo %s!\n", nomeArquivo);
    return;
  }

  printf("\nDados do arquivo: %s:\n", nomeArquivo);

  while ((c = fgetc(pont_arq)) != EOF)
  { // vai fazer a leitura dos caracteres enquanto não for o final do arquivo
    printf("%c", c);
  }
  printf("\n");
  fclose(pont_arq);
  // https://linguagemc.com.br/arquivos-em-c-categoria-usando-arquivos/
}
// essa aqui provavelmente vou apagar
Node *initNode(){
  return NULL;
}
//
Node *creatNode(Book newBook){
  //aloca memória
  Node *novoNo = (Node *)malloc(sizeof(Node));
  //ver se é null
  if (novoNo == NULL){
    printf("Erro: espaço insufiente");
    exit(1);
  }
  //atribui valor
  novoNo->livros = newBook;
  //nulifica os ponteiros
  novoNo->left = NULL;
  novoNo->right = NULL;
  
  return novoNo;
}
//
Node *insertTree(Node *root, Book newBook){
  //Verifica se é null
  if (root == NULL) return creatNode(newBook);
  //vai para esquerda
  if (newBook.codigo < root->livros.codigo)
  {
    root->left = insertTree(root->left, newBook);
  }else if(newBook.codigo > root->livros.codigo){
    root->right = insertTree(root->right, newBook);
  }else{
    printf("Código já cadastrado no sistema!");
  }
  return root;
}
//
Node *searchTree(Node *root, int code){
  if (root == NULL) return NULL;
  if (code < root->livros.codigo)
  {
    return searchTree(root->left, code);
  }else if(code > root->livros.codigo){
    return searchTree(root->right, code);
  }
  else return root;
}
//
void showInOrder(Node *root){
  if (root==NULL) return;
  showInOrder(root->left);
  printf( "%s\n",root->livros.titulo);
  showInOrder(root->right);
}
//
Node *loadTree(Node *root, char *nomeArquivo){
  FILE *pont_arq;

  char nomeCompleto[100];
  
  strcpy(nomeCompleto, nomeArquivo);
  
  strcat(nomeCompleto, ".txt");
  pont_arq = fopen(nomeCompleto, "r");
  if (pont_arq == NULL)
  {
    printf("Erro: Carregamento do arquivo %s falhou!\n", nomeArquivo);
    printf("Iniciando com arvore vazia!\n");
    return root;
  }
  Book livro;
  int statusLT;
  
  // vai fazer a leitura dos caracteres até encontrar \n no final
  while (fscanf(pont_arq, "%[^,],%[^,],%d,%d,%d,%[^\n]\n", livro.titulo, livro.autor, &livro.anoPublicacao, &livro.codigo, &statusLT, livro.usuario.email) == 6) {
      livro.status = (statusLT == 1);
      root = insertTree(root, livro);
  }
  fclose(pont_arq);
  printf("Dados Carregados com sucesso!");
  return root;
  //https://pt.stackoverflow.com/questions/42658/ler-uma-string-separada-por-v%C3%ADrgula
} 
//
void freeNode(Node *root){
  if (root==NULL) return;
  freeNode(root->left);
  freeNode(root->right);
  free(root);
  printf("Memória limpa!\n");
}
//
void buscarPorAutor(Node *root, char *buscaAutor, int *encontrou) {
  if (root == NULL) return;

  buscarPorAutor(root->left, buscaAutor, encontrou);

  if (strcmp(root->livros.autor, buscaAutor) == 0) {
      printf("\n=== Livro Encontrado ===");
      printf("\nTítulo: %s", root->livros.titulo);
      printf("\nAutor: %s", root->livros.autor);
      printf("\nCódigo: %d", root->livros.codigo);
      printf("\nStatus: %s\n", root->livros.status ? "Disponível" : "Emprestado");
      *encontrou = 1;
  }
  buscarPorAutor(root->right, buscaAutor, encontrou);
}
//
void buscaPorCodigo(Node *root, int codBusca, int *encontrou){
  Node *resultado = searchTree(root, codBusca); 
    
    if (resultado != NULL) {
      printf("\n=== Livro Encontrado ===");
      printf("\nTítulo: %s", resultado->livros.titulo);
      printf("\nAutor: %s", resultado->livros.autor);
      printf("\nAno: %d", resultado->livros.anoPublicacao);
      printf("\nCódigo: %d", resultado->livros.codigo);
      printf("\nStatus: %s\n", resultado->livros.status ? "Disponível" : "Emprestado");
      *encontrou = 1;
    }
}
//
int buscarUsuarioPorEmail(char *emailBusca){
  FILE *pnt_arq = fopen("usuarios.txt", "r");
  if (pnt_arq == NULL) {
      return 0; // Se o arquivo não existe, nenhum usuário está cadastrado
  }

  char nome[150], email[100];
  int encontrou = 0;

  while (fscanf(pnt_arq, "%[^,],%[^\n]\n", nome, email) == 2) {
      if (strcmp(email, emailBusca) == 0) {
          printf("\n=== Usuário Encontrado ===");
          printf("\nNome: %s", nome);
          printf("\nE-mail: %s\n", email);
          encontrou = 1;
          break;
      }
  }
  
  fclose(pnt_arq);
  return encontrou;
}
//
int buscarUsuarioPorNome(char *nomeBusca){
  FILE *pnt_arq = fopen("usuarios.txt", "r");
  if (pnt_arq == NULL) {
      return 0;
  }

  char nome[150], email[100];
  int encontrou = 0;

  while (fscanf(pnt_arq, "%[^,],%[^\n]\n", nome, email) == 2) {
      if (strcmp(nome, nomeBusca) == 0) {
          printf("\n=== Usuário Encontrado ===ch");
          printf("\nNome: %s", nome);
          printf("\nE-mail: %s\n", email);
          encontrou = 1;
      }
  }

  fclose(pnt_arq);
  return encontrou;
}