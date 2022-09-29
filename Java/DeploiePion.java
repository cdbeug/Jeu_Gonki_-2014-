import java.util.Scanner;

class DeploiePion extends JeuGounki {
	public static boolean deploiePion (int [][] t, int base, int choix, int sens1, int sens2, int x, int y) {
		int i,j,l, p1=0, forme=1, cr=0, cc=0, couleur=0, ff1=0, ff2=0, x1=0, y1=0;

		/*
			-choix : 0 : rond-carre, 1 : carre-rond.
		*/

		if (x<0 || y<0 || x>7 || y>7) return false;

		p1=t[x][y];

		if (p1<12 && p1>4) couleur=0;
		else couleur=1;

		if (p1==5||p1==12) {cr=2; cc=0;}
		if (p1==6||p1==13) {cr=0; cc=2;}
		if (p1==7||p1==14) {cr=1; cc=1;}
		if (p1==8||p1==15) {cr=3; cc=0;}
		if (p1==9||p1==16) {cr=0; cc=3;}
		if (p1==10||p1==17) {cr=2; cc=1;}
		if (p1==11||p1==18) {cr=1; cc=2;}

		if (cr>0 && cc>0) forme=3; //rond-carre
		if (cr==0 && cc>0) forme=2; //carre
		if (cr>0 && cc==0) forme=1; //rond

		if (forme==1) if (couleur==0) ff1=1; else ff1=3;
		if (forme==2) if (couleur==0) ff1=2; else ff1=4;
		if (forme==3) {
			if (choix==0) { //rond-carre
				if (couleur==0) ff1=1; else ff1=3;
				if (couleur==0) ff2=2; else ff2=4;
			}

			if (choix==1) { //carre-rond
				if (couleur==0) ff1=2; else ff1=4;
				if (couleur==0) ff2=1; else ff2=3;
			}
		}

		//System.out.println("Couleur : "+couleur+"\nforme : "+forme+"\nff1 : "+ff1+"\nff2 : "+ff2);

		if (base==0) { // en bas.
			if (forme==1) {//rond
				if (sens1==0) {
					if (x-cr<0 || y-cr<0) return false;

					t[x][y] = 0;

					for (i=1; i<cr+1; i++) {
						t[x-i][y-i] = transformeUnPion2(t,ff1,x-i,y-i);
					}
				}

				if (sens1==1) {
					if (x-cr<0 || y+cr>7) return false;

					t[x][y] = 0;

					for (i=1; i<cr+1; i++) {
						t[x-i][y+i] = transformeUnPion2(t,ff1,x-i,y+i);
					}
				}
				
			}

			if (forme==2) {//carre
				if (sens1==0) {
					if (y-cc<0) return false;

					t[x][y] = 0;

					for (i=1; i<cc+1; i++) {
						t[x][y-i] = transformeUnPion2(t,ff1,x,y-i);
					}
				}

				if (sens1==1) {
					if (y+cc>7) return false;

					t[x][y] = 0;

					for (i=1; i<cc+1; i++) {
						t[x][y+i] = transformeUnPion2(t,ff1,x,y+i);
					}
				}

				if (sens1==2) {
					if (x-cc<0) return false;

					t[x][y] = 0;

					for (i=1; i<cc+1; i++) {
						t[x-i][y] = transformeUnPion2(t,ff1,x-i,y);
					}
				}
				
			}

			if (forme==3) {//rond-carre
				if (choix==0) {
					if (sens1==0) {
						if (x-cr<0 || y-cr<0) return false;

						t[x][y] = 0;
						
						for (i=1; i<cr+1; i++) {
							t[x-i][y-i] = transformeUnPion2(t,ff1,x-i,y-i);
						}

						x1=x-(i-1);
						y1=y-(i-1);
					}
					
					if (sens1==1) {
						if (x-cr<0 || y+cr>7) return false;
						System.out.println("blabla1");

						t[x][y] = 0;
						
						for (i=1; i<cr+1; i++) {
							t[x-i][y+i] = transformeUnPion2(t,ff1,x-i,y+i);
						}

						x1=x-(i-1);
						y1=y+(i-1);
					}

					if (sens2==0) {
						if (y1-cc<0) return false;
						
						for (i=1; i<cc+1; i++) {
							t[x1][y1-i] = transformeUnPion2(t,ff2,x1,y1-i);
						}
					}
					
					if (sens2==1) {
						if (y1+cc>7) return false;

						for (i=1; i<cc+1; i++) {
							t[x1][y1+i] = transformeUnPion2(t,ff2,x1,y1+i);
						}
					}
					
					if (sens2==2) {
						if (x1-cc<0) return false;
						System.out.println("blabla2");
						
						for (i=1; i<cc+1; i++) {
							t[x1-i][y1] = transformeUnPion2(t,ff2,x1-i,y1);
							System.out.println("x1 = "+x1+"\ny1 = "+y1);
						}
					}
				}

				if (choix==1) {
					if (sens1==0) {
						if (y-cc<0) return false;

						t[x][y] = 0;
						
						for (i=1; i<cc+1; i++) {
							t[x][y-i] = transformeUnPion2(t,ff1,x,y-i);
						}

						x1=x;
						y1=y-(i-1);
					}
					
					if (sens1==1) {
						if (y+cc>7) return false;

						t[x][y] = 0;
						
						for (i=1; i<cc+1; i++) {
							t[x][y+i] = transformeUnPion2(t,ff1,x,y+i);
						}

						x1=x;
						y1=y+(i-1);
					}
					
					if (sens1==2) {
						if (x-cc<0) return false;

						t[x][y] = 0;
						
						for (i=1; i<cc+1; i++) {
							t[x-i][y] = transformeUnPion2(t,ff1,x-i,y);
						}

						x1=x-(i-1);
						y1=y;
					}
					
					if (sens2==0) {
						if (x1-cr<0 || y1-cr<0) return false;
						
						for (i=1; i<cr+1; i++) {
							t[x1-i][y1-i] = transformeUnPion2(t,ff2,x1-i,y1-i);
						}
					}
					
					if (sens2==1) {
						if (x1-cr<0 || y1+cr>7) return false;
						
						for (i=1; i<cr+1; i++) {
							t[x1-i][y1+i] = transformeUnPion2(t,ff2,x1-i,y1+i);
						}
					}
				}
				
			}
		}

		if (base==1) { // en haut.
			if (forme==1) {//rond
				if (sens1==0) {
					if (x+cr>7 || y-cr<0) return false;

					t[x][y] = 0;

					for (i=1; i<cr+1; i++) {
						t[x+i][y-i] = transformeUnPion2(t,ff1,x+i,y-i);
					}
				}

				if (sens1==1) {
					if (x+cr>7 || y+cr>7) return false;

					t[x][y] = 0;

					for (i=1; i<cr+1; i++) {
						t[x+i][y+i] = transformeUnPion2(t,ff1,x+i,y+i);
					}
				}
				
			}

			if (forme==2) {//carre
				if (sens1==0) {
					if (y-cc<0) return false;

					t[x][y] = 0;

					for (i=1; i<cc+1; i++) {
						t[x][y-i] = transformeUnPion2(t,ff1,x,y-i);
					}
				}

				if (sens1==1) {
					if (y+cc>7) return false;

					t[x][y] = 0;

					for (i=1; i<cc+1; i++) {
						t[x][y+i] = transformeUnPion2(t,ff1,x,y+i);
					}
				}

				if (sens1==2) {
					if (x+cc>7) return false;

					t[x][y] = 0;

					for (i=1; i<cc+1; i++) {
						t[x+i][y] = transformeUnPion2(t,ff1,x+i,y);
					}
				}
				
			}

			if (forme==3) {//rond-carre
				if (choix==0) {
					if (sens1==0) {
						if (x+cr>7 || y-cr<0) return false;

						t[x][y] = 0;

						for (i=1; i<cr+1; i++) {
							t[x+i][y-i] = transformeUnPion2(t,ff1,x+i,y-i);
						}

						x1=x+(i-1);
						y1=y-(i-1);
					}
					
					if (sens1==1) {
						if (x+cr>7 || y+cr>7) return false;

						t[x][y] = 0;

						for (i=1; i<cr+1; i++) {
							t[x+i][y+i] = transformeUnPion2(t,ff1,x+i,y+i);
						}

						x1=x+(i-1);
						y1=y+(i-1);
					}

					if (sens2==0) {
						if (y1-cc<0) return false;

						for (i=1; i<cc+1; i++) {
							t[x1][y1-i] = transformeUnPion2(t,ff2,x1,y1-i);
						}
					}
					
					if (sens2==1) {
						if (y1+cc>7) return false;

						for (i=1; i<cc+1; i++) {
							t[x1][y1+i] = transformeUnPion2(t,ff2,x1,y1+i);
						}
					}
					
					if (sens2==2) {
						if (x1+cc>7) return false;
						
						for (i=1; i<cc+1; i++) {
							t[x1+i][y1] = transformeUnPion2(t,ff2,x1+i,y1);
						}
					}
				}

				if (choix==1) {
					if (sens1==0) {
						if (y-cc<0) return false;

						t[x][y] = 0;
						
						for (i=1; i<cc+1; i++) {
							t[x][y-i] = transformeUnPion2(t,ff1,x,y-i);
						}

						x1=x;
						y1=y-(i-1);
					}
					
					if (sens1==1) {
						if (y+cc>7) return false;

						t[x][y] = 0;
						
						for (i=1; i<cc+1; i++) {
							t[x][y+i] = transformeUnPion2(t,ff1,x,y+i);
						}

						x1=x;
						y1=y+(i-1);
					}
					
					if (sens1==2) {
						if (x+cc>7) return false;

						t[x][y] = 0;
						
						for (i=1; i<cc+1; i++) {
							t[x+i][y] = transformeUnPion2(t,ff1,x+i,y);
						}

						x1=x+(i-1);
						y1=y;
					}
					
					if (sens2==0) {
						if (x1+cr>7 || y1-cr<0) return false;

						for (i=1; i<cr+1; i++) {
							t[x1+i][y1-i] = transformeUnPion2(t,ff2,x1+i,y1-i);
						}
					}
					
					if (sens2==1) {
						if (x1+cr>7 || y1+cr>7) return false;

						for (i=1; i<cr+1; i++) {
							t[x1+i][y1+i] = transformeUnPion2(t,ff2,x1+i,y1+i);
						}
					}
				}
				
			}
		}

		pions[p1-1]=pions[p1-1]-1; //Mise à
		if (couleur==0) {pions[1-1]=pions[1-1]+cr; pions[2-1]=pions[2-1]+cc;} // jour
		if (couleur==1) {pions[3-1]=pions[3-1]+cr; pions[4-1]=pions[4-1]+cc;} // de pions.
		
		return true;
	}

