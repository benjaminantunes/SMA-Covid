#pragma once


#include "Position.hpp"
#include "RandMT.hpp"
#include "SimulationParams.hpp"

extern RandMT * randmt;

class Lieu 
{
   private:
      
      static const char SYMBOL = 'L';

      // On a plus de chance d'etre contaminer avec le voisinage, mais aussi le lieu peut nous contaminer (covid sur les murs).
      float    _tauxAugmentationContamination;
      float    _tauxContamination;
      char     _symbol;
      Position _pos;

   public:
 
      Lieu(int,int,float,float);
      
      float     getTauxAugmentationContamination();
      float     getTauxContamination();
      char      to_string();
      Position  getPosition();


};
