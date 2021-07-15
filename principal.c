#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
/*  -------------------------------  VARIAVEIS   CONSTANTES -------------------------------------------------------   */
const char  INICIO[45]      =   "\nCadastre seus dados para ser atendido: \n",
            SIMOUNAO[53]    =   "\nDigite ( S ) para SIM ou ( N ) para NÃO.\n\t-->\t",
            PERGUNTA_1[22]  =   "Tem Febre? (5 pontos)",
            PERGUNTA_2[30]  =   "Tem dor de cabeça? (1 ponto)",
            PERGUNTA_3[43]  =   "Tem secreção nasal ou espirros? (1 ponto)",
            PERGUNTA_4[42]  =   "Tem dor/irritação na garganta? (1 ponto)",
            PERGUNTA_5[27]  =   "Tem tosse seca? (3 pontos)",
            PERGUNTA_6[42]  =   "Tem dificuldade respiratória? (10 pontos)",
            PERGUNTA_7[30]  =   "Tem dores no corpo? (1 ponto)",
            PERGUNTA_8[24]  =   "Tem diarréia? (1 ponto)",
            PERGUNTA_9[102] =   "Esteve em contato, nos últimos 14 dias, com um caso diagnosticado com COVID-19? (10 pontos)",
            PERGUNTA_10[53] =   "Esteve em locais com grande aglomeração? (3 pontos)";
/*  -------------------------------  VARIAVEIS PARA REGISTRO EM ARQUIVO ---------------------------------------------   */
char CPF[100]           = "\n\tCPF:",
     NOME[210]          = "\n\tNOME:",
     SEXO[30]           = "\n\tSEXO:",
     IDADE[50]          = "\n\tIDADE:",
     RESULTADO[50]      = "\n\tPontuação: ",
     resultado_txt[100] = "Vazio",
     gravaResultado[55],
    entCPF[20],
    entNome[200],
    entSexo[30],
    entIdade[4],
    decide;

int valores[10] = { 5, 1, 1, 1, 3, 10, 1, 1, 10, 3 },
    soma = 0,
    tri;

/*  -------------------------------  CLONE FUNÇÃO ---------------------------------------------------------------  */
int limpa();
int escreve();
int gravaTxt(char gravaDados[200]);
/*  -------------------------------  FUNÇÃO CADASTRO ---------------------------------------------------------------  */

/*  -------------------------------  FUNÇÃO CONTROLE DE RESPOSTA -----------------------------------------------------  */
int resposta(char a){          // Entrada de teclado ( S ) para SIM e ( N ) para NÃO
    if(a == 's' || a == 'S'){
        soma = soma + valores[tri];
    }
    else if(a == 'n' || a == 'N');
    else{
        printf("%s", SIMOUNAO);
        scanf("%s", &decide);
        resposta(decide);
    }
    return 0;
}
/*  -------------------------------  FUNÇÃO TRIAGEM (Perguntas ao paciente) ------------------------------------------  */
int triagem(int p){
    switch (p) {
        case 0:
            printf("%s %s", PERGUNTA_1, SIMOUNAO);
            break;
        case 1:
            printf("%s %s", PERGUNTA_2, SIMOUNAO);
            break;
        case 2:
            printf("%s %s", PERGUNTA_3, SIMOUNAO);
            break;
        case 3:
            printf("%s %s", PERGUNTA_4, SIMOUNAO);
            break;
        case 4:
            printf("%s %s", PERGUNTA_5, SIMOUNAO);
            break;
        case 5:
            printf("%s %s", PERGUNTA_6, SIMOUNAO);
            break;
        case 6:
            printf("%s %s", PERGUNTA_7, SIMOUNAO);
            break;
        case 7:
            printf("%s %s", PERGUNTA_8, SIMOUNAO);
            break;
        case 8:
            printf("%s %s", PERGUNTA_9, SIMOUNAO);
            break;
        case 9:
            printf("%s %s", PERGUNTA_10, SIMOUNAO);
            break;
    }
    if (p < 10){
        scanf("%s", &decide);
        resposta(decide);
    }
    return 0;
}

int main(){
    setlocale(LC_ALL, "Portuguese");                         //  FORMATA PADRÃO PORTUGUES

/*     ------------------------------------ Cadastro de dados pessoais do paciente ---------------------------------- */
    escreve(INICIO);

    printf(CPF);
    scanf("%s", &entCPF);

    printf("\n\tNOME:");
    scanf("%200[^\n]s", &entNome);  // CAPTURA FRASE INTEIRA


    printf(SEXO);
    scanf("%s", &entSexo);

    printf(IDADE);
    scanf("%s", &entIdade);

    limpa();
    /*     ------------------------------------ Triagem para decisão de encaminhamentos --------------------------------- */
    escreve("Triagem:");
    for (tri = 0; tri < 11; ++tri){

        escreve(triagem(tri));

    }
/*  ------------------------ Executa Função gravaTxt() - Para salvar dados coletados para arquivo    ---------------   */
    sprintf( gravaResultado, "\n\t%s %d",RESULTADO, soma );           // Concatena String e Inteiro
    gravaTxt("\n|-----------------------------------------------------|\n");
    gravaTxt( strcat( CPF, entCPF ));
    gravaTxt( strcat( NOME,   entNome   ));
    gravaTxt( strcat( SEXO,   entSexo   ));
    gravaTxt( strcat( IDADE,  entIdade  ));
    gravaTxt(gravaResultado);

    /*     ------------------------ Encaminha paciente para a ALA de acordo com sintomas  -------------------------------- */
    if(soma > 19){
        escreve("\n\n\tDirija-se para a ala de alto risco.");
        getchar();
    }
    else if(soma > 9){
        escreve("\n\n\tDirija-se para ala de médio risco.");
        getchar();
    }
    else{
        escreve("\n\n\tDirija-se para ala de baixo risco.");
        getchar();
    }

    escreve("\n\n\tPrecione ENTER para finalizar. ");


    getchar();

    return 0;
}   // fim do MAIN
/*  ---------------------------------   FUNÇÃO CRIA E GRAVA DADOS DA MEMORIA EM ARQUIVO ----------------------------- */
int gravaTxt(char gravaDados[200]){

    FILE *ponteiro;				// cria um ponteiro para o arquivo

    ponteiro = fopen("Registro.txt", "a");	// ABRE O ARQUIVO

    if(ponteiro == NULL){	 		// TESTE SE O ARQUIVO FOI ABERTO COM SUCESSO.
        escreve("Erro na abertura do arquivo!");
        return 1;
    }

    fputs(gravaDados, ponteiro);		// Grava dados no arquivo de texto

    fclose(ponteiro);				// FECHA ARQUIVO
    return 0;
}
/*     -------------------------------  Mantem tela e cache limpos -------------------------------------------------   */
int limpa(){
    fflush(stdin);
    // system("cls");   // Para WINDOWS
    system("clear");    // Para LINUX
}
/*     -------------------------------  Imprime uma linha para formatação -------------------------------------------   */
int escreve(char escr[100]){

    for (int i = 0; i < 52; i++) {
        printf("-");
    }
    printf("\n");
    printf(escr);
    printf("\n");
    for (int i = 0; i < 52; i++) {
        printf("-");
    }

    printf("\n");
}
