#include <stdio.h>
#include <stdlib.h> //stdlib.c que contém a implementação das funções, e como as queremos usar em nosso programa, importamos a declaração delas, que está todas no .h.
#include <string.h>
#include <time.h>
#include "forca.h" // lista de funções que aparecerão no arquivo

//Essas variáveis são chamadas de variáveis globais, pois elas ficam visíveis e passíveis de serem acessadas por qualquer função declarada em nosso programa. Elas são bastante úteis quando temos variáveis que são importantes, e por consequência, manipuladas por todas as nossas funções...//

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0; // Essa variavel servi quantos chutes e proxima tentativas no array


int letraexiste(char letra) {

	for(int j = 0; j < strlen(palavrasecreta); j++) {
		if(letra == palavrasecreta[j]) {
			return 1;
		}
	}

	return 0;
}

int chuteserrados() { ////erros, que contará o número de letras que o usuário chutou de maneira incorreta. Essa variável nos será útil ao final, pois, se ela for maior-ou-igual a 5, então o jogador deve ser enforcado
	int erros = 0;

	for(int i = 0; i < chutesdados; i++) { ////faremos um loop na lista de chutes e, para cada chute dado, verificaremos se a letra existe na palavra secreta
		
		if(!letraexiste(chutes[i])) { //se nao encontrou, soma um na quantidade de erros
			erros++;
		}
	}

	return erros;
}

int enforcou() {
	return chuteserrados() >= 5; //se tivermos mais do que 5 erros
}

int ganhou() {
	for(int i = 0; i < strlen(palavrasecreta); i++) {
		if(!jachutou(palavrasecreta[i])) { //Então, vamos apenas passear pela palavra secreta e ver se a letra já foi chutada. Se ela não foi chutada (então negaremos o if), já fazemos um return 0
			return 0;
		}
	}

	return 1;
}


void abertura() {
	printf("/****************/\n");
	printf("/ Jogo de Forca */\n");
	printf("/****************/\n\n");
}

void chuta() { //o parâmetro CHUTES E TENTATIVAS e diferente da variável CHUTE que está namain(); apenas os conteúdos é que são iguais
	char chute;
	printf("Qual letra? ");
	scanf(" %c", &chute);

	if(letraexiste(chute)) {
		printf("Você acertou: a palavra tem a letra %c\n\n", chute);
	} else {
		printf("\nVocê errou: a palavra NÃO tem a letra %c\n\n", chute);
	}

	chutes[chutesdados] = chute; // Array chutes recebe a variavel chutes../
	chutesdados++; // incrementos da tentativas...//
}

int jachutou(char letra) {
	int achou = 0; //// booleano false igual zero

	for(int j = 0; j < chutesdados; j++) { //Repare também que usamos a letra j para o loop de dentro, afinal a variável i já está sendo usada pelo loop de fora...//
		if(chutes[j] == letra) {
			achou = 1; //a variável achou, que valerá 1, se acharmos a letra no array de chutes. 
			break;
		}
	}

	return achou;
}

void desenhaforca() {

	int erros = chuteserrados();

	//Esse tipo de if, que tem uma condição, um valor de retorno no caso verdadeiro, e outro no caso de falso, é possível de ser feito em uma só linha. Chamamos isso de if ternário..../

	printf("  _______       \n");
	printf(" |/      |      \n");
	printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' ')); // Repare no ponto-de-interrogação separando a condição do valor verdadeiro, e o dois-pontos separando o valor usado no caso que a condição é falsa.
	printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
	printf(" |       %c     \n", (erros>=2?'|':' '));
	printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
	printf(" |              \n");
	printf("_|___           \n");
	printf("\n\n");

	for(int i = 0; i < strlen(palavrasecreta); i++) { //Para capturar o tamanho da palavra dentro de um array de chars, usamos a 
	//função strlen() resumido imprime a palavra secreta.....

		if(jachutou(palavrasecreta[i])) {
			printf("%c ", palavrasecreta[i]);
		} else {
			printf("_ ");
		}

	}
	printf("\n");

}

