# FIFO Ring Buffer

~~~ c
#define BUFFER_SIZE 200

buffer_t buffer;

// init buffer
char buf[BUFFER_SIZE] = {0};
BufferInit(&buffer, buf, BUFFER_SIZE);

// put
BufferPut(char symbol, buffer_t *buf);

// pop
BufferPop(buffer_t *buf);
~~~

#### Example IRQ:
~~~ c
void USART2_IRQHandler(void)
{
    USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    BufferPut(USART_ReceiveData(USART2), &buffer);
    data.flag_off = false;
}
~~~