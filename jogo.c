#include "jogo.h"


struct jogo* criar_jogo(int id, const char *nome, float preco) {
    struct jogo *novo_jogo = malloc(sizeof(struct jogo));
    if (!novo_jogo) {
        printf("Erro ao alocar memória para novo jogo.\n");
        exit(1);
    }
    novo_jogo->id = id;
    strcpy(novo_jogo->nome, nome);
    novo_jogo->preco = preco;
    novo_jogo->next = NULL;
    return novo_jogo;
}


struct usuario* criar_usuario(const char *username, const char *password, const char *email) {
    struct usuario *novo_usuario = malloc(sizeof(struct usuario));
    if (!novo_usuario) {
        printf("Erro ao alocar memória para novo usuário.\n");
        exit(1);
    }
    strcpy(novo_usuario->username, username);
    strcpy(novo_usuario->password, password);
    strcpy(novo_usuario->email, email);
    novo_usuario->qtd_compras = 0;
    novo_usuario->next = NULL;
    return novo_usuario;
}


void adicionar_jogo(struct jogo **lista_jogos, struct jogo *novo_jogo) {
    novo_jogo->next = *lista_jogos;
    *lista_jogos = novo_jogo;
}


void adicionar_usuario(struct usuario **lista_usuarios, struct usuario *novo_usuario) {
    novo_usuario->next = *lista_usuarios;
    *lista_usuarios = novo_usuario;
}


void listar_jogos(struct jogo *lista_jogos) {
    struct jogo *atual = lista_jogos;
    while (atual != NULL) {
        printf("Jogo ID: %d, Nome: %s, Preco: %.2f\n", atual->id, atual->nome, atual->preco);
        atual = atual->next;
    }
}


void listar_usuarios(struct usuario *lista_usuarios) {
    struct usuario *atual = lista_usuarios;
    while (atual != NULL) {
        printf("Usuario: %s, E-mail: %s\n", atual->username, atual->email);
        atual = atual->next;
    }
}


