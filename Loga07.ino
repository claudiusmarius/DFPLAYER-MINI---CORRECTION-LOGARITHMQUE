  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TRACE DE LA CORRECTION LOGARITHMIQUE D'UN SIGNAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Claude DUFOURMONT Le 21/03/2022
  // claude.dufourmont@laposte.net
  // Ma chaine YouTube : https://www.youtube.com/c/ClaudeDufourmont
  // Mon Github : https://github.com/claudiusmarius
  // Github associé à cette vidéo :...................
  // Mes pastebin associés à ce code : ...............
  // Ma page  Facebook : claude DUFOURMONT
  // Ce code a été créé pour montrer la possibilité d'une correction logaritmique d'une rampe en vue de son utilisation sur un DFPlayer Mini
  // Ce code est valable à l'identique pour une utilisation avec un arduino UNO, NANO, SEEEDUINO XIAO et ESP32
  // N'hesitez pas à me faire part de vos questions, remarques propositions, principalement depuis les commentaires de la vidéo YouTube associée
  // Ce code est libre d'accés et peut donc être utilisé et partagé, l'auteur souhaite toutefois que son origine reste tracée
  // vidéos associées à ce code :
  // ..........................
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 
  int a;                                                // Signal à corriger (typiquement le curseur d'un potentiomètre de volume)
  int aa;                                               // Signal à corriger modifié augmenté de 1 pour éviter de se retrouver avecle log d'un nombre < 1 (et donc un log négatif)
                                                    
  
  float LOG10aa;                                        // log10 du signal à corriger logiciellement
  float LOG10y;                                         // log10 du nombre 1023
  float ratio;                                          // Rapport entre le log10 de aa et le log10 de 1024 pour avoir un résultat entre 0 et 1
  float SignalCorrige;                                  // Signal sonore corrigé logarithmiquement dans la fourchette 0 - 1023 points
  
  byte volumeLevel;                                     // variable de volume sonore
 
  void setup() 
  {
  
  Serial.begin(9600);                                   // Initialisation du port série
   
  }

  void loop() 
  
  {
  
  for (a = 0; a<=500; a++)     // Ce signal est l'image d'un potentiomètre (c'est le curseur) de volume dont les 2 extrémités sont branchées sur l'alimentation (Vcc - GND)
                               // En principe son excursion va de 0 à 1023, je l'ai stoppé à 500 pour cette démo, le traceur série ne pouvant afficher que 500 simultanément sur un écran
  {
  aa = a+1;                                              // a, via aa est talonné à 1, les logs < 1 étant négatifs
  int y = 1024;
  LOG10y = log10 (y);
  LOG10aa = log10 (aa);
  ratio = log10 (aa) / log10 (y);
  SignalCorrige = ratio*1023;
  volumeLevel = map(SignalCorrige, 0, 1023, 0, 30);      // Conversion en 0 - 30 points pour être compatible avec la librairie du DFPlayer
  Serial.println (SignalCorrige) ;
  //Serial.println (volumeLevel) ;
  //Serial.println (LOG10aa) ; 
    
  }
   delay(10000);                                        // Tempo de 10 secondes avant une nouvelle boucle
  }