	public static boolean publieDeploiePion (int [][] t, char [] c5, int base, int choix, int sens1, int sens2, int x, int y, int p1) {
		int i,j,l, cc=0, cr=0, forme=1, couleur=0, ff1=0, ff2=0, x1=0, y1=0, x2=0,y2=0,x3=0,y3=0,x4=0,y4=0;

		/*
			-choix : 0 : rond-carre, 1 : carre-rond.
		*/

		if (x<0 || y<0 || x>7 || y>7) return false;

		if (p1<12 && p1>4) couleur=0;
		else couleur=1;

		if (p1==5||p1==12) {cr=2; cc=0;}
		if (p1==6||p1==13) {cr=0; cc=2;}
		if (p1==7||p1==14) {cr=1; cc=1;}
		if (p1==8||p1==15) {cr=3; cc=0;}
		if (p1==9||p1==16) {cr=0; cc=3;}
		if (p1==10||p1==17) {cr=2; cc=1;}
		if (p1==11||p1==18) {cr=1; cc=2;}

		if (cr>0 && cc>0) forme=3; //rond-carre
		if (cr==0 && cc>0) forme=2; //carre
		if (cr>0 && cc==0) forme=1; //rond

		if (forme==1) if (couleur==0) ff1=1; else ff1=3;
		if (forme==2) if (couleur==0) ff1=2; else ff1=4;
		if (forme==3) {
			if (choix==0) { //rond-carre
				if (couleur==0) ff1=1; else ff1=3;
				if (couleur==0) ff2=2; else ff2=4;
			}

			if (choix==1) { //carre-rond
				if (couleur==0) ff1=2; else ff1=4;
				if (couleur==0) ff2=1; else ff2=3;
			}
		}

		char [] c1 = new char[1];
		char [] c2 = new char[1];
		char [] c3 = new char[1];
		char [] c4 = new char[1];

		//System.out.println("Couleur : "+couleur+"\nforme : "+forme+"\nff1 : "+ff1+"\nff2 : "+ff2);

		if (base==0) { // en bas.
			if (forme==1) {//rond
				if (sens1==0) {
					if (x-cr<0 || y-cr<0) return false;

					if (cr==2) {
						x2=x-1;
						y2=y-1;

						x3=x-2;
						y3=y-2;
					}

					if (cr==3) {
						x2=x-1;
						y2=y-1;

						x3=x-2;
						y3=y-2;

						x4=x-3;
						y4=y-3;
					}
				}

				if (sens1==1) {
					if (x-cr<0 || y+cr>7) return false;


					if (cr==2) {
						x2=x-1;
						y2=y+1;

						x3=x-2;
						y3=y+2;
					}

					if (cr==3) {
						x2=x-1;
						y2=y+1;

						x3=x-2;
						y3=y+2;

						x4=x-3;
						y4=y+3;
					}
				}				
			}

			if (forme==2) {//carre
				if (sens1==0) {
					if (y-cc<0) return false;

					if (cc==2) {
						x2=x;
						y2=y-1;

						x3=x;
						y3=y-2;
					}

					if (cc==3) {
						x2=x;
						y2=y-1;

						x3=x;
						y3=y-2;

						x3=x;
						y3=y-3;
					}
				}

				if (sens1==1) {
					if (y+cc>7) return false;

					if (cc==2) {
						x2=x;
						y2=y+1;

						x3=x;
						y3=y+2;
					}

					if (cc==3) {
						x2=x;
						y2=y+1;

						x3=x;
						y3=y+2;

						x3=x;
						y3=y+3;
					}
				}

				if (sens1==2) {
					if (x-cc<0) return false;

					if (cc==2) {
						x2=x-1;
						y2=y;

						x3=x-2;
						y3=y;
					}

					if (cc==3) {
						x2=x-1;
						y2=y;

						x3=x-2;
						y3=y;

						x3=x-3;
						y3=y;
					}
				}				
			}

			if (forme==3) {//rond-carre
				if (choix==0) {
					if (sens1==0) {
						if (x-cr<0 || y-cr<0) return false;

						if (cr==1) {
							x2=x-1;
							y2=y-1;
						}

						if (cr==2) {
							x2=x-1;
							y2=y-1;
	
							x3=x-2;
							y3=y-2;
						}

						x1=x-(cr-1);
						y1=y-(cr-1);
					}
					
					if (sens1==1) {
						if (x-cr<0 || y+cr>7) return false;
						
						if (cr==1) {
							x2=x-1;
							y2=y+1;
						}

						if (cr==2) {
							x2=x-1;
							y2=y+1;
	
							x3=x-2;
							y3=y+2;
						}

						x1=x-(cr-1);
						y1=y+(cr-1);
					}

					if (sens2==0) {
						if (y1-cc<0) return false;

						if (cc==1) {
							x2=x1;
							y2=y1-1;
						}	
							
						if (cc==2) {
							x2=x1;
							y2=y1-1;
	
							x3=x1;
							y3=y1-2;
						}
					}
					
					if (sens2==1) {
						if (y1+cc>7) return false;

						if (cc==1) {
							x2=x1;
							y2=y1+1;
						}

						if (cc==2) {
							x2=x1;
							y2=y1+1;
	
							x3=x1;
							y3=y1+2;
						}
					}
					
					if (sens2==2) {
						if (x1-cc<0) return false;

						if (cc==1) {
							x2=x1-1;
							y2=y1;
						}
						
						if (cc==2) {
							x2=x1-1;
							y2=y1;
	
							x3=x1-2;
							y3=y1;
						}
					}
				}

				if (choix==1) {
					if (sens1==0) {
						if (y-cc<0) return false;

						if (cc==1) {
							x2=x;
							y2=y-1;
						}
						
						if (cc==2) {
							x2=x;
							y2=y-1;
	
							x3=x;
							y3=y-2;
						}
	
						x1=x;
						y1=y-(cc-1);
					}
					
					if (sens1==1) {
						if (y+cc>7) return false;
						
						if (cc==1) {
							x2=x;
							y2=y+1;
						}
						
						if (cc==2) {
							x2=x;
							y2=y+1;
	
							x3=x;
							y3=y+2;
						}

						x1=x;
						y1=y+(cc-1);
					}
					
					if (sens1==2) {
						if (x-cc<0) return false;

						if (cc==1) {
							x2=x-1;
							y2=y;
						}

						if (cc==2) {
							x2=x-1;
							y2=y;
	
							x3=x-2;
							y3=y;
						}

						x1=x-(cc-1);
						y1=y;
					}
					
					if (sens2==0) {
						if (x1-cr<0 || y1-cr<0) return false;

						if (cr==1) {
							x2=x1-1;
							y2=y1-1;
						}

						if (cr==2) {
							x2=x1-1;
							y2=y1-1;
	
							x3=x1-2;
							y3=y1-2;
						}
					}
					
					if (sens2==1) {
						if (x1-cr<0 || y1+cr>7) return false;
						
						if (cr==1) {
							x2=x1-1;
							y2=y1+1;
						}

						if (cr==2) {
							x2=x1-1;
							y2=y1+1;
	
							x3=x1-2;
							y3=y1+2;
						}
					}
				}				
			}
		}

		if (base==1) { // en haut.
			if (forme==1) {//rond
				if (sens1==0) {
					if (x+cr>7 || y-cr<0) return false;

					if (cr==2) {
						x2=x+1;
						y2=y-1;

						x3=x+2;
						y3=y-2;
					}

					if (cr==3) {
						x2=x+1;
						y2=y-1;

						x3=x+2;
						y3=y-2;

						x4=x+3;
						y4=y-3;
					}
				}

				if (sens1==1) {
					if (x+cr>7 || y+cr>7) return false;

					System.out.println("cr = "+cr+"\ncc = "+cc+"\nok1");

					if (cr==2) {
						x2=x+1;
						y2=y+1;

						x3=x+2;
						y3=y+2;
					}

					if (cr==3) {
						x2=x+1;
						y2=y+1;

						x3=x+2;
						y3=y+2;

						x4=x+3;
						y4=y+3;
					}

					System.out.println("c1 = "+x+" "+y+"\nc2 = "+x2+" "+y2+"\nc3 = "+x3+" "+y3);
				}				
			}

			if (forme==2) {//carre
				if (sens1==0) {
					if (y-cc<0) return false;

					if (cc==2) {
						x2=x;
						y2=y-1;

						x3=x;
						y3=y-2;
					}

					if (cc==3) {
						x2=x;
						y2=y-1;

						x3=x;
						y3=y-2;

						x3=x;
						y3=y-3;
					}
				}

				if (sens1==1) {
					if (y+cc>7) return false;

					if (cc==2) {
						x2=x;
						y2=y+1;

						x3=x;
						y3=y+2;
					}

					if (cc==3) {
						x2=x;
						y2=y+1;

						x3=x;
						y3=y+2;

						x3=x;
						y3=y+3;
					}
				}

				if (sens1==2) {
					if (x+cc>7) return false;

					if (cc==2) {
						x2=x+1;
						y2=y;

						x3=x+2;
						y3=y;
					}

					if (cc==3) {
						x2=x+1;
						y2=y;

						x3=x+2;
						y3=y;

						x3=x+3;
						y3=y;
					}
				}				
			}

			if (forme==3) {//rond-carre
				if (choix==0) {
					if (sens1==0) {
						if (x+cr>7 || y-cr<0) return false;

						if (cr==1) {
							x2=x+1;
							y2=y-1;
						}

						if (cr==2) {
							x2=x+1;
							y2=y-1;
	
							x3=x+2;
							y3=y-2;
						}

						x1=x+(cr-1);
						y1=y-(cr-1);
					}
					
					if (sens1==1) {
						if (x+cr>7 || y+cr>7) return false;

						if (cr==1) {
							x2=x+1;
							y2=y+1;
						}

						if (cr==2) {
							x2=x+1;
							y2=y+1;
	
							x3=x+2;
							y3=y+2;
						}
	
						x1=x+(cr-1);
						y1=y+(cr-1);
					}

					if (sens2==0) {
						if (y1-cc<0) return false;

						if (cc==1) {
							x2=x1;
							y2=y1-1;
						}

						if (cc==2) {
							x2=x1;
							y2=y1-1;
	
							x3=x1;
							y3=y1-2;
						}
					}
					
					if (sens2==1) {
						if (y1+cc>7) return false;

						if (cc==1) {
							x2=x1;
							y2=y1+1;
						}

						if (cc==2) {
							x2=x1;
							y2=y1+1;
	
							x3=x1;
							y3=y1+2;
						}
					}
					
					if (sens2==2) {
						if (x1+cc>7) return false;

						if (cc==1) {
							x2=x1+1;
							y2=y1;
						}
						
						if (cc==2) {
							x2=x1;
							y2=y1+1;
	
							x3=x1;
							y3=y1+2;
						}
					}
				}

				if (choix==1) {
					if (sens1==0) {
						if (y-cc<0) return false;

						if (cc==1) {
							x2=x;
							y2=y-1;
						}
						
						if (cc==2) {
							x2=x;
							y2=y-1;
	
							x3=x;
							y3=y-2;
						}
	
						x1=x;
						y1=y-(cc-1);
					}
					
					if (sens1==1) {
						if (y+cc>7) return false;
						
						if (cc==1) {
							x2=x;
							y2=y+1;
						}
						
						if (cc==2) {
							x2=x;
							y2=y+1;
	
							x3=x;
							y3=y+2;
						}
	
						x1=x;
						y1=y+(cc-1);
					}
					
					if (sens1==2) {
						if (x+cc>7) return false;

						if (cc==1) {
							x2=x+1;
							y2=y;
						}
						
						if (cc==2) {
							x2=x+1;
							y2=y;
	
							x3=x+2;
							y3=y;
						}
	
						x1=x+(cc-1);
						y1=y;
					}
					
					if (sens2==0) {
						if (x1+cr>7 || y1-cr<0) return false;

						if (cr==1) {
							x2=x1+1;
							y2=y1-1;
						}

						if (cr==2) {
							x2=x1+1;
							y2=y1-1;
	
							x3=x1+2;
							y3=y1-2;
						}	
					}
					
					if (sens2==1) {
						if (x1+cr>7 || y1+cr>7) return false;

						if (cr==1) {
							x2=x1+1;
							y2=y1+1;
						}

						if (cr==2) {
							x2=x1+1;
							y2=y1+1;
	
							x3=x1+2;
							y3=y1+2;
						}
					}
				}				
			}
		}

		c1 = convertitCoord2(x,y);
		c2 = convertitCoord2(x2,y2);
		c3 = convertitCoord2(x3,y3);
		if (cc==3 || cr==3) c4 = convertitCoord2(x4,y4);

		System.out.println("sens1 = "+sens1+"\nsens2 = "+sens2+"\nchoix = "+choix);
		//System.out.println("c1 = "+x+" "+y+"\nc2 = "+x2+" "+y2+"\nc3 = "+x3+" "+y3);

		c5[0] = c1[0];
		c5[1] = c1[1];
		if (choix==0) c5[2]='*';
		else c5[2]='+';
		c5[3] = c2[0];
		c5[4] = c2[1];
		c5[5] = '-';
		c5[6] = c3[0];
		c5[7] = c3[1];

		if (cr==3 || cc==3) {
			c5[8] = '-';
			c5[9] = c4[0];
			c5[10] = c4[1];
		}
		
		return true;
	}

