# Tests de la pipeline

## Préambule
Ces tests ainsi que l'arbre de fichiers sont extraits de l'image docker publique
configurées dans la pipeline du dépot gitlab.

- ⚠️⚠️  Nous ne cherchons en aucun cas à nous attribuer leurs conceptions. 
- ℹ️ - Nous sommes toutefois à l'origine du script qui permet le lancement automatique

L'objectif est simplement de pouvoir s'en servir en local afin de détecter d'éventuels
problèmes avant même de commit sur le serveur.

## Marche à suivre 

1. Unzipper l'arbre de test, avec par exemple: ``unzip -q ./arbre.zip``
2. Lancer les tests avec ``./run_pipeline_tests.sh`` le make se fait automatiquement.

## Bonus
Si vous avez l'erreur ``/bin/bash^M: bad interpreter: No such file or directory``
sur Windaube, essayez ça :
``` sh
sed -i -e 's/\r$//' ./run_pipeline_tests.sh
ls ./tests/ | xargs printf "./tests/%s\n" | xargs sed -i -e 's/\r$//' $1
```








