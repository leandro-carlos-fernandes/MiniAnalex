#pragma warning(disable : 4996)

/* 
 * MiniAnaLex.c :
 * 
 * Este progama é um exemplo de como implmentar um analisador léxico para
 * o reconhecimento de tokens em um arquivo fonte.
 * Trata-se de um scanner para uma linguagem com os seguintes elementos:
 * - variáveis: classificados como identificadores, devem atender as regras
 *   usuais de formação de identificadores em linguagens de programação;
 * - números: inteiros ou reais, tendo o ponto como separador de decimal;
 * - operadores aritméticos: soma, subtração, multiplicação e divisão, dados
 *   pelos caracteres tradicionalmente associados a tais operações;
 * - operador de atribuição: representado pelo caracter de igual '='
 * 
 * @autor: Leandro Carlos Fernandes
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

 /*
  * Tipos de tokens (classificação)
  */
typedef enum {
	ERRO,			// símbolo inválido
	IDENTIF,		// identificador
	OP_ATRIB,		// =
	OP_SOMA,		// +
	OP_SUB,			// -
	OP_MULT,		// *
	OP_DIV,			// /
	INTEIRO,		// números inteiros
	REAL,			// números reais
	ABRE_PARENT,	// (
	FECHA_PARENT,	// )
	EOS				// fim de sentença/arquivo
} TOKEN_TYPE;

char* tokenToStr[] = {
	"Erro léxico",
	"Identificador",
	"Operador de atribuição",
	"Operador de adição",
	"Operador de subtração",
	"Operador de multiplicação",
	"Operador de divisão",
	"Número inteiro",
	"Número real",
	"Abre parenteses",
	"Fecha parenteses",
	"fim de conteúdo"
};

/*
 * Registro do token
 */
typedef struct {
	TOKEN_TYPE tipo;
	int linha;
	char valor[15];
} TOKEN;

/*
 * Variáveis globais
 */
char* buffer;	// Buffer de memória com o conteúdo lido do arquivo
int linha = 1;	// Contador de linhas
short debugMode = FALSE;

/*
 * Protótipos de funções
 */
TOKEN scanner();

/*
 * Função principal (programa)
 * 
 * Implementa um analisador léxico simples para processamento de expressões
 * aritméticas parentizadas que envolvam variáveis e elementos numéricos.
 */
int main(int argc, char* argv[]) {

	if (argc < 2) {
		printf("Analisador léxico para expressões aritméticas parentizadas envolvendo variáveis e números\n");
		printf("Uso:\n");
		printf("  MiniAnaLex.exe <arquivo_fonte> [/d]\n");
		printf("\n");
		printf("<arquivo_fonte> pode ser qualquer arquivo texto cujo conteúdo será\n");
		printf("analisado quanto a linguagem definida para esse exercício.\n");
		return 0;
	}
	else {
		if ((argc == 3) && (strcmp(argv[2], "/d") == 0))
			debugMode = TRUE;

		printf("Iniciando a análise léxica do arquivo: %s\n\n", argv[1]);
	}

	// Abertura do arquivo e carregamento do seu conteúdo para o buffer
	FILE* arq = fopen(argv[1], "r");
	if (arq == NULL) {
		fprintf(stderr, "Erro ao tentar abrir o aquivo \"%s\"", argv[1]);
		return -1;
	}
	fseek(arq, 0, SEEK_END);
	int tam_arq = ftell(arq);
	fseek(arq, 0, SEEK_SET);

	buffer = (char*)calloc(tam_arq, sizeof(char));
	if (buffer == NULL)
		exit(-1);
	else
		fread(buffer, sizeof(char), tam_arq, arq);

	fclose(arq);

	TOKEN tk;
	do {
		tk = scanner();
		printf("\nLinha:%3d | %-30s | %5s", tk.linha, tokenToStr[tk.tipo], tk.valor);
	} while ((tk.tipo != EOS) && (tk.tipo != ERRO));

	return 0;

}

/*
 * Analisador Léxico de expressões envolvendo variáveis, números e alguns operadores.
 */
TOKEN scanner() {

	TOKEN tk;

	tk.tipo = ERRO;
	strcpy(tk.valor, "");
	tk.linha = linha;

	// Espaços, tabulações e outros elementos decorativos (comentários)
	while ((*buffer == ' ') || (*buffer == '\t') || (*buffer == '\r') || (*buffer == '\n')) {
		if (*buffer == '\n')
			linha++;
		buffer++;
	}
	// Operadores: soma, incremento e somaAtrib
	if (*buffer == '+') {
		if (debugMode) strncat(tk.valor, buffer, 1);
		buffer++;
		tk.tipo = OP_SOMA;
	}
	// Operador de subtração
	else if (*buffer == '-') {
		if (debugMode) strncat(tk.valor, buffer, 1);
		buffer++;
		tk.tipo = OP_SUB;
	}
	// Operador de multiplicação
	else if (*buffer == '*') {
		if (debugMode) strncat(tk.valor, buffer, 1);
		buffer++;
		tk.tipo = OP_MULT;
	}
	// Operador de multiplicação
	else if (*buffer == '/') {
		if (debugMode) strncat(tk.valor, buffer, 1);
		buffer++;
		tk.tipo = OP_DIV;
	}
	// Operador de atribuição
	else if (*buffer == '=') {
		if (debugMode) strncat(tk.valor, buffer, 1);
		buffer++;
		tk.tipo = OP_ATRIB;
	}
	// Parenteses
	else if (*buffer == '(') {
		if (debugMode) strncat(tk.valor, buffer, 1);
		tk.tipo = ABRE_PARENT;
		buffer++;
	}
	else if (*buffer == ')') {
		if (debugMode) strncat(tk.valor, buffer, 1);
		tk.tipo = FECHA_PARENT;
		buffer++;
	}
	// Números
	else if (isdigit(*buffer)) {
		while ((*buffer >= '0') && (*buffer <= '9')) {
			strncat(tk.valor, buffer, 1);
			buffer++;
		}
		tk.tipo = INTEIRO;
		if (*buffer == '.') {
			strncat(tk.valor, buffer, 1);
			buffer++;
			if ((*buffer >= '0') && (*buffer <= '9'))
				while ((*buffer >= '0') && (*buffer <= '9')) {
					strncat(tk.valor, buffer, 1);
					buffer++;
				}
			else
				strcat(tk.valor, "0");
			tk.tipo = REAL;
		}
	}
	// Identificadores
	else if (isalpha(*buffer)) {
		while (isalpha(*buffer) || isdigit(*buffer) || (*buffer == '_')) {
			strncat(tk.valor, buffer, 1);
			buffer++;
		}
		tk.tipo = IDENTIF;
	}
	else if ((*buffer == EOF) || (*buffer == '\x0')) {
		if (debugMode) strncat(tk.valor, "EOF", 1);
		tk.tipo = EOS;
	}
	else {
		strncat(tk.valor, buffer, 1);
		tk.tipo = ERRO;
	}

	tk.linha = linha;
	return tk;
}