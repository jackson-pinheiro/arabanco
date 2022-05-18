#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <locale.h>

using namespace std;

struct extrato_da_conta {
    int extrato_agencia;
    int extrato_conta;
    char extrato_tipo[50];
    int conta_origem;
    int conta_destino;
    float valor;
};

    ifstream fin;
  ofstream fout;

struct cadastrar_conta {
    int numero_conta;
    int numero_agencia;
    char nome_titular[50];
    int cpf;
    float saldo_inicial;
};

cadastrar_conta *P;
extrato_da_conta *V;
int     N;
int     S = 0;

void cadastro(); int menu (); void mostrar(); void alterar (int cont); void consultar(int cont);
void deposito(int cont); void saque(int cont); void transferir (int cont); void extrato_tela (); int escolher_extrato ();
void excluir(); void extrato_impresso (); void salvar_banco(); void carregar_banco();


int main()
{
    setlocale(LC_ALL, "Portuguese");
    int s;
    P = NULL;
    N = 0;

    int cont = 0;

    int op;
        REFAZ: do {
        system("cls");
        op = menu();
        switch (op){
            case 1:
                cadastro();
                break;
            case 2:
                alterar(cont);
                break;
            case 3:
                excluir();
                break;
            case 4:
                consultar(cont);
                break;
            case 5:
                deposito(cont);
                break;
            case 6:
                saque(cont);
                break;
            case 7:
                transferir(cont);
                break;
            case 8:
                mostrar();
                break;
            case 9:
                do {
                system ("cls");
                s = escolher_extrato();
                switch (s) {
                case 1:
                    system ("cls");
                    extrato_tela();
                    break;
                case 2:
                    system ("cls");
                    extrato_impresso();
                    break;
                case 3:
                    system ("cls");
                    goto REFAZ;
                    break;
                default: ;
                }
                system("pause");mostrar;
                } while (s != 3);
            case 10:
             system ("cls");
                fout.open("banco.dat", ios::binary);
                if (!fout){
                    cout << "Erro ao tentar abrir o arquivo!\n";                }
                else {
                    fout.write( (char *)&N, sizeof(N) );
                    fout.write( (char *)P, sizeof(cadastrar_conta) * N );

                    fout.write( (char *)&S, sizeof(S) );
                    fout.write( (char *)V, sizeof(extrato_da_conta) * S );

                    cout << "Dados salvos com sucesso.\n";
                    fout.close();
                }

                break;
            case 11:
                system ("cls");
                fin.open("banco.dat", ios::binary);
                if (!fout){
                    cout << "Erro ao tentar abrir o arquivo!\n";
                }
                else {
                    fin.read( (char *) &N, sizeof (N));

                    if (N > 0){

                        if (P != NULL){
                            delete P;
                        }

                        P = new cadastrar_conta[N];
                        fin.read( (char *)P, sizeof(cadastrar_conta) * N );
                    }

                     fin.read( (char *) &S, sizeof (S));


                    if (S > 0){

                        if (V != NULL){
                            delete V;
                        }

                        V = new extrato_da_conta[S];
                        fin.read( (char *)V, sizeof(extrato_da_conta) * S );
                    }

                    cout << "Dados carregados com sucesso.\n";
                    fin.close();
                }
                break;

            case 12:
                return 0;

                default: ;
        }
        system("pause");
    } while(op != 12);

        if (P != NULL)
            delete P;
    return 0;
}

int menu (){
    cout << "\t----------------------------------------------------\n";
    cout <<"\t|\t\tBanco | A R A B A N C O |\n";
    cout <<"\t|\n";
    cout <<"\t|\t1.  Cadastrar Conta Corrente\n";
    cout <<"\t|\t2.  Alterar Dados de uma Conta Corrente\n";
    cout <<"\t|\t3.  Excluir uma Conta Corrente\n";
    cout <<"\t|\t4.  Consultar Saldo\n";
    cout <<"\t|\t5.  Fazer Depósito\n";
    cout <<"\t|\t6.  Realizar Saque\n";
    cout <<"\t|\t7.  Transferir Valores\n";
    cout <<"\t|\t8.  Mostrar todas as Contas e Saldos\n";
    cout <<"\t|\t9.  Emitir Extrato da Conta\n";
    cout <<"\t|\t10. Salvar Dados do Banco\n";
    cout <<"\t|\t11. Carregar Dados do Banco\n";
    cout <<"\t|\t12. Sair\n";
    cout <<"\t|\n\n";
    cout <<"\tEscolha uma opcão: ";
    int op;
    cin >> op;
    return op;
}

