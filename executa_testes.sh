#!/bin/bash

gcc -O3 testes.c CppVector.c SortFunctionsCPP.c -o benchmark_c -lm
g++ -O3 codigo-nativo.cpp -o benchmark_cpp

HEADER="Linguagem;Tipo;Tamanho;Inserir;Buscar;Ordenar;Remover;Memoria"
echo $HEADER > resultados_c.csv
echo $HEADER > resultados_cpp.csv

echo "Iniciando 10 rodadas..."
for i in {1..10}
do
   echo "Rodada $i de 10"
   
   ./benchmark_c | tr -d " " | sed 's/,/;/g' | sed 's/\./,/g' >> resultados_c.csv
   ./benchmark_cpp | tr -d " " | sed 's/,/;/g' | sed 's/\./,/g' >> resultados_cpp.csv
done

echo "Concluído!"
