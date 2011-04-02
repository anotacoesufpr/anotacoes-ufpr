uses flavours;
flavour pessoa;
    ivars nome idade sexo;
    ;;; Niver
    defmethod niver;
        idade + 1 -> idade ;
        [ feliz niver ^nome] =>
    enddefmethod;

    ;;; Nome
    defmethod nome;
        [ Pessoa: ^nome ] =>
    enddefmethod;

    ;;; Sexo
    defmethod sexo;
        [ Sexo: ^sexo ] =>
    enddefmethod;

    ;;; Idade
    defmethod idade;
        [ Idade: ^idade ] =>
    enddefmethod;
endflavour;


vars p;
make_instance([pessoa nome ramiro idade 23 sexo sim]) -> p;

p <- nome;
p <- idade;
p <- sexo;
