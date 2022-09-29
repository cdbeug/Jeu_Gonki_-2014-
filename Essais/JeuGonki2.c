#include <stdio.h>
#include <stdlib.h>
#include "JeuGonki.h"

int main () {
	Jeu();

	return 0;
}

void Jeu () {
	int couleur = 0;

	int base = (couleur==0)?1:0;

	int i,j;
	int t10[8][8];
	int q = 0;
	int qo = 0;
	int afCoordonnees = 1;

	/*noir : rond = 1, carré = 2;  */
	/*blanc : rond = 3, carré = 4;  */


	for (i=0; i<8; i++) for (j=0; j<8; j++) t10[i][j]=0;

	for (j=0; j<8; j+=2)
	t10[0][j]=1;

	for (j=1; j<8; j+=2)
	t10[1][j]=1;

	for (j=1; j<8; j+=2)
	t10[0][j]=2;

	for (j=0; j<8; j+=2)
	t10[1][j]=2;



	for (j=0; j<8; j+=2)
	t10[6][j]=3;

	for (j=1; j<8; j+=2)
	t10[7][j]=3;

	for (j=1; j<8; j+=2)
	t10[6][j]=4;

	for (j=0; j<8; j+=2)
	t10[7][j]=4;

	q = 0;
	qo = 0;
	afCoordonnees = 1;

	/*affiche(t10,afCoordonnees);  */

	while (1) {
		q = menuPrincipal ();

		if (q==1) {
			affiche(t10,afCoordonnees);

			while (1) {
				printf("%d\n",joueUnCoup(couleur,base,afCoordonnees,t10));

				if (couleur==1) couleur=0; else couleur=1; /*échange de variable couleur.  */
				base = (couleur==0)?1:0;

				affiche(t10,afCoordonnees);
			}
		}

		if (q==2) {
			qo = demandeOptions ();

			if (qo==1) {
				afCoordonnees = OptionsCoordonees ();
			}
		}
	}
}

int verifiePointCouleur (int couleur, int t[][8], int x, int y) {
	/*0 : blanc, 1 : noir  */

	int n=0; n=*(*(t+x)+y);

	if (couleur==0) return ((n>0&&n<3)||(n>4&&n<12));

	else if (couleur==1) return ((n>2&&n<5)||(n>11&&n<19));

	else return 0;
}

