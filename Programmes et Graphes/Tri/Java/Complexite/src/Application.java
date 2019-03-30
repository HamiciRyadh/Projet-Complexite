import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.Duration;
import java.time.Instant;

import javax.swing.JOptionPane;

public class Application {

	public static void main(String[] args) throws IOException {
		String[] tabs = new String[15];
		for (int i = 1; i <= 15; i++) {
			tabs[i - 1] = new String(Files.readAllBytes(Paths.get("data/" + i * 10000 + ".txt")));
		}

		String[] sNumbers;
		int[][] numbers = new int[15][];

		for (int i = 0; i < 15; i++) {
			sNumbers = tabs[i].split(",");
			sNumbers[0] = sNumbers[0].substring(1, sNumbers[0].length());

			numbers[i] = new int[sNumbers.length];
			for (int j = 0; j < sNumbers.length; j++) {
				numbers[i][j] = Integer.parseInt(sNumbers[j]);
			}
		}
		
		Path rapide = Paths.get("results/rapide.txt");
		Path min_suc = Paths.get("results/min_suc.txt");
		Path bulle = Paths.get("results/bulle.txt");
		Path denombrement = Paths.get("results/denombrement.txt");
		Path fusion = Paths.get("results/fusion.txt");
		
		String sRapide = "", sMinSuc = "", sBulle = "", sDenombrement = "", sFusion = "";
		int[] tab;
		Instant start;
		Instant finish;
		double somme = 0, time;
		
		for (int i = 0; i < 15; i++) {
			
			System.out.println("\n\n*********N = "+ (i+1)*10000 + "*********\n\n");
			
			somme = 0;
			sRapide = sRapide + "N = " + (i+1)*10000 + "\n";
			for (int j = 0; j < 10; j++) {
				System.out.println("Tri Rapide, iteration N° " + (j+1));
				tab = numbers[i].clone();
				start = Instant.now();
				tri_rapide(tab, 0, tab.length-1);
				finish = Instant.now();
				time = Duration.between(start, finish).toNanos()/Math.pow(10, 9);
				somme += time;
				sRapide = sRapide + time + "\n";
			}
			sRapide = sRapide + "\nAVG = " + somme/10 + "\n\n";
			
			somme = 0;
			sMinSuc = sMinSuc + "N = " + (i+1)*10000 + "\n";
			for (int j = 0; j < 10; j++) {
				System.out.println("Tri Min Suc, iteration N° " + (j+1));
				tab = numbers[i].clone();
				start = Instant.now();
				trisMinimumSuccessif(tab);
				finish = Instant.now();
				time = Duration.between(start, finish).toNanos()/Math.pow(10, 9);
				somme += time;
				sMinSuc = sMinSuc + time + "\n";
			}
			sMinSuc = sMinSuc + "\nAVG = " + somme/10 + "\n\n";
			
			somme = 0;
			sBulle = sBulle + "N = " + (i+1)*10000 + "\n";
			for (int j = 0; j < 10; j++) {
				System.out.println("Tri Bulle, iteration N° " + (j+1));
				tab = numbers[i].clone();
				start = Instant.now();
				trisBulle(tab);
				finish = Instant.now();
				time = Duration.between(start, finish).toNanos()/Math.pow(10, 9);
				somme += time;
				sBulle = sBulle + time + "\n";
			}
			sBulle = sBulle + "\nAVG = " + somme/10 + "\n\n";
			
			somme = 0;
			sDenombrement = sDenombrement + "N = " + (i+1)*10000 + "\n";
			for (int j = 0; j < 10; j++) {
				System.out.println("Tri Denombrement, iteration N° " + (j+1));
				tab = numbers[i].clone();
				start = Instant.now();
				tri_denombrement(tab, tab.length, 32768);
				finish = Instant.now();
				time = Duration.between(start, finish).toNanos()/Math.pow(10, 9);
				somme += time;
				sDenombrement = sDenombrement + time + "\n";
			}
			sDenombrement = sDenombrement + "\nAVG = " + somme/10 + "\n\n";
			
			somme = 0;
			sFusion = sFusion + "N = " + (i+1)*10000 + "\n";
			for (int j = 0; j < 10; j++) {
				System.out.println("Tri Fusion, iteration N° " + (j+1));
				tab = numbers[i].clone();
				start = Instant.now();
				tri_fusion(tab, 0, tab.length-1);
				finish = Instant.now();
				time = Duration.between(start, finish).toNanos()/Math.pow(10, 9);
				somme += time;
				sFusion = sFusion + time + "\n";
			}
			sFusion = sFusion + "\nAVG = " + somme/10 + "\n\n";
		}
		
		Files.write(rapide, sRapide.getBytes());
		Files.write(min_suc, sMinSuc.getBytes());
		Files.write(bulle, sBulle.getBytes());
		Files.write(denombrement, sDenombrement.getBytes());
		Files.write(fusion, sFusion.getBytes());
		
		//shutdownPC();
	}
	
