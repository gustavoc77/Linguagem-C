// BIBLIOTECAS    
#include <stdio.h>      // manipular arquivos 
#include <conio.h>      // habilita uso do getch
#include <locale.h>     // acentuação
#include <stdlib.h>     // habilita uso do system
#include <string.h>     // para trabalhar com strings (uso da fun??o gets)
#include <time.h>       // PARA USAR srand e time (NULL)

/* TIPOS PRÉ-DEFINIDOS PELO PROGRAMADOR */
typedef    struct
{
    char   pista[17];
    int    qtd;   /* linha coluna */
    char   vetpalavras[3][17]; /*3 linhas por 17 colunas*/
}
registro; /* registro = tipo de dado recém-criado */

typedef  struct
{
    float    valor_premio;
}
reg_premio;

/* VARIÁVEIS GLOBAIS */ 
registro    reg; /* reg = variável do tipo registro */
char        escolha;
int         num;
float valor,premioespecial, grana,granajogador1,granajogador2,granajogador3, acertos=0;
int premio;
int i,r,tm,acerto=1;
char auxiliar[3][17];
char letra;
float premioo[12];
FILE *Arqpremio;
reg_premio  valor_do_premio;
int         numero_registro=0;
int k,erroresposta=0;
int contador;
int contatracinhos;
char resposta[3][17];
int venceu,perdeuj1=0,perdeuj2=0,perdeuj3=0;
int certo=0;
int respostaj1, respostaj2, respostaj3;
/* CRIAÇÃO DAS FUNÇÕES */
void   menu (void)
{
  do
  {
    system ("cls");
    printf ("\n\t\t\t\t\t\t\t--------- M E N U ----------");
    printf ("\n\t\t\t\t\t\t\t    1. Cadastra palavras    ");
    printf ("\n\t\t\t\t\t\t\t    2. Consulta palavras    ");
    printf ("\n\t\t\t\t\t\t\t    3. JOGAR                ");
    printf ("\n\t\t\t\t\t\t\t    S. SAIR                 ");
    printf ("\n\t\t\t\t\t\t\t----------------------------");
    printf ("\n\t\t\t\t\t\t\t    Escolha: ");
    fflush (stdin); 
    escolha = getche ();
  }
  while ( escolha != '1' && escolha != '2' && escolha != '3' &&
          escolha != 'S' && escolha != 's');
}

void captura_dados ( void )
{
    int    indice;
    system ("cls");
    printf ("\n=========== CADASTRO DE PALAVRAS ===============");
    printf ("\nPISTA: ");
    fflush (stdin);
    gets(reg.pista);
    do 
    {  printf ("\n\nQUANTIDADE DE PALAVRAS: ");
       fflush (stdin);
       scanf  ("%i" , &reg.qtd);
    }
    while ( !(reg.qtd>=1 && reg.qtd<=3) );
    reg.vetpalavras[0][0] = '\0';
    reg.vetpalavras[1][0] = '\0';
    reg.vetpalavras[2][0] = '\0';
    for ( indice=0   ; indice<=reg.qtd-1     ; indice++   )
    {
        printf ("\n\n%ia. PALAVRA: ", indice+1);   
        fflush (stdin);
        gets (reg.vetpalavras[indice]);
    }
}

void  grava_dados ( void )
{
  FILE * Arq;
  Arq = fopen ( "palavras.DAT" , "a" );   /* abrir arquivo */
  
  if(Arq == NULL) //Caso haja algum erro ao tentar abrir o arquivo esse bloco imprime na tela mensagem de aviso e encerra o programa.
 {
  system ("cls");
  printf("Arquivo nao pode ser aberto\n");
  getch();
  exit(0);          
 }
  fwrite ( &reg , sizeof(reg), 1, Arq);   /* grava no arquivo */
  fclose (Arq);                           /* fecha arquivo */
}

