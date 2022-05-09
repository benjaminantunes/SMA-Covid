#include "Lieu.hpp"
#include <ostream>
#include <iostream>

using namespace std;




// -------------------------------------------------------------------- //
// Lieu::Lieu:  Constructeur de Lieu                                    //
//                                                                      //
// En entrée:                                                           // 
//                                                                      //
//    inSimulationParams :                                              //
//       Objet contenant les paramètres du fichier de configuration     //
//                                                                      //
//                                                                      //
//    inRow :                                                           //
//       La ligne du Lieu  (Position X sur la carte)                    //
//                                                                      //
//    inColumn :                                                        //
//       La colonne du Lieu  (Position Y sur la carte)                  //
//                                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Un objet lieu                                                     //
// -------------------------------------------------------------------- //
Lieu::Lieu(int   inRow, 
           int   inColumn,
           float inTauxAugmentationContamination,
           float inTauxContamination
          )

{
   _pos                           = Position(inRow,inColumn);
   _symbol                        = Lieu::SYMBOL;
   _tauxAugmentationContamination = inTauxAugmentationContamination;
   _tauxContamination             = inTauxContamination;
   
}



// -------------------------------------------------------------------- //
// Lieu::to_string  Renvoi une représentation graphique du Lieu         //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Char : Signe pour représenter le lieu                             //
// -------------------------------------------------------------------- //

char Lieu::to_string()
{
   return _symbol;
}


// -------------------------------------------------------------------- //
// Lieu::getPosition  Retourne la position du lieu                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Position : La position du lieu                                    //
// -------------------------------------------------------------------- //

Position  Lieu::getPosition()
{
   return _pos;
}


// -------------------------------------------------------------------- //
// Lieu::getTauxAugmentationContamination                               //
//    Le lieu augmente les chances d'être contaminé par un autre humain //
//                                                                      //
// En entrée:                                                           // 
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Float : Le taux d'augmentation de la contamination par voisinage  //
// -------------------------------------------------------------------- //
float Lieu::getTauxAugmentationContamination()
{
   return _tauxAugmentationContamination;
}

// -------------------------------------------------------------------- //
// Lieu::getTauxContamination                                           //
//    Le Lieux a des chances de contaminer les individus                //
//    (virus sur poignet de porte, dans l'air, escaier, etc.)           //
//                                                                      //
// En entrée:                                                           // 
//    Pas d'entrée                                                      //
//                                                                      //
// En sortie:                                                           //
//                                                                      //
//    Float : Le taux de contamination du lieu                          //
// -------------------------------------------------------------------- //
float Lieu::getTauxContamination()
{
   return _tauxContamination;
}
