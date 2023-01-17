#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define TAMNOME 50
#define TAMSOBRENO 50
#define qtddEstudantes 1000

//Estrutura
typedef struct data{
    int dia;
    int mes;
    int ano;
}data;
typedef struct registro{
    char nome[TAMNOME];
    char sobrenome[TAMSOBRENO];
    data datanascimento;
    int prontuario;
    char curso[4];
}aluno;
aluno alunos[qtddEstudantes];

//Cabeçalho das opções
void enfeite(op){
    printf("--- Opcao %d ---\n", op);
}

//Menu Principal
int Menu(op){
    printf("--- Menu ---\n");
    printf("1 - Cadastrar Aluno\n");
    printf("2 - Todos Alunos Cadastrados\n");
    printf("3 - Procurar Alunos\n");
    printf("4 - Ordenar Alunos\n");
    printf("5 - Carregar Arquivo\n");
    printf("6 - Gravar no Arquivo\n");
    printf("7 - Sair \n");
    printf("Escolha a sua opcao: ");
    scanf("%d",&op);
    return op;
}
//Menu da opcao 3
int menuOp3(op){
    printf("1 - Nome e sobrenome\n");
    printf("2 - Nome\n");
    printf("3 - Sobrenome\n");
    printf("4 - Prontuario\n");
    printf("5 - Data de nascimento\n");
    printf("6 - Curso\n");
    printf("Opcao: ");
    scanf("%d",&op);
    return op;
}
int menuOp4(op){
    printf("1 - Nome e sobrenome\n");
    printf("2 - Sobrenome e Nome\n");
    printf("3 - Data de nascimento\n");
    printf("4 - Prontuario\n");
    printf("5 - Curso\n");
    printf("Opcao: ");
    scanf("%d",&op);
    return op;
}
//Menu das formas de ordenar
int menuOrdenacao(op){
    printf("1 - Quick Sort\n");
    printf("2 - Merge Sort\n");
    printf("3 - Insertion Sort\n");
    printf("4 - Selection Sort\n");
    printf("Opcao: ");
    scanf("%d",&op);
    return op;
}
// Cadastramento da opcao 1
int Cadastrar(int cadastrados,aluno alunos[], int *ponteiro, int *ordenado){
    int op = 0;
    if(cadastrados < qtddEstudantes){
        do
        {
            printf("Nome: ");
            while(getchar() != '\n');
            gets(alunos[cadastrados].nome);
            printf("Sobrenome: ");
            gets(alunos[cadastrados].sobrenome);
            printf("Nascimento\n");
            printf("Dia: ");
            scanf("%d",&alunos[cadastrados].datanascimento.dia);
            printf("Mes: ");
            scanf("%d",&alunos[cadastrados].datanascimento.mes);
            printf("Ano: ");
            scanf("%d",&alunos[cadastrados].datanascimento.ano);
            alunos[cadastrados].prontuario = GeradorDeProntuarios(ponteiro);
            printf("Prontuario: SC%d\n",alunos[cadastrados].prontuario);
            printf("Para o nome do curso use abreviacoes como: ADS\n");
            printf("Curso: ");
            while(getchar() != '\n');
            gets(alunos[cadastrados].curso);
            cadastrados += 1;
            *ordenado = 0;
            printf("Deseja cadastrar mais alunos ?\n");
            printf("1 - Sim\n2 - Nao \nOpcao:");
            scanf("%d",&op);
        } while (op != 2);
        return cadastrados;
    }else{
        printf("Quantidade maxima de estudantes atingida! \n");
    }
}
//Gerando prontuários de forma somatória
int GeradorDeProntuarios(int *prontuario){
    return *prontuario += 1;
}

