# Trabalho 2 - Gerenciamento de memória

&nbsp; &nbsp; &nbsp;

```
Disciplina de Sistemas Operacionais - INE5611

Turma 04238A/B 

20 de Junho de 2023
```

&nbsp; &nbsp; &nbsp;

**ALUNOS:**

> `[20200634]` Pedro Santi Binotto
>
> `[20105097]` Petterson Pereira da Rosa
>
> `[20102277]` Bruno Vazquez Lafaiete

\pagebreak

### Estrutura do projeto:

```
. ------------------------------------------ RAIZ DO PROJETO
├── README.md
├── resources
│   └── data ------------------------------- DADOS DE TESTE DO SIMULADOR
└── src
    ├── impl ------------------------------- ARQUIVOS DE IMPLEMENTAÇÃO
    │   ├── FIFO.py                          DOS ALGORITMOS DE PAGINAÇÃO
    │   ├── __init__.py
    │   ├── LRU.py
    │   ├── NRU.py
    │   └── SECONDCHANCE.py
    ├── __init__.py
    ├── lib -------------------------------- ARQUIVOS AUXILIARES 
    │   ├── constants.py                     (IMPLEMENTAÇÃO ESTRUTURAS
    │   ├── DoublyLinkedList.py              DE DADOS, ETC...)
    │   ├── __init__.py
    │   ├── Node.py
    │   ├── PageFaultException.py
    │   ├── Queue.py
    │   └── SecondChanceSpecializedQueue.py
    └── __main__.py ------------------------ MÓDULO PRINCIPAL DO PACOTE
```

---

### Executando o código do simulador

Para executar o código do simulador deve-se certificar que o seu intérprete
python esteja ao menos na versão 3.8

- Na raiz do projeto, executar:

```bash
python -m src
```

O simulador vai ler os dados de teste do arquivo `resources/data`, então, caso
deseje utilizar outro conjunto de teste, basta subsituir o arquivo

---

### Saída do programa

Durante a execuao do programa, serão registrados na saída padrão (`stdout`)
dados referentes à execução de cada um dos algoritmos de paginação, da seeguinte
maneira:

```
- FIFO -
Total page faults: 96929
Total elapsed time: 1.2964086532592773

- SECOND CHANCE -
Total page faults: 96930
Total elapsed time: 1.5335824489593506

- NRU -
Total page faults: 99801
Total elapsed time: 1.2737925052642822

- LRU -
Total page faults: 96941
Total elapsed time: 106.11731576919556
```

---

### Análise e observações

Os algoritmos simulados foram:

- **NRU** NOT RECENTLY USED
- **LRU** LAST RECENTLY USED
- **FIFO** FIRST IN FIRST OUT
- **SECOND CHANCE**

Foram conduzidos testes em diferentes configurações e os resultados destes foram
comparados com o "controle" (execução com 1024 quadros, 100 000 paginas), os
cenários testando possibilidades com:

- \+ QUADROS / + PAGINAS (2048, 200 000)
- \- QUADROS / - PAGINAS (512, 50 000)
- \+ QUADROS / - PAGINAS (2048, 50 000)
- \- QUADROS / + PAGINAS (512, 200 000)

À partir destes experimentos, observou-se que:

- Esta implementação de **NRU** em particular apresenta, em média, o menor tempo
  de execução dos quatro algoritmos sobre os casos em geral;
- Esta implementação de **LRU** em particular apresenta, em média, o maior tempo
  de execução dos quatro algoritmos sobre os casos em geral, por uma margem
  considerável;
- Para casos com número menor de páginas, o algoritmo **NRU** apresentou, em
  média, o menor número de PageFaults;
- O algoritmo **LRU** é o que apresenta a melhor adaptibilidade em critério de
  número de PageFaults para casos com crescente número de páginas.
