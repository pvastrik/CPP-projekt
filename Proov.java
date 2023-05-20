import java.util.Arrays;
import java.util.Random;
import java.util.ArrayList;
import java.util.List;
import java.util.LinkedList;
import java.util.Queue;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
public class Proov {

    static {
        System.loadLibrary("native");
    }
    static class Paar<A, B> {
        A esimene;
        B teine;
        public Paar(A esimene, B teine) {
            this.esimene = esimene;
            this.teine = teine;
        }
    }

    static class GTipp {

       int info;
       List<Kaar> kaared;
       int kaugus;
       int kaari;

       public GTipp(int info) {
           this.info = info;
           kaared = new ArrayList<>();
           kaugus = -1;
           kaari = 0;
       }

       void lisaKaar(Kaar kaar) {
           kaared.add(kaar);
       }
    }

    static class Kaar {
       int kaal;
       GTipp algus;
       GTipp lõpp;

       public Kaar(int kaal, GTipp algus, GTipp lõpp) {
           this.kaal = kaal;
           this.algus = algus;
           this.lõpp = lõpp;
       }

   }

    public static void main(String[] args) {
        Paar<String[], int[][]> graafMat = maatriksiks("linnade_kaugused.tsv", 1000);
        String[] linnad = graafMat.esimene;
        int[][] mat = graafMat.teine;
        String[] tul = jõuame("Põltsamaa", 64, 2, linnad, mat);
        Proov proov = new Proov();

        System.out.println(Arrays.toString(tul));
        tul = proov.cppJouame("Põltsamaa", 64, 2, linnad, mat);

        System.out.println(Arrays.toString(tul));
        long n = 10000000L;
        double[] s = new double[]{1.0, 2.0, 3.0, 1.0, 2.0, 4.0, 5.0, 2.0 };
        //s = annaMassiiv(2000, 1, 14);
        var alg = System.currentTimeMillis();
        System.out.println(tukeldused(s, 7));
        System.out.println("Java aeg: " + (System.currentTimeMillis()-alg));
        alg = System.currentTimeMillis();
        System.out.println(proov.cppTukeldused(s,7, s.length));
        System.out.println("C++ aeg: " + (System.currentTimeMillis()-alg));

    }
     /*
            Traat pikkusega p lõigatakse tükkideks (tükkide pikkused on positiivsed). Lubatud traadipikkuste väärtused
            on etteantud reaalarvuliste väärtustega massiiviga a. Tükeldamisel peab arvestama, et sama pikkusega traate
            võib lõigata kuitahes palju.


            * Antud: ujukomaarvude massiiv a ja traadi pikkus p
            * Tulemus: tagastab võimalike traadi tükelduste arvu massiivis antud pikkusteks nii, et ülejääk oleks väiksem
            * kui vähim element massiivis
            * */
            public static int tukeldused(double[] a, double p) {
                Arrays.sort(a); //et leida vähim element, sorteerime kõigepeal järjendi ning võtame selle esimese elemendi
                return tukeldusedRek(a, p, a[0], 0);
            }

            static int tukeldusedRek(double[] a, double p, double min, int i) {
                int kokku = 0;
                if (p < min){
                    if (p >= 0) return 1;
                    return 0;
                }


                for (;i<a.length;i++) {
                    if (a[i] > p) break;
                    kokku += tukeldusedRek(a,p - a[i], min, i);
                }
                return kokku;

            }

