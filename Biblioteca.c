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
Node *initNode()
{
  return NULL;
}
//
Node *creatNode(Book newBook)
{
  // aloca memória
  Node *novoNo = (Node *)malloc(sizeof(Node));
  // ver se é null
  if (novoNo == NULL)
  {
    printf("Erro: espaço insufiente");
    exit(1);
  }
  // atribui valor
  novoNo->livros = newBook;
  // nulifica os ponteiros
  novoNo->left = NULL;
  novoNo->right = NULL;

  return novoNo;
}
//
Node *insertTree(Node *root, Book newBook)
{
  // Verifica se é null
  if (root == NULL)
    return creatNode(newBook);
  // vai para esquerda
  if (newBook.codigo < root->livros.codigo)
  {
    root->left = insertTree(root->left, newBook);
  }
  else if (newBook.codigo > root->livros.codigo)
  {
    root->right = insertTree(root->right, newBook);
  }
  else
  {
    printf("Código já cadastrado no sistema!");
  }
  return root;
}
//
Node *searchTree(Node *root, int code)
{
  if (root == NULL)
    return NULL;
  if (code < root->livros.codigo)
  {
    return searchTree(root->left, code);
  }
  else if (code > root->livros.codigo)
  {
    return searchTree(root->right, code);
  }
  else
    return root;
}
//
void showInOrder(Node *root)
{
  if (root == NULL)
    return;
  showInOrder(root->left);
  printf("%s\n", root->livros.titulo);
  showInOrder(root->right);
}
//
Node *loadTree(Node *root, char *nomeArquivo)
{
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
  while (fscanf(pont_arq, "%[^,],%[^,],%d,%d,%d,%[^\n]\n", livro.titulo, livro.autor, &livro.anoPublicacao, &livro.codigo, &statusLT, livro.usuario.email) == 6)
  {
    livro.status = (statusLT == 1);
    root = insertTree(root, livro);
  }
  fclose(pont_arq);
  printf("Dados Carregados com sucesso!");
  return root;
  // https://pt.stackoverflow.com/questions/42658/ler-uma-string-separada-por-v%C3%ADrgula
}
//
void freeNode(Node *root)
{
  if (root == NULL)
    return;
  freeNode(root->left);
  freeNode(root->right);
  free(root);
  printf("Memória limpa!\n");
}
//
void buscarPorAutor(Node *root, char *buscaAutor, int *encontrou)
{
  if (root == NULL)
    return;

  buscarPorAutor(root->left, buscaAutor, encontrou);

  if (strcmp(root->livros.autor, buscaAutor) == 0)
  {
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
void buscaPorCodigo(Node *root, int codBusca, int *encontrou)
{
  Node *resultado = searchTree(root, codBusca);

  if (resultado != NULL)
  {
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
int buscarUsuarioPorEmail(char *emailBusca)
{
  FILE *pnt_arq = fopen("usuarios.txt", "r");
  if (pnt_arq == NULL)
  {
    return 0; // Se o arquivo não existe, nenhum usuário está cadastrado
  }

  char nome[150], email[100];
  int encontrou = 0;

  while (fscanf(pnt_arq, "%[^,],%[^\n]\n", nome, email) == 2)
  {
    if (strcmp(email, emailBusca) == 0)
    {
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
int buscarUsuarioPorNome(char *nomeBusca)
{
  FILE *pnt_arq = fopen("usuarios.txt", "r");
  if (pnt_arq == NULL)
  {
    return 0;
  }

  char nome[150], email[100];
  int encontrou = 0;

  while (fscanf(pnt_arq, "%[^,],%[^\n]\n", nome, email) == 2)
  {
    if (strcmp(nome, nomeBusca) == 0)
    {
      printf("\n=== Usuário Encontrado ===ch");
      printf("\nNome: %s", nome);
      printf("\nE-mail: %s\n", email);
      encontrou = 1;
    }
  }

  fclose(pnt_arq);
  return encontrou;
}
//
void buscarLivrosEmprestados(Node *root, char *emailBusca, int *encontrou)
{
  if (root == NULL)
    return;

  buscarLivrosEmprestados(root->left, emailBusca, encontrou);

  if (strcmp(root->livros.usuario.email, emailBusca) == 0 && root->livros.status == false)
  {
    printf("\n- Título: %s (Código: %d)", root->livros.titulo, root->livros.codigo);
    *encontrou = 1;
  }
  buscarLivrosEmprestados(root->right, emailBusca, encontrou);
}
//
void updateBook(Node *root, int id)
{
  int op = -1;
  if (root == NULL)
  {
    printf("A árvore está vazia!\n");
    return;
  }

  Node *livro = searchTree(root, id);

  if (livro == NULL)
  {
    printf("Livro não encontrado!\n");
  }

  else
  {
    printf("\n--- Atualizando Livro: %s ---\n", livro->livros.titulo);
    printf("Atualizar:\n1- Titulo\n2- Autor\n3- Ano da publicação\n4- Todos os dados\nDigite:");
    scanf("%d", &op);
    while (getchar() != '\n' && getchar() != EOF)
      ;
    if (op == 1)
    {
      printf("Digite o novo título: ");
      fgets(livro->livros.titulo, sizeof(livro->livros.titulo), stdin);
      linhaLimpa(livro->livros.titulo);
      printf("Titulo atualizado com sucesso!");
    }
    else if (op == 2)
    {
      printf("Digite o novo autor: ");
      fgets(livro->livros.autor, sizeof(livro->livros.autor), stdin);
      linhaLimpa(livro->livros.autor);
      printf("Autor atualizado com sucesso!");
    }
    else if (op == 3)
    {
      printf("Digite o novo ano de publicação: ");
      scanf("%d", &livro->livros.anoPublicacao);
      while (getchar() != '\n' && getchar() != EOF)
        ;
      printf("Ano da publicação atualizado com sucesso!");
    }
    else if (op == 4)
    {
      printf("\n--- Atualizando Livro: %s ---\n", livro->livros.titulo);

      printf("Digite o novo título: ");
      fgets(livro->livros.titulo, sizeof(livro->livros.titulo), stdin);
      linhaLimpa(livro->livros.titulo);

      printf("Digite o novo autor: ");
      fgets(livro->livros.autor, sizeof(livro->livros.autor), stdin);
      linhaLimpa(livro->livros.autor);

      printf("Digite o novo ano de publicação: ");
      scanf("%d", &livro->livros.anoPublicacao);
      while (getchar() != '\n' && getchar() != EOF)
        ;

      printf("Livro atualizado com sucesso!\n");
    }
    else
    {
      printf("Erro: Opção inválida");
    }
  }
}
//
void updateUser(char *emailBusca)
{
  FILE *arqOriginal = fopen("usuarios.txt", "r");
  FILE *arqTemp = fopen("temp.txt", "w");

  if (arqOriginal == NULL || arqTemp == NULL)
  {
    printf("Erro ao acessar os arquivos de usuário.\n");
    return;
  }

  char nome[150], email[100];
  int encontrou = 0;

  while (fscanf(arqOriginal, "%[^,],%[^\n]\n", nome, email) == 2)
  {
    if (strcmp(email, emailBusca) == 0)
    {
      encontrou = 1;
      char novoNome[150];

      printf("\n--- Atualizando Usuário ---\n");
      printf("E-mail: %s\n", email);
      printf("Digite o novo nome: ");
      fgets(novoNome, sizeof(novoNome), stdin);
      linhaLimpa(novoNome);

      fprintf(arqTemp, "%s,%s\n", novoNome, email);
      printf("Usuário atualizado com sucesso!\n");
    }
    else
    {
      fprintf(arqTemp, "%s,%s\n", nome, email);
    }
  }

  fclose(arqOriginal);
  fclose(arqTemp);

  if (encontrou == 0)
  {
    printf("Usuário não encontrado!\n");
    remove("temp.txt"); // remove() peguei com IA, tava usando fclose só
  }
  else
  {
    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");
  }
}
//
void salvarArquivoNovo(Node *root, FILE *arquivo)
{
  if (root == NULL)
    return;

  salvarArquivoNovo(root->left, arquivo);
  fprintf(arquivo, "%s,%s,%d,%d,%d,%s\n",
          root->livros.titulo,
          root->livros.autor,
          root->livros.anoPublicacao,
          root->livros.codigo,
          root->livros.status ? 1 : 0,
          root->livros.usuario.email);
  salvarArquivoNovo(root->right, arquivo);
}
//
void regravarArquivoLivros(Node *root)
{
  FILE *arquivo = fopen("livros.txt", "w");

  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo para salvar os dados!\n");
    return;
  }
  salvarArquivoNovo(root, arquivo);

  fclose(arquivo);
  printf("Dados salvos com sucesso!\n");
}
//
void exclusionUser(char *emailBusca){
  FILE *arqOriginal = fopen("usuarios.txt", "r");
  FILE *arqTemp = fopen("temp.txt", "w");

  if (arqOriginal == NULL || arqTemp == NULL)
  {
    printf("Erro ao acessar os arquivos de usuário.\n");
    return;
  }

  char nome[150], email[100];
  int encontrou = 0;

  while (fscanf(arqOriginal, "%[^,],%[^\n]\n", nome, email) == 2)
  {
    if (strcmp(email, emailBusca) == 0)
    {
      encontrou = 1;
      printf("Usuário excluído com sucesso!");
    }
    else
    {
      fprintf(arqTemp, "%s,%s\n", nome, email);
    }
  }

  fclose(arqOriginal);
  fclose(arqTemp);

  if (encontrou == 0)
  {
    printf("Usuário não encontrado!\n");
    remove("temp.txt"); // remove() peguei com IA, tava usando fclose só
  }
  else
  {
    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");
  }
}
//
Node *exclusionBook(Node *root, int id) {
  if (root == NULL) {
    return root; 
  }
  // verifica se o id é menor
  if (id < root->livros.codigo) {
    root->left = exclusionBook(root->left, id);
  }   // verifica se o id é maior
  else if (id > root->livros.codigo) {
    root->right = exclusionBook(root->right, id);
  } 
  else { // ele encontrou, agora verifica se o da esquerda é nulo
    if (root->left == NULL) {
      Node *temp = root->right;
      free(root);
      return temp; // esquerda nula, ele exclui o nó e retorna o da direita
    } 
    else if (root->right == NULL) {
      Node *temp = root->left;
      free(root);
      return temp; // direita nula, ele exclui o nó e retorna o da esquerda
    }

    Node *temp = root->right; //vai para a direita
    while (temp->left != NULL) {
      temp = temp->left;  // percorre a esquerda
    }

    root->livros = temp->livros; //duplico o nó, jogando o temporário no root

    root->right = exclusionBook(root->right, temp->livros.codigo); // agora desce na direita e apaga o de baixo
  }
  return root;
}
