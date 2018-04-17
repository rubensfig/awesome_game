# Tiny game demo in C++

## Usage

To run this program execute
```
$ make
$ ./fmq-game
 ```

# Respostas às perguntas

## Pergunta 1

A divisão dos prémios foi feita da seguinte forma:

Multiplicador x3 = A A A
Multiplicador x2 = B B B
Multiplicador x2 = C C C
Multiplicador x1 = D D D
Multiplicador x1 = E E E
Multiplicador x1 = F F F

E o prémio é calculado através de:
Prémio = Multiplicador\*Aposta
Frequência de pagamento = P(x3)^3 + P(B)^3 + P(C)^3 = 25%
Percentagem retorno = 15\*P(x3)^3 + 5\*P(x2)^3 + P(x1)^3 = 75%

## Pergunta 2

Mantendo a mesma lógica da resposta anterior:

1 = MultA\*P(x3)^3 + MultB\*P(x2)^3 + P(x1)^3 <=> MultA = 21 && MultB = 7
