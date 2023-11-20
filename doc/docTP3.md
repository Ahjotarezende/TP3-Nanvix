# TP3 Task

## Estudantes
- Alexandre Magno
- Arthur Oliveira
- João Augusto

## Introdução

Esse documento tem como objetivo reportar a implementação dos semafóros, que é uma primitiva de sincronização inter-processos, no sistema operacional Nanvix. Esta implementação faz parte do Trabalho Prático 3 - Sistemas Operacionais, proposto pelo professor Pedro Henrique Penna. 

## Desenvolvimento

A atividade foi baseada em criar as chamadas de sistemas no Kernel:

- semget: Associa um processo a um semáforo ou cria um novo
- semctl: Operações associadas aos semáforos (valor do semáforo, define valor do semáforo diminui ou destroi o semáforo)
- semop: Operações atômicas de down e up

Assim como fazer a inclusão da estrutura semáforo no sistema (include > sys > sem.h). A estrutura possui id, valor, estado, prioridade, posição e utilização do semáforo.

## Conclusão

Podemos observar que, os semáforos são importantes para evitar que processos acessem simultaneamente um mesmo recurso. Portanto, são necessários em sistemas que se comprometem em manter uma segurança e coerência em seus dados.
