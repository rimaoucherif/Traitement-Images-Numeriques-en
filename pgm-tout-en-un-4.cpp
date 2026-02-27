#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

/// BEGIN ImageGris

/** Structure de donnees pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;
/// END ImageGris

/// BEGIN lirePGM

/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
ImageGris lirePGM(string source) {
    ifstream pgm;
    pgm.open(source);
    if (not pgm)
        throw runtime_error("Fichier non trouve: "+source);
    string type;
    pgm>> type;
    int largeur, hauteur;
    pgm>> largeur;
    pgm>> hauteur;
    int nblanc;
    pgm>> nblanc;
    ImageGris img;
    img= ImageGris(hauteur);
    for (int i =0; i < hauteur; i++){
        img[i] = vector<double>(largeur);
    }
    int pixel;
    for (int i =0; i< hauteur; i++){
        for (int j=0; j< largeur; j++){
            pgm >> pixel;
            img[i][j] = pixel;
        }
    }
    return img;
}


/// BEGIN ecrirePGM

/** Ecrit une image en teintes de gris dans un fichier PGM
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 **/

void ecrirePGM(ImageGris img, string cible) {
      ofstream pgm;
    pgm.open(cible);
    if (not pgm) {
        throw runtime_error("Fichier non trouve: "+cible);
    }

    pgm<<"P2"<<endl;
    pgm<<img[0].size()<<" "<<img.size()<<endl;
    pgm<<"255"<<endl;

    for (int i=0; i<img.size(); i++) {
        for (int j=0; j<img[0].size();j++) {
            pgm<<((int) img[i][j])<<endl;
        }
    } 
    pgm.close();  
}

/** Construit une image cliché d'une image en niveau de gris
 * @param img une image en niveau de gris
 * @return l'image cliché qui inverse les niveaux de gris
 **/

ImageGris inversePGM(ImageGris img) {
    ImageGris inverse(img.size(), vector<double>(img[0].size()));

    for (int i = 0; i < img.size(); i++) {
        for (int j = 0; j < img[0].size(); j++) {
            inverse[i][j] = 255 - img[i][j];
            if (inverse[i][j] < 0) {
                inverse[i][j] = 0;
            } else if (inverse[i][j] > 255) {
                inverse[i][j] = 255;
            }
        }
    }

    return inverse;
}
void lirePGMTest(){
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    ecrirePGM(lirePGM("images/brain.pgm"),  "pgm/brain.pgm");
    ecrirePGM(lirePGM("images/illusion.pgm"),  "pgm/illusion.pgm");
}

void inversePGMTest() {
    ImageGris imageOriginale;
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    imageOriginale = lirePGM("images/brain.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/brain-inverse.pgm");
    imageOriginale = lirePGM("images/illusion.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/illusion-inverse.pgm");
}

int main() {
    lirePGMTest();
    inversePGMTest();
    return 0;
}