//Listamento dos alunos da opcao 2
void ListarAlunos(int cadastrados, aluno alunos[]){
    int i;
    for(i = 0; i < cadastrados; i++){
        printf("--- Aluno %d ---\n",i+1);
        printf("Alun@: %s %s\n",alunos[i].nome,alunos[i].sobrenome);
        printf("Nascimento: %d %d %d\n",alunos[i].datanascimento.dia,alunos[i].datanascimento.mes,alunos[i].datanascimento.ano);
        printf("Prontuario: SC%d\n",alunos[i].prontuario);
        printf("Curso: %s\n",alunos[i].curso);
    }
}
//Mostrar o aluno da opcao 3 passando sua posicao como referencia
void MostrarAlunoOp3(int i,aluno alunos[]){
    printf("\nAlun@: %s %s\n",alunos[i].nome,alunos[i].sobrenome);
    printf("Nascimento: %d %d %d\n",alunos[i].datanascimento.dia,alunos[i].datanascimento.mes,alunos[i].datanascimento.ano);
    printf("Prontuario: SC%d\n",alunos[i].prontuario);
    printf("Curso: %s\n",alunos[i].curso);
}
//Procurando o aluno por nome e sobrenome
int ProcurarAlunoNomeCompleto(int cadastrados, char procuraNome[],char procuraSobrenome[],int i,aluno alunos[],int tipo){
    int indice = 0,removeAlunos[cadastrados],op,tamVetor=0;
    if(tipo == 1){
        int indiceBinario;
        aluno aux;
        strcpy(aux.nome,procuraNome);
        strcpy(aux.sobrenome,procuraSobrenome);
        indiceBinario = BuscaBinaria(alunos,cadastrados,aux,tipo);
        if(indiceBinario == -1){
            printf("Aluno não encontrado\n");
            return cadastrados;
        }else{
            tamVetor = verificarProximos(removeAlunos,indiceBinario,aux,alunos,tipo,cadastrados);
            cadastrados = DesejaRemoverBinario(removeAlunos,tamVetor,cadastrados,alunos);
            return cadastrados;
        }
    }else{
        for (i = 0; i < cadastrados; i++){
            if(strcmp(alunos[i].nome,procuraNome) == 0 && strcmp(alunos[i].sobrenome,procuraSobrenome)==0){
                MostrarAlunoOp3(i,alunos);
                removeAlunos[indice] = i;
                indice++;
                tamVetor++;
            }
        }
        if (indice == 0){
            printf("Aluno nao encontrado\n");
        }else{
            cadastrados = DesejaRemover(removeAlunos,tamVetor,cadastrados,alunos);
        }
        return cadastrados;
    }
}
//Procurando o aluno por nome
int ProcurarAlunoNome(int cadastrados, char procuraNome[],int i,aluno alunos[], int tipo){
    int indice = 0,removeAlunos[cadastrados],op,tamVetor=0;
    if(tipo == 1){
        int indiceBinario;
        tipo = 6;//Buscar apenas com um nome
        aluno aux;
        strcpy(aux.nome,procuraNome);
        indiceBinario = BuscaBinaria(alunos,cadastrados,aux,tipo);
        if(indiceBinario == -1){
            printf("Aluno não encontrado\n");
            return cadastrados;
        }else{
            tamVetor = verificarProximos(removeAlunos,indiceBinario,aux,alunos,tipo,cadastrados);
            cadastrados = DesejaRemoverBinario(removeAlunos,tamVetor,cadastrados,alunos);
            return cadastrados;
        }
    }else{
        for (i = 0; i < cadastrados; i++){
            if(strcmp(alunos[i].nome,procuraNome) == 0){
                MostrarAlunoOp3(i,alunos);
                removeAlunos[indice] = i;
                indice++;
                tamVetor++;
            }
        }
        if (indice == 0){
            printf("Aluno nao encontrado\n");
        }else{
            cadastrados = DesejaRemover(removeAlunos,tamVetor,cadastrados,alunos);
        }
        return cadastrados;
    }

}
//Procura aluno pelo sobrenome
int ProcuraAlunoSobrenome(int cadastrados, char procuraSobrenome[],int i,aluno alunos[],int tipo){
    int indice = 0,removeAlunos[cadastrados],op,tamVetor=0;
    if(tipo == 2){
        int indiceBinario;
        tipo = 7;//comparação apenas com sobrenome
        aluno aux;
        strcpy(aux.sobrenome,procuraSobrenome);
        indiceBinario = BuscaBinaria(alunos,cadastrados,aux,tipo);
        if(indiceBinario == -1){
            printf("Aluno não encontrado\n");
            return cadastrados;
        }else{
            tamVetor = verificarProximos(removeAlunos,indiceBinario,aux,alunos,tipo,cadastrados);
            cadastrados = DesejaRemoverBinario(removeAlunos,tamVetor,cadastrados,alunos);
            return cadastrados;
        }
    }else{
        for (i = 0; i < cadastrados; i++){
            if(strcmp(alunos[i].sobrenome,procuraSobrenome) == 0){
                MostrarAlunoOp3(i,alunos);
                removeAlunos[indice] = i;
                indice++;
                tamVetor++;
            }
        }
        if (indice == 0){
            printf("Aluno nao encontrado\n");
        }else{
            cadastrados = DesejaRemover(removeAlunos,tamVetor,cadastrados,alunos);
        }
        return cadastrados;
    }
}
//Procura aluno pelo prontuario
int ProcuraAlunoProntuario(int cadastrados, int procuraProntuario[],int i,aluno alunos[],int tipo){
    int indice = 0,removeAlunos[cadastrados],op,tamVetor=0;
    if(tipo == 4){
        int indiceBinario;
        aluno aux;
        aux.prontuario = procuraProntuario;
        indiceBinario = BuscaBinaria(alunos,cadastrados,aux,tipo);
        if(indiceBinario == -1){
            printf("Aluno não encontrado\n");
            return cadastrados;
        }else{
            tamVetor = verificarProximos(removeAlunos,indiceBinario,aux,alunos,tipo,cadastrados);
            cadastrados = DesejaRemoverBinario(removeAlunos,tamVetor,cadastrados,alunos);
            return cadastrados;
        }
    }else{
        for (i = 0; i < cadastrados; i++){
            if(procuraProntuario == alunos[i].prontuario){
                MostrarAlunoOp3(i,alunos);
                removeAlunos[indice] = i;
                indice++;
                tamVetor++;
            }
        }
        if (indice == 0){
            printf("Aluno nao encontrado\n");
        }else{
            cadastrados = DesejaRemover(removeAlunos,tamVetor,cadastrados,alunos);
        }
        return cadastrados;
    }
}
//Procura aluno pela data de nascimento
int ProcuraAlunoNascimento(int cadastrados,int pDia,int pMes,int pAno,int i,aluno alunos[], int tipo){
    int indice = 0,removeAlunos[cadastrados],op,tamVetor = 0;
    if(tipo == 3){
        int indiceBinario;
        aluno aux;
        aux.datanascimento.dia = pDia;
        aux.datanascimento.mes = pMes;
        aux.datanascimento.ano = pAno;
        indiceBinario = BuscaBinaria(alunos,cadastrados,aux,tipo);
        if(indiceBinario == -1){
            printf("Aluno não encontrado\n");
            return cadastrados;
        }else{
            tamVetor = verificarProximos(removeAlunos,indiceBinario,aux,alunos,tipo,cadastrados);
            cadastrados = DesejaRemoverBinario(removeAlunos,tamVetor,cadastrados,alunos);
            return cadastrados;
        }
    }else{
        for (i = 0; i < cadastrados; i++){
            if(pDia == alunos[i].datanascimento.dia && pMes == alunos[i].datanascimento.mes && pAno == alunos[i].datanascimento.ano){
                MostrarAlunoOp3(i,alunos);
                removeAlunos[indice] = i;
                indice++;
                tamVetor++;
            } 
        }
        if (indice == 0){
            printf("Aluno nao encontrado\n");
        }else{
            cadastrados = DesejaRemover(removeAlunos,tamVetor,cadastrados,alunos);
        }
        return cadastrados;
    }
}
//Procura aluno pelo curso
int ProcuraAlunoCurso(int cadastrados, char procuraCurso[], int i, aluno alunos[],char tipo){
    int tamVetor = 0,indice = 0,removeAlunos[cadastrados];
    if(tipo == 5){
        int indiceBinario;
        aluno aux;
        strcpy(aux.curso, procuraCurso);
        indiceBinario = BuscaBinaria(alunos,cadastrados,aux,tipo);
        if(indiceBinario == -1){
            printf("Aluno não encontrado\n");
            return cadastrados;
        }else{
            tamVetor = verificarProximos(removeAlunos,indiceBinario,aux,alunos,tipo,cadastrados);
            cadastrados = DesejaRemoverBinario(removeAlunos,tamVetor,cadastrados,alunos);
            return cadastrados;
        }
    }else{
        for (i = 0; i < cadastrados; i++){
            if(strcmp(procuraCurso, alunos[i].curso)==0){
                MostrarAlunoOp3(i,alunos);
                removeAlunos[indice] = i;
                indice++;
                tamVetor++;
            } 
        }
        if (tamVetor == 0){
            printf("Aluno nao encontrado\n");
        }else{
            cadastrados = DesejaRemover(removeAlunos,tamVetor,cadastrados,alunos);
        }
        return cadastrados;
    }
}
//Busca Binário
int BuscaBinaria(aluno alunos[], int tamanho, aluno chave, int tipo){
    printf("OBS: Modelo Binario sendo usado ...\n");
    int ini = 0;
    int fim = tamanho-1;
    int meio;
    while(ini <= fim){
        meio = (ini+fim)/2;
        if(Comparacoes(chave,alunos[meio],tipo) == 0) return meio;
        if(Comparacoes(chave,alunos[meio],tipo) == 2) fim = meio-1;
        else ini = meio+1;
    }
    return -1;
}
//Verifica se existe algum elemento a mais além o que a busca binária faz
int verificarProximos(int removeAlunos[],int indiceBinario,aluno aux,aluno alunos[],int tipo,int cadastrados){
    int i = 0,tamanho;
    while(Comparacoes(aux,alunos[indiceBinario+i],tipo)==0){
        if(indiceBinario+1 <= cadastrados){
            MostrarAlunoOp3(indiceBinario+i,alunos);
            removeAlunos[i] = indiceBinario+i;
            i++;
        }
    }
    tamanho = verificarAnteriores(removeAlunos,indiceBinario,aux,alunos,tipo,i);
    return tamanho;
}
//Verificar Anteriores
int verificarAnteriores(int removeAlunos[],int indiceBinario,aluno aux,aluno alunos[],int tipo, int tamanhoVetor){
    int i = 1;
    while(Comparacoes(aux,alunos[indiceBinario-i],tipo)==0){
        if(indiceBinario-1 >= 0){
            MostrarAlunoOp3(indiceBinario-i,alunos);
            removeAlunos[tamanhoVetor] = indiceBinario-i;
            tamanhoVetor += 1;
            i++;
        }
    }
    return tamanhoVetor;
}
//Confirmacao para remover
int DesejaRemover(int vetor[],int tamVetor, int cadastrados,aluno alunos[]){
    int i,op,k,posicao;
    printf("Deseja excluir esses alunos ?\n");
        printf("1-Sim\n2-Nao\n");
        printf("Opcao: ");
        scanf("%d",&op);
        switch (op){
            case 1:
                for(i = 0;i<tamVetor;i++){
                    for(k = vetor[i]-i; k<cadastrados;k++){
                        alunos[k] = alunos[k+1];
                    }
                    cadastrados--;
                }
                printf("Alun@(s) exluido(s) com sucesso!\n");
                break;
            case 2:
                printf("Nenhum aluno excluido\n");
                break;
            default:
            printf("Opcao nao encontrada!");
                break;
        }
    return cadastrados;
}
int DesejaRemoverBinario(int vetor[],int tamVetor, int cadastrados,aluno alunos[]){
    int i,op,k,posicao;
    printf("Deseja excluir esses alunos ?\n");
        printf("1-Sim\n2-Nao\n");
        printf("Opcao: ");
        scanf("%d",&op);
        switch (op){
            case 1:
                for(i = 0;i<tamVetor;i++){
                    for(k = vetor[i]; k<cadastrados;k++){
                        alunos[k] = alunos[k+1];
                    }
                    cadastrados--;
                }
                printf("Alun@(s) exluido(s) com sucesso!\n");
                break;
            case 2:
                printf("Nenhum aluno excluido\n");
                break;
            default:
            printf("Opcao nao encontrada!");
                break;
        }
    return cadastrados;
}
//Opções para ordenação
void escolhaParaOrdenar(int cadastrados, aluno alunos[], int tipo){
    int op, ini = 0;
    op = menuOrdenacao(op);
    switch (op){
    case 1:
        OrdenacaoPorQuickSort(ini, cadastrados-1, alunos, tipo);
        break;
    case 2:
        OrdenacaoPorMergeSort(ini,cadastrados-1,alunos,tipo);
        break;
    case 3:
        OrdenacaoPorInsertioSort(alunos,cadastrados,tipo);
        break;
    case 4:
        OrdecaoPorSelectionSort(alunos,cadastrados,tipo);
        break;
    default:
        printf("Opção inválida");
        break;
    }
}

