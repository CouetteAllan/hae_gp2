#pragma once

/* Version C uniquement
struct Toto
{
	float x = 0.8f;
};*/

class D {

};


class Toto : D{
public:
	float x = 0.0f;
};

template<typename MaClasse>
class Array{
	MaClasse* ptr = nullptr;
};

typedef Array<float> A;
typedef Array<int> B;
typedef Array<double> C;