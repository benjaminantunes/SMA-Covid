import csv
import os
import math


fileDeptSuperficie = open ("dataDept.csv")
fileDeptNum = open ("departementNum.csv") 
listeDeptSuperficie = list(csv.reader(fileDeptSuperficie))
listeDeptNum = list(csv.reader(fileDeptNum))
#print(listeDeptSuperficie)
for row in listeDeptSuperficie[1:]:
    #os.system("html2csv https://www.bien-dans-ma-ville.fr/departements/"+ row[0].lower()+ ".html -o ville" + row[0] + ".csv")
    #print(row)
    kmCarre = int(row[2].split("km")[0].replace(" ",""))
    ligne1 = "size||"+ str(int(math.sqrt(kmCarre) * 1000))
    ligne2 = "nbHumain||" + row[1].replace(" ","")
    ligne3 = "nbMalade||1000"
    ligne4 = "nbIteration||365"
    ligne5 = "nbPlaceHospital||1000000"
    ligne6 = "nbPlaceReanimation||1000000"
    ligne7 = "nbDeplacementJour||30"
    ligne8 = "probasCumulativesTrancheAge||0.177,0.296,0.411,0.535,0.667,0.793,0.905,1.0"
    ligne9 = "nbHopitaux||0"
    ligne10 = "tailleHopitauxMetreCarre||1500,800,600,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,200"
    ligne11 = "facteurTailleHopitaux||0"
    ligne12 = "nbSalleDeSport||0"
    ligne13 = "nbBoiteDeNuit||0"
    ligne14 = "nbMagasin||0"
    ligne15 = "nbRestaurant||0"
    ligne16 = "##"
    ligne17 = "##https://www.bien-dans-ma-ville.fr/classement-ville-nb-habitant-puy-de-dome/"
    ligne18 = "##Les 4 champs ci-dessous sont corrélés via l'indice de l'information"
    ligne19 = "tailleVille||"
    ligne20 = "nbHabitant||"
    ligne21 = "coordonneeX||"
    ligne22 = "coordonneeY||"

    f = open("ville"+row[0].replace(" ","")+".csv")
    listeVille = list(csv.reader(f))
    first = 1
    listTailleVille = []
    valeurCoordY = 0
    for rowVille in listeVille[10:]:
        if not first:
            ligne19 += ","
            ligne20 += ","
            ligne21 += ","
            ligne22 += ","
            
        kmCarreVille = int(rowVille[2].split("km")[0].replace(" ",""))
        ligne19 += str(int(math.sqrt(kmCarreVille) * 1000))
        listTailleVille.append(int(math.sqrt(kmCarreVille) * 1000))
        first = 0
        ligne20 += rowVille[1].replace(" ","")
        
        if first:
            ligne21 += "0"
            ligne22 += "0"
        else:
            somme = sum(listTailleVille)
            if(somme < int(math.sqrt(kmCarre) * 1000)):
                ligne21 += str(somme)
                ligne22 += str(valeurCoordY)
            else:
                valeurCoordY += max(listTailleVille)
                listTailleVille.clear()
                ligne21 += "0"
                ligne22 += str(valeurCoordY)
                
    numValue = ""
    for rowNum in listeDeptNum:
        if(row[0] == rowNum[2]):
            numValue = rowNum[1].replace("\"","")
            break
                
            
        
    ##File open et write
    f = open("configDpt"+numValue, "w")
    f.write(ligne1)
    f.write("\n")
    f.write(ligne2)
    f.write("\n")
    f.write(ligne3)
    f.write("\n")
    f.write(ligne4)
    f.write("\n")
    f.write(ligne5)
    f.write("\n")
    f.write(ligne6)
    f.write("\n")
    f.write(ligne7)
    f.write("\n")
    f.write(ligne8)
    f.write("\n")
    f.write(ligne9)
    f.write("\n")
    f.write(ligne10)
    f.write("\n")
    f.write(ligne11)
    f.write("\n")
    f.write(ligne12)
    f.write("\n")
    f.write(ligne13)
    f.write("\n")
    f.write(ligne14)
    f.write("\n")
    f.write(ligne15)
    f.write("\n")
    f.write(ligne16)
    f.write("\n")
    f.write(ligne17)
    f.write("\n")
    f.write(ligne18)
    f.write("\n")
    f.write(ligne19)
    f.write("\n")
    f.write(ligne20)
    f.write("\n")
    f.write(ligne21)
    f.write("\n")
    f.write(ligne22)
    f.close()
    


