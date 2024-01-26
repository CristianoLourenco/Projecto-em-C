#include <conio.h>

enum tipo{
    empresa = 0,
    particular = 1,
};


typedef enum tipo TIPO;

struct PESSOA{
	char nome [100];
	char identificacao [40];
	int codigo;
	int telefone;
	TIPO tipoPessoa;
};

struct CONTA{
	int tipo_conta;
	int codigo_cliente;
	int codigo;
	int numero_conta;
	int estado;
	float saldo;
	TIPO tipoConta;
};

//Redefinindo os nomes dos registos
typedef struct PESSOA PESSOAS;
typedef struct CONTA CONTAS;