int Comparacoes(aluno valor1, aluno valor2, int tipo){
    //valor1 > valor2 return 1
    //valor1 < valor2 return 2
    //valor1 == valor2 return 0

    char nome1[50],nome2[50],sobrenome1[50],sobrenome2[50],completo1[100],completo2[100];//Nome e Sobrenome
    switch (tipo){
    case 1://Nome e Sobrenome
        strcpy(nome1, valor1.nome);
        strcpy(sobrenome1, valor1.sobrenome);
        strcpy(completo1,strcat(nome1,sobrenome1));

        strcpy(nome2, valor2.nome);
        strcpy(sobrenome2, valor2.sobrenome);
        strcpy(completo2,strcat(nome2,sobrenome2));

        if(strcmp(completo1,completo2) > 0){
            return 1;
        }
        else if(strcmp(completo1,completo2) < 0){
            return 2;
        }
        else{
            return 0;
        }
        break;
    case 2://Sobrenome e nome
        strcpy(nome1, valor1.nome);
        strcpy(sobrenome1, valor1.sobrenome);
        strcpy(completo1,strcat(sobrenome1,nome1));

        strcpy(nome2, valor2.nome);
        strcpy(sobrenome2, valor2.sobrenome);
        strcpy(completo2,strcat(sobrenome2,nome2));

        if(strcmp(completo1,completo2) > 0){
            return 1;
        }
        else if(strcmp(completo1,completo2) < 0){
            return 2;
        }
        else{
            return 0;
        }
        break;
    case 3://Data de Nascimento
        compareData(valor1,valor2);
        break;
    case 4://Prontuário
        if(valor1.prontuario > valor2.prontuario){
            return 1;
        }else if(valor1.prontuario < valor2.prontuario){
            return 2;
        }else{
            return 0;
        }
        break;
    case 5://por curso
        if(strcmp(valor1.curso,valor2.curso) > 0){
            return 1;
        }else if(strcmp(valor1.curso,valor2.curso) < 0){
            return 2;
        }else{
            return 0;
        }
        break;
    case 6://Apenas um nome
        strcpy(nome1, valor1.nome);
        strcpy(nome2, valor2.nome);

        if(strcmp(nome1,nome2) > 0){
            return 1;
        }
        else if(strcmp(nome1,nome2) < 0){
            return 2;
        }
        else{
            return 0;
        }
        break;
    case 7://Apenas Sobrenome
        strcpy(nome1, valor1.sobrenome);
        strcpy(nome2, valor2.sobrenome);

        if(strcmp(nome1,nome2) > 0){
            return 1;
        }
        else if(strcmp(nome1,nome2) < 0){
            return 2;
        }
        else{
            return 0;
        }
        break;
    }
}
//Modelo QuickSort
void OrdenacaoPorQuickSort(int ini,int fim, aluno alunos[], int tipo){
    int pos;
    if(ini < fim){
        pos = particionar(alunos, ini, fim, tipo);
        OrdenacaoPorQuickSort(ini, pos-1, alunos, tipo);
        OrdenacaoPorQuickSort(pos, fim, alunos, tipo);
    }

}