int joueUnCoup (int couleur, int base, int coordonnees, int t[][8]) {
	int *t5;

	/*
		-0 : blanc, 1 : noir
		-base : 0 : bas, 1 : haut
	*/

	int a, n ,x, y, sens, p;
	char c;

	t5 = malloc (2*sizeof(int));
	a=0; n=0; x=-1; y=-1; sens=0; p=0;
	/*char * b;  */
	c=0;

	while (x<0 || y<0 || x>7 || y>7) {
		printf("Joueur ");
		if (couleur==0) printf("blanc");
		else printf("noir");

		if (coordonnees==1) {
			printf(", veuillez entrer les coordonees de \nvotre coups : \nx = ");
			scanf("%d",&n);

			printf("\ny = ");

			getchar();

			c = getchar();
		}

		else {
			x=-1;

			while (x<0 || x>7) {
				printf(", veuillez entrer les coordonees de \nvotre coups  : \nx = ");
				scanf("%d",&x);
				x-=1;
			}

			y=-1;

			while (y<0 || y>7) {
				printf("\ny = ");
				scanf("%d",&y);
				y-=1;
			}

			if (!(x<0 || y<0 || x>7 || y>7)) if (!verifiePointCouleur(couleur,t,x,y)) { printf("\nErreur de couleurs\n"); /*--*/ x=-1; /*rejoue le while*/ }
		}

		if (coordonnees==1) {
			t5 = convertCoordonnees(c,n);

			x=t5[0];
			y=t5[1];
		}
	}

	p = t[x][y];

	printf("p = %d\n",p);

	printf("\nsens = ");
	a=0;

	if (p==1||p==3) {
		while (a!=1 && a!=2) {
			a=0;

			printf("\n1 : Gauche devant\n2 : Droite devant\n?=");
			scanf("%d",&a);
		}

		sens = a;
	}

	else if (p==2||p==4) {
		a=0;

		while (a!=1 && a!=2 && a!=3) {
			a=0;

			printf("\n1 : Gauche\n2 : Droite\n3 : Milieu\n?=");
			scanf("%d",&a);
		}

		sens = a;
	}

	else if (p==5 || p==12) {
		while (a!=1 && a!=2) {
			a=0;

			printf("\n1 : Gauche devant\n2 : Droite devant\n?=");
			scanf("%d",&a);
		}

		sens = a;
	}

	else if (p==6 || p==13) {
		a=0;

		while (a!=1 && a!=2 && a!=3) {
			a=0;

			printf("\n1 : Gauche\n2 : Droite\n3 : Milieu\n?=");
			scanf("%d",&a);
		}

		sens = a;
	}

	else if (p==7 || p==14) {
		while (a!=1 && a!=2 && a!=3 && a!=4 && a!=5) {
			a=0;

			printf("\n1 : Gauche\n2 : Droite\n3 : Milieu\n4 : Gauche devant\n5 : Droite devant\n?=");
			scanf("%d",&a);
		}

		sens = a;
	}

	else if (p==8 || p==15) {
		while (a!=1 && a!=2) {
			a=0;

			printf("\n1 : Gauche devant\n2 : Droite devant\n?=");
			scanf("%d",&a);
		}

		sens = a;
	}

	else if (p==9 || p==16) {
		a=0;

		while (a!=1 && a!=2 && a!=3) {
			a=0;

			printf("\n1 : Gauche\n2 : Droite\n3 : Milieu\n?=");
			scanf("%d",&a);
		}

		sens = a;
	}

	else if (p==10 || p==17) {
		while (a!=1 && a!=2 && a!=3 && a!=4 && a!=5) {
			a=0;

			printf("\n1 : Gauche\n2 : Droite\n3 : Milieu\n4 : Gauche devant\n5 : Droite devant\n?=");
			scanf("%d",&a);
		}

		sens = a;
	}

	else if (p==11 || p==18) {
		while (a!=1 && a!=2 && a!=3 && a!=4 && a!=5) {
			a=0;

			printf("\n1 : Gauche\n2 : Droite\n3 : Milieu\n4 : Gauche devant\n5 : Droite devant\n?=");
			scanf("%d",&a);
		}

		sens = a;
	}

	/*else return 0;  */

	printf("base = %d\nOk1.\n",base);

	if (p>0 && p<5) printf("%d\n",deplacePion (t, base, sens-1, x,y));

	return 1;
}

int demandeBase () {
	int a=0;



	while (a!=1 && a!=2) {
		a=0;

		printf("Souhaitez-vous jouer en haut ou en bas du plateau ?\n\n1 : Haut\n2 : Bas\n? = ");
		scanf("%d",&a);
	}

	return a;
}

int demandeMode () {
	int a=0;



	while (a!=1 && a!=2 && a!=3) {
		a=0;

		printf("En quel mode souhaitez-vous jouer ?\n\n1 : Vous contre l'ordinateur\n2 : Vous contre un autre humain\n3 : L'ordinateur contre lui-meme\n? = ");
		scanf("%d",&a);
	}

	return a;
}

