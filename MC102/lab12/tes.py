from typing import Any


def main() -> None:
    pass


class Lista(list[Any]):
    def indice(self, valor: Any) -> int:
        inicio = 0
        fim = len(self) - 1
        while inicio <= fim:
            meio = (inicio + fim) // 2
            if self[meio] < valor:
                fim = meio - 1
            else:
                inicio = meio + 1
        return inicio

    def receber(self, valores: list[Any]) -> None:
        for valor in valores:
            indice_valor = self.indice(valor)
            self[indice_valor:indice_valor] = [valor]

    def organizar(self) -> None:
        lista: Lista = Lista()
        lista.receber(self)
        self[:] = lista

    def selecionar(self, carta_ref: Any) -> Any:
        indice_final = self.indice(carta_ref)
        indice_inicial = self.indice(self[indice_final - 1] + 1)
        select = self[indice_inicial:indice_final]
        print(carta_ref)
        print(indice_inicial, indice_final)
        print(select)
        print(self)

        # return Lista(select)

    def __str__(self) -> str:
        return "".join(
            [
                str(i) + ": " + str(valor) + "\n"
                for i, valor in zip(range(len(self)), self)
            ]
        )


teste = Lista([0, 20])
teste2 = Lista([0, 0, 1, 1, 3, 3, 4, 4, 6, 6, 7, 7, 9, 9, 10, 10, 14])

teste.organizar()
teste2.organizar()

# teste.receber([10, 11, 12, 34])
teste[1:1] = [10, 11, 12, 34]
print(teste)

while True:
    numero = int(input())
    # teste.selecionar(numero)
    teste2.selecionar(numero)

main() if __name__ == "__main__" else None
