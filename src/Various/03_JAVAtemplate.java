import java.io.*;
import java.util.*;

public class SolutionF { 
    static Random random;
 
    /* public static void main(String[] args){
        new Thread(null, new SolutionF (), "Main", 1<<26).start();
    } */
 
    public static void main(String[] args) {
        FastScanner in = new FastScanner();
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        random = new Random();
 
        // long timeStamp = System.currentTimeMillis();
        Solver solver = new Solver();
        solver.solve(in, out);
        out.close();
        // System.err.println("TIME: "+(System.currentTimeMillis()-timeStamp)+" ms");
    }
 
    /* ------------------------------------- START -------------------------------------------- */
    static class Solver {
        public void solve(FastScanner in, PrintWriter out) {

        }
    }
    /* -------------------------------------- END --------------------------------------------- */
 
    /* Shuffle function to shuffle before Arrays.sort */
    static void shuffle(int[] arr){
        int swapTemp;
        for(int i = arr.length-1; i>= 1; i--){
            int pos = random.nextInt(i+1);
            if(pos == i) continue;
            {swapTemp = arr[i]; arr[i] = arr[pos]; arr[pos] = swapTemp;}
        }
    }
 
    /* Fast Input reader */
    static class FastScanner {
        BufferedReader reader;
        StreamTokenizer tokenizer;
        public FastScanner() {
            reader = new BufferedReader(new InputStreamReader(System.in));
            tokenizer = new StreamTokenizer(reader);
            tokenizer.resetSyntax();
            tokenizer.whitespaceChars(0, 32);
            tokenizer.wordChars(33, 126);
        }
        private void nextToken() {
            try{ tokenizer.nextToken(); }
            catch (Exception e) { e.printStackTrace(); }
        }
        String next() {
            nextToken();
            return tokenizer.sval;
        }
        int nextInt() {
            nextToken();
            return Integer.parseInt(tokenizer.sval);
        }
        long nextLong() {
            nextToken();
            return Long.parseLong(tokenizer.sval);
        }
        double nextDouble() {
            nextToken();
            return Double.parseDouble(tokenizer.sval);
        }
        String nextLine() {
            try{
                String string = reader.readLine();
                return string;
            } catch (Exception e) {
                e.printStackTrace();
                return "";
            }
        }
    }
}
