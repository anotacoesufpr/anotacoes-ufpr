uses flavours;

flavour pessoa;
    ivars inst=4;
endflavour;

make_instance([ pessoa ])-> p1;

[ p1 p2 p3 p4] -> lista;

vars id;
if (p1<-inst == 4) then
    'sim'->id;
else
    'nao'->id;
endif;
if (valof(lista(1))<-inst == 4) then
    'sim'->id2;
else
    'nao'->id2;
endif;
