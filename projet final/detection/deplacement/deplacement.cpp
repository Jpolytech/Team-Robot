void depart{
    led.switchAmber();
    if(/*bouttonHaut*/){
        led.switchGreen();
        /*timer 2 second*/
        led.turnedOff();
        haut = true;
    } else if(/*bouttonDroite*/){
        led.switchRed();
        /*timer 2 second*/
        led.turnedOff();
    }
    
    void enCours{
        for(int i = 0; i != 4; i++){
            for(int j = 0; j != 8; j++){

            }
        }
    }
    void arret{

    }
}