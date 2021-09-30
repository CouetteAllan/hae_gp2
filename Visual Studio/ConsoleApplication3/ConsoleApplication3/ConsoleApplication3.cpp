// ConsoleApplication3.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "IntArray.hpp"


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
    
    void Incr(Vec4 v) {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;

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



static int monObjet = 33;

class B {
public:
    float cthullu = 0;
};

class A : public B {

};

int Strlen(const char* chaine) {
    int idx = 0;
    while (chaine[idx] != 0) {
        idx++;
    }

    return idx;
};


int Countc(const char* maChaine, char c) {
    //renvoie le nombre d'occurence de c dans maChaine;
    int nbr = 0;
    int size = Strlen(maChaine);

    for (int i = 0; i < size; i++)
    {
        if (maChaine[i] == c)
            nbr++;
    }

    return nbr;
}

void Strcpy(const char* source, char* destination) {
    for (size_t i = 0; i < Strlen(source); i++)
    {
        destination[i] = source[i];
    }
}


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

    char str1[20] = "Banane";
    char str2[20] = "";

    Strcpy(str1, str2);

    printf("%s\n", str2);


}

