//Reference by switch science's github
//https://github.com/SWITCHSCIENCE/samplecodes/blob/master/AQM1248A_breakout/Arduino/AQM1248A_sample/AQM1248A_sample.ino
#include "mbed.h"
#include "font_ascii.h"

SPI device(D11,D12,D13);//SPI_MOSI, SPI_MISO, SPI_SCK
DigitalOut RS(A0);

uint8_t pic[6][128] = {{0,0,0,0,128,192,192,224,224,224,224,224,224,224,224,224,224,96,0,0,0,0,0,0,0,0,0,0,0,0,128,224,224,224,224,224,224,224,224,192,192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,255,255,255,255,255,255,255,255,255,255,255,31,3,0,0,0,0,0,0,0,0,0,0,224,248,254,255,255,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,60,126,126,231,231,199,199,206,142,140,0,0,3,63,255,252,0,0,240,254,30,62,248,240,0,0,254,255,15,0,0,255,255,255,0,7,7,7,7,255,255,255,7,7,7,7,0,248,252,254,15,7,7,7,7,15,30,28,0,0,0,255,255,255,224,224,224,224,255,255,255,0,0,0,0,0,0,0},
    {0,0,0,0,255,255,255,255,255,255,255,255,191,135,128,128,128,128,128,128,128,128,0,0,0,0,7,7,7,7,7,135,199,231,247,251,255,255,255,255,255,255,0,0,0,0,0,0,0,0,12,28,60,56,48,48,49,57,63,31,15,0,0,0,7,63,62,62,63,7,0,0,7,63,62,62,63,7,0,0,0,63,63,63,0,0,0,0,0,63,63,63,0,0,0,0,0,3,15,31,28,56,56,56,56,28,30,14,0,0,0,63,63,63,0,0,0,0,63,63,63,0,0,0,0,0,0,0},
    {0,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,127,31,3,0,0,128,192,224,240,248,252,254,255,255,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,224,176,24,8,8,8,8,16,48,0,0,0,192,48,16,8,8,8,24,16,96,0,0,0,248,0,0,0,248,8,8,8,8,8,8,8,0,0,0,248,16,96,192,0,0,0,0,0,248,0,0,0,192,48,16,8,8,8,24,16,96,0,0,248,8,8,8,8,8,8,8,0,0,0,0,0,0,0},
    {0,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,239,227,240,248,252,254,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,96,193,129,3,2,2,6,132,204,120,0,15,112,192,128,0,0,0,0,192,96,0,0,0,255,0,0,0,255,2,2,2,2,2,2,2,0,0,0,255,0,0,0,3,12,24,96,192,255,0,0,15,112,192,128,0,0,0,0,192,96,0,0,255,2,2,2,2,2,2,2,0,0,0,0,0,0,0},
    {0,0,0,0,1,3,3,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,3,3,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
};

void lcdCmd(uint8_t cmd)
{
    RS = 0;
    device.write(cmd);
}

void lcdData(uint8_t data)
{
    RS = 1;
    device.write(data);
}

void normal_print(void)
{
    RS = 0;
    device.write(0xA6);
}

void reverse_print(void)
{
    RS = 0;
    device.write(0xA7);
}

void initLCD()
{
    lcdCmd(0xAE);           //Display = OFF
    lcdCmd(0xA0);           //ADC = normal
    lcdCmd(0xC8);           //Common output = revers
    lcdCmd(0xA3);           //LCD bias = 1/7

    //内部レギュレータON
    lcdCmd(0x2C);
    wait_ms(2);
    lcdCmd(0x2E);
    wait_ms(2);
    lcdCmd(0x2F);

    //コントラスト設定
    lcdCmd(0x22);           //Vo voltage regulator internal resistor ratio set
    lcdCmd(0x81);           //Electronic volume mode set
    lcdCmd(0x2F);           //Electronic volume register set

    //表示設定
    lcdCmd(0xA4);           //Display all point ON/OFF = normal
    lcdCmd(0x40);           //Display start line = 0
    lcdCmd(0xA6);           //Display normal/revers = normal
    lcdCmd(0xAF);           //Dsiplay = ON
}

void print_sample(void)
{
    for(int page=0; page<6; page++) {
        lcdCmd(0xb0+page);        //ページアドレス選択
        lcdCmd(0x10);             //カラムアドレス上位4bit = 0000
        lcdCmd(0x00);             //カラムアドレス下位4bit = 0000
        for(int col=0; col<128; col++) {
            lcdData(pic[page][col]);
        }
    }
}

void print_AQM1248A(char input[])
{
    int page = 0;
    int cursor_lcd = 0;

    lcdCmd(0xb0);       
    lcdCmd(0x10);          
    lcdCmd(0x00);
    
    for(int cursor=0; (cursor <= 255) && (input[cursor] != '\0'); cursor++)
    {
        //改行
        if(input[cursor] == '\n' && page < 7) {
            page++;
            lcdCmd(0xb0+page);
        }
        //行頭復帰
        else if(input[cursor] == '\r') {
            lcdCmd(0x10);
            lcdCmd(0x00);
            cursor_lcd = 0;
        }
        //文字表示
        else {
            //行頭復帰改行
            if(cursor_lcd >= 16) {
                page++;
                lcdCmd(0xb0+page);
                lcdCmd(0x10);
                lcdCmd(0x00);
                cursor_lcd = 0;
            }
            //文字表示
            for(int j=0; j<8; j++) {
                lcdData(font[input[cursor] - ' '][j]);
            }
            cursor_lcd++;
        }
    }
}



void print_clear(void)
{
    for(int page=0; page<8; page++) {
        lcdCmd(0xb0+page);        //ページアドレス選択
        lcdCmd(0x10);             //カラムアドレス上位4bit = 0000
        lcdCmd(0x00);             //カラムアドレス下位4bit = 0000
        for(int col=0; col<128; col++) {
            lcdData(0);
        }
    }
}


int main(void)
{
    //device.format(8,3);
    //device.frequency(100000);

    initLCD();              //LCD初期化
    
    //print_clear();
    
    while(1) {
        print_clear();
        print_AQM1248A("Hello World!");
        wait(3);
        print_clear();
        print_sample();
        wait(3);
    }
}
