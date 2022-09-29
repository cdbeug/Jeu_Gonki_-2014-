import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.FileReader;
import java.io.BufferedReader;

class NettoieCommentairesCpp {
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
				if (detecteComment(chainelue)) s1=s1+supprimeCppcomment(chainelue)+"\n";
				else s1=s1+chainelue+"\n";
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
		   	pw.println(s1);
			pw.flush();
			pw.close();
	
		}

		catch(Exception e){
			e.printStackTrace();
			System.out.println("Echec de la sauvegarde : écriture dans le fichier.");
		}
	}

	public static boolean detecteComment (String s0) {
		int i, length=s0.length();

		for (i=0; i<length-1; i++) if (s0.charAt(i)=='/' && s0.charAt(i+1)=='/') return true;

		return false;
	}

	public static String supprimeCppcomment (String s0) {
		int i,j, length=s0.length();

		String s1="";

		for (i=0; i<length-3; i++) {
			j=0;

			if (s0.charAt(i)=='/' && s0.charAt(i+1)=='/') {
				s1+="/*";
				for (j=i+2; j<length; j++) s1+=s0.charAt(j);
				s1+="  */";
			}

			else if (j<length) s1+=s0.charAt(i);

			if (j>length-2) i=j;
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
}