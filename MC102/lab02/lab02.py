# Início Funções

# Função validar resposta
def validarResposta(Resposta, Validas):
    if not(Resposta in Validas): 
        print("Opção inválida, recomece o questionário.")
        exit()
    return Resposta

# Fim Funções

# Início declaração de "variáveis", vulgo textos

Caminho_dos_desafios = "Suas escolhas te levaram a um caminho repleto de desafios, para você recomendamos as distribuições:"
Caminho_da_motivacao = "Você passará pelo caminho daqueles que decidiram abandonar sua zona de conforto, as distribuições recomendadas são:"
Caminho_do_aprendizado = "Ao trilhar esse caminho, um novo guru do Linux irá surgir, as distribuições que servirão de base para seu aprendizado são:" 

Pegunta_invade_sistemas = "É programador/ desenvolvedor ou de áreas semelhantes?\n(0) Não\n(1) Sim\n(2) Sim, realizo testes e invasão de sistemas\n"

# Fim declaração de "variáveis"

# Início principal

print("Este é um sistema que irá te ajudar a escolher a sua próxima Distribuição Linux. Responda a algumas poucas perguntas para ter uma recomendação.")

if(validarResposta(input("Seu SO anterior era Linux?\n(0) Não\n(1) Sim\n"), ['0','1']) == "0"):

    if(validarResposta(input("Seu SO anterior era um MacOS?\n(0) Não\n(1) Sim\n"), ['0','1']) == "0"):

        # path para aqui é Não, Não
        print(Caminho_da_motivacao, "Ubuntu Mate, Ubuntu Mint, Kubuntu, Manjaro.")
    else:

        # path para aqui é Não, Sim
        print(Caminho_da_motivacao, "ElementaryOS, ApricityOS.")
else:

    match validarResposta(input(Pegunta_invade_sistemas), ['0','1','2']):

        case "0": print(Caminho_do_aprendizado, "Ubuntu Mint, Fedora.") # path para aqui é Sim, Não

        case "2": print(Caminho_do_aprendizado, "Kali Linux, Black Arch.")# path para aqui é Sim, Sim, realizo testes e invasão de sistemas

        case _:

            if(validarResposta(input("Gostaria de algo pronto para uso ao invés de ficar configurando o SO?\n(0) Não\n(1) Sim\n"), ['0','1']) == "0"):

                if(validarResposta(input("Já utilizou Arch Linux?\n(0) Não\n(1) Sim\n"), ['0','1']) == "0"):

                    # path para aqui é Sim, Sim, Não, Não
                    print(Caminho_do_aprendizado, "Antergos, Arch Linux.")
                else:

                    # path para aqui é Sim, Sim, Não, Sim
                    print(Caminho_dos_desafios, "Gentoo, CentOS, Slackware.")
            else:

                if(validarResposta(input("Já utilizou Debian ou Ubuntu?\n(0) Não\n(1) Sim\n"), ['0','1'])== "0"):

                    # path para aqui é Sim, Sim, Sim, Não
                    print(Caminho_do_aprendizado, "OpenSuse, Ubuntu Mint, Ubuntu Mate, Ubuntu.")
                else:

                    # path para aqui é Sim, Sim, Sim, Sim
                    print(Caminho_dos_desafios, "Manjaro, ApricityOS.")

# Fim principal
# Início notas

# o uso do mach se evita o uso de uma várialvel para guardar a resposta
# tem alguma convenção para o tamanho de uma linha máximo?
# Beba água

# Fim notas