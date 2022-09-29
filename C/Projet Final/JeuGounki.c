#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "JeuGounki.h"
#include "DeploiePion.c"

int * pions; /*Il y a 16 pions par équipe au départ (8 ronds, 8 carres).  */

int main (int argc, char *argv[]) {
	int i;
	char * blabla1;
	int test;

	test=0;

	blabla1 = malloc(2*sizeof(char));
	blabla1[0]='-';
	blabla1[1]='t';

	pions = malloc(16*sizeof(int));

	for (i=0; i<16; i++) pions[i]=0;

	for (i=1; i<argc; i++) {if (argv[i][0]=='-' && argv[i][1]=='t') {JeuTest(0); test=1;}}
	if (!test) Jeu();

	return 0;		
}

/* on inclue le fichier qui contient les fonctions de deploiement.  */

#include "DeploiePion.c"

int compareStrSize (char * c1, int size1,char * c2, int size2) {
	int i;

	if (size1!=size2) return 0;

	for (i=0; i<size1; i++) {
		if (c1[i]!=c2[i]) return 0;
	}

	return 1;
}

int compareStr (char * c1, char * c2) {
	int i, size1, size2;

	size1 = calculeTaille(c1); size2 = calculeTaille(c2);

	if (size1!=size2) return 0;

	for (i=0; i<size1; i++) {
		if (c1[i]!=c2[i]) return 0;
	}

	return 1;
}

int publieDeplacePion (int t[][8], char * c3, int base, int sens, int x, int y, int forme) {
	/*

		-forme : 0 : rond, 1 : carré
		-base : haut ou bas de l'échiquier. 0 : bas, 1 : haut

		-sens : -rond : 0 : gauche, 1 : droite
			-carré : 0 : gauche, 1 : droite, 3 : devant.

		*/

	int x1, y1;

	char * c1;
	char * c2;

	x1=0; y1=0;	
	
	if (x>7||y>7||x<0||y<0) {printf("x>7||y>7||x<0||y<0\n"); return 0;} /*Vérifiaction des coordonnées.  */

	if (forme>1||forme<0) return 0; /*Vérifiaction de la forme.  */

	if (forme==0) { /*rond  */
		if (sens<0||sens>1) {printf("sens<0||sens>1\n"); return 0;}

		if (base==0) {
			if (sens==0) {
				x1=x-1;
				y1=y-1;
			}
			
			if (sens==1) {
				x1=x-1;
				y1=y+1;
			}
		}

		else if (base==1) {
			if (sens==0) {
				x1=x+1;
				y1=y-1;
			}
			
			if (sens==1) {
				x1=x+1;
				y1=y+1;
			}
		}

		else return 0;
	}

	if (forme==1) { /*carré  */
		if (sens<0||sens>2) {printf("sens<0||sens>2\n"); return 0;}

		if (base==0) {
			if (sens==0) {
				x1=x;
				y1=y-1;
			}
			
			if (sens==1) {
				x1=x;
				y1=y+1;
			}

			if (sens==2) {
				x1=x-1;
				y1=y;
			}
		}

		else if (base==1) {
			if (sens==0) {
				x1=x;
				y1=y-1;
			}
			
			if (sens==1) {
				x1=x;
				y1=y+1;
			}

			if (sens==2) {
				x1=x+1;
				y1=y;
			}
		}

		else return 0;	
	}

	c1 = convertitCoord2(x,y);
	c2 = convertitCoord2(x1,y1);

	c3[0] = c1[0];
	c3[1] = c1[1];
	c3[2] = '-';
	c3[3] = c2[0];
	c3[4] = c2[1];

	return 1;
}

int publieDeplacePionCompose (char * c3, int t[][8], int base, int sens, int x, int y, int ct, int p1) {
	int cr, cc, pion,x1,y1;
	int rond_carre;

	char * c1;
	char * c2;

	rond_carre=0;
	cr=0; cc=0; pion=0;

	/*

		-base : haut ou bas de l'échiquier. 0 : bas, 1 : haut

		cr = coup rond.
		cc = coup carré.	

		*/


	x1=0, y1=0;

	if (p1==5||p1==12) {cr=2; cc=0;}
	if (p1==6||p1==13) {cr=0; cc=2;}
	if (p1==7||p1==14) {cr=1; cc=1;}
	if (p1==8||p1==15) {cr=3; cc=0;}
	if (p1==9||p1==16) {cr=0; cc=3;}
	if (p1==10||p1==17) {cr=2; cc=1;}
	if (p1==11||p1==18) {cr=1; cc=2;}

	if (cr+cc==2) pion=2; /*pion composé de deux pions  */
	if (cr+cc==3) pion=3; /*pion composé de trois pions (saturé).  */

	if (p1==5 || p1==8 || p1==12 || p1==15) cr=ct; /*rond  */
	if (p1==6 || p1==9 || p1==13 || p1==16) cc=ct; /*carre  */
	if (p1==7 || p1==10 || p1==11 || p1==14 || p1==17 || p1==18) { /*rond-carre  */
		if (sens<2) cr=ct; /*rond  */
		if (sens>1) cc=ct; /*carre  */
	}

	/*printf("ok1.\nBase = "+base+"\nsens = "+sens+"\nx = "+x+"\ny = "+y+"\ncr = "+cr+"\ncc = "+cc+"\n");  */

	if (p1==7||p1==10||p1==11||p1==14||p1==17||p1==18) rond_carre=1;
	
	if (base==0) {
		if (p1==1||p1==3||p1==5||p1==8||p1==12||p1==15||rond_carre) { /* rond ou rond-carre  */
			if (sens==0) {
				if (x-1<0||y-1<0) {printf("x-1<0||y-1<0"); return 0;}

				else {
					if (cr==2) {
						if (x-2<0&&y-2<0) {
							x1=x;
							y1=y;
							

						}

						else if (x-2<0) {
							x1=x;
							y1=y-2;
							

						}

						else if (y-2<0) {
							x1=x-2;
							y1=y;
							

						}

						else {
							x1=x-cr;
							y1=y-cr;
							

						}
					}
					
					else if (cr==3) {
						if (x-2<0&&y-2<0) {
							x1=x+1;
							y1=y+1;
							

						}

						else if (x-3<0&&y-3<0) {
							x1=x-1;
							y1=y-1;
							

						}

						else if (x-1==1&&y-1==0) {
							x1=1;
							y1=2;
							

						}

						else if (x-2==1&&y-2==0) {
							x1=0;
							y1=1;
							

						}

						else {
							x1=x-cr;
							y1=y-cr;
							

						}
					}

					else {
						x1=x-cr;
						y1=y-cr;
						

					}
				}
			}
			
			if (sens==1) {
				if (x-1<0||y+1>7) {printf("x-1<0||y+1>7"); return 0;}

				else {
					if (cr==2) {
						if (x-2<0 && y+2>7) {
							x1=x;
							y1=y;


						}

						else if (x-2<0) {
							x1=x;
							y1=y+2;
							

						}

						else if (y+2>7) {
							x1=x-2;
							y1=y;
							

						}

						else {
							x1=x-cr;
							y1=y+cr;
							

						}
					}

					else if (cr==3) {
						if (x-2<0&&y+2>7) {
							x1=x+1;
							y1=y-1;
							

						}

						else if (x-3<0&&y+3>7) {
							x1=x-1;
							y1=y+1;				
							

						}

						else if (x-1==1&&y+1==7) {
							x1=1;
							y1=5;					
							

						}

						else if (x-2==1&&y+2==7) {
							x1=0;
							y1=6;					
							

						}

						else {
							x1=x-cr;
							y1=y+cr;							
							

						}
					}

					else {
						x1=x-cr;
						y1=y+cr;										
						
					}
				}
			}		
		}

		if (p1==2||p1==4||p1==6||p1==9||p1==13||p1==16||rond_carre) { /* carre  */
			if (((!rond_carre)&&sens==0) || (rond_carre&&sens==2)) { /* sens=0  */
				if (y-1<0) {printf("y-1<0"); return 0;}

				else {
					if (cc==2) {
						if (y-2<0) {
							x1=x;
							y1=y;


						}

						else {
							x1=x;
							y1=y-cc;						
							

						}
					}

					else if (cc==3) {
						if (y-2<0) {
							x1=x;
							y1=y+1;							
							

						}

						else if (y-3<0) {
							x1=x;
							y1=y-1;
							
							
						}

						else {
							x1=x;
							y1=y-cc;					
							

						}
					}

					else {						
						x1=x;
						y1=y-cc;										
						
						
					}
				}
			}
			
			if (((!rond_carre)&&sens==1) || (rond_carre&&sens==3)) { /* sens=1  */
				if (y+1>7) {printf("y+1>7"); return 0;}

				else {
					if (cc==2) {
						if (y+2>7) {
							x1=x;
							y1=y;


						}

						else {
							x1=x;
							y1=y+cc;
							

						}
					}

					else if (cc==3) {
						if (y+2>7) {
							x1=x;
							y1=y-1;					
							

						}

						else if (y+3>7) {
							x1=x;
							y1=y+1;							
							
							
						}

						else {
							x1=x;
							y1=y+cc;
							

						}
					}

					else {						
						x1=x;
						y1=y+cc;			
						
						
					}
				}
			}
			
			if (((!rond_carre)&&sens==2) || (rond_carre&&sens==4)) { /* sens=2  */
				if (x-1<0) {printf("x-1<0"); return 0;}

				else {
					if (cc==2) {
						if (x-2<0) {
							x1=x;
							y1=y;


						}

						else {
							x1=x-cc;
							y1=y;					
							

						}
					}

					else if (cc==3) {
						if (x-2<0) {
							x1=x+1;
							y1=y;							
							

						}

						else if (x-3<0) {
							x1=x-1;
							y1=y;
							
							
						}

						else {
							x1=x-cc;
							y1=y;						
							

						}
					}

					else {
						x1=x-cc;
						y1=y;
						
						
					}
				}
			}
		}
	}

	if (base==1) {
		if (p1==1||p1==3||p1==5||p1==8||p1==12||p1==15||rond_carre) { /* rond  */
			/*printf("p1==8");  */
			
			if (sens==0) {
				if (x+1>7||y-1<0) {printf("x+1>7||y-1<0"); return 0;}

				else {
					if (cr==2) {
						if (x+2>7&&y-2<0) {
							x1=x;
							y1=y;


						}

						else if (x+2>7) {
							x1=x;
							y1=y-2;					
							

						}

						else if (y-2<0) {
							x1=x+2;
							y1=y;
							

						}

						else {
							x1=x+cr;
							y1=y-cr;
							

						}
					}

					if (cr==3) {
						if (x+2>7&&y-2<0) {
							x1=x-1;
							y1=y+1;
							

						}

						else if (x+3>7&&y-3<0) {
							x1=x+1;
							y1=y-1;
							

						}

						else if (x+1==6&&y-1==0) {
							x1=6;
							y1=2;
							

						}

						else if (x+2==6&&y-2==0) {
							x1=7;
							y1=1;
							

						}

						else {
							x1=x+cr;
							y1=y-cr;
							

						}
					}

					else {
						x1=x+cr;
						y1=y-cr;								
						
						
					}
				}
			}
			
			if (sens==1) {
				if (x+1>7||y+1>7) {printf("x+1>7||y+1>7"); return 0;}

				else {
					if (cr==2) {
						if (x+2>7&&y+2>7) {
							x1=x;
							y1=y;


						}

						else if (x+2>7) {
							x1=x;
							y1=y+2;						
							

						}

						else if (y+2>7) {
							x1=x+2;
							y1=y;
							

						}

						else {
							x1=x+cr;
							y1=y+cr;								
							

						}
					}

					if (cr==3) {
						if (x+2>7&&y+2>7) {
							x1=x+1;
							y1=y+1;
							

						}

						else if (x+3>7&&y+3>7) {
							x1=x-1;
							y1=y-1;
							

						}

						else if (x+1==6&&y+1==7) {
							x1=6;
							y1=5;
							

						}

						else if (x+2==6&&y+2==7) {
							x1=7;
							y1=6;
							

						}

						else {
							x1=x+cr;
							y1=y+cr;
							

						}
					}

					else {
						x1=x+cr;
						y1=y+cr;
						
						
					}
				}
			}		
		}

		if (p1==2||p1==4||p1==6||p1==9||p1==13||p1==16||rond_carre) { /* carre  */
			if (((!rond_carre)&&sens==0) || (rond_carre&&sens==2)) { /* sens=0  */
				if (y-1<0) {printf("y-1<0"); return 0;}

				else {
					if (cc==2) {
						if (y-2<0) {
							x1=x;
							y1=y;


						}

						else {
							x1=x;
							y1=y-cc;
							

						}							
					}

					else if (cc==3) {
						if (y-2<0) {
							x1=x;
							y1=y+1;
							

						}

						else if (y-3<0) {
							x1=x;
							y1=y-1;
							
							
						}

						else {
							x1=x;
							y1=y-cc;
							

						}
					}

					else {
						x1=x;
						y1=y-cc;
						
						
					}
				}
			}
			
			if (((!rond_carre)&&sens==1) || (rond_carre&&sens==3)) { /* sens=1  */
				if (y+1>7) {printf("y+1>7"); return 0;}

				else {
					if (cc==2) {
						if (y+2>7) {
							x1=x;
							y1=y;


						}

						else {
							x1=x;
							y1=y+cc;
							

						}
					}

					else if (cc==3) {
						if (y+2>7) {
							x1=x;
							y1=y-1;
							

						}

						else if (y+3>7) {
							x1=x;
							y1=y+1;
							
						}

						else {
							x1=x;
							y1=y+cc;
							

						}
					}

					else {
						x1=x;
						y1=y+cc;
						
						
					}
				}
			}
			
			if (((!rond_carre)&&sens==2) || (rond_carre&&sens==4)) { /* sens=2  */
				if (x+cc>7) {printf("x+cc>7"); return 0;}

				else {
					if (cc==2) {
						if (x+2>7) {
							x1=x;
							y1=y;


						}

						else {
							x1=x+cc;
							y1=y;
							

						}
					}

					else if (cc==3) {
						if (x+2>7) {
							x1=x-1;
							y1=y;
							

						}

						else if (x+3>7) {
							x1=x+1;
							y1=y;
							
							
						}

						else {
							x1=x+cc;
							y1=y;
							

						}
					}

					else {							
						x1=x+cc;
						y1=y;
						
						
					}
				}
			}
		}
	}

	c1 = convertitCoord2(x,y);
	c2 = convertitCoord2(x1,y1);

	c3[0]=c1[0];
	c3[1]=c1[1];
	c3[2]='-';
	c3[3]=c2[0];
	c3[4]=c2[1];

	return 1;
}

char * convertitCoord2 (int x, int y) {
	char * s;
	s = malloc(sizeof(int)*2);

	if (y==0) s[0]='a';
	else if (y==1) s[0]='b';
	else if (y==2) s[0]='c';
	else if (y==3) s[0]='d';
	else if (y==4) s[0]='e';
	else if (y==5) s[0]='f';
	else if (y==6) s[0]='g';
	else if (y==7) s[0]='h';
	else printf("Erreur sur le charactere entre.");

	if (x==0) s[1]='8';
	else if (x==1) s[1]='7';
	else if (x==2) s[1]='6';
	else if (x==3) s[1]='5';
	else if (x==4) s[1]='4';
	else if (x==5) s[1]='3';
	else if (x==6) s[1]='2';
	else if (x==7) s[1]='1';
	else printf("Erreur sur le chiffre entre.");

	return s;
}

int convertPieceInv (int p1) {
	int a;

	a=p1;

	/*
		-couleur : 0 : blanc, 1 : noir.
	*/

	if (p1==0) a=0;
	if (p1==2 || p1==4) a=1;
	if (p1==1 || p1==3) a=2;
	if (p1==6 || p1==13) a=3;
	if (p1==5 || p1==12) a=4;
	if (p1==9 || p1==16) a=5;
	if (p1==8 || p1==15) a=6;
	if (p1==7 || p1==14) a=7;
	if (p1==11 || p1==18) a=8;
	if (p1==10 || p1==17) a=9;

	return a;
}

int convertPiece (int couleur, int n) {
	int a;

	a=n;

	/*
			-couleur : 0 : blanc, 1 : noir.
	*/

	if (n==0) a=0;
	if (couleur==0) {
		if (n==1) a=2;
		if (n==2) a=1;
		if (n==3) a=6;
		if (n==4) a=5;
		if (n==5) a=9;
		if (n==6) a=8;
		if (n==7) a=7;
		if (n==8) a=11;
		if (n==9) a=10;
	}

	if (couleur==1) {
		if (n==1) a=4;
		if (n==2) a=3;
		if (n==3) a=13;
		if (n==4) a=12;
		if (n==5) a=16;
		if (n==6) a=15;
		if (n==7) a=14;
		if (n==8) a=18;
		if (n==9) a=17;
	}

	return a;
}

void JeuTest (int configuration) {
	int i,n, finJeu;
	char * s;
	char * s1;
	int t[8][8];

	n=0; finJeu=0;

	remplitTabbleau(t,configuration);

	while (1) {
		printf("\nCoup %d : \n",n);
		affiche(t,1,3); /*t,afCoordonnees,esp.  */
		printf("\n");

		if (finJeu!=0) {
			if (s[calculeTaille(s)-1]!='#') {
				s1 = malloc((calculeTaille(s)+1)*sizeof(char));
				for (i=0; i<calculeTaille(s); i++) s1[i]=s[i];
				s1[calculeTaille(s)]='#';
			}

			else {
				s1 = malloc((calculeTaille(s))*sizeof(char));
				for (i=0; i<calculeTaille(s); i++) s1[i]=s[i];
			}

			if (finJeu==1) {
				printf("\n%s\n\n\nLe joueur blanc a gagne !!!\n\n\n",s1);
			}
			
			if (finJeu==2) {
				printf("\n%s\n\n\nLe joueur noir a gagne !!!\n\n\n",s1);
			}

			exit(0);
		}

		printf("Entrez un coup : ");
		s = recupereExpr(11);

		/*printf("%s\ncalculeTaille(s) : %d",s,calculeTaille(s));  */

		if (!analyseExprCoup(t,calculeTaille(s),s,configuration)) exit(3);

		finJeu = verifieFinJeu(t,configuration);

		n++;
	}
}

