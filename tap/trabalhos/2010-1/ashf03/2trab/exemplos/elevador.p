lib flavours;


vars requisicoes = [], atual = 0, arvore, graf;

flavour entidade;
ivars nome andar meu_elevador;

    defmethod saia_do_predio;
		[^nome ^andar 0 0] :: requisicoes -> requisicoes;
    enddefmethod;

endflavour;

flavour pessoa isa entidade;

    defmethod vai_pra_casa;
		[^nome 0 ^andar 0] :: requisicoes -> requisicoes;
    enddefmethod;

endflavour;

flavour funcionario isa entidade;

    defmethod limpe_o_andar(a);
		[^nome 0 ^a 0] :: requisicoes -> requisicoes;
    enddefmethod;

endflavour;

flavour elevador isa entidade;
ivars nome, altura, andar;

	defmethod cria_arvore;
	vars i = 1, a;

		[0] -> arvore;
		while i <= altura then
			[^i [^^arvore]] -> arvore;
			i + 1 -> i;
		endwhile;

	enddefmethod;

    defmethod atenda_chamadas_e_requisicoes;
    vars i, sentido, parada;

		;;; self <- cria_arvore;
		;;; redesenha_arvore(arvore);
		;;; monta_lista_coord(arvore) -> graf;
		;;; arvore =>
		;;; graf =>

		pr('Eu, '); pr(self<-nome); pr(', dei inicio ao atendimento de chamadas e requisições.\n');

		while true then

			-1 -> sentido;
			0 -> parada;

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
				pr('Eu, '); pr(self<-nome); pr(', parei no andar '); pr(atual); pr(' e abri a porta.'); pr('\n');

				;;; Verifica quem sai e quem fica
				for i in requisicoes do

					if i(3) = atual and i(4) = 1 then
						pr('Eu, '); pr(i(1)); pr(', saí do elevador.\n');
						delete(i, requisicoes) -> requisicoes;
					endif;

					if i(2) = atual and i(4) = 0 then
						pr('Eu, '); pr(i(1)); pr(', entrei no elevador.\n');
						pr('Eu, ');	pr(i(1)); pr(', apertei o botão para ir ao andar '); pr(i(3)); pr('.\n');
						1 -> i(4);
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
			endif;

			;;; Altera o sentido e o andar atual do elevador
			atual + sentido -> atual;
			if atual < 0 then 0 -> atual; endif;
			if atual > altura then altura -> atual; endif;

		endwhile;

		pr('Eu, '); pr(self<-nome); pr(', terminei de atender as requisições.\n');

    enddefmethod;

endflavour;

vars e1 p1 p2 p3 p4 f1 f2 f3;

make_instance([ elevador nome e1 altura 8 andar 0 ]) -> e1;
make_instance([ pessoa nome p1 andar 3 meu_elevador e1 ]) -> p1;
make_instance([ pessoa nome p2 andar 3 meu_elevador e1 ]) -> p2;
make_instance([ pessoa nome p3 andar 6 meu_elevador e1 ]) -> p3;
make_instance([ pessoa nome p4 andar 7 meu_elevador e1 ]) -> p4;
make_instance([ funcionario nome f1 andar 5 meu_elevador e1 ]) -> f1;
make_instance([ funcionario nome f2 andar 4 meu_elevador e1 ]) -> f2;
make_instance([ funcionario nome f3 andar 0 meu_elevador e1 ]) -> f3;

p1 <- saia_do_predio;
p2 <- vai_pra_casa;
p3 <- saia_do_predio;
p4 <- vai_pra_casa;
f1 <- limpe_o_andar(7);
f2 <- saia_do_predio;
f3 <- limpe_o_andar(6);

e1 <- atenda_chamadas_e_requisicoes;
;;; e1 <- cria_arvore;
;;; arvore =>
