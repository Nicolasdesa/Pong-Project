#include <iostream> // Biblioteca padrão de entrada e saída.
#include <conio.h> // Biblioteca para captura de entrada de teclado (_kbhit e _getch).
#include <windows.h> // Biblioteca para manipulação de cursor e controle de console no Windows.

using namespace std; // Evita o uso de 'std::' antes de cada função da biblioteca padrão.

// Declaração da função definirPosicao para que o compilador a reconheça
void definirPosicao(int x, int y);

class Ponto {
public:
    int x, y; // Coordenadas x e y.

    // Construtor que inicializa as coordenadas (padrão 0, 0 se não especificado).
    Ponto(int x = 0, int y = 0) : x(x), y(y) {}

    // Sobrecarga do operador '+' para somar dois pontos.
    Ponto operator+(const Ponto& outro) const {
        return Ponto(x + outro.x, y + outro.y);
    }

    // Sobrecarga do operador '+=' para adicionar um ponto diretamente.
    Ponto& operator+=(const Ponto& outro) {
        x += outro.x;
        y += outro.y;
        return *this;
    }
};

// Classe base para objetos do jogo (Bola e Jogador herdarão dela).
class ObjetoJogo {
public:
    Ponto posicao; // Posição do objeto no campo.

    // Construtor que inicializa a posição do objeto.
    ObjetoJogo(int x = 0, int y = 0) : posicao(x, y) {}

    // Método virtual puro para desenhar o objeto (definido nas classes derivadas).
    virtual void desenhar() = 0;
};

// Classe Bola, que representa a bola do jogo e herda de ObjetoJogo.
class Bola : public ObjetoJogo {
public:
    Ponto direcao; // Direção da bola.

    // Construtor que inicializa a posição e a direção da bola.
    Bola(int x, int y, int dx, int dy) : ObjetoJogo(x, y), direcao(dx, dy) {}

    // Método para mover a bola de acordo com sua direção.
    void mover() {
        posicao += direcao;
    }

    // Inverte a direção horizontal da bola.
    void inverterDirecaoX() {
        direcao.x = -direcao.x;
    }

    // Inverte a direção vertical da bola.
    void inverterDirecaoY() {
        direcao.y = -direcao.y;
    }

    // Implementação do método virtual para desenhar a bola na posição atual.
    void desenhar() override {
        definirPosicao(posicao.x, posicao.y);
        cout << "O"; // Representação da bola.
    }
};

// Classe Jogador, representando cada jogador e herdando de ObjetoJogo.
class Jogador : public ObjetoJogo {
public:
    // Construtor que inicializa a posição do jogador.
    Jogador(int x, int y) : ObjetoJogo(x, y) {}

    // Move o jogador para cima se ele não estiver na borda superior.
    void moverCima() {
        if (posicao.y > 0) posicao.y--;
    }

    // Move o jogador para baixo se ele não estiver na borda inferior.
    void moverBaixo(int alturaCampo) {
        if (posicao.y < alturaCampo - 4) posicao.y++;
    }

    // Implementação do método virtual para desenhar o jogador na posição atual.
    void desenhar() override {
        for (int i = 0; i < 4; i++) {
            definirPosicao(posicao.x, posicao.y + i);
            cout << "|"; // Representação do jogador (raquete).
        }
    }
};

// Variáveis constantes e globais para o campo de jogo e pontuação.
const int larguraCampo = 60;
const int alturaCampo = 15;
int pontosJogador1 = 0, pontosJogador2 = 0;
bool gameLoop = true; // Controla o loop principal do jogo.

// Cria uma bola no centro do campo com direção inicial.
Bola bola(larguraCampo / 2, alturaCampo / 2, 1, 1);

// Cria dois jogadores em posições iniciais opostas.
Jogador jogador1(1, alturaCampo / 2 - 2);
Jogador jogador2(larguraCampo - 2, alturaCampo / 2 - 2);

