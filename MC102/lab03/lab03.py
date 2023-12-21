#!/usr/bin/python
# -*- coding: utf-8 -*-

# Início Inputs

quant_Jres = int(input())
num_Jres = list(map(int,input().split()))
inter_Jres = list(map(int,input().split()))

# Fim Inputs

# Início Cálculo de pontuação

pont_Jres = list()
for i in range(quant_Jres):
    if (i<(quant_Jres//2)):
        pont_Jres.append((inter_Jres[(i*2)+1]-inter_Jres[(i*2)])*num_Jres[i])
    else:
        pont_Jres.append((inter_Jres[(i*2)+1]-inter_Jres[(i*2)])+num_Jres[i])
# Fim Cálculo de pontuação

# Início Determinar vencedor

jogador_Ganhador = None
empate = False
pont_ganhador = 0
for i in range(quant_Jres):
    if pont_Jres[i] > pont_ganhador:
        empate = False
        pont_ganhador = pont_Jres[i]
        jogador_Ganhador = i+1
    elif pont_Jres[i] == pont_ganhador:
        empate = True

# Fim Determinar vencedor

# Início Imprimir resultados

if(empate):
    print("Rodada de cerveja para todos os jogadores!")
else:
    print("O jogador número", jogador_Ganhador, "vai receber o melhor bolo da cidade pois venceu com", pont_ganhador, "ponto(s)!")

# Fim Imprimir resultados
