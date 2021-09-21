// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Toto.h"

namespace GP2 {

}

/*int main0()
{
    std::cout << "Hello World!\n";
	printf("0\n");

	int zero = 0;
	
	printf("%i\n",zero);


	printf("%.1f\n", 0.5);

	printf("%s\n", "toto");

	printf("%lli", 123456789123456789);

	//std::cout << "123456789123456789" << std::endl;
}*/


int main()
{
	printf("0\n");
	//allocation statique,
	//l'instance est sur la pile / stack

	Toto tStatic;

	printf("%.1f", tStatic.x);

	//garde pour plus tard
	//allocation dynamique
	Toto*tDynamic = new Toto();

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
