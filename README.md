# minitalk

Projeto `minitalk` da 42 com:
- mandatory em `src/`
- bonus em `bonus/`
- dependencia `ft_printf/`

## Documentacao

- Avaliacao: [README_EVALUATION.md](/c:/Users/Jo%C3%A3o%20Ramalhosa/Desktop/42-Commoncore/minitalk/README_EVALUATION.md)

## Estado atual

- `norminette src bonus`: OK
- Mandatory stress: 8/8 PASS
- Bonus stress: 7/7 PASS
- Makefile com targets de stress:
  - `make stress_mandatory`
  - `make stress_bonus`
  - `make stress`

## Comandos

Mandatory:
```bash
make
./server
./client <PID> "<MESSAGE>"
```

Bonus:
```bash
make bonus
./server
./client <PID> "<MESSAGE>"
```

## Protocolo

- Sinais usados: `SIGUSR1` (bit 1), `SIGUSR2` (bit 0)
- Terminador de mensagem: `'\0'`
- Mandatory e bonus usam ACK/BUSY por bit para robustez em concorrencia.

## Limite importante (subject + OS)

`client` recebe a mensagem por argumento (`argv[2]`), como pedido no subject.

Por isso existe limite do sistema operativo (`ARG_MAX`):
- se o texto for demasiado grande, o processo nem arranca (`Argument list too long`)
- isto acontece antes do teu codigo executar

Teste real neste ambiente WSL:
- 130000 chars: OK (integridade total)
- >= 140000 chars: bloqueado pelo OS

## Ficheiros principais

- [Makefile](/c:/Users/Jo%C3%A3o%20Ramalhosa/Desktop/42-Commoncore/minitalk/Makefile)
- [src/server.c](/c:/Users/Jo%C3%A3o%20Ramalhosa/Desktop/42-Commoncore/minitalk/src/server.c)
- [src/client.c](/c:/Users/Jo%C3%A3o%20Ramalhosa/Desktop/42-Commoncore/minitalk/src/client.c)
- [bonus/server_bonus.c](/c:/Users/Jo%C3%A3o%20Ramalhosa/Desktop/42-Commoncore/minitalk/bonus/server_bonus.c)
- [bonus/client_bonus.c](/c:/Users/Jo%C3%A3o%20Ramalhosa/Desktop/42-Commoncore/minitalk/bonus/client_bonus.c)
