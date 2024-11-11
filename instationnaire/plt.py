#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Dec 12 09:44:15 2023

@author: administrateur
"""

import numpy as np
import csv
import matplotlib.pyplot as plt
M = 5000
x_0= np.ones(M)
x_15 = np.ones(M)
x_300 = np.ones(M)
x_100 = np.ones(M)
x_599 = np.ones(M)
# Spécifiez le chemin vers votre fichier CSV
chemin_fichier_csv = 'resultat_avec_M_5000t_300_et_N_600.csv'

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
      
        
        x_300[i] = float(ligne[1])
        i += 1 


chemin_fichier_csv = 'resultat_avec_M_5000t_100_et_N_600.csv'

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
      
        
        x_100[i] = float(ligne[1])
        i += 1 
chemin_fichier_csv = 'resultat_avec_M_5000t_15_et_N_600.csv'

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
      
        
        x_15[i] = float(ligne[1])
        i += 1 

chemin_fichier_csv = 'resultat_avec_M_5000t_15_et_N_600.csv'

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
      
        
        x_15[i] = float(ligne[1])
        i += 1 

chemin_fichier_csv = 'resultat_avec_M_5000_t0et_N_600.csv'

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
        i += 1 

chemin_fichier_csv = 'resultat_avec_M_5000t_599_et_N_600.csv'

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
      
        
        x_599[i] = float(ligne[1])
        i += 1 
t = np.linspace(0,4,5000)
plt.plot(t, x_15 ,label = 'x_15')
plt.plot(t, x_100,label = 'x_100')
plt.plot(t,x_0,label = 'x_0')
plt.plot(t, x_300,label = 'x_300')
plt.plot(t,x_599,label = 'x_599')
plt.legend(loc ='upper right')
plt.show()