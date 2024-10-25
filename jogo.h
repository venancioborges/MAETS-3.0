#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_EMAIL 80
#define MAX_COMPRAS 100


struct jogo {
    int id;
    char nome[MAX_NOME + 1];
    float preco;
    struct jogo *next; 
};


struct usuario {
    char username[MAX_NOME + 1];
    char password[MAX_NOME + 1];
    char email[MAX_EMAIL];
    int compras[MAX_COMPRAS]; 
    int qtd_compras;
    struct usuario *next; 
};


struct jogo* criar_jogo(int id, const char *nome, float preco);
void adicionar_jogo(struct jogo **lista_jogos, struct jogo *novo_jogo);
void listar_jogos(struct jogo *lista_jogos);
void excluir_jogo(struct jogo **lista_jogos);
void salvar_jogos(const char *nome_arquivo, struct jogo *lista_jogos);
struct jogo* carregar_jogos(const char *nome_arquivo);


struct usuario* criar_usuario(const char *username, const char *password, const char *email);
void adicionar_usuario(struct usuario **lista_usuarios, struct usuario *novo_usuario);
void listar_usuarios(struct usuario *lista_usuarios);
void excluir_usuario(struct usuario **lista_usuarios);
void salvar_usuarios(const char *nome_arquivo, struct usuario *lista_usuarios);
struct usuario* carregar_usuarios(const char *nome_arquivo);
int validar_email(const char *email, struct usuario *lista_usuarios);
void cadastrar(struct usuario **lista_usuarios);
void editar_senha(struct usuario *lista_usuarios);
void login_usuario(struct usuario *lista_usuarios);
void comprar_jogo(struct usuario *lista_usuarios, struct jogo *lista_jogos);
void meus_jogos(struct usuario *lista_usuarios, struct jogo *lista_jogos);
void excluir_jogo(struct jogo **lista_jogos);
#endif
