/*
    Campos:  nome: (string com espaco)
                valor: (float)
                data: (string)
                desenvolvedora: (string com espaco)
                pico_max: (int)
                genero: (string com espaco)              */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct jogo // cria uma struct para armazenar os dados
{
    string nome;
    float valor;
    string data;
    string desenvolvedora;
    int pico_max;
    string genero;
};

bool lerUma(ifstream &arqJogos, jogo &umJogo) // ler uma linha do arquivo
{

    if (not(getline(arqJogos, umJogo.nome, ',')))
    {
        return false;
    };
    if (not(arqJogos >> umJogo.valor))
    {
        cout << "Erro na leitura do valor" << endl;
        return false;
    };
    arqJogos.ignore();
    if (not(getline(arqJogos, umJogo.data, ',')))
    {
        cout << "Erro na leitura da data" << endl;
        return false;
    };
    if (not(getline(arqJogos, umJogo.desenvolvedora, ',')))
    {
        cout << "Erro na leitura da desenvolvedora" << endl;
        return false;
    };
    if (not(arqJogos >> umJogo.pico_max))
    {
        cout << "Erro na leitura do pico maximo" << endl;
        return false;
    };
    arqJogos.ignore();
    if (not(getline(arqJogos, umJogo.genero)))
    {
        cout << "Erro na leitura do genero" << endl;
        return false;
    };
    return true;
}

jogo *lerDados(ifstream &arqJogos, jogo *vetorJogos, int &numRegistros, int &tamanho) // ler todas as linhas do arquivo
{
    jogo umJogo;
    while (lerUma(arqJogos, umJogo))
    {
        if (tamanho >= numRegistros) // verificando o tamanho do vetor, se for maior que o numero de registros, aumenta o tamanho do vetor
        {
            jogo *novoVetor = new jogo[numRegistros * 2];           // cria um novo vetor com o dobro do tamanho
            copy(vetorJogos, vetorJogos + numRegistros, novoVetor); // copia os dados do vetor antigo para o novo
            delete[] vetorJogos;                                    // deleta o vetor antigo
            vetorJogos = novoVetor;                                 // atribui o novo vetor ao vetor antigo
        }
        vetorJogos[tamanho] = umJogo; // atribui os dados lidos ao vetor
        tamanho++;                    // aumenta o tamanho
    }
    return vetorJogos;
}

void imprimirDados(jogo *vetorJogos, int numRegistros) // imprime os dados
{
    for (int i = 0; i < numRegistros; i++)
    {
        cout << "Jogo " << i + 1 << ":" << endl;
        cout << "Nome: " << vetorJogos[i].nome << endl;
        cout << "Valor: " << vetorJogos[i].valor << endl;
        cout << "Data de lancamento: " << vetorJogos[i].data << endl;
        cout << "Desenvolvedora: " << vetorJogos[i].desenvolvedora << endl;
        cout << "Pico Maximo de jogadores: " << vetorJogos[i].pico_max << endl;
        cout << "Genero: " << vetorJogos[i].genero << endl;
        cout << endl;
    }
}

int jogosPico(jogo *vetorJogos, int tamanho) // retorna o jogo com o maior pico de jogadores
{
    int picoMaior = 0;
    int maior = vetorJogos[0].pico_max;

    for (int i = 1; i < tamanho; i++)
    {
        if (vetorJogos[i].pico_max > maior)
        {
            maior = vetorJogos[i].pico_max;
            picoMaior = i;
        }
    }
    return picoMaior;
}
int jogosPreco(jogo *vetorJogos, int tamanho) // retorna o jogo mais caro
{
    int precoMaior = 0;
    int maior = vetorJogos[0].valor;

    for (int i = 1; i < tamanho; i++)
    {
        if (vetorJogos[i].valor > maior)
        {
            maior = vetorJogos[i].valor;
            precoMaior = i;
        }
    }
    return precoMaior;
}

