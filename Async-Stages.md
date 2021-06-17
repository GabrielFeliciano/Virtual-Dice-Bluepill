# Asynchronous Stages 

## English Version

1. Logic: Design the project's algorithm and its flowchart.

2. Project input circuit: The project requires a button. Decide which gpio type of input suits the project objectives and justify your choice.

3. Functions: Make a research about the *rand()* and describes how it can be used in the C language.

4. Functions: Search for the 7 segment displayer and its diferences between the catode common and anode common. Then, study the function that writes a number into the display and makes the right ajusts.

5. Project output circuit: Find the necessary value of a resistor that must placed in each pin of the 7 segment display. Find the HDSP-5501's datasheet and identify the VF and IF parameters for the calculation of the resistor.

```markdown
Serie 55XX
* Vf (typical): ~2.1[V] (max: 2.5[V])
* If: 10[mA] ~ 20[mA]

R = (3.3[V] - 2.1[V]) / 15[mA] = 80[Ω] (90[Ω] recommended)
```

## Portuguese Version

1. Lógica: elabore o algoritmo e o fluxograma do projeto.

```markdown
* Fluxograma do projeto: https://lucid.app/lucidchart/invitations/accept/inv_041dea28-
d025-4666-813b-e2b5ea054e91?viewport_loc=-852%2C24%2C3636%2C1700%2C0_0
```

2. Projeto circuito entrada: na implementação do projeto, é necessário 1 botão. Decida qual tipo de entrada do STM32 vocês vão utilizar e justifique a escolha.

```markdown
* GPIO: Escolhemos o GPIOB por causa que a maioria dos pinos GPIOB suportam 5v
* Input: Pull Down. Escolhemos esse tipo de entrada pois iremos conectar o botão entre **VCC** e o pino de entrada.
* Fluxograma do circuito: https://lucid.app/lucidchart/invitations/accept/inv_ec10d772-
43fe-4dd8-9dc6-5e9f376a953f?viewport_loc=220%2C273%2C1480%2C692%2C0_0
```

3. Funções: pesquise sobre a função rand() e como ela pode ser utilizada em um programa na linguagem C.

```markdown
R: A rand() é uma função da biblioteca (stdlib.h) que gera números inteiros aleatórios.
Para ser utilizada na linguegem C basta usar o RAND_MAX, que gera um valor de 0
até RAND_MAX sendo que o RAND_MAX pode variar.
```

4. Funções: estude o que é um display de 7 segmentos e a diferença entre os modelos anodo comum e catodo comum. Após isso, estude a função de mostrar um número de display 7 segmentos fornecida e ajuste a pinagem para o seu circuito.

5. Projeto circuito saída: calcule o resistor que deve ser colocado em série em cada segmento do display de 7 segmentos. Pesquise o manual do display HDSP-5501 e identifique os parâmetros VF e IF para o cálculo do resistor.

```markdown
Serie 55XX
* Vf (típico): ~2.1[V] (max: 2.5[V])
* If: 10[mA] ~ 20[mA]

R = (3.3[V] - 2.1[V]) / 15[mA] = 80[Ω] (90[Ω] recomendável)
```