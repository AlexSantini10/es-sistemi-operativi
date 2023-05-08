#!/bin/bash

# Variabili generali
debug=0

reInt='^[0-9]+$'
reReal='^[0-9]+([.][0-9]+)?$'

# Check numero di argomenti
if [[ $# -lt 2 ]]; then
    echo "Numero di argomenti troppo basso"
    exit
fi

s=$1

shift

for it in $*; do
    echo $it

    # Check path
    if ! [[ -d $it ]]; then
        echo "Il path "$it" non è valido"
        exit
    fi

    ls -l $it | awk '{print $3" "$10}' > temp.txt

    # TODO: Finire stampa delle righe corrette
    while read line
    do
        echo $line
    done < temp.txt
done