void  consulta ( void )
{
  FILE * Arq;
  Arq = fopen ( "palavras.DAT" , "r" );   /* abrir arquivo */
  
  if(Arq == NULL) //Caso haja algum erro ao tentar abrir o arquivo esse bloco imprime na tela mensagem de aviso e encerra o programa.
 {
  system ("cls");
  printf("Arquivo nao pode ser aberto\n");
  getch();
  exit(0);          
 }
  
  while ( !feof(Arq) ) /* enquanto não for fim do arquivo...*/
  {
       fread ( &reg, sizeof(reg), 1, Arq); /*...lê e...*/
       if ( !feof(Arq) )
       {
          printf("\n[%16s] [%02d] [%16s] [%16s] [%16s]",  /*...mostra na tela*/
          reg.pista, reg.qtd, reg.vetpalavras[0], reg.vetpalavras[1], reg.vetpalavras[2]);
       }        
  }
  fclose (Arq);/* fecha arquivo */
}

int  quantidadeRegistros ( void )
{
  FILE * Arq;
  int qtdregs=0;
  Arq = fopen ( "palavras.DAT" , "r" );   /* abrir arquivo */
  
  if(Arq == NULL) //Caso haja algum erro ao tentar abrir o arquivo esse bloco imprime na tela mensagem de aviso e encerra o programa.
 {
  system ("cls");
  printf("Arquivo nao pode ser aberto\n");
  getch();
  exit(0);          
 }
  
  while ( !feof(Arq) ) /* enquanto não for fim do arquivo...*/
  {
       fread ( &reg, sizeof(reg), 1, Arq); /*...lê e...*/
       if ( !feof(Arq) )
       {
          qtdregs++;
       }        
  }
  fclose (Arq);/* fecha arquivo */
  return qtdregs;
}

void  cadastra ( void ) 
{
    captura_dados();
    grava_dados();
}

void gera_tela(void){
	printf("\t\t\t\t\t\t\tA palavra está associada com: %s",reg.pista);
	printf("\n");
	i=0;
	while(i <= (reg.qtd-1)){
		tm = strlen(reg.vetpalavras[i]);
		for(r=0;r<=(tm-1);r++){
			auxiliar[i][r] = '-';
			contatracinhos++;
		}
		printf("\n\t\t\t\t\t\t\t%s",auxiliar[i]); 
		i++;
	}
		printf("\n\n\t\t\tJogador 1 \t\t\t Jogador 2 \t\t\t Jogador 3");    
		printf(" \n\t\t\t===================== \t\t===================== \t\t=====================");
		printf("\n\n\t\t\tR$%.2f     \t\t\t  R$%.2f  \t\t\t  R$%.2f",grana,granajogador2,granajogador3);
		getch();
}

void tela(void){
	system("cls");
	printf("\n\t\t\t\t\tA palavra está associada com: %s\n",reg.pista);
	printf("\n\t\t\t\t\t\t\t%s",auxiliar[0]);
	printf("\n\t\t\t\t\t\t\t%s",auxiliar[1]);
	printf("\n\t\t\t\t\t\t\t%s",auxiliar[2]); 
	printf("\n\n\t\t\tJogador 1 \t\t\t Jogador 2 \t\t\t Jogador 3");    
	printf(" \n\t\t\t===================== \t\t===================== \t\t=====================");
	printf("\n\n\t\t\tR$%.2f     \t\t\t  R$%.2f  \t\t\t  R$%.2f",granajogador1,granajogador2,granajogador3);
}
int numerosregistros(void){
        /* Abrir o arquivo */
    Arqpremio = fopen ( "PREMIOS.DAT" , "r" ); 
    /* testar se a abertura do arquivo foi BEM  SUCEDIDA */
    if ( Arqpremio == NULL ) /* NULL = 0000:0000 */
    {
        system ("cls");
        printf ("ERRO AO ABRIR O ARQUIVO! \n IMPOSSIVEL FAZER CONSULTA!");
        getch();
        exit(0);
    }
    /* Enquanto não chegar no fim do arquivo...*/
    while ( !feof(Arqpremio) )
    {
        /*...Lê... e...*/
        fread ( &valor_do_premio, sizeof(valor_do_premio), 1, Arqpremio );
        /*... mostra o registro lido na tela ...*/
        if ( !feof(Arqpremio) )  /*...se não for o fim de arquivo */
        {
            numero_registro++; 
            premioo[k] = valor_do_premio.valor_premio;
        }
        k++;      
    }
    /* Fecha o arquivo */
    fclose ( Arqpremio );
    
}