char * recupereExpr(int n) {
	char * s;

	s = malloc((n+1)*sizeof(char));

	fgets(s,n+1,stdin);

	return s;
}

int calculeTaille (char * s) {
	int i, cmp;

	cmp=0;

	for (i=0; (s[i]!='\0'&&s[i]!=' '); i++) cmp++;

	return cmp-1;
}

int analyseExprCoup (int t[][8], int taille, char * s, int configuration) {
	int i, p1, p2, cr, cc, slength, x1,x2,x3,x4,y1,y2,y3,y4, base, sens1, sens2, tmp, ct, plus_etoile;
	int rond_carre;
	char * s1;
	int * cChoix;
	int * t1;
	int t2[60];
	int t3[60];
	cChoix = malloc(1*sizeof(int));

	p1=0; p2=0; cr=0; cc=0; slength = taille; x1=0; x2=0; x3=0; x4=0; y1=0; y2=0; y3=0; y4=0; base=0; sens1=0; sens2=0; tmp=-1; ct=0; plus_etoile=0;
	rond_carre=0;
	t1 = malloc(2*sizeof(int));

	/*
		-plus_etoile : 0 : * (rond d'abord], 1 : + (carre d'abord)
	*/

	for (i=0; i<60; i++) {t2[i]=0; t3[i]=0;}

	if (slength<5) return 0;

	if (slength==6) {
		if (s[5]!='#') return 0; else {
			s1 = malloc (6*sizeof(char));
			for (i=0; i<5; i++) s1[i]=s[i];
			s1[5]='\0';
			free(s);
			s=malloc(6*sizeof(char));
			for (i=0; i<5; i++) s[i]=s1[i];
			s[5]='\0';
			free(s1);
			slength=5;
		}
	} /* on choisit de rendre l'opérateur # sans signification (le dépassement et la fin du jeu étant signalée par un message le cas échéant).  */

	if (slength>5 && s[2]!='*' && s[2]!='+') return 0;
	if (slength==9) {
		if (s[8]!='#') return 0; else {
			s1 = malloc (9*sizeof(char));
			for (i=0; i<8; i++) s1[i]=s[i];
			s1[8]='\0';
			free(s);
			s=malloc(9*sizeof(char));
			for (i=0; i<8; i++) s[i]=s1[i];
			s[8]='\0';
			free(s1);
			slength=8;
		}
	}

	if (slength==12) {
		if (s[11]!='#') return 0; else {
			s1 = malloc (11*sizeof(char));
			for (i=0; i<11; i++) s1[i]=s[i];
			s1[11]='\0';
			free(s);
			s=malloc(11*sizeof(char));
			for (i=0; i<11; i++) s[i]=s1[i];
			s[11]='\0';
			free(s1);
			slength=11;
		}
	}

	/*récupération des données*/

	/*deplacement de pions*/


	if (slength==5) {
		if (s[2]!='-') return 0;

		t1 = convertCoordonnees2(t1,s[0],convertNombre(s[1]));
		if (t1[0]>7 || t1[0]<0) return 0;
		if (t1[1]>7 || t1[1]<0) return 0;
		x1=t1[0];
		y1=t1[1];

		/*printf("t1[0] = %d\nt1[1] = %d\nx1 = %d\ny1 = %d\n",t1[0],t1[1],x1,y1);  */

		t1 = convertCoordonnees2(t1,s[3],convertNombre(s[4]));
		if (t1[0]>7 || t1[0]<0) return 0;
		if (t1[1]>7 || t1[1]<0) return 0;
		x2=t1[0];
		y2=t1[1];

		/*printf("t1[0] = %d\nt1[1] = %d\nx2 = %d\ny2 = %d",t1[0],t1[1],x2,y2);  */
	}

	/*deploiement*/

	if (slength>5) { /*deploiement  */
		if (slength==8) { /*2 pièces  */
			if (s[5]!='-') return 0;

			t1 = convertCoordonnees2(t1,s[0],convertNombre(s[1]));
			if (t1[0]>7 || t1[0]<0) return 0;
			if (t1[1]>7 || t1[1]<0) return 0;
			x1=t1[0];
			y1=t1[1];

			/*printf("t1[0] = %d\nt1[1] = %d\nx1 = %d\ny1 = %d",t1[0],t1[1],x1,y1);  */

			t1 = convertCoordonnees2(t1,s[3],convertNombre(s[4]));
			if (t1[0]>7 || t1[0]<0) return 0;
			if (t1[1]>7 || t1[1]<0) return 0;
			x2=t1[0];
			y2=t1[1];

			/*printf("t1[0] = %d\nt1[1] = %d\nx2 = %d\ny2 = %d",t1[0],t1[1],x2,y2);  */

			t1 = convertCoordonnees2(t1,s[6],convertNombre(s[7]));
			if (t1[0]>7 || t1[0]<0) return 0;
			if (t1[1]>7 || t1[1]<0) return 0;
			x3=t1[0];
			y3=t1[1];

			/*printf("t1[0] = %d\nt1[1] = %d\nx3 = %d\ny3 = %d",t1[0],t1[1],x3,y3);  */
		}

		if (slength==11) { /*3 pièces  */
			if (s[5]!='-' || s[8]!='-') return 0;

			t1 = convertCoordonnees2(t1,s[0],convertNombre(s[1]));
			if (t1[0]>7 || t1[0]<0) return 0;
			if (t1[1]>7 || t1[1]<0) return 0;
			x1=t1[0];
			y1=t1[1];

			t1 = convertCoordonnees2(t1,s[3],convertNombre(s[4]));
			if (t1[0]>7 || t1[0]<0) return 0;
			if (t1[1]>7 || t1[1]<0) return 0;
			x2=t1[0];
			y2=t1[1];

			t1 = convertCoordonnees2(t1,s[6],convertNombre(s[7]));
			if (t1[0]>7 || t1[0]<0) return 0;
			if (t1[1]>7 || t1[1]<0) return 0;
			x3=t1[0];
			y3=t1[1];

			/*printf("t1[0] = %d\nt1[1] = %d\nx3 = %d\ny3 = %d",t1[0],t1[1],x3,y3);  */

			t1 = convertCoordonnees2(t1,s[9],convertNombre(s[10]));
			if (t1[0]>7 || t1[0]<0) return 0;
			if (t1[1]>7 || t1[1]<0) return 0;
			x4=t1[0];
			y4=t1[1];

			/*printf("t1[0] = %d\nt1[1] = %d\nx4 = %d\ny4 = %d",t1[0],t1[1],x4,y4);  */
		}
	}

	/*printf("x1 = %d\ny1 = %d\nx2 = %d\ny2 = %d\nx3 = %d\ny3 = \nx4 = %d\ny4 = %d",x1,y1,x2,y2,x3,y3,x4,y4);  */

	/*analyse des données*/

	if (slength==5) {
		p1 = t[x1][y1];
		p2 = t[x2][y2];

		if (p1==0) return 0;

		if (p1>0 && p1<5) { /*pion simple  */
			if (configuration==0) {if (p1>0 && p1<3) /*blanc*/ base=1; else base=0;}
			if (configuration==1) {if (p1>0 && p1<3) /*blanc*/ base=0; else base=1;}

			if (p1==1 || p1==3) { /*rond  */
				if (base==0) {
					if (x2!=x1-1) return 0;

					if (y2!=y1-1 && y2!=y1+1) return 0;
					
					if (y2==y1-1) sens1=0; /*gauche devant  */
					if (y2==y1+1) sens1=1; /*droite devant  */
				}

				if (base==1) {
					if (x2!=x1+1) return 0;

					if (y2!=y1-1 && y2!=y1+1) return 0;
					
					if (y2==y1-1) sens1=0; /*gauche devant  */
					if (y2==y1+1) sens1=1; /*droite devant  */
				}
			}

			if (p1==2 || p1==4) { /*carre  */
				if (base==0) {
					if (x2!=x1-1 && y2!=y1-1 && y2!=y1+1) return 0;

					if (y2==y1-1) sens1=0; /*gauche  */
					if (y2==y1+1) sens1=1; /*droite  */
					if (x2==x1-1) sens1=2; /*milieu  */
				}

				if (base==1) {
					if (x2!=x1+1 && y2!=y1-1 && y2!=y1+1) return 0;

					if (y2==y1-1) sens1=0; /*gauche  */
					if (y2==y1+1) sens1=1; /*droite  */
					if (x2==x1+1) sens1=2; /*milieu  */
				}
			}

			return deplacePion(t,cChoix,base,sens1,x1,y1);
		}

		if (p1>4 && p1<19) { /*pion composé  */
			if (configuration==0) {if (p1>4 && p1<12) /*blanc*/ base=1; else base=0;}
			if (configuration==1) {if (p1>11 && p1<19) /*noir*/ base=0; else base=1;}

			if (p1==5||p1==12) {cr=2; cc=0;}
			if (p1==6||p1==13) {cr=0; cc=2;}
			if (p1==7||p1==14) {cr=1; cc=1;}
			if (p1==8||p1==15) {cr=3; cc=0;}
			if (p1==9||p1==16) {cr=0; cc=3;}
			if (p1==10||p1==17) {cr=2; cc=1;}
			if (p1==11||p1==18) {cr=1; cc=2;}

			rond_carre = (p1==7 || p1==10 || p1==11 || p1==14 || p1==17 || p1==18);

			if (p1==5 || p1==8 || p1==12 || p1==15 || rond_carre) {/*rond  */

				if (base==0) {
					if (cr==1 || cr==2 || cr==3) {
						t2[0]=1;

						if (x2!=x1-1) t2[0]=0;
						if (y2!=y1-1 && y2!=y1+1) t2[0]=0;
						
						if (y2==y1-1) t3[0]=0; /*gauche devant  */
						if (y2==y1+1) t3[0]=1; /*droite devant  */
					}

					if (cr==2 || cr==3) {
						if (x1-2<0 && y1-2<0) {
							t2[1]=1;
							if (x1!=x2 || y1!=y2) t2[1]=0;
							t3[1]=0;
						}

						if (x1-2<0 && y1+2>7) {
							t2[2]=1;
							if (x1!=x2 || y1!=y2) t2[2]=0;
							t3[2]=1;
						}

						if (x1-2<0) {
							t2[3]=1;
							if (y2!=y1-2 && y2!=y1+2) t2[3]=0;
							if (x2!=x1) t2[3]=0;

							if (y2==y1-2) t3[3]=0;
							if (y2==y1+2) t3[3]=1;
						}

						if (y1-2<0) {
							t2[4]=1;
							if (x2!=x1-2) t2[4]=0;
							if (y2!=y1) t2[4]=0;

							t3[4]=0;
						}

						if (y1+2>7) {
							t2[5]=1;
							if (x2!=x1-2) t2[5]=0;
							if (y2!=y1) t2[5]=0;

							t3[5]=1;
						}

						t2[6]=1;
						if (x2!=x1-2) t2[6]=0;
						if (y2!=y1-2 && y2!=y1+2) t2[6]=0;
						
						if (y2==y1-2) t3[6]=0; /*gauche devant  */
						if (y2==y1+2) t3[6]=1; /*droite devant  */
					}

					if (cr==3) {
						if (x1-2<0 && y1-2<0) {
							t2[7]=1;
							if (x2!=x1+1) t2[7]=0;
							if (y2!=y1+1) t2[7]=0;

							t3[7]=0;
						}

						if (x1-3<0 && y1-3<0) {
							t2[8]=1;
							if (x2!=x1-1) t2[8]=0;
							if (y2!=y1-1) t2[8]=0;

							t3[8]=0;
						}

						if (x1-2<0) {
							t2[9]=1;
							if (x2!=x1+1) t2[9]=0;
							if (y2!=y1-3 && y2!=y1+3) t2[9]=0;

							if (y2==y1-3) t3[9]=0;
							if (y2==y1+3) t3[9]=1;
						}

						if (x1-3<0) {
							t2[10]=1;
							if (x2!=x1-1) t2[10]=0;
							if (y2!=y1-3 && y2!=y1+3) t2[10]=0;

							if (y2==y1-3) t3[10]=0;
							if (y2==y1+3) t3[10]=1;
						}

						if (y1-2<0) {
							t2[11]=1;
							if (y2!=y1+1) t2[11]=0;
							if (x2!=x1-3) t2[11]=0;

							t3[11]=0;
						}

						if (y1-3<0) {
							t2[12]=1;
							if (y2!=y1-1) t2[12]=0;
							if (x2!=x1-3) t2[12]=0;

							t3[12]=1;
						}

						if (x1-2<0 && y1+2>7) {
							t2[13]=1;
							if (x2!=x1+1) t2[13]=0;
							if (y2!=y1-1) t2[13]=0;

							t3[13]=0;
						}

						if (x1-3<0 && y1+3>7) {
							t2[14]=1;
							if (x2!=x1-1) t2[14]=0;
							if (y2!=y1+1) t2[14]=0;

							t3[14]=0;
						}

						if (y1+2>7) {
							t2[15]=1;
							if (y2!=y1-1) t2[15]=0;
							if (x2!=x1-3) t2[15]=0;

							t3[15]=0;
						}

						if (y1+3>7) {
							t2[16]=1;
							if (y2!=y1+1) t2[16]=0;
							if (x2!=x1-3) t2[16]=0;

							t3[16]=1;
						}

						t2[17]=1;

						if (x2!=x1-3) t2[17]=0;
						if (y2!=y1-3 && y2!=y1+3) t2[17]=0;
						
						if (y2==y1-3) t3[17]=0; /*gauche devant  */
						if (y2==y1+3) t3[17]=1; /*droite devant  */
					}
				}

				if (base==1) {
					if (cr==1 || cr==2 || cr==3) {
						t2[18]=1;
						if (x2!=x1+1) t2[18]=0;
						if (y2!=y1-1 && y2!=y1+1) t2[18]=0;
						
						if (y2==y1-1) t3[18]=0; /*gauche devant  */
						if (y2==y1+1) t3[18]=1; /*droite devant  */
					}

					if (cr==2 || cr==3) {
						if (x1+2>7 && y1-2<0) {
							t2[19]=1;
							if (x1!=x2 || y1!=y2) t2[19]=0;
							t3[19]=0;
						}

						if (x1+2>7 && y1+2>7) {
							t2[20]=1;
							if (x1!=x2 || y1!=y2) t2[20]=0;
							t3[20]=1;
						}

						if (x1+2>7) {
							t2[21]=1;
							if (y2!=y1-2 && y2!=y1+2) t2[21]=0;
							if (x2!=x1) t2[21]=0;

							if (y2==y1-2) t3[21]=0;
							if (y2==y1+2) t3[21]=1;
						}

						if (y1-2<0) {
							t2[22]=1;
							if (x2!=x1+2) t2[22]=0;
							if (y2!=y1) t2[22]=0;

							t3[22]=0;
						}

						if (y1+2>7) {
							t2[23]=1;
							if (x2!=x1+2) t2[23]=0;
							if (y2!=y1) t2[23]=0;

							t3[23]=1;
						}

						t2[24]=1;

						if (x2!=x1+2) t2[24]=0;
						if (y2!=y1-2 && y2!=y1+2) t2[24]=0;
						
						if (y2==y1-2) t3[24]=0; /*gauche devant  */
						if (y2==y1+2) t3[24]=1; /*droite devant  */
					}

					if (cr==3) {
						if (x1+2>7 && y1-2<0) {
							t2[25]=1;
							if (x2!=x1-1) t2[25]=0;
							if (y2!=y1+1) t2[25]=0;

							t3[25]=0;
						}

						if (x1+3>7 && y1-3<0) {
							t2[26]=1;
							if (x2!=x1+1) t2[26]=0;
							if (y2!=y1-1) t2[26]=0;

							t3[26]=0;
						}

						if (x1+2>7 && y1+2>7) {
							t2[27]=1;
							if (x2!=x1-1) t2[27]=0;
							if (y2!=y1-1) t2[27]=0;

							t3[27]=0;
						}

						if (x1+3>7 && y1+3>7) {
							t2[28]=1;
							if (x2!=x1+1) t2[28]=0;
							if (y2!=y1+1) t2[28]=0;

							t3[28]=0;
						}

						if (x1+2>7) {
							t2[29]=1;
							if (x2!=x1-1) t2[29]=0;
							if (y2!=y1-3 && y2!=y1+3) t2[29]=0;

							if (y2==y1-3) t3[29]=0;
							if (y2==y1+3) t3[29]=1;
						}

						if (x1+3>7) {
							t2[30]=1;
							if (x2!=x1+1) t2[30]=0;
							if (y2!=y1-3 && y2!=y1+3) t2[30]=0;

							if (y2==y1-3) t3[30]=0;
							if (y2==y1+3) t3[30]=1;
						}

						if (y1-2<0) {
							t2[31]=1;
							if (y2!=y1+1) t2[31]=0;
							if (x2!=x1-3) t2[31]=0;

							t3[31]=0;
						}

						if (y1-3<0) {
							t2[32]=1;
							if (y2!=y1-1) t2[32]=0;
							if (x2!=x1-3) t2[32]=0;

							t3[32]=1;
						}

						if (y1+2>7) {
							t2[33]=1;
							if (y2!=y1-1) t2[33]=0;
							if (x2!=x1-3) t2[33]=0;

							t3[33]=0;
						}

						if (y1+3>7) {
							t2[34]=1;
							if (y2!=y1+1) t2[34]=0;
							if (x2!=x1-3) t2[34]=0;

							t3[34]=1;
						}

						t2[35]=1;
						if (x2!=x1+3) t2[35]=0;
						if (y2!=y1-3 && y2!=y1+3) t2[35]=0;
						
						if (y2==y1-3) t3[35]=0; /*gauche devant  */
						if (y2==y1+3) t3[35]=1; /*droite devant  */
						
					}
				}
			}

			if (p1==6 || p1==9 || p1==13 || p1==16 || rond_carre) {/*carre  */
				if (base==0) {
					if (cc==1 || cc==2 || cc==3) {
						t2[36]=1;
						if (y2==y1-1 && x2==x1) if (rond_carre) t3[36]=2; else t3[36]=0; /*gauche  */
						else if (y2==y1+1 && x2==x1) if (rond_carre) t3[36]=3; else t3[36]=1; /*droite  */
						else if (x2==x1-1 && y2==y1) if (rond_carre) t3[36]=4; else t3[36]=2; /*milieu  */
						else t2[36]=0;
					}

					if (cc==2 || cc==3) {
						if (x1-2<0) {
							t2[37]=1;
							if (x1!=x2) t2[37]=0;
							if (y1!=y2) t2[37]=0;

							if (rond_carre) t3[37]=4; else t3[37]=2;
						}

						if (y1-2<0) {
							t2[38]=1;
							if (x1!=x2) t2[38]=0;
							if (y1!=y2) t2[38]=0;

							if (rond_carre) t3[38]=2; else t3[38]=0;
						}

						if (y1+2>7) {
							t2[39]=1;
							if (x1!=x2) t2[39]=0;
							if (y1!=y2) t2[39]=0;

							if (rond_carre) t3[39]=3; else t3[39]=1;
						}
						
						t2[40]=1;
						if (y2==y1-2 && x2==x1) if (rond_carre) t3[40]=2; else t3[40]=0; /*gauche  */
						else if (y2==y1+2 && x2==x1) if (rond_carre) t3[40]=3; else t3[40]=1; /*droite  */
						else if (x2==x1-2 && y2==y1) if (rond_carre) t3[40]=4; else t3[40]=2; /*milieu  */
						else t2[40]=0;
					}

					if (cc==3) {
						if (x1-2<0) {
							t2[41]=1;
							if (x2!=x1+1) t2[41]=0;
							if (y2!=y1) t2[41]=0;

							if (rond_carre) t3[41]=4; else t3[41]=2;
						}

						if (x1-3<0) {
							t2[42]=1;
							if (x2!=x1-1) t2[42]=0;
							if (y2!=y1) t2[42]=0;

							if (rond_carre) t3[42]=4; else t3[42]=2;
						}

						if (y1-2<0) {
							t2[43]=1;
							if (y2!=y1+1) t2[43]=0;
							if (x2!=x1) t2[43]=0;

							if (rond_carre) t3[43]=2; else t3[43]=0;
						}

						if (y1-3<0) {
							t2[44]=1;
							if (y2!=y1-1) t2[44]=0;
							if (x2!=x1) t2[44]=0;

							if (rond_carre) t3[44]=2; else t3[44]=0;
						}

						if (y1+2>7) {
							t2[45]=1;
							if (y2!=y1-1) t2[45]=0;
							if (x2!=x1) t2[45]=0;

							if (rond_carre) t3[45]=3; else t3[45]=1;
						}

						if (y1+3>7) {
							t2[46]=1;
							if (y2!=y1+1) t2[46]=0;
							if (x2!=x1) t2[46]=0;

							if (rond_carre) t3[46]=3; else t3[46]=1;
						}
						
						t2[47]=1;
						if (y2==y1-3 && x2==x1) if (rond_carre) t3[47]=2; else t3[47]=0; /*gauche  */
						else if (y2==y1+3 && x2==x1) if (rond_carre) t3[47]=3; else t3[47]=1; /*droite  */
						else if (x2==x1-3 && y2==y1) if (rond_carre) t3[47]=4; else t3[47]=2; /*milieu  */
						else t2[47]=0;
					}
				}

				if (base==1) {
					if (cc==1 || cc==2 || cc==3) {
						t2[48]=1;
						if (y2==y1-1 && x2==x1) if (rond_carre) t3[48]=2; else t3[48]=0; /*gauche  */
						else if (y2==y1+1 && x2==x1) if (rond_carre) t3[48]=3; else t3[48]=1; /*droite  */
						else if (x2==x1+1 && y2==y1) if (rond_carre) t3[48]=4; else t3[48]=2; /*milieu  */
						else t2[48]=0;
					}

					if (cc==2 || cc==3) {
						if (x1+2>7) {
							t2[49]=1;
							if (x1!=x2) t2[49]=0;
							if (y1!=y2) t2[49]=0;

							if (rond_carre) t3[49]=4; else t3[49]=2;
						}

						if (y1-2<0) {
							t2[50]=1;
							if (x1!=x2) t2[50]=0;
							if (y1!=y2) t2[50]=0;

							if (rond_carre) t3[50]=2; else t3[50]=0;
						}

						if (y1+2>7) {
							t2[51]=1;
							if (x1!=x2) t2[51]=0;
							if (y1!=y2) t2[51]=0;

							if (rond_carre) t3[51]=3; else t3[51]=1;
						}
						
						t2[52]=1;
						if (y2==y1-2 && x2==x1) if (rond_carre) t3[52]=2; else t3[52]=0; /*gauche  */
						else if (y2==y1+2 && x2==x1) if (rond_carre) t3[52]=3; else t3[52]=1; /*droite  */
						else if (x2==x1+2 && y2==y1) if (rond_carre) t3[52]=4; else t3[52]=2; /*milieu  */
						else t2[52]=0;
					}

					if (cc==3) {
						if (x1+2>7) {
							t2[53]=1;
							if (x2!=x1-1) t2[53]=0;
							if (y2!=y1) t2[53]=0;

							if (rond_carre) t3[53]=4; else t3[53]=2;
						}

						if (x1+3>7) {
							t2[54]=1;
							if (x2!=x1+1) t2[54]=0;
							if (y2!=y1) t2[54]=0;

							if (rond_carre) t3[54]=4; else t3[54]=2;
						}

						if (y1-2<0) {
							t2[55]=1;
							if (y2!=y1+1) t2[55]=0;
							if (x2!=x1) t2[55]=0;

							if (rond_carre) t3[55]=2; else t3[55]=0;
						}

						if (y1-3<0) {
							t2[56]=1;
							if (y2!=y1-1) t2[56]=0;
							if (x2!=x1) t2[56]=0;

							if (rond_carre) t3[56]=2; else t3[56]=0;
						}

						if (y1+2>7) {
							t2[57]=1;
							if (y2!=y1-1) t2[57]=0;
							if (x2!=x1) t2[57]=0;

							if (rond_carre) t3[57]=3; else t3[57]=1;
						}

						if (y1+3>7) {
							t2[58]=1;
							if (y2!=y1+1) t2[58]=0;
							if (x2!=x1) t2[58]=0;

							if (rond_carre) t3[58]=3; else t3[58]=1;
						}
						
						t2[59]=1;
						if (y2==y1-3 && x2==x1) if (rond_carre) t3[59]=2; else t3[59]=0; /*gauche  */
						else if (y2==y1+3 && x2==x1) if (rond_carre) t3[59]=3; else t3[59]=1; /*droite  */
						else if (x2==x1+3 && y2==y1) if (rond_carre) t3[59]=4; else t3[59]=2; /*milieu  */
						else t2[59]=0;
					}
				}
			}
		}

		ct=0;

		for (i=0; i<60; i++) if (t2[i]==1) {
			tmp = t3[i];
			if (i==0 || i==18 || i==36 || i==48) ct=1;
			else if ((i>0 && i<7) || (i>18 && i<25) || (i>36 && i<41) || (i>48 && i<53)) ct=2;
			else if ((i>6 && i<18) || (i>24 && i<36) || (i>40 && i<48) || (i>52 && i<60)) ct=3;
		}

		if (tmp==-1) return 0; /*aucune réponse n'a été trouvée.		  */
		
		deplacePionCompose (t,cChoix,base,tmp,x1,y1,ct);
	}

	if (slength>5) { /*deploiement  */
		sens2=0;
		plus_etoile=0;

		p1=t[x1][y1];


		if (configuration==0) {if (p1>4 && p1<12) /*blanc*/ base=1; else base=0;}
		if (configuration==1) {if (p1>11 && p1<19) /*noir*/ base=0; else base=1;}

		if (slength==8) { /*2 pièces  */
			if (p1>0 && p1<5) return 0;

			if (p1==5 || p1==8 || p1==12 || p1==15) { /* rond  */
				if (base==0) {
					if (x2!=x1-1) return 0;
					if (x3!=x2-1) return 0;
					
					if (y2==y1-1) {if (y3!=y2-1) return 0; else sens1=0;}
					else if (y2==y1+1) {if (y3!=y2+1) return 0; else sens1=1;}
					else return 0;
				}
				
				if (base==1) {
					if (x2!=x1+1) return 0;
					if (x3!=x2+1) return 0;	
					
					if (y2==y1-1) {if (y3!=y2-1) return 0; else sens1=0;}
					else if (y2==y1+1) {if (y3!=y2+1) return 0; else sens1=1;}
					else return 0;
				}
			}

			if (p1==6 || p1==9 || p1==13 || p1==16) { /* carre  */
				if (base==0) {
					if (x2==x1-1 && y2==y1) {if (x3!=x2-1 && y3==y2) return 0; else sens1=2;}
					else if (y2==y1-1) {if (y3!=y2-1) return 0; else sens1=0;}
					else if (y2==y1+1) {if (y3!=y2+1) return 0; else sens1=1;}
					else return 0;
				}
				
				if (base==1) {
					if (x2==x1+1 && y2==y1) {if (x3!=x2+1 && y3==y2) return 0; else sens1=2;}
					else if (y2==y1-1 && x2==x1) {if (y3!=y2-1 && x3==x2) return 0; else sens1=0;}
					else if (y2==y1+1 && x2==x1) {if (y3!=y2+1 && x3==x2) return 0; else sens1=1;}
					else return 0;
				}
			}

			if (p1==7 || p1==10 || p1==11 || p1==14 || p1==17 || p1==18) { /* rond-carre  */
				if (s[2]=='*') plus_etoile=0;
				if (s[2]=='+') plus_etoile=1;

				if (plus_etoile==0) { /*rond d'abord  */
					if (base==0) {
						if (x2!=x1-1) return 0;
						
						if (y2==y1-1) sens1=0;
						else if (y2==y1+1) sens1=1;
						else return 0;
					}
					
					if (base==1) {
						if (x2!=x1+1) return 0;
						
						if (y2==y1-1) sens1=0;
						else if (y2==y1+1) sens1=1;
						else return 0;
					}

					if (base==0) {
						if (x3==x2-1 && y3==y2) sens2=2;
						else if (y3==y2-1 && x3==x2) sens2=0;
						else if (y3==y2+1 && x3==x2) sens2=1;
						else return 0;
					}
					
					if (base==1) {
						if (x3==x2+1 && y3==y2) sens2=2;
						else if (y3==y2-1 && x3==x2) sens2=0;
						else if (y3==y2+1 && x3==x2) sens2=1;
						else return 0;
					}
				}

				if (plus_etoile==1) { /*carre d'abord  */
					if (base==0) {
						if (x2==x1-1 && y2==y1) sens1=2;
						else if (y2==y1-1 && x2==x1) sens1=0;
						else if (y2==y1+1 && x2==x1) sens1=1;
						else return 0;
					}
					
					if (base==1) {
						if (x2==x1+1 && y2==y1) sens1=2;
						else if (y2==y1-1 && x2==x1) sens1=0;
						else if (y2==y1+1 && x2==x1) sens1=1;
						else return 0;
					}

					if (base==0) {
						if (x3!=x2-1) return 0;
						
						if (y3==y2-1) sens2=0;
						else if (y3==y2+1) sens2=1;
						else return 0;
					}
					
					if (base==1) {
						if (x3!=x2+1) return 0;	
						
						if (y3==y2-1) sens2=0;
						else if (y3==y2+1) sens2=1;
						else return 0;
					}
				}
			}

			if (!detecteDeploiement (t,base,plus_etoile,sens1,sens2,x1,y1)) return 0;
			deploiePion (t,base,plus_etoile,sens1,sens2,x1,y1);

			return 1;
		}

		if (slength==11) { /*3 pièces  */
			if (p1>0 && p1<5) return 0;

			if (p1==5 || p1==8 || p1==12 || p1==15) { /* rond  */
				if (base==0) {
					if (x2!=x1-1) return 0;
					if (x3!=x2-1) return 0;
					if (x4!=x3-1) return 0;
					
					if (y2==y1-1) {if (y3!=y2-1) return 0; else if (y4!=y3-1) return 0; else sens1=0;}
					else if (y2==y1+1) {if (y3!=y2+1) return 0; else if (y4!=y3+1) return 0; else sens1=1;}
					else return 0;
				}
				
				if (base==1) {
					if (x2!=x1+1) return 0;
					if (x3!=x2+1) return 0;
					if (x4!=x3+1) return 0;
					
					if (y2==y1-1) {if (y3!=y2-1) return 0; else if (y4!=y3-1) return 0; else sens1=0;}
					else if (y2==y1+1) {if (y3!=y2+1) return 0; else if (y4!=y3+1) return 0; else sens1=1;}
					else return 0;
				}
			}

			if (p1==6 || p1==9 || p1==13 || p1==16) { /* carre  */
				if (base==0) {
					if (x2==x1-1 && y2==y1) {if (x3!=x2-1 && y3==y2) return 0; else if (x4!=x3-1 && y4==y3) return 0; else sens1=2;}
					else if (y2==y1-1 && x2==x1) {if (y3!=y2-1 && x3==x2) return 0; else if (y4!=y3-1 && x4==x3) return 0; else sens1=0;}
					else if (y2==y1+1 && x2==x1) {if (y3!=y2+1 && x3==x2) return 0; else if (y4!=y3+1 && x4==x3) return 0; else sens1=1;}
					else return 0;
				}
				
				if (base==1) {
					if (x2==x1+1 && y2==y1) {if (x3!=x2+1 && y3==y2) return 0; else if (x4!=x3+1 && y4==y3) return 0; else sens1=2;}
					else if (y2==y1-1 && x2==x1) {if (y3!=y2-1 && x3==x2) return 0; else if (y4!=y3-1 && x4==x3) return 0; else sens1=0;}
					else if (y2==y1+1 && x2==x1) {if (y3!=y2+1 && x3==x2) return 0; else if (y4!=y3+1 && x4==x3) return 0; else sens1=1;}
					else return 0;
				}
			}

			if (p1==7 || p1==10 || p1==11 || p1==14 || p1==17 || p1==18) { /* rond-carre  */
				if (s[2]=='*') plus_etoile=0;
				if (s[2]=='+') plus_etoile=1;

				if (p1==10 || p1==17) { /*double rond - carre  */
					if (plus_etoile==0) { /*rond d'abord  */
						if (base==0) {
							if (x2!=x1-1) return 0;
							if (x3!=x2-1) return 0;
							
							if (y2==y1-1) {if (y3!=y2-1) return 0; else sens1=0;}
							else if (y2==y1+1) {if (y3!=y2+1) return 0; else sens1=1;}
							else return 0;
						}
						
						if (base==1) {
							if (x2!=x1+1) return 0;
							if (x3!=x2+1) return 0;	
							
							if (y2==y1-1) {if (y3!=y2-1) return 0; else sens1=0;}
							else if (y2==y1+1) {if (y3!=y2+1) return 0; else sens1=1;}
							else return 0;
						}

						if (base==0) {
							if (x4==x3-1 && y4==y3) sens2=2;
							else if (y4==y3-1 && x4==x3) sens2=0;
							else if (y4==y3+1 && x4==x3) sens2=1;
							else return 0;
						}
						
						if (base==1) {
							if (x4==x3+1 && y4==y3) sens2=2;
							else if (y4==y3-1 && x4==x3) sens2=0;
							else if (y4==y3+1 && x4==x3) sens2=1;
							else return 0;
						}
					}

					if (plus_etoile==1) { /*carre d'abord  */
						if (base==0) {
							if (x2==x1-1 && y2==y1) sens1=2;
							else if (y2==y1-1 && x2==x1) sens1=0;
							else if (y2==y1+1 && x2==x1) sens1=1;
							else return 0;
						}
						
						if (base==1) {
							if (x2==x1+1 && y2==y1) sens1=2;
							else if (y2==y1-1 && x2==x1) sens1=0;
							else if (y2==y1+1 && x2==x1) sens1=1;
							else return 0;
						}

						if (base==0) {
							if (x3!=x2-1) return 0;
							if (x4!=x3-1) return 0;
							
							if (y3==y2-1) {if (y4!=y3-1) return 0; else sens2=0;}
							else if (y3==y2+1) {if (y4!=y3+1) return 0; else sens2=1;}
							else return 0;
						}
						
						if (base==1) {
							if (x3!=x2+1) return 0;
							if (x4!=x3+1) return 0;	
							
							if (y3==y2-1) {if (y4!=y3-1) return 0; else sens2=0;}
							else if (y3==y2+1) {if (y4!=y3+1) return 0; else sens2=1;}
							else return 0;
						}
					}
				}

				if (p1==11 || p1==18) { /*double carre - rond  */
					if (plus_etoile==0) { /*rond d'abord  */
						if (base==0) {
							if (x2!=x1-1) return 0;
							
							if (y2==y1-1) sens1=0;
							else if (y2==y1+1) sens1=1;
							else return 0;
						}
						
						if (base==1) {
							if (x2!=x1+1) return 0;
							
							if (y2==y1-1) sens1=0;
							else if (y2==y1+1) sens1=1;
							else return 0;
						}

						if (base==0) {
							if (x3==x2-1 && y3==y2) {if (x4!=x3-1 && y4==y3) return 0; else sens2=2;}
							else if (y3==y2-1 && x3==x2) {if (y4!=y3-1 && x4==x3) return 0; else sens2=0;}
							else if (y3==y2+1 && x3==x2) {if (y4!=y3+1 && x4==x3) return 0; else sens2=1;}
							else return 0;
						}
						
						if (base==1) {
							if (x3==x2+1 && y3==y2) {if (x4!=x3+1 && y4==y3) return 0; else sens2=2;}
							else if (y3==y2-1 && x3==x2) {if (y4!=y3-1 && x4==x3) return 0; else sens2=0;}
							else if (y3==y2+1 && x3==x2) {if (y4!=y3+1 && x4==x3) return 0; else sens2=1;}
							else return 0;
						}
					}

					if (plus_etoile==1) { /*carre d'abord  */
						if (base==0) {
							if (x2==x1-1 && y2==y1) {if (x3!=x2-1 && y3==y2) return 0; else sens1=2;}
							else if (y2==y1-1 && x2==x1) {if (y3!=y2-1 && x3==x2) return 0; else sens1=0;}
							else if (y2==y1+1 && x2==x1) {if (y3!=y2+1 && x3==x2) return 0; else sens1=1;}
							else return 0;
						}
						
						if (base==1) {
							if (x2==x1+1 && y2==y1) {if (x3!=x2+1 && y3==y2) return 0; else sens1=2;}
							else if (y2==y1-1 && x2==x1) {if (y3!=y2-1 && x3==x2) return 0; else sens1=0;}
							else if (y2==y1+1 && x2==x1) {if (y3!=y2+1 && x3==x2) return 0; else sens1=1;}
							else return 0;
						}

						if (base==0) {
							if (x4!=x3-1) return 0;
							
							if (y4==y3-1) sens2=0;
							else if (y4==y3+1) sens2=1;
							else return 0;
						}
						
						if (base==1) {
							if (x4!=x3+1) return 0;	
							
							if (y4==y3-1) sens2=0;
							else if (y4==y3+1) sens2=1;
							else return 0;
						}
					}
				}
			}

			if (!detecteDeploiement (t,base,plus_etoile,sens1,sens2,x1,y1)) return 0;
			deploiePion (t,base,plus_etoile,sens1,sens2,x1,y1);

			return 1;
		}
	}

	return 1;
	
}

