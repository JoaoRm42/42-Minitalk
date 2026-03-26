# bonus - Bonus

Este diretorio contem a implementacao bonus do `minitalk`.

## Objetivo do bonus

Adicionar confirmacao de entrega robusta mantendo comunicacao por sinais:
- `SIGUSR1` = ACK (bit aceite)
- `SIGUSR2` = BUSY (server ocupado com outro cliente)

Mensagem continua terminada por `'\0'`.

## Ficheiros

- `client_bonus.c`: envio fiavel com retries por bit.
- `server_bonus.c`: rececao com controlo por `active_pid`.
- `utils_bonus.c`: `ft_atoi` e `ft_putnbr_fd`.
- `minitalk_bonus.h`: includes e prototipos.

## Protocolo bonus

1. `server` aceita um cliente ativo (`active_pid`).
2. Cada bit recebido desse cliente gera `SIGUSR1` de ACK.
3. Se outro cliente enviar durante a sessao ativa, recebe `SIGUSR2` (BUSY).
4. `client_bonus` interpreta BUSY e reenvia o bit.
5. Ao receber `'\0'`, o server imprime `\n` e liberta `active_pid`.
6. O client imprime confirmacao: `Message received by server.`

## Funcoes principais

### `client_bonus.c`

- `ft_state(void)`
  - Guarda flags locais (`ACK`, `BUSY`) sem globals de ficheiro.
- `ft_confirm(int sig)`
  - Handler das respostas do server.
- `ft_try_bit(int pid, unsigned char c, int bit)`
  - Envia 1 bit e espera ACK; em BUSY tenta novamente.
- `ft_send_char(int pid, unsigned char c)`
  - Envia byte completo (8 bits).
- `main(int argc, char **argv)`
  - Valida entrada, configura handlers e envia string + `'\0'`.

### `server_bonus.c`

- `ft_is_busy(pid_t client_pid, pid_t *active_pid)`
  - Define/valida cliente ativo.
- `ft_flush_byte(unsigned char *c, int *bit, pid_t *active_pid)`
  - Escreve byte e fecha sessao no `'\0'`.
- `ft_handler(int signal, siginfo_t *info, void *context)`
  - Reconstrucao de bits com `SA_SIGINFO`.
- `main(void)`
  - Setup de sinais e loop infinito com `pause()`.

## Comportamento sob carga

- Este bonus foi ajustado para modo anti-tank:
  - retries controlados no client
  - serializacao por `active_pid` no server
  - evita corrupcao quando varios clients tentam enviar em simultaneo

## Limite conhecido

Tal como no mandatory, o texto vem por `argv[2]`.
Logo, existe limite do sistema para tamanho de argumentos (`ARG_MAX`).
Se for excedido, o processo nao arranca e o programa nao chega a executar.
