% Exemplo de if do ramiro:

caminho(A,B,Caminho):-
    achaAeroportos(Aeros),
    % Qual componenteConexa de A.
    % componenteConexa(A,Aeros,AeroA),
    % Qual componenteConexa de B.
    % componenteConexa(B,Aeros,AeroB),

    componenteConexa(A,CompConexaA),
    componenteConexa(B,CompConexaB),
    aeroporto(CompConexaA,AeroA),
    aeroporto(CompConexaB,AeroB),
    % aerop(CompConexa, Aeros, AeroA),
    % aerop(CompConexa, Aeros, AeroB).

    % Verifica se a cidad esta dentro da mesma componente coneexa
    ((CompConexaA = CompConexaB) -> path(A,B,Caminho,Custo); 
    (   
        % Pega caminho de A ate Aeroporto_de_A.
        path(A,AeroA,CaminhoA,CustoA),
        % Pega caminho de B ate Beroporto_de_B.
        path(B,AeroB,CaminhoBTmp,CustoB),
        reverse(CaminhoBTmp, CaminhoB),
        % Unifica caminhos em Caminho.
        concatenadas(CaminhoA, CaminhoB, Caminho)
    )). 