void escolhepalavra() {

	FILE* f; //Agora vamos começar a ler esse arquivo. A primeira coisa que precisamos fazer é abrí-lo. Para isso, precisamos declarar 
	//um ponteiro do tipo FILE*../


	f = fopen("palavras.txt", "r"); //fopen() que abre um arquivo do disco. Essa função nos devolve então um ponteiro (que 
	//guardaremos /na variável já declarada), e a partir daí, passamos esses ponteiros para as funções que lerão os caracteres desse arquivo. 
	//Repare no "r". Isso indica que estamos abrindo o arquivo somente para leitura (poderíamos tê-lo aberto para escrita). 
 
	if(f == 0) {
		printf("Banco de dados de palavras não disponível\n\n");
		exit(1); ///Repare que o parâmetro 1, passado ao exit indica ao sistema operacional que o programa terminou de maneira que ele não gostaria; ou seja, um erro ocorreu
	}

	int qtddepalavras;

	//Toda vez que lemos de um arquivo, a leitura é sequencial. Ou seja, se já capturamos o primeiro número, a próxima vez que 
	//chamarmos a função fscanf(), ela continuará a leitura do ponto que parou. É como se ela tivesse uma pequena seta, que aponta 
	//para a posição que está lendo no arquivo no momento.

	fscanf(f, "%d", &qtddepalavras); // A funcao fscanf() A diferença dela é que o primeiro parâmetro é o ponteiro para um arquivo. 

	srand(time(0)); // gera numero aleatorio
	int randomico = rand() % qtddepalavras; // Calcula o numero randomico

	for(int i = 0; i <= randomico; i++) { //lê do arquivo até chegar na linha desejada//
		fscanf(f, "%s", palavrasecreta); //Vamos declarar um array e ler, usando a máscara "%s"//
	}

	fclose(f); // Afuncao fclose Fechar o arquivo txt
}


void adicionapalavra() {
	char quer;

	printf("Você deseja adicionar uma nova palavra no jogo (S/N)?");
	scanf(" %c", &quer);

	if(quer == 'S') { //Se ele responder "S", então perguntaremos a ele a palavra
		char novapalavra[TAMANHO_PALAVRA];

		printf("Digite a nova palavra, em letras maiúsculas: ");
		scanf("%s", novapalavra);

		FILE* f; //ponteiro FILE* aponta para um arquivo, e passamos esse ponteiro para todas as outras funções que o manipulam.../

		 // abre arquivo
		f = fopen("palavras.txt", "r+"); //r+. Ele nos permite ler e alterar um arquivo//

		if(f == 0) {
			printf("Banco de dados de palavras não disponível\n\n");
			exit(1);
		}

		int qtd;
		fscanf(f, "%d", &qtd); //O fscanf() consegue ler dados de um arquivo//// 
		qtd++;

		//Vamos posicioná-la então "0 bytes" a partir do começo do arquivo://///
		fseek(f, 0, SEEK_SET); //função fseek(). Ela recebe três parâmetros: o arquivo, quantos bytes ela deve andar (para a esquerda 
		// ou para a direita) e da onde ela deve começar a andar (do começo do arquivo, da posição corrente, ou do final)...

		fprintf(f, "%d", qtd);//Com o ponteiro posicionado na posição que queremos, basta agora escrevermos a variável qtd, 
		//usando o fprintf(). A máquina não pensará duas vezes e escreverá por cima do que está naquela posição:../ 

		//Agora, por fim, precisamos escrever a palavra no final do arquivo. Vamos novamente usar fseek() para ir ao fim do arquivo, e fprintf() para escrever a palavra.../
		fseek(f, 0, SEEK_END);//Poderíamos usar também as SEEK_CUR para andar a partir do ponto atual, ou mesmo SEEK_END, para andar a partir do fim do arquivo. 

		// escreve a palavra nele
		fprintf(f, "\n%s", novapalavra); //A diferença é que o primeiro parâmetro que ela recebe é justamente o arquivo em que ela escreverá 

		fclose(f); // fecha arquivo

	}

}

int main() { //Quando um programa comeca é executado primeiro a funcao main()...//

	abertura(); //A funcao abertur Invoca a funcao void abertura com printf/// 

	escolhepalavra();

	do {

		desenhaforca();
		chuta();

	} while (!ganhou() && !enforcou());

	if(ganhou()) {
		printf("\nParabéns, você ganhou!\n\n");

		printf("       ___________      \n");
		printf("      '._==_==_=_.'     \n");
		printf("      .-\\:      /-.    \n");
		printf("     | (|:.     |) |    \n");
		printf("      '-|:.     |-'     \n");
		printf("        \\::.    /      \n");
		printf("         '::. .'        \n");
		printf("           ) (          \n");
		printf("         _.' '._        \n");
		printf("        '-------'       \n\n");

	} else {
		printf("\nPuxa, você foi enforcado!\n");
		printf("A palavra era **%s**\n\n", palavrasecreta);

		printf("    _______________         \n");
		printf("   /               \\       \n"); 
		printf("  /                 \\      \n");
		printf("//                   \\/\\  \n");
		printf("\\|   XXXX     XXXX   | /   \n");
		printf(" |   XXXX     XXXX   |/     \n");
		printf(" |   XXX       XXX   |      \n");
		printf(" |                   |      \n");
		printf(" \\__      XXX      __/     \n");
		printf("   |\\     XXX     /|       \n");
		printf("   | |           | |        \n");
		printf("   | I I I I I I I |        \n");
		printf("   |  I I I I I I  |        \n");
		printf("   \\_             _/       \n");
		printf("     \\_         _/         \n");
		printf("       \\_______/           \n");
	}

	adicionapalavra();
}