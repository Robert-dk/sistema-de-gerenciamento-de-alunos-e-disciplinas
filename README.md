# Sistema de Gerenciamento de Alunos e Disciplinas em C

Este projeto implementa um sistema de gerenciamento de alunos e disciplinas em C, utilizando alocação dinâmica de memória e listas encadeadas.

## Descrição

Este sistema permite gerenciar informações de alunos, como nome e RGM (Registro Geral Matricula), e as disciplinas que cada aluno cursa, incluindo o nome da disciplina e a nota. As principais funcionalidades incluem:

*   Adicionar alunos com nome e RGM.
*   Remover alunos.
*   Listar todos os alunos cadastrados.
*   Adicionar disciplinas a um aluno específico, com nome e nota.
*   Remover disciplinas de um aluno.
*   Listar as disciplinas de um aluno.
*   Ordenar alunos por RGM.

O projeto foi desenvolvido com foco em boas práticas de programação em C, incluindo tratamento de erros, prevenção de vazamentos de memória e uso eficiente de recursos.

## Funcionalidades

*   **Alocação Dinâmica de Memória:** O sistema utiliza `malloc` e `realloc` para alocar memória dinamicamente para os alunos, permitindo o gerenciamento de uma quantidade variável de registros sem a necessidade de definir um tamanho fixo.
*   **Listas Encadeadas:** As disciplinas de cada aluno são armazenadas em uma lista encadeada, o que facilita a adição e remoção de disciplinas sem a necessidade de realocar grandes blocos de memória.
*   **Tratamento de Erros:** O código inclui verificações de erros em alocações de memória e entradas inválidas do usuário, tornando o sistema mais robusto.
*   **Ordenação por RGM:** A função `bubblesort` implementa o algoritmo de ordenação Bubble Sort para organizar os alunos em ordem alfabética de RGM.
* **Limpeza de Buffer:** O sistema usa uma função `limparBuffer` para garantir que entradas inválidas não causem comportamento inesperado.

## Estrutura do Código

*   `main.c`: Contém a função `main` (principal) e a lógica do menu.
*   `// outros arquivos .c se você modularizar o código`: Poderia conter as implementações das funções de alunos e disciplinas separadamente.
* `//arquivos .h se você modularizar o código`: Poderia conter as declarações das funções.

## Dependências

*   Compilador C (GCC ou similar)

## Autor

*   Robert Emanuel

## Versão

2.0

## Data de Criação

12/06/2024

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir *issues* e *pull requests*.

## Melhorias Futuras

*   Implementar outros algoritmos de ordenação mais eficientes (Quick Sort, Merge Sort).
*   Adicionar funcionalidades de busca por nome ou RGM.
*   Persistência de dados em arquivo para que as informações não sejam perdidas ao fechar o programa.
*   Melhorar a interface do usuário.
*   Adicionar tratamento de erros mais abrangente.
