# SMA-Covid
### Propriétaire de ce repo : Benjamin Antunes, doctorant au Limos.

Vous êtes sur le repository du projet de modèle reproductible de simulation Covid 19.

Articles références : A venir

Ce modèle est développé en C++ pour les performances. Il est parallélisé en SPMD (plusieurs simulations tournent simultanéments). Vous serez donc limité par votre nombre de coeurs de calcul (et votre RAM). 
Pour exécuter l'exemple, chaque simulation devrait utiliser 4 Go de RAM.

## Prérequis : 
- Pouvoir exécuter un makefile en ligne de commande (Compileur C++ -> g++)
- Avoir installé Jupyter Notebook
- Avoir Python3
- Etre sur une machine Ubuntu (non testé sur d'autres distributions)

## Procédure :
- Télécharger la branche master du projet, en fichier un git clone, ou bien en téléchargeant le Zip
- Se placer dans le dossier du projet
- Executer la commande : ./replicationSimulation.sh configLyon.txt configNoMesure.txt 4
(Cette commande va lancer 4 réplications en parallèle de la simulation sur la ville de Lyon avec la configuration sans mesure sanitaire)
- Comparer les résultats avec le dossier "expectedOutputCommandLine" la répétabilité

## Pour aller plus loin :
- Ouvrir un terminal
- Executer la commande : sudo apt-get install python3 (Si pas déja fait)
- Executer la commande : sudo apt-get install jupyter (Si pas déja fait)
- Télécharger la branche master du projet, en fichier un git clone, ou bien en téléchargeant le Zip
- Se placer dans le dossier du projet
- Lancer la commande : jupyter notebook
- Un navigateur Web avec Jupyter devrait s'ouvrir : Vous devez ensuite lancer le fichier de notebook SMA Covid.ipynb
- Vous retrouverez dans ce fichier les cellules qui sont expliquées ci-dessous (seulement deux cellules).
- Comparer les résultats avec le dossier "expectedOutputNotebook" pour assurer la répétabilité

## Description des fichiers : 

Les fichiers .cpp et . hpp correspondent au code du modèle. Vous n'avez pas besoin d'y toucher (mais vous pouvez).

Le fichier makefile permet de compiler correctement le projet.

Les fichiers "mts10p9N0000X" sont des statuts du générateur de nombre pseudo-aléatoire Mersenne Twister. Ils sont espacés de 2 Milliard de tirages. Ces 30 fichiers permettent donc de lancer 30 réplications indépendantes de simulations, qui doivent utiliser au maximum 2 milliard de nombre aléatoire. Si vos contraintes vous demande de faire plus de réplication ou plus de tirage par simulation, alors vous devrez utiliser/créer vos propres statuts de MT. Attention à respecter la norme de nommage en place. Pour en savoir plus sur la parallélisation de code utlisant des générateurs de nombres pseudo-aléatoire, veuillez vous référer à cet article : Hill 2018 ... 

Le fichier bash "ReplicationSimulation.sh" permet de lancer des simulations.

Le notebook Jupyter "SMA Covid.ipynb" permet de lancer très facilement vos expériences et récupérer vos résultats.

Les fichiers de configuration "configVille" et "configMesure" permettent de définir des configurations pour des villes/pays/territoires, et de paramétrer les différents éléments de la maladie, ainsi que les mesures sanitaires en place.


## Prise en main :

Pour prendre en main le modèle, vous devez simplement lancer le notebook jupyter via la commande "jupyter notebook" dans un terminal, ou autre moyen de votre choix.

Vous pouvez executer toutes les cellules.

La commande *!make* va permettre de compiler le programme.
La commande *!./replicationSimulation configLyon.txt configNoMesure.txt 30* est à faire évoluer !

Vous pouvez mettre vos propres fichiers de configurations de ville et de mesures que vous avez créé en suivant le format déjà présent. Vous pouvez au départ essayer le modèle avec les configurations existantes et comparer vos résultats avec ceux déjà obtenu, afin de tester la répétabilité. Si vos résultats sont différents, contactez nous à l'adresse benjamin.antunes@uca.fr (Nous pourrons étudier les causes de non répétabilité).
Cette commande peut prendre un certain temps. Elle va lancer le code C++ avec N simulation pour chaque ville que vous avez choisi avec votre fichier de configuration.
Par exemple, la ligne : 
*!./replicationSimulation configParis.txt configLyon.txt configNoVaccin.txt 10*
Va lancer 10 réplications de la simuation sur Paris avec la configNoVaccin et 10 réplications sur Lyon.
Il y aura donc 20 réplications en tout (20 processus de lancés en parallèle).

La cellule d'en dessous est également à modifier selon ce que vous avez entré au dessus : **Vous devez modifier NB_REPLICATION et listVille selon ce que vous avez utilisé dans la commande d'avant.**

Le fonctionnement est le suivant : Le code va générer des fichiers de log pour chaque simulation que vous avez lancé. La dernière cellule va utiliser ces logs afin de générer des statistiques et des figures pour chaque simulation, et les stocker dans le dossier dans lequel le notebook a été lancé. Vous pourrez ensuite établir vos propres conclusion sur l'impact des mesures sanitaires sur l'épidémie par exemple.

A noter : Vous devez calibrer le modèle en fonction des villes que vous utilisez : Le modèle n'est pas générique.
Il est tout à fait possible de passer sur une échelle département / pays, mais cela demandera plus de puissance de calcul, et surtout de mémoire.


## Les paramètres : 

### Ville : 
-	size : Taille de la carte.
-	nbHumain : Nombre d’humains dans la simu-lation.
-	nbMalade : Nombre de malades initial dans la simulation.
-	nbIteration : Nombre d’itérations de la simu-lation correspondant au nombre de jours.
-	nbPlaceHospital : Places disponibles dans les hôpitaux.
-	nbPlaceReanimation : Places disponibles en réanimation.
-	nbDeplacementJour : Le nombre de déplacement par itération des humains contaminés.

### Config : 
-	tauxMortRea : Taux de mortalité une fois en réanimation.
-	isVaccin : Booléen indiquant si oui ou non la population est vaccinée.
-	resistanceInfectionValuesByAge : Huit va-leurs flottantes correspondant aux huit classes d’âge représentées dans la simulation pour définir la résistance à la contamination après avoir été infecté une première fois.
-	maxResistanceInjectionValuesByAge : Huit valeurs flottantes correspondant aux huit classes d’âge représentées dans la simulation pour définir la résistance maximale à la con-tamination après avoir reçu deux doses de vaccin.
-	minResistanceInjectionValuesByAge : Huit valeurs flottantes correspondant aux huit classes d’âge représentées dans la simulation pour définir la résistance minimale à la con-tamination après avoir reçu deux doses de vaccin.
-	tableTauxHospitalisationByAge : Huit va-leurs flottantes correspondant aux huit classes d’âge représentées dans la simulation pour définir la probabilité d’hospitalisation.
-	histogrammeContamination : Onze valeurs flottantes correspondant aux onze jours de contamination, définissant le taux de conta-mination par jour.
-	pourcentAsymptomatique : Probabilité d’être asymptomatique.
-	tauxDeChanceDeMourirHospitalFull : Pro-babilité de mourir si les hôpitaux sont saturés.
-	tauxVaccination : Taux de vaccination de la population (actif si « isVaccin » est utilisé)
-	tauxContaDistanceDeux :Taux de contami-nation d’un humain sur un voisinage de Moore avec une distance de 2 mètres (cases). Ce facteur se multiplie au paramètre « histo-grammeContamination » afin d’établir un taux de contamination sur la distance deux.
-	tauxVaccinationRappel : Taux de vaccination pour la 3ème dose.
-	tauxDeProtectionHospVaccinByAge : Taux de protection de deux doses de vaccin vis-à-vis de l’hospitalisation.
-	tauxDeProtectionReaVaccinByAge : Taux de protection de deux doses de vaccin vis-à-vis de la réanimation.
-	tauxDeProtectionHospVaccinRappelByAge : Taux de protection d’une 3ème dose de vac-cin vis-à-vis de l’hospitalisation.
-	tauxDeProtectionReaVaccinRappelByAge : Taux de protection d’une 3ème dose de vac-cin vis-à-vis de la réanimation.
-	tauxDeProtectionHospInfectionByAge : Taux de protection d’une précédente infec-tion vis-à-vis de l’hospitalisation.
-	tauxDeProtectionReaInfectionByAge : Taux de protection d’une précédente infection vis-à-vis de la réanimation.
-	isMedicament : Booléen déterminant la pré-sence de traitement médicamenteux.
-	tauxProtectionReaMedicament : Taux de protection des médicaments vis-à-vis de la réanimation.
-	isMasqueTissu : Booléen déterminant l’utilisation de masques en tissus.
-	tauxProtectionMasqueTissu : Taux de protec-tion des masques en tissu.
-	isMasqueChir : Booléen déterminant l’utilisation de masques chirurgicaux.
-	tauxProtectionMasqueChir : Taux de protec-tion des masques chirurgicaux.
-	isMasqueFFP2 : Booléen déterminant l’utilisation de masques FFP2.
-	tauxProtectionMasqueFFP2 : Taux de pro-tection des masques FFP2.
-	isConfinement : Booléen activant la mise en place d’un confinement.
-	nbDeplacementReductionConfinement : Ré-duction du nombre de déplacements journa-liers lié au confinement.
-	nbLimiteDistanceMaxConfinement : Dis-tance maximale journalière possible lié au confinement.
-	isDeplacementLimites : Booléen activant la mise en place d’une limitation dans la dis-tance des déplacements.
-	nbDistanceMax : Distance maximale journa-lière possible liée à la limite des déplace-ments.
-	isGelHydroalcolique : Booléen déterminant l’utilisation du gel hydro-alcoolique.
-	tauxProtectionTransmissionGelHydro : Taux de protection de transmission de la maladie lié à l’utilisation du gel hydro-alcoolique.
-	isTestCovid : Booléen activant l’utilisation de test.
-	tauxDeDivisionAsymptomatique : Réduction du nombre d’asymptomatiques en circulation lié à l’utilisation des tests.
-	isCouvreFeu : Booléen activant la mise en place d’un couvre-feu.
-	nbDeplacementReductionCouvreFeu : Ré-duction du nombre de déplacements journa-liers lié au couvre-feu.
-	isSuperContaminateur : Booléen activant la présence d’humains super-contaminants.
-	nbDeplacementSuperContaminateur : Nombre de déplacements journaliers des su-per-contaminateurs.
-	probasCumulativesTrancheAge : Proportions cumulatives des individus de la population à étudier par tranches d’âge (0 à 10 ans, 10 – 20, 20 – 30 , 30 - 40 , 40 – 50 , 50 – 60, 60 – 70, 70 ans et +). 

## Expected Ouput : 
Le dossier expectedOutput contient les résultats supposés de l'exécution du Notebook Jupyter de base sur la métropole de Lyon avec 4 réplications. Vous pouvez comparer les résultats sur cela pour vous assurer d'avoir la répétabilité, avant de pouvoir faire vos propres expériences.
