#include <stdlib.h>
#include "models.c"



PESSOAS clientes[100];
CONTAS contas[100];
int total_clientes;
int total_contas;

const char* filePath = "E:\\Ambiente de trabalho\\classDocs\\2 ano\\Programação 1\\projecto de programaçao\\novaVersao\\projectobaiC\\file.txt";

void copia_de_seguranca()
{
    FILE* file ;
    file =  fopen(filePath,"w");
    if(file == NULL)
    return;


   for(int indice = 0;indice < total_clientes;++indice)
   {
       	if(clientes[indice].codigo == EOF)
            return;
		PESSOAS p = clientes[indice];
        fprintf(file,"%d,%s,%s,%d",p.codigo, p.nome,p.identificacao,p.telefone);

	 	if(contas[indice].codigo != EOF)
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

// Função de cadastro de clientes
int cadastrar_clientes(PESSOAS p)
{
    clientes[total_clientes] = p;
    total_clientes += 1;
    return 1;
}

// Função buscar conta
int buscar_conta (int id){
    int position = 0;
    for(int i= 0; i <= (total_contas) ; i++)
    {
        if (contas[position].numero_conta == id || contas[position].codigo_cliente == id)
        return position;
    }
    return -1;
}

// Função buscar cliente
int buscar_cliente (int id){
    int position = 0;
    for (int i = 0 ; i <=  (total_clientes); ++i )
    {
       if (clientes[position].codigo == id)
       return position;
    }
    return -1;
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
int depositar (int numero_conta, double valor){
    int position = buscar_conta(numero_conta);
    if (position != -1 && valor >= 1)
    {
        contas[position].saldo = valor;
        return 1;
    }
    return 0;
}

// Função de levantar dinheiro
int levantar_dinheiro (int numero_conta, double valor){
    int position = buscar_conta(numero_conta);
    if(position != -1 && valor >= 1 && valor <= contas[position].saldo)
    {
	 	contas[position].saldo -= valor;
		return 1;
    }
	return 0;
}

double consultar_saldo(int numero_conta)
{
	int position = buscar_conta(numero_conta);
	if (position != -1)
        return contas[position].saldo;
	return -1;
}

int transferir_dinheiro(int num_c_enviar, int num_c_receber, double valor)
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
	printf("\nTIPO DE CONTA: TIPO" );
}

void apresentar_dados_Cliente(PESSOAS p)
{
	printf("\nCODIGO: %d",p.codigo);
	printf("\nNOME: %s",p.nome);
	printf("\nIDENTIFICAÇÃO: %s", p.identificacao);
	printf("\nTELEFONE: %d", p.telefone	);
}
//ZAU
void listar_clientes ()
{
    for(int contador =0; contador <= (total_clientes - 1); contador++)
    {
        PESSOAS p = clientes[contador];
		int posicao_conta = buscar_conta(p.codigo);
        apresentar_dados_Cliente(p);
		if(posicao_conta >= 0 )
		{
            apresentar_dados_conta(contas[posicao_conta]);
            printf("\n=====================================\n");
        }
    }
}

void resultado(int condicao)
{
    if(condicao)
    {
        copia_de_seguranca();
		printf("operacao realizada com suesso\n ");
    }
	else
		printf("Falha na operacao\nRepita o processo!");
}


