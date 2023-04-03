enum class Etat {
    CHOIX, D_INIT, D_DROITE, D_HAUT, D_POTEAU, D_REHAUT, D_AUCUN,
    TRANSMISSION};(

    int main() {
       auto etat = Etat::CHOIX;

       while(true){
        switch(etat){
            case(Etat::CHOIX):
                //faire choix
                

            case(Etat::D_INIT):
                //Initialisation du mode detection
                led.switchAmber();
            
            case(Etat::D_DROITE):
                //Robot est dans l'orientation droite
                led.switchRed();
                //timer 2 sec
                //routine droite
            
            case(Etat:: D_HAUT):
                //Robot est dans l'orientation haut
                //timer 2 secondes
                timer.startTimer(2000);
                led.switchGreen();
                timer.stopTimer();
                //routine haut

            case(Etat::D_POTEAU):
                //Poteau detecte
                //robot s'arrete
                for(i = 0; i < 3; i++){
                    timer.startTimer(300);
                    //son aigu
                    timer.stopTimer();
                    //son aigu arret
                    timer.startTimer(300);
                    timer.stopTimer();
                }
                //son aigu 3 fois 300ms
                while(true){
                    timer.startTimer(500);
                    led.switchRed();
                    timer.stopTimer();
                    led.turnedOff();
                }
                //lumiere rouge 2Hz
                }
                led.switchRed();
            case(Etat::D_REHAUT):
                //Apres la detection du poteau le robot est place a l'emplacement du poteau dans l'orientation haut

            case(Etat::D_AUCUN):
                //Aucun poteau detecte
                //robot s'arrete
                //son grave 2 secondes
                while(true){
                    timer.startTimer(500);
                    led.switchRed();
                    timer.stopTimer();
                    led.turnedOff();
                }

            case(Etat::TRANSMISSION):
                //robot en mode transmission
       }
    }