#include <stdio.h>
#include <string.h>

#define MAX_ESTUDANTES 15
#define MAX_DISCIPLINA 2
#define MAX_PROFESSOR 3

typedef struct
{
    char nome[50];
    int funcional;
    char titulacao[20];
} Professor;

typedef struct
{
    char nome[50];
    int codigo;
    int carga_horaria;
    Professor professor_responsavel;
} Disciplina;

typedef struct
{
    char nome[50];
    int matricula;
    int idade;
} Estudante;

void bubble_sort(Estudante *estudantes, int n)
{
    int i, j;
    Estudante temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (estudantes[j].idade > estudantes[j + 1].idade)
            {
                temp = estudantes[j];
                estudantes[j] = estudantes[j + 1];
                estudantes[j + 1] = temp;
            }
        }
    }
}

int le_valida_idade()
{
    int idade;
    do
    {
        printf("Digite a idade do estudante (entre 16 e 26): ");
        scanf("%d", &idade);
    } while (idade < 16 || idade > 26);
    return idade;
}

int main()
{
    Professor professores[MAX_PROFESSOR];
    Disciplina disciplinas[MAX_DISCIPLINA];
    Estudante estudantes[MAX_ESTUDANTES];

    int i, j, n1 = 0, n2 = 0;

    // Cadastro de professores
    for (i = 0; i < MAX_PROFESSOR; i++)
    {
        printf("Cadastro de Professor %d\n", i + 1);
        printf("Nome: ");
        scanf("%s", professores[i].nome);
        fflush(stdin);
        printf("Funcional: ");
        scanf("%d", &professores[i].funcional);
        fflush(stdin);
        printf("Titulacao (especialista, mestre ou doutor): ");
        scanf("%s", professores[i].titulacao);
        fflush(stdin);

        printf("\n");
    }

    // Cadastro de disciplinas
    for (i = 0; i < MAX_DISCIPLINA; i++)
    {
        printf("Cadastro de Disciplina %d\n", i + 1);
        printf("Nome: ");
        scanf("%s", disciplinas[i].nome);
        fflush(stdin);
        printf("Codigo: ");
        scanf("%d", &disciplinas[i].codigo);
        fflush(stdin);
        printf("Carga Horaria: ");
        scanf("%d", &disciplinas[i].carga_horaria);
        fflush(stdin);

        // Seleciona o professor responsavel
        printf("Selecione o professor responsavel:\n");
        for (j = 0; j < MAX_PROFESSOR; j++)
        {
            printf("%d - %s\n", j + 1, professores[j].nome);
        }
        int opcao;
        do
        {
            scanf("%d", &opcao);
        } while (opcao < 1 || opcao > MAX_PROFESSOR);
        disciplinas[i].professor_responsavel = professores[opcao - 1];
        printf("\n");
    }

    // Cadastro de estudantes
    for (i = 0; i < MAX_ESTUDANTES; i++)
    {
        printf("Cadastro de Estudante %d\n", i + 1);
        printf("Nome: ");
        scanf("%s", estudantes[i].nome);
        fflush(stdin);
        printf("Matricula: ");
        scanf("%d", &estudantes[i].matricula);
        fflush(stdin);
        estudantes[i].idade = le_valida_idade();

        // Seleciona a disciplina
        printf("Selecione a disciplina:\n");
        for (j = 0; j < MAX_DISCIPLINA; j++)
        {
            printf("%d - %s\n", j + 1, disciplinas[j].nome);
            fflush(stdin);
        }
        int opcao;
        do
        {
            scanf("%d", &opcao);
            fflush(stdin);
        } while (opcao < 1 || opcao > MAX_DISCIPLINA);

        // Verifica se a disciplina ja possui 10 estudantes
        if (opcao == 1 && n1 < 10)
        {
            n1++;
        }
        else if (opcao == 2 && n2 < 10)
        {
            n2++;
        }
        else
        {
            printf("Disciplina ja possui o numero maximo de estudantes matriculados!\n");
            i--;
            continue;
        }

        // Adiciona o estudante na disciplina selecionada
        disciplinas[opcao - 1].professor_responsavel = professores[opcao - 1];
        printf("\n");
    }

    // Relatorio de alunos matriculados na primeira disciplina ordenados por idade
    printf("Relatorio de Alunos Matriculados na Primeira Disciplina Ordenados por Idade\n");
    printf("Codigo da Disciplina\tNome do Professor\tNome do Estudante\tIdade do Estudante\n");
    bubble_sort(estudantes, n1);
    for (i = 0; i < n1; i++)
    {
        printf("\t%d\t\t\t%s\t\t\t%s\t\t\t%d\n", disciplinas[0].codigo, disciplinas[0].professor_responsavel.nome, estudantes[i].nome, estudantes[i].idade);
    }

    // Relatorio de alunos matriculados na segunda disciplina ordenados por idade em ordem decrescente
    printf("\nRelatorio de Alunos Matriculados na Segunda Disciplina Ordenados por Idade em Ordem Decrescente\n");
    printf("Codigo da Disciplina\tNome do Professor\tNome do Estudante\tIdade do Estudante\n");
    bubble_sort(estudantes + n1, n2);
    for (i = n2 - 1; i >= 0; i--)
    {
        printf("\t%d\t\t\t%s\t\t\t%s\t\t\t%d\n", disciplinas[1].codigo, disciplinas[1].professor_responsavel.nome, estudantes[n1 + i].nome, estudantes[n1 + i].idade);
    }

    return 0;
}
