# Emulador PH1 v1.0

### Curso de Ciência da Computação UPF

Trabalho da disciplina de Arquitetura e Organização de Computadores

### Alunos:

- João Pedro Lumi
- Vítor De Bortoli

Prof. Marcos José Brusso

---

## O que é o PH1

> O PH1 é um processador que trabalha com uma palavra de máquina de 8 bits, porém utiliza apenas 4 bits para representar seu conjunto de 16 instruções, as quais são suficientes para se entender o funcionamento de um processador simples.

### Instruções:
|Código em Hexa|Instrução|Descrição|
|-|-|-|
|00|NOP|Nenhuma operação|
|10|LDR|Carrega valor em registrador|
|20|STR|Armazena valor na memória|
|30|ADD|Soma|
|40|SUB|Subtração|
|50|MUL|Multiplicação|
|60|DIV|Divisão|
|70|NOT|Negação lógica bit-a-bit|
|80|AND|E lógico bit-a-bit|
|90|OR|OU lógico bit-a-bit|
|A0|XOR|OU lógico exclusivo bit-a-bit|
|B0|JMP|Desvio incondicional|
|C0|JEQ|Desvio se AC igual a zero|
|D0|JG|Desvio se AC maior que zero|
|E0|JL|Desvio se AC menor que zero|
|F0|HLT|Término da execução|

---

### Exemplo de entrada:

A primeira coluna representa os endereços de memória e a segunda coluna o valor que o endereço guarda, ambos em hexadecimal.

```
00 10
01 81
02 30
03 82
04 20
05 80
06 F0
80 00
81 05
82 02
```

### Exemplo de saída:

```
Input file: example.txt

LDR 81 ; AC <- MEM[81]
ADD 82 ; AC <- AC + MEM[82]
STR 80 ; MEM[80] <- AC
HLT

4 instructions executed

Registers:
AC 07
PC 07

Memory:
80 07
```