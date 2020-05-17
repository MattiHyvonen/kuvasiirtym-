#include "siirtyma.h"
#include <iostream>


siirtyma::siirtyma() {
    lataaAsetukset("asetukset.conf");
    lataaAsetukset("asetukset2.conf");
    
    if(tallennetaan) {
        tavoiteFPS = fps_tulos;
    }

    else {
        tavoiteFPS = fps_esikatselu;
        T1 *= tavoiteFPS/fps_tulos;
        T2 *= tavoiteFPS/fps_tulos;
        marginaali = 0;
    }

    lataaKuvat();
    frame = 0;
    
    t.setPeriod_fps(tavoiteFPS);
    t.reset();
    t0.reset();
    
    suorita();
}


bool siirtyma::lataaKuvat() {
    kuva1.lataa(kuvatiedostot[0]);  //alkukuva
    kuva2.lataa(kuvatiedostot[1]);  //välikuva
    kuva3.lataa(kuvatiedostot[2]);  //loppukuva
    kuva4.lataa(kuvatiedostot[3]);  //loppukuva
    
    kartta1.lataa_16(karttatiedostot[0]);
    if(!kartta2.lataa_16(karttatiedostot[1]) )
        kartta2.asetaTyhjana(leveys, korkeus);
    if(!kartta3.lataa_16(karttatiedostot[2]) )
        kartta3.asetaTyhjana(leveys, korkeus);
    if(!kartta4.lataa_16(karttatiedostot[3]) )
        kartta4.asetaTyhjana(leveys, korkeus);
    kartta5.lataa_16(karttatiedostot[4]);
    kartta6.lataa_16(karttatiedostot[5]);
    
    tmp.asetaTyhjana(leveys, korkeus);
    tmp2.asetaTyhjana(leveys, korkeus);
    sekoitus.asetaTyhjana(leveys, korkeus);
    sekoitus2.asetaTyhjana(leveys, korkeus);
    tulos.asetaTyhjana(leveys, korkeus);
}


void siirtyma::kerroAjat() {
    //kulunut aika sekunteina
    float t_s = t0.getTime();
    float fps = (float)frame / t_s;
    float eta = (T2-frame) / fps;
    
    std::cout << "frame " << frame << " / " << T2 << "\n";
    std::cout << "fps: " << fps << "\n";

    std::cout << "kestää vielä noin ";
    
    if(eta < 60)
        std::cout << (int)eta << " s\n";
    else {
        int tunnit = eta/3600;
        int minuutit = (eta - tunnit*3600)/60;
        if(tunnit > 0)
            std::cout << tunnit << " h ";
        std::cout << minuutit << " min\n";
    }
}
    
    
std::string siirtyma::luoTiedostonimi() {
    static int i = 0;
    std::string tulos = "data/frames/frame" + std::to_string(i) + ".jpg";
    i++;
    return tulos;
}
    
    
void siirtyma::suorita() {
    ikkuna& I = haeIkkuna();
    I.piirra(kuva1);
    I.paivita();
    
    //tallennetaan alkukuvaa marginaalin verran
    for(int i=0; i<marginaali; i++) {
        std::cout << "tallennetaan kuva " << i << "/" << marginaali << "\n";
        kuva1.tallenna(luoTiedostonimi() );
    }
    
    do{
        if(frame < T1) {
            //0...1
            float f = ((float)frame) / T1;
            float d1 = (1-f) * 0.02 + 0.04;
            float s1 = f * 0.025;
            
            piirraKuvaan(tmp, SYRJAYTYS, d1, kuva3, kartta1);

            for(int i=0; i<5; i++) {
                piirraKuvaan(tmp2, SYRJAYTYS, d1, tmp, kartta1);
                piirraKuvaan(tmp, SYRJAYTYS, d1, tmp2, kartta1);
            }
            
            piirraKuvaan(tmp2, SEKOITUS_A, s1, kuva1, tmp, tmp);
			
			piirraKuvaan(tulos, SEKOITUS, f, kuva1, tmp2);
            
        }
        else if (frame<T2) {
            //0...1
            float f = ((float)frame-T1) / (T2-T1);

            float d1 = pow(1-f, 2) * 0.04;
            
            float s1 = pow(f, 5) + 0.025;
            
            piirraKuvaan(tmp, SYRJAYTYS, d1, kuva3, kartta1);

            for(int i=0; i<5; i++) {
                piirraKuvaan(tmp2, SYRJAYTYS, d1, tmp, kartta1);
                piirraKuvaan(tmp, SYRJAYTYS, d1, tmp2, kartta1);
            }
            
            
            piirraKuvaan(tmp2, SEKOITUS_A, s1, kuva1, tmp, tmp);			
			piirraKuvaan(tulos, tmp2);
			
        }
        else{
            piirraKuvaan(tulos, kuva3);
        }
    
        I.piirra(tulos);
        
        if(frame < T2) {
            //tallennetaan ja näytetään tulos
            if(tallennetaan)
                tulos.tallenna(luoTiedostonimi() );                
            kerroAjat();

        }
        
        else if (frame == T2) {
            //tallennetaan alkukuvaa marginaalin verran
            for(int i=0; i<marginaali; i++) {
                std::cout << "tallennetaan kuva " << i << "/" << marginaali << "\n";
                kuva3.tallenna(luoTiedostonimi() );
            }
            std::cout << "Siirtymä päättyi\n";
        }

        if(!tallennetaan)
            t.sleep();

        frame++;
    }
    //Jos tallennetaan, lopetetaan ohjelma heti kun siirtymä päättyy
    //Jos ei tallenneta, odotetaan että käyttäjä sulkee ohjelman
    while(I.paivita() && (frame <= T2 || tallennetaan == false) );
}    
    