void shellSortPico(jogo *vetorJogos, int tamanho) // ordena o vetor pelo maior pico de jogadores
{
    int gap = tamanho / 2;
    while (gap > 0)
    {
        for (int i = gap; i < tamanho; i++)
        {
            jogo temp = vetorJogos[i];
            int j = i;
            while (j >= gap and vetorJogos[j - gap].pico_max < temp.pico_max)
            {
                vetorJogos[j] = vetorJogos[j - gap];
                j -= gap;
            }
            vetorJogos[j] = temp;
        }
        gap /= 2;
    }
}

void shellSortPreco(jogo *vetorJogos, int tamanho) // ordena o vetor pelo maior preco
{
    int gap = tamanho / 2;
    while (gap > 0)
    {
        for (int i = gap; i < tamanho; i++)
        {
            jogo temp = vetorJogos[i];
            int j = i;
            while (j >= gap and vetorJogos[j - gap].valor < temp.valor)
            {
                vetorJogos[j] = vetorJogos[j - gap];
                j -= gap;
            }
            vetorJogos[j] = temp;
        }
        gap /= 2;
    }
}

void imprimirTrecho(jogo *vetorJogos, int posicaoInicial, int posicaoFinal, int tamanho)
{
    if (posicaoInicial < 0 or posicaoInicial >= posicaoFinal or posicaoFinal >= tamanho)
    {
        cout << "Posições invalidas" << endl;
        return;
    }

    for (int i = posicaoInicial - 1; i <= posicaoFinal - 1; i++) //-1 para o usuario nao tenha que ser preocupar com a posicao 0
    {
        cout << "Jogo " << i + 1 << ":" << endl;
        cout << "Nome: " << vetorJogos[i].nome << endl;
        cout << "Valor: " << vetorJogos[i].valor << endl;
        cout << "Data de lancamento: " << vetorJogos[i].data << endl;
        cout << "Desenvolvedora: " << vetorJogos[i].desenvolvedora << endl;
        cout << "Pico Maximo de jogadores: " << vetorJogos[i].pico_max << endl;
        cout << "Genero: " << vetorJogos[i].genero << endl;
        cout << endl;
    }
}

void buscaNome(string nomeProcurado, jogo *vetorJogos, int tamanho) // busca por nome
{
    for (int i = 0; i < tamanho; i++)
    {
        if (vetorJogos[i].nome == nomeProcurado)
        {
            cout << "Jogo " << i + 1 << ":" << endl;
            cout << "Nome: " << vetorJogos[i].nome << endl;
            cout << "Valor: " << vetorJogos[i].valor << endl;
            cout << "Data de lancamento: " << vetorJogos[i].data << endl;
            cout << "Desenvolvedora: " << vetorJogos[i].desenvolvedora << endl;
            cout << "Pico Maximo de jogadores: " << vetorJogos[i].pico_max << endl;
            cout << "Genero: " << vetorJogos[i].genero << endl;
            cout << endl;
        }
    }
}

void buscaGenero(string generoProcurado, jogo *vetorJogos, int tamanho) // busca por genero
{
    for (int i = 0; i < tamanho; i++)
    {
        if (vetorJogos[i].genero == generoProcurado)
        {
            cout << "Jogo " << i + 1 << ":" << endl;
            cout << "Nome: " << vetorJogos[i].nome << endl;
            cout << "Valor: " << vetorJogos[i].valor << endl;
            cout << "Data de lancamento: " << vetorJogos[i].data << endl;
            cout << "Desenvolvedora: " << vetorJogos[i].desenvolvedora << endl;
            cout << "Pico Maximo de jogadores: " << vetorJogos[i].pico_max << endl;
            cout << "Genero: " << vetorJogos[i].genero << endl;
            cout << endl;
        }
    }
}

