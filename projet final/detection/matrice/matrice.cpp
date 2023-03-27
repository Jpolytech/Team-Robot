void avance{
    if(haut == true){

        if(x % 2 == 0){
            while(y != 3){
                matrice[x][y] = 1;
                y += 1;
            tourner();
        } else{
            while(y != 0){
                matrice[x][y] = 1;
                y -= 1;
            }
            tourner();
        }
    } else{
        if(y % 2 == 0){
            while(x != 7){
                matrice[x][y] = 1;
                x += 1;
            }
            tourner();
        } else{
            while(x != 0){
                matrice[x][y] = 1;
                x -= 1;
            }
            tourner();
            }
        }
    }
}

void tourner{
    if(haut == true){
        x += 1;
    } else{
        y += 1;
    }

}

void poteau{
    matrice[x][y] = 2;
    arret();
}