void cadastro(){
cadastrar_conta p, *aux;
extrato_da_conta v, *aux2;
int cont = 0;
int conta;

                system ("cls");
                cout << "Cadastrar Conta Corrente\n\n";
                cout << "Número da Conta: ";
                cin >> p.numero_conta;
                for (int i = 0; i < N ; i++)
                    if (p.numero_conta == P[i].numero_conta){
                    cout << "\nConta Existente, Realize um Novo Cadastro!" << endl;
                    cont++;
                    }

            if (cont == 0){
                v.conta_origem = -1;
                v.conta_destino = -1;
                strcpy(v.extrato_tipo,"Saldo Inicial");
                v.extrato_conta = p.numero_conta;
                cout << "Número da Agencia: ";
                cin >> p.numero_agencia;
                v.extrato_agencia = p.numero_agencia;
                cout << "Nome do Titular: ";
                cin >> p.nome_titular;
                cout << "CPF do Titular: ";
                cin >> p.cpf;
                cout << "Saldo Inicial: ";
                cin >> p.saldo_inicial;
                v.valor = p.saldo_inicial;
                cout <<"Cadastro Criado Com Sucesso \n";

                aux = new cadastrar_conta[N+1];
                for (int i = 0; i < N; i++)
                    aux[i] = P[i];

                aux[N] = p;

                N++;

                delete P;

                P = aux;

                aux2 = new extrato_da_conta[S+1];
                for (int i = 0; i < S; i++)
                    aux2[i] = V[i];

                aux2[S] = v;

                S++;

                delete V;

                V = aux2;
            }
}

void mostrar (){
system("cls");
    cout << "INFORMAÇÕES SOBRE AS CONTAS CADASTRADAS\n\n";
    for (int i = 0; i < N; i++){
        cout << "Numero da Conta: " << P[i].numero_conta;
        cout << "\nNumero da Agencia: " << P[i].numero_agencia;
        cout << "\nNome do Titular: " << P[i].nome_titular;
        cout << "\nCPF do Titular: " << P[i].cpf;
        cout << "\nSaldo Atual: " << P[i].saldo_inicial;
        cout << "\n---------------------------\n\n";
    }
    if (N == 0)
        cout << "Não Possui Contas Cadastradas" << endl;
}

void alterar (int cont){
    int numero, agencia;
    system ("cls");
    if (N == 0)
        cout << "Não Existem Contas Cadastradas!" << endl;
    else {
        cout << "Digite o Número da Conta: ";
        cin >> numero;
        cout << "Digite o Número da Agência ";
        cin >> agencia;
        for (int j = 0; j < N; j++){
            if (numero == P[j].numero_conta && agencia == P[j].numero_agencia){
                cout << "Dados Encontrados, Digite os Novos Dados: " << endl;
                cout << "\nNome do Titular: ";
                cin >> P[j].nome_titular;
                cout << "\nCPF do Titular: ";
                cin >> P[j].cpf;
                cont++;
            }
        }
    }
            if (cont == 0 && N > 0)
            cout << "Registro não encontrado!" << endl;
}