    /*
        Failis linnade_kaugused.tsv on antud Eesti suuremate asulate omavahelised kaugused.

         Olgu meil elektriauto, mis võimaldab ühe laadimiskorraga sõita x kilomeetrit ja akusid laadida
         saab vaid tabelis nimetatud asulates. Eesmärgiks on koostada programm, mis vastavalt etteaantud
         väärtuse x ja lubatud tankimiste arvu k järgi leiab lähtelinnast alustades need linnad, mis on k
         tankimise kaugusel. Kokkuleppeliselt loeme, et tankimiskordade arv võrdub läbitud kaarte arvuga.

        * Meetod antud laadimiste arvu kaugusel olevate linnade leidmiseks
        * Antud: lähtelinn, elektriauto aku suurus (km) k, laadimiskordade arv x, linnade massiiv, graafi esitus maatriksina
        * Tulemus: linnade massiiv, kuhu antu akuga lühim tee võtab täpselt k laadimist ehksiis k linnadevahelist sõitu
        * */
        public static String[] jõuame(String lähtelinn, int x, int k, String[] linnad, int[][] M) {
            int lähte = Arrays.asList(linnad).indexOf(lähtelinn);
            List<Integer> saab = new ArrayList<>();
            List<GTipp> graaf = graafiks(M, x), läbitud = new LinkedList<>();
            GTipp prg = graaf.get(lähte);
            Queue<Kaar> järjekord = new LinkedList<>(prg.kaared); //töödeldavad kaared
            läbitud.add(prg);
            while (!järjekord.isEmpty()) {
                Kaar praegune = järjekord.poll(); //võtame järjest kaari

                prg = praegune.lõpp;
                if (!läbitud.contains(prg)) { //kui kaare lõpppunkt on juba läbitud, siis pole vaja seda enam vaadata
                    for (Kaar kaar : prg.kaared) { //lisame kõik väljuvad kaared järjekorda, mille lõppu pole veel läbitud
                        if (!läbitud.contains(kaar.lõpp)) {
                            järjekord.add(kaar);
                        }
                    }
                    // kõikide kaarte algused on juba läbi töödeldud, seega on sinna lisatud õige kaarte arv alates lähtetipust
                    prg.kaari = praegune.algus.kaari + 1;

                    if (prg.kaari == k) {
                        saab.add(prg.info);
                    }
                    läbitud.add(prg);
                }
            }

            String[] tul = saab.stream().map(y -> linnad[y]).toList().toArray(new String[0]);
            Arrays.sort(tul);
            return tul;
        }

        static List<GTipp> graafiks(int[][] M, int x) {
            //räpane :((
            List<GTipp> graaf = new ArrayList<>();
            for (int i = 0; i < M.length; i++) {
                GTipp tipp;
                if (graaf.size() <= i) { //kontroll, et ei looks uut tippu, kui pole vaja ja kõik kaared läheks ikka õige tipu alla.
                    tipp = new GTipp(i);
                    graaf.add(tipp);
                } else tipp = graaf.get(i);

                for (int j = 0; j < M.length; j++) {
                    GTipp teine;
                    if (j >= graaf.size()) {
                        teine = new GTipp(j);
                        graaf.add(teine);
                    } else {
                        teine = graaf.get(j);
                    }
                    if (M[i][j] > 0 && M[i][j] <= x) {
                        Kaar kaar = new Kaar(M[i][j], tipp, teine);
                        tipp.kaared.add(kaar);
                    }
                }
            }
            return graaf;
        }

    static Paar<String[], int[][]> maatriksiks(String failinimi, int maxkaugus) {
        List<String[]> andmed;
        try {
            andmed = Files.readAllLines(Path.of(failinimi)).stream().map(s->s.split("\t")).toList();
        } catch (IOException e) {
            return null;
        }

        String[] linnad = new String[andmed.size()];
        int[][] mat = new int[linnad.length][linnad.length];

        for (int i = 0; i < andmed.size(); i++) {
            linnad[i] = andmed.get(i)[0];
            for (int j = 1; j <= andmed.size(); j++) {
                if (i == j-1) continue;
                String anne = andmed.get(i)[j];
                int kaugus = Integer.parseInt(anne);
                mat[i][j-1] = kaugus > maxkaugus ? -1 : kaugus;
            }
        }

        return new Paar<>(linnad, mat);
    }

    public static double[] annaMassiiv(int n, int min, int max) {
        return new Random().doubles(n, min, max).toArray();
    }


    private native int cppTukeldused(double[] a, double p, int length);
    private native String[] cppJouame(String lahtelinn, int x, int k, String[] linnad, int[][] m);
    private native long[] cppSortIsikukoodid(long[] isikukoodid);
}