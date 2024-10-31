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

// Função para desenhar o campo e jogadores.
void draw() {
    system("cls"); // Limpa a tela do terminal.

    // Desenhando elementos do jogo
    for (int i =0; i < alturadocampo; i++) { // Desenhando altura do campo
        for (int j = 0; j < larguradocampo; j++) { // Desenhando largura do campo
            if (j == 0) { // Verificando se o eixo X esta na posição 0 do campo para podermos desenhar o jogador1
                if (i == posicaojogador1y) std::cout << "|"; // Desenha o jogador1 quando chegar na metade do campo no eixo Y
                else std::cout << " "; // Desenha espaços vazios no eixo Y quando não estiver no meio do campo
            }
            else if (j == larguradocampo - 1) { // Verifica se a posição X do campo esta na ultima casa para desenharmos o jogador2
                if (i == posicaojogador2y) std::cout << "|"; // Desenha o jogador2 quando chegar na metade do campo no eixo Y
                else std::cout << "|"; // Desenha espaços vazios no eixo Y quando não estiver no meio do campo
            }
            else if (j == posicaobolax && i == posicaobolay) { // Verifica se o eixo X e Y estão no meio do campo para desenhar a bola
                std:cout << "O"; // Desenhar a bola
            }
            else {
                std::cout << " "; // Desenha espaço vazio quando não se encaixa em nenhum dos parâmetros acima
            }
        }
        std::cout << "\n"; // Ao desenhar uma linha do campo pula para a próxima linha (para continuar desenhando o campo)
    }
}

// Função com o jogo
int main() {
    setup(); // Chamando a posição inicial de todos os elementos do jogo
    while(gameloop) {
        input();
        simulate();
        render();
    }
}