void consultar(int cont){
int numero, agencia;
    system ("cls");
        if (N == 0)
            cout << "Não Possui Contas Cadastradas" << endl;
        else {
            cout << "Digite o Número da Conta: ";
            cin >> numero;
            cout << "Digite o Número da Agência ";
            cin >> agencia;
        for (int j = 0; j < N; j++){
            if (numero == P[j].numero_conta && agencia == P[j].numero_agencia){
                cout << "\n\nDados Encontrados: " << endl;
                cont ++;
                cout << "\nNúmero da Conta: " << P[j].numero_conta;
                cout << "\nNúmero da Agencia: " << P[j].numero_agencia;
                cout << "\nNome do Titular: " << P[j].nome_titular;
                cout << "\nCPF do Titular: " << P[j].cpf;
                cout << "\nSaldo Atual: " << P[j].saldo_inicial << endl;
            }
        }
            if (cont == 0)
            cout << "\nConta Inexistente!" << endl;
        }
}

void deposito (int cont){
    extrato_da_conta v, *aux2;
    int numero, agencia, dep;
    system ("cls");
        if (N == 0)
            cout << "Não Possui Contas Cadastradas" << endl;
        else {
            cout << "Digite o Número da Conta: ";
            cin >> numero;
            cout << "Digite o Número da Agência ";
            cin >> agencia;
        for (int j = 0; j < N; j++){
            if (numero == P[j].numero_conta && agencia == P[j].numero_agencia){
                cout << "\n\nDados Encontrados: " << endl;
                cont ++;
                cout << "\nNúmero da Conta: " << P[j].numero_conta;
                cout << "\nNúmero da Agência: " << P[j].numero_agencia;
                cout << "\nNome do Titular: " << P[j].nome_titular;
                cout << "\nCPF do Titular: " << P[j].cpf;
                cout << "\nSaldo Atual: " << P[j].saldo_inicial << endl;
                REFAZ: cout << "\n\nDigite o valor a ser Depositado: ";
                cin >> dep;
                if (dep > 0){
                    P[j].saldo_inicial += dep;
                    cout << "Depósito feito com Sucesso!" << endl;

                    v.conta_origem = -1;
                    v.conta_destino = -1;
                    v.extrato_agencia = P[j].numero_agencia;
                    v.extrato_conta = P[j].numero_conta;
                    strcpy(v.extrato_tipo, "Deposito");
                    v.valor = dep;

                aux2 = new extrato_da_conta[S+1];
                for (int i = 0; i < S; i++)
                    aux2[i] = V[i];
                aux2[S] = v;
                S++;
                delete V;
                V = aux2;

                }
                else {
                    cout << "Valor não pode ser negativo!" << endl;
                    goto REFAZ;
                }
            }
        }

            if (cont == 0)
            cout << "\nConta Inexistente!" << endl;
        }
}

void saque (int cont){
    int numero, agencia, saque;
    extrato_da_conta v;
    extrato_da_conta *aux2;
    system ("cls");
        if (N == 0)
            cout << "Não Possui Contas Cadastradas" << endl;
        else {
            cout << "Digite o Número da Conta: ";
            cin >> numero;
            cout << "Digite o Número da Agência ";
            cin >> agencia;
        for (int j = 0; j < N; j++){
            if (numero == P[j].numero_conta && agencia == P[j].numero_agencia){
                cout << "\n\nDados Encontrados: " << endl;
                cont ++;
                cout << "\nNúmero da Conta: " << P[j].numero_conta;
                cout << "\nNúmero da Agência: " << P[j].numero_agencia;
                cout << "\nNome do Titular: " << P[j].nome_titular;
                cout << "\nCPF do Titular: " << P[j].cpf;
                cout << "\nSaldo Atual: " << P[j].saldo_inicial << endl;
                REFAZ: cout << "\n\nDigite o Valor a ser Sacado: ";
                cin >> saque;
                if (P[j].saldo_inicial >= saque && saque > 0){
                        P[j].saldo_inicial -= saque;
                    cout << "Saque feito com Sucesso!" << endl;
                    v.conta_origem = -1;
                    v.conta_destino = -1;
                    v.extrato_agencia = P[j].numero_agencia;
                    v.extrato_conta = P[j].numero_conta;
                    strcpy(v.extrato_tipo, "Saque");
                    v.valor = saque;

                    aux2 = new extrato_da_conta[S+1];
                    for (int i = 0; i < S; i++)
                        aux2[i] = V[i];
                    aux2[S] = v;
                    S++;
                    delete V;
                    V = aux2;
                }
                else {
                    cout << "Valor do saque superior ao saldo existente ou valor do saque negativo!" << endl;
                    goto REFAZ;
                }
            }
        }

            if (cont == 0)
            cout << "\nConta Inexistente!" << endl;

        }
}

