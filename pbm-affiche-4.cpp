#include <stdexcept>
/** @file
 * Affichage d'une image PBM
 **/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param source le nom d'un fichier PBM
 **/
void affichePBM(string source)  {
    ifstream fichier;
    fichier.open(source);
    if (not fichier){
        cout << "erreur à l'ouverture" <<endl;
    }
    string type;
    fichier >> type;
    int largeur;
    fichier>> largeur;
    int hauteur;
    fichier >> hauteur;
    int pixel;
    for (int i =1; i<= largeur; i++){
        for (int j=1; j<= hauteur; j++){
            fichier >> pixel;
            if (pixel == 0) {
                cout << " " ;
            } else if (pixel == 1){
                cout << "@" ;
            }
        }
        cout<< endl;
    }
    fichier.close();
}

/** Echange le noir et le blanc dans une image PBM
 * @param source le nom du fichier PBM à lire
 * @param cible le nom du nouveau fichier PMB créé
 **/
void inversePBM(string source, string cible) {
    int nbColonnes, nbLignes; // Remove the extra line numbers
string ligne;
char val;

ifstream fichier1(source);
ofstream fichier2(cible);

if (not fichier1)
    throw runtime_error("Fichier non trouve: " + source);

if (not fichier2)
    throw runtime_error("Fichier non trouve: " + source);

    // Supression de la premiere ligne (un commentaire)
    getline(fichier1, ligne);

    // Lecture de l'entete
    fichier1 >> nbColonnes;
    fichier1 >> nbLignes;

    // Ecriture de l'entete
    fichier2 << "P1" << endl;
    fichier2 << nbColonnes << " " << nbLignes << endl;

    for(int i=0; i<nbLignes; i++) {
        for(int j=0; j<nbColonnes; j++) {
            fichier1 >> val;
            if (val == '0') {
                fichier2 << "1 ";
            } else {
               fichier2 << "0 ";
            }
        }
        fichier2 << endl;
    }
    fichier1.close();
    fichier2.close();
 }



int main(){
    cout << "Affichage du smiley " << endl;
    affichePBM("./images/smiley.pbm");
    cout << "Fabrication du smiley inversé (vérifiez que le nouveau fichier a été créé dans le dossier pbm/smiley-inverse.pbm" << endl;
    inversePBM("images/smiley.pbm","pbm/smiley-inverse.pbm");
    cout << "Affichage du smiley inversé" << endl;
    affichePBM("./pbm/smiley-inverse.pbm");
    return 0;
}

