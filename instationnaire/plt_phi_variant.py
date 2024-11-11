#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Dec 12 09:54:42 2023

@author: administrateur
"""

import numpy as np
import csv
import matplotlib.pyplot as plt
M = 600

x_0= np.ones(M)
x_1500 = np.ones(M)
x_3000 = np.ones(M)

# Spécifiez le chemin vers votre fichier CSV
chemin_fichier_csv = 'resultat_avec_M_5000_N_600et_phi_variant.csv'

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
      
        
        x_0[i] = float(ligne[1])
        x_1500[i] = float(ligne[2])
        x_3000[i] = float(ligne[3])
        i += 1 
        
t = np.linspace(0, 300,600)
plt.plot(t, x_1500 ,label = 'x_1500')
plt.plot(t, x_3000,label = 'x_3000')
plt.plot(t,x_0,label = 'x_0')
plt.legend()