void remplitTabbleau (int t[][8], int configuration) {/*remplit le tableau avec la configuration initiale du plateau de jeu*/
	int i,j;

	pions = malloc(sizeof(int)*18);

	for (i=0; i<4; i++) pions[i] = 8; /* initialisation du nombre de pions  */

	for (i=0; i<8; i++) for (j=0; j<8; j++) t[i][j]=0;

	if (configuration==0) {
		for (j=0; j<8; j+=2)
		t[0][j]=1;
		
		for (j=1; j<8; j+=2)
		t[1][j]=1;
		
		for (j=1; j<8; j+=2)
		t[0][j]=2;
		
		for (j=0; j<8; j+=2)
		t[1][j]=2;
		
		
		
		for (j=0; j<8; j+=2)
		t[6][j]=3;
		
		for (j=1; j<8; j+=2)
		t[7][j]=3;
		
		for (j=1; j<8; j+=2)
		t[6][j]=4;
		
		for (j=0; j<8; j+=2)
		t[7][j]=4;
	}
	else {
		for (j=0; j<8; j+=2)
		t[0][j]=3;
		
		for (j=1; j<8; j+=2)
		t[1][j]=3;
		
		for (j=1; j<8; j+=2)
		t[0][j]=4;
		
		for (j=0; j<8; j+=2)
		t[1][j]=4;
		
		
		
		for (j=0; j<8; j+=2)
		t[6][j]=1;
		
		for (j=1; j<8; j+=2)
		t[7][j]=1;
		
		for (j=1; j<8; j+=2)
		t[6][j]=2;
		
		for (j=0; j<8; j+=2)
		t[7][j]=2;
	}
}

