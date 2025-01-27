#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <cstdlib> // Para a função system("clear")
using namespace std;

// Função para configurar o terminal em modo "não canônico"
void configurarModoNaoCanonico() {
    termios t;
    tcgetattr(STDIN_FILENO, &t); // Obtém as configurações atuais do terminal
    t.c_lflag &= ~ICANON;        // Desativa o modo canônico
    t.c_lflag &= ~ECHO;          // Desativa o eco
    tcsetattr(STDIN_FILENO, TCSANOW, &t); // Aplica as alterações
}

// Função para restaurar o terminal para o modo original
void restaurarModoCanonico(termios& tOriginal) {
    tcsetattr(STDIN_FILENO, TCSANOW, &tOriginal);
}

// Função para verificar se o comando passado é PS1=
string chargeName(const string& comando){
    const string prefixo = "PS1=";

    if (comando.substr(0, prefixo.length()) == prefixo) {
        return comando.substr(prefixo.length());
    }

    return "";
}

void capturarComando(string& comando, const string& promptName) {
    comando.clear();
    while (true) {
        char ch = getchar(); // Captura o caractere pressionado
        if (ch == '\n') {
            cout << endl;
            break;
        } else if (ch == 127) { // Backspace
            if (!comando.empty()) {
                comando.pop_back();
                cout << "\b \b";
            }
        } else if (ch == 12) { // Ctrl + L
            system("clear");
            cout << promptName << " > " << comando;
        } else if (isprint(ch)) { // Qualquer tecla imprimível
            comando += ch;
            cout << ch;
        }
    }
}

int main() {
    string promptName = "msh";
    string comando;
    string novoNome;
    termios tOriginal;

    tcgetattr(STDIN_FILENO, &tOriginal); // Salva as configurações originais do terminal
    configurarModoNaoCanonico();

    do {
        cout << promptName << " >";
        capturarComando(comando, promptName);

        // Verifica se o comando é "exit" antes de alterar o prompt
        if (comando == "exit") {
            break;
        }

        // Atualiza o prompt caso a instrução PS1= tenha sido detectada
        if (auto novoNome = chargeName(comando); !novoNome.empty()) {
            promptName = novoNome;
        }

    } while (true);

    restaurarModoCanonico(tOriginal); // Restaura o terminal ao estado original

    return 0;
}