int deplacePion (int t[][8], int base, int sens, int x, int y) {
	/*

-forme : 0 : rond, 1 : carré
-base : haut ou bas de l'échiquier. 0 : bas, 1 : haut

-sens : -rond : 0 : gauche, 1 : droite
-carré : 0 : gauche, 1 : droite, 3 : devant.

*/

	int forme=0;


	if (x>7||y>7||x<0||y<0) { printf("x>7||y>7||x<0||y<0\n"); return 0;} /*Vérifiaction des coordonnées.  */


	if (t[x][y]==1||t[x][y]==3) { printf("t[x][y]==0||t[x][y]==3\n"); forme=0;} if (t[x][y]==2||t[x][y]==4) { printf("t[x][y]==1||t[x][y]==4\n"); forme=1;}



	if (forme>1||forme<0) return 0; /*Vérifiaction de la forme.  */

	if (forme==0) { /*rond  */
		if (sens<0||sens>1) { printf("sens<0||sens>1\n"); return 0;}

		if (base==0) {
			if (sens==0) {
				if (x-1<0||y-1<0) { printf("x-1<0||y-1<0\n"); return 0;}

				else {
					t[x-1][y-1]=transformeUnPion(t,x,y,x-1,y-1);

					t[x][y]=0;

					return 1;
				}
			}

			if (sens==1) {
				if (x-1<0||y+1>7) { printf("x-1<0||y+1>7\n"); return 0;}

				else {
					t[x-1][y+1]=transformeUnPion(t,x,y,x-1,y+1);

					t[x][y]=0;

					return 1;
				}
			}
		}

		else if (base==1) {
			if (sens==0) {
				if (x+1>7||y-1<0) { printf("x+1>7||y-1<0\n"); return 0;}

				else {
					t[x+1][y-1]=transformeUnPion(t,x,y,x+1,y-1);

					t[x][y]=0;

					return 1;
				}
			}

			if (sens==1) {
				if (x+1>7||y+1>7) { printf("x+1>7||y+1>7\n"); return 0;}

				else {
					t[x+1][y+1]=transformeUnPion(t,x,y,x+1,y+1);

					t[x][y]=0;

					return 1;
				}
			}
		}

		else return 0;
	}

	if (forme==1) { /*carré  */
		if (sens<0||sens>2) { printf("sens<0||sens>2\n"); return 0;}

		if (base==0) {
			if (sens==0) {
				if (x-1<0||y-1<0) { printf("x-1<0||y-1<0\n"); return 0;}

				else {
					t[x][y-1]=transformeUnPion(t,x,y,x,y-1);

					t[x][y]=0;

					return 1;
				}
			}

			if (sens==1) {
				if (x-1<0||y+1>7) { printf("x-1<0||y+1>7\n"); return 0;}

				else {
					t[x][y+1]=transformeUnPion(t,x,y,x,y+1);

					t[x][y]=0;

					return 1;
				}
			}

			if (sens==2) {
				if (x-1<0) { printf("x-1<0\n"); return 0;}

				else {
					t[x-1][y]=transformeUnPion(t,x,y,x-1,y);

					t[x][y]=0;

					return 1;
				}
			}
		}

		else if (base==1) {
			if (sens==0) {
				if (x+1>7||y-1<0) { printf("x+1>7||y-1<0\n"); return 0;}

				else {
					t[x][y-1]=transformeUnPion(t,x,y,x,y-1);

					t[x][y]=0;

					return 1;
				}
			}

			if (sens==1) {
				if (x+1>7||y+1>7) { printf("x+1>7||y+1>7\n"); return 0;}

				else {
					t[x][y+1]=transformeUnPion(t,x,y,x,y+1);

					t[x][y]=0;

					return 1;
				}
			}

			if (sens==2) {
				if (x+1>7) { printf("x+1>7\n"); return 0;}

				else {
					printf("ok1\n");
					t[x+1][y]=transformeUnPion(t,x,y,x+1,y);

					t[x][y]=0;

					return 1;
				}
			}
		}

		else return 0;
	}

	return 0;
}

/*int deplacePionCompose (int t[][8], int base, int sens, int x, int y) {
int p1 = t[x][y];



}*/

int transformeUnPion (int t[][8], int x, int y, int x1, int y1) {
	int p1 = t[x][y];
	int p2 = t[x1][y1];

	/*if (p2==0) return p1;  */

	if (p1==p2) {
		if (p1==1) return 5;
		if (p1==2) return 6;

		if (p1==3) return 12;
		if (p1==4) return 13;
	}

	else {
		if ((p1==1 && p2==2) || (p1==2 && p2==1)) return 7;
		if ((p1==3 && p2==4) || (p1==4 && p2==3)) return 14;


		if ((p1==1 && p2==5) || (p1==5 && p2==1)) return 8;
		if ((p1==1 && p2==6) || (p1==6 && p2==1)) return 11;
		if ((p1==1 && p2==7) || (p1==7 && p2==1)) return 10;

		if ((p1==2 && p2==5) || (p1==5 && p2==2)) return 10;
		if ((p1==2 && p2==6) || (p1==6 && p2==2)) return 9;
		if ((p1==2 && p2==7) || (p1==7 && p2==2)) return 11;

		if ((p1==3 && p2==12) || (p1==12 && p2==3)) return 15;
		if ((p1==3 && p2==13) || (p1==13 && p2==3)) return 18;
		if ((p1==3 && p2==14) || (p1==14 && p2==3)) return 17;

		if ((p1==4 && p2==12) || (p1==12 && p2==4)) return 17;
		if ((p1==4 && p2==13) || (p1==13 && p2==4)) return 16;
		if ((p1==4 && p2==14) || (p1==14 && p2==4)) return 18;
	}

	return p1;
}