void Jeu () {
	int finJeu;
	int tmp;
	int couleur;
	int coupJoue;
	int esp;
	int configuration;
	int commence;
	int base;
	int q;
	int qo;
	int afCoordonnees;

	int t10[8][8];

	finJeu=0;
	tmp=0;
	couleur = 0;
	coupJoue = 0;
	esp = 3;
	configuration = 0;
	commence=0;
	
	base = 0;
	if (configuration==0) base = (couleur==0)?1:0;
	if (configuration==1) base = (couleur==0)?0:1;

	/*
			Habituellement, j'utilise la variable q (commme question) pour les menus : 

				-q = menu
				-qo = menu options.
		*/

	/*noir : rond = 1, carré = 2;  */
	/*blanc : rond = 3, carré = 4;  */

	q = 0;
	qo = 0;
	afCoordonnees = 1;

	/*affiche(t10,afCoordonnees,esp);  */

	while (1) {
		q = menuPrincipal ();

		if (q==1) {
			if (commence==0) couleur=0;
			else couleur=1;				

			finJeu = 0;

			remplitTabbleau(t10,configuration);

			affiche(t10,afCoordonnees,esp);

			couleur = commence;

			coupJoue = 3;
			
			while (coupJoue!=2 && finJeu==0) {
				if (configuration==0) base = (couleur==0)?1:0;
				else base = (couleur==0)?0:1;

				while (coupJoue==3) {
					coupJoue=joueUnCoup(esp,couleur,base,afCoordonnees,t10);
				}					
				
				printf(coupJoue+"\n");

				if (couleur==1) couleur=0; else couleur=1; /*échange de variable couleur.  */

				affiche(t10,afCoordonnees,esp);

				if (coupJoue!=2) coupJoue=3;

				finJeu = verifieFinJeu(t10,configuration);

				if (finJeu!=0) {
					if (finJeu==1) {
						printf("\n\nFelicitations : \n\nLes blancs ont gagne !!!\n\n");
					}
					
					if (finJeu==2) {
						printf("\n\nFelicitations : \n\nLes noirs ont gagne !!!\n\n");
					}
				}
			}				
		}


		if (q==2) {
			qo=0;
			
			while (qo!=1&&qo!=2&&qo!=3&&qo!=4&&qo!=5) {
				qo = demandeOptions (configuration, commence);
				
				if (qo==1) {
					tmp = OptionsCoordonees ();
					
					if (tmp!=3) afCoordonnees = tmp;
					qo=0;
				}
				
				if (qo==2) {
					esp = OptionsNombreDespaces (esp);
					qo=0;
				}

				if (qo==3) {
					tmp = demandePlacement ();

					if (tmp!=3) configuration = tmp-1;
					qo=0;
				}

				if (qo==4) {
					tmp = demandeCommence ();

					if (tmp!=3) commence = tmp-1;
					qo=0;
				}
			}
		}
	}
}

int verifiePointCouleur (int couleur, int t[][8], int x, int y) {
	/*0 : blanc, 1 : noir  */

	int n;
	n=t[x][y];

	if (couleur==0) return ((n>0&&n<3)||(n>4&&n<12));

	else if (couleur==1) return ((n>2&&n<5)||(n>11&&n<19));

	else return 0;
}

int verifieFinJeu (int t[][8], int configuration) {
	int i, g1, g2;
	g1=0; g2=0;

	/*
			0 : pas de gagnant
			1 : les blancs ont gagné
			2 : les noirs ont gagné.

			-g1 : nombre de pions blancs
			-g2 : nombre de pions noirs

			-configuration : 0 : blancs en haut, noirs en bas, 1 : blancs en bas, noirs en haut.
		*/

	g1 = pions[0]+pions[1];
	for (i=4; i<11; i++) g1=g1+pions[i];

	g2 = pions[2]+pions[3];
	for (i=11; i<18; i++) g2=g2+pions[i];

	if (g1==0) return 2;
	else if (g2==0) return 1;
	else { /*g1!=0 et g2!=0  */
		for (i=0; i<7; i++) {
			if (configuration==0) if (t[0][i]==3 || t[0][i]==4 || (t[0][i]>11&&t[0][i]<19)) return 2;
			if (configuration==1) if (t[0][i]==1 || t[0][i]==2 || (t[0][i]>4&&t[0][i]<12)) return 1;
		}

		for (i=0; i<7; i++) {
			if (configuration==1) if (t[7][i]==3 || t[7][i]==4 || (t[7][i]>11&&t[7][i]<19)) return 2;
			if (configuration==0) if (t[7][i]==1 || t[7][i]==2 || (t[7][i]>4&&t[7][i]<12)) return 1;
		}

		return 0;
	}	
}

int verifiePionFranchisLigne (int t[][8], int configuration) {
	int i;

	for (i=0; i<7; i++) {
		if (configuration==0) if (t[0][i]==3 || t[0][i]==4 || (t[0][i]>11&&t[0][i]<19)) return 2;
		if (configuration==1) if (t[0][i]==1 || t[0][i]==2 || (t[0][i]>4&&t[0][i]<12)) return 1;
	}

	for (i=0; i<7; i++) {
		if (configuration==1) if (t[7][i]==3 || t[7][i]==4 || (t[7][i]>11&&t[7][i]<19)) return 2;
		if (configuration==0) if (t[7][i]==1 || t[7][i]==2 || (t[7][i]>4&&t[7][i]<12)) return 1;
	}

	return 0;
}

int joueUnCoup (int lignes, int couleur, int base, int coordonnees,int t[][8]) {
	/*0 : blanc, 1 : noir  */
	/*base : 0 : bas, 1 : haut  */

	int i, qj,qs,ok, cmp, cr, cc, ct, a, n, x, y, sens, p, cSens1, cSens2, cChoixI, p1,forme;
	char c=0;
	char * c3;
	int * cChoix;
	int * a1;
	int * t5;

	int retour=1;

	qj=0; qs=0; ok=1; cmp=0; cr=0; cc=0; ct=0; a=0; n=0; x=-1; y=-1; sens=0; p=0; cSens1=0; cSens2=0; cChoixI=0; p1=0;
	c=0;
	c3 = malloc(sizeof(char)*1);
	cChoix = malloc(sizeof(int)*4);
	t5 = malloc(sizeof(int)*2);

	retour=1;

	printf("\nC'est au joueur ");
	if (couleur==0) printf("blanc");
	else printf("noir");
	printf(" de jouer :\n");

	qj = MenuCoup(); /*question jeu  */

	if (qj==2) {
		qs = EtesVousSur (); /*etes-vous sur de vouloir quitter  */

		if (qs==1) return 2;

		else return 3;
	}

	if (qj==1) {
		cmp=0;

		while (retour) {

			retour=0;

			a=0; n=0; x=-1; y=-1; sens=0; p=0;
			c=0;

			while (x<0 || y<0 || x>7 || y>7) {
				if (coordonnees==1) {
					printf("Veuillez entrer les coordonees de \nvotre coups : \nx = ");
					getchar();

					c = getchar();

					printf("\ny = ");
					scanf("%d",&n);
				}

				else {
					x=-1;
					
					while (x<0 || x>7) {
						printf("Veuillez entrer les coordonees de \nvotre coups  : \nLigne = ");
						scanf("%d",&x);
						x-=1;
					}
					
					y=-1;
					
					while (y<0 || y>7) {
						printf("Colonne = ");
						scanf("%d",&y);
						y-=1;
					}
					
					if (!(x<0 || y<0 || x>7 || y>7)) {
						if (t[x][y]==0) {printf("Il n'y a aucune piece a cet endroit.\n"); /*--*/ x=-1; /*rejoue le while*/ }
						else if (!verifiePointCouleur(couleur,t,x,y)) {printf("\nErreur de couleurs\n"); /*--*/ x=-1; /*rejoue le while*/ }
					}
				}
				
				if (coordonnees==1) {			
					t5 = convertCoordonnees3(c,n);
					
					x=t5[0];
					y=t5[1];

					free(t5);

					if (!(x<0 || y<0 || x>7 || y>7)) {
						if (t[x][y]==0) {printf("Il n'y a aucune piece a cet endroit.\n"); /*--*/ x=-1; /*rejoue le while*/ }
						else if (!verifiePointCouleur(couleur,t,x,y)) {printf("\nErreur de couleurs\n"); /*--*/ x=-1; /*rejoue le while*/ }
					}
				}

				cmp++;

				if (cmp>=lignes) {
					cmp=0;
					affiche (t,coordonnees,lignes);
					printf("\n");
				}
			}

			p = t[x][y];

			/*printf("p = %d\n",p);		  */

			printf("\nsens = ");

			if (p==1 || p==3 || p==5 || p==12 || p==8 || p==15) {
				if (p==1 || p==3) {
					a=0;

					while (a!=1 && a!=2 && a!=3) {
						a=0;

						printf("\n1 : Gauche devant\n2 : Droite devant\n3 : Choisir un autre piece\n? = ");
						scanf("%d",&a);
					}

					sens = a;
				}

				else {
					a=0;

					while (a!=1 && a!=2 && a!=3 && a!=4) {
						a=0;

						printf("\n1 : Gauche devant\n2 : Droite devant\n3 : Deploiement\n4 : Choisir un autre piece\n? = ");
						scanf("%d",&a);
					}

					sens = a;
				}
			}

			else if (p==2||p==4||p==6 || p==13 || p==9 || p==16) {
				if (p==2||p==4) {
					a=0;

					while (a!=1 && a!=2 && a!=3 && a!=4) {
						a=0;

						printf("\n1 : Gauche\n2 : Droite\n3 : Milieu\n4 : Choisir une autre case\n? = ");
						scanf("%d",&a);
					}

					sens = a;
				}

				else {
					a=0;

					while (a!=1 && a!=2 && a!=3 && a!=4 && a!=5) {
						a=0;

						printf("\n1 : Gauche\n2 : Droite\n3 : Milieu\n4 : Deploiement\n5 : Choisir une autre case\n? = ");
						scanf("%d",&a);
					}

					sens = a;
				}
			}

			else if (p==7 || p==14 || p==10 || p==17 || p==11 || p==18) {
				while (a!=1 && a!=2 && a!=3 && a!=4 && a!=5 && a!=6 && a!=7) {
					a=0;

					printf("\n1 : Gauche devant\n2 : Droite devant\n3 : Gauche\n4 : Droite\n5 : Milieu\n6 : Deploiement\n7 : Choisir une autre case\n? = ");
					scanf("%d",&a);
				}

				sens = a;			
			}

			/*printf("base = "+base+"\nOk1.\n");  */

			a1 = malloc(sizeof(int)*5);

			a1[0]=(p==1 || p==3)&&(sens==3);
			a1[1]=(p==2 || p==4)&&(sens==4);
			a1[2]=(p==5 || p==12 || p==8 || p==15)&&(sens==4); /*L'une des  */
			a1[3]=(p==6 || p==13 || p==9 || p==16)&&(sens==5); /*configurations  */
			a1[4]=(p==7 || p==14 || p==10 || p==17 || p==11 || p==18)&&(sens==7); /*a repondu "Choisir une autre case".  */

			if (a1[0]||a1[1]||a1[2]||a1[3]||a1[4]) {
				retour = 1;

				x=-1;
			}

			else {
				free(a1);					
				a1 = malloc(sizeof(int)*3);
				
				a1[0]=(p==5 || p==12 || p==8 || p==15)&&(sens==3); /*L'une des  */
				a1[1]=(p==6 || p==13 || p==9 || p==16)&&(sens==4); /*configurations  */
				a1[2]=(p==7 || p==14 || p==10 || p==17 || p==11 || p==18)&&(sens==6); /*a repondu "Choisir une autre case".  */

				if (a1[0] || a1[1] || a1[2]) {
					if (!DemandeDeploiePion (lignes,cChoix,coordonnees,t,base,x,y)) {
						printf("Impossible de deployer cette piece a cet endroit.");
						retour = 1;
						ok=0;
					}

					else {
						cSens1 = cChoix[0];
						cSens2 = cChoix[1];
						cChoixI = cChoix[2];
						p1 = cChoix[3];

						if (p1==5||p1==12) {cr=2; cc=0;}
						if (p1==6||p1==13) {cr=0; cc=2;}
						if (p1==7||p1==14) {cr=1; cc=1;}
						if (p1==8||p1==15) {cr=3; cc=0;}
						if (p1==9||p1==16) {cr=0; cc=3;}
						if (p1==10||p1==17) {cr=2; cc=1;}
						if (p1==11||p1==18) {cr=1; cc=2;}

						if (cr+cc==2) {free(c3); c3 = malloc(sizeof(char)*8);}
						if (cr+cc==3) {free(c3); c3 = malloc(sizeof(char)*11);}

						if (publieDeploiePion (t,c3,base,cChoixI,cSens1,cSens2,x,y,p1)) {
							if (cr+cc==2) for (i=0; i<8; i++) printf("%d",c3[i]);
							if (cr+cc==3) for (i=0; i<11; i++) printf("%d",c3[i]);
							printf("\n");
						}
					}
				}

				else {
					if (p>0 && p<5) {
						free(cChoix);
						cChoix = malloc(sizeof(int)*1);

						if (!deplacePion (t, cChoix, base, sens-1, x,y)) {retour = 1; ok=0;} /*si le coup n'est pas conforme, on redemande a l'utilisateur d'entrer des coordonnees de son coup.  */
						else {
							free(c3);
							c3 = malloc(sizeof(char)*5);
							forme = cChoix[0];

							if (publieDeplacePion(t, c3, base, sens-1, x,y,forme)) {
								for (i=0; i<5; i++) printf("%d",c3[i]);
								printf("\n");
							}								
						}
					}
					
					if (!(p>0 && p<5)) {
						sens--;
						if (p==5||p==12) {cr=2; cc=0;}
						if (p==6||p==13) {cr=0; cc=2;}
						if (p==7||p==14) {cr=1; cc=1;}
						if (p==8||p==15) {cr=3; cc=0;}
						if (p==9||p==16) {cr=0; cc=3;}
						if (p==10||p==17) {cr=2; cc=1;}
						if (p==11||p==18) {cr=1; cc=2;}

						if (cr<2 && cc>1) {
							if (cr==0) cc=demandeDeplaceCompose(cc); /*(3-2) carres, (0-1) rond(s).  */
							if (cr==1) if (sens>1) cc=demandeDeplaceCompose(cc); /*(3-2) carres, (0-1) rond(s).  */
						}
						
						if (cc<2 && cr>1) {
							if (cc==0) cr=demandeDeplaceCompose(cr); /*(3-2) ronds, (0-1) carre(s).  */
							if (cc==1) if (sens<2) cr=demandeDeplaceCompose(cr); /*(3-2) ronds, (0-1) carre(s).  */
						}

						ct=1;

						if (p==5 || p==8 || p==12 || p==15) ct=cr; /*rond  */
						if (p==6 || p==9 || p==13 || p==16) ct=cc; /*carre  */
						if (p==7 || p==10 || p==11 || p==14 || p==17 || p==18) { /*rond-carre  */
							if (sens<2) ct=cr; /*rond  */
							if (sens>1) ct=cc; /*carre  */
						}

						free(cChoix);
						cChoix = malloc(sizeof(int)*1);

						if (!deplacePionCompose(t, cChoix, base, sens, x,y,ct)) {retour = 1; ok=0;}
						else {
							free(c3);
							c3 = malloc(sizeof(char)*5);

							p1=cChoix[0];

							if (publieDeplacePionCompose(c3,t,base,sens,x,y,ct,p1)) {
								for (i=0; i<5; i++) printf("%d",c3[i]);
								printf("\n");
							}
						}
					}

				}

				cmp++;

				if (cmp>=lignes) {
					cmp=0;
					affiche (t,coordonnees,lignes);
					printf("\n");
				}
			}
		}
	}

	return ok;
}