int particionar(aluno alunos[], int ini, int fim, int tipo){
    aluno pivo;
    aluno aux;

    pivo = alunos[fim];
    while (ini < fim){
        while (ini < fim && (Comparacoes(alunos[ini],pivo,tipo) == 2 || Comparacoes(alunos[ini],pivo,tipo) == 0)){
            ini++;
        }
       
        while (ini < fim && (Comparacoes(alunos[fim],pivo,tipo) == 1)){
            fim--;
        }
        
        aux = alunos[ini];
        alunos[ini] = alunos[fim];
        alunos[fim] = aux;
    }
    
    return ini; //Obs a primeira posição do elemento grande
}
//Modelo Margen Sort
void OrdenacaoPorMergeSort(int ini,int fim, aluno alunos[], int tipo){
    int meio;
    if(ini < fim){
        meio = (ini + fim) / 2;
        OrdenacaoPorMergeSort(ini,meio,alunos,tipo);//Ordenar do meio para tras
        OrdenacaoPorMergeSort(meio+1,fim,alunos,tipo);//Ordenar dps do meio
        intercalar(alunos,ini,meio,fim,tipo);
    }
}

void intercalar(aluno alunos[],int ini,int meio,int fim,int tipo){
    aluno vetorAux[qtddEstudantes];
    int i = ini, j = meio + 1, k = 0;

    while(i <= meio && j <= fim){
        if(Comparacoes(alunos[j],alunos[i],tipo) <= 1){
            vetorAux[k++] = alunos[i++];
        }else{
            vetorAux[k++] = alunos[j++];
        }
    }
    //Copiando o resto do subveto
    while (i <= meio){
        vetorAux[k++] = alunos[i++];
    }
    while (j <= fim){
        vetorAux[k++] = alunos[j++];
    }
    //Copiando os auxiliares para o vetor
    for(i = ini, k = 0; i <= fim; i++, k++){
        alunos[i] = vetorAux[k];
    }
}

