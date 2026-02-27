#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
using namespace std;

/** Structure de donnee pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;



/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl


/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};



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

/** Teste si deux images en teintes de gris sont égales modulo imprécision numérique
 * En cas de différence un message est affiché
 * @param a une image en teintes de gris
 * @param b une image en teintes de gris
 * @param precision un flottant positif: la précision souhaitée; typiquement 0.001
 * @return vrai si les images sont égales et faux sinon
 **/
bool ImageGrisEgal(ImageGris a, ImageGris b, float precision) {
    if (a.size() != b.size())  {
        cout << "Nombre de lignes différent" << endl;
        return false;
    }
    for (int i=0; i<a[0].size(); i++)
        if (a[0].size() != b[i].size()) {
            cout << "Nombre de colonnes différent" << endl;
            return false;
        }
    for (int i=0; i<a.size(); i++)
        for (int j=0; j<a[0].size(); j++)
            if (abs(a[i][j] - b[i][j]) > precision) {
                cout << "Valeur differentes en position " << i << "," << j
             << ": " << a[i][j] << " au lieu de " << b[i][j] << endl;
                return false;
            }
    return true;
}

/// BEGIN intensiteH

/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 **/

ImageGris intensiteH(ImageGris img) {
    ImageGris hintensite(img.size());

    for (int i = 0; i < img.size(); i++) {
        hintensite[i] = vector<double>(img[0].size());
    }

    for (int i = 1; i < img.size() - 1; i++) {
        for (int j = 1; j < img[0].size() - 1; j++) {
            hintensite[i][j] = img[i - 1][j - 1] + 2 * img[i][j - 1] + img[i + 1][j - 1] - img[i - 1][j + 1] - 2 * img[i][j + 1] - img[i + 1][j + 1];
        }
    }

    return hintensite;
}


ImageGris intensiteV(ImageGris img) {
    ImageGris vintensite(img.size());

    for (int i = 0; i < img.size(); i++) {
        vintensite[i] = vector<double>(img[0].size());
    }

    for (int i = 1; i < img.size() - 1; i++) {
        for (int j = 1; j < img[0].size() - 1; j++) {
            vintensite[i][j] = img[i - 1][j - 1] + 2 * img[i - 1][j] + img[i - 1][j + 1]
                               - img[i + 1][j - 1] - 2 * img[i + 1][j] - img[i + 1][j + 1];
        }
    }

    return vintensite;
}


ImageGris intensite(ImageGris img) {
    ImageGris VHintensite(img.size());

    for (int i = 0; i < img.size(); i++) {
        VHintensite[i] = vector<double>(img[0].size());
    }

    double h;
    double v;
    
    for (int i = 1; i < img.size() - 1; i++) {
        for (int j = 1; j < img[0].size() - 1; j++) {
            h = img[i - 1][j - 1] + 2 * img[i][j - 1] + img[i + 1][j - 1] - img[i - 1][j + 1] - 2 * img[i][j + 1] - img[i + 1][j + 1];
            v = img[i - 1][j - 1] + 2 * img[i - 1][j] + img[i - 1][j + 1] - img[i + 1][j - 1] - 2 * img[i + 1][j] - img[i + 1][j + 1];
            VHintensite[i][j] = sqrt(h * h + v * v);
        }
    }

    return VHintensite;
}




void testSobel() {
    CHECK( ImageGrisEgal(intensiteH(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -373.47, 227.507, 0},
                  {0, -22.1312, 323.866, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensiteV(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -15.1398, 150.501, 0},
                  {0, -9.0336, 273.023, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensite(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, 373.777, 272.782, 0},
                  {0, 23.9039, 423.593, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );

    cout << "Vérifier que les images obtenues dans 'sobel/' sont semblables à celles fournies dans 'sobel/correction/'" << endl;
    ecrirePGM(intensite(lirePGM("images/Willis.512.pgm" )), "sobel/Willis.512.pgm");
    ecrirePGM(intensite(lirePGM("images/Baboon.512.pgm" )), "sobel/Baboon.512.pgm");
    ecrirePGM(intensite(lirePGM("images/Billes.256.pgm" )), "sobel/Billes.256.pgm");
    ecrirePGM(intensite(lirePGM("images/Embryos.512.pgm")), "sobel/Embryos.512.pgm");
    ecrirePGM(intensite(lirePGM("images/House.256.pgm"  )), "sobel/House.256.pgm");
}



int main(){

    testSobel();
    return 0 ;
}
