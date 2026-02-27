#include <stdexcept>
/** @file
 * Lecture et ecriture d'images binaires au format PBM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

/// BEGIN ImageNB
/** Structure de données pour représenter une image binaire **/
typedef vector<vector<int> > ImageNB;
/// END ImageNB

/// BEGIN lirePBM

/** Construire une image binaire depuis un fichier PBM
 * @param source le nom d'un fichier PBM
 * @return une image binaire (0/1)
 **/
ImageNB lirePBM(string source) {
    ifstream PBM;
    PBM.open(source);
    if (not PBM) {
        throw runtime_error("Fichier non trouve: " + source);
    }
    string type;
    PBM >> type;
    int largeur;
    PBM >> largeur;
    int hauteur;
    PBM >> hauteur;
    int pixel;

    // Resize the 2D tableau
    ImageNB img(hauteur, vector<int>(largeur));
    
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            PBM >> pixel;
            img[i][j] = pixel;
        }
    }

    PBM.close();
    return img;
}


/// BEGIN ecrirePBM

/** Ecrit une image binaire dans un fichier PBM
 * @param img une image binaire (0/1)
 * @param cible le nom d'un fichier PBM
 **/
void ecrirePBM(ImageNB img, string cible) {
     ofstream fichier;
    fichier.open(cible);
    if (not fichier) {
        throw runtime_error("Fichier non trouve: "+cible);
    }
    fichier<< "P1"<< endl;
    fichier<< img[0].size() << " " << img.size() << endl;
    for (int i = 0; i < img.size(); i++){
    for(int j = 0; j < img[0].size(); j++){
    fichier<< img[i][j] << endl;
}
    }
    fichier.close();
}




/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param img une image binaire (0/1)
 **/
void affichePBM(ImageNB img) {
    for (int i=0;i<img.size();i++) {
    for(int j=0; j<img[0].size(); j++) {
    if (img[i][j]==1) {
        cout<<"@"<<" ";
    }else{
        cout<<" "<<" ";
    }
    }
        cout<<endl;
    }
}


/// BEGIN inversePBM

/** Echange le noir et le blanc dans une image PBM
 * @param img une image binaire (0/1)
 * @return l'image où le blanc et le noir ont été inversés
 **/
ImageNB inversePBM(ImageNB img) {
    for (int i = 0; i < img.size(); i++) {
        for (int j = 0; j < img[0].size(); j++) {
            if (img[i][j] == 0) {
                img[i][j] = 1;
            } else if (img[i][j] == 1) {
                img[i][j] = 0;
            }
        }
    }
    return img;
}



void testLirePBM() {
    cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
    ecrirePBM(lirePBM("./images/smiley.pbm"),  "./pbm/smiley.pbm");
    ecrirePBM(lirePBM("./images/cercle.pbm"),  "./pbm/cercle.pbm");
    ecrirePBM(lirePBM("./images/code.pbm"), "./pbm/code.pbm");
    ecrirePBM(lirePBM("./images/damier.pbm"), "./pbm/damier.pbm");
}

int main() {
    testLirePBM();
    ImageNB picture, inverse;
    picture = lirePBM("./images/smiley.pbm");
        cout << "l’image normale est :" << endl;
    affichePBM(picture);
        cout << "l’image inversee :) :" << endl;
    inverse = inversePBM(picture);
        affichePBM(inverse);
    return 0;
    
}

