#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

enum tipo{
    empresa = 0,
    particular = 1,
};


typedef enum tipo TIPO;

struct PESSOA{
	char nome [250];
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



PESSOAS clientes[100];
CONTAS contas[100];
int total_clientes;
int total_contas;

const char* filePath = "E:\\Ambiente de trabalho\\file.txt";


void smsretult(int condicao,char smsTrue[], char smsFalse[])
{
    if(condicao)
       printf("%s",smsTrue);
    else
        printf("%s",smsFalse);
}

// Função buscar conta
int buscar_conta (int id){
    for(int i= 0; i <= (total_contas -1) ; ++i)
    {
        if(contas[i].estado == 0)
            return EOF;
        if (contas[i].numero_conta == id || contas[i].codigo_cliente == id)
            return i;
    }
    return EOF;
}

// Função buscar cliente
int buscar_cliente (int id){
    for (int i = 0 ; i <=  (total_clientes - 1); ++i )
    {
       if (clientes[i].codigo == id)
       return i;
    }
    return EOF;
}

// Função de cadastro de clientes
int cadastrar_clientes(PESSOAS p)
{
    clientes[total_clientes] = p;
    total_clientes += 1;
    return 1;
}

// Função abertura de conta
int abrir_conta (PESSOAS p, TIPO type){
    CONTAS c_cliente;
    c_cliente.codigo = total_contas + 1;
    c_cliente.codigo_cliente = p.codigo;
    c_cliente.tipoConta = type;
    c_cliente.estado = 1;
    c_cliente.numero_conta = 100 + total_contas;

    contas[total_contas] = c_cliente;
    total_contas += 1;
    return 1;
    }

// Função de depositar dinheiro
int depositar (int numero_conta, float valor){
    int position = buscar_conta(numero_conta);
    if ((position == -1) || (valor <= 10))
        return 0;
   contas[position].saldo += valor;
   return 1;
}

// Função de levantar dinheiro
int levantar_dinheiro (int numero_conta, float valor){
    int position = buscar_conta(numero_conta);
    if(position != -1 && valor >= 1 && valor <= contas[position].saldo)
    {
	 	contas[position].saldo -= valor;
		return 1;
    }
	return 0;
}

float consultar_saldo(int numero_conta)
{
	int position = buscar_conta(numero_conta);
	if (position != -1)
        return contas[position].saldo;
	return EOF;
}

int transferir_dinheiro(int num_c_enviar, int num_c_receber, float valor)
{
  int position_c_enviar = buscar_conta(num_c_enviar);
  int position_c_receber = buscar_conta(num_c_receber);
  if (position_c_enviar != -1 && position_c_receber != -1)
  if (valor >= 1 &&  valor <= contas[position_c_enviar].saldo )
  {
	  contas[position_c_enviar].saldo -= valor;
	  contas[position_c_receber].saldo += valor;
    return 1;
  }
	return 0;
}

int actualizar_dados(PESSOAS p, int clientId)
{
	int position = buscar_cliente(clientId);
	if (position != -1)
    {
        p.codigo = clientId;
		clientes[position] = p;
		return 1;
    }
	return 0;
}

void apresentar_dados_conta(CONTAS c)
{
    printf("\n===DADOS DE CONTA===\n");
	printf("NUMERO DE CONTA: %d" , c.numero_conta);
	printf("\nESTADO: ACTIVADO" );
	printf("\nTIPO DE CONTA: ");
	smsretult(c.tipoConta == empresa,"Empresa\n","Particular\n");
}

void apresentar_dados_Cliente(PESSOAS p)
{
	printf("\nCODIGO: %d",p.codigo);
	printf("\nNOME: %s",p.nome);
	printf("\nIDENTIFICACAO: %s", p.identificacao);
	printf("\nTELEFONE: %d", p.telefone);
	printf("\nNatureza: ");
	smsretult(p.tipoPessoa == empresa,"Empresa\n","Particular\n") ;
}

void listar_clientes ()
{
    for(int contador =0; contador <= (total_clientes - 1); contador++)
    {
        PESSOAS p = clientes[contador];
		int posicao_conta = buscar_conta(p.codigo);
        apresentar_dados_Cliente(p);
		if(posicao_conta != -1)
		{
            apresentar_dados_conta(contas[posicao_conta]);
            printf("=====================================\n");
        }
    }
}


/*cases****************/

int menu()
{
    int opcao;
    printf ("=====OPERACOES===== \n\n");
	printf ("[1] CADASTRAR CLIENTE\n");
	printf ("[2] LISTAR CLIENTES\n");
	printf ("[3] ABERTURA DE CONTA\n");
	printf ("[4] DEPOSITAR DINHEIRO\n");
	printf ("[5] LEVANTAR DINHEIRO\n");
	printf ("[6] CONSULTAR SALDO\n");
	printf ("[7] TRANSFERIR DINHEIRO\n");
	printf ("[8] ACTUALIZAR DADOS DO CLIENTE\n");
	printf ("[9] TERMINAR\n\n");
	printf ("opcao: ");
	scanf("%d", &opcao);
	return opcao;
}
void caseCadastro()
{
            PESSOAS p;
            char first;
            char sec;
            int tipoPessoa = 100;
            p.codigo = total_clientes;
            printf ("INFORME O SEU NOME: ");
                scanf("%s",p.nome);
            printf ("INFORME O NUMERO: ");
                scanf("%d", &p.telefone);
            printf ("INFORME A IDENTIFICACAO: ");
                scanf("%s", p.identificacao);
            printf ("INFORME O TIPO DE CONTA: \n");
            printf ("[0] EMPRESA \n");
            printf ("[1] PARTICULAR \n");
            printf ("TIPO: ");
                scanf("%d", &tipoPessoa);
            if(tipoPessoa == 0 || tipoPessoa == 1)
            {
                p.tipoPessoa = tipoPessoa;
                resultado(cadastrar_clientes(p));
            }
            else
                printf("\nFalha na Opreacao!\nRepita a Opreacao.");
            return;
}

void caseAberturaConta()
{
 int opcao, codigo, indiceCliente;
            TIPO type;
            printf("DIGITE O CODIGO DE CLIENTE: \n");
                scanf("%i", &codigo);
            indiceCliente = buscar_cliente(codigo);
            printf("--------------------------\n");
            if(indiceCliente != -1)
            {
                printf ("DIGITE O TIPO DE CONTA: \n");
                printf ("[0] EMPRESA \n");
                printf ("[1] PARTICULAR \n");
                printf("OPCAO: ");
                    scanf ("%i", &opcao);
                if (opcao == 0 && clientes[indiceCliente].tipoPessoa == opcao)
                    type = empresa;
                else if (opcao == 1 && clientes[indiceCliente].tipoPessoa == opcao)
                    type = particular;
                else
                {
                    printf("\nFalha na Opreacao!\nRepita a Opreacao.");
                    return;
                }
                resultado(abrir_conta(clientes[indiceCliente], type));
            }
            return;
}

void caseDeposito()
{
int numero_conta;
float valor;
printf("Informe o numero de Conta: ");
    scanf("%i", &numero_conta);
printf ("Informe o valor a depositar: ");
    scanf("%f", &valor);
resultado(depositar(numero_conta, valor));
return;
}

void caseLevantamento()
{
    int numero_conta;
            float valor;
            printf("Informe o numero de Conta: ");
                scanf("%i",&numero_conta);
            printf("Informe o valor a levantar: ");
                scanf("%f",&valor);
            resultado(levantar_dinheiro(numero_conta, valor));
    return;

}

void caseConsulta()
{
       int numero_conta;
            double saldo;

            printf("Informe o numero de Conta: ");
                scanf("%i", &numero_conta ) ;
            saldo = consultar_saldo(numero_conta);

        if(saldo != -1 )
            printf("operacao realizada com suesso\nSaldo: %.2f\n", saldo);
        else
            printf("Falha na operacao\nRepita o processo!");
        return;
}

void caseTransferencia()
{
       int conta_enviar, conta_receber;
            float valor;

            printf( "Informe o numero de conta a enviar: ");
                scanf("%i", &conta_enviar);
            printf("Informe o numero de conta a receber: ");
                scanf("%i", &conta_receber);
            printf( "Informe o valor: ");
                scanf("%f",&valor);
            resultado(transferir_dinheiro(conta_enviar, conta_receber, valor));
            return;
}

void caseActualizar()
{
     PESSOAS cliente_actualizado;
            int codigo_cliente;

            printf("Informe o codigo: ");
                scanf("%d", &codigo_cliente);
            printf("Informe o nome: ");
                scanf("%s", cliente_actualizado.nome) ;
            printf("Informe a identificacao: ");
                scanf("%s",cliente_actualizado.identificacao);
            printf("Informe o telefone: ");
                scanf("%d", &cliente_actualizado.telefone );
            resultado(actualizar_dados(cliente_actualizado, codigo_cliente));
            return;
}



void copia_de_seguranca()
{

   FILE* file =  fopen(filePath,"w+");
   if(file == NULL)
   return;

   for(int indice = 0;indice < total_clientes;++indice)
   {
       	if(clientes[indice].codigo == EOF)
            return;
		PESSOAS p = clientes[indice];
        fprintf(file,"%d,%s,%s,%d",p.codigo, p.nome,p.identificacao,p.telefone);

	 	if(buscar_conta(p.codigo) != -1)
        {
            CONTAS c = contas[indice];
            c.estado = 1 ;
            fprintf(file,"%d,%d,%d,%.2f,%d\n",c.codigo,c.codigo_cliente,c.estado,c.saldo,c.numero_conta);
        }
        else
        {
            fprintf(file,"%s","\n");
        }

   }
   fclose(file);
}

void resultado(int condicao)
{
    if(condicao)
    {
        copia_de_seguranca();
		printf("\noperacao realizada com suesso\n ");
    }
	else
		printf("Falha na operacao\nRepita o processo!");
}



int main(){

 int opcao = 0;
 while(opcao != 9)
 {
   opcao = menu();
    switch (opcao)
    {
    case 1:
        caseCadastro();
        break;
    case 2:
        listar_clientes();
        break;
    case 3:
        caseAberturaConta();
        break;
    case 4:
        caseDeposito();
        break;
    case 5:
        caseLevantamento();
        break;
    case 6:
        caseConsulta();
        break;
    case 7:
        caseTransferencia();
        break;
    case 8:
        caseActualizar();
        break;
    default:
            printf ("\nTERMINADO COM SUCESSO, MUITO OBRIGADO E VOLTE SEMPRE!\n");
    }
 }
return 0;
}
