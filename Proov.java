import java.util.Arrays;
import java.util.Random;
import java.util.ArrayList;
import java.util.List;
import java.util.LinkedList;
import java.util.Queue;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Calendar;

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
//         Paar<String[], int[][]> graafMat = maatriksiks("linnade_kaugused.tsv", 1000);
//         String[] linnad = graafMat.esimene;
//         int[][] mat = graafMat.teine;
//         String[] tul = jõuame("Põltsamaa", 64, 2, linnad, mat);
//         Proov proov = new Proov();
//
//         System.out.println(Arrays.toString(tul));
//         tul = proov.cppJouame("Põltsamaa", 64, 2, linnad, mat);
//
//         System.out.println(Arrays.toString(tul));
//         long n = 10000000L;
//         double[] s = new double[]{1.0, 2.0, 3.0, 1.0, 2.0, 4.0, 5.0, 2.0 };
//         //s = annaMassiiv(2000, 1, 14);
//         var alg = System.currentTimeMillis();
//         System.out.println(tukeldused(s, 7));
//         System.out.println("Java aeg: " + (System.currentTimeMillis()-alg));
//         alg = System.currentTimeMillis();
//         System.out.println(proov.cppTukeldused(s,7, s.length));
//         System.out.println("C++ aeg: " + (System.currentTimeMillis()-alg));
            Proov proov = new Proov();
            long[] isikud = new long[10000_000];
            for (int i = 0; i < 10000_000; i++) {
                isikud[i] = genereeriIsikukood();
            }
            //System.out.println(Arrays.toString(isikud));
            //isikud = new long[]{21207274409L, 82702134101L, 78908120033L, 49203256017L, 77912117196L,65408285011L};
            long aeg = System.currentTimeMillis();
            sort(isikud);
            System.out.println("Java: " + (System.currentTimeMillis() - aeg));
            aeg = System.currentTimeMillis();
            proov.cppSortIsikukoodid(isikud);
            System.out.println("Cpp: " + (System.currentTimeMillis() - aeg));

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

     static long genereeriIsikukood() {
            java.util.concurrent.ThreadLocalRandom juhus = java.util.concurrent.ThreadLocalRandom.current();
            Calendar kalender = new java.util.GregorianCalendar();
            kalender.setTime(new java.util.Date(juhus.nextLong(-5364669600000L, 7258024800000L)));
            long kood = ((kalender.get(Calendar.YEAR) - 1700) / 100 * 2 - juhus.nextInt(2)) * (long) Math.pow(10, 9) +
                    kalender.get(Calendar.YEAR) % 100 * (long) Math.pow(10, 7) +
                    (kalender.get(Calendar.MONTH) + 1) * (long) Math.pow(10, 5) +
                    kalender.get(Calendar.DAY_OF_MONTH) * (long) Math.pow(10, 3) +
                    juhus.nextLong(1000);
            int korrutisteSumma = 0;
            int[] IAstmeKaalud = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1};
            for (int i = 0; i < 10; i++) korrutisteSumma += kood / (long) Math.pow(10, i) % 10 * IAstmeKaalud[9 - i];
            int kontroll = korrutisteSumma % 11;
            if (kontroll == 10) {
                korrutisteSumma = 0;
                int[] IIAstmeKaalud = {3, 4, 5, 6, 7, 8, 9, 1, 2, 3};
                for (int i = 0; i < 10; i++) korrutisteSumma += kood / (long) Math.pow(10, i) % 10 * IIAstmeKaalud[9 - i];
                kontroll = korrutisteSumma % 11;
                kontroll = kontroll < 10 ? kontroll : 0;
            }
            return kood * 10 + kontroll;
        }


    static void countingSort(List<Long> array, int size, long place, int vahemik) {
        /**
         * @Funk - Rakendab counting sort
         */
        long[] output = new long[size + 1];
        long max = array.get(0);
        for (int i = 1; i < size; i++) {
            if (array.get(0) > max)
                max = array.get(0);
        }
        long[] count = new long[vahemik];


        // Calculate count of elements
        for (int i = 0; i < size; i++) {
            count[(int) ((array.get(i) / place) % 10)]++;
        }
        // Calculate cumulative count
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        // Place the elements in sorted order
        for (int i = size - 1; i >= 0; i--) {
            output[(int) (count[(int) ((array.get(i) / place) % 10)] - 1)] = array.get(i);
            count[(int) ((array.get(i) / place) % 10)]--;
        }

        for (int i = 0; i < size; i++)
            array.set(i,output[i]);
    }


    //Jaga kohe alguses 1 ja 2, 3 ja 4, 5 ja 6 jne ära ja käsitle neid eraldi.
    static List<Long> radixSort(List<Long> list, int size) {
        // Get maximum element
        long max = 8991231999L;
        /**Arrays.stream(array).forEach(id -> {
            id /= 10;
            System.out.println(id);
        });*/

        // Apply counting sort to sort elements based on place value.
        //for (int place = 1; max / place > 10; place *= 10)
        countingSort(list, size, 1,10); //10
        countingSort(list, size, 10,10); //10
        countingSort(list, size, 100,10); //10
        countingSort(list, size, 1000,10); //10
        countingSort(list, size, 10000,10); //4
        countingSort(list, size, 100000,10); //10
        countingSort(list, size, 1000000,10); //2
        countingSort(list, size, 10000000,10); //10
        countingSort(list, size, 100000000,10); //10
        countingSort(list, size, 1000000000,10); //10

        return list;
    }



    /** Sorteerib isikukoodid sünniaja järgi:
     * <ul style="list-style-type:none">
     *     <li>a) järjestuse aluseks on sünniaeg, vanemad inimesed on eespool;</li>
     *     <li>b) kui sünniajad on võrdsed, määrab järjestuse isikukoodi järjekorranumber (kohad 8-10);</li>
     *     <li>c) kui ka järjekorranumber on võrdne, siis määrab järjestuse esimene number.</li>
     * </ul>
     * @param isikukoodid sorteeritav isikukoodide massiiv
     */
    public static void sort(long[] isikukoodid){
        /**radixSort(isikukoodid, isikukoodid.length);
        for (int i = 0; i < isikukoodid.length; i++) {
            int kontroll=security(isikukoodid[i]);
            isikukoodid[i]=isikukoodid[i]*10+kontroll;
        }*/
        List<Long> list= new ArrayList<>();
        for (int i = 0; i < isikukoodid.length; i++) {
            list.add(isikukoodid[i]);
        }
        countingSort(list, list.size(), 1000000000L, 10);

        List<Long> ykskaks= new ArrayList<>();
        List<Long> kolmneli= new ArrayList<>();
        List<Long> viiskuus= new ArrayList<>();
        List<Long> seitsekaheksa= new ArrayList<>();

        for (int i = 0; i < isikukoodid.length; i++) {
            //isikukoodid[i]=isikukoodid[i]/10;
            if(list.get(i)<30000000000L){
                ykskaks.add(list.get(i));
            }
            else if(list.get(i)<50000000000L){
                kolmneli.add(list.get(i));
            }
            else if(list.get(i)<70000000000L){
                viiskuus.add(list.get(i));
            }
            else if(list.get(i)<90000000000L){
                seitsekaheksa.add(list.get(i));
            }
        }
        int isikukoodidindex=0;
        if(ykskaks.size()>0){
            List<Long> yk= radixSort(ykskaks, ykskaks.size());
            for (Long aLong : yk) {
                isikukoodid[isikukoodidindex] = aLong;
                isikukoodidindex += 1;
            }
        }
        if(kolmneli.size()>0){
            List<Long> kn= radixSort(kolmneli,kolmneli.size());
            for (Long aLong : kn) {
                isikukoodid[isikukoodidindex]=aLong;
                isikukoodidindex+=1;
            }
        }
        if(viiskuus.size()>0){
            List<Long> vk= radixSort(viiskuus,viiskuus.size());
            for (Long aLong : vk) {
                isikukoodid[isikukoodidindex]=aLong;
                isikukoodidindex+=1;
            }
        }
        if(seitsekaheksa.size()>0){
            List<Long> sk= radixSort(seitsekaheksa,seitsekaheksa.size());
            for (Long aLong : sk) {
                isikukoodid[isikukoodidindex]=aLong;
                isikukoodidindex+=1;
            }
        }
    }







    private native int cppTukeldused(double[] a, double p, int length);
    private native String[] cppJouame(String lahtelinn, int x, int k, String[] linnad, int[][] m);
    private native long[] cppSortIsikukoodid(long[] isikukoodid);
}