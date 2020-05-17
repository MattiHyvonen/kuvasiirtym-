#pragma once
#include "ikkuna.h"
#include "shader.h"
#include "kuva.h"

#include <string>
#include <map>

const int EI_EFEKTIA = 0;
const int SEKOITUS = 1;
const int SYRJAYTYS = 2;
const int SEKOITUS_A = 3;
const int SYRJAYTYS_R = 4;
const int OFFSET = 5;
const int SEKOITUS_VALO = 6;

class kuvanPiirtaja{
    std::map<int, shader> shaderit;
    
public:
    kuvanPiirtaja();
    
    //Piirrä toinen kuva ensimmäiseen (suora kopiointi)
    bool piirraKuvaan(kuva& kohde, const kuva& lahde);
    
    //Piirrä kohteeseen annetulla efektillä ja kuvilla
    bool piirraKuvaan(  kuva& kohde, 
                        int efekti = EI_EFEKTIA, 
                        float maara = 0.5,
                        const kuva& lahde1 = kuva(),
                        const kuva& lahde2 = kuva(),
                        const kuva& lahde3 = kuva(),
                        const kuva& lahde4 = kuva(),
                        const kuva& lahde5 = kuva()
                     );
};
