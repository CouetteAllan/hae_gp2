// ConsoleApplication3.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>


struct Vec {
    float x = 0;
    float y = 0;
    float z = 0;
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

    //Vec toto;
    Vec* toto = new Vec();

    toto->y = 67;//(*toto).y = 67;
    (*toto).x = 42;
    toto->z = 7;

    printf("%.1f %.1f %.1f", toto->x, toto->y, toto->z);
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
