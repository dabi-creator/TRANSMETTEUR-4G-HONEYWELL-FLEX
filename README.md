# TRANSMETTEUR-4G-HONEYWELL-FLEX - "En cours de TEST"
Transmetteur 4G pour centrale HONEYWELL Flex

# Matériels nécessaire :

- Centrale Honeywell Flex version > 3.00
- 1 x Carte d'extension de sortie A071-00-01
- 1 x Carte WAVESHARE SIM7600-4G-HAT V1.0
- 1 x Carte Arduino ATMEGA2560
- 1 x Shield Arduino / SIM7600 / A071-00-01


# Réalisation & Installation :

1 - Réalisation du Shield Arduino / SIM7600 / A071-00-01 (Fabriquée chez JLCPCB pour moins de 10 € livraison comprise)

![image](https://user-images.githubusercontent.com/57842257/141687708-a3c436a0-fec5-4def-9851-39ef407e2c49.png)

2 - Impression 3D du support pour le Shield (à enficher à l'emplacement RF Portal en haut à droite de la centrale - Antenne 4G à l'horizontale)

![image](https://user-images.githubusercontent.com/57842257/141688253-6e281d73-d0ca-459d-a255-bd9a16e2dcf5.png)

3 - Installation et déclaration de la carte d'extension de sortie A071-00-01 dans la centrale Honeywell Flex

    Menu Paramètre 51.50 - Set to 1 = Enabled
    
 ![image](https://user-images.githubusercontent.com/57842257/141687645-be053fe3-7756-4b69-ae5b-1fec8430213d.png)
 
 ![image](https://user-images.githubusercontent.com/57842257/141688588-8f89a4fc-9fc9-49ec-b857-941ad92c1872.png)

4 - Programmation de la centrale Honeywell Flex

    Menu Paramètres 53.1 / 53.2 / 53.3 / 53.5

![image](https://user-images.githubusercontent.com/57842257/141687429-884b2506-db3f-4f36-8aa9-9f176770c341.png)


5 - Programmation Arduino ATMEGA2560

    Modifier les 2 numéros de téléphone et codes d'accés associés
    
![image](https://user-images.githubusercontent.com/57842257/141687988-0e79ecff-63a3-4b0c-be2e-f365b6090ea8.png)

6 - Configuration de la carte SIM7600

    Vitesse de tranfert à initialiser 
    AT+IPREX=19200

    Pour vérifier la configuration
    AT+IPREX?
    
![image](https://user-images.githubusercontent.com/57842257/141689407-980ba255-a03b-4cf3-bc65-ee843ff39316.png)


![image](https://user-images.githubusercontent.com/57842257/141689257-3392ef55-a25d-40b7-bd51-9b658ca89b49.png)



6 - Câblage & Essais

    Les entrées :
        Carte A071 - T1 = Shield Borne 1 => MES PARTIELLE
        Carte A071 - T2 = Shield Borne 2 => MES TOTALE
        Carte A071 - T3 = Shield Borne 3 => AUTOPROTECTION
        Carte A071 - T4 = Shield Borne 4 => MHS
        Carte A071 - T5 = Shield Borne 5 => DEFAUT SYSTEME
        Carte A071 - T6 = Shield Borne 6 => DEFAUT SECTEUR
        Carte A071 - T7 = Shield Borne 7 => INTRUSION
        Carte A071 - T8 = Shield Borne 8 => INCENDIE
        
        Shield Borne G => GND 0V
        Shield Borne +12 => +12V
        
        Shield Borne P = Borne Zone 7 sur la carte mère centrale Flex
        Shield Borne T = Borne Zone 8 sur la carte mère centrale Flex
        
        Menu Paramètres 52.x.x
        
 ![image](https://user-images.githubusercontent.com/57842257/141688324-756b3b22-df61-4497-862c-ab82ee2b9c91.png)
 
 ![image](https://user-images.githubusercontent.com/57842257/141688424-576c1e89-8f6b-4707-b142-981de36f6059.png)


    
    