//Modelo insertion sort
void OrdenacaoPorInsertioSort(aluno alunos[], int tamanhoVet, int tipo){
    int i,j;
    aluno aux;

    for(i = 1; i < tamanhoVet; i++){
        aux = alunos[i];
        j = i - 1;
        while(j >= 0 && Comparacoes(alunos[j],aux,tipo) == 1){
            alunos[j+1] = alunos[j];
            j--;
        }
        alunos[j+1] = aux;
    }
}

//Modelo Selection Sort
void OrdecaoPorSelectionSort(aluno alunos[], int cadastrados, int tipo){
    int i, menor;
    for(i = 0; i < cadastrados; i++){
        menor = menorElemento(alunos,cadastrados,i,tipo);
        trocarValores(&alunos[i], &alunos[menor]);
    }

}

void trocarValores(aluno *valor1, aluno *valor2){
    aluno aux = *valor1;
    *valor1 = *valor2;
    *valor2 = aux;
}

int menorElemento(aluno alunos[], int tamVetor, int primeiro, int tipo){
    int i,menor = primeiro;
    for (i = primeiro + 1; i < tamVetor; i++){
        if(Comparacoes(alunos[i],alunos[menor],tipo) == 2){
            menor = i;
        }
    }
    return menor;
}

void OrdenarPorNome(int cadastrados, aluno alunos[], int *tipoOrdem){
    int tipo = 1; //Para Nome e sobrenome
    *tipoOrdem = tipo;
    escolhaParaOrdenar(cadastrados, alunos, tipo);
    ListarAlunos(cadastrados,alunos);
}

