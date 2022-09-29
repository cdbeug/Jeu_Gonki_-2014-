#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TestString.h"

int * pions;

int main () {
	JeuTest(0);

	return 0;
}

void JeuTest (int configuration) {
	int i,j, n=0, finJeu=0;
	char * s;
	char * s1;
	int t[8][8];

	remplitTabbleau(t,configuration);

	while (1) {
		printf("\nCoup %d : \n",n);
		affiche(t,1,3); //t,afCoordonnees,esp.
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
				printf("\n%s\n\n\nLe joueur noirs a gagne !!!\n\n\n",s1);
			}

			exit(0);
		}

		printf("Entrez un coup : ");
		s = recupereExpr(11);

		//printf("%s\ncalculeTaille(s) : %d",s,calculeTaille(s));

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
	int i, cmp=0;

	for (i=0; (s[i]!='\0'&&s[i]!=' '); i++) cmp++;

	return cmp-1;
}

int analyseExprCoup (int t[][8], int taille, char * s, int configuration) {
	int i,j, p1=0, p2=0, p3=0, p4=0, cr=0, cc=0, slength = taille, x1=0,x2=0,x3=0,x4=0,y1=0,y2=0,y3=0,y4=0, base=0, sens1=0, sens2=0, tmp=-1, ct=0, plus_etoile=0;
	int rond_carre=0;
	char * s1;
	int * t1 = malloc(2*sizeof(int));
	int t2[60];
	int t3[60];

	/*
		-plus_etoile : 0 : * (rond d'abord], 1 : + (carre d'abord)
	*/

	for (i=0; i<60; i++) {t2[i]=0; t3[i]=0;}

	if (slength<5) return 0;

	if (slength==6) {if (s[5]!='#') return 0; else {
		s1 = malloc (6*sizeof(char));
		for (i=0; i<5; i++) s1[i]=s[i];
		s1[5]='\0';
		free(s);
		s=malloc(6*sizeof(char));
		for (i=0; i<5; i++) s[i]=s1[i];
		s[5]='\0';
		free(s1);
		slength=5;
	}} // on choisit de rendre l'opérateur # sans signification (le dépassement et la fin du jeu étant signalée par un message le cas échéant).

	if (slength>5 && s[2]!='*' && s[2]!='+') return 0;
	if (slength==9) {if (s[8]!='#') return 0; else {
		s1 = malloc (9*sizeof(char));
		for (i=0; i<8; i++) s1[i]=s[i];
		s1[8]='\0';
		free(s);
		s=malloc(9*sizeof(char));
		for (i=0; i<8; i++) s[i]=s1[i];
		s[8]='\0';
		free(s1);
		slength=8;
	}}

	if (slength==12) {if (s[11]!='#') return 0; else {
		s1 = malloc (11*sizeof(char));
		for (i=0; i<11; i++) s1[i]=s[i];
		s1[11]='\0';
		free(s);
		s=malloc(11*sizeof(char));
		for (i=0; i<11; i++) s[i]=s1[i];
		s[11]='\0';
		free(s1);
		slength=11;
	}}

	/*récupération des données*/

	/*deplacement de pions*/


	if (slength==5) {
		if (s[2]!='-') return 0;

		t1 = convertCoordonnees2(t1,s[0],convertNombre(s[1]));
		if (t1[0]>7 || t1[0]<0) return 0;
		if (t1[1]>7 || t1[1]<0) return 0;
		x1=t1[0];
		y1=t1[1];

		//printf("t1[0] = %d\nt1[1] = %d\nx1 = %d\ny1 = %d\n",t1[0],t1[1],x1,y1);

		t1 = convertCoordonnees2(t1,s[3],convertNombre(s[4]));
		if (t1[0]>7 || t1[0]<0) return 0;
		if (t1[1]>7 || t1[1]<0) return 0;
		x2=t1[0];
		y2=t1[1];

		//printf("t1[0] = %d\nt1[1] = %d\nx2 = %d\ny2 = %d",t1[0],t1[1],x2,y2);
	}

	/*deploiement*/

	if (slength>5) { //deploiement
		if (slength==8) { //2 pièces
			if (s[5]!='-') return 0;

			t1 = convertCoordonnees2(t1,s[0],convertNombre(s[1]));
			if (t1[0]>7 || t1[0]<0) return 0;
			if (t1[1]>7 || t1[1]<0) return 0;
			x1=t1[0];
			y1=t1[1];

			//printf("t1[0] = %d\nt1[1] = %d\nx1 = %d\ny1 = %d",t1[0],t1[1],x1,y1);

			t1 = convertCoordonnees2(t1,s[3],convertNombre(s[4]));
			if (t1[0]>7 || t1[0]<0) return 0;
			if (t1[1]>7 || t1[1]<0) return 0;
			x2=t1[0];
			y2=t1[1];

			//printf("t1[0] = %d\nt1[1] = %d\nx2 = %d\ny2 = %d",t1[0],t1[1],x2,y2);

			t1 = convertCoordonnees2(t1,s[6],convertNombre(s[7]));
			if (t1[0]>7 || t1[0]<0) return 0;
			if (t1[1]>7 || t1[1]<0) return 0;
			x3=t1[0];
			y3=t1[1];

			//printf("t1[0] = %d\nt1[1] = %d\nx3 = %d\ny3 = %d",t1[0],t1[1],x3,y3);
		}

		if (slength==11) { //3 pièces
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

			//printf("t1[0] = %d\nt1[1] = %d\nx3 = %d\ny3 = %d",t1[0],t1[1],x3,y3);

			t1 = convertCoordonnees2(t1,s[9],convertNombre(s[10]));
			if (t1[0]>7 || t1[0]<0) return 0;
			if (t1[1]>7 || t1[1]<0) return 0;
			x4=t1[0];
			y4=t1[1];

			//printf("t1[0] = %d\nt1[1] = %d\nx4 = %d\ny4 = %d",t1[0],t1[1],x4,y4);
		}
	}

	//printf("x1 = %d\ny1 = %d\nx2 = %d\ny2 = %d\nx3 = %d\ny3 = \nx4 = %d\ny4 = %d",x1,y1,x2,y2,x3,y3,x4,y4);
}

int * convertCoordonnees (int * t, char c, int n) {
	int x=0, y=0;


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

int * convertCoordonnees2 (int * t, char c, int n) {
	int x=0, y=0;


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

int convertNombre (char s) {
	int c=0, d=0;

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


void remplitTabbleau (int t[][8], int configuration) { /*remplit le tableau avec la configuration initiale du plateau de jeu*/
	int i,j;

	pions = malloc(18*sizeof(int));

	for (i=0; i<4; i++) pions[i] = 8; // initialisation du nombre de pions

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

void affiche (int t[][8], int coordonnees, int nombreDespaces) {
	int i,j,k, l=8, cc=nombreDespaces, c=cc, s=2+(cc-5);

	printf("\nLegende : \n\no,@ : pion rond\n+,# : pion carre\n\no et + representent le joueur blanc\n@ et # representent le joueur noir\n\n\nVoici le plateau de jeu : \n\n\n");

	if (cc<2) {cc=2; c=cc; }

	if (s<1) s=1; //s = nombre de sauts de lignes.

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
	}
}

int verifieFinJeu (int t[][8], int configuration) {
	int i, g1=0, g2=0;

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
	else { //g1!=0 et g2!=0
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
