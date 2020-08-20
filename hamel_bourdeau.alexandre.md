# Évaluation du travail pratique 2

## Identification de l'étudiant

* Nom d'utilisateur: hamel_bourdeau.alexandre
* Nom et prénom: Hamel Bourdeau Alexandre
* Code permanent: HAMA12128907

## Points

| Tâche     | Documentation | Requête   |   Code    | Fonctionnalité |  Total    |
| --------- | ------------- | --------- | --------- | -------------- | --------- |
| Tâche 1   |               |    6/8    |    3/4    |       8/8      |   17/20   |
| Tâche 2   |      4/4      |    6/8    |    4/5    |       8/8      |   22/25   |
| Tâche 3   |      5/5      |   10/10   |    5/5    |       7/10     |   27/30   |
| Tâche 4   |      4/4      |    6/8    |    5/5    |       8/8      |   23/25   |
| **Total** |     13/13     |   28/34   |   17/19   |      31/34     |   89/100  |

## Tâche 1: `memory-leak`

- La requête d'intégration est très bien, peut-être juste inclure la commande
  dans le bloc de code qui contient le rapport de Valgrind:

```sh
$ commande
résultat
```

- Ne pas mettre de ligne vide sans raison dans le code modifié (respecter le
  style existant). De la même façon, utiliser la syntaxe `snake_case` et non
  `camelCase` pour les identifiants (`refCount`, `sRefCount`).
- 5 messages de commit avec le même nom "Correction: fuite de mémoire", c'est
  pas très descriptif. De plus, la syntaxe des messages de *commit* ne
  respectent pas celle utilisée dans le projet.

## Tâche 2: `dot-output`

- Requête très bien, même commentaire que pour la tâche 1
- README impeccable
- Dans `geometry.c`, pas idéal d'utiliser `malloc`. Ça peut potentiellement
  entraîner des fuites de mémoire (je vois que tu fais attention ensuite, mais
  c'est risqué). Mieux vaut passer la chaîne en argument et la remplir (comme
  fait la fonction `strcpy` par exemple, qui n'utilise pas l'allocation
  dynamique). Mieux, tu devrais simplement afficher directement avec `fprintf`
  plutôt qu'utiliser `sprintf`.