void transferir(int cont){
int numero1, agencia1, numero2, agencia2, valor;
extrato_da_conta *aux2;
extrato_da_conta x;
    system ("cls");
        if (N == 0 || N == 1)
            cout << "Não Possui Contas Cadastradas suficiente para Transferência" << endl;
        else {
            cout << "Digite o Número da Conta de Origem: ";
            cin >> numero1;
            cout << "Digite o Número da Agência de Origem: ";
            cin >> agencia1;
        for (int j = 0; j < N; j++){
            if (numero1 == P[j].numero_conta && agencia1 == P[j].numero_agencia){
                cont ++;
                cout << "\n\nDados Encontrados - Conta de Origem: " << endl;
                cout << "\nNúmero da Conta: " << P[j].numero_conta;
                cout << "\nNúmero da Agencia: " << P[j].numero_agencia;
                cout << "\nNome do Titular: " << P[j].nome_titular;
                cout << "\nCPF do Titular: " << P[j].cpf;
                cout << "\nSaldo Atual: " << P[j].saldo_inicial << endl;
            }

        }
            if (cont == 0){
            cout << "\nConta Inexistente!" << endl;
           }
           if (cont == 1){
            cout << "\nDigite o Número da Conta de Destino: ";
            cin >> numero2;
            cout << "Digite o Número da Agência Destino: ";
            cin >> agencia2;

        for (int i = 0; i < N; i++){
            if (numero2 == P[i].numero_conta && agencia2 == P[i].numero_agencia){
                cont ++;
                cout << "\n\nDados Encontrados - Conta de Destino: " << endl;
                cout << "\nNúmero da Conta: " << P[i].numero_conta;
                cout << "\nNúmero da Agência: " << P[i].numero_agencia;
                cout << "\nNome do Titular: " << P[i].nome_titular;
                cout << "\nCPF do Titular: " << P[i].cpf;
                cout << "\nSaldo Atual: " << P[i].saldo_inicial << endl;
            }
        }
           if (cont == 1){
            cout << "\nConta Inexistente!" << endl;
           }

           if (cont == 2){



            cout << "\nDigite o Valor a ser Transferido: ";
            cin >> valor;

        for (int k = 0; k < N; k++){
            if (numero1 == P[k].numero_conta && agencia1 == P[k].numero_agencia && valor <= P[k].saldo_inicial && valor > 0){
                P[k].saldo_inicial -= valor;
                cont++;
            }
        }
            if (cont != 3)
                cout << "Valor do saque maior do que o saldo atual ou negativo!\n";
            else {
                for (int v = 0; v < N; v++){
                    if (numero2 == P[v].numero_conta && agencia2 == P[v].numero_agencia)
                        P[v].saldo_inicial += valor;
                }
            cout << "Transferência feita com sucesso!" << endl;

            x.conta_origem = numero1;
            x.conta_destino = numero2;
            x.extrato_agencia = agencia1;
            x.extrato_conta = numero1;
            strcpy(x.extrato_tipo, "Transferência de Crédito para Terceiros");
            x.valor = valor;

            aux2 = new extrato_da_conta[S+1];
            for (int i = 0; i < S; i++)
                aux2[i] = V[i];
            aux2[S] = x;
            S++;
            delete V;
            V = aux2;

            x.conta_origem = numero1;
            x.conta_destino = numero2;
            x.extrato_agencia = agencia2;
            x.extrato_conta = numero2;
            strcpy(x.extrato_tipo, "DEPÓSITO RECEBIDO POR TRANSFERÊNCIA");
            x.valor = valor;

            aux2 = new extrato_da_conta[S+1];
            for (int i = 0; i < S; i++)
                aux2[i] = V[i];
            aux2[S] = x;
            S++;
            delete V;
            V = aux2;
        }
           }


        }
}
}

