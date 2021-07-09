#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

/*  -------------------------------  VARIAVEIS   CONSTANTES -------------------------------------------------------   */
const char  INICIO[45] =        "\nCadastre seus dados para ser atendido: \n",
            SIMOUNAO[53] =      "\nDigite ( S ) para SIM ou ( N ) para NÃO.\n\t-->\t",
            PERGUNTA_1[22] =    "Tem Febre? (5 pontos)",
            PERGUNTA_2[30] =    "Tem dor de cabeça? (1 ponto)",
            PERGUNTA_3[43] =    "Tem secreção nasal ou espirros? (1 ponto)",
            PERGUNTA_4[42] =    "Tem dor/irritação na garganta? (1 ponto)",
            PERGUNTA_5[27] =    "Tem tosse seca? (3 pontos)",
            PERGUNTA_6[42] =    "Tem dificuldade respiratória? (10 pontos)",
            PERGUNTA_7[30] =    "Tem dores no corpo? (1 ponto)",
            PERGUNTA_8[24] =    "Tem diarréia? (1 ponto)",
            PERGUNTA_9[102] =   "Esteve em contato, nos últimos 14 dias, com um caso diagnosticado com COVID-19? (10 pontos)",
            PERGUNTA_10[53] =   "Esteve em locais com grande aglomeração? (3 pontos)";
/*  -------------------------------  VARIAVEIS PARA REGISTRO EM ARQUIVO ---------------------------------------------   */
char    CPF[100] =           "\n\tCPF:    ",
        NOME[210] =          "\n\tNOME:   ",
        SEXO[50] =          "\n\tSEXO:   ",
        IDADE[50] =         "\n\tIDADE:  ",
        RESULTADO[50]   =    "\n\tPontuação: ",
        entCPF[20],    // dadosPaciente[0]
        entNome[200],   // dadosPaciente[1]
        entSexo[30],   // dadosPaciente[2]
        entIdade[4],  // dadosPaciente[3]
        decide;

int valores[10] = { 5, 1, 1, 1, 3, 10, 1, 1, 10, 3 },
    soma = 0,           // dadosPaciente[4]
    tri;

/*  -------------------------------  CLONE FUNÇÃO ---------------------------------------------------------------  */
int limpa();
int linha();
int gravaTxt(char gravaDados[200]);
/*  -------------------------------  FUNÇÃO CADASTRO ---------------------------------------------------------------  */
int cadastro(int ent)
{
    switch (ent) {
        case 0:
            printf(CPF);
            scanf("%s", &entCPF);
            getchar();
            break;
        case 1:
            printf(NOME);
            scanf("%200[^\n]s", &entNome);  // CAPTURA FRASE INTEIRA
            getchar();
            break;
        case 2:
            printf(SEXO);
            scanf("%s", &entSexo);
            getchar();
            break;
        case 3:
            printf(IDADE);
            scanf("%s", &entIdade);
            getchar();
            break;
    }
}
/*  -------------------------------  FUNÇÃO CONTROLE DE RESPOSTA -----------------------------------------------------  */
int resposta(char a)          // Entrada de teclado ( S ) para SIM e ( N ) para NÃO
{
    if(a == 's' || a == 'S')
    {
        soma = soma + valores[tri];
    }
    else if(a == 'n' || a == 'N');
    else
    {
        printf("%s", SIMOUNAO);
        scanf("%s", &decide);
        resposta(decide);
    }
    return 0;
}
/*  -------------------------------  FUNÇÃO TRIAGEM (Perguntas ao paciente) ------------------------------------------  */
int triagem(int p)
{
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
    if (p < 10)
    {
        scanf("%s", &decide);
        resposta(decide);
    }
    return 0;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");                         //  FORMATA PADRÃO PORTUGUES
    linha();
/*     ------------------------------------ Cadastro de dados pessoais do paciente ---------------------------------- */
    printf(INICIO);
    for (int cad = 0; cad < 4; cad++)
    {
        cadastro(cad);
    }
    limpa();
/*     ------------------------------------ Triagem para decisão de encaminhamentos --------------------------------- */
    linha();
    for (tri = 0; tri < 11; ++tri)
    {
        linha();
        triagem(tri);
        limpa();
    }

    gravaTxt("\n|-----------------------------------------------------|\n");
    gravaTxt( strcat( CPF, entCPF ));
    gravaTxt( strcat( NOME,   entNome   ));
    gravaTxt( strcat( SEXO,   entSexo   ));
    gravaTxt( strcat( IDADE,  entIdade  ));
    
/*     ------------------------ Encaminha paciente para a ALA de acordo com sintomas  -------------------------------- */
    if(soma > 19)
    {      
        gravaTxt(strcat(RESULTADO,"ALTO RISCO"));
        printf("\n\n\tDirija-se para a ala de alto risco.");
    }
    else if(soma > 9)
    {
        gravaTxt(strcat(RESULTADO,"MÉDIO RISCO"));  
        printf("\n\n\tDirija-se para ala de médio risco.");
    }
    else
    {
        gravaTxt(strcat(RESULTADO,"BAIXO RISCO"));
        printf("\n\n\tDirija-se para ala de baixo risco.");
    }

    linha();
    printf("\n\n\tPrecione ENTER para finalizar. ");
    getchar();

    limpa();
    linha();
/*     -------------------------------------------------------------------------------------------------------------- */    
return 0;
}   // fim do MAIN
/*  ---------------------------------   FUNÇÃO CRIA E GRAVA DADOS DA MEMORIA EM ARQUIVO ----------------------------- */
int gravaTxt(char gravaDados[200])
{
    FILE *ponteiroTXT; // cria um ponteiro para o arquivo

    ponteiroTXT = fopen("Registro.txt", "a");   // ABRE O ARQUIVO

    if(ponteiroTXT == NULL) // TESTE SE O ARQUIVO FOI ABERTO COM SUCESSO.
    {
        printf("Erro na abertura do arquivo!");
        return 1;
    }

/*     -------------------------------  CONTEÚDO A SER GRAVADO VAI AQUI -------------------------------------------   */
    fputs(gravaDados, ponteiroTXT);
    fclose(ponteiroTXT);    // FECHA ARQUIVO
    return 0;
}

/*     -------------------------------  Mantem tela e cache limpos -------------------------------------------------   */
int limpa()                                                   
{
    fflush(stdin);  
    system("clear");
}
/*     -------------------------------  Imprime uma linha para formatação -------------------------------------------   */
int linha()                                                   
{
    printf("\n");
    for (int i = 0; i < 52; i++) {
        printf("-");
    }
    printf("\n");
}