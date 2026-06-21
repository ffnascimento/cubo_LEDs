//código do receptor. comentei o que é código da minha telinha LCD e podem ser apagados

#include <Arduino.h>
#include <U8x8lib.h> //painel LCD
#include <VirtualWire.h>

#ifdef U8X8_HAVE_HW_SPI//painel LCD
#include <SPI.h>//painel LCD
#endif//painel LCD

// Please UNCOMMENT one of the contructor lines below
// U8x8 Contructor List 
// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8x8setupcpp
// Please update the pin numbers according to your setup. Use U8X8_PIN_NONE if the reset pin is not connected
//U8X8_NULL u8x8;	// null device, a 8x8 pixel display which does nothing
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 	//painel LCD      
//U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 2, /* data=*/ 0, /* reset=*/ U8X8_PIN_NONE); 	      // Digispark ATTiny85
//U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display

// End of constructor list


void setup(void)
{
  u8x8.begin();//painel LCD
  u8x8.setPowerSave(0);//painel LCD
  u8x8.setFont(u8x8_font_chroma48medium8_r);//painel LCD

  vw_set_rx_pin(5); // Define o pino 5 do Arduino como entrada de dados do receptor
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);             // Bits por segundo
  vw_rx_start();              // Inicializa o receptor

  u8x8.drawString(0,0,"Aguardando...");//painel LCD
  u8x8.setInverseFont(0);//painel LCD

  delay(2000);
  
  
}

void loop(void)
{
  uint8_t message[VW_MAX_MESSAGE_LEN]; //vetor de variáveis que armazena a mensagem, um caracter ASCII por posição
  uint8_t msgLength = VW_MAX_MESSAGE_LEN; //variável que armazena o número de caracteres da mensagem
  
  memset(message, 0, VW_MAX_MESSAGE_LEN);  // ← limpa o buffer antes de receber

  if (vw_get_message(message, &msgLength)) //se mensagem recebida, entra no loop. vetor message terá os caracteres, um por posição do vetor
  {
    u8x8.clearDisplay();//painel LCD
    u8x8.drawString(0,0,"Recebido:");//painel LCD
    u8x8.setInverseFont(0);//painel LCD
    u8x8.draw2x2String(2,4,(char*)message); //painel LCD
    u8x8.setInverseFont(0);//painel LCD
  }
}