	public static boolean DemandeDeploiePion (int lignes, int [] cChoix, int coordonnees, int [][] t, int base, int x, int y) {
		int i,j, k, l, p1=0, ok=0, forme=1, choix=0, cr=0, cc=0, a=0, b=0, sens1=0, sens2=0, couleur=0, ff1=0, ff2=0, x1=0, y1=0, cmp=0;

		/*
			-choix : 0 : rond-carre, 1 : carre-rond.
		*/

		int [] t1 = AutoriseDeploiement(t,x,y);

		for (i=0; i<t1.length; i++) System.out.println("t1["+i+"] = "+t1[i]);

		if (x<0 || y<0 || x>7 || y>7) return false;

		p1=t[x][y];

		if (p1<12 && p1>4) couleur=0;
		else couleur=1;

		if (p1==5||p1==12) {cr=2; cc=0;}
		if (p1==6||p1==13) {cr=0; cc=2;}
		if (p1==7||p1==14) {cr=1; cc=1;}
		if (p1==8||p1==15) {cr=3; cc=0;}
		if (p1==9||p1==16) {cr=0; cc=3;}
		if (p1==10||p1==17) {cr=2; cc=1;}
		if (p1==11||p1==18) {cr=1; cc=2;}

		if (cr>0 && cc>0) forme=3; //rond-carre
		if (cr==0 && cc>0) forme=2; //carre
		if (cr>0 && cc==0) forme=1; //rond

		if (forme==1) if (couleur==0) ff1=1; else ff1=3;
		if (forme==2) if (couleur==0) ff1=2; else ff1=4;
		if (forme==3) {
			if (choix==0) { //rond-carre
				if (couleur==0) ff1=1; else ff1=3;
				if (couleur==0) ff2=2; else ff2=4;
			}

			if (choix==1) { //carre-rond
				if (couleur==0) ff1=2; else ff1=4;
				if (couleur==0) ff2=1; else ff2=3;
			}
		}

		System.out.println("Couleur : "+couleur+"\nforme : "+forme+"\nff1 : "+ff1+"\nff2 : "+ff2);

		if (t1[0]==1) return false;

		Scanner sc = new Scanner(System.in);

		if (base==0) { // en bas.
			if (forme==1) {//rond
				if (t1[0]!=5) return false;

				else {
					j=0;
					for (i=1; i<3; i++) {
						if (t1[i]==1) j=1;
					}

					if (j==0) return false;

					ok=0;
					cmp=0;
					while (a<1 || a>2 || ok==0) {
						a=0; ok=0;

						System.out.print("sens : \n");

						if (t1[1]==1) System.out.print("1 : gauche devant\n");
						if (t1[2]==1) System.out.print("2 : droite devant\n");

						System.out.print("? = ");

						ok=1;

						if (t1[1]==1&&t1[2]!=1) if (a==2) ok=0;
						if (t1[1]!=1&&t1[2]==1) if (a==1) ok=0;

						a = sc.nextInt();
						
						cmp++;
						
						if (cmp>=lignes) {
							cmp=0;
							affiche (t,coordonnees,lignes);
							System.out.print("\n");
						}
					}

					sens1=a-1;

					if (sens1==0) {
						if (x-cr<0 || y-cr<0) return false;

						t[x][y] = 0;

						for (i=1; i<cr+1; i++) {
							t[x-i][y-i] = transformeUnPion2(t,ff1,x-i,y-i);
						}
					}

					if (sens1==1) {
						if (x-cr<0 || y+cr>7) return false;

						t[x][y] = 0;

						for (i=1; i<cr+1; i++) {
							t[x-i][y+i] = transformeUnPion2(t,ff1,x-i,y+i);
						}
					}
				}
			}

			if (forme==2) {//carre
				if (t1[0]!=7) return false;

				else {
					j=0;
					for (i=1; i<4; i++) {
						if (t1[i]==1) j=1;
					}

					if (j==0) return false;

					ok=0;
					cmp=0;
					while (a<1 || a>3 || ok==0) {
						a=0; ok=0;

						System.out.print("sens : \n");

						if (t1[1]==1) System.out.print("1 : gauche\n");
						if (t1[2]==1) System.out.print("2 : droite\n");
						if (t1[3]==1) System.out.print("3 : milieu\n");

						System.out.print("? = ");

						a = sc.nextInt();

						ok=1;

						if (t1[1]==1&&t1[2]==1&&t1[3]!=1) if (a==3) ok=0;
						if (t1[2]==1&&t1[3]==1&&t1[1]!=1) if (a==1) ok=0;
						if (t1[1]==1&&t1[3]==1&&t1[2]!=1) if (a==2) ok=0;

						cmp++;
						
						if (cmp>=lignes) {
							cmp=0;
							affiche (t,coordonnees,lignes);
							System.out.print("\n");
						}
					}

					sens1=a-1;

					if (sens1==0) {
						if (y-cc<0) return false;

						t[x][y] = 0;

						for (i=1; i<cc+1; i++) {
							t[x][y-i] = transformeUnPion2(t,ff1,x,y-i);
						}
					}

					if (sens1==1) {
						if (y+cc>7) return false;

						t[x][y] = 0;

						for (i=1; i<cc+1; i++) {
							t[x][y+i] = transformeUnPion2(t,ff1,x,y+i);
						}
					}

					if (sens1==2) {
						if (x-cc<0) return false;

						t[x][y] = 0;

						for (i=1; i<cc+1; i++) {
							t[x-i][y] = transformeUnPion2(t,ff1,x-i,y);
						}
					}
				}
			}

			if (forme==3) {//rond-carre
				if (t1[0]!=35) return false;

				else {
					j=2;
					k=0;
					l=3;

					/*
						-l=3 : les deux sont correctes.
						-l=1 ou l=2 : 1 ou 2 seulement est correcte.
					*/


					for (i=1; i<3; i++) {
						if (t1[i]==1) k++;
					}
					if (k==0) j--; else l=1;

					k=0;
					for (i=9; i<12; i++) {
						if (t1[i]==1) k++;
					}
					if (k==0) j--; else l=2;
					if (j==2) l=3;
					if (j==0) return false;

					cmp=0;
					while (choix<1 || choix>2) {
						choix=0;
						System.out.print("Vous souhaitez commencer par deployer : ");
						if (l==1 || l==3) System.out.print("\n1 : Les ronds");
						if (l==2 || l==3) System.out.print("\n2 : Les carres");
						System.out.print("\n? = ");

						choix = sc.nextInt();

						if (l==1) if (choix==2) choix=0;
						if (l==2) if (choix==1) choix=0;
						
						cmp++;
						
						if (cmp>=lignes) {
							cmp=0;
							affiche (t,coordonnees,lignes);
							System.out.print("\n");
						}
					}

					choix--;

					if (choix==0) { //rond-carre
						if (couleur==0) ff1=1; else ff1=3;
						if (couleur==0) ff2=2; else ff2=4;
					}
					
					if (choix==1) { //carre-rond
						if (couleur==0) ff1=2; else ff1=4;
						if (couleur==0) ff2=1; else ff2=3;
					}

					System.out.println("ff1 : "+ff1+"\nff2 : "+ff2);

					System.out.println("choix : "+choix);

					if (choix==0) {
						j=0;
						for (i=3; i<9; i++) {
							if (t1[i]==1) j=1;
						}
						
						if (j==0) return false;

						ok=0;	
						cmp=0;
						while (a<1 || a>2 || ok==0) { // rond
							a=0; ok=0;
							
							System.out.print("sens : \n");
							
							if (t1[1]==1) System.out.print("1 : gauche devant\n");
							if (t1[2]==1) System.out.print("2 : droite devant\n");
							
							System.out.print("? = ");

							a = sc.nextInt();

							ok=1;

							if (t1[1]==1&&t1[2]!=1) if (a==2) ok=0;
							if (t1[1]!=1&&t1[2]==1) if (a==1) ok=0;
							
							cmp++;
							
							if (cmp>=lignes) {
								cmp=0;
								affiche (t,coordonnees,lignes);
								System.out.print("\n");
							}
						}

						sens1=a-1;

						ok=0;
						cmp=0;
						while (b<1 || b>3 || ok==0) { // carre
							b=0; ok=0;
							
							System.out.print("sens : \n");
							
							if (t1[sens1*3+3]==1) System.out.print("1 : gauche\n");
							if (t1[sens1*3+4]==1) System.out.print("2 : droite\n");
							if (t1[sens1*3+5]==1) System.out.print("3 : milieu\n");
							
							System.out.print("? = ");
							
							b = sc.nextInt();

							ok=1;


							if (t1[sens1*3+3]==1&&t1[sens1*3+4]!=1&&t1[sens1*3+5]!=1) if (b==2||b==3) ok=0;
							if (t1[sens1*3+3]!=1&&t1[sens1*3+4]==1&&t1[sens1*3+5]!=1) if (b==1||b==3) ok=0;
							if (t1[sens1*3+3]!=1&&t1[sens1*3+4]!=1&&t1[sens1*3+5]==1) if (b==1||b==2) ok=0;
							
							if (t1[sens1*3+3]==1&&t1[sens1*3+4]==1&&t1[sens1*3+5]!=1) if (b==3) ok=0;
							if (t1[sens1*3+4]==1&&t1[sens1*3+5]==1&&t1[sens1*3+3]!=1) if (b==1) ok=0;
							if (t1[sens1*3+3]==1&&t1[sens1*3+5]==1&&t1[sens1*3+4]!=1) if (b==2) ok=0;

							cmp++;
							
							if (cmp>=lignes) {
								cmp=0;
								affiche (t,coordonnees,lignes);
								System.out.print("\n");
							}
						}

						sens2=b-1;

						System.out.println("sens1 : "+sens1+"\nsens2 : "+sens2);

						if (sens1==0) {
							if (x-cr<0 || y-cr<0) return false;

							t[x][y] = 0;
							
							for (i=1; i<cr+1; i++) {
								t[x-i][y-i] = transformeUnPion2(t,ff1,x-i,y-i);
							}

							x1=x-(i-1);
							y1=y-(i-1);
						}
						
						if (sens1==1) {
							if (x-cr<0 || y+cr>7) return false;
							System.out.println("blabla1");

							t[x][y] = 0;
							
							for (i=1; i<cr+1; i++) {
								t[x-i][y+i] = transformeUnPion2(t,ff1,x-i,y+i);
							}

							x1=x-(i-1);
							y1=y+(i-1);
						}

						if (sens2==0) {
							if (y1-cc<0) return false;
							
							for (i=1; i<cc+1; i++) {
								t[x1][y1-i] = transformeUnPion2(t,ff2,x1,y1-i);
							}
						}
						
						if (sens2==1) {
							if (y1+cc>7) return false;

							for (i=1; i<cc+1; i++) {
								t[x1][y1+i] = transformeUnPion2(t,ff2,x1,y1+i);
							}
						}
						
						if (sens2==2) {
							if (x1-cc<0) return false;
							System.out.println("blabla2");
							
							for (i=1; i<cc+1; i++) {
								t[x1-i][y1] = transformeUnPion2(t,ff2,x1-i,y1);
								System.out.println("x1 = "+x1+"\ny1 = "+y1);
							}
						}
					}

					if (choix==1) {
						j=0;
						for (i=12; i<18; i++) {
							if (t1[i]==1) j=1;
						}
						
						if (j==0) return false;

						ok=0;
						cmp=0;	
						while (a<1 || a>3 ||ok==0) { // carre
							a=0; ok=0;
							
							System.out.print("sens : \n");
							
							if (t1[9]==1) System.out.print("1 : gauche\n");
							if (t1[10]==1) System.out.print("2 : droite\n");
							if (t1[10]==1) System.out.print("3 : milieu\n");
							
							System.out.print("? = ");
							
							a = sc.nextInt();

							ok=1;

							if (t1[9]==1&&t1[10]!=1&&t1[11]!=1) if (a==2 || a==3) ok=0;
							if (t1[9]!=1&&t1[10]==1&&t1[11]!=1) if (a==1 || a==3) ok=0;
							if (t1[9]!=1&&t1[10]!=1&&t1[11]==1) if (a==1 || a==2) ok=0;

							if (t1[9]==1&&t1[10]==1&&t1[11]!=1) if (a==3) ok=0;
							if (t1[10]==1&&t1[11]==1&&t1[9]!=1) if (a==1) ok=0;
							if (t1[9]==1&&t1[11]==1&&t1[10]!=1) if (a==2) ok=0;
							
							cmp++;
							
							if (cmp>=lignes) {
								cmp=0;
								affiche (t,coordonnees,lignes);
								System.out.print("\n");
							}
						}

						sens1=a-1;

						ok=0;
						cmp=0;	
						while (b<1 || b>2 || ok==0) { // rond
							b=0; ok=0;
							
							System.out.print("sens : \n");
							
							if (t1[sens1*2+12]==1) System.out.print("1 : gauche devant\n");
							if (t1[sens1*2+13]==1) System.out.print("2 : droite devant\n");
							
							System.out.print("? = ");
							
							b = sc.nextInt();

							ok=1;

							if (t1[sens1*2+12]==1&&t1[sens1*2+13]!=1) if (b==2) ok=0;
							if (t1[sens1*2+12]!=1&&t1[sens1*2+13]==1) if (b==1) ok=0;
							
							cmp++;
							
							if (cmp>=lignes) {
								cmp=0;
								affiche (t,coordonnees,lignes);
								System.out.print("\n");
							}
						}

						sens2=b-1;

						if (sens1==0) {
							if (y-cc<0) return false;

							t[x][y] = 0;
							
							for (i=1; i<cc+1; i++) {
								t[x][y-i] = transformeUnPion2(t,ff1,x,y-i);
							}

							x1=x;
							y1=y-(i-1);
						}
						
						if (sens1==1) {
							if (y+cc>7) return false;

							t[x][y] = 0;
							
							for (i=1; i<cc+1; i++) {
								t[x][y+i] = transformeUnPion2(t,ff1,x,y+i);
							}

							x1=x;
							y1=y+(i-1);
						}
						
						if (sens1==2) {
							if (x-cc<0) return false;

							t[x][y] = 0;
							
							for (i=1; i<cc+1; i++) {
								t[x-i][y] = transformeUnPion2(t,ff1,x-i,y);
							}

							x1=x-(i-1);
							y1=y;
						}
						
						if (sens2==0) {
							if (x1-cr<0 || y1-cr<0) return false;
							
							for (i=1; i<cr+1; i++) {
								t[x1-i][y1-i] = transformeUnPion2(t,ff2,x1-i,y1-i);
							}
						}
						
						if (sens2==1) {
							if (x1-cr<0 || y1+cr>7) return false;
							
							for (i=1; i<cr+1; i++) {
								t[x1-i][y1+i] = transformeUnPion2(t,ff2,x1-i,y1+i);
							}
						}
					}
				}
			}
		}

		if (base==1) { // en haut.
			if (forme==1) {//rond
				if (t1[0]!=5) return false;

				else {
					//System.out.println("Base1\nforme=1");

					j=0;
					for (i=3; i<5; i++) {
						if (t1[i]==1) j=1;
					}

					if (j==0) return false;

					ok=0;
					cmp=0;
					while (a<1 || a>2 || ok==0) {
						a=0; ok=0;

						System.out.print("sens : \n");

						if (t1[3]==1) System.out.print("1 : gauche devant\n");
						if (t1[4]==1) System.out.print("2 : droite devant\n");

						System.out.print("? = ");

						a = sc.nextInt();

						ok=1;

						if (t1[3]==1&&t1[4]!=1) if (a==2) ok=0;
						if (t1[3]!=1&&t1[4]==1) if (a==1) ok=0;
						
						cmp++;
						
						if (cmp>=lignes) {
							cmp=0;
							affiche (t,coordonnees,lignes);
							System.out.print("\n");
						}
					}

					sens1=a-1;

					if (sens1==0) {
						if (x+cr>7 || y-cr<0) return false;

						t[x][y] = 0;

						for (i=1; i<cr+1; i++) {
							t[x+i][y-i] = transformeUnPion2(t,ff1,x+i,y-i);
						}
					}

					if (sens1==1) {
						if (x+cr>7 || y+cr>7) return false;

						t[x][y] = 0;

						for (i=1; i<cr+1; i++) {
							t[x+i][y+i] = transformeUnPion2(t,ff1,x+i,y+i);
						}
					}
				}
			}

			if (forme==2) {//carre
				if (t1[0]!=7) return false;

				else {
					j=0;
					for (i=4; i<7; i++) {
						if (t1[i]==1) j=1;
					}

					if (j==0) return false;

					ok=0;
					cmp=0;
					while (a<1 || a>3 || ok==0) {
						a=0; ok=0;

						System.out.print("sens : \n");

						if (t1[4]==1) System.out.print("1 : gauche\n");
						if (t1[5]==1) System.out.print("2 : droite\n");
						if (t1[6]==1) System.out.print("3 : milieu\n");

						System.out.print("? = ");

						a = sc.nextInt();

						ok=1;

						if (t1[4]==1&&t1[5]==1&&t1[6]!=1) if (a==3) ok=0;
						if (t1[5]==1&&t1[6]==1&&t1[4]!=1) if (a==1) ok=0;
						if (t1[4]==1&&t1[6]==1&&t1[5]!=1) if (a==2) ok=0;

						cmp++;
						
						if (cmp>=lignes) {
							cmp=0;
							affiche (t,coordonnees,lignes);
							System.out.print("\n");
						}
					}

					sens1=a-1;


					if (sens1==0) {
						if (y-cc<0) return false;

						t[x][y] = 0;

						for (i=1; i<cc+1; i++) {
							t[x][y-i] = transformeUnPion2(t,ff1,x,y-i);
						}
					}

					if (sens1==1) {
						if (y+cc>7) return false;

						t[x][y] = 0;

						for (i=1; i<cc+1; i++) {
							t[x][y+i] = transformeUnPion2(t,ff1,x,y+i);
						}
					}

					if (sens1==2) {
						if (x+cc>7) return false;

						t[x][y] = 0;

						for (i=1; i<cc+1; i++) {
							t[x+i][y] = transformeUnPion2(t,ff1,x+i,y);
						}
					}
				}
			}

			if (forme==3) {//rond-carre
				if (t1[0]!=35) return false;

				else {
					for (i=0; i<t1.length; i++) System.out.println("t1["+i+"] = "+t1[i]);

					j=2;
					k=0;
					l=3;

					/*
						-l=3 : les deux sont correctes.
						-l=1 ou l=2 : 1 ou 2 seulement est correcte.
					*/

					for (i=18; i<20; i++) {
						if (t1[i]==1) k++;
					}
					if (k==0) j--; else l=1;

					k=0;
					for (i=26; i<29; i++) {
						if (t1[i]==1) k++;
					}
					if (k==0) j--; else l=2;
					if (j==2) l=3;
					if (j==0) return false;

					cmp=0;
					while (choix<1 || choix>2) {
						choix=0;
						System.out.print("Vous souhaitez commencer par deployer : ");
						if (l==1 || l==3) System.out.print("\n1 : Les ronds");
						if (l==2 || l==3) System.out.print("\n2 : Les carres");
						System.out.print("\n? = ");

						choix = sc.nextInt();

						if (l==1) if (choix==2) choix=0;
						if (l==2) if (choix==1) choix=0;

						cmp++;
						
						if (cmp>=lignes) {
							cmp=0;
							affiche (t,coordonnees,lignes);
							System.out.print("\n");
						}
					}

					choix--;

					if (choix==0) { //rond-carre
						if (couleur==0) ff1=1; else ff1=3;
						if (couleur==0) ff2=2; else ff2=4;
					}
					
					if (choix==1) { //carre-rond
						if (couleur==0) ff1=2; else ff1=4;
						if (couleur==0) ff2=1; else ff2=3;
					}

					if (choix==0) {
						j=0;
						for (i=20; i<26; i++) {
							if (t1[i]==1) j=1;
						}
						
						if (j==0) return false;

						ok=0;
						cmp=0;	
						while (a<1 || a>2 || ok==0) { // rond
							a=0; ok=0;
							
							System.out.print("sens : \n");
							
							if (t1[18]==1) System.out.print("1 : gauche devant\n");
							if (t1[19]==1) System.out.print("2 : droite devant\n");
							
							System.out.print("? = ");
							
							a = sc.nextInt();

							ok=1;

							if (t1[18]==1&&t1[19]!=1) if (a==2) ok=0;
							if (t1[18]!=1&&t1[19]==1) if (a==1) ok=0;

							cmp++;
							
							if (cmp>=lignes) {
								cmp=0;
								affiche (t,coordonnees,lignes);
								System.out.print("\n");
							}
						}

						sens1=a-1;

						ok=0;
						cmp=0;
						while (b<1 || b>3 || ok==0) { // carre
							b=0; ok=0;
							
							System.out.print("sens : \n");
							
							if (t1[sens1*3+20]==1) System.out.print("1 : gauche\n");
							if (t1[sens1*3+21]==1) System.out.print("2 : droite\n");
							if (t1[sens1*3+22]==1) System.out.print("3 : milieu\n");
							
							System.out.print("? = ");
							
							b = sc.nextInt();

							ok=1;

							if (t1[sens1*3+20]==1&&t1[sens1*3+21]!=1&&t1[sens1*3+22]!=1) if (b==2 || b==3) ok=0;
							if (t1[sens1*3+20]!=1&&t1[sens1*3+21]==1&&t1[sens1*3+22]!=1) if (b==1 || b==3) ok=0;
							if (t1[sens1*3+20]!=1&&t1[sens1*3+21]!=1&&t1[sens1*3+22]==1) if (b==1 || b==2) ok=0;
							
							if (t1[sens1*3+20]==1&&t1[sens1*3+21]==1&&t1[sens1*3+22]!=1) if (b==3) ok=0;
							if (t1[sens1*3+21]==1&&t1[sens1*3+22]==1&&t1[sens1*3+20]!=1) if (b==1) ok=0;
							if (t1[sens1*3+20]==1&&t1[sens1*3+22]==1&&t1[sens1*3+21]!=1) if (b==2) ok=0;

							cmp++;
							
							if (cmp>=lignes) {
								cmp=0;
								affiche (t,coordonnees,lignes);
								System.out.print("\n");
							}
						}

						sens2=b-1;

						if (sens1==0) {
							if (x+cr>7 || y-cr<0) return false;

							t[x][y] = 0;

							for (i=1; i<cr+1; i++) {
								t[x+i][y-i] = transformeUnPion2(t,ff1,x+i,y-i);
							}

							x1=x+(i-1);
							y1=y-(i-1);
						}
						
						if (sens1==1) {
							if (x+cr>7 || y+cr>7) return false;

							t[x][y] = 0;

							for (i=1; i<cr+1; i++) {
								t[x+i][y+i] = transformeUnPion2(t,ff1,x+i,y+i);
							}

							x1=x+(i-1);
							y1=y+(i-1);
						}

						if (sens2==0) {
							if (y1-cc<0) return false;

							for (i=1; i<cc+1; i++) {
								t[x1][y1-i] = transformeUnPion2(t,ff2,x1,y1-i);
							}
						}
						
						if (sens2==1) {
							if (y1+cc>7) return false;

							for (i=1; i<cc+1; i++) {
								t[x1][y1+i] = transformeUnPion2(t,ff2,x1,y1+i);
							}
						}
						
						if (sens2==2) {
							if (x1+cc>7) return false;
							
							for (i=1; i<cc+1; i++) {
								t[x1+i][y1] = transformeUnPion2(t,ff2,x1+i,y1);
							}
						}
					}

					if (choix==1) {
						j=0;
						for (i=29; i<35; i++) {
							if (t1[i]==1) j=1;
						}
						
						if (j==0) return false;

						ok=0;	
						cmp=0;
						while (a<1 || a>3 || ok==0) { // carre
							a=0; ok=0;
							
							System.out.print("sens : \n");
							
							if (t1[26]==1) System.out.print("1 : gauche\n");
							if (t1[27]==1) System.out.print("2 : droite\n");
							if (t1[28]==1) System.out.print("3 : milieu\n");
							
							System.out.print("? = ");
							
							a = sc.nextInt();

							ok=1;

							if (t1[26]==1&&t1[27]!=1&&t1[28]!=1) if (a==2 || a==3) ok=0;
							if (t1[26]!=1&&t1[27]==1&&t1[28]!=1) if (a==1 || a==3) ok=0;
							if (t1[26]!=1&&t1[27]!=1&&t1[28]==1) if (a==1 || a==2) ok=0;

							if (t1[26]==1&&t1[27]==1&&t1[28]!=1) if (a==3) ok=0;
							if (t1[27]==1&&t1[28]==1&&t1[26]!=1) if (a==1) ok=0;
							if (t1[26]==1&&t1[28]==1&&t1[27]!=1) if (a==2) ok=0;

							cmp++;
							
							if (cmp>=lignes) {
								cmp=0;
								affiche (t,coordonnees,lignes);
								System.out.print("\n");
							}
						}

						sens1=a-1;

						ok=0;
						cmp=0;
						while (b<1 || b>2 || ok==0) { // rond
							b=0; ok=0;
							
							System.out.print("sens : \n");
							
							if (t1[sens1*2+29]==1) System.out.print("1 : gauche devant\n");
							if (t1[sens1*2+30]==1) System.out.print("2 : droite devant\n");
							
							System.out.print("? = ");

							b = sc.nextInt();

							ok=1;

							if (t1[sens1*2+29]==1&&t1[sens1*2+30]!=1) if (b==2) ok=0;
							if (t1[sens1*2+29]!=1&&t1[sens1*2+30]==1) if (b==1) ok=0;

							cmp++;
							
							if (cmp>=lignes) {
								cmp=0;
								affiche (t,coordonnees,lignes);
								System.out.print("\n");
							}
						}

						sens2=b-1;

						if (sens1==0) {
							if (y-cc<0) return false;

							t[x][y] = 0;
							
							for (i=1; i<cc+1; i++) {
								t[x][y-i] = transformeUnPion2(t,ff1,x,y-i);
							}

							x1=x;
							y1=y-(i-1);
						}
						
						if (sens1==1) {
							if (y+cc>7) return false;

							t[x][y] = 0;
							
							for (i=1; i<cc+1; i++) {
								t[x][y+i] = transformeUnPion2(t,ff1,x,y+i);
							}

							x1=x;
							y1=y+(i-1);
						}
						
						if (sens1==2) {
							if (x+cc>7) return false;

							t[x][y] = 0;
							
							for (i=1; i<cc+1; i++) {
								t[x+i][y] = transformeUnPion2(t,ff1,x+i,y);
							}

							x1=x+(i-1);
							y1=y;
						}
						
						if (sens2==0) {
							if (x1+cr>7 || y1-cr<0) return false;

							for (i=1; i<cr+1; i++) {
								t[x1+i][y1-i] = transformeUnPion2(t,ff2,x1+i,y1-i);
							}
						}
						
						if (sens2==1) {
							if (x1+cr>7 || y1+cr>7) return false;

							for (i=1; i<cr+1; i++) {
								t[x1+i][y1+i] = transformeUnPion2(t,ff2,x1+i,y1+i);
							}
						}
					}
				}
			}
		}

		cChoix[0] = sens1;
		cChoix[1] = sens2;
		cChoix[2] = choix;
		cChoix[3] = p1;

		pions[p1-1]=pions[p1-1]-1; //Mise à
		if (couleur==0) {pions[1-1]=pions[1-1]+cr; pions[2-1]=pions[2-1]+cc;} // jour
		if (couleur==1) {pions[3-1]=pions[3-1]+cr; pions[4-1]=pions[4-1]+cc;} // de pions.
		
		return true;
	}

