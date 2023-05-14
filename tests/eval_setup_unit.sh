#!/bin/bash

if [ ! -d git_eleves_eval ]
then
    echo "No git_eleve machin"
    exit 1
fi

if [ $1 -le 9 ]
then
    dir_eleve="rs2022proj20$1"
else
    dir_eleve="rs2022proj2$1"
fi

cd git_eleves_eval

cd $dir_eleve
#rm detailed_results_*
#rm recap_result_*
#ls ..
#sudo rm -r arbre
#sudo cp -r ../../arbre arbre
rm -r tests
cp -r ../../mimou tests
rm detailed_results_$1
rm recap_result_$1
#sudo chown -R mracouch arbre
cd ..

