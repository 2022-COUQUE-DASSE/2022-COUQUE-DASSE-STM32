# Yuuri-iot

made by Yuuri-team

---

## 보드

---

<b>Nucleo-F103RB</b>

- 클럭: 64MHz
- 사용 핀
  - PB10: UART3 / TX
  - PB11: UART3 / RX

---

## 코드

---

main() -> while 전 USER CODE

```c
MX_USART3_UART_Init();
```

while문

```c
HAL_UART_Receive(&huart3, &data_sign, sizeof(data_sign), 1000);
HAL_UART_Transmit(&huart2, "hello", sizeof("hello"), 1000);
HAL_UART_Transmit(&huart2, data_sign, sizeof(data_sign), 1000);
```
