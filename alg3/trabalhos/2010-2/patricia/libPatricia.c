#include "libPatriz.h"

nodo PatriciaInsere (nodo p, int key)
{
	int i;
	if (!p)
		{
			for (i = 1; i < tamPalavra && apl_digit (key, i); i++);
			if (i >= tamPalavra)
			{
				i = 0;
			}
			p = PatriciaInsereNodo (p, key, i-1, 0);
			return p;
	}
    nodo q = patriciaBuscaNodo (p, key, -1, NULL);

	for (i = 0; i < tamPalavra && (apl_digit (key, i) == apl_digit (q->key, i)); i++);
	if(i == q->bit)
	{
		return PatriciaInsereNodo (p, key, i+1, NULL);
	}	
	else
	{
		return PatriciaInsereNodo (p, key, i, NULL);
	}
}

nodo PatriciaInsereNodo (nodo p, int key, int bit, nodo parent) {
   int novoInt = 0;

	/**
	* @note Algoritmo discutido em sala
	**/

	if (!p || p->bit >= bit)
	{	
	novoInt = 1;
	}
	else if (parent)
	{
		if (p->bit <= parent->bit)
		{
			novoInt = 1;
		}
	}
	if (novoInt)
	{
		nodo n = criaNodo (key, bit);
		if (apl_digit(key, bit) == 0)
		{
			n->right = p;
			n->left = n;
		}
		else
		{
				n->right = n;
				n->left = p;
		}
		return n;
	}
	else
	{
		if (apl_digit(key, p->bit) == 0)
		{
			p->left = PatriciaInsereNodo (p->left, key, bit, p);
		}
		else
		{
            p->right = PatriciaInsereNodo (p->right, key, bit, p);
		}
		return p;
	}

}


void patriciaBusca (nodo p, int key, int bit)
{

	if (!p)
	{
		printf("nao achou");
		return;
	}

	if (p->bit <= bit && p->key == key)
	{
		int i;
		for (i = 0; i < countAux1; i++)
			printf("%d, ", transicaoBuff[i]);
		printf("{%d}", p->key);
		return;
	}
	else
	{
		if (p->bit <= bit)
			{
				printf ("nao achou");
				return;
			}
	}
	transicaoBuff[countAux1++] = p->key;
	if (apl_digit(key, p->bit) == 0)
	{
		patriciaBusca (p->left, key, p->bit);
	}
	else
	{
		patriciaBusca (p->right, key, p->bit);
	}
}

nodo patriciaBuscaNodo (nodo p, int key, int bit, nodo parent)
{
	if (!p)
	{
		return parent;
	}
	if (p->bit <= bit )
	{
	return p;
	}
	if (apl_digit (key, p->bit) == 0)
	{
		return patriciaBuscaNodo (p->left, key, p->bit, p);
	}
	else
	{
		return patriciaBuscaNodo (p->right, key, p->bit, p);
	}
}


void patriciaImpressao (nodo p, int bit)
{
	/**
	* @note tentei seguir a risca as instrucoes da especificacao para impressao
	* algoritmo comum, recursivo, para impressao, tambem discutido em aula
	**/
	if (!p)
	{
		printf ("()");
		return;
	}
	if (p->bit <= bit)
	{
		printf( "{%d}", p->key );
		return;
	}
	printf ("(");
	printf ("%d[%d] ", p->key, p->bit);
	patriciaImpressao (p->left, p->bit);
	patriciaImpressao (p->right, p->bit);
	printf(")");
}


void patrizEmOrdem (nodo p, int bit)
{
	if (!p)
	{
		return;
	}
	patrizEmOrdem (p->left, p->bit);
	if (p->key > 0)
	{
		transicaoBuff[countAux1++] = p->key;
	}
	patrizEmOrdem (p->right, p->bit);
}


nodo transformaPatrizEmPatricia (nodo patriz)
{
	apl_free_transicaoBuff ();
	patrizEmOrdem (patriz, 0);
	int i;
	nodo patricia = NULL;
	for (i = 0; i < countAux1; i++)
	{
        patricia = PatriciaInsere (patricia, transicaoBuff[i]);
	}
    return patricia;
}


void patriciaAnalisaCusto (nodo p, int bit)
{
	if (!p)
	{
		return;
	}
	countAux1 += sizeof (struct _nodo);
	countAux2++;
	if (p->bit <= bit)
	{
		return;
	}

	/**
	* @note algoritmo recursivo igual patriz
	**/
	patriciaAnalisaCusto (p->left, p->bit);
	patriciaAnalisaCusto (p->right, p->bit);

}

int apl_digit (int key, int bit)
{
	unsigned int *bin = malloc (tamPalavra * sizeof(int));
	bin = apl_dec2bin (key);
	return bin[bit];
}

int apl_bin2dec (int bin)
{
	int i, d = 0, t = 0;
	for (i = 0; i < tamPalavra; i++)
	{
		d = bin % 10;
      t += pow (2, i) * d;
      bin /= 10;
	}

    return t;
}

unsigned int* apl_dec2bin (int dec)
{
	int i;
	unsigned int *bin = malloc (tamPalavra * sizeof (int));
	for (i = 0; i < tamPalavra-1; i++) bin[i] = 0;
	for (i = tamPalavra - 1; dec > 0; i--)
	{
        bin[i] = dec % 2;
        dec >>= 1;
	}
	return bin;
}

void apl_free_transicaoBuff ()
{
	countAux1 = 0;
	countAux2 = 0;
	free (transicaoBuff);
	transicaoBuff = malloc (tamBuff * sizeof(int));
}

nodo criaNodo (int key, int bit)
{
	nodo p = malloc (sizeof(struct _nodo));
	p->left = NULL;
	p->right = NULL;
	p->bit = bit;
	p->key = key;
	return p;
}