void extrato_tela(){
    int ac, ag, cont = 0;
    int s=0;
    cout << "Informe o número da conta: ";
    cin >> ac;
    cout << "Informe o número da agência: ";
    cin >> ag;

    for (int i = 0; i < S; i++){
        if (ac == V[i].extrato_conta && ag == V[i].extrato_agencia){
                s++;
            if (s==1){
                cont ++;
                cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
                cout <<"\t  EXTRATO DE MOVIMENTAÇAO \n";
                cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
                cout << "\t Nome do Titular: \t" << P[i].nome_titular<<endl;
                cout << "\t CPF do Titular: \t" << P[i].cpf<<endl;
                cout << "\t Numero da Conta: \t" << P[i].numero_conta<<endl;
                cout << "\t Numero da Agencia: \t" << P[i].numero_agencia<<endl;
                cout << "\t Saldo Inicial: \t" << V[i].valor<<endl;

                 cout << "\n-------------------------------------------------\n\n";


            }
            if (s!=1){
                cout << "Tipo de Operação: " << V[i].extrato_tipo << "\n\t";
        if (V[i].conta_origem !=-1){
            cout << "\n\tConta de Origem: " << V[i].conta_origem << "\n\t";
        }
        if (V[i].conta_destino !=-1){
            cout << "Conta de Destino: " << V[i].conta_destino << "\n\t";
        }


        cout << "Valor  : " << V[i].valor << endl << endl;
        cout << "\n-------------------------------------------------\n\n";

            }


        }


        }
         for (int i = 0; i < S; i++){
            if (ac == P[i].numero_conta && ag ==P[i].numero_agencia){
                cout <<"Saldo Final :" <<P[i].saldo_inicial<<endl;
            }

        if (cont == 0)
            cout << "Conta informada não cadastrada!" << endl;
        }
}

int escolher_extrato(){
    int x;
    cout << "Escolha o Tipo de Extrato" << endl;
    cout << "1. \tExtrato em Tela" << endl;
    cout << "2. \tExtrato em Arquivo" << endl;
    cout << "3. \tRetornar ao Menu" << endl;
    cin >> x;
    return x;
}

void excluir () {
    system ("cls");
    cadastrar_conta *aux;
    extrato_da_conta *aux2;
    int calc = 0;
    int cont = 0;
    if (N == 0)
        cout << "Não Possui Contas Cadastradas" << endl;
    else {

    aux = new cadastrar_conta[N-1];
    aux2 = new extrato_da_conta[S-1];
    int s[S];

    int cc, ag;
    cout << "Digite o Número da Conta Corrente: ";
    cin >> cc;
    cout << "Digite a Agência: ";
    cin >> ag;
    for (int i = 0; i < N; i++){
        if (P[i].numero_conta == cc && P[i].numero_agencia == ag){
            int p = -1;
    for (int i = 0; i < N; i++){
        if (P[i].numero_conta == cc && P[i].numero_agencia == ag){
            p = i;
        }
    }
        if (p != -1){
            int j = 0;
            for (int i = 0; i < N; i++)
                if(i != p)
                    aux[j++] = P[i];
                    cont ++;
            }

    delete P;
    P = aux;
    N--;


        cout << "Dados Excluidos com Sucesso!" << endl;

    }
    }

        for (int i = 0; i < S; i++){
            if (V[i].extrato_conta == cc && V[i].extrato_agencia == ag){
                bool var = false;
        for (int i = 0; i < S; i++){
            if (V[i].extrato_conta == cc && V[i].extrato_agencia == ag){
                s[i] = i;
                calc++;
    }
    }
        if (var != true){
            int j = 0;
            for (int i = 0; i < S; i++)
                if(i != s[i])
                    aux2[j++] = V[i];
            }

    delete V;
    V = aux2;
    S=S-calc;
    }
    }

    if (cont == 0){
        cout << "\nConta ou Agencia Inexistente!" << endl;
    }
    }

}

