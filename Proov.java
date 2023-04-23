public class Proov {
    static {
        System.loadLibrary("native");
    }
    public static void main(String[] args) {
        long n = 10000000L;
        Proov proov = new Proov();
        var alg = System.currentTimeMillis();
        int a = 0;
        for (int i = 0; i < n; i++) {
            a++;
        }
        System.out.println("Java aeg: " + (System.currentTimeMillis()-alg));
        alg = System.currentTimeMillis();
        proov.prooviLoopi(n);
        System.out.println("C++ aeg: " + (System.currentTimeMillis()-alg));

    }

    private native void prooviLoopi(long n);

}