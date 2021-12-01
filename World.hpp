#include <string>
#include <map>
#include <fstream>
#include "RandMT.hpp"
#include <vector>
#include "Human.hpp"
using namespace std;

class World{
    private:
        int size;

        // Le type map serait il necessaire ici ? Je ne pense pas.
        // Python : _map: Dict[int, Dict[int,Agent]] = None
        // Problème pour la taille dynamique de la map : Agent *** _map sera mieux, je ferai ça
        Human *** carte;
        
	float taux_contamination_voisin;
	
	int nbPlaceHospital;
	int nbPlaceReanimation;
	
	// On considère ici le taux de mortalité réel, en supposant qu'on a deux fois plus de chance d'avoir été en réanimation (50% des gens en réa meurent) et deux fois plus de chance d'avoir été hospitalisé (50% de personnes hospitalisés vont en réa)
	// Ces chiffres sont purement arbitraires, à mettre en param
	float table_taux_mortalite_by_age_by_10[8] = {0, 0.2, 0.2, 0.4, 1.3, 3.6, 8, 14.8};
	//float table_taux_reanimation_by_age_by_10[9] = {0, 0.4, 0.4, 0.4, 0.8, 2.6, 7.2, 16, 29.6};
	//float table_taux_hospitalisation_by_age_by_10[9] = {0, 0.8, 0.8, 0.8, 1.6, 5.2, 14.4, 32, 59.2};
	//float table_taux_reanimation_by_age_by_10[9];
	float table_taux_hospitalisation_by_age_by_10[8];

        //Position humansPosition[80] = NULL;
        vector<Position *> humansPosition;
        bool log = false;
        fstream logfile;
        int iteration = 0;

        map<string, int> stats;

        static const char SYMBOL_EMPTY = '.';
        static constexpr float MAX_HUMANS = 0.8;
        
        int nbNouveauxCas = 0;
        int nbPersonneHospital = 0 ;
        int nbPersonneReanimation = 0;
        int nbNouveauxHospitalisation = 0;
        int nbNouveauxReanimation = 0;
        int nbMorts = 0;
        int timeline_hospitalisation_21_11_2021[642];
        int timeline_reanimation_21_11_2021[642];


    public:
        World(int,float,int,int,int,bool);
        //Pour le __exit__
        ~World();
        void writeLog(string);
        static void pause();
        void display();
        void updateStats(string, RandMT*);
        void displayStats();
        bool isValid(int,int);
        bool isHuman(int,int);
        bool isEmpty(int,int);
        void addAgent(string,int,float, RandMT* ,int sicks = 0);
        void initialize(int, RandMT*, int sicks = 0);
        map<string,vector<Position*>> vision (int,int,int);
        void contamination(int,int,RandMT*, int, int);
        void humanGoFromTo(int,int,int,int, RandMT*, bool die = false);
        Position * moveHuman(int,int, RandMT*);
        void nextIteration(RandMT*);
        void startSimulation(int, RandMT*);

};
