#include "header.hpp"


using namespace std;

typedef std::pair<int, float> pairs;
// comparateur personnalisé pour trier un pair vector par rapport à son second élément dans l'ordre décroissant
struct comp {
    bool operator()(const pairs& a, const pairs& b) {
        if (a.second != b.second) {
            return a.second > b.second;
        }
        return a.first > b.first;
    }
};

struct comp2 {
    bool operator()(const pairs& a, const pairs& b) {
        if (a.second != b.second) {
            return a.second < b.second;
        }
        return a.first > b.first;
    }
};



void Solution_P1(const std::vector<std::pair<int, int>>& liste_objets, int capacite_objets) {
    srand(time(NULL));
    vector<pair<int, float>> tab_rapport_benef;
    vector<pair<int, int>> tab_size;
    float rapport_benef{ 0.f }; // le rapport  prix/capacité
    int j{ 0 }; // l'indice de l'objet

    // étiquettage des objets en fonction du rapport prix/capacité
    
    for (auto itr = 0; itr != liste_objets.size(); ++itr) {
        tab_size.emplace_back(j, (float)liste_objets[itr].first);
        j++;
    }
    sort(tab_size.begin(), tab_size.end(), comp2());

    j = { 0 };

    for (auto itr = 0; itr != liste_objets.size(); ++itr) {
        rapport_benef = (float)liste_objets[itr].second / (float)liste_objets[itr].first;
        tab_rapport_benef.emplace_back(j, rapport_benef);
        j++;
    }
    // tri par ordre décroissant de leur rapport prix/capacité
    sort(tab_rapport_benef.begin(), tab_rapport_benef.end(), comp());
    for (auto itr = 0; itr != tab_rapport_benef.size(); ++itr) {
        cout << itr << " " << tab_rapport_benef[itr].first << " " << tab_rapport_benef[itr].second << endl;
    }
    vector<pair<int, int>> capacite_vehicule;

    int k{ 0 };
    int i{ 0 };
    int random;
    // Tant qu'il reste de la capacité suffisante dans le véhicule...
    while (capacite_objets > tab_size[i].second) {
        
        if (liste_objets[tab_rapport_benef[k].first].first > capacite_objets) {

            k++;
        }
        else {

            random = rand() % 2;
            cout << random << endl;
            if (random == 1) {

                tab_rapport_benef.emplace_back(tab_rapport_benef[k]);
                k++;
            }
            capacite_objets -= liste_objets[tab_rapport_benef[k].first].first;
            capacite_vehicule.emplace_back(liste_objets[tab_rapport_benef[k].first].first, liste_objets[tab_rapport_benef[k].first].second);
            k++;
        }
    }


    // Affichage des objets optimaux choisis
    cout << endl << "les objets choisis sont :" << endl;
    for (auto itr = 0; itr < capacite_vehicule.size(); ++itr) {
        
        
        cout << tab_rapport_benef[itr].first << " " << capacite_vehicule[itr].first << " " << capacite_vehicule[itr].second << endl;
    }
}


int main() {

    ifstream monFlux("5colis30capacite.txt");  //Ouverture d'un fichier en lecture
    pair<pair<int, int>, vector<pair<int, int>>> final_pair;


    if (monFlux)
    {
        //Tout est prêt pour la lecture.
        int nombre_capacite;
        monFlux >> nombre_capacite; //Lit un nombre à virgule depuis le fichier
        int nombre_objet_dispo;
        monFlux >> nombre_objet_dispo;    //Lit un mot depuis le fichier

        string ligne;
        vector<pair<int, int>> monVectorConsoCapa;
        int i = 1;
        int nombre_pair1;
        int nombre_pair2;
        while (getline(monFlux, ligne)) {

            monFlux >> nombre_pair1;
            monFlux >> nombre_pair1;
            monFlux >> nombre_pair2;

            monVectorConsoCapa.push_back(make_pair(nombre_pair1, nombre_pair2));
            i++;
        }
        cout << monVectorConsoCapa.size() << endl;
        for (auto itr = 0; itr != monVectorConsoCapa.size(); ++itr) {
            cout << itr << " " << monVectorConsoCapa[itr].first << " " << monVectorConsoCapa[itr].second << endl;
        }

        pair<pair<int, int>, vector<pair<int, int>>> final_pair;
        final_pair.first.first = nombre_capacite;
        final_pair.first.second = nombre_objet_dispo;
        final_pair.second = monVectorConsoCapa;

        Solution_P1(monVectorConsoCapa, nombre_capacite);
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
}