int demandeBase () {
	int a;
	a=0;

	while (a!=1 && a!=2) {
		a=0;

		printf("Souhaitez-vous jouer en haut ou en bas du plateau ?\n\n1 : Haut\n2 : Bas\n? = ");
		scanf("%d",&a);
	}

	return a;
}

int demandeMode () {
	int a;
	a=0;

	while (a!=1 && a!=2 && a!=3) {
		a=0;

		printf("En quel mode souhaitez-vous jouer ?\n\n1 : Vous contre l'ordinateur\n2 : Vous contre un autre humain\n3 : L'ordinateur contre lui-meme\n? = ");
		scanf("%d",&a);
	}

	return a;
}

int demandeCouleur () {
	int a;
	a=0;

	while (a!=1 && a!=2) {
		a=0;

		printf("Vous souhaitez jouer avec : \n1 : Les noirs\n2 : Les Blancs\n? = ");
		scanf("%d",&a);
	}

	return a;
}

int deplacePion (int t[][8], int * cChoix, int base, int sens, int x, int y) {
	/*

		-forme : 0 : rond, 1 : carré
		-base : haut ou bas de l'échiquier. 0 : bas, 1 : haut

		-sens : -rond : 0 : gauche, 1 : droite
			-carré : 0 : gauche, 1 : droite, 3 : devant.

		*/

	int forme=0;		


	if (x>7||y>7||x<0||y<0) {printf("x>7||y>7||x<0||y<0\n"); return 0;} /*Vérifiaction des coordonnées.  */


	if (t[x][y]==1||t[x][y]==3) {/*printf("t[x][y]==0||t[x][y]==3\n");*/ forme=0;} if (t[x][y]==2||t[x][y]==4) {/*printf("t[x][y]==1||t[x][y]==4\n");*/ forme=1;}

	cChoix[0]=forme;

	if (forme>1||forme<0) return 0; /*Vérifiaction de la forme.  */

	if (forme==0) { /*rond  */
		if (sens<0||sens>1) {/*printf("sens<0||sens>1\n");*/ return 0;}

		if (base==0) {
			if (sens==0) {
				if (x-1<0||y-1<0||detectePionSature(t,x,y,x-1,y-1)) {printf("x-1<0||y-1<0"); return 0;}

				else {
					t[x-1][y-1]=transformeUnPion(t,x,y,x-1,y-1);

					t[x][y]=0;

					return 1;
				}
			}
			
			if (sens==1) {
				if (x-1<0||y+1>7||detectePionSature(t,x,y,x-1,y+1)) {printf("x-1<0||y+1>7"); return 0;}

				else {
					t[x-1][y+1]=transformeUnPion(t,x,y,x-1,y+1);

					t[x][y]=0;

					return 1;
				}
			}
		}

		else if (base==1) {
			if (sens==0) {
				if (x+1>7||y-1<0||detectePionSature(t,x,y,x+1,y-1)) {printf("x+1>7||y-1<0"); return 0;}

				else {
					t[x+1][y-1]=transformeUnPion(t,x,y,x+1,y-1);

					t[x][y]=0;

					return 1;
				}
			}
			
			if (sens==1) {
				if (x+1>7||y+1>7||detectePionSature(t,x,y,x+1,y+1)) {printf("x+1>7||y+1>7"); return 0;}

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
		if (sens<0||sens>2) {printf("sens<0||sens>2\n"); return 0;}

		if (base==0) {
			if (sens==0) {
				if (y-1<0||detectePionSature(t,x,y,x,y-1)) {printf("y-1<0"); return 0;}

				else {
					t[x][y-1]=transformeUnPion(t,x,y,x,y-1);

					t[x][y]=0;

					return 1;
				}
			}
			
			if (sens==1) {
				if (y+1>7||detectePionSature(t,x,y,x,y+1)) {printf("y+1>7"); return 0;}

				else {
					t[x][y+1]=transformeUnPion(t,x,y,x,y+1);

					t[x][y]=0;

					return 1;
				}
			}

			if (sens==2) {
				if (x-1<0||detectePionSature(t,x,y,x-1,y)) {printf("x-1<0"); return 0;}

				else {
					t[x-1][y]=transformeUnPion(t,x,y,x-1,y);

					t[x][y]=0;

					return 1;
				}
			}
		}

		else if (base==1) {
			if (sens==0) {
				if (y-1<0||detectePionSature(t,x,y,x,y-1)) {printf("y-1<0"); return 0;}

				else {
					t[x][y-1]=transformeUnPion(t,x,y,x,y-1);

					t[x][y]=0;

					return 1;
				}
			}
			
			if (sens==1) {
				if (y+1>7||detectePionSature(t,x,y,x,y+1)) {printf("y+1>7"); return 0;}

				else {
					t[x][y+1]=transformeUnPion(t,x,y,x,y+1);

					t[x][y]=0;

					return 1;
				}
			}

			if (sens==2) {
				if (x+1>7||detectePionSature(t,x,y,x+1,y)) {printf("x+1>7"); return 0;}

				else {
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

int deplacePionTest (int t[][8], int base, int sens, int x, int y) {
	/*

		-forme : 0 : rond, 1 : carré
		-base : haut ou bas de l'échiquier. 0 : bas, 1 : haut

		-sens : -rond : 0 : gauche, 1 : droite
			-carré : 0 : gauche, 1 : droite, 3 : devant.

		*/

	int forme;
	forme=0;		


	if (x>7||y>7||x<0||y<0) {printf("x>7||y>7||x<0||y<0\n"); return 0;} /*Vérifiaction des coordonnées.  */


	if (t[x][y]==1||t[x][y]==3) {printf("t[x][y]==0||t[x][y]==3\n"); forme=0;} if (t[x][y]==2||t[x][y]==4) {printf("t[x][y]==1||t[x][y]==4\n"); forme=1;}

	if (forme>1||forme<0) return 0; /*Vérifiaction de la forme.  */

	if (forme==0) { /*rond  */
		if (sens<0||sens>1) {printf("sens<0||sens>1\n"); return 0;}

		if (base==0) {
			if (sens==0) {
				if (x-1<0||y-1<0||detectePionSature(t,x,y,x-1,y-1)) {printf("x-1<0||y-1<0"); return 0;}

				else {
					return 1;
				}
			}
			
			if (sens==1) {
				if (x-1<0||y+1>7||detectePionSature(t,x,y,x-1,y+1)) {printf("x-1<0||y+1>7"); return 0;}

				else {
					return 1;
				}
			}
		}

		else if (base==1) {
			if (sens==0) {
				if (x+1>7||y-1<0||detectePionSature(t,x,y,x+1,y-1)) {printf("x+1>7||y-1<0"); return 0;}

				else {
					return 1;
				}
			}
			
			if (sens==1) {
				if (x+1>7||y+1>7||detectePionSature(t,x,y,x+1,y+1)) {printf("x+1>7||y+1>7"); return 0;}

				else {
					return 1;
				}
			}
		}

		else return 0;
	}

	if (forme==1) { /*carré  */
		if (sens<0||sens>2) {printf("sens<0||sens>2\n"); return 0;}

		if (base==0) {
			if (sens==0) {
				if (y-1<0||detectePionSature(t,x,y,x,y-1)) {printf("y-1<0"); return 0;}

				else {
					return 1;
				}
			}
			
			if (sens==1) {
				if (y+1>7||detectePionSature(t,x,y,x,y+1)) {printf("y+1>7"); return 0;}

				else {
					return 1;
				}
			}

			if (sens==2) {
				if (x-1<0||detectePionSature(t,x,y,x-1,y)) {printf("x-1<0"); return 0;}

				else {
					return 1;
				}
			}
		}

		else if (base==1) {
			if (sens==0) {
				if (y-1<0||detectePionSature(t,x,y,x,y-1)) {printf("y-1<0"); return 0;}

				else {
					return 1;
				}
			}
			
			if (sens==1) {
				if (y+1>7||detectePionSature(t,x,y,x,y+1)) {printf("y+1>7"); return 0;}

				else {
					return 1;
				}
			}

			if (sens==2) {
				if (x+1>7||detectePionSature(t,x,y,x+1,y)) {printf("x+1>7"); return 0;}

				else {
					return 1;
				}
			}
		}

		else return 0;	
	}

	return 0;
}

int demandeDeplaceCompose (int tr) {
	int i, a;
	a=0;

	/*
			tr=cc si carre, tr=cr si rond.
		*/

	while (a<1 || a>tr) {
		a=0;

		printf("Entrer le nombre de cases : \n");
		for (i=0; i<tr; i++) {
			printf("%d : %d case",(i+1),(i+1));
			if ((i+1)>1) printf("s");
			printf("\n");
		}
		printf("? = ");

		scanf("%d",&a);
	}

	return a;
}

int detectePionSature (int t[][8], int x, int y, int x1, int y1) {
	int p1, p2, cr, cc;
	p1 = t[x][y]; p2 = t[x1][y1]; cr=0; cc=0;

	if (p2==5||p2==12) {cr=2; cc=0;}
	if (p2==6||p2==13) {cr=0; cc=2;}
	if (p2==7||p2==14) {cr=1; cc=1;}
	if (p2==8||p2==15) {cr=3; cc=0;}
	if (p2==9||p2==16) {cr=0; cc=3;}
	if (p2==10||p2==17) {cr=2; cc=1;}
	if (p2==11||p2==18) {cr=1; cc=2;}

	if (cr+cc==3) {
		if ((p1>0 && p1<3) || (p1>4 && p1<12)) /*blanc*/ if ((p2>0 && p2<3) || (p2>4 && p2<12)) return 1;
		if ((p1>2 && p1<5) || (p1>11 && p1<19)) /*noir*/ if ((p2>2 && p2<5) || (p2>11 && p2<19)) return 1;
	}

	return 0;
}

int detectePourPion2 (int t[][8], int x, int y, int x1, int y1) {
	return (detectePionAmi2(t,x,y,x1,y1) || detectePionSature(t,x,y,x1,y1));
}

int detectePionAmi (int t[][8], int x, int y, int x1, int y1) {
	int p1;
	int p2;

	p1 = t[x][y];
	p2 = t[x1][y1];

	if ((p1>0 && p1<3) || (p1>4 && p1<12)) /*blanc*/ if ((p2>0 && p2<3) || (p2>4 && p2<12)) return 1;
	if ((p1>2 && p1<5) || (p1>11 && p1<19)) /*noir*/ if ((p2>2 && p2<5) || (p2>11 && p2<19)) return 1;

	return 0;
}

int detectePionAmi2 (int t[][8], int x, int y, int x1, int y1) { /* composé de deux pions.  */
	int p1, cr, cc, p2;
	p1 = t[x][y]; cr=0; cc=0; p2 = t[x1][y1];

	if (p2==5||p2==12) {cr=2; cc=0;}
	if (p2==6||p2==13) {cr=0; cc=2;}
	if (p2==7||p2==14) {cr=1; cc=1;}
	if (p2==8||p2==15) {cr=3; cc=0;}
	if (p2==9||p2==16) {cr=0; cc=3;}
	if (p2==10||p2==17) {cr=2; cc=1;}
	if (p2==11||p2==18) {cr=1; cc=2;}

	if (cr+cc==2) {
		if ((p1>0 && p1<3) || (p1>4 && p1<12)) /*blanc*/ if ((p2>0 && p2<3) || (p2>4 && p2<12)) return 1;
		if ((p1>2 && p1<5) || (p1>11 && p1<19)) /*noir*/ if ((p2>2 && p2<5) || (p2>11 && p2<19)) return 1;
	}

	return 0;
}

int deplacePionCompose (int t[][8], int * cChoix, int base, int sens, int x, int y, int ct) {
	int i, p1, cr, cc, pion;
	int rond_carre;

	p1 = t[x][y]; cr=0; cc=0; pion=0;
	rond_carre=0;

	/*

		-base : haut ou bas de l'échiquier. 0 : bas, 1 : haut

		cr = coup rond.
		cc = coup carré.	

		*/

	cChoix[0] = p1;

	if (p1==5||p1==12) {cr=2; cc=0;}
	if (p1==6||p1==13) {cr=0; cc=2;}
	if (p1==7||p1==14) {cr=1; cc=1;}
	if (p1==8||p1==15) {cr=3; cc=0;}
	if (p1==9||p1==16) {cr=0; cc=3;}
	if (p1==10||p1==17) {cr=2; cc=1;}
	if (p1==11||p1==18) {cr=1; cc=2;}

	if (cr+cc==2) pion=2; /*pion composé de deux pions  */
	if (cr+cc==3) pion=3; /*pion composé de trois pions (saturé).  */

	if (p1==5 || p1==8 || p1==12 || p1==15) cr=ct; /*rond  */
	if (p1==6 || p1==9 || p1==13 || p1==16) cc=ct; /*carre  */
	if (p1==7 || p1==10 || p1==11 || p1==14 || p1==17 || p1==18) { /*rond-carre  */
		if (sens<2) cr=ct; /*rond  */
		if (sens>1) cc=ct; /*carre  */
	}

	if (p1==7||p1==10||p1==11||p1==14||p1==17||p1==18) rond_carre=1;
	
	if (base==0) {
		if (p1==1||p1==3||p1==5||p1==8||p1==12||p1==15||rond_carre) { /* rond ou rond-carre  */
			if (sens==0) {
				if (x-1<0||y-1<0) {printf("x-1<0||y-1<0"); return 0;}

				else {
					if (cr==2) {
						if (x-2<0&&y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							t[x-1][y-1]=transformeUnPion3(t,x,y,x-1,y-1);

							return 1;
						}

						else if (x-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-2)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-2)) return 0;

							t[x-1][y-1]=transformeUnPion3(t,x,y,x-1,y-1);

							t[x][y-2]=transformeUnPion(t,x,y,x,y-2);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-2,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-2,y)) return 0;

							t[x-1][y-1]=transformeUnPion3(t,x,y,x-1,y-1);

							t[x-2][y]=transformeUnPion(t,x,y,x-2,y);
							
							t[x][y]=0;
							
							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x-cr,y-cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-cr,y-cr)) return 0;

							t[x-1][y-1]=transformeUnPion3(t,x,y,x-1,y-1);

							t[x-cr][y-cr]=transformeUnPion(t,x,y,x-cr,y-cr);
							
							t[x][y]=0;
							
							return 1;
						}
					}
					
					else if (cr==3) {
						if (x-2<0&&y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+1,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+1,y+1)) return 0;

							for (i=0; i<2; i++) t[x-i][y-i]=transformeUnPion3(t,x,y,x-i,y-i);

							t[x+1][y+1]=transformeUnPion(t,x,y,x+1,y+1);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (x-3<0&&y-3<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-1,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-1,y-1)) return 0;

							for (i=0; i<3; i+=2) t[x-i][y-i]=transformeUnPion3(t,x,y,x-i,y-i);

							t[x-1][y-1]=transformeUnPion(t,x,y,x-1,y-1);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (x-1==1&&y-1==0) {
							if (pion==2) if (detectePourPion2 (t,x,y,1,2)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,1,2)) return 0;

							t[1][0]=transformeUnPion3(t,x,y,1,0);
							t[0][1]=transformeUnPion3(t,x,y,0,1);

							t[1][2]=transformeUnPion(t,x,y,1,2);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (x-2==1&&y-2==0) {
							if (pion==2) if (detectePourPion2 (t,x,y,0,1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,0,1)) return 0;

							t[2][1]=transformeUnPion3(t,x,y,2,1);
							t[1][0]=transformeUnPion3(t,x,y,1,0);

							t[0][1]=transformeUnPion(t,x,y,0,1);
							
							t[x][y]=0;
							
							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x-cr,y-cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-cr,y-cr)) return 0;

							for (i=0; i<3; i++) t[x-i][y-i]=transformeUnPion3(t,x,y,x-i,y-i);

							t[x-cr][y-cr]=transformeUnPion(t,x,y,x-cr,y-cr);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x-cr,y-cr)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x-cr,y-cr)) return 0;

						for (i=0; i<cr; i++) t[x-i][y-i]=transformeUnPion3(t,x,y,x-i,y-i);

						t[x-cr][y-cr]=transformeUnPion(t,x,y,x-cr,y-cr);
						
						t[x][y]=0;
						
						return 1;
					}
				}
			}
			
			if (sens==1) {
				if (x-1<0||y+1>7) {printf("x-1<0||y+1>7"); return 0;}

				else {
					if (cr==2) {
						if (x-2<0&&y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							t[x-1][y+1]=transformeUnPion3(t,x,y,x-1,y+1);

							return 1;
						}

						else if (x-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+2)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+2)) return 0;

							t[x-1][y+1]=transformeUnPion3(t,x,y,x-1,y+1);

							t[x][y+2]=transformeUnPion(t,x,y,x,y+2);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-2,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-2,y)) return 0;

							t[x-1][y+1]=transformeUnPion3(t,x,y,x-1,y+1);

							t[x-2][y]=transformeUnPion(t,x,y,x-2,y);
							
							t[x][y]=0;
							
							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x-cr,y+cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-cr,y+cr)) return 0;

							t[x-1][y+1]=transformeUnPion3(t,x,y,x-1,y+1);

							t[x-cr][y+cr]=transformeUnPion(t,x,y,x-cr,y+cr);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else if (cr==3) {
						if (x-2<0&&y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+1,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+1,y-1)) return 0;

							for (i=0; i<2; i++) t[x-i][y+i]=transformeUnPion3(t,x,y,x-i,y+i);

							t[x+1][y-1]=transformeUnPion(t,x,y,x+1,y-1);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (x-3<0&&y+3>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-1,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-1,y+1)) return 0;

							for (i=0; i<3; i+=2) t[x-i][y+i]=transformeUnPion3(t,x,y,x-i,y+i);

							t[x-1][y+1]=transformeUnPion(t,x,y,x-1,y+1);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (x-1==1&&y+1==7) {
							if (pion==2) if (detectePourPion2 (t,x,y,1,5)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,1,5)) return 0;

							t[1][7]=transformeUnPion3(t,x,y,1,7);
							t[0][6]=transformeUnPion3(t,x,y,0,6);

							t[1][5]=transformeUnPion(t,x,y,1,5);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (x-2==1&&y+2==7) {
							if (pion==2) if (detectePourPion2 (t,x,y,0,6)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,0,6)) return 0;

							t[2][6]=transformeUnPion3(t,x,y,2,6);
							t[1][7]=transformeUnPion3(t,x,y,1,7);

							t[0][6]=transformeUnPion(t,x,y,0,6);
							
							t[x][y]=0;
							
							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x-cr,y+cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-cr,y+cr)) return 0;

							for (i=0; i<3; i++) t[x-i][y+i]=transformeUnPion3(t,x,y,x-i,y+i);

							t[x-cr][y+cr]=transformeUnPion(t,x,y,x-cr,y+cr);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x-cr,y+cr)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x-cr,y+cr)) return 0;

						for (i=0; i<cr; i++) t[x-i][y+i]=transformeUnPion3(t,x,y,x-i,y+i);

						t[x-cr][y+cr]=transformeUnPion(t,x,y,x-cr,y+cr);
						
						t[x][y]=0;
						
						return 1;
					}
				}
			}		
		}

		if (p1==2||p1==4||p1==6||p1==9||p1==13||p1==16||rond_carre) { /* carre  */
			if (((!rond_carre)&&sens==0) || (rond_carre&&sens==2)) { /* sens=0  */
				if (y-1<0) {printf("y-1<0"); return 0;}

				else {
					if (cc==2) {
						if (y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							t[x][y-1]=transformeUnPion3(t,x,y,x,y-1);

							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-cc)) return 0;

							t[x][y-1]=transformeUnPion3(t,x,y,x,y-1);

							t[x][y-cc]=transformeUnPion(t,x,y,x,y-cc);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else if (cc==3) {
						if (y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+1)) return 0;

							for (i=0; i<2; i++) t[x][y-i]=transformeUnPion3(t,x,y,x,y-i);

							t[x][y+1]=transformeUnPion(t,x,y,x,y+1);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (y-3<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-1)) return 0;

							for (i=0; i<3; i+=2) t[x][y-i]=transformeUnPion3(t,x,y,x,y-i);

							t[x][y-1]=transformeUnPion(t,x,y,x,y-1);
							
							t[x][y]=0;
							
							return 1;										
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-cc)) return 0;
							
							for (i=0; i<cc; i++) t[x][y-i]=transformeUnPion3(t,x,y,x,y-i);

							t[x][y-cc]=transformeUnPion(t,x,y,x,y-cc);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x,y-cc)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x,y-cc)) return 0;
						
						for (i=0; i<cc; i++) t[x][y-i]=transformeUnPion3(t,x,y,x,y-i);
						
						t[x][y-cc]=transformeUnPion(t,x,y,x,y-cc);
						
						t[x][y]=0;
						
						return 1;
					}
				}
			}
			
			if (((!rond_carre)&&sens==1) || (rond_carre&&sens==3)) { /* sens=1  */
				if (y+1>7) {printf("y+1>7"); return 0;}

				else {
					if (cc==2) {
						if (y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							t[x][y+1]=transformeUnPion3(t,x,y,x,y+1);

							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+cc)) return 0;

							t[x][y+1]=transformeUnPion3(t,x,y,x,y+1);

							t[x][y+cc]=transformeUnPion(t,x,y,x,y+cc);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else if (cc==3) {
						if (y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-1)) return 0;

							for (i=0; i<2; i++) t[x][y+i]=transformeUnPion3(t,x,y,x,y+i);

							t[x][y-1]=transformeUnPion(t,x,y,x,y-1);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (y+3>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+1)) return 0;

							for (i=0; i<3; i+=2) t[x][y+i]=transformeUnPion3(t,x,y,x,y+i);

							t[x][y+1]=transformeUnPion(t,x,y,x,y+1);
							
							t[x][y]=0;
							
							return 1;										
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+cc)) return 0;
							
							for (i=0; i<cc; i++) t[x][y+i]=transformeUnPion3(t,x,y,x,y+i);

							t[x][y+cc]=transformeUnPion(t,x,y,x,y+cc);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x,y+cc)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x,y+cc)) return 0;
						
						for (i=0; i<cc; i++) t[x][y+i]=transformeUnPion3(t,x,y,x,y+i);
						
						t[x][y+cc]=transformeUnPion(t,x,y,x,y+cc);
						
						t[x][y]=0;
						
						return 1;
					}
				}
			}
			
			if (((!rond_carre)&&sens==2) || (rond_carre&&sens==4)) { /* sens=2  */
				if (x-1<0) {printf("x-1<0"); return 0;}

				else {
					if (cc==2) {
						if (x-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							t[x-1][y]=transformeUnPion3(t,x,y,x-1,y);

							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x-cc,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-cc,y)) return 0;

							t[x-1][y]=transformeUnPion3(t,x,y,x-1,y);

							t[x-cc][y]=transformeUnPion(t,x,y,x-cc,y);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else if (cc==3) {
						if (x-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+1,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+1,y)) return 0;

							for (i=0; i<2; i++) t[x-i][y]=transformeUnPion3(t,x,y,x-i,y);

							t[x+1][y]=transformeUnPion(t,x,y,x+1,y);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (x-3<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-1,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-1,y)) return 0;

							for (i=0; i<3; i+=2) t[x-i][y]=transformeUnPion3(t,x,y,x-i,y);

							t[x-1][y]=transformeUnPion(t,x,y,x-1,y);
							
							t[x][y]=0;
							
							return 1;										
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x-cc,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-cc,y)) return 0;
							
							for (i=0; i<cc; i++) t[x-i][y]=transformeUnPion3(t,x,y,x-i,y);

							for (i=0; i<3; i++) t[x-i][y]=transformeUnPion(t,x,y,x-i,y);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x-cc,y)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x-cc,y)) return 0;
						
						for (i=0; i<cc; i++) t[x-i][y]=transformeUnPion3(t,x,y,x-i,y);

						t[x-cc][y]=transformeUnPion(t,x,y,x-cc,y);
						
						t[x][y]=0;
						
						return 1;
					}
				}
			}
		}
	}

	if (base==1) {
		if (p1==1||p1==3||p1==5||p1==8||p1==12||p1==15||rond_carre) { /* rond  */
			/*printf("p1==8");  */
			
			if (sens==0) {
				if (x+1>7||y-1<0) {printf("x+1>7||y-1<0"); return 0;}

				else {
					if (cr==2) {
						if (x+2>7&&y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							t[x+1][y-1]=transformeUnPion3(t,x,y,x+1,y-1);

							return 1;
						}

						else if (x+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-2)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-2)) return 0;

							t[x+1][y-1]=transformeUnPion3(t,x,y,x+1,y-1);

							t[x][y-2]=transformeUnPion(t,x,y,x,y-2);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+2,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+2,y)) return 0;

							t[x+1][y-1]=transformeUnPion3(t,x,y,x+1,y-1);

							t[x+2][y]=transformeUnPion(t,x,y,x+2,y);
							
							t[x][y]=0;
							
							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x+cr,y-cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+cr,y-cr)) return 0;

							t[x+1][y-1]=transformeUnPion3(t,x,y,x+1,y-1);

							t[x+cr][y-cr]=transformeUnPion(t,x,y,x+cr,y-cr);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					if (cr==3) {
						if (x+2>7&&y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-1,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-1,y+1)) return 0;

							for (i=0; i<2; i++) t[x+i][y-i]=transformeUnPion3(t,x,y,x+i,y-i);

							t[x-1][y+1]=transformeUnPion(t,x,y,x-1,y+1);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (x+3>7&&y-3<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+1,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+1,y-1)) return 0;

							for (i=0; i<3; i+=2) t[x+i][y-i]=transformeUnPion3(t,x,y,x+i,y-i);

							t[x+1][y-1]=transformeUnPion(t,x,y,x+1,y-1);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (x+1==6&&y-1==0) {
							if (pion==2) if (detectePourPion2 (t,x,y,6,2)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,6,2)) return 0;

							t[6][0]=transformeUnPion3(t,x,y,6,0);
							t[7][1]=transformeUnPion3(t,x,y,7,1);

							t[6][2]=transformeUnPion(t,x,y,6,2);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (x+2==6&&y-2==0) {
							if (pion==2) if (detectePourPion2 (t,x,y,7,1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,7,1)) return 0;

							t[5][1]=transformeUnPion3(t,x,y,5,1);
							t[6][0]=transformeUnPion3(t,x,y,6,0);

							t[7][1]=transformeUnPion(t,x,y,7,1);
							
							t[x][y]=0;
							
							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x+cr,y-cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+cr,y-cr)) return 0;

							for (i=0; i<3; i++) t[x+i][y-i]=transformeUnPion3(t,x,y,x+i,y-i);

							t[x+cr][y-cr]=transformeUnPion(t,x,y,x+cr,y-cr);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x+cr,y-cr)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x+cr,y-cr)) return 0;

						for (i=0; i<cr; i++) t[x+i][y-i]=transformeUnPion3(t,x,y,x+i,y-i);

						t[x+cr][y-cr]=transformeUnPion(t,x,y,x+cr,y-cr);
						
						t[x][y]=0;
						
						return 1;
					}
				}
			}
			
			if (sens==1) {
				if (x+1>7||y+1>7) {printf("x+1>7||y+1>7"); return 0;}

				else {
					if (cr==2) {
						if (x+2>7&&y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							t[x+1][y+1]=transformeUnPion3(t,x,y,x+1,y+1);

							return 1;
						}

						else if (x+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+2)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+2)) return 0;

							t[x+1][y+1]=transformeUnPion3(t,x,y,x+1,y+1);

							t[x][y+2]=transformeUnPion(t,x,y,x,y+2);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+2,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+2,y)) return 0;

							t[x+1][y+1]=transformeUnPion3(t,x,y,x+1,y+1);

							t[x+2][y]=transformeUnPion(t,x,y,x+2,y);
							
							t[x][y]=0;
							
							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x+cr,y+cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+cr,y+cr)) return 0;

							t[x+1][y+1]=transformeUnPion3(t,x,y,x+1,y+1);

							t[x+cr][y+cr]=transformeUnPion(t,x,y,x+cr,y+cr);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					if (cr==3) {
						if (x+2>7&&y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+1,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+1,y+1)) return 0;

							for (i=0; i<2; i++) t[x+i][y+i]=transformeUnPion3(t,x,y,x+i,y+i);

							t[x+1][y+1]=transformeUnPion(t,x,y,x+1,y+1);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (x+3>7&&y+3>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-1,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-1,y-1)) return 0;

							for (i=0; i<3; i+=2) t[x+i][y+i]=transformeUnPion3(t,x,y,x+i,y+i);

							t[x-1][y-1]=transformeUnPion(t,x,y,x-1,y-1);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (x+1==6&&y+1==7) {
							if (pion==2) if (detectePourPion2 (t,x,y,6,5)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,6,5)) return 0;

							t[6][7]=transformeUnPion3(t,x,y,6,7);
							t[7][6]=transformeUnPion3(t,x,y,7,6);

							t[6][5]=transformeUnPion(t,x,y,6,5);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (x+2==6&&y+2==7) {
							if (pion==2) if (detectePourPion2 (t,x,y,7,6)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,7,6)) return 0;

							t[5][6]=transformeUnPion3(t,x,y,5,6);
							t[6][7]=transformeUnPion3(t,x,y,6,7);

							t[7][6]=transformeUnPion(t,x,y,7,6);
							
							t[x][y]=0;
							
							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x+cr,y+cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+cr,y+cr)) return 0;

							for (i=0; i<3; i++) t[x+i][y+i]=transformeUnPion3(t,x,y,x+i,y+i);

							t[x+cr][y+cr]=transformeUnPion(t,x,y,x+cr,y+cr);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x+cr,y+cr)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x+cr,y+cr)) return 0;

						for (i=0; i<cr; i++) t[x+i][y+i]=transformeUnPion3(t,x,y,x+i,y+i);

						t[x+cr][y+cr]=transformeUnPion(t,x,y,x+cr,y+cr);
						
						t[x][y]=0;
						
						return 1;
					}
				}
			}		
		}

		if (p1==2||p1==4||p1==6||p1==9||p1==13||p1==16||rond_carre) { /* carre  */
			if (((!rond_carre)&&sens==0) || (rond_carre&&sens==2)) { /* sens=0  */
				if (y-1<0) {printf("y-1<0"); return 0;}

				else {
					if (cc==2) {
						if (y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							t[x][y-1]=transformeUnPion3(t,x,y,x,y-1);

							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-cc)) return 0;

							t[x][y-1]=transformeUnPion3(t,x,y,x,y-1);

							t[x][y-cc]=transformeUnPion(t,x,y,x,y-cc);
							
							t[x][y]=0;
							
							return 1;
						}							
					}

					else if (cc==3) {
						if (y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+1)) return 0;

							for (i=0; i<2; i++) t[x][y-i]=transformeUnPion3(t,x,y,x,y-i);

							t[x][y+1]=transformeUnPion(t,x,y,x,y+1);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (y-3<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-1)) return 0;

							for (i=0; i<3; i+=2) t[x][y-i]=transformeUnPion3(t,x,y,x,y-i);

							t[x][y-1]=transformeUnPion(t,x,y,x,y-1);
							
							t[x][y]=0;
							
							return 1;										
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-cc)) return 0;
							
							for (i=0; i<cc; i++) t[x][y-i]=transformeUnPion3(t,x,y,x,y-i);

							t[x][y-cc]=transformeUnPion(t,x,y,x,y-cc);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x,y-cc)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x,y-cc)) return 0;
						
						for (i=0; i<cc; i++) t[x][y-i]=transformeUnPion3(t,x,y,x,y-i);

						t[x][y-cc]=transformeUnPion(t,x,y,x,y-cc);
						
						t[x][y]=0;
						
						return 1;
					}
				}
			}
			
			if (((!rond_carre)&&sens==1) || (rond_carre&&sens==3)) { /* sens=1  */
				if (y+1>7) {printf("y+1>7"); return 0;}

				else {
					if (cc==2) {
						if (y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							t[x][y+1]=transformeUnPion3(t,x,y,x,y+1);

							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+cc)) return 0;

							t[x][y+1]=transformeUnPion3(t,x,y,x,y+1);

							t[x][y+cc]=transformeUnPion(t,x,y,x,y+cc);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else if (cc==3) {
						if (y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-1)) return 0;

							for (i=0; i<2; i++) t[x][y+i]=transformeUnPion3(t,x,y,x,y+i);

							t[x][y-1]=transformeUnPion(t,x,y,x,y-1);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (y+3>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+1)) return 0;

							for (i=0; i<3; i+=2) t[x][y+i]=transformeUnPion3(t,x,y,x,y+i);

							t[x][y+1]=transformeUnPion(t,x,y,x,y+1);
							
							t[x][y]=0;
							
							return 1;										
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+cc)) return 0;
							
							for (i=0; i<cc; i++) t[x][y+i]=transformeUnPion3(t,x,y,x,y+i);

							t[x][y+cc]=transformeUnPion(t,x,y,x,y+cc);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x,y+cc)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x,y+cc)) return 0;
						
						for (i=0; i<cc; i++) t[x][y+i]=transformeUnPion3(t,x,y,x,y+i);

						t[x][y+cc]=transformeUnPion(t,x,y,x,y+cc);
						
						t[x][y]=0;
						
						return 1;
					}
				}
			}
			
			if (((!rond_carre)&&sens==2) || (rond_carre&&sens==4)) { /* sens=2  */
				if (x+cc>7) {printf("x+cc>7"); return 0;}

				else {
					if (cc==2) {
						if (x+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							t[x+1][y]=transformeUnPion3(t,x,y,x+1,y);

							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x+cc,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+cc,y)) return 0;

							t[x+1][y]=transformeUnPion3(t,x,y,x+1,y);

							t[x+cc][y]=transformeUnPion(t,x,y,x+cc,y);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else if (cc==3) {
						if (x+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-1,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-1,y)) return 0;

							for (i=0; i<2; i++) t[x+i][y]=transformeUnPion3(t,x,y,x+i,y);

							t[x-1][y]=transformeUnPion(t,x,y,x-1,y);
							
							t[x][y]=0;
							
							return 1;
						}

						else if (x+3>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+1,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+1,y)) return 0;

							for (i=0; i<3; i+=2) t[x+i][y]=transformeUnPion3(t,x,y,x+i,y);

							t[x+1][y]=transformeUnPion(t,x,y,x+1,y);
							
							t[x][y]=0;
							
							return 1;										
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x+cc,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+cc,y)) return 0;
							
							for (i=0; i<cc; i++) t[x+i][y]=transformeUnPion3(t,x,y,x+i,y);

							t[x+cc][y]=transformeUnPion(t,x,y,x+cc,y);
							
							t[x][y]=0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x+cc,y)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x+cc,y)) return 0;

						for (i=0; i<cc; i++) t[x+i][y]=transformeUnPion3(t,x,y,x+i,y);
						
						t[x+cc][y]=transformeUnPion(t,x,y,x+cc,y);
						
						t[x][y]=0;
						
						return 1;
					}
				}
			}
		}
	}

	return 0;
}

