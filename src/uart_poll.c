#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/uart.h>

#define UART5_DEVICE_NODE DT_NODELABEL(uart5)

static const struct device *uart_device = DEVICE_DT_GET(UART5_DEVICE_NODE);

char buf[128];

void uart_tx_msg(char *msg) {
    for (int i = 0; i < strlen(msg); ++i)
        uart_poll_out(uart_device, msg[i]);
}

char uart_rx_next_char() {
    char c;
    while (true) { 
        int ret = uart_poll_in(uart_device, &c);
        if (ret == 0) {
            printf("received: %c == 'r': %d\n", c, (c == 'r'));
            break;
        } else if (ret == -1) {
            // Poling
        } else {
            printf("ERR Polling\n");
        }
    }
    // printf("c again: %c", c);
    // if (c == 'r') printf("c is equal to r\n");
    // printk("received: %c\n", c);
    return c;
}

void uart_rx_read(char *buf, char stop) {
    char data;
    while (1) {
        data = uart_rx_next_char();
        if (data == stop) {
            break;
        }
        *(buf++) = data;
    }
    *buf = '\0';
}

void process_response() {
    printk("processing\n");
    uart_rx_next_char(); // ','

    uart_rx_read(buf, ','); // velocity x
    float vx = atof(buf);

    uart_rx_read(buf, ','); // velocity y
    float vy = atof(buf);

    uart_rx_read(buf, ','); // valid
    float vz = buf[0];

    uart_rx_read(buf, ','); // altitude
    float altitude = atof(buf);

    uart_rx_read(buf, ','); // fom
    float fom = atof(buf);

    // covariance matrix
    for (int i = 0; i < 8; ++i) {
        uart_rx_read(buf, ';');
    }
    
    uart_rx_read(buf, ','); // timestamp
    int timestamp = atoi(buf);

    uart_rx_read(buf, ','); // transmission
    int transmission = atoi(buf);

    uart_rx_read(buf, ','); // time since last read
    float time = atof(buf);

    char status = uart_rx_next_char(); // status

    // checksum
    uart_rx_next_char(); // *
    uart_rx_next_char(); // x
    uart_rx_next_char(); // x

    printf("vx: {%f}, vy: {%f}, vz: {%f}, alt: {%f}, time: {%f}",
            vx, 
            vy, 
            vz, 
            altitude,
            time);

}


void main(void){
    printk("DEVICE %s READY!", CONFIG_BOARD);

    printk("testing\n");
    k_msleep(1000);

    if (!device_is_ready(uart_device)) {
        printk("UART model not found\n");
    } else  {
        printk("found UART device\n");
    }

    k_msleep(1000);

    printk("got here?\n");
    while (1) {
        if (uart_rx_next_char() == 'r' && uart_rx_next_char() == 'w' && uart_rx_next_char() == 'z') {
            printf("cool, proccessing\n");
        }
        /*
        char byte;
        if (uart_poll_in(uart_device, &byte) == 0) {
            printk("rec: %c\n", byte);
            if (byte == 'w') {
                // process_response();
            }
        }
        */
    }
}
