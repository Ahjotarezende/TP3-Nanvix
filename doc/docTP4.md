## Estudantes

- Alexandre Magno
- Arthur Oliveira
- João Augusto

Neste último trabalho, foi realizado a implementação de dois algoritmos:
NRU(Not Recently Used) que, na necessidade de retirar uma página de disco da memória, dá prioridade àquelas que não foram acessadas ou modificadas durante um certo período de tempo.

Aging: Modificação do NFU, com adição de contadores que são sempre deslocados um bit para direita antes de serem somados com o bit R, que sempre é adicionado ao bit mais à esquerda do contador, ao invés de ser somado ao mais à direita (No nosso algoritmo foi utilizado um contador comum, onde era incrementado em 1 a cada acesso, e não há a necessidade de soma ao Bit R). A página escolhida para ser removida é a de menor contador.

Há uma necessidade de limpeza do Bit R, nosso grupo escolheu 20 acessos como limite para realizar a limpeza, o algoritmo passa por cada processo e pega sua devida página, em seguida a variavel de acesso é setada para 0.

Para remoção de uma devida página, seguimos uma política de prioridade onde a página vazia é a menos prioritária e a página acessada e modificada é a mais prioritária. A página menos prioritária será removida.

As alterações feitas no código resultam em um custo muito baixo (no nanvix), logo, em relação ao tempo de execução é pouco percepitível uma diferença. Claro que em problemas de larga escala e SO’s maiores e mais completos existem outras opções que mostram melhores resultados, para nosso caso, LRU e Aging são ótimas escolhas.
