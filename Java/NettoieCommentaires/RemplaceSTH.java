import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.FileReader;
import java.io.BufferedReader;
import java.util.Scanner;

class RemplaceSTH {
	public static void main (String [] args) {
		int i,j,s1length=0;

		if (args==null) return;

		String s0 = args[0];

		String s1="";

		try{
			File f1 = new File (s0);

			BufferedReader br=new BufferedReader(new FileReader(f1));

			String chainelue;

			chainelue=br.readLine();

			while(chainelue!=null){
				s1=s1+chainelue+"\n";
				chainelue=br.readLine();
			}

			//System.out.println("Fin de lecture");

			br.close();
		}

		catch(Exception e){
			System.out.println("Fichier introuvable.");
		} // lecture


		String ext=detecteExtenion(s0);
		String nom2 = str(s0,0,s0.length()-ext.length()-1);

		//System.out.println(nom2+"modifié.c");

		File f2 = new File(nom2+"modifié.c");

		try{
			f2.createNewFile();
		}

		catch(Exception e){
			e.printStackTrace();
			System.out.println("Echec de la sauvegarde : enregistrement du fichier.");
		}

		try {
			PrintWriter pw = new PrintWriter(new FileWriter(f2));
		   	pw.println(modifie(s1));
			pw.flush();
			pw.close();
	
		}

		catch(Exception e){
			e.printStackTrace();
			System.out.println("Echec de la sauvegarde : écriture dans le fichier.");
		}
	}

	public static String modifie (String s) {
		int i,j, slength=s.length(), h=0;
		String s1="";

		j=0;

		for (i=0; i<slength-2; i++) {
			if ((""+s.charAt(i)+s.charAt(i+1)+s.charAt(i+2)).equals("t3[") || (""+s.charAt(i)+s.charAt(i+1)+s.charAt(i+2)).equals("t2[")) {
				System.out.print(""+s.charAt(i)+s.charAt(i+1)+s.charAt(i+2));
				h=0;

				while (h!=2) {
					h = demandeRemplace ();
					if (h==0) j++;
					if (h==1) j--;
				}

				if (h==2) {
					if (s.charAt(i+1)=='3') {s1+="t3["+j; i+=2;}
					if (s.charAt(i+1)=='2') {s1+="t2["+j; i+=2;}
					System.out.print(""+s.charAt(i-2)+s.charAt(i-1)+s.charAt(i)+j);
				}
			}

			else {
				s1+=s.charAt(i)+"";
				System.out.print(s.charAt(i)+"");
			}
		}

		return s1;
	}

	public static String modifie2 (String s) {
		int i,j, slength=s.length(), h=0;
		String s1="";

		j=0;

		for (i=0; i<slength-3; i++) {
			if ((""+s.charAt(i)+s.charAt(i+1)+s.charAt(i+2)+s.charAt(i+3)).equals("t2[]")) {
				if (s.charAt(i+1)=='2') {s1+="t2["+j+"]"; j++; i+=3;}
			}

			else {
				s1+=s.charAt(i)+"";
			}
		}

		return s1;
	}

	public static String modifie3 (String s) {
		int i,j, slength=s.length(), h=0;
		String s1="";

		j=0;

		for (i=0; i<slength-3; i++) {
			if ((""+s.charAt(i)+s.charAt(i+1)+s.charAt(i+2)+s.charAt(i+3)).equals("{ t2")) {
				s1+="{\n\t\t\t\t\t\t\t\tt2"; j++; i+=3;
			}

			else {
				s1+=s.charAt(i)+"";
			}
		}

		return s1;
	}
	public static String str (String s0, int d, int f) {
		int i, length=s0.length();

		String s1 = "";

		for (i=d; i<length&&i<f; i++) s1+=s0.charAt(i);

		return s1;
	}

	public static String detecteExtenion (String s0) {
		int i, length=s0.length();
		boolean a=false;

		String s1 = "";

		for (i=0; i<length; i++) {
			if (a) s1+=s0.charAt(i);

			if (s0.charAt(i)=='.') a=true;
		}

		return s1;
	}

	public static int demandeRemplace () {
		Scanner sc = new Scanner(System.in);

		int a=0;

		while (a<1 || a>3) {
			a=0;

			System.out.print("\n1 : Incrementer j\n2 : decrementer j\n3 : remplacer\n? = ");

			a = sc.nextInt();
		}

		return a-1;
	}
}