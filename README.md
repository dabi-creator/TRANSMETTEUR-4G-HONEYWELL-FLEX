# TRANSMETTEUR-4G-HONEYWELL-FLEX - "En cours de TEST"
Transmetteur 4G pour centrale HONEYWELL Flex

# Matériels nécessaire :

- Centrale Honeywell Flex version > 3.00
- 1 x Carte d'extension de sortie A071-00-01
- 1 x Carte WAVESHARE SIM7600-4G-HAT V1.0
- 1 x Carte Arduino ATMEGA2560
- 1 x Shield Arduino / SIM7600 / A071-00-01


# Réalisation & Installation :

1 - Réalisation du Shield Arduino / SIM7600 / A071-00-01

![image](https://user-images.githubusercontent.com/57842257/141687708-a3c436a0-fec5-4def-9851-39ef407e2c49.png)

2 - Impression 3D du support pour le Shield (à enficher à l'emplacement RF Portal en haut à droite de la centrale - Antenne 4G à l'horizontale)

3 - Installation et déclaration de la carte d'extension de sortie A071-00-01 dans la centrale Honeywell Flex

    Menu Paramètre 51.50 - Set to 1 = Enabled
    
 ![image](https://user-images.githubusercontent.com/57842257/141687645-be053fe3-7756-4b69-ae5b-1fec8430213d.png)


4 - Programmation de la centrale Honeywell Flex

    Menu Paramètres 53.1 / 53.2 / 53.3 / 53.5

![image](https://user-images.githubusercontent.com/57842257/141687429-884b2506-db3f-4f36-8aa9-9f176770c341.png)


5 - Programmation Arduino ATMEGA2560

    Modifier les 2 numéros de téléphone et codes d'accés associés
    
![image](https://user-images.githubusercontent.com/57842257/141687988-0e79ecff-63a3-4b0c-be2e-f365b6090ea8.png)


6 - Câblage & Essais

    Chaque borne du module de sorties A071 est à relier à une borne portant le même numéro au Shield (T1 = 1 Shield / T2 = 2 Shield ...)
    
    
    



