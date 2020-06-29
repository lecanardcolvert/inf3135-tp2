---
title: "Travail pratique 2: Générer des cartes isométriques"
---

Dans ce deuxième travail pratique, vous devez apporter des modifications à un
programme qui permet de générer des [cartes
isométriques](https://fr.wikipedia.org/wiki/Perspective_isom%C3%A9trique).

Le travail doit être réalisé **seul**. Il doit être remis au plus tard le **26
juillet 2020** à **23h59**.  À partir de minuit, une pénalité de **2% par
heure** de retard sera appliquée.

## Objectifs spécifiques

Les principaux objectifs visés sont les suivants :

* Se **familiariser** avec un logiciel développé en C par quelqu'un d'autre
* Apporter des **modifications** à ce logiciel, en utilisant notamment des
  **requêtes d'intégration** (*merge requests*)
* Apprendre à utiliser des **bibliothèques tierces** à l'intérieur d'un
  programme C, en consultant la documentation disponible
* **Documenter** convenablement des requêtes d'intégration à l'aide du format
  Markdown
* Utiliser correctement un **logiciel de contrôle de version** pour apporter
  les modifications en question
* S'assurer que les modifications apportées sont adéquates en proposant ou en
  mettant à jour un **cadre de tests** qui montre que les modifications
  n'entraînent pas de régression

## Description du travail

Rendez-vous sur
[https://gitlab.info.uqam.ca/inf3135-ete2020/inf3135-ete2020-tp2](https://gitlab.info.uqam.ca/inf3135-ete2020/inf3135-ete2020-tp2),
où se trouve le générateur de cartes isométriques. Avant-même de créer une
copie (*fork*), prenez le temps de bien vous familiariser avec la structure du
projet, les fichiers disponibles, le code source et le fonctionnement général
du programme.

**Note**: ne négligez pas cette étape importante. Vous devez prévoir un certain
temps pour comprendre le programme avant même d'écrire une seule ligne de code!

Votre travail consiste à compléter les quatre tâches ci-bas. Bien que ce ne
soit pas obligatoire, il est recommandé de les implémenter dans l'ordre
présenté.

### Tâche 1: Régler les fuites de mémoire (`memory-leak`)

En l'état actuel, le programme entraîne des fuites de mémoire lorsqu'il est
invoqué dans certaines situations. À l'aide de l'outil
[Valgrind](https://valgrind.org/), identifiez les sources de ces fuites et
apportez les correctifs nécessaires.

Vos modifications devront être sauvegardées sur une branche nommée
`memory-leak`.

### Tâche 2: Générer un fichier DOT du graphe de la carte (`dot-output`)

À compléter.

### Tâche 3: Valider la lecture d'une carte au format JSON (`validate-json`)

Lorsque le programme charge une carte isométrique depuis un fichier JSON,
aucune validation n'est faite: le programme suppose que le format JSON est bien
respecté, que les données disponibles sont intègres et que les fichiers des
images dessinées existent bien.

Ce comportement rend difficile le débogage lorsque les données sont corrompues,
car il peut soulever des erreurs de segmentation ou des comportements
indéterminés. Dans cette tâche, vous devez améliorer la robustesse de votre
programme et, en cas d'erreur, afficher des messages d'erreur 

### Tâche 4: Tracer un chemin entre le départ et l'arrivée (`draw-walk`)

À compléter.

### Dépendance/indépendance entre les tâches

Il est important de bien diviser les branches et les *commits* selon les tâches
auxquelles ils se rapportent. En particulier, vous devez faire attention de les
diviser selon qu'elles sont dépendantes ou indépendantes. Par conséquent, il
est important de bien structurer la « topologie » de vos contributions pour
qu'elle reflète les dépendances ou l'indépendance des branches.

## Soumettre une contribution

Un des objectifs de ce travail pratique est de vous habituer à soumettre vos
modifications en utilisant les mécanismes offerts par le logiciel de contrôle
de versions Git et les plateformes de développement collaboratif telles que
GitLab. Plus précisément, vous devrez utiliser une *requête d'intégration* (en
anglais, *merge request*, aussi parfois appelée *pull request*). Pour cela,
vous devrez créer une branche pour chacune des tâches demandées. Afin de
simplifier la correction, il est important de respecter **exactement** la
nomenclature des branches (`memory-leak`, `validate-json`, `dot-output`,
`draw-walk`).

Dans un premier temps, vous devez répliquer (en anglais *fork*) le programme de
base disponible. Assurez-vous de bien faire une copie **privée** (sinon les
autres étudiants pourront voir votre solution et vous serez alors responsable
s'il y a plagiat). Ensuite, vous devrez donner accès à votre projet en mode
*Maintainer* à l'utilisateur `blondin_al`.

Supposons que vous avez complété la branche `memory-leak` sur votre dépôt local
et que vous souhaitez la partager. Alors il vous suffit de pousser la branche
`memory-leak` sur votre propre dépôt puis de créer une requête d'intégration de
la branche `memory-leak` à la branche `master` (toujours dans votre dépôt). Il
est recommandé de vous inspirer de la
[task0](https://gitlab.com/ablondin/inf3135-aut2017-tp2/merge_requests/1) pour
un exemple de requête bien rédigée.

**Attention!** Dans votre travail, il est important de **ne pas** fusionner de
branche lors de la remise de votre travail, car vous devez attendre que vos
modifications soient validées par quelqu'un d'autre, en l'occurrence, votre
enseignant. En pratique, on fait une requête d'intégration d'une branche de
notre dépôt personnel (`origin`) vers le dépôt principal (`upstream`).
Cependant, dans ce contexte académique, la requête doit être faite
à l'intérieur de votre dépôt privé, pour vous assurer que personne d'autre ne
puisse consulter votre code. Ainsi, toutes vos requêtes se feront d'une branche
vers la branche `master` de votre propre dépôt.

## Tests automatiques

Actuellement, lorsqu'on entre la commande

```sh
$ make test
```

une suite de tests est lancée. Lorsque vous apporterez des modifications au
programme, vous devez vous assurer que celles-ci ne brisent pas les suites de
tests (autrement dit, il s'agit de **tests de régression** et vous devez en
tenir compte dans vos modifications).

Lorsque vous allez apporter des modifications au logiciel, vous devrez
également ajouter ou modifier des suites de tests afin d'illustrer que ce que
vous avez fait est fonctionnel et ne brise pas l'état actuel du projet.

## Contraintes

Afin d'éviter des pénalités, il est important de respecter les contraintes
suivantes:

- Votre projet doit être un clone (*fork*) **privé** du projet
  https://gitlab.com/inf3135-ete2020/inf3135-ete2020-tp2. L'adjectif **privé**
  est très important si vous ne voulez pas que d'autres étudiants accèdent
  à votre solution!
- Vos quatre tâches doivent se trouver sur des branches nommées **exactement**
  `memory-leak`, `validate-json`, `dot-output` et `draw-walk`
- **Aucune requête d'intégration** ne doit être faite vers le dépôt public
  (sans quoi les autres étudiants pourront voir vos modifications!)
- **Aucune requête d'intégration** ne doit être fusionnée sur la branche
  `master` (ou tout autre branche), car elle doit d'abord être validée par
  quelqu'un d'autre (l'enseignant ou le correcteur) avant d'être intégrée,
  étape qui ne sera pas couverte dans le présent travail pratique
- **Aucune variable globale** (à l'exception des constantes) n'est permise
- Votre programme doit **compiler** sans **erreur** et sans **avertissement**
  lorsqu'on entre ``make``.

Advenant le non-respect d'une ou plusieurs de ces contraintes, une pénalité
pouvant aller jusqu'à **50%** de la note totale pourrait être appliquée.

## Remise

Votre travail doit être remis au plus tard le **26 juillet 2020** à **23h59**.
À partir de minuit, une pénalité de **2% par heure** de retard sera appliquée.

La remise se fait **obligatoirement** par l'intermédiaire de la plateforme
[GitLab du département](https://gitlab.info.uqam.ca/). **Aucune remise par
courriel ne sera acceptée** (le travail sera considéré comme non remis).

Les travaux seront corrigés sur Linux ou sur le serveur Java. Vous devez donc
vous assurer que votre programme fonctionne **sans modification** sur au moins
une de ces deux plateformes.

## Barème

Pour chacune des quatre tâches, les critères suivants seront pris en compte
dans l'évaluation:

**Documentation du code source**

* Les *docstrings* respectent le standard Javadoc
* La documentation est bien formatée et bien aérée
* Le format est cohérent avec les autres *docstrings* déjà présentes dans le
  projet
* La *docstring* ne contient pas d'erreurs d'orthographe

**Qualité de la requête d'intégration (*merge request*)**

* Le titre de la requête est significatif
* La description de la modification apportée est claire, concise et précise. En
  particulier, elle respecte le format Markdown et l'exploite à son maximum.
* Le comportement du programme avant modification est décrit
* Le comportement du programme après modification est décrit
* Les messages de *commits* sont significatifs et ont un format cohérent avec
  les messages rédigés par les autres développeurs
* La requête ne contient pas d'erreurs d'orthographe

**Qualité du changement de code**

* Le code modifié est lisible, clair et concis
* Le code est bien aéré, de façon cohérente avec le style de programmation déjà
  existant
* Il utilise au maximum les fonctionnalités déjà présentes (ne pas réinventer
  la roue)
* Il est bien factorisé
* La solution n'est pas inutilement complexe

**Fonctionnalité**

* Les modifications apportées répondent à ce qui est demandé
* Les modifications ne brisent pas les tests déjà présents
* S'il y a lieu, des tests sont ajoutés pour illustrer le fait que les
  nouvelles fonctionnalités ont été correctement implémentées

La pondération pour chacune des tâches est distribuée comme suit:

| Tâche                     | Documentation | Requête   |   Code    | Fonctionnalité |  Total    |
| ------------------------- | ------------- | --------- | --------- | -------------- | --------- |
| Tâche 1: `memory-leak`    |      0        |     8     |     2     |      10        |    20     |
| Tâche 2: `dot-output`     |      2        |     8     |     2     |       8        |    20     |
| Tâche 3: `validate-json`  |      5        |    10     |     5     |      10        |    30     |
| Tâche 4: `draw-walk`      |      5        |    10     |     5     |      10        |    30     |
| **Total**                 |   **12**      |  **36**   |  **14**   |    **38**      | **100**   |
