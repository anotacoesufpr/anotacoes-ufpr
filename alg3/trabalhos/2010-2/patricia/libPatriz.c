#include "libPatriz.h"

void buscaPatriz (nodo p, int key, int bit)
{
	if (!p)
	{
		printf("nao achou");
		return;
	}

	if (p->key == key)
	{
		int i;
		for (i = 0; i < countAux1; i++)
		{
			printf("[%d], ", transicaoBuff[i]);
		}
		printf("(%d)", p->key);
		return;
	}
	else if (p->bit <= bit)
	{
		printf ("nao achou");
		return;
	}
	transicaoBuff[countAux1++] = p->bit;
	if (apl_digit(key, p->bit) == 0)
	{
		buscaPatriz (p->left, key, p->bit);
	}
	else
	{
		buscaPatriz (p->right, key, p->bit);
	}
}

void patrizImpressao (nodo p)
{
	if (!p)
	{
		printf ("()");
		return;
	}
	if (p->key > 0)
	{
		printf("(%d)", p->key);
	}
	else
	{
		printf ("([%d] ", p->bit);
		patrizImpressao (p->left);
		patrizImpressao (p->right);
		printf (")");
	}
}

nodo patrizInsere (nodo p, int key)
{
	if (!p)
	{
		p = criaNodo (-1, 0);
		if (apl_digit (key, 0) == 0)
		{
            p->left = criaNodo (key, 1);
		}
		else
		{
            p->right = criaNodo (key, 1);
		}
		return p;
	}
	return patrizInsereNodo (p, key, 0, NULL);
}

nodo patrizInsereNodo (nodo p, int key, int bit, nodo parent)
{
	int i, novoInt = 0;

	/**
	* @note Algoritmo discutido em sala
	**/

	if (!p)
	{
		novoInt = 1;
		i = bit;
	}
	else if (p->key > 0)
	{
		novoInt = 1;
		for (i = 0; i < tamPalavra && (apl_digit (key, i) == apl_digit (p->key, i)); i++);
	}
	if (novoInt)
	{
		nodo n = criaNodo (-1, i);
		nodo o = criaNodo (key, i+1);
		if (apl_digit (key, i) == 0)
		{
			n->left = o;
			n->right = p;
		}
		else
		{
			n->left = p;
			n->right = o;
		}
		return n;
	}
	else
	{
		if (apl_digit(key, p->bit) == 0)
		{
			p->left = patrizInsereNodo (p->left, key, bit+1, p);
		}
		else
		{
			p->right = patrizInsereNodo (p->right, key, bit+1, p);
		}
		return p;
    }
}

void patriciaEmOrdem (nodo p, int bit)
{
	/**
	* @note usado algorimto discutido em classe
	**/
	if (!p)
	{
		return;
	}
	if (p->bit <= bit)
	{
        return;
	}
	patriciaEmOrdem (p->left, p->bit);
	transicaoBuff[countAux1++] = p->key;
	patriciaEmOrdem (p->right, p->bit);
}

nodo transformaPatriciaEmPatriz (nodo patricia)
{
	int i;
	apl_free_transicaoBuff ();
	patriciaEmOrdem (patricia, -1);
	nodo patriz = criaNodo (-1, 0);
	for (i = 0; i < countAux1; i++)
	{
		patriz = patrizInsere (patriz, transicaoBuff[i]);
	}

	return patriz;
}

void patrizAnalisaCusto (nodo p)
{
	if (!p)
	{
		return;
	}
	countAux1 += sizeof (struct _nodo);
   countAux2++;

	/**
	* @note algoritmo recursivo igual patricia
	**/
	patrizAnalisaCusto (p->left);
	patrizAnalisaCusto (p->right);
}
