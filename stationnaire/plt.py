#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Nov 29 12:51:28 2023

@author: administrateur
"""

import numpy as np
import csv
import matplotlib.pyplot as plt
M = 5000
x_num = np.ones(M)
x_exac = np.ones(M)
# Spécifiez le chemin vers votre fichier CSV
chemin_fichier_csv = f'resultat_avec_M_{M}.csv'

# Ouvrir le fichier CSV en mode lecture
a = True 
with open(chemin_fichier_csv, 'r') as fichier_csv:
    
    # Créer un objet lecteur CSV
    lecteur_csv = csv.reader(fichier_csv)
    i = 0    # Lire et traiter chaque ligne du fichier CSV
    for ligne in lecteur_csv:
        if a :
            a = False
            continue
        # Faites quelque chose avec chaque ligne
      
        x_num[i] = float(ligne[0])
        x_exac[i] = float(ligne[1])
        i += 1 



x = np.linspace(0,4,5000)
plt.plot(x, x_num, '+b', label='x_num')
plt.plot(x, x_exac, 'r', linestyle='--', label='x_exac')
plt.legend()
plt.show()