	/*public static int [] AutoriseDeploiement1 (int [][] t, int x, int y) {
		int [] t2=new int [1];
		t[6][0]=18;

		System.out.println(detecteDeploiement(t,0,1,2,1,6,0)); //base 0, choix : carre-rond, sens1 milieu, sens2 droite devant.

		return t2;
	}*/

	public static int [] AutoriseDeploiement (int [][] t, int x, int y) {//0 : rond-carre, 1 : carre-rond.
		int i,j,k,m,p1=0, n=0, l=0;

		int [] t1 = new int [1]; t1[0]=0; // faire un free(t1).

		if (x>7||y>7||x<0||y<0) {System.out.print("x>7||y>7||x<0||y<0\n"); return t1;} //Vérifiaction des coordonnées.

		p1 = t[x][y];

		/* 

			t1[0] = taille de t1-1. Si la taille est de 1 : pas de déploiement possible.

			Il faut compter 2 fois le nombre de cases, à cause des deux bases.

			-base : 0 : bas, 1 : haut.

			si rond : 0,1;
			si carre  : 0,1,2;
			si rond-carre : 0,1,2,3,4.

		*/

		if (p1==5 || p1==8 || p1==12 || p1==15) { // rond
			for (i=0; i<2; i++) for (j=0; j<2; j++) if (detecteDeploiement(t,i,0,j,0,x,y)) n++;

			//System.out.println("Autorise deploiement : n = "+n);

			if (n==0) { // pas de déploiement possible.
				n=1;
				t1 = new int [n];
				t1[0]=1;
				return t1;
			}

			else {
				t1 = new int [5];
				t1[0]=5;
				for (i=1; i<5; i++) t1[i]=0; // initialisation de t1.

				k=1;
				
				for (i=0; i<2; i++) {for (j=0; j<2; j++) {
						System.out.println("i = "+i+"\nj = "+j+"\nk = "+k);
						if (detecteDeploiement(t,i,0,j,0,x,y)) {System.out.println("\ntrue"); t1[k]=1;}
						k++;
					}}
			}
		}

		else if (p1==6 || p1==9 || p1==13 || p1==16) { // carre
			for (i=0; i<2; i++) for (j=0; j<3; j++) if (detecteDeploiement(t,i,0,j,0,x,y)) n++;

			if (n==0) { // pas de déploiement possible.
				n=1;
				t1 = new int [n];
				t1[0]=1;
				return t1;
			}

			else {
				t1 = new int [7];
				t1[0]=7;
				for (i=1; i<7; i++) t1[i]=0; // initialisation de t1.

				k=1;
				
				for (i=0; i<2; i++) {for (j=0; j<3; j++) {
						//System.out.println("i = "+i+"\nj = "+j+"\nk = "+k);
						System.out.println("Avant l'appel.");
						System.out.println("detecteDeploiement(t,base="+i+",choix="+0+",sens1="+j+",sens2="+0+",x="+x+",y="+y+") : "+detecteDeploiement(t,i,0,j,0,x,y));
						if (detecteDeploiement(t,i,0,j,0,x,y)) t1[k]=1;
						k++;
					}}
			}
		}

		else { // rond-carre
			for (i=0; i<2; i++) {
				j=0;
				for (k=0; k<2; k++) {
					if (detecteDeploiement(t,i,j,k,0,x,y) || detecteDeploiement(t,i,j,k,1,x,y) || detecteDeploiement(t,i,j,k,1,x,y)) {
						//System.out.println("i = "+i+"\nj = "+j+"\nk = "+k+"\nOK10");
						n++;

						for (l=0; l<3; l++) if (detecteDeploiement(t,i,j,k,l,x,y)) n++;
					}
				}

				j=1;
				for (k=0; k<3; k++) {
					if (detecteDeploiement(t,i,j,k,0,x,y) || detecteDeploiement(t,i,j,k,1,x,y)) {
						n++;

						for (l=0; l<2; l++) if (detecteDeploiement(t,i,j,k,l,x,y)) n++;
					}
				}

				//System.out.println("n = "+n);
			}

			if (n==0) { // pas de déploiement possible.
				n=1;
				t1 = new int [n];
				t1[0]=1;
				return t1;
			}

			else {
				//System.out.println("OK15.");
				t1 = new int [35];
				t1[0]=35;

				for (i=1; i<35; i++) t1[i]=0; // initialisation de t1.

				k=0;

				for (i=0; i<2; i++) {
					j=0;
					for (k=0; k<2; k++) {
						//System.out.println("Avant l'appel.");
						//System.out.println("detecteDeploiement(t,base="+i+",choix="+j+",sens1="+k+",sens2="+0+",x="+x+",y="+y+") : "+detecteDeploiement(t,i,j,k,0,x,y));
						if (detecteDeploiement(t,i,j,k,0,x,y) || detecteDeploiement(t,i,j,k,1,x,y) || detecteDeploiement(t,i,j,k,2,x,y)) {
							t1[i*17+1+k]=1;
							/*System.out.println("detecteDeploiement(t,"+i+","+j+","+k+","+0+","+x+","+y+") : "+detecteDeploiement(t,i,j,0,l,x,y));*/
							//System.out.println("i*17+1+k : "+(i*17+1+k));
							
							for (l=0; l<3; l++) if (detecteDeploiement(t,i,j,k,l,x,y)) {/*System.out.println("detecteDeploiement(t,"+i+","+j+","+k+","+l+","+x+","+y+") : "+detecteDeploiement(t,i,j,k,l,x,y));*/ t1[i*17+1+2+k*3+l]=1;}
						}
					}

					j=1;
					for (k=0; k<3; k++) {
						//System.out.println("Avant l'appel.");
						System.out.println("detecteDeploiement(t,base="+i+",choix="+j+",sens1="+k+",sens2="+0+",x="+x+",y="+y+") : "+detecteDeploiement(t,i,j,k,0,x,y));
						if (detecteDeploiement(t,i,j,k,0,x,y) || detecteDeploiement(t,i,j,k,1,x,y)) {
							//System.out.println("ok20");
							t1[i*17+9+k]=1;
							/*System.out.println("detecteDeploiement(t,"+i+","+j+","+k+","+0+","+x+","+y+") : "+detecteDeploiement(t,i,j,0,l,x,y));*/
							
							for (l=0; l<2; l++) if (detecteDeploiement(t,i,j,k,l,x,y)) {System.out.println("detecteDeploiement(t,"+i+","+j+","+k+","+l+","+x+","+y+") : "+detecteDeploiement(t,i,j,k,l,x,y)+"t1[i*17+6+k*2+3+l] = "+t1[i*10+6+3+l]); t1[i*17+9+k*2+3+l]=1;}
						}
					}
				}
			}
		}

		return t1;
	}