void buscaDesenvolvedora(string devProcurado, jogo *vetorJogos, int tamanho) // busca por desenvolvedora
{
    for (int i = 0; i < tamanho; i++)
    {
        if (vetorJogos[i].desenvolvedora == devProcurado)
        {
            cout << "Jogo " << i + 1 << ":" << endl;
            cout << "Nome: " << vetorJogos[i].nome << endl;
            cout << "Valor: " << vetorJogos[i].valor << endl;
            cout << "Data de lancamento: " << vetorJogos[i].data << endl;
            cout << "Desenvolvedora: " << vetorJogos[i].desenvolvedora << endl;
            cout << "Pico Maximo de jogadores: " << vetorJogos[i].pico_max << endl;
            cout << "Genero: " << vetorJogos[i].genero << endl;
            cout << endl;
        }
    }
}

int menu(int &escolha) // menu
{
    cout << "Escolha uma opcao:" << endl
         << "1 - Imprimir o arquivo" << endl
         << "2 - Buscar um jogo por nome" << endl
         << "3 - Buscar um jogo por genero" << endl
         << "4 - Buscar um jogo por desenvolvedora" << endl
         << "5 - Ver o jogo com o maior pico de jogadores" << endl
         << "6 - Ver o jogo mais caro" << endl
         << "7 - Organizar o arquivo pelo maior pico de jogadores" << endl
         << "8 - Organizar o arquivo pelo mais caro" << endl;

    cin >> escolha;
    return escolha;
}

void adicionarJogo(jogo *vetorJogos, int &tamanho, int &numRegistros, jogo novoJogo) // adiciona um novo jogo ao vetor
{
    if (tamanho >= numRegistros)
    {
        jogo *novoVetor = new jogo[numRegistros + 1]; // Cria um novo vetor com o tamanho atual + 1
        for (int i = 0; i < tamanho; i++)             // Copia os registros do vetor antigo para o novo vetor
        {
            novoVetor[i] = vetorJogos[i];
        }
        delete[] vetorJogos;    // Libera a memória ocupada pelo vetor antigo
        vetorJogos = novoVetor; // Atualiza o vetor de jogos com o novo vetor
        numRegistros++;
    }
    vetorJogos[tamanho] = novoJogo; // Adiciona o novo jogo ao vetor
    tamanho++;
}

void dadosDoNovoJogo(jogo &novoJogo) // adiciona os dados do novo jogo
{
    cout << "Digite o nome do jogo:" << endl;
    cin.ignore();
    getline(cin, novoJogo.nome);
    cout << "Digite o valor do jogo:" << endl;
    cin >> novoJogo.valor;
    cout << "Digite a data de lancamento do jogo:" << endl;
    cin.ignore();
    getline(cin, novoJogo.data);
    cout << "Digite a desenvolvedora do jogo:" << endl;
    getline(cin, novoJogo.desenvolvedora);
    cout << "Digite o pico maximo de jogadores do jogo:" << endl;
    cin >> novoJogo.pico_max;
    cout << "Digite o genero do jogo:" << endl;
    cin.ignore();
    getline(cin, novoJogo.genero);
    cout << endl;
}

