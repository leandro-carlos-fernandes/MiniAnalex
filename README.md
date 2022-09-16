# MiniAnalex

O objetivo deste projeto é servir de exemplo de como podemos construir um analisador léxico, implementado em linguagem C, que seja capaz de identificar elementos representativos em uma linguagem fonte.

Nossos arquivos de entrada (codigos-fontes) consistem em estruturas que representem expressões aritméticas que envolvam:
- operações básicas,
- parênteses,
- literais e
- variáveis (identificadores).

## Elementos da linguagem:

As expressões são escritas de forma linear, sendo constituidas essencialmente das operações e operandos que elas envolvem. O uso de parênteses permite alterar a precendência entre as operações e/ou agrupar elementos de modo a utilizar seus resultados parciais em outras operações.

### Operadores

| Símbolo | Operação | Exemplo | Descrição |
| ----------- | ----------- | ----------- | ----------- |
| `<-` | Atribuição | X <- 12 + 23 | Aramazena o valor resultante da expressão a direita na variável a esquerda do operador. |
| `+` | Adição | 0.5 + taxa | Realiza a adição de literais ou de valores armazenados em variáveis. |
| `-` | Subtração | saldo - valor | Operador binário que subtrai o valor do segundo operando do valor do primeiro. |
| `*` | Multiplicação | montante * 1.73 | Representa a operação de multiplicação entre dois operandos. |
| `/` | Divsão | | Descreve a operação de divisão real entre valores numéricos. |

### Identificadores

Nomes descritivos que identificam, de maneira unequivoca, variáveis e funções.

Sua formação deve seguir as seguintes regras:
- Podem ser constituidos de letras ou digitos, exceto assim o emprego de caracteres especiais (espaços, simbolos, pontuação etc); e
- Não podem iniciar com um dígito.

## Exemplos de entradas válidas

Conversão de temperatura:
```
F <- 1.8 * C + 32
```

Báskara:
```
delta <- b*b - 4*a*c
x1 <- (-b + sqrt(delta)) / (2*a)
x2 <- (-b - sqrt(delta)) / (2*a)
```
