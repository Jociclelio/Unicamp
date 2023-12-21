# Ordena três números de forma decrescente 
maior = float(input("Digite o primeiro numero:"))
meio = float(input("Digite o Segundo numero:"))
menor = float(input("Digite o terceiro numero"))
if meio > maior:
    # Troca os valores de meio com o de maior
    meio = meio - maior
    maior = meio + maior
    meio = maior - meio
if menor > maior:
    # Troca os valores de menor com o de maior
    menor = menor - maior
    maior = menor + maior
    menor = maior - menor
if menor > meio:
    # Troca os valores de menor com o de meio
    menor = menor - meio
    meio = menor + meio
    menor = meio - menor
print("imprimindo numeros em ordem decrescente:")
print(maior,meio,menor)
# Caso queira em ordem crescente
# print(menor,meio,maior)