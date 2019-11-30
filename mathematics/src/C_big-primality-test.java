import java.math.BigInteger;
import java.util.Scanner;
 
public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        long c = Long.parseLong(in.nextLine());
        for (long i = 0; i < c; ++i) {
            if (isPrime(in.nextLine())) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
    }
 
    static boolean isPrime(String num) {
        BigInteger b = new BigInteger(num);
        return b.isProbablePrime(9);
    }
}