#include <asm/io.h>
#include <micro-os/module.h>
#include <micro-os/pic32-serial.h>
#include <micro-os/uart.h>

#define MODE_REGISTER 0x0
#define STA_REGISTER  0x10
#define TX_REGISTER   0x20
#define RX_REGISTER   0x30
#define BRG_REGISTER  0x40

/* Mode register bit definitions */
#define MODE_ON (0x01 << 15)
#define MODE_UARTEN_TXRXBCLK (0x03 << 9) /* TX,RX,BLCK pins are enabled and used, CTS PORT register*/
#define MODE_UARTEN_TXRXCTSRTS (0x01 << 9) /* TX,RX,CTS,RTS pins enabled and used */
#define MODE_UARTEN_TXRXRTS (0x01 << 8) /* TX,RX,RTS pins are enabled and used */
#define MODE_UARTEN_TXRX (0x00) /* TX,RX pins are enabled and used, everything else by PORT register */

/* Status/Control register definitions */
#define STAT_RXEN (0x01 << 12)
#define STAT_TXEN (0x01 << 10)
#define STAT_TXBF (0x01 << 9) /* 1 if transmit buffer full */
#define STAT_TRMT (0x01 << 8) /* 1 if shift register is empty */

#define PCLK (80000000ul/2)

#define read_reg(data,reg) readl(data->base_address + reg)
#define write_reg(data,reg,value) writel(value, data->base_address + reg)

void main(void);

static void pic32_serial_write(struct pic32_uart_data* device, const void* data, uint32_t len){
    //TODO DMA this stuff, yo
    //For now, blocking I/O
    int pos = 0;
    const uint8_t* byte_data = data;

    while( pos < len ){
        while( (read_reg(device, STA_REGISTER) & STAT_TXBF) > 0 ){ /* spinlock while transmit */ }
        write_reg(device, TX_REGISTER, byte_data[ pos++ ]);
    }

    /* wait for buffer to clear */
    while( (read_reg(device, STA_REGISTER) & STAT_TRMT) == 0 ){}
}

static void pic32_serial_set_baud(struct pic32_uart_data* data, int baud){
    int brg = ((PCLK / baud)/16) - 1;
    write_reg(data, BRG_REGISTER, brg);
}

void pic32_console_write(struct console * console, const char * text, unsigned len){
    struct pic32_uart_data* data = console->data;
    pic32_serial_write(data, text, len);
}

void pic32_init_serial(struct pic32_uart_data* data){
    int32_t mode, stat;

    stat = read_reg(data, STA_REGISTER);
    stat |= STAT_RXEN | STAT_TXEN;
    write_reg(data, STA_REGISTER, stat);
 
    pic32_serial_set_baud(data, 115200);

    //mode = read_reg(data, MODE_REGISTER);
    mode = MODE_ON;
    write_reg(data, MODE_REGISTER, mode );
}
