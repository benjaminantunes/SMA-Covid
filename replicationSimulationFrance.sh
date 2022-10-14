#!/bin/bash
# ${@: -1} récupère le dernier argument (ici la config à utiliser).

valeurStatut = 0
for i in `seq 0 $1`;
do
    echo "./exe  $valeurStatut ${@: -1} &"
    time ./exe  $valeurStatut ${@: -1} &
    valeurStatut = $(($valeurStatut + 96))
    echo $valeurStatut
done
wait
