#include <stdio.h>

main () {
	void *a,*b,*c,*d;

	a=meuAlocaMem(100);
	imprMapa();
	b=meuAlocaMem(200);
	imprMapa();
	c=meuAlocaMem(300);
	imprMapa();
	d=meuAlocaMem(400);
	imprMapa();
	
	meuLiberaMem(b);
	imprMapa();

	b=meuAlocaMem(50);
	imprMapa();

	meuLiberaMem(c);
	imprMapa();
	meuLiberaMem(d);
	imprMapa();
	meuLiberaMem(a);
	imprMapa();
	meuLiberaMem(b);
	imprMapa();

}