int deplacePionComposeTest (int t[][8], int base, int sens, int x, int y, int ct) {
	int p1, cr, cc, pion;
	int rond_carre;

	p1 = t[x][y]; cr=0; cc=0; pion=0;
	rond_carre=0;

	/*

		-base : haut ou bas de l'échiquier. 0 : bas, 1 : haut

		cr = coup rond.
		cc = coup carré.	

		*/

	if (p1==5||p1==12) {cr=2; cc=0;}
	if (p1==6||p1==13) {cr=0; cc=2;}
	if (p1==7||p1==14) {cr=1; cc=1;}
	if (p1==8||p1==15) {cr=3; cc=0;}
	if (p1==9||p1==16) {cr=0; cc=3;}
	if (p1==10||p1==17) {cr=2; cc=1;}
	if (p1==11||p1==18) {cr=1; cc=2;}

	if (cr+cc==2) pion=2; /*pion composé de deux pions  */
	if (cr+cc==3) pion=3; /*pion composé de trois pions (saturé).  */

	if (p1==5 || p1==8 || p1==12 || p1==15) cr=ct; /*rond  */
	if (p1==6 || p1==9 || p1==13 || p1==16) cc=ct; /*carre  */
	if (p1==7 || p1==10 || p1==11 || p1==14 || p1==17 || p1==18) { /*rond-carre  */
		if (sens<2) cr=ct; /*rond  */
		if (sens>1) cc=ct; /*carre  */
	}

	if (p1==7||p1==10||p1==11||p1==14||p1==17||p1==18) rond_carre=1;
	
	if (base==0) {
		if (p1==1||p1==3||p1==5||p1==8||p1==12||p1==15||rond_carre) { /* rond ou rond-carre  */
			if (sens==0) {
				if (x-1<0||y-1<0) {printf("x-1<0||y-1<0"); return 0;}

				else {
					if (cr==2) {
						if (x-2<0&&y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							return 1;
						}

						else if (x-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-2)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-2)) return 0;

							return 1;
						}

						else if (y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-2,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-2,y)) return 0;

							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x-cr,y-cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-cr,y-cr)) return 0;
							
							return 1;
						}
					}
					
					else if (cr==3) {
						if (x-2<0&&y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+1,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+1,y+1)) return 0;
							
							return 1;
						}

						else if (x-3<0&&y-3<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-1,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-1,y-1)) return 0;
							
							return 1;
						}

						else if (x-1==1&&y-1==0) {
							if (pion==2) if (detectePourPion2 (t,x,y,1,2)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,1,2)) return 0;
							
							return 1;
						}

						else if (x-2==1&&y-2==0) {
							if (pion==2) if (detectePourPion2 (t,x,y,0,1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,0,1)) return 0;
							
							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x-cr,y-cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-cr,y-cr)) return 0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x-cr,y-cr)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x-cr,y-cr)) return 0;
						
						return 1;
					}
				}
			}
			
			if (sens==1) {
				if (x-1<0||y+1>7) {printf("x-1<0||y+1>7"); return 0;}

				else {
					if (cr==2) {
						if (x-2<0&&y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							return 1;
						}

						else if (x-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+2)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+2)) return 0;
							
							return 1;
						}

						else if (y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-2,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-2,y)) return 0;
							
							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x-cr,y+cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-cr,y+cr)) return 0;
							
							return 1;
						}
					}

					else if (cr==3) {
						if (x-2<0&&y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+1,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+1,y-1)) return 0;
							
							return 1;
						}

						else if (x-3<0&&y+3>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-1,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-1,y+1)) return 0;
							
							return 1;
						}

						else if (x-1==1&&y+1==7) {
							if (pion==2) if (detectePourPion2 (t,x,y,1,5)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,1,5)) return 0;
							
							return 1;
						}

						else if (x-2==1&&y+2==7) {
							if (pion==2) if (detectePourPion2 (t,x,y,0,6)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,0,6)) return 0;
							
							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x-cr,y+cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-cr,y+cr)) return 0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x-cr,y+cr)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x-cr,y+cr)) return 0;
						
						return 1;
					}
				}
			}		
		}

		if (p1==2||p1==4||p1==6||p1==9||p1==13||p1==16||rond_carre) { /* carre  */
			if (((!rond_carre)&&sens==0) || (rond_carre&&sens==2)) { /* sens=0  */
				if (y-1<0) {printf("y-1<0"); return 0;}

				else {
					if (cc==2) {
						if (y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-cc)) return 0;
							
							return 1;
						}
					}

					else if (cc==3) {
						if (y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+1)) return 0;
							
							return 1;
						}

						else if (y-3<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-1)) return 0;
							
							return 1;										
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-cc)) return 0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x,y-cc)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x,y-cc)) return 0;
						
						return 1;
					}
				}
			}
			
			if (((!rond_carre)&&sens==1) || (rond_carre&&sens==3)) { /* sens=1  */
				if (y+1>7) {printf("y+1>7"); return 0;}

				else {
					if (cc==2) {
						if (y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+cc)) return 0;
							
							return 1;
						}
					}

					else if (cc==3) {
						if (y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-1)) return 0;
							
							return 1;
						}

						else if (y+3>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+1)) return 0;
							
							return 1;										
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+cc)) return 0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x,y+cc)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x,y+cc)) return 0;
						
						return 1;
					}
				}
			}
			
			if (((!rond_carre)&&sens==2) || (rond_carre&&sens==4)) { /* sens=2  */
				if (x-1<0) {printf("x-1<0"); return 0;}

				else {
					if (cc==2) {
						if (x-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x-cc,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-cc,y)) return 0;
							
							return 1;
						}
					}

					else if (cc==3) {
						if (x-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+1,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+1,y)) return 0;
							
							return 1;
						}

						else if (x-3<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-1,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-1,y)) return 0;
							
							return 1;										
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x-cc,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-cc,y)) return 0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x-cc,y)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x-cc,y)) return 0;
						
						return 1;
					}
				}
			}
		}
	}

	if (base==1) {
		if (p1==1||p1==3||p1==5||p1==8||p1==12||p1==15||rond_carre) { /* rond  */
			/*printf("p1==8");  */
			
			if (sens==0) {
				if (x+1>7||y-1<0) {printf("x+1>7||y-1<0"); return 0;}

				else {
					if (cr==2) {
						if (x+2>7&&y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							return 1;
						}

						else if (x+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-2)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-2)) return 0;
							
							return 1;
						}

						else if (y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+2,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+2,y)) return 0;
							
							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x+cr,y-cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+cr,y-cr)) return 0;
							
							return 1;
						}
					}

					if (cr==3) {
						if (x+2>7&&y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-1,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-1,y+1)) return 0;
							
							return 1;
						}

						else if (x+3>7&&y-3<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+1,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+1,y-1)) return 0;
							
							return 1;
						}

						else if (x+1==6&&y-1==0) {
							if (pion==2) if (detectePourPion2 (t,x,y,6,2)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,6,2)) return 0;
							
							return 1;
						}

						else if (x+2==6&&y-2==0) {
							if (pion==2) if (detectePourPion2 (t,x,y,7,1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,7,1)) return 0;

							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x+cr,y-cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+cr,y-cr)) return 0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x+cr,y-cr)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x+cr,y-cr)) return 0;
						
						return 1;
					}
				}
			}
			
			if (sens==1) {
				if (x+1>7||y+1>7) {printf("x+1>7||y+1>7"); return 0;}

				else {
					if (cr==2) {
						if (x+2>7&&y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							return 1;
						}

						else if (x+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+2)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+2)) return 0;
							
							return 1;
						}

						else if (y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+2,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+2,y)) return 0;
							
							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x+cr,y+cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+cr,y+cr)) return 0;
							
							return 1;
						}
					}

					if (cr==3) {
						if (x+2>7&&y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+1,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+1,y+1)) return 0;
							
							return 1;
						}

						else if (x+3>7&&y+3>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-1,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-1,y-1)) return 0;
							
							return 1;
						}

						else if (x+1==6&&y+1==7) {
							if (pion==2) if (detectePourPion2 (t,x,y,6,5)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,6,5)) return 0;
							
							return 1;
						}

						else if (x+2==6&&y+2==7) {
							if (pion==2) if (detectePourPion2 (t,x,y,7,6)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,7,6)) return 0;
							
							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x+cr,y+cr)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+cr,y+cr)) return 0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x+cr,y+cr)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x+cr,y+cr)) return 0;
						
						return 1;
					}
				}
			}		
		}

		if (p1==2||p1==4||p1==6||p1==9||p1==13||p1==16||rond_carre) { /* carre  */
			if (((!rond_carre)&&sens==0) || (rond_carre&&sens==2)) { /* sens=0  */
				if (y-1<0) {printf("y-1<0"); return 0;}

				else {
					if (cc==2) {
						if (y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-cc)) return 0;
							
							return 1;
						}							
					}

					else if (cc==3) {
						if (y-2<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+1)) return 0;
							
							return 1;
						}

						else if (y-3<0) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-1)) return 0;
							
							return 1;										
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-cc)) return 0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x,y-cc)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x,y-cc)) return 0;
						
						return 1;
					}
				}
			}
			
			if (((!rond_carre)&&sens==1) || (rond_carre&&sens==3)) { /* sens=1  */
				if (y+1>7) {printf("y+1>7"); return 0;}

				else {
					if (cc==2) {
						if (y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+cc)) return 0;
							
							return 1;
						}
					}

					else if (cc==3) {
						if (y+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y-1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y-1)) return 0;
							
							return 1;
						}

						else if (y+3>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+1)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+1)) return 0;
							
							return 1;										
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y+cc)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y+cc)) return 0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x,y+cc)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x,y+cc)) return 0;
						
						return 1;
					}
				}
			}
			
			if (((!rond_carre)&&sens==2) || (rond_carre&&sens==4)) { /* sens=2  */
				if (x+cc>7) {printf("x+cc>7"); return 0;}

				else {
					if (cc==2) {
						if (x+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x,y)) return 0;

							return 1;
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x+cc,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+cc,y)) return 0;
							
							return 1;
						}
					}

					else if (cc==3) {
						if (x+2>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x-1,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x-1,y)) return 0;
							
							return 1;
						}

						else if (x+3>7) {
							if (pion==2) if (detectePourPion2 (t,x,y,x+1,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+1,y)) return 0;
							
							return 1;										
						}

						else {
							if (pion==2) if (detectePourPion2 (t,x,y,x+cc,y)) return 0;
							if (pion==3) if (detectePionAmi (t,x,y,x+cc,y)) return 0;
							
							return 1;
						}
					}

					else {
						if (pion==2) if (detectePourPion2 (t,x,y,x+cc,y)) return 0;
						if (pion==3) if (detectePionAmi (t,x,y,x+cc,y)) return 0;
						
						return 1;
					}
				}
			}
		}
	}

	return 0;
}

