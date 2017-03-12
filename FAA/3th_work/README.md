# Descrição

SW de controle de voos para a ANAC, para os aeroportos nacionais

  Número ilimitado de aeroportos
  Para cada aeroporto um número ilimitado de voos cadastrados

  Cada nó de voo deve conter o seu aeroporto de origem e de destino

## Aeroporto

  Nome: 3 letras em UPERCASE, única

## Voos

  Companhia aéria:  único, UPERCASE
  Número identificador (único) do voo

## Regras

  não deve existir mais de um voo no mesmo sentido entre um par de aeroportos. As rotas são exclusivas para cada companhia

Tudo deve ser implementado por meio de listas encadeadas, com a seguinte estrutura:

```
# lista de todos os aeroportos
lista_de_voos => {
  nome_do_aeroporto,
  ponteiro_proximo_voo,
  ponteiro_lista_voos
}

# associada a cada aeroporto
voos => {
  numero_do_voo,
  nome_da_companhia,
  ponteiro_aeroporto_destino,
  ponteiro_proximo_voo
}

```

## Devem ser implementados

* CadastraAeroporto(aeroporto): cadastra um novo aeroporto no sistema.
* RemoveAeroporto(aeroporto): remove um aeroporto do sistema. Note que toda a lista de voo desse aeroporto deve ser removida também;
* CadastraVoo(Aeroporto1, Aeroporto2, Numero Voo, Nome Companhia): Cadastra um novo voo entre dois aeroportos, informando o número do voo e nome da companhia;
* RemoveVoo(Aeroporto1,Aeroporto2): Remove um voo existente entre dois aeroportos;
* ImprimeVoosCompanhia(Nome Companhia): Imprime todos os voos de uma determinada companhia;
* ImprimeVoosAeroporto(Aeroporto): Imprime todos os voos partindo de um determinado aeroporto;
* ImprimeAeroportos(): Imprime todos os aeroportos cadastrados;
* ViagemInterativa(Aeroporto Inicio): Permite navegar entre aeroportos através das opções de voo de cada aeroporto. Deve ser exibido todos os voos de uma aeroporto, o usuário escolhe um voo e vai para o aeroporto de destino, e o processo se repete até que o usuário informe que deseja parar de viajar;
* ImportaDados(arquivo): Importa operações a partir de um arquivo de texto. Os dados que
já estão em memória não devem ser perdidos durante a importação.
* ExportaDados(arquivo):  Exporta todos os dados da memória para um arquivo de instruções conforme descrito abaixo.


Fortmato de importação de dados a partir de um arquivo

```
  CAD_AEROPORTO nome_aeroporto
  REM_AEROPORTO nome_aeroporo
  CAD_VOO aeroporto1 aeroporto2 num_voo nome_comp
  REM_VOO aeroporto1 aeroporto2
```