void sorteia_premios(void){
	
     	numerosregistros();
    	srand(time(NULL)); /* Garante que os números sorteados não se repitam */
  		premio = rand() % 12;
    	printf("%.2f:",premioo[premio]);
    	valor = premioo[premio];
 		premioespecial = rand() % 12;
}

void temporizador(void){
	setlocale(LC_ALL,"portuguese");
	 	contador = 5;
	 	printf("\n\t\t\tVocê tem 5 segundos para pensar e depois digitar a palavra...");
        while(contador >= 1){		
        //mostra o número
        printf("%i...",contador);
        //aguarda 5 segundos
        sleep(1);
        //beep
        printf("\a");
        //diminui de 1 o contador
        contador = contador - 1;                                                                          
      	  }
}
void vencedor(void){
	if(erroresposta != 0){
	system("cls");
	printf("\n\t\t\t\t\tA palavra está associada com: %s\n",reg.pista);
	printf("\n\t\t\t\t\t\t\t%s",reg.vetpalavras[0]);
	printf("\n\t\t\t\t\t\t\t%s",reg.vetpalavras[1]);
	printf("\n\t\t\t\t\t\t\t%s",reg.vetpalavras[2]); 
	printf("\n\n\t\t\tJogador 1 \t\t\t Jogador 2 \t\t\t Jogador 3");    
	printf(" \n\t\t\t===================== \t\t===================== \t\t=====================");
	printf("\n\n\t\t\tR$%.2f     \t\t\t  R$%.2f  \t\t\t  R$%.2f",granajogador1,granajogador2,granajogador3);
	printf("\nSEM VENCEDORES");
	exit(0);
	}else{
		if((granajogador1 > granajogador2)&&(granajogador1 > granajogador3)){
			system("cls");
			printf("\n\t\t\t\t\tA palavra está associada com: %s\n",reg.pista);
			printf("\n\t\t\t\t\t\t\t%s",reg.vetpalavras[0]);
			printf("\n\t\t\t\t\t\t\t%s",reg.vetpalavras[1]);
			printf("\n\t\t\t\t\t\t\t%s",reg.vetpalavras[2]); 
			printf("\n\n\t\t\tJogador 1 \t\t\t Jogador 2 \t\t\t Jogador 3");    
			printf(" \n\t\t\t===================== \t\t===================== \t\t=====================");
			printf("\n\n\t\t\tR$%.2f     \t\t\t  R$%.2f  \t\t\t  R$%.2f",granajogador1,granajogador2,granajogador3);
			printf("\n\n\t\t\tVENCEDOR");
		}
		if((granajogador2 > granajogador1)&&(granajogador2 > granajogador3)){
			system("cls");
			printf("\n\t\t\t\t\tA palavra está associada com: %s\n",reg.pista);
			printf("\n\t\t\t\t\t\t\t%s",reg.vetpalavras[0]);
			printf("\n\t\t\t\t\t\t\t%s",reg.vetpalavras[1]);
			printf("\n\t\t\t\t\t\t\t%s",reg.vetpalavras[2]); 
			printf("\n\n\t\t\tJogador 1 \t\t\t Jogador 2 \t\t\t Jogador 3");    
			printf(" \n\t\t\t===================== \t\t===================== \t\t=====================");
			printf("\n\n\t\t\tR$%.2f     \t\t\t  R$%.2f  \t\t\t  R$%.2f",granajogador1,granajogador2,granajogador3);
			printf("\n\n\t\t\t\t\t\t\tVENCEDOR");
			
		}	
		if((granajogador3 > granajogador1)&&(granajogador3 > granajogador2)){
			system("cls");
			printf("\n\t\t\t\t\tA palavra está associada com: %s\n",reg.pista);
			printf("\n\t\t\t\t\t\t\t%s",reg.vetpalavras[0]);
			printf("\n\t\t\t\t\t\t\t%s",reg.vetpalavras[1]);
			printf("\n\t\t\t\t\t\t\t%s",reg.vetpalavras[2]); 
			printf("\n\n\t\t\tJogador 1 \t\t\t Jogador 2 \t\t\t Jogador 3");    
			printf(" \n\t\t\t===================== \t\t===================== \t\t=====================");
			printf("\n\n\t\t\tR$%.2f     \t\t\t  R$%.2f  \t\t\t  R$%.2f",granajogador1,granajogador2,granajogador3);
			printf("\n\n\t\t\t\t\t\t\t\t\t\t\tVENCEDOR");
		}	
	}	
}

