

#início Principal
def main(): 

    #início Entradas
    num_dias = int(input())
    dias = []
    for num_dia in range(num_dias):
        dias.append(Dia(num_dia+1))     
    del num_dias # número disponível em len(Dias)
    # Fim Entradas

    # Início Saídas

    for dia in dias:
        dia.Resulado_Dia()
        print() if dia.num_dia < len(dias) else print(end = "")

    # Fim Saídas

# Fim Principal
 
# Início Classes
class Dia:
    def __init__(self, num_dia):
        self.num_dia = num_dia
        num_pares_brigas = int(input())
        self.pares_brigas = []
        for i in range(num_pares_brigas):
            self.pares_brigas.append(input().split())
        del num_pares_brigas # número disponível em len(pares_brigas)

        in_tmp = input().split()
        procedi = [] 
        Quant = []
        for i in range(len(in_tmp)//2):
            procedi.append(in_tmp[i*2])
            Quant.append(int(in_tmp[(i*2)+1]))
        self.procedi_quant = [procedi,Quant]
        del in_tmp, procedi, Quant 

        num_animais = int(input())
        self.animal_procedimento = []
        for i in range(num_animais):
            self.animal_procedimento.append(input().split())
        del num_animais # Número disponível em len(animal_procedimento)
        
        self.animais = []
        for bixo in self.animal_procedimento:
            self.animais.append(bixo[0])

    def Resulado_Dia(self):
        
        print("Dia:", self.num_dia)

        quant_brigas = 0 
        for brigas in self.pares_brigas:
            if brigas[0] in self.animais and brigas[1] in self.animais:
                quant_brigas += 1
        print("Brigas:", quant_brigas)
       
        animais_Atendidos = []
        animais_Nao_Atendidos = []
        animais_Soliciou_Indisponivel = []
        for animal in self.animal_procedimento:
            
            if animal[1] in self.procedi_quant[0]:
                index_procedimento = self.procedi_quant[0].index(animal[1])     
                if(self.procedi_quant[1][index_procedimento] > 0):
                    self.procedi_quant[1][index_procedimento] -= 1
                    animais_Atendidos.append(animal[0])
                else:
                    animais_Nao_Atendidos.append(animal[0])
            else:
                animais_Soliciou_Indisponivel.append(animal[0])

        if(len(animais_Atendidos) > 0): 
            print("Animais atendidos: ", end="")
            print(*animais_Atendidos, sep=", ") 
        if(len(animais_Nao_Atendidos) > 0):
            print("Animais não atendidos: ", end="")
            print(*animais_Nao_Atendidos, sep=", ")
        if(len(animais_Soliciou_Indisponivel) > 0):
            for animal in animais_Soliciou_Indisponivel:
                print("Animal", animal, "solicitou procedimento não disponível.")
                    
#Fim Classes

main()



