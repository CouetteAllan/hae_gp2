// ConsoleApplication3.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>


struct Vec4 {
    float x = 0;
    float y = 0;
    float z = 0;
    float w = 0;

    /*void Add(Vec4* vector) {
        x += vector->x;
        y += vector->y;
        z += vector->z;
        w += vector->w;
    };*/

    Vec4 add(Vec4 v) {
        Vec4 res;
        res.x = x + v.x;
        res.y = y + v.y;
        res.z = z + v.z;
        res.w = w + v.w;
        return res;
    };

    void Incr(float n) {
        x += n;
        y += n;
        z += n;
        w += n;
    };

    void Div(Vec4* vector) {
        x /= vector->x;
        y /= vector->y;
        z /= vector->z;
        w /= vector->w;
    };
    
    void Mult(Vec4* vector) {
        x *= vector->x;
        y *= vector->y;
        z *= vector->z;
        w *= vector->w;
    };
};

struct Array {
    //int borne max ?
    //remplir ce tableau
};

int main()
{
    /*int tab[] = { 0,1,2,3 };

    int* c = &tab[0];

    *c = 0;

    //printf("%d\n",*c++); //incrémente c et prend le contenu
    //*c => pile
    //afficher c 
    //incrementer la valeur
    //incremente c et prend le contenu

    //printf("%d\n",(*c)++); // prend le contenu de c et incremente 

    //printf("%d\n", *++c); // incremente c et prend le contenu 
    //1 ?

    //printf("%d\n", ++*c); //prend le contenu de c et incremente le */

    /*Vec4 toto;

    toto.x = 42;
    toto.y = 67;
    toto.z = 7;
    toto.w = 18;

    


    //toto->Incr(5);


    Vec4 tata;
    tata.x = 58;
    tata.y = 33;
    tata.z = 93;
    tata.w = 82;
    
    Vec4 res = toto.add(tata);

    printf("%.0f %.0f %.0f %.0f\n", res.x,res.y,res.z,res.w);

    tata->Mult(toto);

    printf("%.2f %.2f %.2f %.2f\n", tata->x, tata->y, tata->z, tata->w);*/

    Array tableau;
    return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