int * convertCoordonnees (char c, int n) {
	int x=0, y=0;

	int * t;
	t=malloc(2*sizeof(int));

	if (c=='A'||c=='a') y=0;
	else if (c=='B'||c=='b') y=1;
	else if (c=='C'||c=='c') y=2;
	else if (c=='D'||c=='d') y=3;
	else if (c=='E'||c=='e') y=4;
	else if (c=='F'||c=='f') y=5;
	else if (c=='G'||c=='g') y=6;
	else if (c=='H'||c=='h') y=7;
	else printf("Erreur sur le charactere entre.\n");

	if (n==8) x=0;
	else if (n==7) x=1;
	else if (n==6) x=2;
	else if (n==5) x=3;
	else if (n==4) x=4;
	else if (n==3) x=5;
	else if (n==2) x=6;
	else if (n==1) x=7;
	else printf("Erreur sur le chiffre entre.\n");

	t[0]=x;
	t[1]=y;

	return t;
}

void affiche (int t[][8], int coordonnees) {
	int i,j,k, l=8, c=5;

	if (coordonnees==1) {

		for (k=0; k<c+1; k++) printf(" ");
		printf("A");
		for (k=0; k<c; k++) printf(" ");
		printf("B");
		for (k=0; k<c; k++) printf(" ");
		printf("C");
		for (k=0; k<c; k++) printf(" ");
		printf("D");
		for (k=0; k<c; k++) printf(" ");
		printf("E");
		for (k=0; k<c; k++) printf(" ");
		printf("F");
		for (k=0; k<c; k++) printf(" ");
		printf("G");
		for (k=0; k<c; k++) printf(" ");
		printf("H");
		for (k=0; k<c; k++) printf(" ");
		printf("\n\n\n");

	}

	else {
		for (k=0; k<c+1; k++) printf(" ");

		for (i=0; i<8; i++) {
			printf("%d",(i+1));
			for (k=0; k<c; k++) printf(" ");
		}

		printf("\n\n\n");
	}

	for (i=0; i<8; i++) {

		if (coordonnees==1) {
			printf("%d",l);

			l--;
		}
		else {
			printf("%d",(i+1));
		}

		for (k=0; k<c; k++) printf(" ");

		for (j=0; j<8; j++) {
			if (t[i][j]==0) {printf(".");}
			if (t[i][j]==1) {printf("o");}
			if (t[i][j]==2) {printf("+");}

			if (t[i][j]==3) {printf("@");}
			if (t[i][j]==4) {printf("#");}

			if (t[i][j]==5) {printf("oo"); c=c-1; } 
			if (t[i][j]==6) {printf("++"); c=c-1; }
			if (t[i][j]==7) {printf("o+"); c=c-1; }
			if (t[i][j]==8) {printf("ooo"); c=c-2; }
			if (t[i][j]==9) {printf("+++"); c=c-2; }
			if (t[i][j]==10) {printf("+oo"); c=c-2; }
			if (t[i][j]==11) {printf("o++"); c=c-2; }

			if (t[i][j]==12) {printf("@@"); c=c-1; } 
			if (t[i][j]==13) {printf("##"); c=c-1; }
			if (t[i][j]==14) {printf("@#"); c=c-1; }
			if (t[i][j]==15) {printf("@@@"); c=c-2; }
			if (t[i][j]==16) {printf("###"); c=c-2; }
			if (t[i][j]==17) {printf("#@@"); c=c-2; }
			if (t[i][j]==18) {printf("@##"); c=c-2; }

			for (k=0; k<c; k++) printf(" ");

			c=5;
		}

		printf("\n\n\n");
	} /*temporaire  */
}

/*int menuPrincipal () {
int a=0;

while (a!=1) {
a=0;

printf("\nJeu de Gonki : \n\n\nMenu principal : \n\n1 : Jouer\n? = ");
scanf("%d",&a);
}

return a;
}*/

int menuPrincipal () {
	int a=0;

	while (a!=1 && a!=2) {
		a=0;

		printf("\nJeu de Gonki : \n\n\nMenu principal : \n\n1 : Jouer\n2 : Options\n? = ");
		scanf("%d",&a);
	}

	return a;
}

int demandeOptions () {
	int a=0;



	while (a!=1 && a!=2) {
		a=0;

		printf("\nOptions : \n\n1 : Modifier l'affichage des coordonees\n2 : Retour\n? = ");
		scanf("%d",&a);
	}

	return a;
}

int OptionsCoordonees () {
	int a=0;



	while (a!=1 && a!=2 && a!=3) {
		a=0;

		printf("\nModifier l'affichage des coordonnees : \n\n1 : Affichage par lettres et chiffres\n2 : Affichge par chiffres\n3 : Retour\n? = ");
		scanf("%d",&a);
	}

	return a;
}