int joueAleat (int t[][8], int couleur, int composition) {
	int i,j, k, x, y, coup0, coup, c2, base, sens1, /*sens2,*/ cmp, /*lt,*/ p1, cr, cc;
	int * t1;
	int * t2;
	int ** t3;

	x=0; y=0; coup0=0; coup = rand()%(4)+1; c2=0; base=0; sens1=0; /*sens2=0;*/ cmp=0; /*lt=0;*/ p1=0; cr=0; cc=0;
	t1 = malloc(sizeof(int)*1);
	t2 = malloc(sizeof(int)*1);
	t3 = malloc(sizeof(int)*1);
	for (i=0; i<cmp; i++) t3[i] = malloc(sizeof(int)*2);

	srand(time(NULL));

	for (i=0; i<7; i++) {
		for (j=0; j<7; j++) {
			if (couleur==0) /*blanc*/ if ((t[i][j]>0 && t[i][j]<3) || (t[i][j]>4 && t[i][j]<12)) {
				t1 = autoriseDeplacePion (t,i,j);
				if (t1[0]!=1) cmp++;
			}

			if (couleur==1) /*noir*/ if ((t[i][j]>2 && t[i][j]<5) || (t[i][j]>11 && t[i][j]<19)) {
				t1 = autoriseDeplacePion (t,i,j);
				if (t1[0]!=1) cmp++;
			}
		}
	}

	if (cmp==0) return 3; /* les <couleur>s ont perdu.  */

	t3 = malloc(sizeof(int)*cmp);
	for (i=0; i<cmp; i++) t3[i] = malloc(sizeof(int)*2);

	k=0;

	for (i=0; i<7; i++) {
		for (j=0; j<7; j++) {
			if (couleur==0) /*blanc*/ if ((t[i][j]>0 && t[i][j]<3) || (t[i][j]>4 && t[i][j]<12)) {
				t1 = autoriseDeplacePion (t,i,j);

				if (t1[0]!=1) {
					t3[k][0]=i;
					t3[k][1]=j;
					
					if (k<cmp-1) k++;
				}
			}

			if (couleur==1) /*noir*/ if ((t[i][j]>2 && t[i][j]<5) || (t[i][j]>11 && t[i][j]<19)) {
				t1 = autoriseDeplacePion (t,i,j);

				if (t1[0]!=1) {
					t3[k][0]=i;
					t3[k][1]=j;
					
					if (k<cmp-1) k++;
				}
			}
		}
	}

	coup0 = rand()%(cmp);
	if (coup0>cmp) coup0=cmp;

	x = t3[cmp][0];
	y = t3[cmp][1];

	p1 = t[x][y];

	if (p1==5||p1==12) {cr=2; cc=0;}
	if (p1==6||p1==13) {cr=0; cc=2;}
	if (p1==7||p1==14) {cr=1; cc=1;}
	if (p1==8||p1==15) {cr=3; cc=0;}
	if (p1==9||p1==16) {cr=0; cc=3;}
	if (p1==10||p1==17) {cr=2; cc=1;}
	if (p1==11||p1==18) {cr=1; cc=2;}

	cmp=0;

	if (composition==0 && couleur==0) base=1;
	if (composition==0 && couleur==1) base=0;
	if (composition==1 && couleur==0) base=0;
	if (composition==1 && couleur==1) base=1;

	

	if (coup==1 || coup==2) { /* coup simple  */
		t1 = autoriseDeplacePion (t,x,y);

		for (i=0; i<t1[0]; i++) {
			cmp++;
		}

		if (cmp==0) coup = rand()%(4)+1;

		/*free(t2);  */
		t2 = malloc(sizeof(int)*cmp);

		j=0;
		for (i=1; i<t1[0]; i++) {
			if (t1[i]>0) t2[j]=i;
			if (j<cmp-1) j++;
		}

		c2 = rand()%(cmp);
		if (c2>=cmp) c2=cmp-1;

		if (p1>0 && p1<5) { /* pion simple  */
			if ((c2>0 && c2<3) || (c2>4 && c2<7)) base=0;
			if ((c2>2 && c2<5) || (c2>6 && c2<9)) base=1;
			if (c2==1 || c2==3 || c2==5 || c2==7) sens1=0;
			if (c2==2 || c2==4 || c2==6 || c2==8) sens1=0;

		}

		if (p1>4 && p1<19) { /* pion compose  */
			if (cr+cc==2) { /* 1 rond, 1 carre  */

			}

			if (cr+cc==3) {
				if (cr==2) { /* 2 ronds, 1 carre  */

				}

				if (cc==2) { /* 2 carres, 1 carre  */

				}
			}
		}			
	}

	if (coup==3 || coup==4) { /* deploiement  */
		t1 = (AutoriseDeploiement(t,x,y));

		for (i=0; i<t1[0]; i++) {
			cmp++;
		}

		/*free(t2);  */
		t2 = malloc(sizeof(int)*cmp);

		j=0;
		for (i=1; i<t1[0]; i++) {
			if (t1[i]>0) t2[j]=t1[i];
			if (j<cmp-1) j++;
		}
	}

	return 0;
}