int main()
{
    ifstream arqJogos("jogos.csv"); // abre o arquivo

    string cabecalho;
    int numRegistros = 100;
    jogo *vetorJogos = new jogo[numRegistros]; // cria um vetor de jogos dinamicamente
    int tamanho = 0;
    int escolha = 1;
    string nomeProcurado;
    string generoProcurado;
    string devProcurado;
    int qualTrecho;
    int trechoMaior;
    int trechoMenor;
    int addJogo;
    jogo novoJogo;

    cout << "Bem vindo ao nosso projeto!" << endl
         << "Para ir ao menu, digite 1!" << endl
         << "Para adicionar um novo jogo, digite 2!" << endl;
    cin >> addJogo;

    if (addJogo == 1)
    {
        menu(escolha);
    }
    else if (addJogo == 2)
    {
        dadosDoNovoJogo(novoJogo);
        adicionarJogo(vetorJogos, tamanho, numRegistros, novoJogo);
        menu(escolha);
    }
    else
    {
        cout << "Opção invalida" << endl;
    }

    if (arqJogos) // verifica se o arquivo foi aberto
    {
        getline(arqJogos, cabecalho);

        vetorJogos = lerDados(arqJogos, vetorJogos, numRegistros, tamanho); // ler os dados

        if (escolha == 1)
        {
            imprimirDados(vetorJogos, numRegistros); // imprimir os dados
        }
        else if (escolha == 2) // busca por nome
        {
            cout << "Digite o nome do jogo que deseja buscar:" << endl;
            cin.ignore();
            getline(cin, nomeProcurado);
            buscaNome(nomeProcurado, vetorJogos, tamanho);
        }

        else if (escolha == 3) // busca por genero
        {
            cout << "Digite o genero dos jogos que deseja buscar:" << endl;
            cin.ignore();
            getline(cin, generoProcurado);
            buscaGenero(generoProcurado, vetorJogos, tamanho);
        }
        else if (escolha == 4) // busca por desenvolvedora
        {
            cout << "Digite a desenvolvedora dos jogos que deseja buscar:" << endl;
            cin.ignore();
            getline(cin, devProcurado);
            buscaDesenvolvedora(devProcurado, vetorJogos, tamanho);
        }

        else if (escolha == 5) // jogo com o maior pico de jogadores
        {
            int picoMaior = jogosPico(vetorJogos, tamanho);
            cout << "O jogo com o maior pico de jogadores foi: " << vetorJogos[picoMaior].nome << endl; // imprime o jogo com o maior pico de jogadores
            cout << "Quantidade de jogadores: " << vetorJogos[picoMaior].pico_max << " jogadores." << endl;
        }

        else if (escolha == 6) // jogo mais caro
        {
            int precoMaior = jogosPreco(vetorJogos, tamanho);
            cout << "O jogo mais caro foi " << vetorJogos[precoMaior].nome << endl; // imprime o jogo mais caro
            cout << "Preco do jogo: " << vetorJogos[precoMaior].valor << " reais." << endl;
        }
        else if (escolha == 7) // ordena o vetor pelo maior pico de jogadores
        {
            shellSortPico(vetorJogos, tamanho);
            cout << "se voce gostaria de ver todos os jogos, digite 1, se quiser ver apenas um trecho, digite 2" << endl;
            cin >> qualTrecho;

            if (qualTrecho == 1) // imprime todos os jogos
            {
                imprimirDados(vetorJogos, tamanho);
            }
            else if (qualTrecho == 2) // imprime um trecho do vetor
            {
                cout << "coloque a posicao do primeiro jogo, e a posicao do ultimo jogo que gostaria de ver" << endl;
                cin >> trechoMaior >> trechoMenor;
                imprimirTrecho(vetorJogos, trechoMaior, trechoMenor, tamanho);
            }
        }
        else if (escolha == 8) // ordena o vetor pelo maior preco
        {
            shellSortPreco(vetorJogos, tamanho);
            cout << "se voce gostaria de ver todos os jogos, digite 1, se quiser ver apenas um trecho, digite 2" << endl;
            cin >> qualTrecho;

            if (qualTrecho == 1) // imprime todos os jogos
            {
                imprimirDados(vetorJogos, tamanho);
            }
            else if (qualTrecho == 2) // imprime um trecho do vetor
            {
                cout << "coloque a posicao do primeiro jogo, e a posicao do ultimo jogo que gostaria de ver" << endl;
                cin >> trechoMaior >> trechoMenor;
                imprimirTrecho(vetorJogos, trechoMaior, trechoMenor, tamanho);
            }
            else
            {
                cout << "Opçao invalida" << endl;
            }
        }
        else
        {
            cout << "Arquivo nao encontrado" << endl;
        }
    }
    delete[] vetorJogos; // deleta o vetor
    return 0;
};