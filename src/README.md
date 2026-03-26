# src - Mandatory

Este diretorio contem a implementacao mandatory do `minitalk`.

## Objetivo

Enviar uma mensagem de `client` para `server` usando apenas:
- `SIGUSR1` para bit `1`
- `SIGUSR2` para bit `0`

A mensagem termina com o byte `'\0'`.

## Ficheiros

- `client.c`: envia a mensagem bit a bit.
- `server.c`: recebe sinais e reconstrui bytes.
- `utils.c`: `ft_atoi` e `ft_putnbr_fd`.
- `minitalk.h`: includes e prototipos.

## Fluxo de envio/rececao

1. `server` arranca e imprime `PID`.
2. `client` recebe `<PID> <MESSAGE>`.
3. Para cada caractere:
- envia 8 bits (LSB -> MSB).
4. `server` acumula 8 sinais e reconstrui 1 byte.
5. Ao receber `'\0'`, o `server` imprime `\n` e fecha a sessao ativa.

## Modo anti-tank (mandatory)

Mesmo no mandatory, o protocolo foi reforcado para aguentar concorrencia:

- `server` aceita apenas um `active_pid` por mensagem.
- Se outro cliente tentar enviar durante uma sessao ativa, recebe `SIGUSR2` (BUSY).
- Para cada bit aceite, o server responde `SIGUSR1` (ACK).
- `client` espera ACK e faz retry quando recebe BUSY.

Resultado: evita mistura de mensagens quando varios clientes enviam ao mesmo tempo.

## Funcoes principais

### `client.c`

- `ft_state(void)`
  - Guarda flags locais de estado (`ACK`, `BUSY`).
- `ft_confirm(int sig)`
  - Handler de sinais de resposta do server.
- `ft_try_bit(int pid, unsigned char c, int bit)`
  - Envia 1 bit e espera ACK; em BUSY faz retry.
- `ft_send_char(int pid, unsigned char c)`
  - Envia um byte completo (8 bits).
- `main(int argc, char **argv)`
  - Valida argumentos/PID, configura handlers e envia mensagem + `'\0'`.

### `server.c`

- `ft_is_busy(pid_t client_pid, pid_t *active_pid)`
  - Controla exclusao de cliente ativo.
- `ft_flush_byte(unsigned char *c, int *curr_bit, pid_t *active_pid)`
  - Escreve byte completo e reseta estado quando recebe `'\0'`.
- `ft_handler(int signal, siginfo_t *info, void *context)`
  - Handler principal de rececao de bits.
- `main(void)`
  - Configura `sigaction` e entra em loop com `pause()`.

## Notas importantes

- O `client` usa `argv[2]` (como pede o subject).
- Mensagens gigantes podem falhar com `Argument list too long` por limite do OS (`ARG_MAX`), antes de entrar no programa.
- Isso nao e erro do `minitalk`, e limite da chamada `execve`.