void extrato_impresso() {

    int ac, ag, cont = 0;
    int t=0;
    cout << "Informe o número da conta: ";
    cin >> ac;
    cout << "Informe o número da agência: ";
    cin >> ag;

    for (int i = 0; i < S; i++){
        if (ac == V[i].extrato_conta && ag == V[i].extrato_agencia) {
            ofstream fout;
            fout.open ("extrato.html");

        if (!fout){
            cout << "Erro ao criar arquivo";
        }


            for (int i = 0; i < S; i++){
                if (ac == V[i].extrato_conta && ag == V[i].extrato_agencia){

                        cont++;
                        fout <<"<table>";
                        fout <<"<table border=1>";
                        fout << "<body background=plano.jpg>";

                        if (ac == P[i].numero_conta && ag == P[i].numero_agencia){
                            fout << "<tr><td><h1><center>Extrato Conta</h1></center></code>";
                            fout << " <tr><td><h3> Nome Do Titular : </font></code></h3><font color=#006400>" << P[i].nome_titular << endl<<"</td></tr>";
                            fout << " <tr><td><h3> CPF Do Titular  </font></code></h3><font color=#006400>" << P[i].cpf << endl<<"</td></tr>";
                            fout << "<tr><td><h3> Conta Do Titular: </font></code></h3><font color=#006400>" << P[i].numero_conta << endl<<"</td></tr>";
                            fout << " <tr><td><h3> Agencia Do Titular: </font></code><font color=#006400>"<<P[i].numero_agencia << "\n"<<"</td></tr>";
                            fout << " <tr><td><h3> Saldo Inicial: </font></code></h3><font color=#006400>" << V[i].valor << endl<<"</td></tr>";
                            fout << "<tr><td><font color=#FF0000>***********************************************************************************</font> <p>" ;
                            fout << "<tr><td><font color=##0000FF>***********************************************************************************</font> \n" ;
                            fout << "<tr><td><h1><center>Movimentação da Conta</h1><center></code>";
                        }
                        else{

                            fout << "<tr><td><h3>Tipo de Operação: <font color=#088A08> <code><b>" << V[i].extrato_tipo << "</h3> </b> </font> \n</td></tr>";
                                if (V[i].conta_destino!=-1){
                                    fout << "<tr><td><h3>Conta de Destino:</h3> <font color=#088A08> <code>" << V[i].conta_destino<<"</td></tr>";
                                }
                                if (V[i].conta_origem!=-1){
                                    fout << "<tr><td><h3>Conta de Origem: </h3><font color=#088A08> <code>" << V[i].conta_origem << endl<<"</td></tr>";
                                }
                            fout << "<tr><td><h3> Valor Do  "<<V[i].extrato_tipo<<" <\h3><font color=#088A08> <code>"<< V[i].valor <<"</td></tr>";
                        }
                        fout <<"</pr>";
                        fout << "<tr><td><font color=#FF0000>***********************************************************************************</font> <p>" ;
                        fout << "<tr><td><font color=##0000FF>***********************************************************************************</font> \n" ;
                        fout <<"</pr> ";
                        fout <<"</table>";
                    }
        }




        for (int i = 0; i < S; i++){

          if (ac == P[i].numero_conta && ag == P[i].numero_agencia){
            fout <<"<table>";
            fout <<"<table border=1>";
            fout <<"</pr> ";
            fout << "<tr><td><h3>Saldo Total :</h3> <font color=#088A08> <code>" << P[i].saldo_inicial<<"</td></tr>";
            fout << "<tr><td><font color=#FF0000>***********************************************************************************</font> <p>" ;
            fout << "<tr><td><font color=##0000FF>***********************************************************************************</font> \n" ;

            fout <<"</table>";

          }
        }

     fout.close();

    }



}
    if (cont == 0){
        cout << "Conta informada não cadastrada!" << endl;
        }
    if (cont!=0){
        system ("extrato.html");
    }


}