void OrdenarPorSobrenome(int cadastrados,aluno alunos[],int *tipoOrdem){
    int tipo = 2; //Para Sobrenome e nome
    *tipoOrdem = tipo;
    escolhaParaOrdenar(cadastrados,alunos,tipo);
    ListarAlunos(cadastrados,alunos);
}

void OrdenarPorNascimento(int cadastrados, aluno alunos[],int *tipoOrdem){
    int tipo = 3;//Para Data de Nascimento
    *tipoOrdem = tipo;
    escolhaParaOrdenar(cadastrados,alunos,tipo);
    ListarAlunos(cadastrados,alunos);
}

int compareData(aluno a1,aluno a2){
    int soma;
    soma = ((a1.datanascimento.ano*10000+a1.datanascimento.mes*100+a1.datanascimento.dia)-(a2.datanascimento.ano*10000+a2.datanascimento.mes*100+a2.datanascimento.dia));
    if(soma > 0){
        return 1;
    }else if(soma < 0){
        return 2;
    }else{
        return 0;
    }
}

void OrdenarPorProntuario(int cadastrados,aluno alunos[],int *tipoOrdem){
    int tipo = 4;
    *tipoOrdem = tipo;
    escolhaParaOrdenar(cadastrados,alunos,tipo);
    ListarAlunos(cadastrados,alunos);
}

void OrdenarPorCurso(int cadastrados,aluno alunos[],int *tipoOrdem){
    int tipo = 5;//Curso
    *tipoOrdem = tipo;
    escolhaParaOrdenar(cadastrados,alunos,tipo);
    ListarAlunos(cadastrados,alunos);
}

//Coloca dados no arquivo
void escreverNoArquivo(int cadastrados, aluno alunos[]){
    FILE *arquivo;
    arquivo = fopen("escola1","wb");
    if(arquivo != NULL){
        fwrite(alunos, sizeof(aluno), cadastrados, arquivo);
        fclose(arquivo);
        printf("Dados salvos com sucesso!\n");
        
    }else{
        printf("[ERRO] falha ao abrir o arquivo");
    }
}

