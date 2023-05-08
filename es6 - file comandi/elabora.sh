#!/bin/bash

# Variabili generali
debug=0

reInt='^[0-9]+$'
reReal='^[0-9]+([.][0-9]+)?$'

# Check numero di argomenti
if [[ $# != 1 ]]; then
    echo "Numero di argomenti errato"
    exit
fi

# Inserimento n
echo "Inserisci un numero intero N"
read n

# Debug n
if [[ $debug = 1 ]]; then
    echo $n
fi

# Check numero intero n
if ! [[ $n =~ $reInt ]]; then
    echo "Non è stato inserito un numero intero"
    exit
fi

# Check path
if ! [[ -f $1 ]]; then
    echo "Il path non è valido"
    exit
fi

# Check permessi
if ! [[ -r $1 ]]; then
    echo "Il file non è leggibile"
    exit
fi

# Lettura da file e scrittura in ordine su file out.txt
tail "$1" --lines="$n" > out.txt
sort -dr out.txt -o out.txt