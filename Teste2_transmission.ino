//código do transmissor. o "/0" é necessário para a minha tela LCD, não sei se é necessário em geral
#include <VirtualWire.h>

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(A3)); //geração de números aleatórios
  vw_set_tx_pin(14); //pino do transmissor
  vw_setup(2000);
  pinMode(19, INPUT_PULLUP); //botão
}

bool button;
char data[7];   // vetor de caracteres a enviar.  'X' + 5 dígitos + '\0'

void loop()
{
  data[0] = 'E'; //primeiro caracter do vetor é minha letra de identificação. sou o quinto na lista de alunos.
  data[6] = '\0';  // garante terminação da string

  button = digitalRead(19);
  if (!button) { //se botão apertado
    delay(100);
    char numero;

    for (char i = 1; i < 6; i++) { //loop de geração dos 5 comandos a enviar, 1 caractere ASCII de cada vez. garante que são gerados 5 dígitos aleatórios e sem repetição
      bool repetido;
      do {
        repetido = false;
        numero = random('0', '9' + 1);
        for (char j = 1; j < i; j++) { //lê e compara caracter gerado com cada um dos caracteres já incluídos no vetor anteriormente
          if (numero == data[j]) {
            repetido = true;
            break;
          }
        }
      } while (repetido); //se número gerado já foi inserido no vetor anteriormente, gera outro número
      data[i] = numero; //vetor a ser enviado. Caracter só é adicionado se passar no teste (numero != data[j])
    }

    Serial.print("Enviando: ");
    Serial.println(data);   // deve imprimir ex: "E47302"
    send(data);
  }
}

void send(char *message)
{
  vw_send((uint8_t *)message, strlen(message) +1 ); // +1 inclui o '\0'. necessário pro painel LCD
  vw_wait_tx();
}