//Carregar dados do arquivo
int carregarDoArquivo(int cadastrados,aluno alunos[]){
    FILE *arquivo;
    
    arquivo = fopen("escola1","rb");
    if(arquivo != NULL){
        cadastrados = fread(alunos,sizeof(aluno),qtddEstudantes,arquivo);
        fclose(arquivo);
        printf("Dados carregados com sucesso!\n");
    }else{
        printf("[ERRO] falha ao abrir o arquivo\n");
    }
    return cadastrados;
}

//Funcao principal
void main(){
    char procuraNome[100],procuraSobrenome[100],procuraCurso[4],nomeArq[50];
    int op,cadastrados = 0,i,opBusca,procuraProntuario,pDia,pMes,pAno,prontuario=1000, tipoOrdem = 0;
    
    aluno alunos[qtddEstudantes];

    while(op != 7){
    op = Menu(op);
    switch (op){
    case 1:
        enfeite(1);
        cadastrados = Cadastrar(cadastrados,alunos, &prontuario, &tipoOrdem);
        break;
    case 2:
        enfeite(2);
        ListarAlunos(cadastrados,alunos);
        break;
    case 3:
        enfeite(3);
        printf("Qual sera a forma de procura: \n");
        opBusca = menuOp3(opBusca);
        switch (opBusca){
        case 1:
            while(getchar() != '\n');
            printf("Nome: ");
            gets(procuraNome);
            printf("Sobrenome: ");
            gets(procuraSobrenome);
            cadastrados = ProcurarAlunoNomeCompleto(cadastrados, procuraNome, procuraSobrenome, i,alunos,tipoOrdem);
            break;
        case 2:
            while(getchar() != '\n');
            printf("Nome: ");
            gets(procuraNome);
            cadastrados = ProcurarAlunoNome(cadastrados, procuraNome, i,alunos,tipoOrdem);
            break;
        case 3:
            while(getchar() != '\n');
            printf("Sobrenome: ");
            gets(procuraSobrenome);   
            cadastrados = ProcuraAlunoSobrenome(cadastrados, procuraSobrenome, i,alunos,tipoOrdem);
            break;
        case 4:
            while(getchar() != '\n');
            printf("Prontuario: SC");
            scanf("%d",&procuraProntuario);   
            cadastrados = ProcuraAlunoProntuario(cadastrados, procuraProntuario, i,alunos,tipoOrdem);
            break;
        case 5:
            while(getchar() != '\n')
                printf("Nascimento\n");
                printf("Dia: ");
                scanf("%d",&pDia);
                printf("Mes: ");
                scanf("%d",&pMes);
                printf("Ano: ");
                scanf("%d",&pAno);
                cadastrados = ProcuraAlunoNascimento(cadastrados,pDia,pMes,pAno,i,alunos,tipoOrdem);
                break;
        case 6:
            while(getchar() != '\n');
            printf("Curso: ");
            gets(procuraCurso);
            cadastrados = ProcuraAlunoCurso(cadastrados, procuraCurso, i, alunos,tipoOrdem);
            break;
        }
        break;
    case 4:
        enfeite(4);
        printf("Qual sera a forma de ordenacao: \n");
        opBusca = menuOp4(opBusca);
        switch (opBusca){
            case 1:
                OrdenarPorNome(cadastrados,alunos,&tipoOrdem);
                break;
            case 2:
                OrdenarPorSobrenome(cadastrados,alunos,&tipoOrdem);
                break;
            case 3:
                OrdenarPorNascimento(cadastrados,alunos,&tipoOrdem);
                break;
            case 4:
                OrdenarPorProntuario(cadastrados,alunos,&tipoOrdem);
                break;
            case 5:
                OrdenarPorCurso(cadastrados,alunos,&tipoOrdem);
                break;
            }
        break;
    case 5:
        enfeite(5);
        cadastrados = carregarDoArquivo(cadastrados,alunos);
        prontuario += cadastrados;
        break;
    case 6:
        enfeite(6);
        escreverNoArquivo(cadastrados,alunos);
        break;
    default:
        printf("--- Opcao 7 ---\n");
        printf("Obrigado por usar o nosso programa\nAte a proxima\n");
        break;
        }
    }
}