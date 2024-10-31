#include <iostream> // Biblioteca padrão de entrada e saída.
#include <conio.h> // Utilizada para verificar se o usuário esta interagindo com o programa sem aguardar uma entrada padrão (_kbhit) e ler uma tecla precionada sem a necessidade de apertar enter (_getch).
#include <thread> // Usada para executar tarefas simultaneamente no jogo.
#include <chrono> // Usada junto com thread, verificar se precisaremos utilizar depois

//Variáveis padrões do jogo
bool gameloop = true; // Controle de loop do jogo
const int larguraCampo = 80;
const int alturaCampo = 20;
int posicaoJogador1y = 4;
int posicaojogador2y = 4;
int posicaoBolax = 10;
int posicaoBolay = 5;

void posiçõesIniciais() { //Função para deifinir as posições padrões dos jogadores e bola
    posicaoBolax = larguraCampo / 2; // bola irá iniciar no meio do campo
    posicaoBolay = alturaCampo / 2;
    posicaoJogador1y = alturaCampo / 2;
    posicaojogador2y = alturaCampo / 2;
}

// Função para desenhar o campo e jogadores.
void desenharJogo() {
    // Desenha o campo e jogadores
    for (int i = 0; i < alturaCampo; i++) {
        for (int j = 0; j < larguraCampo; j++) {
            if (j == 0) {
                std::cout << (i == posicaoJogador1y ? "|" : " "); // Desenha o jogador 1
            } else if (j == larguraCampo - 1) {
                std::cout << "|"; // Borda do jogador 2
            } else {
                std::cout << " "; // Espaço vazio
            }
        }
        std::cout << "\n"; // Nova linha
    }
    std::cout.flush(); // Garante que tudo seja exibido de uma vez
}

// Função com o jogo
int main() {

    while(gameloop) {
        desenharJogo();
    }
}