int * autoriseDeplacePion (int t[][8], int x, int y) {
	int i,j,k,l,p1, cr, cc,cmp;
	int * t1;

	l=0; p1=t[x][y]; cr=0; cc=0; cmp=0;

	t1 = malloc(sizeof(int)*1);
	t1[0]=1;

	if (x<0 || x>7 || y<0 || y>7) return t1;

	if (p1>0 && p1<5) { /* pion simple  */
		/*free(t1);  */
		t1 = malloc(sizeof(int)*5);

		t1[0]=5; /* taille du tableau  */

		if (p1==1 || p1==3) l=2; /*rond  */
		if (p1==2 || p1==4) l=3; /*carre  */

		k=1;
		for (i=0; i<2; i++) {
			for (j=0; j<l; j++) {
				t1[k] = deplacePionTest(t, i, j,x,y);

				k++;
			}
		}
	}

	if (p1>4 && p1<19) { /* pion compose  */
		if (p1==5||p1==12) {cr=2; cc=0;}
		if (p1==6||p1==13) {cr=0; cc=2;}
		if (p1==7||p1==14) {cr=1; cc=1;}
		if (p1==8||p1==15) {cr=3; cc=0;}
		if (p1==9||p1==16) {cr=0; cc=3;}
		if (p1==10||p1==17) {cr=2; cc=1;}
		if (p1==11||p1==18) {cr=1; cc=2;}

		if (cc==0) { /*rond  */
			/*free(t1);  */
			t1 = malloc(sizeof(int)*9);

			t1[0]=9; /* taille du tableau  */

			l=1;

			i=2;
			for (j=0; j<2; j++) {
				for (k=0; k<2; k++) {
					t1[l] = deplacePionComposeTest (t,j,k,x,y,i);

					l++;
				}
			}

			if (cr==3) {
				i=3;
				for (j=0; j<2; j++) {
					for (k=0; k<2; k++) {
						t1[l] = deplacePionComposeTest (t,j,k,x,y,i);
						
						l++;
					}
				}
			}

			else {
				for (i=5; i<9; i++) {
					t1[i]=0;
				}
			}
		}

		if (cr==0) { /* carre  */
			/*free(t1);  */
			t1 = malloc(sizeof(int)*13);

			t1[0]=13; /* taille du tableau  */

			l=1;

			i=2;
			for (j=0; j<2; j++) {
				for (k=0; k<3; k++) {
					t1[l] = deplacePionComposeTest (t,j,k,x,y,i);

					l++;
				}
			}

			if (cc==3) {
				i=3;
				for (j=0; j<2; j++) {
					for (k=0; k<3; k++) {
						t1[l] = deplacePionComposeTest (t,j,k,x,y,i);
						
						l++;
					}
				}
			}

			else {
				for (i=7; i<13; i++) {
					t1[i]=0;
				}
			}
		}

		if (cr+cc==2) { /* 1 carre, 1 rond  */
			/*free(t1);  */
			t1 = malloc(sizeof(int)*11);

			t1[0]=11; /* taille du tableau  */

			k=1;
			for (i=0; i<2; i++) {
				for (j=0; j<2; j++) {
					t1[k] = deplacePionComposeTest (t,i,j,x,y,1);

					k++;
				}
			}

			for (i=0; i<2; i++) {
				for (j=0; j<3; j++) {
					t1[k] = deplacePionComposeTest (t,i,j,x,y,1);

					k++;
				}
			}
		}

		if (cr+cc==3) { /* 2 carres, 1 rond ou 2 ronds, 1 carre.  */
			if (cr==2) { /* 2 ronds, 1 carre  */
				/*free(t1);  */
				t1 = malloc(sizeof(int)*15);

				t1[0]=15; /* taille du tableau  */

				l=1;
				for (i=0; i<2; i++) {
					for (j=0; j<3; j++) {
						t1[l] = deplacePionComposeTest (t,i,j,x,y,1);

						l++;
					}
				}

				for (i=2; i<4; i++) {
					for (j=0; j<2; j++) {
						for (k=0; k<2; k++) {
							t1[l] = deplacePionComposeTest (t,j,k,x,y,i);

							l++;
						}
					}
				}
			}

			if (cc==2) { /* 2 carres, 1 rond  */
				/*free(t1);  */
				t1 = malloc(sizeof(int)*17);

				t1[0]=17; /* taille du tableau  */

				l=1;

				for (i=0; i<2; i++) {
					for (j=0; j<2; j++) {
						t1[l] = deplacePionComposeTest (t,i,j,x,y,1);

						l++;
					}
				}

				for (i=2; i<4; i++) {
					for (j=0; j<2; j++) {
						for (k=0; k<3; k++) {
							t1[l] = deplacePionComposeTest (t,j,k,x,y,i);

							l++;
						}
					}
				}
			}
		}
	}

	cmp=0;

	for (i=0; i<t1[0]; i++) if (t1[i]==1) cmp++;
	if (cmp==0) {
		/*free(t1);  */
		t1 = malloc(sizeof(int)*1);
		t1[0]=1;
	}

	return t1;
}

int transformeUnPion3 (int t[][8], int x, int y, int x1, int y1) {
	int p1;
	int p2;

	p1 = t[x][y];
	p2 = t[x1][y1];

	if (p1>4 && p1<12) /*blanc*/ if ((p2>2 && p2<5) || (p2>11 && p2<19)) {pions[p2-1]=pions[p2-1]-1; return 0;}
	if (p1>11 && p1<19) /*noir*/ if ((p2>0 && p2<3) || (p2>4 && p2<12)) {pions[p2-1]=pions[p2-1]-1; return 0;}

	return p2;
}

int transformeUnPion (int t[][8], int x, int y, int x1, int y1) {
	int p1;
	int p2;

	p1 = t[x][y];
	p2 = t[x1][y1];

	/*if (p2==0) return p1;  */

	if (p1==p2) {
		if (p1==1) return 5;
		if (p1==2) return 6;

		if (p1==3) return 12;
		if (p1==4) return 13;
	}

	else {
		if ((p1==1 && p2==2) || (p1==2 && p2==1)) {pions[p1-1]=pions[p1-1]-1; pions[p2-1]=pions[p2-1]-1; pions[7-1]=pions[7-1]+1; return 7;}
		if ((p1==3 && p2==4) || (p1==4 && p2==3)) {pions[p1-1]=pions[p1-1]-1; pions[p2-1]=pions[p2-1]-1; pions[14-1]=pions[14-1]+1; return 14;}


		if ((p1==1 && p2==5) || (p1==5 && p2==1)) {pions[p1-1]=pions[p1-1]-1; pions[p2-1]=pions[p2-1]-1; pions[8-1]=pions[8-1]+1; return 8;}
		if ((p1==1 && p2==6) || (p1==6 && p2==1)) {pions[p1-1]=pions[p1-1]-1; pions[p2-1]=pions[p2-1]-1; pions[11-1]=pions[11-1]+1; return 11;}
		if ((p1==1 && p2==7) || (p1==7 && p2==1)) {pions[p1-1]=pions[p1-1]-1; pions[p2-1]=pions[p2-1]-1; pions[10-1]=pions[10-1]+1; return 10;}

		if ((p1==2 && p2==5) || (p1==5 && p2==2)) {pions[p1-1]=pions[p1-1]-1; pions[p2-1]=pions[p2-1]-1; pions[10-1]=pions[10-1]+1; return 10;}
		if ((p1==2 && p2==6) || (p1==6 && p2==2)) {pions[p1-1]=pions[p1-1]-1; pions[p2-1]=pions[p2-1]-1; pions[9-1]=pions[9-1]+1; return 9;}
		if ((p1==2 && p2==7) || (p1==7 && p2==2)) {pions[p1-1]=pions[p1-1]-1; pions[p2-1]=pions[p2-1]-1; pions[11-1]=pions[11-1]+1; return 11;}

		if ((p1==3 && p2==12) || (p1==12 && p2==3)) {pions[p1-1]=pions[p1-1]-1; pions[p2-1]=pions[p2-1]-1; pions[15-1]=pions[15-1]+1; return 15;}
		if ((p1==3 && p2==13) || (p1==13 && p2==3)) {pions[p1-1]=pions[p1-1]-1; pions[p2-1]=pions[p2-1]-1; pions[18-1]=pions[18-1]+1; return 18;}
		if ((p1==3 && p2==14) || (p1==14 && p2==3)) {pions[p1-1]=pions[p1-1]-1; pions[p2-1]=pions[p2-1]-1; pions[17-1]=pions[17-1]+1; return 17;}

		if ((p1==4 && p2==12) || (p1==12 && p2==4)) {pions[p1-1]=pions[p1-1]-1; pions[p2-1]=pions[p2-1]-1; pions[17-1]=pions[17-1]+1; return 17;}
		if ((p1==4 && p2==13) || (p1==13 && p2==4)) {pions[p1-1]=pions[p1-1]-1; pions[p2-1]=pions[p2-1]-1; pions[16-1]=pions[16-1]+1; return 16;}
		if ((p1==4 && p2==14) || (p1==14 && p2==4)) {pions[p1-1]=pions[p1-1]-1; pions[p2-1]=pions[p2-1]-1; pions[18-1]=pions[18-1]+1; return 18;}

		if (p1>4 && p1<12) /*blanc*/ if ((p2>2 && p2<5) || (p2>11 && p2<19)) pions[p2-1]=pions[p2-1]-1;
		if (p1>11 && p1<19) /*noir*/ if ((p2>0 && p2<3) || (p2>4 && p2<12)) pions[p2-1]=pions[p2-1]-1;
	}

	if (p1==0) printf("p1=0");

	return p1;
}

int * convertCoordonnees (char c, int n) {
	int x, y;
	int * t;

	x=0; y=0;

	t = malloc(sizeof(int)*2);

	if (c=='A'||c=='a') y=0;
	else if (c=='B'||c=='b') y=1;
	else if (c=='C'||c=='c') y=2;
	else if (c=='D'||c=='d') y=3;
	else if (c=='E'||c=='e') y=4;
	else if (c=='F'||c=='f') y=5;
	else if (c=='G'||c=='g') y=6;
	else if (c=='H'||c=='h') y=7;
	else printf("Erreur sur le charactere entre.");

	if (n==8) x=0;
	else if (n==7) x=1;
	else if (n==6) x=2;
	else if (n==5) x=3;
	else if (n==4) x=4;
	else if (n==3) x=5;
	else if (n==2) x=6;
	else if (n==1) x=7;
	else printf("Erreur sur le chiffre entre.");

	t[0]=x;
	t[1]=y;

	return t;
}

int * convertCoordonnees2 (int * t, char c, int n) {
	int x, y;

	x=0; y=0;

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

int * convertCoordonnees3 (char c, int n) {
	int x, y;

	int * t;

	x=0; y=0;

	t = malloc(2*sizeof(int));

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

void affiche (int t[][8], int coordonnees, int nombreDespaces) {
	int i,j,k, l, cc, c, s;

	l=8; cc=nombreDespaces; c=cc; s=2+(cc-5);

	printf("\nLegende : \n\no,@ : pion rond\n+,# : pion carre\n\no et + representent le joueur blanc\n@ et # representent le joueur noir\n\n\nVoici le plateau de jeu : \n\n\n");

	if (cc<2) {cc=2; c=cc; }

	if (s<1) s=1; /*s = nombre de sauts de lignes.  */

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

		for (k=0; k<s; k++) printf("\n");

	}

	else {
		for (k=0; k<c+1; k++) printf(" ");

		for (i=0; i<8; i++) {
			printf("%d",(i+1));
			for (k=0; k<c; k++) printf(" ");
		}

		for (k=0; k<s; k++) printf("\n");
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

			c=cc;
		}

		for (k=0; k<s; k++) printf("\n");
	} /*temporaire  */
}

/*public static int menuPrincipal () {
		int a;
		a=0;

		while (a!=1) {
			a=0;

			printf("\nJeu de Gonki : \n\n\nMenu principal : \n\n1 : Jouer\n? = ");
			scanf("%d",&a);
		}

		return a;		
	}*/

int menuPrincipal () {
	int a;
	a=0;

	while (a!=1 && a!=2) {
		a=0;

		printf("\nJeu de Gonki : \n\n\nMenu principal : \n\n1 : Jouer\n2 : Options\n3 : Quitter\n? = ");
		scanf("%d",&a);

		if (a==3) exit(0);
	}

	return a;		
}

int demandeOptions (int placement, int commence) {
	int a;
	a=0;

	while (a!=1 && a!=2 && a!=3 && a!=4 && a!=5) {
		a=0;

		printf("\nOptions : \n\n1 : Modifier l'affichage des coordonees\n2 : Nombre d'espaces affiches dans la grille de jeu\n3 : Placement des pions : %s\n4 : Qui commence : %s\n5 : Retour\n? = ",((placement==0)?"les blancs jouent en haut, les noirs en bas.":"les noirs jouent en haut, les blancs en bas."),((commence==0)?"les blancs.":"les noirs."));
		scanf("%d",&a);
	}

	return a;
}

int demandeCommence () {
	int a;
	a=0;

	while (a!=1 && a!=2 && a!=3) {
		a=0;

		printf("\nChoisissez qui commence : \n1 : Les blancs\n2 : Les noirs\n3 : Retour\n? = ");
		scanf("%d",&a);
	}

	return a;
}

int demandePlacement () {
	int a;
	a=0;

	while (a!=1 && a!=2 && a!=3) {
		a=0;

		printf("\nChoisissez le placement des pions : \n1 : Les blancs jouent en haut, les noirs en bas\n2 : Les noirs jouent en haut, les blancs en bas\n3 : Retour\n? = ");
		scanf("%d",&a);
	}

	return a;
}

int MenuCoup () {
	int a;
	a=0;

	while (a!=1 && a!=2) {
		a=0;

		printf("\n1 : Jouer un coup\n2 : Quitter la partie et revenir au menu principal\n? = ");
		scanf("%d",&a);
	}

	return a;
}

int EtesVousSur () {
	int a;
	a=0;

	while (a!=1 && a!=2) {
		a=0;

		printf("Etes-vous sur de vouloir quitter \nla partie et revenir au menu principal?\n1 : Oui\n2 : Non\n? = ");
		scanf("%d",&a);
	}

	return a;
}

int OptionsNombreDespaces (int esp) {
	int a;
	a=-1;

	while (a<0 || a>50) {
		a=-1;

		printf("\nVeuillez entrer le nombre d'espaces a afficher dans la grille (%d actuellement) : \n(5 par defaut) : \n? = ",esp);
		scanf("%d",&a);
	}

	return a;
}

int OptionsCoordonees () {
	int a;
	a=0;

	while (a!=1 && a!=2 && a!=3) {
		a=0;

		printf("\nModifier l'affichage des coordonnees : \n\n1 : Affichage par lettres et chiffres\n2 : Affichge par chiffres\n3 : Retour\n? = ");
		scanf("%d",&a);
	}

	return a;
}

int convertNombre (char s) {
	int c, d;
	c=0; d=0;

	if (s=='0') c=0;
	if (s=='1') c=1;
	if (s=='2') c=2;
	if (s=='3') c=3;
	if (s=='4') c=4;
	if (s=='5') c=5;
	if (s=='6') c=6;
	if (s=='7') c=7;
	if (s=='8') c=8;
	if (s=='9') c=9;

	d=c;

	if (d<0) printf("\n//Le nombre est trop grand\n");

	return d;
}

int convertNombre1 (char * s) {
	int i, a, c, d;
	a = calculeTaille(s); c=0; d=0;

	if (!s) {
		printf("\n\n//Le char * est null : convertion impossible.\n");
	}

	if (a==1) {
		if (s[0]=='0') c=0;
		if (s[0]=='1') c=1;
		if (s[0]=='2') c=2;
		if (s[0]=='3') c=3;
		if (s[0]=='4') c=4;
		if (s[0]=='5') c=5;
		if (s[0]=='6') c=6;
		if (s[0]=='7') c=7;
		if (s[0]=='8') c=8;
		if (s[0]=='9') c=9;

		d=c;
	}else {
		for (i=0; i<a; i++) {
			c=-1;
			if (s[i]=='0') c=0;
			if (s[i]=='1') c=1;
			if (s[i]=='2') c=2;
			if (s[i]=='3') c=3;
			if (s[i]=='4') c=4;
			if (s[i]=='5') c=5;
			if (s[i]=='6') c=6;
			if (s[i]=='7') c=7;
			if (s[i]=='8') c=8;
			if (s[i]=='9') c=9;
			
			if (c!=-1) d=d*10+c;	
		}
	}

	if (d<0) printf("\n//Le nombre est trop grand");

	return d;
}

