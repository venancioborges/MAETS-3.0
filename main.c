#include "jogo.h"

void menu() {
    printf("=== Bem-vindo a MAETS ===\n");
    printf("1 - Cadastrar\n");
    printf("2 - Login\n");
    printf("3 - Listar Usuarios\n");
    printf("4 - Cadastrar Jogos\n");
    printf("5 - Listar Jogos\n");
    printf("6 - Meus Jogos\n");
    printf("7 - Excluir Jogos\n");
    printf("8 - Comprar Jogos\n");
    printf("9 - Editar Senha\n");
    printf("10 - Excluir Usuario\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    struct jogo *lista_jogos = carregar_jogos("jogos.txt"); 
    struct usuario *lista_usuarios = carregar_usuarios("usuarios.txt"); 

    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                cadastrar(&lista_usuarios);
                salvar_usuarios("usuarios.txt", lista_usuarios); 
                break;
            case 2:
                login_usuario(lista_usuarios);
                break;
            case 3:
                listar_usuarios(lista_usuarios);
                break;
            case 4: {
                int id;
                char nome[MAX_NOME + 1];
                float preco;
                printf("Informe o ID do jogo: ");
                scanf("%d", &id);
                getchar(); 
                printf("Informe o nome do jogo: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0; 
                printf("Informe o preco do jogo: ");
                scanf("%f", &preco);
                getchar(); 
                struct jogo *novo_jogo = criar_jogo(id, nome, preco);
                adicionar_jogo(&lista_jogos, novo_jogo);
                salvar_jogos("jogos.txt", lista_jogos); 
                break;
            }
            case 5:
                listar_jogos(lista_jogos);
                break;
            case 6:
                meus_jogos(lista_usuarios, lista_jogos);
                break;
            case 7:
                excluir_jogo(&lista_jogos);
                salvar_jogos("jogos.txt", lista_jogos); 
                break;
            case 8:
                comprar_jogo(lista_usuarios, lista_jogos);
                break;
            case 9:
                editar_senha(lista_usuarios);
                salvar_usuarios("usuarios.txt", lista_usuarios); 
                break;
            case 10:
                excluir_usuario(&lista_usuarios);
                salvar_usuarios("usuarios.txt", lista_usuarios); 
                break;
            case 0:
                salvar_usuarios("usuarios.txt", lista_usuarios); 
                salvar_jogos("jogos.txt", lista_jogos); 
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    
    return 0;
}
