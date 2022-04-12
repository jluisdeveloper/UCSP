from scipy import *
import numpy as np
import os
import wave
import copy
import random
import sys

def ADA_FFT(file):

    audioDATA = wave.open(file, 'r')

    signal = audioDATA.readframes(-1)
    signal = np.fromstring(signal, 'Int16') 
    
    fps = audioDATA.getframerate()
    fragments = []
    FFTs = []
    golbalPromDistance = 0.0
    count = 0.0

    for i in range(1, len(signal)-10001, 10000): # fragmentacion de la senhal segun la longituf
        sum = 0
        for j in signal[i:i+10000]:
            if j > 0:
                sum += j
        if sum > 0:
            fragments.extend([[sum, signal[i:i+10000]]])

    fragments.sort(reverse=True) # Se ordena los datos mas "ruidosos"

    for i in range(5): # los 5 fragmentos mas "ruidosos"
        if i < len(fragments): # si esta presente entonces
            FFTnew = []
            FFTs.append(fft(fragments[i][1])) # calculamos la FFTs 
            FFTs[i] = abs(FFTs[i]) 
            

            # TESTING 
            # aux = 400.0/fps
            # print( np.mean( FFTs[i][:int(aux * 10000)] )*1.6 )
            # print( (400.0 / 22050)*10000 )

            FFTavg = np.mean(FFTs[i][:int(400.0/fps * 10000)])*1.6 # (sacamos los de intensidad media que van de 0-400Hz)*1.6
            
            for ind, val in enumerate(FFTs[i][:int(400.0/fps * 10000)]): # eliminamos los picos mas pronunciados de FFTavg
                if val < FFTavg:
                    FFTnew.append(0)
                else:
                    FFTnew.append(val)

            maxes = []
            for i in range(0, len(FFTnew)): # buscamos los maximos locales
                if i+6<len(FFTnew):
                    if FFTnew[i]<FFTnew[i+1] and FFTnew[i+1]>FFTnew[i+2]:
                        maxes.append(i+1)

            maxesNew = copy.copy(maxes) # eliminamos los maximos duplicados
            for i in range(len(maxes)-1):
                if maxes[i+1]-maxes[i]<9:
                    maxesNew.remove(maxes[i+1])

            avgDistance=0.0
            if (len(maxesNew) > 1): # calculamos las distancias entre los armonicos (decibeles?)(tono de voz si es aguda o grave) para cada fragmento
                count += 1
                for i in range(len(maxesNew)-1):
                    avgDistance += maxesNew[i+1]-maxesNew[i]
                avgDistance /= float(len(maxesNew)-1)
                golbalPromDistance += avgDistance

    if count > 0:
        golbalPromDistance /= float(count) # calculamos las distancias de todos los fragmentos restantes

    if golbalPromDistance < 25.5: # determinamos si la voz es de mujer o de hombre (mooz de dota2 no cuenta xD :v ese rompe todo xD)
        print("Macho alfa garganta de vikingo con barba y pelo en pecho")
    else:
        print("Flaca hay nooo, esas cosas yo no hago xD")

ADA_FFT(sys.argv[1])