void   jogar (void)
{
  FILE * Arq;
  int  contaux=-1;
  /* Sorteia um dos totalregs*/
  srand(time(NULL)); /* Garante que os números sorteados não se repitam */
  num = rand() % quantidadeRegistros();
  Arq = fopen ( "palavras.DAT" , "r" );   /* abrir arquivo */
  while ( !feof(Arq) ) /* enquanto não for fim do arquivo...*/
  {
       fread ( &reg, sizeof(reg), 1, Arq); /*...lê e...*/
       if ( !feof(Arq) )       
       {
            contaux++;
            if (contaux == num) /* PARA A LEITURA */
               break;
       }        
  }
  fclose (Arq);/* fecha arquivo */
	system("cls");
	gera_tela();
	while((contatracinhos >=3) ){
	/*JOGADOR1*/
	tela();
	grana=0;
	acerto=1;
	premio=0;
	while((acerto==1) && (premio!=4)){
		granajogador1 = granajogador1 + grana; 
		do{
			acertos=0;
			acerto=0;
			if(contatracinhos <=3){
				respostaj1 = 1;
				break;
			}
			printf("\n\n\t\t\tRoda a Roda! ");
			printf ("\n\n\t\t\tUma letra por R$");sorteia_premios();   
			if(premio==4){
				tela();
				printf("\n\n\t\t\tPASSA A VEZ");
				printf("\n\n\t\t\tA vez será passada para o jogador 2.");
				printf("\n\n\t\t\t%.2f",premioo);
				getch();
				break;
			}   	
			if(premio==8){
				granajogador1=0;
				tela();
				printf("\n\n\t\t\tJogador 1 perde tudo");
				printf("\n\n\t\t\tA vez será passada para o jogador 2.");
				printf("\n\n\t\t\t%.2f",premioo);
				getch();
				break;
			}   
			fflush (stdin);
			letra = getche(); 
			letra = toupper(letra);
		    /* PROCURA A LETRA DENTRO DO VETOR */
		    i=0;
		    	while(i <= (reg.qtd-1)){
					tm = strlen(reg.vetpalavras[i]);
					for(r=0;r<=(tm-1);r++){
						if(auxiliar[i][r]== '-'){
							system("cls");
							if(reg.vetpalavras[i][r] == letra){
								auxiliar[i][r] = letra;
								acerto=1;
								acertos++;
								grana =acertos*valor;
								contatracinhos--;	
							}
						}
					}
					tela();
					i++;
				}			
				if(acerto !=1){
					tela();
					printf("\n\n\t\t\tUma letra por R$%.2f:%c",premioo[premio],letra);
					printf("\n\n\t\t\tNão existe letra %c na palavra.",letra);
					printf("\n\n\t\t\tA vez será passada para o jogador 2.");
				}
				tela();
			/*TÉRMINO DA PROCURA DENTRO DO VETOR*/					
		}while(letra <=65 || letra >=90 ); //Enquanto o jogador não digitar uma letra
	}
	tela();
	if(respostaj1==1){
		break;
	}
	/*JOGADOR 2*/
	tela();
	grana=0;
	acerto=1;
	premio=0;
	while((acerto==1) && (premio!=4)){ 
	granajogador2 = granajogador2 + grana; 
		do{
			acertos=0;
			acerto=0;
			if(contatracinhos <=3){
				respostaj2=1;
				break;
			}
			printf("\n\n\t\t\t\t\t\t\tRoda a Roda! ");
			printf ("\n\n\t\t\tUma letra por R$");sorteia_premios();   
			if(premio==4){
				tela();
				printf("\n\n\t\t\tPASSA A VEZ");
				printf("\n\n\t\t\tA vez será passada para o jogador 3.");
				printf("\n\n\t\t\t%.2f",premioo);
				getch();
				break;
			}
			if(premio==8){
				granajogador2=0;
				tela();
				printf("\n\n\t\t\tJogador 2 perde tudo");
				printf("\n\n\t\t\tA vez será passada para o jogador 3.");
				printf("\n\n\t\t\t%.2f",premioo);
				getch();
				break;
			}      	
			fflush (stdin);
			letra = getche(); 
			letra = toupper(letra);
		    /* PROCURA A LETRA DENTRO DO VETOR */
		    i=0;
		    	while(i <= (reg.qtd-1)){
					tm = strlen(reg.vetpalavras[i]);
					for(r=0;r<=(tm-1);r++){
						if(auxiliar[i][r]== '-'){
							system("cls");
							if(reg.vetpalavras[i][r] == letra){
								auxiliar[i][r] = letra;
								acerto=1;
								acertos++;
								grana=acertos*valor;	
								contatracinhos--;
							}
						}
					}
					tela();
					i++;
				}
				if(acerto !=1){
					tela();
					printf("\n\n\t\t\tUma letra por R$%.2f:%c",premioo[premio],letra);
					printf("\n\n\t\t\tNão existe letra %c na palavra.",letra);
					printf("\n\n\t\t\tA vez será passada para o jogador 3.");
				}
			/*TÉRMINO DA PROCURA DENTRO DO VETOR*/					
		}while(letra <=65 || letra >=90 ); //Enquanto o jogador não digitar uma letra
	}
		if(respostaj2==1){
		break;
	}
	/*JOGADOR 3*/
	tela();
	grana=0;
	acerto=1;
	premio=0;
	while((acerto==1) && (premio!=4)){
		granajogador3 = granajogador3 + grana; 
		do{
			acertos=0;
			acerto=0;
				/*JOGADOR3*/
			if(contatracinhos <=3){
				respostaj3=1;
				break;	
			}
			printf("\n\n\t\t\t\t\t\t\t\t\t\t\tRoda a Roda! ");
			printf ("\n\n\t\t\tUma letra por R$");sorteia_premios();   
			if(premio==4 ){
				tela();
				printf("\n\n\t\t\tPASSA A VEZ");
				printf("\n\n\t\t\tA vez será passada para o jogador 1.");
				printf("\n\n\t\t\t%.2f",premioo);
				getch();
				break;
			}   	
			if(premio==8){
				granajogador3=0;
				tela();
				printf("\n\n\t\t\tJogador 3 perde tudo");
				printf("\n\n\t\t\tA vez será passada para o jogador 1.");
				printf("\n\n\t\t\t%.2f",premioo);
				getch();
				break;
			}   
			fflush (stdin);
			letra = getche(); 
			letra = toupper(letra);
		    /* PROCURA A LETRA DENTRO DO VETOR */
		    i=0;
		    	while(i <= (reg.qtd-1)){
					tm = strlen(reg.vetpalavras[i]);
					for(r=0;r<=(tm-1);r++){
						if(auxiliar[i][r]== '-'){
							system("cls");
							if(reg.vetpalavras[i][r] == letra){
								auxiliar[i][r] = letra;
								acerto=1;
								acertos++;
								grana=acertos*valor;	
								contatracinhos--;
							}
						}
					}
					tela();
					i++;
				}

				if(acerto !=1){
					tela();
					printf("\n\n\t\t\tUma letra por R$%.2f:%c",premioo[premio],letra);
					printf("\n\n\t\t\tNão existe letra %c na palavra.",letra);
					printf("\n\n\t\t\tA vez será passada para o jogador 1.");
				}
				/*TÉRMINO DA PROCURA DENTRO DO VETOR*/					
				}while(letra <=65 || letra >=90 ); //Enquanto o jogador não digitar uma letra
			}
			if(respostaj3==1){
				break;
			}
		}/*ATÉ FALTAR 3 TRACINHOS OU MENOS PARA COMPLETAR*/
		
		/*VERIFICA AS RESPOSTAS*/
		while(contatracinhos <=3){
		/*SE A PRIMEIRA RESPOSTA FOR DADA PELO JOGADOR1*/
		if(respostaj1==1){
			printf("\n\n\n\t\t\tJogador 1: Faltam 3 letras para completar a palavra");
			temporizador();
			printf("\n\t\t\tValendo R$%.2f a palavra é:",premioespecial);
			/*Recebe a resposta do jogador1 e compara às respostas certas*/
					i=0;
					while(i <= (reg.qtd-1)){
						scanf("\t\t\t\t%s",&resposta[i]);
						printf("\n\t\t\t\t\t\t");
						
						strcmp(reg.vetpalavras[i],resposta[i]);
						if(strcmp(reg.vetpalavras[i],resposta[i])==0){
							certo++;
							
						}else{
							respostaj1==0;
							
						}
						i++;
					}
					/*Se as respostas estiverem erradas..*/
					if(certo == i){
							system("cls");
								granajogador1+=premioespecial;//adiciona o novo prêmio sorteado ao que o jogador já possui
								granajogador2=0;
								granajogador3=0;
								tela();
								/*COMPARAÇÃO PRA VER QUEM FOI O VENCEDOR*/
								
								vencedor();
								exit(0);
					}else {
						granajogador1=0;
					}
					

					//JOGADOR2
					printf("\n\n\n\t\t\tJogador 2: Faltam 3 letras para completar a palavra");
					temporizador();
					printf("\n\t\t\tValendo R$%.2f a palavra é:",premioespecial);
					/*Recebe a resposta do jogador2 e compara às respostas certas*/
					i=0;
					while(i <= (reg.qtd-1)){
						scanf("\t\t\t\t%s",&resposta[i]);
						printf("\n\t\t\t\t\t\t");
						
						strcmp(reg.vetpalavras[i],resposta[i]);
						if(strcmp(reg.vetpalavras[i],resposta[i])==0){
							certo++;
							
						}
						i++;
					}
					/*Se as respostas estiverem erradas..*/
					if(certo == i){
							system("cls");
								granajogador2+=premioespecial;//adiciona o novo prêmio sorteado ao que o jogador já possui
								granajogador1=0;
								granajogador3=0;
								tela();
								vencedor();
								exit(0);
					}else{
						granajogador2=0;
					}
					

					//JOGADOR3
					printf("\n\n\n\t\t\tJogador 3: Faltam 3 letras para completar a palavra");
					temporizador();
					printf("\n\t\t\tValendo R$%.2f a palavra é:",premioespecial);
										/*Recebe a resposta do jogador2 e compara às respostas certas*/
					i=0;
					while(i <= (reg.qtd-1)){
						scanf("\t\t\t\t%s",&resposta[i]);
						printf("\n\t\t\t\t\t\t");
						
						strcmp(reg.vetpalavras[i],resposta[i]);
						if(strcmp(reg.vetpalavras[i],resposta[i])==0){
							certo++;
							
						}
						i++;
					}
					/*Se as respostas estiverem erradas..*/
					if(certo == i){
							system("cls");
								granajogador3+=premioespecial;//adiciona o novo prêmio sorteado ao que o jogador já possui
								granajogador1=0;
								granajogador2=0;
								tela();
								vencedor();
								exit(0);
					}
					else{
						granajogador3=0;
						erroresposta=1;
						vencedor();
						
					}				
		}	
		
		
		/*SE A PRIMEIRA RESPOSTA FOR DADA PELO JOGADOR2*/
				if(respostaj2==1){
					printf("\n\n\n\t\t\tJogador 2: Faltam 3 letras para completar a palavra");
					temporizador();
					printf("\n\t\t\tValendo R$%.2f a palavra é:",premioespecial);
					i=0;
					while(i <= (reg.qtd-1)){
						scanf("\n\t\t\t\t%s",&resposta[i]);
						printf("\n\t\t\t\t\t\t");
						
						strcmp(reg.vetpalavras[i],resposta[i]);
						if(strcmp(reg.vetpalavras[i],resposta[i])==0){
							certo++;
							
						}
						i++;
					}
					/*Se as respostas estiverem erradas..*/
					if(certo == i){
							system("cls");
								granajogador2+=premioespecial;//adiciona o novo prêmio sorteado ao que o jogador já possui
								granajogador1=0;
								granajogador3=0;
								tela();
								vencedor();
								exit(0);
					}else{
						granajogador2=0;
					}

				
					//JOGADOR3
					printf("\n\n\n\t\t\tJogador 3: Faltam 3 letras para completar a palavra");
					temporizador();
					printf("\n\t\t\tValendo R$%.2f a palavra é:",premioespecial);
										/*Recebe a resposta do jogador2 e compara às respostas certas*/
					i=0;
					while(i <= (reg.qtd-1)){
						scanf("\n\t\t\t\t%s",&resposta[i]);
						printf("\n\t\t\t\t\t\t");
						
						strcmp(reg.vetpalavras[i],resposta[i]);
						if(strcmp(reg.vetpalavras[i],resposta[i])==0){
							certo++;
							
						}
						i++;
					}
					/*Se as respostas estiverem erradas..*/
					if(certo == i){
							system("cls");
								granajogador3+=premioespecial;//adiciona o novo prêmio sorteado ao que o jogador já possui
								granajogador1=0;
								granajogador2=0;
								tela();
								vencedor();
								exit(0);
					}else{
						granajogador3=0;
					}

					
					//JOGADOR1
					printf("\n\n\n\t\t\tJogador 1: Faltam 3 letras para completar a palavra");
					temporizador();
					printf("\n\t\t\tValendo R$%.2f a palavra é:",premioespecial);
					/*Recebe a resposta do jogador2 e compara às respostas certas*/
					i=0;
					while(i <= (reg.qtd-1)){
						scanf("\n\t\t\t\t%s",&resposta[i]);
						printf("\n\t\t\t\t\t\t");
						
						strcmp(reg.vetpalavras[i],resposta[i]);
						if(strcmp(reg.vetpalavras[i],resposta[i])==0){
							certo++;
							
						}
						i++;
					}
					/*Se as respostas estiverem erradas..*/
					if(certo == i){
							system("cls");
								granajogador1+=premioespecial;//adiciona o novo prêmio sorteado ao que o jogador já possui
								granajogador2=0;
								granajogador3=0;
								tela();
								exit(0);
					}
					else{
						granajogador1=0;
						erroresposta=1;
						vencedor();
						exit(0);
					}						
				}
				
				
				/*SE A PRIMEIRA RESPOSTA FOR DADA PELO JOGADOR3*/
				if(respostaj3==1){
					printf("\n\n\n\t\t\tJogador 3: Faltam 3 letras para completar a palavra");
					temporizador();
					printf("\n\t\t\tValendo R$%.2f a palavra é:",premioespecial);
										/*Recebe a resposta do jogador2 e compara às respostas certas*/
					i=0;
					while(i <= (reg.qtd-1)){
						scanf("\t\t\t\t%s",&resposta[i]);
						printf("\n\t\t\t\t\t\t");
						
						strcmp(reg.vetpalavras[i],resposta[i]);
						if(strcmp(reg.vetpalavras[i],resposta[i])==0){
							certo++;
						
						}
						i++;
					}
					/*Se as respostas estiverem erradas..*/
					if(certo == i){
							system("cls");
								granajogador3+=premioespecial;//adiciona o novo prêmio sorteado ao que o jogador já possui
								granajogador1=0;
								granajogador2=0;
								tela();
								vencedor();
								exit(0);
					}
					else{
						granajogador3=0;
						
					}	
					
					//JOGADOR1
					printf("\n\n\n\t\t\tJogador 1: Faltam 3 letras para completar a palavra");
					temporizador();
					printf("\n\t\t\tValendo R$%.2f a palavra é:",premioespecial);
					/*Recebe a resposta do jogador2 e compara às respostas certas*/
					i=0;
					while(i <= (reg.qtd-1)){
						scanf("\t\t\t\t%s",&resposta[i]);
						printf("\n\t\t\t\t\t\t");
						
						strcmp(reg.vetpalavras[i],resposta[i]);
						if(strcmp(reg.vetpalavras[i],resposta[i])==0){
							certo++;
							
						}
						i++;
					}
					/*Se as respostas estiverem erradas..*/
					if(certo == i){
							system("cls");
								granajogador1+=premioespecial;//adiciona o novo prêmio sorteado ao que o jogador já possui
								granajogador2=0;
								granajogador3=0;
								tela();
								vencedor();
								exit(0);
					}
					else{
						granajogador1=0;
					}		
					
					//JOGADOR2
					printf("\n\n\n\t\t\tJogador 2: Faltam 3 letras para completar a palavra");
					temporizador();
					printf("\n\t\t\tValendo R$%.2f a palavra é:",premioespecial);
					/*Recebe a resposta do jogador2 e compara às respostas certas*/
					i=0;
					while(i <= (reg.qtd-1)){
						scanf("\t\t\t\t%s",&resposta[i]);
						printf("\n\t\t\t\t\t\t");
						strcmp(reg.vetpalavras[i],resposta[i]);
						if(strcmp(reg.vetpalavras[i],resposta[i])==0){
							certo++;
						}
						i++;
					}
					/*Se as respostas estiverem erradas..*/
					if(certo == i){
							system("cls");
								granajogador2+=premioespecial;//adiciona o novo prêmio sorteado ao que o jogador já possui
								granajogador1=0;
								granajogador3=0;
								tela();
								vencedor();
								exit(0);
					}
					else{
						granajogador2=0;
						erroresposta=1;
						vencedor();
						exit(0);
					}			
				}				
		}
}

void   admin ( void )
{    
    menu();  
    switch ( escolha )
    {
        case '1' : 
        {
            cadastra();
        }
        break;
        
        case '2' : 
        {
            consulta();
        }
        break;
        
        case '3' : 
        {
            jogar();
        }
        break;
        
        case 's' : 
        case 'S' : exit (0); break;
    }
    getch();    
}
/* CORPO DO PROGRAMA */
main()
{
	setlocale(LC_ALL,"portuguese");
  do
  {
      admin();
  }
  while (escolha != 'S' && escolha != 's');
}


