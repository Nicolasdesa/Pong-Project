#include <iostream> // Biblioteca padrão de entrada e saída.
#include <conio.h> // Utilizada para verificar se o usuário esta interagindo com o programa sem aguardar uma entrada padrão (_kbhit) e ler uma tecla precionada sem a necessidade de apertar enter (_getch).
#include <thread> // Usada para executar tarefas simultaneamente no jogo.
#include <chrono> // Usada junto com thread, verificar se precisaremos utilizar depois

//Variáveis padrões do jogo
bool gameloop = true; // Controle de loop do jogo
const int larguradocampo = 80;
const int alturadocampo = 20;
int posicaojogador1y = 4;
int posicaojogador2y = 4;
int posicaobolax = 10;
int posicaobolay = 5;

void setup() { //Função para deifinir as posições padrões dos jogadores e bola
    posicaobolax = larguradocampo / 2; // bola irá iniciar no meio do campo
    posicaobolay = alturadocampo / 2;
    posicaojogador1y = alturadocampo / 2;
    posicaojogador2y = alturadocampo / 2;
}

// Função para desenhar o campo.
void draw() {
    system("cls"); // Limpa a tela do terminal.
}

int main() {
    while(gameloop) {
        input();
        simulate();
        render();
    }
}