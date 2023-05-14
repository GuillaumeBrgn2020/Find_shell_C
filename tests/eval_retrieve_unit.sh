#!/bin/bash

if [ ! -d git_eleves_eval ]
then
    mkdir git_eleves_eval
fi

cd git_eleves_eval

dir_eleve=""

if [[ $1 -le 9 ]]
then
    dir_eleve="rs2022proj20$1"
else
    dir_eleve="rs2022proj2$1"
fi


echo "Mimou $dir_eleve"


git clone https://gitlab.telecomnancy.univ-lorraine.fr/rs2022/$dir_eleve
#git pull https://gitlab.telecomnancy.univ-lorraine.fr/rs2022/$dir_eleve

cd $dir_eleve
sudo cp -r ../../arbre arbre
cp -r ../../mimou tests
sudo chown -R mracouch arbre
cd ../..
