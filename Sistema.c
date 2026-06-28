#include "Biblioteca.h"

int main (){
  User usuario;
  //
  Book livro;
  //
  int op, option;

  while (op!= 0) {
    printf("\n====== BIBLIOTECA ======\n");
    printf("Digite a opção desejada:\n1- Cadastro\n2- Consulta\n0- Sair\n");
    scanf("%d", &op);
    switch (op){
      case 1:
      //cadastro
        option = -1;
        while (option != 0)
        {
          printf("\n====== Cadastro ======\n");
          printf("1 - Livro\n2 - Usuário\n0 - Voltar\n");
          scanf("%d", &option);
          while (getchar() != '\n' && getchar() != EOF); //Peguei com IA porque não conseguia limpar o buffer
          switch (option)
          {
          // MENU CADASTRO
          case 1:
            cadastraLivro(&livro);
            break;
          case 2:
          cadastraUsuario(&usuario);
        }
        break;
        
      case 2:
        //consulta
        { 
          int escolha;
          printf("\n====== Consulta ======\n");
          printf("Para listar os livros Digite 1\nPara listar os usuários digite 2\nDigite: ");
          scanf("%d", &escolha);
          while (getchar() != '\n' && getchar() != EOF); 
          if (escolha == 1) {
            char books[50] = "livros";
            lerArquivos(books);
          } else if (escolha == 2) {
            char names[50] = "usuarios";
            lerArquivos(names);
          } else {
            printf("Opção inválida!\n");
          }
        }
        break;
      case 3:
        //atualização
      case 4:
        //exclusão
      case 5:
        //empréstimo
      case 6:
        //devolução
      case 0:
        exit(1);

    }
  }


  }


  return 0;
}
