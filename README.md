# SMA-Covid
Benjamin Antunes, doctorant au Limos.

Vous êtes sur le repository du projet de modèle reproductible de simulation Covid 19.

Articles références : XXXX

Ce modèle est développé en C++ pour les performances. Il est parallélisé en SPMD (plusieurs simulations tourne simultanéments).
Vous serz donc limité par votre nombre de coeurs de calcul.

Description des fichiers : 

Les fichiers .cpp et . hpp correspondent au code du modèle. Vous n'avez pas besoin d'y toucher (mais vous pouvez).

Le fichier makefile permet de compiler correctement le projet.

Les fichiers "mts10p9N0000X" sont des statuts du générateur de nombre pseudo-aléatoire Mersenne Twister. Ils sont espacés de 2 Milliard de tirages. Ces 30 fichiers permettent donc de lancer 30 réplications indépendantes de simulations, qui doivent utiliser au maximum 2 milliard de nombre aléatoire. Si vos contraintes vous demande de faire plus de réplication ou plus de tirage par simulation, alors vous devrez utiliser/créer vos propres statuts de MT. Attention à respecter la norme de nommage en place. Pour en savoir plus sur la parallélisation de code utlisant des générateurs de nombres pseudo-aléatoire, veuillez vous référer à cette article : Hill 2018 ... 

Le fichier bash "ReplicationSimulation.sh" permet de lancer des simulations.

Le notebook Jupyter "SMA Covid.ipynb" permet de lancer très facilement vos expériences et récupérer vos résultats.

Les fichiers de configuration "configVille" et "configMesure" permettent de définir des configurations pour des villes/pays/territoires, et de paramétrer les différents éléments de la maladie, ainsi que les mesures sanitaires en place.


Prise en main :

Pour prendre en main le modèle, vous devez simplement lancer le notebook jupyter via la commande "jupyter notebook" dans un terminal, ou autre moyen de votre choix.

Vous pouvez executer toutes les cellules.
La commande !make va permettre de compiler le programme.
La commande !./replicationSimulation configParis.txt configLyon.txt configNoVaccin.txt configClermont.txt 10 est à faire évoluer !
Vous pouvez mettre vos propres fichiers de configurations de ville et de mesures que vous avez créé en suivant le format déjà présent. Vous pouvez au départ essayer le modèle avec les configurations existantes et comparer vos résultats avec ceux déjà obtenu, afin de tester la répétabilité. Si vos résultats sont différents, contactez nous à l'adresse benjamin.antunes@uca.fr (Nous pourrons étudier les causes de non répétabilité, et voir la reproductibilité).
Cette commande peut prendre un certain temps. Elle va lancer le code C++ avec N simulation pour chaque ville que vous avez choisi avec votre fichier de configuration.
Par exemple, la ligne : 
!./replicationSimulation configParis.txt configLyon.txt configNoVaccin.txt 10
Va lancer 10 réplications de la simuation sur Paris avec la configNoVaccin, 10 réplications sur Lyon et 10 réplications sur Clermont.
Il y aura donc 30 réplications en tout (30 processus de lancés en parallèle).

La cellule d'en dessous est également à modifier selon ce que vous avez entré au dessus : Vous devez modifier NB_REPLICATION et listVille selon ce que vous avez utilisé dans la commande d'avant.

Le fonctionnement est le suivant : Le code va générer des fichiers de  log pour chaque simulation que vous avez lancé. La dernière cellule va utiliser ces logs afin de générer des statistiques et des figures pour chaque simulation, et les sotcker dans le dossier dans lequel le notebook a été lancé. Vous pourrez ensuite établir vos propres conclusion sur l'impact des mesures sanitaires sur l'épidémie par exemple.

A noter : Dans des villes de faible densité, il est normal que l'épidémie ne démarre pas! Les cluster de l'épidémie de covid 19 n'ont jamais été les campagnes profondes du Cantal. Dans des villes comme Paris, 1 seul patient zéro peut permettre de lancer une épidémie globale. Si le patient zéro se trouve dans un endroit peu densément peuplé, alors l'épidémie n'existe pas.


Les paramètres : 
Ville : 
-	size : Taille de la carte.
-	nbHumain : Nombre d’humains dans la simu-lation.
-	nbMalade : Nombre de malades initial dans la simulation.
-	nbIteration : Nombre d’itérations de la simu-lation correspondant au nombre de jours.
-	nbPlaceHospital : Places disponibles dans les hôpitaux.
-	nbPlaceReanimation : Places disponibles en réanimation.

Config : 
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