// Função para posicionar o cursor do terminal em (x, y).
void definirPosicao(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Função para esconder o cursor no terminal, melhorando a estética do jogo.
void esconderCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Função para reiniciar as posições dos objetos e esconde o cursor.
void inicializar() {
    bola = Bola(larguraCampo / 2, alturaCampo / 2, 1, 1);
    jogador1 = Jogador(1, alturaCampo / 2 - 2);
    jogador2 = Jogador(larguraCampo - 2, alturaCampo / 2 - 2);
    gameLoop = true;
    esconderCursor();
}

// Função para desenhar o campo de jogo, jogadores e bola.
void desenhar() {
    definirPosicao(0, 0); // Reseta o cursor para a posição inicial.

    // Desenha a borda superior do campo.
    for (int i = 0; i < larguraCampo + 2; i++) cout << "#";
    cout << endl;

    // Desenha as linhas do campo.
    for (int i = 0; i < alturaCampo; i++) {
        for (int j = 0; j < larguraCampo; j++) {
            if (j == 0 || j == larguraCampo - 1) cout << "#"; // Borda lateral.
            else cout << " ";
        }
        cout << endl;
    }

    // Desenha a borda inferior do campo.
    for (int i = 0; i < larguraCampo + 2; i++) cout << "#";

    // Desenha a bola e os jogadores.
    bola.desenhar();
    jogador1.desenhar();
    jogador2.desenhar();

    // Exibe o placar no final do campo.
    cout << "\nPontos: Jogador1: " << pontosJogador1 << " | Jogador2: " << pontosJogador2 << endl;
}

// Função para capturar a entrada do usuário e mover o jogador1.
void entrada() {
    if (_kbhit()) { // Verifica se uma tecla foi pressionada.
        switch (_getch()) {
            case 'w': jogador1.moverCima(); break; // W: move para cima.
            case 's': jogador1.moverBaixo(alturaCampo); break; // S: move para baixo.
            case 'q': gameLoop = false; break; // Q: sai do jogo.
        }
    }
}

// Função para movimentar o jogador2 (IA) acompanhando a posição da bola.
void logicaIA() {
    if (bola.posicao.y > jogador2.posicao.y + 1 && jogador2.posicao.y < alturaCampo - 4) {
        jogador2.moverBaixo(alturaCampo);
    } else if (bola.posicao.y < jogador2.posicao.y && jogador2.posicao.y > 0) {
        jogador2.posicao.y--;
    }
}

// Função principal de lógica para movimentação da bola e colisões.
void logica() {
    bola.mover(); // Move a bola de acordo com sua direção.

    // Verifica colisões da bola com as bordas superior/inferior.
    if (bola.posicao.y == 0 || bola.posicao.y == alturaCampo - 1) bola.inverterDirecaoY();

    // Colisão com o jogador1 (muda a direção da bola).
    if (bola.posicao.x == jogador1.posicao.x + 1 &&
        bola.posicao.y >= jogador1.posicao.y && bola.posicao.y <= jogador1.posicao.y + 3) {
        bola.inverterDirecaoX();
    }

    // Colisão com o jogador2 (muda a direção da bola).
    if (bola.posicao.x == jogador2.posicao.x - 1 &&
        bola.posicao.y >= jogador2.posicao.y && bola.posicao.y <= jogador2.posicao.y + 3) {
        bola.inverterDirecaoX();
    }

    // Se a bola sai pela esquerda, jogador2 pontua e bola é reiniciada.
    if (bola.posicao.x == 0) {
        pontosJogador2++;
        bola.posicao = Ponto(larguraCampo / 2, alturaCampo / 2);
        bola.inverterDirecaoX();
    }

    // Se a bola sai pela direita, jogador1 pontua e bola é reiniciada.
    if (bola.posicao.x == larguraCampo - 1) {
        pontosJogador1++;
        bola.posicao = Ponto(larguraCampo / 2, alturaCampo / 2);
        bola.inverterDirecaoX();
    }
}

// Função principal do programa (inicializa, desenha e executa o jogo).
int main() {
    inicializar();

    // Loop principal do jogo.
    while (gameLoop) {
        desenhar();
        entrada();
        logicaIA();
        logica();
        Sleep(50); // Pausa breve para controle de velocidade.
    }

    return 0;
}