#!/bin/bash
# shellcheck disable=SC2181

# On se déplace à l'emplacement du script pour que son déroulement
# ne dépende pas du cd du lanceur
cd "$(dirname "$0")" || exit 1

#if [ "$#" -ge 1 ]; then
    cd ../..
    echo "----------------- MAKE -------------------"
    make
    cd ./tests_/tests_pipeline || exit 1
    cp ../../ftc ./
#fi

./tests/file_exist ftc
list=$(ls ./tests/)
c=1
for i in $list ; do
  echo ""
  echo "----------------- Test $c/11 : $i -------------------"
  ./tests/"$i"
  if [ $? -ne 0 ]; then
      echo "------ ECHEC :( --------"
      exit 1
  fi
  c=$((c+1))
done

echo " _______________________________________"
echo "/  ____                            _ _  \\"
echo "| / ___| _   _  ___ ___  ___ ___  | | | |"
echo "| \___ \| | | |/ __/ _ \/ __/ __| | | | |      (so far...)"
echo "|  ___) | |_| | (_|  __/\__ \__ \ |_|_| |"
echo "| |____/ \__,_|\___\___||___/___/ (_|_) |"
echo "\                                       /"
echo " ---------------------------------------"
echo "        \   ^__^"
echo "         \  (oo)\_______"
echo "            (__)\       )\/'\'"
echo "                ||----w |"
echo "                ||     ||"
