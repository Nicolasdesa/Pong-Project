#include <iostream> // Biblioteca padrão de entrada e saída.
#include <conio.h> // Utilizada para verificar se o usuário está interagindo com o programa sem aguardar uma entrada padrão (_kbhit) e ler uma tecla pressionada sem a necessidade de apertar enter (_getch).
#include <windows.h> // Usada para que a tela possa não piscar, escondendo o cursor do cmd

using namespace std; // Usado para evitar colocar o std:: a cada função ou objeto da biblioteca padrão (cout por exemplo)

// Variáveis padrão do jogo
const int larguraCampo = 60; // Largura do campo
const int alturaCampo = 15;  // Altura do campo
int xBola, yBola, xJogador1, xJogador2, yJogador1, yJogador2; // Posição inicial da bola e dos jogadores
int direçãoxBola = 1, direçãoyBola = 1; // Direção inicial que a bola irá
int pontosJogador1 = 0, pontosJogador2 = 0; // Pontuação dos jogadores
bool gameLoop = true; // Mantém o jogo rodando

// Função para esconder o cursor do terminal, evitando que o cursor fique navegando durante a partida, podendo atrapalhar os jogadores
void esconderCursor() {
    CONSOLE_CURSOR_INFO cursorInfo; // Variável para armazenar as informações do cursor
    cursorInfo.dwSize = 1; // Colocando o cursos com tamanho 1 (sem essa linha os flickes voltam a ocorrer)
    cursorInfo.bVisible = FALSE; // Deixando o cursor invisível
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // Aplicando as novas configurações no cursor do terminal
}

// Função para mover o cursor do terminal para a posição inicial
void definirPosicao(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Função para definir a posição inicial de cada elemento do jogo
void inicializar() {
    xBola = larguraCampo / 2; // Inicia a bola no meio do campo
    yBola = alturaCampo / 2;
    xJogador1 = 1; // Posição da raquete do jogador 1
    yJogador1 = alturaCampo / 2 - 2;
    xJogador2 = larguraCampo - 2; // Posição da raquete do jogador 2
    yJogador2 = alturaCampo / 2 - 2;
    gameLoop = true; // Inicia o loop do jogo
    esconderCursor(); // Esconde o cursor
}

// Função para desenhar os elementos do jogo: Campo, jogadores e bola
void desenhar() {
    definirPosicao(0, 0); // Reseta a posição do cursor para 0, 0
    
    for (int i = 0; i < larguraCampo + 2; i++) { // Desenha o teto do campo
        cout << "#"; // Desenhando a área do campo
    }
    cout << endl; // Indo para a linha de baixo após desenhar todo o teto do campo

    for (int i = 0; i < alturaCampo; i++) { // Loop para selecionar cada linha do campo
        for (int j = 0; j < larguraCampo; j++) { // Loop para desenhar na primeira e última coluna do campo
            if (j == 0) cout << "#"; // Desenha a primeira coluna do campo
            if (j == xBola && i == yBola) cout << "O"; // Desenha a bola na sua posição atual
            // Desenha os jogadores na posição inicial com três caracteres cada
            else if (j == xJogador1 && (i >= yJogador1 && i <= yJogador1 + 3)) cout << "|"; 
            else if (j == xJogador2 && (i >= yJogador2 && i <= yJogador2 + 3)) cout << "|";
            else cout << " "; // Desenha um espaço vazio caso não estejamos desenhando nenhum elemento do jogo
            if (j == larguraCampo - 1) cout << "#"; // Desenha a última coluna do campo
        }
        cout << endl; 
    }

    for (int i = 0; i < larguraCampo + 2; i++) cout << "#"; // Desenha o chão do campo
    // Exibe o placar
    cout << "\nPontos: Jogador1: " << pontosJogador1 << " | Jogador2: " << pontosJogador2 << endl;
}

// Função para capturar a entrada do usuário e movimentar o jogador1
void entrada() {
    if (_kbhit()) { // Verifica se alguma tecla foi pressionada
        switch (_getch()) { // Captura a tecla pressionada
            case 'w': if (yJogador1 > 0) yJogador1--; break; // Apertando W move o jogador1 para cima
            case 's': if (yJogador1 < alturaCampo - 4) yJogador1++; break; // Apertando S move jogador 1 para baixo
            case 'q': gameLoop = false; break; // Encerra o jogo
        }
    }
}

// Função para o jogador2 seguir a bola no eixo Y
void logicaIA() {
    if (yBola > yJogador2 + 1 && yJogador2 < alturaCampo - 4) {
        yJogador2++;
    } else if (yBola < yJogador2 && yJogador2 > 0) {
        yJogador2--;
    }
}

// Função de colisões e movimentação da bola
void logica() {
    xBola += direçãoxBola; // Atualiza a posição da bola no eixo X
    yBola += direçãoyBola; // Atualiza a posição da bola no eixo Y

    // Verifica colisão da bola com as bordas superior/inferior e muda sua direção
    if (yBola == 0 || yBola == alturaCampo - 1) direçãoyBola = -direçãoyBola; 
    // Altera direção quando colidir com o jogador1
    if (xBola == xJogador1 + 1 && (yBola >= yJogador1 && yBola <= yJogador1 + 3)) direçãoxBola = -direçãoxBola; 
    // Altera direção quando colidir com o jogador2
    if (xBola == xJogador2 - 1 && (yBola >= yJogador2 && yBola <= yJogador2 + 3)) direçãoxBola = -direçãoxBola;

    // Verifica se a bola passou pela coluna esquerda campo (fez gol)
    if (xBola == 0) { 
        pontosJogador2++; // Jogador2 pontua
        // Leva a bola para o centro
        xBola = larguraCampo / 2;
        yBola = alturaCampo / 2;
        direçãoxBola = -direçãoxBola; // Inverte a direção da bola
    }

    // Verifica se a bola passou pela coluna direita do campo (fez gol)
    if (xBola == larguraCampo - 1) { 
        pontosJogador1++; // Jogador1 pontua
        // Leva a bola para o centro
        xBola = larguraCampo / 2;
        yBola = alturaCampo / 2;
        direçãoxBola = -direçãoxBola; // Inverte a direção da bola
    }
}

// Função principal do jogo
int main() {
    inicializar(); // Inicializa as variáveis e a posição da bola e dos jogadores
    while (gameLoop) { // Loop do jogo
        desenhar(); // Desenha o campo
        entrada(); // Movimento do jogador
        logicaIA(); // Lógica de IA do jogador 2
        logica(); // Lógica do movimento da bola
        Sleep(40); // Controle de velocidade do jogo
    }
    return 0; // Finaliza o programa
}