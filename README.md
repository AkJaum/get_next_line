# get_next_line

Implementacao do projeto `get_next_line`.

A funcao `get_next_line(int fd)` retorna uma linha por chamada a partir de um file descriptor, mantendo estado entre chamadas com buffer estatico.

## Objetivo

Ler de um file descriptor e retornar:

- A proxima linha (incluindo `\n`, quando existir).
- `NULL` quando chegar ao fim do arquivo (EOF) ou em caso de erro.

## Estrutura do projeto

- `get_next_line.c`: logica principal (versao obrigatoria).
- `get_next_line_utils.c`: funcoes auxiliares de string.
- `get_next_line.h`: header da versao obrigatoria.
- `get_next_line_bonus.c`: versao bonus (multiplos FDs).
- `get_next_line_utils_bonus.c`: utils da versao bonus.
- `get_next_line_bonus.h`: header da versao bonus.

## Como funciona

1. Um buffer estatico guarda dados lidos que ainda nao foram retornados.
2. A funcao faz `read` em blocos de `BUFFER_SIZE` ate encontrar `\n` ou EOF.
3. Quando encontra `\n`, retorna a linha e guarda o restante para a proxima chamada.
4. Se nao houver mais dados, retorna o restante final (sem `\n`) e depois `NULL`.

### Mandatory

- Usa `static char *lastbuffer;` para manter estado de um unico FD por vez.

### Bonus

- Usa `static char *lastbuffer[4096];` para manter estado independente por FD.

## Compilacao

### Mandatory

```bash
cc -Wall -Wextra -Werror -c get_next_line.c get_next_line_utils.c
```

### Bonus

```bash
cc -Wall -Wextra -Werror -c get_next_line_bonus.c get_next_line_utils_bonus.c
```

### Definindo `BUFFER_SIZE`

Por padrao no projeto:

- `BUFFER_SIZE` = `1024`

Para testar com outro valor:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c get_next_line.c get_next_line_utils.c
```

### Compilando com um teste (`main.c`)

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl_test
```

## Exemplo de uso

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    fd = open("arquivo.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Regras importantes de uso

- Sempre liberar (`free`) a linha retornada por `get_next_line`.
- Nao chamar com `fd` invalido.
- Se `BUFFER_SIZE <= 0`, a funcao retorna `NULL`.

## Observacoes

- A linha retornada inclui `\n` quando ele existe no input.
- Em EOF, a ultima linha pode vir sem `\n`.
- Em erro de leitura/alocacao, a funcao retorna `NULL`.

## Autor

- `jneris-d`