	public static boolean detecteDeploiement (int [][] t, int base, int choix, int sens1, int sens2, int x,  int y) {
		int i,j, cr=0, cc=0, erreurCouleur=0, x1=0, y1=0;
		int p1 = t[x][y], px=0;


		if (x>7||y>7||x<0||y<0) {System.out.print("x>7||y>7||x<0||y<0\n"); return false;} //Vérifiaction des coordonnées.

		/*

			-base : haut ou bas de l'échiquier. 0 : bas, 1 : haut
			-sens : carre : 0 : gauche, 1 : droite, 2 : milieu ; rond : 0 : gauche devant, 1 : droite devant.
	
			cr = coup rond.
			cc = coup carré.
	
			-choix : 0 : rond-carre, 1 : carre-rond.

		*/

		if (p1==5||p1==12) {cr=2; cc=0;}
		if (p1==6||p1==13) {cr=0; cc=2;}
		if (p1==7||p1==14) {cr=1; cc=1;}
		if (p1==8||p1==15) {cr=3; cc=0;}
		if (p1==9||p1==16) {cr=0; cc=3;}
		if (p1==10||p1==17) {cr=2; cc=1;}
		if (p1==11||p1==18) {cr=1; cc=2;}


		if (p1==5 || p1==8 || p1==12 || p1==15) { // rond
			if (base==0) {
				if (sens1==0) {
					//System.out.println("Detecte deploiement : rond, gauche devant.");
					if (x-cr<0 || y-cr<0) {System.out.println("x-cr<0 || y-cr<0"); return false;}
					else {
						for (i=1; i<cr+1; i++)  if (detectePionSature (t,x,y,x-i,y-i)) return false;
						for (i=1; i<cr+1; i++) {
							px=t[x-i][y-i];
							if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
							if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
						}
					}
				}

				if (sens1==1) {
					//System.out.println("Detecte deploiement : rond, droite devant.");
					//System.out.println("cr = "+cr+"\nx = "+x+"\ny = "+y);

					if (x-cr<0 || y+cr>7) {System.out.println("x-cr<0 || y+cr>7"); return false;}
					else {
						for (i=1; i<cr+1; i++)  if (detectePionSature (t,x,y,x-i,y+i)) return false;
						for (i=1; i<cr+1; i++) {
							px=t[x-i][y+i];
							if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
							if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
						}
					}
				}
			}

			if (base==1) {
				if (sens1==0) {
					System.out.println("Detecte deploiement : rond, base1, gauche devant.");
					System.out.println("cr = "+cr+"\nx = "+x+"\ny = "+y);

					if (x+cr>7 || y-cr<0) {System.out.println("x+cr>7 || y-cr<0"); return false;}
					else {
						for (i=1; i<cr+1; i++)  if (detectePionSature (t,x,y,x+i,y-i)) return false;
						for (i=1; i<cr+1; i++) {
							px=t[x+i][y-i];
							if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
							if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
						}
					}
				}

				if (sens1==1) {
					System.out.println("Detecte deploiement : rond, base1, droite devant.");
					System.out.println("cr = "+cr+"\nx = "+x+"\ny = "+y);

					if (x+cr>7 || y+cr>7) {System.out.println("x+cr>7 || y+cr>7"); return false;}
					else {
						for (i=1; i<cr+1; i++)  if (detectePionSature (t,x,y,x+i,y+i)) return false;
						for (i=1; i<cr+1; i++) {
							px=t[x+i][y+i];
							if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
							if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
						}
					}
				}
			}
		}

		if (p1==6 || p1==9 || p1==13 || p1==16) { //carre
			if (base==0) {
				if (sens1==0) {
					if (y-cc<0) {System.out.println("y-cc<0"); return false;}
					else {
						for (i=1; i<cc+1; i++)  if (detectePionSature (t,x,y,x,y-i)) return false;
						for (i=1; i<cc+1; i++) {
							px=t[x][y-i];
							if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
							if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
						}
					}
				}

				if (sens1==1) {
					if (y+cc>7) {System.out.println("y+cc>7"); return false;}
					else {
						for (i=1; i<cc+1; i++)  if (detectePionSature (t,x,y,x,y+i)) return false;
						for (i=1; i<cc+1; i++) {
							px=t[x][y+i];
							if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
							if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
						}
					}
				}

				if (sens1==2) {
					if (x-cc<0) {System.out.println("x-cc<0"); return false;}
					else {
						for (i=1; i<cc+1; i++)  if (detectePionSature (t,x,y,x-i,y)) return false;
						for (i=1; i<cc+1; i++) {
							px=t[x-i][y];
							if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
							if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
						}
					}
				}
			}

			if (base==1) {
				if (sens1==0) {
					if (y-cc<0) {System.out.println("y-cc<0"); return false;}
					else {
						for (i=1; i<cc+1; i++)  if (detectePionSature (t,x,y,x,y-i)) return false;
						for (i=1; i<cc+1; i++) {
							px=t[x][y-i];
							if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
							if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
						}
					}
				}

				if (sens1==1) {
					if (y+cc>7) {System.out.println("y+cc>7"); return false;}
					else {
						for (i=1; i<cc+1; i++)  if (detectePionSature (t,x,y,x,y+i)) return false;
						for (i=1; i<cc+1; i++) {
							px=t[x][y+i];
							if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
							if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
						}
					}
				}

				if (sens1==2) {
					if (x+cc>7) {System.out.println("x+cc>7"); return false;}
					else {
						for (i=1; i<cc+1; i++)  if (detectePionSature (t,x,y,x+i,y)) return false;
						for (i=1; i<cc+1; i++) {
							px=t[x+i][y];
							if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
							if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
						}
					}
				}
			}			
		}

		if (p1==7 || p1==10 || p1==11 || p1==14 || p1==17 || p1==18) { //rond-carre
			if (choix==0) { // rond d'abord
				if (base==0) {
					if (sens1==0) {
						if (x-cr<0 || y-cr<0) {System.out.println("x-cr<0 || y-cr<0"); return false;}
						else {
							for (i=1; i<cr+1; i++)  if (detectePionSature (t,x,y,x-i,y-i)) return false;
							for (i=1; i<cr+1; i++) {
								px=t[x-i][y-i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}

							x1=x-(i-1);
							y1=y-(i-1);
						}
					}

					if (sens1==1) {
						if (x-cr<0 || y+cr>7) {System.out.println("x-cr<0 || y+cr>7"); return false;}
						else {
							for (i=1; i<cr+1; i++)  if (detectePionSature (t,x,y,x-i,y+i)) return false;
							for (i=1; i<cr+1; i++) {
								px=t[x-i][y+i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}

							x1=x-(i-1);
							y1=y+(i-1);
						}
					}
				}

				if (base==1) {
					if (sens1==0) {
						if (x+cr>7 || y-cr<0) {System.out.println("x+cr>7 || y-cr<0"); return false;}
						else {
							for (i=1; i<cr+1; i++)  if (detectePionSature (t,x,y,x+i,y-i)) return false;
							for (i=1; i<cr+1; i++) {
								px=t[x+i][y-i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}

							x1=x+(i-1);
							y1=y-(i-1);
						}
					}

					if (sens1==1) {
						if (x+cr>7 || y+cr>7) {System.out.println("x+cr>7 || y+cr>7"); return false;}
						else {
							for (i=1; i<cr+1; i++)  if (detectePionSature (t,x,y,x+i,y+i)) return false;
							for (i=1; i<cr+1; i++) {
								px=t[x+i][y+i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}

							x1=x+(i-1);
							y1=y+(i-1);
						}
					}
				}//rond
				
				if (base==0) {
					if (sens2==0) {
						if (y1-cc<0) {System.out.println("y-cc<0"); return false;}
						else {
							for (i=1; i<cc+1; i++)  if (detectePionSature (t,x1,y1,x1,y1-i)) return false;
							for (i=1; i<cc+1; i++) {
								px=t[x1][y1-i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}
						}
					}

					if (sens2==1) {
						if (y1+cc>7) {System.out.println("y+cc>7"); return false;}
						else {
							for (i=1; i<cc+1; i++)  if (detectePionSature (t,x1,y1,x1,y1+i)) return false;
							for (i=1; i<cc+1; i++) {
								px=t[x1][y1+i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}
						}
					}

					if (sens2==2) {
						if (x1-cc<0) {System.out.println("x-cc<0"); return false;}
						else {
							for (i=1; i<cc+1; i++)  if (detectePionSature (t,x1,y1,x1-i,y1)) return false;
							for (i=1; i<cc+1; i++) {
								px=t[x1-i][y1];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}
						}
					}
				}

				if (base==1) {
					if (sens2==0) {
						if (y1-cc<0) {System.out.println("y-cc<0"); return false;}
						else {
							for (i=1; i<cc+1; i++)  if (detectePionSature (t,x1,y1,x1,y1-i)) return false;
							for (i=1; i<cc+1; i++) {
								px=t[x1][y1-i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}
						}
					}

					if (sens2==1) {
						if (y1+cc>7) {System.out.println("y+cc>7"); return false;}
						else {
							for (i=1; i<cc+1; i++)  if (detectePionSature (t,x1,y1,x1,y1+i)) return false;
							for (i=1; i<cc+1; i++) {
								px=t[x1][y1+i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}
						}
					}

					if (sens2==2) {
						if (x1+cc>7) {System.out.println("x+cc>7"); return false;}
						else {
							for (i=1; i<cc+1; i++)  if (detectePionSature (t,x1,y1,x1+i,y1)) return false;
							for (i=1; i<cc+1; i++) {
								px=t[x1+i][y1];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}
						}
					}
				}//carre
			}

			if (choix==1) { // carre d'abord
				if (base==0) {
					if (sens1==0) {
						if (y-cc<0) {System.out.println("y-cc<0"); {System.out.println("y-cc<0"); return false;}}
						else {
							for (i=1; i<cc+1; i++)  if (detectePionSature (t,x,y,x,y-i)) return false;
							for (i=1; i<cc+1; i++) {
								px=t[x][y-i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}

							x1=x;
							y1=y-(i-1);
						}
					}

					if (sens1==1) {
						if (y+cc>7) {System.out.println("y+cc>7"); return false;}
						else {
							for (i=1; i<cc+1; i++)  if (detectePionSature (t,x,y,x,y+i)) return false;
							for (i=1; i<cc+1; i++) {
								px=t[x][y+i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}

							x1=x;
							y1=y+(i-1);
						}
					}

					if (sens1==2) {
						if (x-cc<0) {System.out.println("x-cc<0"); return false;}
						else {
							for (i=1; i<cc+1; i++)  if (detectePionSature (t,x,y,x-i,y)) return false;
							for (i=1; i<cc+1; i++) {
								px=t[x-i][y];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}

							x1=x-(i-1);
							y1=y;
						}
					}
				}

				if (base==1) {
					if (sens1==0) {
						if (y-cc<0) {System.out.println("y-cc<0"); return false;}
						else {
							for (i=1; i<cc+1; i++)  if (detectePionSature (t,x,y,x,y-i)) return false;
							for (i=1; i<cc+1; i++) {
								px=t[x][y-i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}

							x1=x;
							y1=y-(i-1);
						}
					}

					if (sens1==1) {
						if (y+cc>7) {System.out.println("y+cc>7"); return false;}
						else {
							for (i=1; i<cc+1; i++)  if (detectePionSature (t,x,y,x,y+i)) return false;
							for (i=1; i<cc+1; i++) {
								px=t[x][y+i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}

							x1=x;
							y1=y+(i-1);
						}
					}

					if (sens1==2) {
						if (x+cc>7) {System.out.println("x+cc>7"); return false;}
						else {
							for (i=1; i<cc+1; i++)  if (detectePionSature (t,x,y,x+i,y)) return false;
							for (i=1; i<cc+1; i++) {
								px=t[x+i][y];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}

							x1=x+(i-1);
							y1=y;
						}
					}
				}//carre

				if (base==0) {
					if (sens2==0) {
						if (x1-cr<0 || y1-cr<0) {System.out.println("x-cr<0 || y-cr<0"); return false;}
						else {
							for (i=1; i<cr+1; i++)  if (detectePionSature (t,x1,y1,x1-i,y1-i)) return false;
							for (i=1; i<cr+1; i++) {
								px=t[x1-i][y1-i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}
						}
					}

					if (sens2==1) {
						if (x1-cr<0 || y1+cr>7) {System.out.println("x-cr<0 || y+cr>7"); return false;}
						else {
							for (i=1; i<cr+1; i++)  if (detectePionSature (t,x1,y1,x1-i,y1+i)) return false;
							for (i=1; i<cr+1; i++) {
								px=t[x1-i][y1+i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}
						}
					}
				}

				if (base==1) {
					if (sens2==0) {
						if (x1+cr>7 || y1-cr<0) {System.out.println("x+cr>7 || y-cr<0"); return false;}
						else {
							for (i=1; i<cr+1; i++)  if (detectePionSature (t,x1,y1,x1+i,y1-i)) return false;
							for (i=1; i<cr+1; i++) {
								px=t[x1+i][y1-i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}
						}
					}

					if (sens2==1) {
						if (x1+cr>7 || y1+cr>7) {System.out.println("x+cr>7 || y+cr>7"); return false;}
						else {
							for (i=1; i<cr+1; i++)  if (detectePionSature (t,x1,y1,x1+i,y1+i)) return false;
							for (i=1; i<cr+1; i++) {
								px=t[x1+i][y1+i];
								if (p1>4 && p1<12) /*blanc*/ if ((px>2 && px<5) || (px>11 && px<19)) erreurCouleur=1;
								if (p1>11 && p1<19) /*noir*/ if ((px>0 && px<3) || (px>4 && px<12)) erreurCouleur=1;
							}
						}
					}
				}//rond
			}
		}

		if (erreurCouleur==1) {System.out.println("Piece de couleur adverse rencontree."); return false;}

		System.out.println("OK5");

		return true;
	}

	public static int transformeUnPion2 (int [][] t, int p1, int x1, int y1) { // utilisé uniquement pour les déploiements.
		int p2 = t[x1][y1];

		//if (p2==0) return p1;

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

		if (p1==0) System.out.println("p1=0");

		return p1;
	}

	public static int [] convertCoordonnees (char c, int n) {
		int x=0, y=0;

		int [] t = new int [2];

		if (c=='A'||c=='a') y=0;
		else if (c=='B'||c=='b') y=1;
		else if (c=='C'||c=='c') y=2;
		else if (c=='D'||c=='d') y=3;
		else if (c=='E'||c=='e') y=4;
		else if (c=='F'||c=='f') y=5;
		else if (c=='G'||c=='g') y=6;
		else if (c=='H'||c=='h') y=7;
		else System.out.println("Erreur sur le charactere entre.");

		if (n==8) x=0;
		else if (n==7) x=1;
		else if (n==6) x=2;
		else if (n==5) x=3;
		else if (n==4) x=4;
		else if (n==3) x=5;
		else if (n==2) x=6;
		else if (n==1) x=7;
		else System.out.println("Erreur sur le chiffre entre.");

		t[0]=x;
		t[1]=y;

		return t;
	}
}