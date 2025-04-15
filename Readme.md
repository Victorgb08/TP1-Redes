TRABALHO PRÁTICO Nº 1 (10 pontos)

### Orientações Gerais
- **Na GRADUAÇÃO**: Para os Trabalhos Práticos da disciplina deverão ser adotados os **MESMOS grupos** já formados para os Estudos Teóricos: **TRÊS grupos**, cada grupo formado por exatamente três membros, exceto um que será uma dupla.  
  **Na PÓS**: O trabalho será individual.
- Todos os experimentos deste trabalho deverão ser desenvolvidos em estações utilizando o sistema operacional **Linux**.  
  A instalação e familiarização com o ambiente Linux será uma atividade preliminar a ser realizada pelos membros do grupo.  
  **Sugestão de distribuição Linux gratuita, de fácil instalação e uso**: [Ubuntu](https://ubuntu.com).  
  **ATENÇÃO**: NÃO serão aceitos trabalhos executados em ambiente **Windows Subsystem for Linux (WSL)**.
- Todos os experimentos deste trabalho deverão ser programados e compilados em linguagem **C**, não se aceitando **NENHUMA construção de C++**.
- Todos os experimentos deste trabalho deverão ser testados em ambiente de **rede local**, com o servidor em uma estação **FISICAMENTE DIFERENTE** da estação dos clientes.  
  Sugere-se usar uma rede local sem fio.  
  **NÃO serão aceitos trabalhos** em que clientes e servidor estejam em locais fisicamente diferentes, usando comunicação via Internet (ex.: usando LogMeIn Hamachi).

---

### Experimentos

#### Etapa inicial de preparação
- Após estudar os textos de referência sobre programação em rede usando soquetes, digitem, compilem e executem os programas cliente e servidor do exemplo **simplextalk** da seção 1.4 do Capítulo 1 do livro-texto.
- Fiquem atentos às observações detalhadas no arquivo **“simplex-talk COMENTARIOS”**, disponível no espaço da disciplina no Moodle.
- Resolvam todos os possíveis problemas, de modo que os programas funcionem e “conversem” um com o outro.  
  **Nenhum relatório deverá ser gerado sobre esta etapa inicial.**

#### Experimento 1
- **Enunciado**:  
  Obtenha e construa o programa de exemplo usando sockets denominado simplex-talk, mostrado no texto.  
  Inicie um servidor e um cliente, em janelas separadas. Enquanto o primeiro cliente estiver sendo executado, inicie 10 outros clientes que se conectam ao mesmo servidor; esses outros clientes provavelmente deverão ser iniciados em segundo plano, com sua entrada redirecionada para um arquivo.  
  O que acontece com esses 10 clientes? Seus `connect()`s falham, esgotam o tempo limite ou têm sucesso? Alguma outra chamada é bloqueada?  
  Agora encerre o primeiro cliente. O que acontece? Experimente isso também com o valor `MAX_PENDING` do servidor definido como 1.

#### Experimento 2
- **Enunciado**:  
  Modifique o programa baseado em sockets denominado simplex-talk de modo que, toda vez que o cliente enviar uma linha ao servidor, este enviará a linha de volta ao cliente.  
  O cliente (e o servidor) agora terá que fazer chamadas alternadas a `recv()` e `send()`.

#### Experimento 3
- **Enunciado**:  
  Modifique o programa baseado em sockets denominado simplex-talk de modo que ele use UDP como protocolo de transporte em vez de TCP.  
  Você terá que substituir o parâmetro `SOCK_STREAM` pelo parâmetro `SOCK_DGRAM` no cliente e no servidor.  
  Depois, no servidor, remova as chamadas a `listen()` e `accept()` e substitua os dois laços aninhados no final por um único laço que invoca `recv()` com o socket `s`.  
  Finalmente, veja o que acontece quando dois desses clientes UDP se conectam simultaneamente ao mesmo servidor UDP e compare isso com o comportamento do TCP.

---

### Comentários sobre o código `simplex-talk`

- **AF_INET** e **PF_INET** são sinônimos.
- Use a porta **54321** em vez de **5432**:  
  ```c
  #define SERVER_PORT 54321

  ### Relatório

Realizados os experimentos, produzam o **Relatório do Trabalho Prático 1**, com a seguinte estrutura:

1. **Capa**  
   - Instituição, curso, disciplina, semestre, título do relatório, composição do grupo, data.

2. **Introdução**  
   - Breve descrição do que se trata o relatório.

3. **Experimento 1**  
   - Enunciado.  
   - Códigos fonte.  
   - Modificações feitas.  
   - Descrição detalhada dos testes realizados.  
   - Resultados obtidos.  
   - Análise dos resultados e conclusões.

4. **Experimento 2**  
   - Enunciado.  
   - Códigos fonte.  
   - Modificações feitas.  
   - Descrição detalhada dos testes realizados.  
   - Resultados obtidos.  
   - Análise dos resultados e conclusões.

5. **Experimento 3**  
   - Enunciado.  
   - Códigos fonte.  
   - Modificações feitas.  
   - Descrição detalhada dos testes realizados.  
   - Resultados obtidos.  
   - Análise dos resultados e conclusões.

6. **Bibliografia**  
   - Relação da bibliografia consultada.

---

### Entrega
- Este **Relatório do Trabalho Prático 1** deverá ser entregue em arquivo **PDF** (se em grupo, apenas um membro entrega).  
- **Prazo**: Até **23:59 h de 07/05/2025 (quarta-feira)** no Moodle.