uses flavours;

flavour grafico;
    ivars altura,lista_ord=[];

        defmethod cria;
            lvars arvore,andar,i,lista;

                ;;; Cria a hierarquia de andares
                ['andar_0'] -> arvore;
                for i from 1 to altura do
                    'andar_' >< i -> andar;
                    [ ^andar  ^arvore] -> arvore;
                endfor;
   
                ;;; Pega as coordenadas dos andares
                monta_lista_coord(arvore) -> lista;

                ;;; Ordena a lista com as coordenadas
                for i from 0 to altura do
                    for item in lista do
                        consword('andar_' >< i) -> andar;
                        if andar == item(1) then
                            [^^lista_ord ^item] -> lista_ord;
                        endif;  
                    endfor;
                endfor;

                ;;; Desenha na tela
                redesenha_arvore(arvore);
        enddefmethod;

    
        defmethod acenda(andar_atual);
            lvars lista;
                lista_ord(andar_atual+1) -> lista;
                video_reverso(lista(1),(lista(2))(1),(lista(2))(2),(lista(2))(3),(lista(2))(4));
        enddefmethod;


        defmethod apague(andar_atual);
            lvars lista;
                lista_ord(andar_atual+1) -> lista;
                video_normal(lista(1),(lista(2))(1),(lista(2))(2),(lista(2))(3),(lista(2))(4));
        enddefmethod;

endflavour;

flavour pessoa;
    ivars nome andar meu_elevador dentro=0, func=0, casa=0;

    defmethod chama;
        if dentro ==0 then
            syssleep(100);
            'Eu, '><nome><', entrei na cabine.' =>
            1->dentro;
            if valof(meu_elevador)<-andar == andar then
                valof(meu_elevador) <- adiciona(0,nome);
                'Eu, '><nome><', apertei o botao para ir ao andar 0.' =>
            else
                valof(meu_elevador) <- adiciona(andar,nome);
                'Eu, '><nome><', apertei o botao para ir ao andar '><andar><'.' =>
            endif;
            
            valof(meu_elevador) <- remove(valof(meu_elevador)<-andar,nome);
        else
        valof(meu_elevador) <- remove(valof(meu_elevador)<-andar,nome);
        syssleep(100);
        'Eu, '><nome><', sai da cabine.' =>
        endif;

    enddefmethod;

    defmethod saia_do_predio;
        valof(meu_elevador) <- adiciona(andar,nome);
        'Eu, '><nome><', chamei o elevador.' =>
    enddefmethod;
    
    defmethod vai_para_casa;
        valof(meu_elevador) <- adiciona(0,nome);
        1->casa;
        'Eu, '><nome><', chamei o elevador.' =>
    enddefmethod;
    
endflavour;
;;;========================================
flavour funcionario isa pessoa;
    ivars destino=0, func=1;

    defmethod chama;
        if dentro ==0 then
            syssleep(100);
            'Eu, '><nome><', entrei na cabine.' =>
            1->dentro;
            valof(meu_elevador) <- adiciona(destino,nome);
            'Eu, '><nome><', apertei o botao para ir ao andar '><destino><'.' =>
            
            valof(meu_elevador) <- remove(valof(meu_elevador)<-andar,nome);
        else
        valof(meu_elevador) <- remove(valof(meu_elevador)<-andar,nome);
        'Eu, '><nome><', sai da cabine.' =>
            syssleep(100);
        endif;

    enddefmethod;

    defmethod limpe_o_andar(andno);
        valof(meu_elevador) <- adiciona(andar,nome);
        andno -> destino;
        'Eu, '><nome><', chamei o elevador.' =>
    enddefmethod;
endflavour;
;;;========================================

flavour elevador;
    ivars nome andar=0, altura lista=0, maior=0, gf;


    defmethod ver;
        for i from 0 to altura do i >< lista(i) =>
        endfor;
    enddefmethod;

    defmethod remove(andno,pess);
        delete(pess,lista(andno)) -> lista(andno);
    enddefmethod;

    defmethod adiciona(andno,pess);
        
        if lista==0 then
            self<-init_vetor;
        endif;

        if andno > maior then
            andno -> maior;
        endif;

        if lista(andno) == -1 then
            [ ^pess ] -> lista(andno);
        else
            [ ^pess ^^(lista(andno)) ] -> lista(andno);
        endif;

    enddefmethod;

    defmethod init_vetor;
        newarray([0 ^altura],0) -> lista;
        for i from 0 to altura do [] -> lista(i);
        endfor;
    enddefmethod;

    defmethod atenda_chamadas_e_requisicoes;
    make_instance([grafico altura ^altura]) -> gf;
    gf<-cria;
        'Eu, '><nome>< ', dei inicio ao atendimento de chamadas e requisicoes.' =>

        for i from 0 to maior do
        i->andar;
        gf<-acenda(andar);
        if lista(andar)==[] then
            syssleep(33);
            'Eu, '><nome>< ', passei direto pelo andar '><andar><' na subida.' =>
        else
             if andar >0 then
            'Eu, '><nome>< ', parei no andar '><andar><' e abri a porta.' =>
             endif;
        
;;; TEM GENTE NO ANDAR
            if andar > 0 then
                for i2 in lista(andar) do
                if (valof(i2)<-func == 1) then;
                valof(i2)<-chama;
                else
                    if (valof(i2)<-casa == 1) then;
                    valof(i2)<-chama;
                    endif;
                endif;
                endfor;
             else
                for i2 in lista(andar) do
                valof(i2)<-chama;
                endfor;
             endif;

            'Eu, '><nome>< ',  fechei a porta.' =>
            if andar == maior then
            'Eu, '><nome>< ', deixei o andar '><andar><' e desci.' =>
            else
            'Eu, '><nome>< ', deixei o andar '><andar><' e subi.' =>
            endif
        endif;
        gf<-apague(andar);
        endfor;
;;; DESCENDOOOOOOOOOOOO
        for i from maior-1 by -1 to 0 do
        i->andar;
        gf<-acenda(andar);

        if lista(andar)==[] then
            syssleep(33);
            'Eu, '><nome>< ', passei direto pelo andar '><andar><' na descida.' =>
        else
            'Eu, '><nome>< ', parei no andar '><andar><' e abri a porta.' =>
        

            for i2 in lista(andar) do
            valof(i2)<-chama;
            endfor;

            if andar > 0 then
                'Eu, '><nome>< ',  fechei a porta.' =>
                'Eu, '><nome>< ', deixei o andar '><andar><' e desci.' =>
            endif;
        endif;
        gf<-apague(andar);
        endfor;
        'Eu, '><nome>< ' terminei o atendimento de chamadas e requisicoes.' =>
    enddefmethod;

endflavour;