void excluir_usuario(struct usuario **lista_usuarios) {
    char username[MAX_NOME + 1];
    printf("Informe o nome de usuario a ser excluido: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; 

    struct usuario *atual = *lista_usuarios;
    struct usuario *anterior = NULL;

    while (atual != NULL && strcmp(atual->username, username) != 0) {
        anterior = atual;
        atual = atual->next;
    }

    if (atual == NULL) {
        printf("Usuario com nome %s nao encontrado.\n", username);
        return;
    }

    if (anterior == NULL) {
        *lista_usuarios = atual->next; 
    } else {
        anterior->next = atual->next; 
    }

    free(atual);
    printf("Usuario excluido com sucesso!\n");
}


int validar_email(const char *email, struct usuario *lista_usuarios) {
    if (strchr(email, '@') == NULL) {
        printf("E-mail invalido: deve conter o caractere '@'.\n");
        return 0;
    }
    if (strlen(email) >= MAX_EMAIL) {
        printf("E-mail invalido: deve ter menos de 80 caracteres.\n");
        return 0;
    }
    struct usuario *atual = lista_usuarios;
    while (atual != NULL) {
        if (strcmp(email, atual->email) == 0) {
            printf("E-mail ja cadastrado.\n");
            return 0;
        }
        atual = atual->next;
    }
    return 1;
}


void cadastrar(struct usuario **lista_usuarios) {
    char username[MAX_NOME + 1];
    char password[MAX_NOME + 1];
    char email[MAX_EMAIL];

    printf("Informe o nome de usuario: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; 

    printf("Informe a senha: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; 

    printf("Informe o e-mail: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0; 

    if (validar_email(email, *lista_usuarios)) {
        struct usuario *novo_usuario = criar_usuario(username, password, email);
        adicionar_usuario(lista_usuarios, novo_usuario);
        printf("Cadastrado com sucesso!\n");
    }
}


void editar_senha(struct usuario *lista_usuarios) {
    char username[MAX_NOME + 1];
    char senha_atual[MAX_NOME + 1];
    char nova_senha[MAX_NOME + 1];

    printf("Digite o nome de usuario: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; 

    printf("Digite a senha atual: ");
    fgets(senha_atual, sizeof(senha_atual), stdin);
    senha_atual[strcspn(senha_atual, "\n")] = 0; 

    struct usuario *usuario_logado = NULL;
    struct usuario *atual = lista_usuarios;
    while (atual != NULL) {
        if (strcmp(username, atual->username) == 0 && strcmp(senha_atual, atual->password) == 0) {
            usuario_logado = atual;
            break;
        }
        atual = atual->next;
    }

    if (usuario_logado == NULL) {
        printf("Nome de usuario ou senha atual incorretos!\n");
        return;
    }

    printf("Digite a nova senha: ");
    fgets(nova_senha, sizeof(nova_senha), stdin);
    nova_senha[strcspn(nova_senha, "\n")] = 0; 
    strcpy(usuario_logado->password, nova_senha);
    printf("Senha alterada com sucesso!\n");
}


void login_usuario(struct usuario *lista_usuarios) {
    char username[MAX_NOME + 1];
    char password[MAX_NOME + 1];

    printf("Digite o nome de usuario: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; 

    printf("Digite a senha: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; 

    struct usuario *atual = lista_usuarios;
    while (atual != NULL) {
        if (strcmp(username, atual->username) == 0 && strcmp(password, atual->password) == 0) {
            printf("Login realizado com sucesso!\n");
            return;
        }
        atual = atual->next;
    }
    printf("Usuario ou senha invalidos!\n");
}


void comprar_jogo(struct usuario *lista_usuarios, struct jogo *lista_jogos) {
    char username[MAX_NOME + 1];
    printf("Informe o nome do usuario: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; 

    struct usuario *atual_usuario = lista_usuarios;
    while (atual_usuario != NULL && strcmp(atual_usuario->username, username) != 0) {
        atual_usuario = atual_usuario->next;
    }

    if (atual_usuario == NULL) {
        printf("Usuario nao encontrado!\n");
        return;
    }

    int id_jogo;
    printf("Informe o ID do jogo a ser comprado: ");
    scanf("%d", &id_jogo);
    getchar();

    struct jogo *atual_jogo = lista_jogos;
    while (atual_jogo != NULL && atual_jogo->id != id_jogo) {
        atual_jogo = atual_jogo->next;
    }

    if (atual_jogo == NULL) {
        printf("Jogo nao encontrado!\n");
        return;
    }

    if (atual_usuario->qtd_compras < MAX_COMPRAS) {
        atual_usuario->compras[atual_usuario->qtd_compras++] = id_jogo;
        printf("Compra realizada com sucesso!\n");
    } else {
        printf("Limite de compras atingido!\n");
    }
}


void meus_jogos(struct usuario *lista_usuarios, struct jogo *lista_jogos) {
    char username[MAX_NOME + 1];
    printf("Informe o nome do usuario: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; 

    struct usuario *atual_usuario = lista_usuarios;
    while (atual_usuario != NULL && strcmp(atual_usuario->username, username) != 0) {
        atual_usuario = atual_usuario->next;
    }

    if (atual_usuario == NULL) {
        printf("Usuario nao encontrado!\n");
        return;
    }

    printf("Jogos comprados por %s:\n", username);
    for (int i = 0; i < atual_usuario->qtd_compras; i++) {
        struct jogo *atual_jogo = lista_jogos;
        while (atual_jogo != NULL) {
            if (atual_jogo->id == atual_usuario->compras[i]) {
                printf("Jogo ID: %d, Nome: %s, Preco: %.2f\n", atual_jogo->id, atual_jogo->nome, atual_jogo->preco);
                break;
            }
            atual_jogo = atual_jogo->next;
        }
    }
}


void salvar_jogos(const char *nome_arquivo, struct jogo *lista_jogos) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return;
    }
    struct jogo *atual = lista_jogos;
    while (atual != NULL) {
        fprintf(arquivo, "%d;%s;%.2f\n", atual->id, atual->nome, atual->preco);
        atual = atual->next;
    }
    fclose(arquivo);
}


struct jogo* carregar_jogos(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return NULL;
    }

    struct jogo *lista_jogos = NULL;
    int id;
    char nome[MAX_NOME + 1];
    float preco;

    while (fscanf(arquivo, "%d;%[^;];%f\n", &id, nome, &preco) == 3) {
        struct jogo *novo_jogo = criar_jogo(id, nome, preco);
        adicionar_jogo(&lista_jogos, novo_jogo);
    }

    fclose(arquivo);
    return lista_jogos;
}

void excluir_jogo(struct jogo **lista_jogos) {
    int id;
    printf("Informe o ID do jogo a ser excluido: ");
    scanf("%d", &id);
    getchar(); 

    struct jogo *atual = *lista_jogos;
    struct jogo *anterior = NULL;

    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->next;
    }

    if (atual == NULL) {
        printf("Jogo com ID %d nao encontrado.\n", id);
        return;
    }

    if (anterior == NULL) {
        *lista_jogos = atual->next; 
    } else {
        anterior->next = atual->next; 
    }

    free(atual);
    printf("Jogo excluido com sucesso!\n");
}


void salvar_usuarios(const char *nome_arquivo, struct usuario *lista_usuarios) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return;
    }
    struct usuario *atual = lista_usuarios;
    while (atual != NULL) {
        fprintf(arquivo, "%s;%s;%s\n", atual->username, atual->password, atual->email);
        atual = atual->next;
    }
    fclose(arquivo);
}


struct usuario* carregar_usuarios(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return NULL;
    }

    struct usuario *lista_usuarios = NULL;
    char username[MAX_NOME + 1];
    char password[MAX_NOME + 1];
    char email[MAX_EMAIL];

    while (fscanf(arquivo, "%[^;];%[^;];%[^\n]\n", username, password, email) == 3) {
        struct usuario *novo_usuario = criar_usuario(username, password, email);
        adicionar_usuario(&lista_usuarios, novo_usuario);
    }

    fclose(arquivo);
    return lista_usuarios;
}
