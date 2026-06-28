#include "Biblioteca.h"

int main()
{
  // carrega o arquivo quando abre o sistema
  Node *root = NULL;
  root = loadTree(root, "livros");
  //
  User usuario;
  //
  Book livro;
  //
  int op = -1, option = -1, alt = -1;

  while (op != 0)
  {
    printf("\n====== BIBLIOTECA ======\n");
    printf("Digite a opção desejada:\n1- Cadastro\n2- Consulta\n3- Atualização\n0- Sair\n");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
      // cadastro
      while (option != 0)
      {
        printf("\n====== Cadastro ======\n");
        printf("1 - Livro\n2 - Usuário\n0 - Voltar\n");
        scanf("%d", &option);
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
          ; // Peguei com IA porque não conseguia limpar o buffer
        switch (option)
        {
        // MENU CADASTRO
        case 1:
          cadastraLivro(&livro);
          root = insertTree(root, livro);
          break;
        case 2:
          cadastraUsuario(&usuario);
          break;
        case 0:
          break; // Sai do switch interno para o while poder encerrar
        }
      } // AQUI fecha o while (option != 0)
      break; // AQUI é o break verdadeiro do 'case 1' do menu principal!
    case 2:
      // consulta
      {
        int opcao = -1;
        while (opcao != 0)
        {
          printf("\n====== Consulta ======\n");
          printf("1 - Livros\n2 - Usuários\n3 - Empréstimos\n0 - Voltar\nDigite: ");
          scanf("%d", &opcao);
          while (getchar() != '\n' && getchar() != EOF)
            ;

          if (opcao == 1)
          {
            int subOpcaoBook;
            printf("\n====== Consulta de Livros ======\n");
            printf("1 - Por Código\n2 - Por Autor\n0 - Voltar\nDigite: ");
            scanf("%d", &subOpcaoBook);
            while (getchar() != '\n' && getchar() != EOF)
              ;

            if (subOpcaoBook == 1)
            {
              int codBusca;
              printf("Digite o código do livro: ");
              scanf("%d", &codBusca);
              while (getchar() != '\n' && getchar() != EOF)
                ;
              //
              int encontrou = 0;
              buscaPorCodigo(root, codBusca, &encontrou);
              if (encontrou == 0)
              {
                printf("Livro não encontrado\n");
              }
            }
            else if (subOpcaoBook == 2)
            {
              char autorBusca[150];
              printf("Digite o nome do autor: ");
              fgets(autorBusca, sizeof(autorBusca), stdin);
              linhaLimpa(autorBusca);
              //
              int encontrou = 0;
              buscarPorAutor(root, autorBusca, &encontrou);
              if (encontrou == 0)
              {
                printf("Livro não encontrado\n");
              }
            }
            else if (subOpcaoBook == 0)
            {
              continue;
            }
            else
            {
              printf("Opção inválida!\n");
            }
          }
          else if (opcao == 2)
          {
            int subOpcaoUser;
            printf("\n====== Consulta de Usuários ======\n");
            printf("1 - Por E-mail\n2 - Por Nome\n0 - Voltar\nDigite: ");
            scanf("%d", &subOpcaoUser);
            while (getchar() != '\n' && getchar() != EOF)
              ;

            if (subOpcaoUser == 1)
            {
              char emailBusca[100];
              printf("Digite o e-mail do usuário: ");
              fgets(emailBusca, sizeof(emailBusca), stdin);
              linhaLimpa(emailBusca);

              if (buscarUsuarioPorEmail(emailBusca) == 0)
              {
                printf("Usuário não cadastrado\n");
              }
            }
            else if (subOpcaoUser == 2)
            {
              char nomeBusca[150];
              printf("Digite o nome do usuário: ");
              fgets(nomeBusca, sizeof(nomeBusca), stdin);
              linhaLimpa(nomeBusca);

              if (buscarUsuarioPorNome(nomeBusca) == 0)
              {
                printf("Usuário não cadastrado\n");
              }
            }
            else if (subOpcaoUser == 0)
            {
              continue;
            }
            else
            {
              printf("Opção inválida!\n");
            }
          }
          else if (opcao == 3)
          {
            {
              char emailBusca[100];
              printf("\n====== Consulta de Empréstimos ======\n");
              printf("Digite o e-mail do usuário: ");
              fgets(emailBusca, sizeof(emailBusca), stdin);
              linhaLimpa(emailBusca);

              if (buscarUsuarioPorEmail(emailBusca) == 1)
              {
                int encontrou = 0;
                printf("\n=== Livros emprestados ===");
                buscarLivrosEmprestados(root, emailBusca, &encontrou);

                if (encontrou == 0)
                {
                  printf("\nNenhum livro em empréstimo no momento.\n");
                }
                printf("\n");
              }
              else
              {
                printf("Usuário não cadastrado no sistema.\n");
              }
            }
          }
          else if (opcao == 0)
          {
            break;
          }
          else
          {
            printf("Opção inválida!\n");
          }
        }
      }
      break;
    case 3:
      alt = -1;
      // atualização
      int idBook;
      char email[150];
      while (alt != 0)
      {
        printf("\n=== Atualização de dados ===\n1- Livros\n2- Usuários\n0 - Voltar\nDigite:");
        scanf("%d", &alt);
        while (getchar() != '\n' && getchar() != EOF)
          ;
        switch (alt)
        {
        case 1:
          printf("Digite o ID do livro a ser atualizado:");
          scanf("%d", &idBook);
          while (getchar() != '\n' && getchar() != EOF)
            ;
          updateBook(root, idBook);
          break;
        case 2:
          printf("Digite o e-mail do usuário a ser atualizado:");
          fgets(email, sizeof(email), stdin);
          linhaLimpa(email);
          updateUser(email);
          break;
        case 0:
          break;
        }
      }
      break;
    case 4:
      // exclusão
      break;
    case 5:
      // empréstimo
      break;
    case 6:
      // devolução
      break;
    case 0:
      printf("Sistema encerrado!\n");
      regravarArquivoLivros(root);
      freeNode(root);
      exit(1);
    }
  }
  return 0;
}