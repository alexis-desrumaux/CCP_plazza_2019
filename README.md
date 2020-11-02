Le but de ce projet est de recréer le principe d'une pizzeria.
Le programme fonctionne comme un mini-shell avec des commandes spécifiques tels que "help", "status" ou encore "exit".
Lorque le programme est lancé, il y a un message d'accueil recréant le principe d'une carte de restaurant.
Pour les commandes:

 - La commande "help" joue le rôle du serveur. Elle va donner des informations sur le programme ainsi que comment l'utiliser.
 - La commande "status" va donner les information sur le(s) cuisine(s) et cuisinier(s). Si aucune cuisine n'est active, la commande n'affichera rien. Sinon, elle va afficher la liste des cuisines en service avec leurs nombres de cuisinier(s) ainsi que leurs status et le nombre d'ingrédients encore présent dans la cuisine.
 - La commande "exit" va faire quitter le programme et libérer la mémoire.

Sinon aucune de ces commandes n'est rentrées, le programme va alors considérer que c'est une commande de pizza(s). Elle va alors commencer par nettoyer la chaine de caractères pour ne laisser q'un seul espace entre chaque mot (principe d'un clean_str). La chaine sera alors mise sous forme de vecteur pour inspection et gesion d'erreur à savoir:
 - ligne 0 du vecteur: verification du nom de la pizza
 - ligne 1 du vecteur: verification de la taille de la pizza
 - ligne 2 du vecteur: verification de la quantité de pizza souhaitée sans le x (le caractere est aussi verifié ce qui fait que si dans cette case, on a par exemple g7, la commande sera fausse)

S'il n'y a pas lignes dans le vecteur ou si un des arguments n'est pas bon, la commande sera considérée comme non valide et sera donc ignorée.
Dans le cas ou plusieurs commandes successives sont faites(regina XXL x2; margarita XL x1), le programme découpera la chaine en vecteur de commandes et en sous vecteurs pour les arguments. En reprenant ce même exemple, un affichage graphique serait:
 - regina XXL x2
   - regina
   - XXL
   - 2
 - margarita XL x1
   - margarita
   - XL
   - 1

En cas de commandes fausses, elles seront ausi ignorées. Par exemple pour cette commande "regina XXL x2; margarita X x1; fantasia M x-1", la vérification indiquera que es commandes 2 et 3 sont fausses avec pour chacune des commandes un message d'erreur approprié.
La commande envoyé sera donc juste "regina XXL x2" puisqe que les 2 autres seront ignorées.

Pour le fonctionnement des cuisines, un systeme de cuisine "mère" et "filles" sont mise en place afin de faciliter la repartition des commandes, donc des pizzas.
La cuisine mère elle va servir d'intermediraire et va avoir aussi pour mission de récuperer les information des cuisines "filles" pour les afficher sur la sortie standard.
Si le timeout est depasée, la cuisine "mère" va envoyer un message a la cuisine "fille" concernée pour qu'elle se ferme.

En Résumé, dans ce programme il y a:
 - la gestion des multi-commandes avec ignorance des commandes fausses
 - la repartitions dans les cuisines
 - la création et destrucion de cuisines
 - l'ajout et le retrait d'ingrédients pour chaque cuisine
 - un système de surveillanc grâce à la commande "status"
 - un serveur qui nous aide en tapant a commande "help"
 - une sortie du restaurant avec la commande "quit"
 - un "log" des pizzas dans le fichier "ticketOrder.txt"
 - une communication par système de sockets, et de threads et mutex, est faite dans ce projet.

Merci.

Alexis Desrumaux
Damien Sun
Benjamin Bappel