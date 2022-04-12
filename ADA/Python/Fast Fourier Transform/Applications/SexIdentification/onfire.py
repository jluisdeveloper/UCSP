from scipy import *
import numpy as np
import scipy.io.wavfile
import scipy.signal
import wave
import copy
import sys

def ADA_FFT(file):

    audioDATA = wave.open(file, 'r')  # solo para sacar el fps :v 

    signal = scipy.io.wavfile.read(file)
    signal = signal[1] # es un array de 3 dimensiones solo usamos la segunda dimension q contiene el array de de arrys con todas las senhales
    signal = signal.ravel() # unificamos el array d arrays a una sola dimension

    # original_signal = scipy.io.wavfile.read(file)
    # original_signal = original_signal[1]

    # aux = np.vstack(original_signal)
    # aux = aux.ravel(
    
    fps = audioDATA.getframerate() # sacamos el frame rate
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
            FFTs.append(scipy.fft.fft(fragments[i][1])) # calculamos la FFTs de los fragmentos mas ruidosos
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

            localMaxs = []
            for i in range(0, len(FFTnew)): # buscamos los maximos locales
                if i+6<len(FFTnew):
                    if FFTnew[i]<FFTnew[i+1] and FFTnew[i+1]>FFTnew[i+2]:
                        localMaxs.append(i+1)

            maxsNews = copy.copy(localMaxs) # eliminamos los maximos duplicados
            for i in range(len(localMaxs)-1):
                if localMaxs[i+1]-localMaxs[i]<9:
                    maxsNews.remove(localMaxs[i+1])

            avgDistance = 0.0
            if (len(maxsNews) > 1): # calculamos las distancias entre los armonicos (decibeles?)(tono de voz si es aguda o grave) para cada fragmento
                count += 1
                for i in range(len(maxsNews)-1):
                    avgDistance += maxsNews[i+1]-maxsNews[i]
                avgDistance /= float(len(maxsNews)-1)
                golbalPromDistance += avgDistance

    if count > 0:
        golbalPromDistance /= float(count) # calculamos las distancias de todos los fragmentos restantes

    if golbalPromDistance < 25.5: # determinamos si la voz es de mujer o de hombre
        print("Distinguido Hombre")
    else:
        print("Distinguida Dama")

ADA_FFT(sys.argv[1])