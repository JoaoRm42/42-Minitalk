# minitalk - Evaluation Notes

## Compliance

- Interface mantida: `./client <PID> <MESSAGE>`
- Comunicacao so com `SIGUSR1` e `SIGUSR2`
- Terminacao da mensagem com `'\0'`
- Mandatory e bonus compilam com `-Wall -Wextra -Werror`
- `norminette src bonus`: OK

## Build

```bash
make
make bonus
make clean
make fclean
make re
```

## Checklist Mandatory

- `server` imprime PID
- `client` envia bits corretamente
- `server` reconstrui e imprime mensagem
- Tratamento de erro para argumentos/PID
- Robustez concorrente com ACK/BUSY por bit

## Checklist Bonus

- `sigaction` + `SA_SIGINFO` no server bonus
- identificacao de `si_pid`
- ACK/BUSY por bit
- confirmacao de entrega no client bonus

## Stress Results

- `make stress_mandatory` -> PASS (8/8)
- `make stress_bonus` -> PASS (7/7)

## Known OS Limit (not project bug)

Mensagens muito grandes em `argv[2]` dependem de `ARG_MAX`.
Se ultrapassar, o `client` nem arranca (`Argument list too long`).
