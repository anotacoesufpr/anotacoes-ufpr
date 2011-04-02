;;;
;;;                       Universidade Federal do Paraná
;;;                     Bacharelado em Ciência da Computação
;;;
;;;                    Técnicas Alternativas de Programação
;;;                           Prof. Alexandre Direne
;;;
;;;                         Implementação de Controle de
;;;                        um Elevador em POP11 Flavours
;;;
;;;                          Vinícius André Massuchetto
;;;                                 GRR20063784
;;;
;;;  Detalhes da implementação:
;;;
;;;    * `Entidades` são `pessoas` e `funcionários` no que diz respeito à
;;;       semelhança de chamadas que podem ser atribuídas a ambas;
;;;    * A `animação` encarrega-se de construir o gráfico e piscar
;;;      (escurecer) o andar desejado pelo tempo desejado;
;;;    * O `elevador` constrói, modifica e processa uma lista de listas
;;;      formatadas de acordo com o padrão `[nome saída chegada estado]`, onde:
;;;        nome    => nome da entidade;
;;;        saída   => andar de saída;
;;;        chegada => andar de chegada;
;;;        estado  => 1 para dentro do elevador, 0 para fora.
;;;

flavour entidade;
ivars nome andar meu_elevador;

    defmethod saia_do_predio;
		valof(meu_elevador) <- adiciona_requisicao([^nome ^andar 0 0]);
    enddefmethod;

endflavour;

flavour pessoa isa entidade;

    defmethod vai_pra_casa;
		valof(meu_elevador) <- adiciona_requisicao([^nome 0 ^andar 0]);
    enddefmethod;

endflavour;

flavour funcionario isa entidade;

    defmethod limpe_o_andar(a);
		valof(meu_elevador) <- adiciona_requisicao([^nome 0 ^a 0]);
    enddefmethod;

endflavour;

flavour animacao;
ivars altura, lista_ordenada = [];

	defmethod cria_arvore;
	lvars i = 1, a, item, arvore, andar, lista;

		[andar_0] -> arvore;
		while i <= altura then
			'andar_' >< i -> a;
			[^a ^arvore] -> arvore;
			i + 1 -> i;
		endwhile;

		monta_lista_coord(arvore) -> lista;

		for i from 0 to altura do
			for item in lista do
				consword('andar_' >< i) -> andar;
				if andar == item(1) then
					[^^lista_ordenada ^item] -> lista_ordenada;
				endif;
			endfor;
		endfor;

		redesenha_arvore(arvore);

	enddefmethod;

	defmethod pisca(andar_atual, tempo);
	lvars quadro;

		lista_ordenada(andar_atual+1) -> quadro;
		video_reverso(quadro(1),(quadro(2))(1),(quadro(2))(2),(quadro(2))(3),(quadro(2))(4));
        syssleep(tempo);
        video_normal(quadro(1),(quadro(2))(1),(quadro(2))(2),(quadro(2))(3),(quadro(2))(4));

	enddefmethod;

endflavour;

flavour elevador isa entidade;
ivars nome, altura, andar, atual = 0, requisicoes = [];

	defmethod adiciona_requisicao(requisicao);
		requisicao :: requisicoes -> requisicoes;
	enddefmethod;

	defmethod remove_requisicao(requisicao);
		delete(requisicao, requisicoes) -> requisicoes;
	enddefmethod;

    defmethod atenda_chamadas_e_requisicoes;
    vars i, tempo, sentido, parada, anim;

		make_instance([animacao altura ^altura]) -> anim;
		anim <- cria_arvore;

		pr('Eu, '); pr(self<-nome); pr(', dei inicio ao atendimento de chamadas e requisições.\n');

		while true then

			-1 -> sentido;
			0 -> parada;
			0 -> tempo;

			for i in requisicoes do

				;;; Define o sentido do elevador: [-1] desce, [1] sobe
				if
					;;; Se alguém está esperando em um andar acima
					(i(2) > atual and i(4) = 0) or

					;;; Se alguém está indo para um andar acima
					(i(3) > atual and i(4) = 1)
				then
					1 -> sentido;
				endif;

				;;; Define se o elevador deve parar: [0] não, [1] sim
				if
					;;; Se alguém precisa sair neste andar
					(i(3) = atual and i(4) = 1) or

					;;; Se alguém precisa entrar neste andar
					(i(2) = atual and i(4) = 0)
				then
					1 -> parada;
				endif;

			endfor;

			if parada = 1 then
				pr('Eu, '); pr(self<-nome); pr(', parei no andar '); pr(atual); pr(' e abri a porta.\n');

				;;; Verifica quem sai e quem fica
				for i in requisicoes do

					if i(3) = atual and i(4) = 1 then
						pr('Eu, '); pr(i(1)); pr(', saí do elevador.\n');
						self <- remove_requisicao(i);
						atual=>
						anim<-pisca(atual, 100);
					endif;

					if i(2) = atual and i(4) = 0 then
						pr('Eu, '); pr(i(1)); pr(', entrei no elevador.\n');
						pr('Eu, ');	pr(i(1)); pr(', apertei o botão para ir ao andar '); pr(i(3)); pr('.\n');
						1 -> i(4);
						anim<-pisca(atual, 100);
					endif;

				endfor;

				if length(requisicoes) = 0 then quitloop; endif;

				pr('Eu, '); pr(self<-nome); pr(', fechei a porta.\n');
				pr('Eu, '); pr(self<-nome); pr(', deixei o andar '); pr(atual);
				if sentido = 1 then
					pr(' e subi.\n');
				else
					pr(' e desci.\n');
				endif;

			else
				pr('Eu, '); pr(self<-nome); pr(', passei direto pelo andar '); pr(atual);
				if sentido = 1 then
					pr(' na subida.\n');
				else
					pr(' na descida.\n');
				endif;
				anim<-pisca(atual, 33);
			endif;

			;;; Altera o sentido e o andar atual do elevador
			atual + sentido -> atual;
			if atual < 0 then 0 -> atual; endif;
			if atual > altura then altura -> atual; endif;

		endwhile;

		pr('Eu, '); pr(self<-nome); pr(', terminei de atender as requisições.\n');

    enddefmethod;

endflavour;
