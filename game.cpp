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
int velocidadeBolax = 1;
int velocidadeBolay = 1;

void setup() { //Função para deifinir as posições padrões dos jogadores e bola
    posicaoBolax = larguraCampo / 2; // bola irá iniciar no meio do campo
    posicaoBolay = alturaCampo / 2;
    posicaoJogador1y = alturaCampo / 2;
    posicaojogador2y = alturaCampo / 2;
}

// Função para desenhar o campo e jogadores.
void desenharJogo() {
    system("cls"); // Limpa a tela do terminal.

    // Desenhando elementos do jogo
    for (int i =0; i < alturaCampo; i++) { // Desenhando altura do campo
        for (int j = 0; j < larguraCampo; j++) { // Desenhando largura do campo
            if (j == 0) { // Verificando se o eixo X esta na posição 0 do campo para podermos desenhar o jogador1
                if (i == posicaoJogador1y) std::cout << "|"; // Desenha o jogador1 quando chegar na metade do campo no eixo Y
                else std::cout << " "; // Desenha espaços vazios no eixo Y quando não estiver no meio do campo
            }
            else if (j == larguraCampo - 1) { // Verifica se a posição X do campo esta na ultima casa para desenharmos o jogador2
                if (i == posicaojogador2y) std::cout << "|"; // Desenha o jogador2 quando chegar na metade do campo no eixo Y
                else std::cout << " "; // Desenha espaços vazios no eixo Y quando não estiver no meio do campo
            }
            else if (j == posicaoBolax && i == posicaoBolay) { // Verifica se o eixo X e Y estão no meio do campo para desenhar a bola
                std::cout << "O"; // Desenhar a bola
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
        desenharJogo();
    }
}