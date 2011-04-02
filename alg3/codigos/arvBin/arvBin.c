/*
* representacao de arvores binarias
*/

Typedef struct no *apontador;
Typedef struct no {
	int chave;
	apontador esq, dir;
	/* conteudo */
} no;

/* percurso em pre-ordem recursiva */
void preordem(apontador n)
{
	if (n==null)
		return;
	printf("%d\n", n->chave);
	preordem(n->esq);
	preordem(n->dir);
}

/* percurso em pre-ordem recursiva */
void preordem(apontador n)
{
	pilha p;
	inicializa_pilha(p);
	while (!vazia(p))
		{
			n=pop(n);
			printf("%d\n", n->chave)
			if (n->dir != NULL)
				push(p, n->dir);
			if (n->esq != NULL)
				push(p,n->esq);
		}
}

/* contagem dos nos */
int contano(apontador n)
{
	if (n==null)
		return 0;
	return contano(n->esq) + contano(n->dir) +1;
}

/* altura da arvore */
int MAX(int S, int T)
{
	return S>T?S:T;
}

int altura(apontador n)
{
	if(n==null)
		return -1;
	return MAX(altura(n->esq), altura(n->dir))+1;
}

apontador busca(apontador P, int chave)
{
	if (p==null)
		return null;
	if (p->chave == chave)
		return p;
	else if (p->chave > chave)
		return busca(p->esq, chave);
	else
		return busca(p->dir, chave);
}

apontador insere (apontador p, int chave)
{
	if(p==null)
		return cria_no(chave);
	else if (p->chave > chave)
		p->esq = insere(p->esq, chave);
	else
		p->dir = insere(p->dir, chave);
	return p;
}

apontador remove (apontador p, int chave)
{
	apontador aux;

	if(p==null)
		return null;
	else if (p->chave > chave)
		p->esq = remove(p->esq, chave);
	else if (p->chave < chave)
		p->dir = insere(p->dir, chave);
	else if (p->esq==null && p->dir==null)
	{
		free(p);
		return NULL;
	}
	else if (p->dir == NULL)
	{
		aux=p->esq;
		free(p);
		return aux;
	}
	else if (p->esq == null)
	{
		aux = p->dir;
		free(p);
		return aux;
	}
	p->esq = substAntecessor(p,p->esq);
	return p;
}

apontador substAntecessor(apontador p, apontador ant)
{
	apontador aux;
	if (ant->dir != null)
	{
		ant->dir = subAntecessor(p,ant->dir);
		return ant;
	}
	p->chave = ant->chave;
	aux = ant->esq;
	free(ant);
	return aux;
}