	public static void shutdownPC(){
	    try {
	        Runtime r = Runtime.getRuntime();
	        r.exec("shutdown -s");
	    } catch (NumberFormatException | IOException e) {
	        JOptionPane.showMessageDialog(null, "Restart failed.");
	    }
	}

	
	public static void trisMinimumSuccessif(int tab[]) {
		int i = 0, pos = 0;

		while (i < tab.length) {
			pos = posMin(tab, i);
			permuter(tab, pos, i);
			i++;
		}
	}

	public static void trisBulle(int tab[]) {
	    int i,k;
	    int permute = 1;
	
	    for (i = 0; i < tab.length && permute == 1; i++) {
	        permute = 0;
	        for (k = tab.length-1; k > i+1; k--) {
	            if (tab[k] < tab[k-1]) {
	                permuter(tab, k, k-1);
	                permute = 1;
	            }
	        }
	    }
	}

	public static int posMin(int tab[], int startPos) {
	    int position = startPos, i;
	
	    for (i = startPos+1; i < tab.length; i++) {
	        if (tab[position] > tab[i]) position = i;
	    }
	
	    return position;
	}

	public static void permuter(int tab[], int pos1, int pos2) {
	    int temps = tab[pos1];
	    tab[pos1] = tab[pos2];
	    tab[pos2] = temps;
	}

	public static int partition(int tableau[], int deb, int fin) {
		int compt = deb;
		int pivot = tableau[deb];
		int i;

		for (i = deb + 1; i <= fin; i++) {
			if (tableau[i] < pivot) {
				compt++;
				permuter(tableau, compt, i);
			}
		}
		permuter(tableau, compt, deb);
		return (compt);
	}

	public static void tri_rapide(int tableau[], int debut, int fin) {
		if (debut < fin) {
			int pivot = partition(tableau, debut, fin);
			tri_rapide(tableau, debut, pivot - 1);
			tri_rapide(tableau, pivot + 1, fin);
		}
	}
	
	public static int[] tri_denombrement(int tab[], int n, int k) {
		int i;
		int c[] = new int[k];
		int b[] = new int[n];
		
		for (i = 0; i < k; i++) c[i] = 0;
		for (i = 0; i < n; i++) b[i] = 0;
		
		for (i = 0; i < n; i++) {
			c[tab[i]] += 1;
		}

		for (i = 1; i < k; i++) {
			c[i] = c[i] + c[i-1];
		}
		for (i = n-1; i >= 0; i--) {
			b[c[tab[i]]-1] = tab[i];
			c[tab[i]] -= 1;
		}
		for (i = 0 ; i < n; i++) {
			tab[i] = b[i];
		}
		return b;
	}

	public static void tri_fusion(int tab[], int deb, int fin) {
		if (deb < fin) {
			int m = (deb+fin)/2;
			tri_fusion(tab, deb, m);
			tri_fusion(tab, m+1, fin);
			tri_fusion_fusionner(tab, deb, m, fin);
		}
	}

	public static void tri_fusion_fusionner(int tab[], int deb, int m, int fin) {
		int i, j, k, t[];
		t = new int[fin-deb+1];

		i = deb;
		j = m+1;
		k = 0;

		while (i <= m && j <= fin) {
			if (tab[i] < tab[j]) {
				t[k] = tab[i];
				i++;
			} else {
				t[k] = tab[j];
				j++;
			}
			k++;
		}

		if (i <= m) {
			for (j = i; j <= m; j++) {
				t[k] = tab[j];
				k++;
			}
		} else {
			for (i = j; i <= fin; i++) {
				t[k] = tab[i];
				k++;
			}
		}

		for (i = deb; i <= fin; i++) {
			tab[i] = t[i-deb];
		}
	}

}