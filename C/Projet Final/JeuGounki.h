void Jeu ();
int verifiePointCouleur (int couleur, int t[][8], int x, int y);
int demandeBase ();
int demandeMode ();
int transformeUnPion (int t[][8], int x, int y, int x1, int y1);
int * convertCoordonnees (char c, int n);
int menuPrincipal ();
int OptionsCoordonees ();
int compareStrSize (char * c1, int size1,char * c2, int size2);
int compareStr (char * c1, char * c2);
int publieDeplacePion (int t[][8], char * c3, int base, int sens, int x, int y, int forme);
int publieDeplacePionCompose (char * c3, int t[][8], int base, int sens, int x, int y, int ct, int p1);
char * convertitCoord2 (int x, int y);
int convertPieceInv (int p1);
int convertPiece (int couleur, int n);
void JeuTest (int configuration);
char * recupereExpr(int n);
int calculeTaille (char * s);
int analyseExprCoup (int t[][8], int taille, char * s, int configuration);
void remplitTabbleau (int t[][8], int configuration);
int verifiePointCouleur (int couleur, int t[][8], int x, int y);
int verifieFinJeu (int t[][8], int configuration);
int verifiePionFranchisLigne (int t[][8], int configuration);
int joueUnCoup (int lignes, int couleur, int base, int coordonnees,int t[][8]);
int demandeCouleur ();
int deplacePion (int t[][8], int * cChoix, int base, int sens, int x, int y);
int deplacePionTest (int t[][8], int base, int sens, int x, int y);
int demandeDeplaceCompose (int tr);
int detectePionSature (int t[][8], int x, int y, int x1, int y1);
int detectePourPion2 (int t[][8], int x, int y, int x1, int y1);
int detectePionAmi (int t[][8], int x, int y, int x1, int y1);
int detectePionAmi2 (int t[][8], int x, int y, int x1, int y1);
int deplacePionCompose (int t[][8], int * cChoix, int base, int sens, int x, int y, int ct);
int deplacePionComposeTest (int t[][8], int base, int sens, int x, int y, int ct);
int joueAleat (int t[][8], int couleur, int composition);
int * autoriseDeplacePion (int t[][8], int x, int y);
int transformeUnPion3 (int t[][8], int x, int y, int x1, int y1);
int * convertCoordonnees (char c, int n);
int * convertCoordonnees2 (int * t, char c, int n);
void affiche (int t[][8], int coordonnees, int nombreDespaces);
int demandeOptions (int placement, int commence);
int demandeCommence ();
int demandePlacement ();
int MenuCoup ();
int EtesVousSur ();
int OptionsNombreDespaces (int esp);
int convertNombre (char s);
int convertNombre1 (char * s);
int * convertCoordonnees3 (char c, int n);

/* DeploiePion.c */

int deploiePion (int t[][8], int base, int choix, int sens1, int sens2, int x, int y);
int publieDeploiePion (int t[][8], char * c5, int base, int choix, int sens1, int sens2, int x, int y, int p1);
int DemandeDeploiePion (int lignes, int * cChoix, int coordonnees, int t[][8], int base, int x, int y);
int * AutoriseDeploiement (int t[][8], int x, int y);
int detecteDeploiement (int t[][8], int base, int choix, int sens1, int sens2, int x,  int y);
int transformeUnPion2 (int t[][8], int p1, int x1, int y1);
int * convertCoordonnees (char c, int n);