- Ne pas commenter les code (`// Paramètres par défaut`, `// Premièrement`,
  etc.). Si ces commentaires sont nécessaires, alors mieux vaut créer des
  fonctions et utiliser leur nomenclature pour jouer le rôle de commentaires.
  Éviter les lignes vides (comme c'est le cas dans le reste du programme).
- Même problème avec les messages de *commit* qui devraient commencer avec un
  verbe.

## Tâche 3: `validate-json`

- Nombre de tests réussis (voir annexe): 7/10.
- 6 fichiers de tests
- Avertissement à la compilation: `comparison of integer expressions of
  different signedness` (12 fois)
- Requête impeccable
- README. C'est bien de décrire le système de code. J'aurais mis moins de
  valeurs possibles par contre.
- Code ajouté. Vraiment bien. Préférer le nom `json_validation` à
  `jsonvalidation`. Aussi, dans les *docstrings* ne mettre qu'une seule ligne
  générale et ensuite sauter une ligne pour donner les détails. Quand on décrit
  `@return`, ne pas donner tous les cas possibles, juste dire que ça retourne
  une valeur d'état. Et le type de retour devrait être un `enum`, pas `unsigned
  int`.
- Mêmes remarques sur les messages de *commit*


## Tâche 4: `draw-walk`

- La branche est basée sur `dot-output`, mais pas sur le dernier commit
- Requête très bien. Une image aurait été intéressante pour montrer le format
  PNG
- Code ajouté très bien. Ne pas commenter et éviter les lignes vides sans
  raison précise.
- Mêmes remarques sur les *commits*

## Annexe: Résultats tests (validate-json)

### data_wrong_format (33) : ok

```text
Erreur #33.
Veuillez svp vérifier les données du fichier JSON source.
```

### data_wrong_value (0) : not ok

```text
Tileset of 3 tiles:
  Tile id=1
    incoming directions: vect(1,0,-1),vect(-1,0,-1),vect(0,1,-1),vect(0,-1,-1)
    outgoing directions: vect(1,0,-1),vect(-1,0,-1),vect(0,1,-1),vect(0,-1,-1)
  Tile id=2
    incoming directions: vect(1,0,0),vect(-1,0,0),vect(0,1,0),vect(0,-1,0),vect(1,0,1),vect(-1,0,1),
    outgoing directions: vect(1,0,0),vect(-1,0,0),vect(0,1,0),vect(0,-1,0),vect(1,0,1),vect(-1,0,1),
  Tile id=3
    incoming directions: vect(1,0,-1),vect(-1,0,-1),vect(0,1,-1),vect(0,-1,-1)
    outgoing directions: vect(1,0,-1),vect(-1,0,-1),vect(0,1,-1),vect(0,-1,-1)
A map of 2 layers
  Layer 0: A layer of 3 rows and 3 columns (offset = (0,0,0))
    2 2 2 
    2 2 2 
    2 2 2 
  Layer 1: A layer of 3 rows and 3 columns (offset = (0,0,1))
    1 0 0 
    0 10 0 
    0 0 3 
```

### filename_wrong_value (31) : ok

```text
Erreur #31.
Veuillez svp vérifier les données du fichier JSON source.
```

### id_wrong_value (30) : ok

```text
Erreur #30.
Veuillez svp vérifier les données du fichier JSON source.
```

### missing_filename_in_tileset (15) : ok

```text
Erreur #15.
Veuillez svp vérifier les données du fichier JSON source.
```

### missing_offset_in_layers (26) : ok

```text
Erreur #26.
Veuillez svp vérifier les données du fichier JSON source.
```

### missing_z-offset (6) : ok

```text
Erreur #6.
Veuillez svp vérifier les données du fichier JSON source.
```

### num-cols_negative_value (33) : ok

```text
Erreur #33.
Veuillez svp vérifier les données du fichier JSON source.
```

### offset_wrong_format (0) : not ok

```text
Tileset of 3 tiles:
  Tile id=1
    incoming directions: vect(1,0,-1),vect(-1,0,-1),vect(0,1,-1),vect(0,-1,-1)
    outgoing directions: vect(1,0,-1),vect(-1,0,-1),vect(0,1,-1),vect(0,-1,-1)
  Tile id=2
    incoming directions: vect(1,0,0),vect(-1,0,0),vect(0,1,0),vect(0,-1,0),vect(1,0,1),vect(-1,0,1),
    outgoing directions: vect(1,0,0),vect(-1,0,0),vect(0,1,0),vect(0,-1,0),vect(1,0,1),vect(-1,0,1),
  Tile id=3
    incoming directions: vect(1,0,-1),vect(-1,0,-1),vect(0,1,-1),vect(0,-1,-1)
    outgoing directions: vect(1,0,-1),vect(-1,0,-1),vect(0,1,-1),vect(0,-1,-1)
A map of 2 layers
  Layer 0: A layer of 3 rows and 3 columns (offset = (0,0,0))
    2 2 2 
    2 2 2 
    2 2 2 
  Layer 1: A layer of 3 rows and 3 columns (offset = (0,0,1))
    1 0 0 
    0 0 0 
    0 0 3 
```

### tile-width_negative_value (0) : not ok

```text
Tileset of 3 tiles:
  Tile id=1
    incoming directions: vect(1,0,-1),vect(-1,0,-1),vect(0,1,-1),vect(0,-1,-1)
    outgoing directions: vect(1,0,-1),vect(-1,0,-1),vect(0,1,-1),vect(0,-1,-1)
  Tile id=2
    incoming directions: vect(1,0,0),vect(-1,0,0),vect(0,1,0),vect(0,-1,0),vect(1,0,1),vect(-1,0,1),
    outgoing directions: vect(1,0,0),vect(-1,0,0),vect(0,1,0),vect(0,-1,0),vect(1,0,1),vect(-1,0,1),
  Tile id=3
    incoming directions: vect(1,0,-1),vect(-1,0,-1),vect(0,1,-1),vect(0,-1,-1)
    outgoing directions: vect(1,0,-1),vect(-1,0,-1),vect(0,1,-1),vect(0,-1,-1)
A map of 2 layers
  Layer 0: A layer of 3 rows and 3 columns (offset = (0,0,0))
    2 2 2 
    2 2 2 
    2 2 2 
  Layer 1: A layer of 3 rows and 3 columns (offset = (0,0,1))
    1 0 0 
    0 0 0 
    0 0 3 
```
